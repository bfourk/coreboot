## SPDX-License-Identifier: GPL-2.0-only

ifeq ($(CONFIG_SOC_INTEL_COOPERLAKE_SP),y)

subdirs-y += ../../../../cpu/intel/turbo
subdirs-y += ../../../../cpu/intel/microcode

romstage-y += romstage.c soc_util.c
romstage-$(CONFIG_DISPLAY_UPD_DATA) += upd_display.c
romstage-$(CONFIG_DISPLAY_HOBS) += hob_display.c

ramstage-y += chip.c cpu.c soc_util.c soc_acpi.c
ramstage-y += ../chip_gen1.c ../lpc_gen1.c
ramstage-$(CONFIG_DISPLAY_HOBS) += hob_display.c
ramstage-$(CONFIG_DISPLAY_UPD_DATA) += upd_display.c
ramstage-y += ../pcu0.c
ramstage-y += ../pcu1.c
ramstage-y += ../pcu2.c
ramstage-y += ../pcu3.c
CPPFLAGS_common += -I$(src)/soc/intel/xeon_sp/cpx/include -I$(src)/soc/intel/xeon_sp/cpx
CPPFLAGS_common += -I$(src)/vendorcode/intel/fsp/fsp2_0/cooperlake_sp

cpu_microcode_bins += 3rdparty/intel-microcode/intel-ucode/06-55-0b

endif ## CONFIG_SOC_INTEL_COOPERLAKE_SP
