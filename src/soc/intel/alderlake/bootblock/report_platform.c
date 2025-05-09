/* SPDX-License-Identifier: GPL-2.0-only */

/*
 * This file is created based on Intel Alder Lake Platform Stepping and IDs
 * Document number: 619362, 619501
 * Chapter number: 2, 14
 */

#include <commonlib/helpers.h>
#include <console/console.h>
#include <cpu/cpu.h>
#include <cpu/intel/cpu_ids.h>
#include <cpu/intel/microcode.h>
#include <cpu/x86/msr.h>
#include <cpu/x86/name.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <device/pci_ops.h>
#include <intelblocks/car_lib.h>
#include <soc/bootblock.h>
#include <soc/pci_devs.h>

static struct {
	u32 cpuid;
	const char *name;
} cpu_table[] = {
	{ CPUID_ALDERLAKE_J0, "Alderlake J0 Platform" },
	{ CPUID_ALDERLAKE_K0, "Alderlake K0 Platform" },
	{ CPUID_ALDERLAKE_L0, "Alderlake L0 Platform" },
	{ CPUID_ALDERLAKE_Q0, "Alderlake Q0 Platform" },
	{ CPUID_ALDERLAKE_R0, "Alderlake R0 Platform" },
	{ CPUID_ALDERLAKE_N_A0, "Alderlake-N Platform" },
	{ CPUID_ALDERLAKE_A0, "Alderlake A0 Platform" },
	{ CPUID_ALDERLAKE_B0, "Alderlake B0 Platform" },
	{ CPUID_ALDERLAKE_C0, "Alderlake C0 Platform" },
	{ CPUID_ALDERLAKE_G0, "Alderlake G0 Platform" },
	{ CPUID_ALDERLAKE_H0, "Alderlake H0 Platform" },
	{ CPUID_RAPTORLAKE_A0, "Raptorlake A0 Platform" },
	{ CPUID_RAPTORLAKE_B0, "Raptorlake B0 Platform" },
	{ CPUID_RAPTORLAKE_C0, "Raptorlake C0 Platform" },
	{ CPUID_RAPTORLAKE_H0, "Raptorlake H0 Platform" },
	{ CPUID_RAPTORLAKE_J0, "Raptorlake J0 Platform" },
	{ CPUID_RAPTORLAKE_Q0, "Raptorlake Q0 Platform" },
};

static struct {
	u16 mchid;
	const char *name;
} mch_table[] = {
	{ PCI_DID_INTEL_ADL_P_ID_1, "Alderlake-P" },
	{ PCI_DID_INTEL_ADL_P_ID_3, "Alderlake-P" },
	{ PCI_DID_INTEL_ADL_P_ID_4, "Alderlake-P" },
	{ PCI_DID_INTEL_ADL_P_ID_5, "Alderlake-P" },
	{ PCI_DID_INTEL_ADL_P_ID_6, "Alderlake-P" },
	{ PCI_DID_INTEL_ADL_P_ID_7, "Alderlake-P" },
	{ PCI_DID_INTEL_ADL_P_ID_8, "Alderlake-P" },
	{ PCI_DID_INTEL_ADL_P_ID_9, "Alderlake-P" },
	{ PCI_DID_INTEL_ADL_P_ID_10, "Alderlake-P" },
	{ PCI_DID_INTEL_ADL_M_ID_1, "Alderlake-M" },
	{ PCI_DID_INTEL_ADL_M_ID_2, "Alderlake-M" },
	{ PCI_DID_INTEL_ADL_N_ID_1, "Alderlake-N" },
	{ PCI_DID_INTEL_ADL_N_ID_2, "Alderlake-N" },
	{ PCI_DID_INTEL_ADL_N_ID_3, "Alderlake-N" },
	{ PCI_DID_INTEL_ADL_N_ID_4, "Alderlake-N" },
	{ PCI_DID_INTEL_ADL_N_ID_5, "Alderlake-N" },
	{ PCI_DID_INTEL_ADL_N_ID_6, "Alderlake-N" },
	{ PCI_DID_INTEL_ADL_N_ID_7, "Alderlake-N" },
	{ PCI_DID_INTEL_ADL_N_ID_8, "Alderlake-N" },
	{ PCI_DID_INTEL_ADL_N_ID_9, "Alderlake-N" },
	{ PCI_DID_INTEL_ADL_S_ID_1, "Alderlake-S (8+8)" },
	{ PCI_DID_INTEL_ADL_S_ID_2, "Alderlake-S" },
	{ PCI_DID_INTEL_ADL_S_ID_3, "Alderlake-S (8+4)" },
	{ PCI_DID_INTEL_ADL_S_ID_4, "Alderlake-S" },
	{ PCI_DID_INTEL_ADL_S_ID_5, "Alderlake-S (8+0)" },
	{ PCI_DID_INTEL_ADL_S_ID_6, "Alderlake-S" },
	{ PCI_DID_INTEL_ADL_S_ID_7, "Alderlake-S" },
	{ PCI_DID_INTEL_ADL_S_ID_8, "Alderlake-S (6+4)" },
	{ PCI_DID_INTEL_ADL_S_ID_9, "Alderlake-S" },
	{ PCI_DID_INTEL_ADL_S_ID_10, "Alderlake-S (6+0)" },
	{ PCI_DID_INTEL_ADL_S_ID_11, "Alderlake-S (4+0)" },
	{ PCI_DID_INTEL_ADL_S_ID_12, "Alderlake-S (2+0)" },
	{ PCI_DID_INTEL_ADL_S_ID_13, "Alderlake-S" },
	{ PCI_DID_INTEL_ADL_S_ID_14, "Alderlake-S" },
	{ PCI_DID_INTEL_ASL_ID_1, "Amstonlake" },
	{ PCI_DID_INTEL_ASL_ID_2, "Amstonlake" },
	{ PCI_DID_INTEL_ASL_ID_3, "Amstonlake" },
	{ PCI_DID_INTEL_RPL_HX_ID_1, "Raptorlake-HX (8+16)" },
	{ PCI_DID_INTEL_RPL_HX_ID_2, "Raptorlake-HX (8+12)" },
	{ PCI_DID_INTEL_RPL_HX_ID_3, "Raptorlake-HX (8+8)" },
	{ PCI_DID_INTEL_RPL_HX_ID_4, "Raptorlake-HX (6+8)" },
	{ PCI_DID_INTEL_RPL_HX_ID_5, "Raptorlake-HX (6+4)" },
	{ PCI_DID_INTEL_RPL_HX_ID_6, "Raptorlake-HX (8+8)" },
	{ PCI_DID_INTEL_RPL_HX_ID_7, "Raptorlake-HX (6+8)" },
	{ PCI_DID_INTEL_RPL_HX_ID_8, "Raptorlake-HX (6+4)" },
	{ PCI_DID_INTEL_RPL_P_ID_1, "Raptorlake-P/H/H Refresh (6+8)" },
	{ PCI_DID_INTEL_RPL_P_ID_2, "Raptorlake-P/H/H Refresh (4+8)" },
	{ PCI_DID_INTEL_RPL_P_ID_3, "Raptorlake-U/U Refresh (2+8)" },
	{ PCI_DID_INTEL_RPL_P_ID_4, "Raptorlake-U/U Refresh (2+4)" },
	{ PCI_DID_INTEL_RPL_P_ID_5, "Raptorlake-U (1+4)" },
	{ PCI_DID_INTEL_RPL_P_ID_6, "Raptorlake-PX (6+8)" },
	{ PCI_DID_INTEL_RPL_P_ID_7, "Raptorlake-PX (4+8)" },
	{ PCI_DID_INTEL_RPL_P_ID_8, "Raptorlake-H (4+4)" },
	{ PCI_DID_INTEL_RPL_S_ID_1, "Raptorlake-S (8+16)" },
	{ PCI_DID_INTEL_RPL_S_ID_2, "Raptorlake-S (8+0)" },
	{ PCI_DID_INTEL_RPL_S_ID_3, "Raptorlake-S (8+8)" },
	{ PCI_DID_INTEL_RPL_S_ID_4, "Raptorlake-S (6+8)" },
	{ PCI_DID_INTEL_RPL_S_ID_5, "Raptorlake-S (6+4)" },
};

static struct {
	u16 espiid;
	const char *name;
} pch_table[] = {
	{ PCI_DID_INTEL_ADP_M_N_ESPI_1, "Alderlake-N SKU" },
	{ PCI_DID_INTEL_ADP_M_N_ESPI_2, "Alderlake-N SKU" },
	{ PCI_DID_INTEL_ADP_M_N_ESPI_10, "Amstonlake SKU" },
	{ PCI_DID_INTEL_ADP_S_ESPI_H610E, "AlderLake-S H610E" },
	{ PCI_DID_INTEL_ADP_S_ESPI_Q670E, "AlderLake-S Q670E" },
	{ PCI_DID_INTEL_ADP_S_ESPI_R680E, "AlderLake-S R680E" },
	{ PCI_DID_INTEL_ADP_S_ESPI_H610, "AlderLake-S H610" },
	{ PCI_DID_INTEL_ADP_S_ESPI_B660, "AlderLake-S B660" },
	{ PCI_DID_INTEL_ADP_S_ESPI_H670, "AlderLake-S H670" },
	{ PCI_DID_INTEL_ADP_S_ESPI_Q670, "AlderLake-S Q670" },
	{ PCI_DID_INTEL_ADP_S_ESPI_Z690, "AlderLake-S Z690" },
	{ PCI_DID_INTEL_ADP_S_ESPI_W680, "AlderLake-S W680" },
	{ PCI_DID_INTEL_ADP_S_ESPI_W790, "AlderLake-S W790" },
	{ PCI_DID_INTEL_ADP_S_ESPI_WM690, "AlderLake-S WM690" },
	{ PCI_DID_INTEL_ADP_S_ESPI_HM670, "AlderLake-S HM670" },
	{ PCI_DID_INTEL_RPP_S_ESPI_0, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_1, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_2, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_3, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_Z790, "Raptorlake-S Z790" },
	{ PCI_DID_INTEL_RPP_S_ESPI_H770, "Raptorlake-S H770" },
	{ PCI_DID_INTEL_RPP_S_ESPI_B760, "Raptorlake-S B760" },
	{ PCI_DID_INTEL_RPP_S_ESPI_7, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_8, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_9, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_10, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_11, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_HM770, "Raptorlake-S HM770" },
	{ PCI_DID_INTEL_RPP_S_ESPI_WM790, "Raptorlake-S WM790" },
	{ PCI_DID_INTEL_RPP_S_ESPI_14, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_15, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_16, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_17, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_18, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_19, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_20, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_21, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_22, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_23, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_24, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_25, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_26, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_27, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_28, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_29, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_30, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_S_ESPI_31, "Raptorlake-S SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_0, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ADP_P_ESPI_1, "Alderlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ADP_P_ESPI_2, "Alderlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_3, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_4, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_5, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ADP_M_ESPI_6, "Alderlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_7, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_8, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_9, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_10, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_11, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_12, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_13, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_14, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_15, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_16, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_17, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_18, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_19, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_20, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_21, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_22, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_23, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_24, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_25, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_26, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_27, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_28, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_29, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_30, "Raptorlake-P SKU" },
	{ PCI_DID_INTEL_RPP_P_ESPI_31, "Raptorlake-P SKU" },
};

static struct {
	u16 igdid;
	const char *name;
} igd_table[] = {
	{ PCI_DID_INTEL_ADL_GT0, "Alderlake GT0" },
	{ PCI_DID_INTEL_ADL_GT1, "Alderlake GT1" },
	{ PCI_DID_INTEL_ADL_GT1_1, "Alderlake GT1" },
	{ PCI_DID_INTEL_ADL_GT1_2, "Alderlake GT1" },
	{ PCI_DID_INTEL_ADL_GT1_3, "Alderlake GT1" },
	{ PCI_DID_INTEL_ADL_GT1_4, "Alderlake GT1" },
	{ PCI_DID_INTEL_ADL_GT1_5, "Alderlake GT1" },
	{ PCI_DID_INTEL_ADL_GT1_6, "Alderlake GT1" },
	{ PCI_DID_INTEL_ADL_GT1_7, "Alderlake GT1" },
	{ PCI_DID_INTEL_ADL_GT1_8, "Alderlake GT1" },
	{ PCI_DID_INTEL_ADL_GT1_9, "Alderlake GT1" },
	{ PCI_DID_INTEL_ADL_P_GT2, "Alderlake P GT2" },
	{ PCI_DID_INTEL_ADL_P_GT2_1, "Alderlake P GT2" },
	{ PCI_DID_INTEL_ADL_P_GT2_2, "Alderlake P GT2" },
	{ PCI_DID_INTEL_ADL_P_GT2_3, "Alderlake P GT2" },
	{ PCI_DID_INTEL_ADL_P_GT2_4, "Alderlake P GT2" },
	{ PCI_DID_INTEL_ADL_P_GT2_5, "Alderlake P GT2" },
	{ PCI_DID_INTEL_ADL_P_GT2_6, "Alderlake P GT2" },
	{ PCI_DID_INTEL_ADL_P_GT2_7, "Alderlake P GT2" },
	{ PCI_DID_INTEL_ADL_P_GT2_8, "Alderlake P GT2" },
	{ PCI_DID_INTEL_ADL_P_GT2_9, "Alderlake P GT2" },
	{ PCI_DID_INTEL_ADL_M_GT1, "Alderlake M GT1" },
	{ PCI_DID_INTEL_ADL_M_GT2, "Alderlake M GT2" },
	{ PCI_DID_INTEL_ADL_M_GT3, "Alderlake M GT3" },
	{ PCI_DID_INTEL_ADL_N_GT1, "Alderlake N GT1" },
	{ PCI_DID_INTEL_ADL_N_GT2, "Alderlake N GT2" },
	{ PCI_DID_INTEL_ADL_N_GT3, "Alderlake N GT3" },
	{ PCI_DID_INTEL_ADL_N_GT4, "Alderlake N GT4" },
	{ PCI_DID_INTEL_ADL_N_GT5, "Alderlake N GT5" },
	{ PCI_DID_INTEL_ADL_S_GT1,   "Alderlake S GT1" },
	{ PCI_DID_INTEL_ADL_S_GT1_1, "Alderlake S GT1" },
	{ PCI_DID_INTEL_ADL_S_GT2,   "Alderlake S GT2" },
	{ PCI_DID_INTEL_ADL_S_GT2_1, "Alderlake S GT2" },
	{ PCI_DID_INTEL_ADL_S_GT2_2, "Alderlake S GT2" },
	{ PCI_DID_INTEL_RPL_HX_GT1, "Raptorlake HX GT1" },
	{ PCI_DID_INTEL_RPL_HX_GT2, "Raptorlake HX GT2" },
	{ PCI_DID_INTEL_RPL_HX_GT3, "Raptorlake HX GT3" },
	{ PCI_DID_INTEL_RPL_HX_GT4, "Raptorlake HX GT4" },
	{ PCI_DID_INTEL_RPL_P_GT1, "Raptorlake P GT1" },
	{ PCI_DID_INTEL_RPL_P_GT2, "Raptorlake P GT2" },
	{ PCI_DID_INTEL_RPL_P_GT3, "Raptorlake P GT3" },
	{ PCI_DID_INTEL_RPL_P_GT4, "Raptorlake P GT4" },
	{ PCI_DID_INTEL_RPL_P_GT5, "Raptorlake P GT5" },
	{ PCI_DID_INTEL_RPL_U_GT1, "Raptorlake U GT1" },
	{ PCI_DID_INTEL_RPL_U_GT2, "Raptorlake U GT2" },
	{ PCI_DID_INTEL_RPL_U_GT3, "Raptorlake U GT3" },
	{ PCI_DID_INTEL_RPL_U_GT4, "Raptorlake U GT4" },
	{ PCI_DID_INTEL_RPL_U_GT5, "Raptorlake U GT5" },
	{ PCI_DID_INTEL_RPL_S_GT0, "Raptorlake S GT0" },
	{ PCI_DID_INTEL_RPL_S_GT1_1, "Raptorlake S GT1" },
	{ PCI_DID_INTEL_RPL_S_GT1_2, "Raptorlake S GT1" },
	{ PCI_DID_INTEL_RPL_S_GT1_3, "Raptorlake S GT1" },
	{ PCI_DID_INTEL_TWL_GT1_1, "Twinlake GT1" },
	{ PCI_DID_INTEL_TWL_GT1_2, "Twinlake GT1" },
};

static inline uint8_t get_dev_revision(pci_devfn_t dev)
{
	return pci_read_config8(dev, PCI_REVISION_ID);
}

static inline uint16_t get_dev_id(pci_devfn_t dev)
{
	return pci_read_config16(dev, PCI_DEVICE_ID);
}

static void report_cpu_info(void)
{
	u32 i, cpu_id, cpu_feature_flag;
	char cpu_name[49];
	int vt, txt, aes;
	static const char *const mode[] = {"NOT ", ""};
	const char *cpu_type = "Unknown";

	fill_processor_name(cpu_name);
	cpu_id = cpu_get_cpuid();

	/* Look for string to match the name */
	for (i = 0; i < ARRAY_SIZE(cpu_table); i++) {
		if (cpu_table[i].cpuid == cpu_id) {
			cpu_type = cpu_table[i].name;
			break;
		}
	}

	printk(BIOS_DEBUG, "CPU: %s\n", cpu_name);
	printk(BIOS_DEBUG, "CPU: ID %x, %s, ucode: %08x\n",
	       cpu_id, cpu_type, get_current_microcode_rev());

	cpu_feature_flag = cpu_get_feature_flags_ecx();
	aes = !!(cpu_feature_flag & CPUID_AES);
	txt = !!(cpu_feature_flag & CPUID_SMX);
	vt = !!(cpu_feature_flag & CPUID_VMX);
	printk(BIOS_DEBUG,
		"CPU: AES %ssupported, TXT %ssupported, VT %ssupported\n",
		mode[aes], mode[txt], mode[vt]);

	car_report_cache_info();
}

static void report_mch_info(void)
{
	int i;
	uint16_t mchid = get_dev_id(SA_DEV_ROOT);
	const char *mch_type = "Unknown";

	for (i = 0; i < ARRAY_SIZE(mch_table); i++) {
		if (mch_table[i].mchid == mchid) {
			mch_type = mch_table[i].name;
			break;
		}
	}

	printk(BIOS_DEBUG, "MCH: device id %04x (rev %02x) is %s\n",
		mchid, get_dev_revision(SA_DEV_ROOT), mch_type);
}

static void report_pch_info(void)
{
	int i;
	pci_devfn_t dev = PCH_DEV_ESPI;
	uint16_t espiid = get_dev_id(dev);
	const char *pch_type = "Unknown";

	for (i = 0; i < ARRAY_SIZE(pch_table); i++) {
		if (pch_table[i].espiid == espiid) {
			pch_type = pch_table[i].name;
			break;
		}
	}
	printk(BIOS_DEBUG, "PCH: device id %04x (rev %02x) is %s\n",
		espiid, get_dev_revision(dev), pch_type);
}

static void report_igd_info(void)
{
	int i;
	pci_devfn_t dev = SA_DEV_IGD;
	uint16_t igdid = get_dev_id(dev);
	const char *igd_type = "Unknown";

	for (i = 0; i < ARRAY_SIZE(igd_table); i++) {
		if (igd_table[i].igdid == igdid) {
			igd_type = igd_table[i].name;
			break;
		}
	}
	printk(BIOS_DEBUG, "IGD: device id %04x (rev %02x) is %s\n",
		igdid, get_dev_revision(dev), igd_type);
}

void report_platform_info(void)
{
	report_cpu_info();
	report_mch_info();
	report_pch_info();
	report_igd_info();
}
