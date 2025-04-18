/* SPDX-License-Identifier: GPL-2.0-only */

#include <mainboard/gpio.h>
#include <soc/gpio.h>
#include <gpio.h>
#include <timer.h>
#include <delay.h>

static const struct pad_config gpio_table[] = {

	/* ------- GPIO Community 0 ------- */

	/* ------- GPIO Group CPU ------- */

	/* ------- GPIO Group V ------- */
	PAD_CFG_NF(GPP_V00, UP_20K, DEEP, NF1),	/* BATLOW# */
	PAD_CFG_NF(GPP_V01, NATIVE, DEEP, NF1),	/* ACPRESENT */
	PAD_CFG_GPI_TRIG_OWN(GPP_V02, NATIVE, DEEP, OFF, ACPI),	/* GPIO - CPU_LAN_WAKEUP# */
	PAD_CFG_NF(GPP_V03, UP_20K, DEEP, NF1),	/* PWRBTN# */
	PAD_CFG_NF(GPP_V04, NONE, DEEP, NF1),	/* SLP_S3# */
	PAD_CFG_NF(GPP_V05, NONE, DEEP, NF1),	/* SLP_S4# */
	PAD_CFG_NF(GPP_V06, NONE, DEEP, NF1),	/* SLP_A# */
	PAD_CFG_GPO(GPP_V07, 0, DEEP),	/* GPIO */
	PAD_CFG_NF(GPP_V08, NONE, DEEP, NF1),	/* SUSCLK */
	PAD_CFG_NF(GPP_V09, NONE, DEEP, NF1),	/* SLP_WLAN# */
	PAD_CFG_NF(GPP_V10, NONE, DEEP, NF1),	/* SLP_S5# */
	PAD_CFG_GPO(GPP_V11, 1, DEEP),	/* GPIO - GPIO_LAN_EN */
	PAD_CFG_NF(GPP_V12, NONE, DEEP, NF1),	/* SLP_LAN# */
	PAD_CFG_GPO(GPP_V13, 0, DEEP),	/* GPIO */
	PAD_CFG_NF(GPP_V14, NONE, DEEP, NF1),	/* WAKE# */
	PAD_CFG_GPO(GPP_V15, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_V16, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_V17, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_V18, 0, DEEP),	/* GPIO */
	PAD_CFG_NF(GPP_V19, NONE, DEEP, NF1),	/* n/a */
	PAD_CFG_NF(GPP_V20, NONE, DEEP, NF1),	/* n/a */
	PAD_CFG_NF(GPP_V21, NONE, DEEP, NF1),	/* n/a */
	PAD_CFG_GPO(GPP_V22, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_V23, 0, DEEP),	/* GPIO */

	/* ------- GPIO Group GPP_C ------- */
	PAD_CFG_NF(GPP_C00, UP_20K, DEEP, NF1),	/* SMBCLK */
	PAD_CFG_NF(GPP_C01, UP_20K, DEEP, NF1),	/* SMBDATA */
	PAD_CFG_GPI_TRIG_OWN(GPP_C02, NONE, DEEP, OFF, ACPI),	/* GPIO */
	PAD_CFG_NF(GPP_C03, NONE, DEEP, NF1),	/* SML0CLK */
	PAD_CFG_NF(GPP_C04, NONE, DEEP, NF1),	/* SML0DATA */
	PAD_CFG_GPO(GPP_C05, 0, DEEP),	/* GPIO */
	PAD_CFG_NF(GPP_C06, NONE, RSMRST, NF1),	/* SML1CLK */
	PAD_CFG_NF(GPP_C07, NONE, RSMRST, NF1),	/* SML1DATA */
	PAD_CFG_GPO(GPP_C08, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_C09, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_C10, 0, DEEP),	/* GPIO */
	PAD_CFG_NF(GPP_C11, NONE, DEEP, NF1),	/* SRCCLKREQ2# */
	PAD_CFG_NF(GPP_C12, NONE, DEEP, NF1),	/* SRCCLKREQ3# */
	PAD_CFG_GPO(GPP_C13, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_C14, 0, DEEP),	/* GPIO */
	PAD_CFG_GPI_TRIG_OWN(GPP_C15, NONE, DEEP, OFF, ACPI),	/* GPIO - CPU_DGPU_PWRGD */
	PAD_CFG_NF(GPP_C16, NONE, DEEP, NF1),	/* TBT_LSX0_TXD */
	PAD_CFG_NF(GPP_C17, NONE, DEEP, NF1),	/* TBT_LSX0_RXD */
	PAD_CFG_GPO(GPP_C18, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_C19, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_C20, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_C21, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_C22, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_C23, 0, DEEP),	/* GPIO */

	/* ------- GPIO Community 1 ------- */

	/* ------- GPIO Group GPP_A ------- */
	PAD_CFG_NF(GPP_A00, UP_20K, DEEP, NF1),	/* ESPI_IO0 */
	PAD_CFG_NF(GPP_A01, UP_20K, DEEP, NF1),	/* ESPI_IO1 */
	PAD_CFG_NF(GPP_A02, UP_20K, DEEP, NF1),	/* ESPI_IO2 */
	PAD_CFG_NF(GPP_A03, UP_20K, DEEP, NF1),	/* ESPI_IO3 */
	PAD_CFG_NF(GPP_A04, UP_20K, DEEP, NF1),	/* ESPI_CS0# */
	PAD_CFG_NF(GPP_A05, UP_20K, DEEP, NF1),	/* ESPI_CLK */
	PAD_CFG_NF(GPP_A06, NONE, DEEP, NF1),	/* ESPI_RESET# */
	PAD_CFG_GPO(GPP_A07, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_A08, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_A09, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_A10, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_A11, 0, DEEP),	/* GPIO - ADDS_CODE */
	PAD_CFG_GPI_TRIG_OWN(GPP_A12, NONE, DEEP, OFF, ACPI),	/* GPIO - WLAN_WAKEUP# */
	PAD_CFG_TERM_GPO(GPP_A13, 1, UP_20K, PLTRST),	/* GPIO - M2_SSD2_RST# */
	PAD_CFG_GPI_TRIG_OWN(GPP_A14, UP_20K, DEEP, OFF, ACPI),	/* GPIO - NVVDD_ALERT# */
	PAD_CFG_GPO(GPP_A15, 0, DEEP),	/* GPIO - CPU_SWI# */
	PAD_CFG_NF(GPP_A16, UP_20K, DEEP, NF1),	/* RSVD - ESPI_ALERT0# */
	PAD_CFG_GPI_INT(GPP_A17, NONE, PLTRST, LEVEL),	/* GPIO - TP_ATTN# */
	PAD_CFG_GPO(GPP_A18, 0, DEEP),	/* GPIO - TEST_R (ANX7411) */
	PAD_CFG_GPI_APIC(GPP_A19, NONE, DEEP, LEVEL, NONE),	/* GPIO - INTP_OUT (ANX7411) */
	PAD_CFG_GPO(GPP_A20, 1, DEEP),	/* GPIO - LAN_PLT_RST# */
	PAD_CFG_NF(GPP_A21, NATIVE, DEEP, NF1),	/* PMCALERT# */
	PAD_NC(GPP_A22, NATIVE),	/* GPIO */
	PAD_NC(GPP_A23, NATIVE),	/* GPIO */

	/* ------- GPIO Group GPP_E ------- */
	PAD_CFG_GPI_TRIG_OWN(GPP_E00, NONE, DEEP, OFF, ACPI),	/* GPIO - BOARD_ID7 */
	PAD_CFG_GPI_APIC(GPP_E01, UP_20K, DEEP, LEVEL, NONE),	/* GPIO - TPM_PIRQ# */
	PAD_CFG_GPI_TRIG_OWN(GPP_E02, NONE, DEEP, OFF, ACPI),	/* GPIO - BOARD_ID4 */
	PAD_CFG_GPI_TRIG_OWN(GPP_E03, NONE, DEEP, OFF, ACPI),	/* GPIO - CPU_CNVI_WAKE# */
	PAD_CFG_GPO(GPP_E04, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_E05, 0, DEEP),	/* GPIO */
	PAD_CFG_GPI_TRIG_OWN(GPP_E06, NONE, DEEP, OFF, ACPI),	/* GPIO */
	PAD_CFG_GPO(GPP_E07, 0, DEEP),	/* GPIO - CPU_SMI# */
	PAD_CFG_GPO(GPP_E08, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_E09, 1, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_E10, 0, DEEP),	/* GPIO */
	PAD_CFG_GPI_TRIG_OWN(GPP_E11, NONE, DEEP, OFF, ACPI),	/* GPIO - BOARD_ID6 */
	PAD_CFG_NF(GPP_E12, NONE, DEEP, NF8),	/* I2C4_SDA - ANX7411 */
	PAD_CFG_NF(GPP_E13, NONE, DEEP, NF8),	/* I2C4_SCL - ANX7411 */
	PAD_CFG_NF(GPP_E14, NONE, DEEP, NF1),	/* DDSP_HPDA */
	PAD_CFG_GPO(GPP_E15, 0, DEEP),	/* GPIO - CPU_SCI# */
	PAD_CFG_NF(GPP_E16, NONE, DEEP, NF2),	/* VRALERT# */
	PAD_CFG_GPI_TRIG_OWN(GPP_E17, NONE, DEEP, OFF, ACPI),	/* GPIO - BOARD_ID5 */
	PAD_CFG_GPO(GPP_E18, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_E19, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_E20, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_E21, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_E22, 0, DEEP),	/* GPIO */
	PAD_NC(GPP_E23, NONE),	/* GPIO */
	PAD_NC(GPP_THC0_GSPI_CLK_LPBK, NONE),	/* GPIO */

	/* ------- GPIO Community 3 ------- */

	/* ------- GPIO Group GPP_H ------- */
	PAD_CFG_GPO(GPP_H00, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_H01, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_H02, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_H03, 0, DEEP),	/* GPIO */
	PAD_CFG_NF(GPP_H04, NONE, DEEP, NF2),	/* CNV_MFUART2_RXD */
	PAD_CFG_NF(GPP_H05, NONE, DEEP, NF2),	/* CNV_MFUART2_TXD */
	PAD_CFG_NF(GPP_H06, NONE, DEEP, NF1),	/* I2C3_SDA */
	PAD_CFG_NF(GPP_H07, NONE, DEEP, NF1),	/* I2C3_SCL */
	PAD_CFG_NF(GPP_H08, NONE, DEEP, NF1),	/* UART0_RXD */
	PAD_CFG_NF(GPP_H09, NONE, DEEP, NF1),	/* UART0_TXD */
	PAD_CFG_GPO(GPP_H10, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_H11, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_H12, 0, DEEP),	/* GPIO */
	PAD_CFG_NF(GPP_H13, NONE, DEEP, NF1),	/* PROC_C10_GATE# */
	PAD_CFG_GPO(GPP_H14, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_H15, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_H16, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_H17, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_H18, 0, DEEP),	/* GPIO */
	PAD_CFG_NF(GPP_H19, NONE, DEEP, NF1),	/* I2C0_SDA */
	PAD_CFG_NF(GPP_H20, NONE, DEEP, NF1),	/* I2C0_SCL */
	PAD_CFG_NF(GPP_H21, NONE, DEEP, NF1),	/* I2C1_SDA */
	PAD_CFG_NF(GPP_H22, NONE, DEEP, NF1),	/* I2C1_SCL */
	PAD_NC(GPP_H23, NONE),	/* GPIO */
	PAD_NC(GPP_LPI3C1_CLK_LPBK, NATIVE),	/* GPIO */
	PAD_CFG_NF(GPP_LPI3C0_CLK_LPBK, NATIVE, DEEP, NF2),	/* n/a */

	/* ------- GPIO Group GPP_F ------- */
	PAD_CFG_NF(GPP_F00, NONE, DEEP, NF1),	/* CNV_BRI_DT */
	PAD_CFG_NF(GPP_F01, UP_20K, DEEP, NF1),	/* CNV_BRI_RSP */
	PAD_CFG_NF(GPP_F02, NONE, DEEP, NF1),	/* CNV_RGI_DT */
	PAD_CFG_NF(GPP_F03, UP_20K, DEEP, NF1),	/* CNV_RGI_RSP */
	PAD_CFG_NF(GPP_F04, NONE, DEEP, NF1),	/* CNV_RF_RESET# */
	PAD_CFG_NF(GPP_F05, NONE, DEEP, NF3),	/* MODEM_CLKREQ */
	PAD_CFG_NF(GPP_F06, NONE, DEEP, NF1),	/* CNVI_GNSS_PA_BLANKING */
	PAD_CFG_GPO(GPP_F07, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_F08, 0, DEEP),	/* GPIO */
	PAD_CFG_GPI_TRIG_OWN(GPP_F09, NONE, DEEP, OFF, ACPI),	/* GPIO - TPM_DET */
	PAD_CFG_GPO(GPP_F10, 0, DEEP),	/* GPIO */
	PAD_CFG_GPI_TRIG_OWN(GPP_F11, NONE, DEEP, OFF, ACPI),	/* GPIO - BOARD_ID3 */
	PAD_CFG_NF(GPP_F12, NONE, DEEP, NF8),	/* I2C5_SCL - Smart AMP */
	PAD_CFG_NF(GPP_F13, NONE, DEEP, NF8),	/* I2C5_SDA - Smart AMP */
	PAD_CFG_GPI_TRIG_OWN(GPP_F14, NONE, DEEP, OFF, ACPI),	/* GPIO - BOARD_ID1 */
	PAD_CFG_GPI_TRIG_OWN(GPP_F15, NONE, DEEP, OFF, ACPI),	/* GPIO - BOARD_ID2 */
	PAD_CFG_GPI_TRIG_OWN(GPP_F16, NONE, DEEP, OFF, ACPI),	/* GPIO - GPIO4_GC6_NVVDD_EN */
	PAD_CFG_GPI_TRIG_OWN(GPP_F17, NONE, PLTRST, OFF, ACPI),	/* GPIO - CPU_GC6_FB_EN */
	PAD_CFG_GPO(GPP_F18, 0, DEEP),	/* GPIO -CCD_WP# */
	PAD_CFG_GPO(GPP_F19, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_F20, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_F21, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_F22, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_F23, 0, DEEP),	/* GPIO */
	PAD_NC(GPP_THC1_GSPI1_CLK_LPBK, NONE),	/* GPIO */
	PAD_NC(GPP_GSPI0A_CLK_LOOPBK, NONE),	/* GPIO */

	/* ------- GPIO Group SPI ------- */

	/* ------- GPIO Group VGPIO3 ------- */
	PAD_CFG_NF(GPP_VGPIO3_USB0, NONE, DEEP, NF1),	/* GPP_VGPIO3_USB0 */
	PAD_CFG_NF(GPP_VGPIO3_USB1, NONE, DEEP, NF1),	/* GPP_VGPIO3_USB1 */
	PAD_CFG_NF(GPP_VGPIO3_USB2, NONE, DEEP, NF1),	/* GPP_VGPIO3_USB2 */
	PAD_CFG_NF(GPP_VGPIO3_USB3, NONE, DEEP, NF1),	/* GPP_VGPIO3_USB3 */
	PAD_CFG_NF(GPP_VGPIO3_USB4, NONE, DEEP, NF1),	/* GPP_VGPIO3_USB4 */
	PAD_CFG_NF(GPP_VGPIO3_USB5, NONE, DEEP, NF1),	/* GPP_VGPIO3_USB5 */
	PAD_CFG_NF(GPP_VGPIO3_USB6, NONE, DEEP, NF1),	/* GPP_VGPIO3_USB6 */
	PAD_CFG_NF(GPP_VGPIO3_USB7, NONE, DEEP, NF1),	/* GPP_VGPIO3_USB7 */
	PAD_CFG_GPI_TRIG_OWN(GPP_VGPIO3_TS0, NONE, DEEP, OFF, ACPI),	/* GPIO */
	PAD_CFG_GPI_TRIG_OWN(GPP_VGPIO3_TS1, NONE, DEEP, OFF, ACPI),	/* GPIO */
	PAD_CFG_GPI_TRIG_OWN(GPP_VGPIO3_THC0, NONE, DEEP, OFF, ACPI),	/* GPIO */
	PAD_CFG_GPI_TRIG_OWN(GPP_VGPIO3_THC1, NONE, DEEP, OFF, ACPI),	/* GPIO */
	PAD_CFG_GPI_TRIG_OWN(GPP_VGPIO3_THC2, NONE, DEEP, OFF, ACPI),	/* GPIO */
	PAD_CFG_GPI_TRIG_OWN(GPP_VGPIO3_THC3, NONE, DEEP, OFF, ACPI),	/* GPIO */

	/* ------- GPIO Community 4 ------- */

	/* ------- GPIO Group GPP_S ------- */
	PAD_CFG_GPO(GPP_S00, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_S01, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_S02, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_S03, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_S04, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_S05, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_S06, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_S07, 0, DEEP),	/* GPIO */

	/* ------- GPIO Group JTAG ------- */

	/* ------- GPIO Community 5 ------- */

	/* ------- GPIO Group GPP_B ------- */
	PAD_CFG_GPO(GPP_B00, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_B01, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_B02, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_B03, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_B04, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_B05, 0, DEEP),	/* GPIO - CPU_KBCRST# */
	PAD_CFG_GPO(GPP_B06, 0, DEEP),	/* GPIO - ROM_I2C_EN */
	PAD_CFG_GPO(GPP_B07, 0, DEEP),	/* GPIO - PANTONE_WP# */
	PAD_CFG_GPO(GPP_B08, 0, DEEP),	/* GPIO - PS8461_SW (DDS for eDP) */
	PAD_CFG_GPO(GPP_B09, 0, DEEP),	/* GPIO - DGPU_RST#_PCH */
	PAD_CFG_GPI_SCI(GPP_B10, NONE, PLTRST, EDGE_BOTH, INVERT),	/* GPIO - NV Type-C DP HPD */
	PAD_CFG_GPI_SCI(GPP_B11, NONE, PLTRST, EDGE_BOTH, INVERT),	/* GPIO - NV HDMI HPD */
	PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1),	/* SLP_S0# */
	PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1),	/* PLTRST# */
	PAD_CFG_GPO(GPP_B14, 0, DEEP),	/* GPIO */
	PAD_CFG_GPI_TRIG_OWN(GPP_B15, NONE, DEEP, OFF, ACPI),	/* GPIO */
	PAD_CFG_GPO(GPP_B16, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_B17, 1, DEEP),	/* GPIO - CPU_GPIO_LANRTD3 */
	PAD_CFG_GPO(GPP_B18, 1, DEEP),	/* GPIO - PCH_BT_EN */
	PAD_CFG_GPO(GPP_B19, 1, DEEP),	/* GPIO - WIFI_RF_EN */
	PAD_CFG_GPO(GPP_B20, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_B21, 0, PLTRST),	/* GPIO - TBT_FORCE_PWR */
	PAD_CFG_GPO(GPP_B22, 0, DEEP),	/* GPIO */
	PAD_CFG_TERM_GPO(GPP_B23, 0, DN_20K, DEEP),	/* GPIO */
	PAD_CFG_NF(GPP_ACI3C0_CLK_LPBK, NATIVE, DEEP, NF4),	/* n/a */

	/* ------- GPIO Group GPP_D ------- */
	PAD_CFG_GPO(GPP_D00, 1, DEEP),	/* GPIO - SB_BLON */
	PAD_CFG_GPO(GPP_D01, 1, DEEP),	/* GPIO - SSD2_PWR_EN */
	PAD_CFG_GPO(GPP_D02, 1, DEEP),	/* GPIO - M2_SSD1_RST# */
	PAD_CFG_GPO(GPP_D03, 0, DEEP),	/* GPIO - CPU_DGPU_PWR_EN */
	PAD_CFG_GPO(GPP_D04, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_D05, 1, DEEP),	/* GPIO - SSD1_PWR_EN */
	PAD_CFG_GPO(GPP_D06, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_D07, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_D08, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_D09, 0, DEEP),	/* GPIO */
	PAD_CFG_NF(GPP_D10, NONE, DEEP, NF1),	/* HDA_BCLK */
	PAD_CFG_NF(GPP_D11, NATIVE, DEEP, NF1),	/* HDA_SYNC */
	PAD_CFG_NF(GPP_D12, NATIVE, DEEP, NF1),	/* HDA_SDO */
	PAD_CFG_NF(GPP_D13, NATIVE, DEEP, NF1),	/* HDA_SDI0 */
	PAD_CFG_GPO(GPP_D14, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_D15, 0, DEEP),	/* GPIO */
	PAD_CFG_GPO(GPP_D16, 0, DEEP),	/* GPIO - GPIO_SPK_MUTE */
	PAD_CFG_NF(GPP_D17, NONE, DEEP, NF1),	/* HDA_RST# */
	PAD_CFG_NF(GPP_D18, NONE, DEEP, NF1),	/* SRCCLKREQ6# */
	PAD_CFG_NF(GPP_D19, NONE, DEEP, NF1),	/* SRCCLKREQ7# */
	PAD_CFG_NF(GPP_D20, NONE, DEEP, NF1),	/* SRCCLKREQ8# */
	PAD_CFG_NF(GPP_D21, NONE, DEEP, NF2),	/* SRCCLKREQ5# */
	PAD_CFG_NF(GPP_D22, NATIVE, DEEP, NF1),	/* n/a */
	PAD_CFG_NF(GPP_D23, NATIVE, DEEP, NF1),	/* n/a */
	PAD_CFG_NF(GPP_BOOTHALT_B, UP_20K, DEEP, NF1),	/* GPP_BOOTHALT_B */

	/* ------- GPIO Group VGPIO ------- */
	PAD_CFG_GPO(GPP_VGPIO00, 1, DEEP),	/* GPIO */
	PAD_CFG_GPI_TRIG_OWN(GPP_VGPIO04, NONE, DEEP, OFF, ACPI),	/* GPIO */
	PAD_CFG_GPO(GPP_VGPIO05, 1, DEEP),	/* GPIO */
	PAD_CFG_GPIO_BIDIRECT(GPP_VGPIO06, 0, NONE, DEEP, LEVEL, ACPI),	/* GPIO */
	PAD_CFG_GPIO_BIDIRECT(GPP_VGPIO07, 0, NONE, DEEP, LEVEL, ACPI),	/* GPIO */
	PAD_CFG_GPIO_BIDIRECT(GPP_VGPIO08, 0, NONE, DEEP, LEVEL, ACPI),	/* GPIO */
	PAD_CFG_GPIO_BIDIRECT(GPP_VGPIO09, 0, NONE, DEEP, LEVEL, ACPI),	/* GPIO */
	PAD_CFG_NF(GPP_VGPIO10, NONE, DEEP, NF1),	/* GPP_VGPIO10 */
	PAD_CFG_NF(GPP_VGPIO11, NONE, DEEP, NF1),	/* GPP_VGPIO11 */
	PAD_CFG_NF(GPP_VGPIO12, NONE, DEEP, NF1),	/* GPP_VGPIO12 */
	PAD_CFG_NF(GPP_VGPIO13, NONE, DEEP, NF1),	/* GPP_VGPIO13 */
	PAD_CFG_GPIO_BIDIRECT(GPP_VGPIO18, 0, NONE, DEEP, LEVEL, ACPI),	/* GPIO */
	PAD_CFG_GPIO_BIDIRECT(GPP_VGPIO19, 0, NONE, DEEP, LEVEL, ACPI),	/* GPIO */
	PAD_CFG_GPIO_BIDIRECT(GPP_VGPIO20, 0, NONE, DEEP, LEVEL, ACPI),	/* GPIO */
	PAD_CFG_GPIO_BIDIRECT(GPP_VGPIO21, 0, NONE, DEEP, LEVEL, ACPI),	/* GPIO */
	PAD_CFG_NF(GPP_VGPIO22, NONE, DEEP, NF1),	/* GPP_VGPIO22 */
	PAD_CFG_NF(GPP_VGPIO23, NONE, DEEP, NF1),	/* GPP_VGPIO23 */
	PAD_CFG_NF(GPP_VGPIO24, NONE, DEEP, NF1),	/* GPP_VGPIO24 */
	PAD_CFG_NF(GPP_VGPIO25, NONE, DEEP, NF1),	/* GPP_VGPIO25 */
	PAD_CFG_NF(GPP_VGPIO30, NONE, DEEP, NF3),	/* RESERVED */
	PAD_CFG_NF(GPP_VGPIO31, NONE, DEEP, NF3),	/* RESERVED */
	PAD_CFG_NF(GPP_VGPIO32, NONE, DEEP, NF3),	/* RESERVED */
	PAD_CFG_NF(GPP_VGPIO33, NONE, DEEP, NF3),	/* RESERVED */
	PAD_CFG_NF(GPP_VGPIO34, NONE, DEEP, NF1),	/* GPP_VGPIO34 */
	PAD_CFG_NF(GPP_VGPIO35, NONE, DEEP, NF1),	/* GPP_VGPIO35 */
	PAD_CFG_NF(GPP_VGPIO36, NONE, DEEP, NF1),	/* GPP_VGPIO36 */
	PAD_CFG_NF(GPP_VGPIO37, NONE, DEEP, NF1),	/* GPP_VGPIO37 */
	PAD_CFG_NF(GPP_VGPIO40, NONE, DEEP, NF2),	/* RESERVED */
	PAD_CFG_NF(GPP_VGPIO41, NONE, DEEP, NF2),	/* RESERVED */
	PAD_CFG_NF(GPP_VGPIO42, NONE, DEEP, NF2),	/* RESERVED */
	PAD_CFG_NF(GPP_VGPIO43, NONE, DEEP, NF2),	/* RESERVED */
	PAD_CFG_NF(GPP_VGPIO44, NONE, DEEP, NF1),	/* GPP_VGPIO44 */
	PAD_CFG_NF(GPP_VGPIO45, NONE, DEEP, NF1),	/* GPP_VGPIO45 */
	PAD_CFG_NF(GPP_VGPIO46, NONE, DEEP, NF1),	/* GPP_VGPIO46 */
	PAD_CFG_NF(GPP_VGPIO47, NONE, DEEP, NF1),	/* GPP_VGPIO47 */
};

#define DGPU_RST_N GPP_B09
#define DGPU_PWR_EN GPP_D03
#define DGPU_PWRGD GPP_C15

/* Pad configuration was generated automatically using intelp2m utility */
void variant_configure_gpios(void)
{
	bool result;

	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));

	/* dGPU power on sequence */
	mdelay(4);
	gpio_set(DGPU_PWR_EN, 1);
	result = wait_ms(200, gpio_get(DGPU_PWRGD) == 1);
	if (result) {
		printk(BIOS_INFO, "dGPU powered on\n");
		gpio_set(DGPU_RST_N, 1);
	} else {
		printk(BIOS_ERR, "dGPU failed to power on, turning off\n");
		gpio_set(DGPU_PWR_EN, 0);
	}
	mdelay(50);
}
