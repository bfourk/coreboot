/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <arch/cpu.h>
#include <assert.h>
#include <cbmem.h>
#include <cf9_reset.h>
#include <console/console.h>
#include <cpu/x86/msr.h>
#include <device/pci_ops.h>
#include <mrc_cache.h>
#include <northbridge/intel/haswell/haswell.h>
#include <northbridge/intel/haswell/raminit.h>
#include <southbridge/intel/lynxpoint/me.h>
#include <southbridge/intel/lynxpoint/pch.h>
#include <types.h>

#include "raminit_native.h"

static void wait_txt_clear(void)
{
	const struct cpuid_result cpuid = cpuid_ext(1, 0);

	/* Check if TXT is supported */
	if (!(cpuid.ecx & BIT(6)))
		return;

	/* Some TXT public bit */
	if (!(read32p(0xfed30010) & 1))
		return;

	/* Wait for TXT clear */
	do {} while (!(read8p(0xfed40000) & (1 << 7)));
}

static enum raminit_boot_mode get_boot_mode(void)
{
	const uint16_t pmcon_2 = pci_read_config16(PCH_LPC_DEV, GEN_PMCON_2);
	const uint16_t bitmask = GEN_PMCON_2_DISB | GEN_PMCON_2_MEM_SR;
	return (pmcon_2 & bitmask) == bitmask ? BOOTMODE_WARM : BOOTMODE_COLD;
}

static bool early_init_native(enum raminit_boot_mode bootmode)
{
	printk(BIOS_DEBUG, "Starting native platform initialisation\n");

	intel_early_me_init();
	bool cpu_replaced = bootmode == BOOTMODE_COLD && intel_early_me_cpu_replacement_check();

	early_pch_init_native(bootmode == BOOTMODE_S3);

	if (!CONFIG(INTEL_LYNXPOINT_LP))
		dmi_early_init();

	return cpu_replaced;
}

static void save_mrc_data(void)
{
	mrc_cache_stash_data(MRC_TRAINING_DATA, reg_frame_rev(),
			     reg_frame_ptr(), reg_frame_size());
}

static struct mrc_data prepare_mrc_cache(void)
{
	struct mrc_data md = {0};
	md.buffer = mrc_cache_current_mmap_leak(MRC_TRAINING_DATA,
						reg_frame_rev(),
						&md.buffer_len);
	return md;
}

static const char *const bm_names[] = {
	"BOOTMODE_COLD",
	"BOOTMODE_WARM",
	"BOOTMODE_S3",
	"BOOTMODE_FAST",
};

static void clear_disb(void)
{
	pci_and_config16(PCH_LPC_DEV, GEN_PMCON_2, ~GEN_PMCON_2_DISB);
}

static void raminit_reset(void)
{
	clear_disb();
	system_reset();
}

static enum raminit_boot_mode do_actual_raminit(
	const bool s3resume,
	const bool cpu_replaced,
	const enum raminit_boot_mode orig_bootmode)
{
	struct mrc_data md = prepare_mrc_cache();

	enum raminit_boot_mode bootmode = orig_bootmode;

	bool save_data_valid = md.buffer && md.buffer_len == reg_frame_size();

	if (s3resume) {
		if (bootmode == BOOTMODE_COLD) {
			printk(BIOS_EMERG, "Memory may not be in self-refresh for S3 resume\n");
			printk(BIOS_EMERG, "S3 resume and cold boot are mutually exclusive\n");
			raminit_reset();
		}
		/* Only a true mad hatter would replace a CPU in S3 */
		if (cpu_replaced) {
			printk(BIOS_EMERG, "Oh no, CPU was replaced during S3\n");
			/*
			 * No reason to continue, memory consistency is most likely lost
			 * and ME will probably request a reset through DID response too.
			 */
			/** TODO: Figure out why past self commented this out **/
			//raminit_reset();
		}
		bootmode = BOOTMODE_S3;
		if (!save_data_valid) {
			printk(BIOS_EMERG, "No training data, S3 resume is impossible\n");
			/* Failed S3 resume, reset to come up cleanly */
			raminit_reset();
		}
	}
	if (!s3resume && cpu_replaced) {
		printk(BIOS_NOTICE, "CPU was replaced, forcing a cold boot\n");
		/*
		 * Looks like the ME will get angry if raminit takes too long.
		 * It will report that the CPU has been replaced on next boot.
		 * Try to continue anyway. This should not happen in most cases.
		 */
		/** TODO: Figure out why past self commented this out **/
		//save_data_valid = false;
	}
	if (bootmode == BOOTMODE_COLD) {
		/* If possible, promote to a fast boot */
		if (save_data_valid)
			bootmode = BOOTMODE_FAST;

		clear_disb();
	} else if (bootmode == BOOTMODE_WARM) {
		/* If a warm reset happened before raminit is done, force a cold boot */
		if (mchbar_read32(SSKPD) == 0 && mchbar_read32(SSKPD + 4) == 0) {
			printk(BIOS_NOTICE, "Warm reset occurred early in cold boot\n");
			save_data_valid = false;
		}
		if (!save_data_valid)
			bootmode = BOOTMODE_COLD;
	}
	assert(save_data_valid != (bootmode == BOOTMODE_COLD));
	if (save_data_valid) {
		printk(BIOS_INFO, "Using cached memory parameters\n");
		memcpy(reg_frame_ptr(), md.buffer, reg_frame_size());
	}
	printk(RAM_DEBUG, "Initial bootmode: %s\n", bm_names[orig_bootmode]);
	printk(RAM_DEBUG, "Current bootmode: %s\n", bm_names[bootmode]);

	/*
	 * And now, the actual memory initialization thing.
	 */
	printk(RAM_DEBUG, "\nStarting native raminit\n");
	raminit_main(bootmode);

	return bootmode;
}

void perform_raminit(const int s3resume)
{
	/*
	 * See, this function's name is a lie. There are more things to
	 * do that memory initialisation, but they are relatively easy.
	 */
	const enum raminit_boot_mode orig_bootmode = get_boot_mode();

	const bool cpu_replaced = early_init_native(s3resume ? BOOTMODE_S3 : orig_bootmode);

	wait_txt_clear();
	wrmsr(0x2e6, (msr_t) {.lo = 0, .hi = 0});

	const enum raminit_boot_mode bootmode =
			do_actual_raminit(s3resume, cpu_replaced, orig_bootmode);

	/** TODO: report_memory_config **/

	if (intel_early_me_uma_size() > 0) {
		/*
		 * The 'other' success value is to report loss of memory
		 * consistency to ME if warm boot was downgraded to cold.
		 */
		uint8_t me_status;
		if (BOOTMODE_WARM == orig_bootmode && BOOTMODE_COLD == bootmode)
			me_status = ME_INIT_STATUS_SUCCESS_OTHER;
		else
			me_status = ME_INIT_STATUS_SUCCESS;

		intel_early_me_init_done(me_status);
	}

	intel_early_me_status();

	const bool cbmem_was_initted = !cbmem_recovery(s3resume);
	if (s3resume && !cbmem_was_initted) {
		/* Failed S3 resume, reset to come up cleanly */
		printk(BIOS_CRIT, "Failed to recover CBMEM in S3 resume.\n");
		system_reset();
	}

	/* Save training data on non-S3 resumes */
	if (!s3resume)
		save_mrc_data();

	/** TODO: setup_sdram_meminfo **/
}
