/* SPDX-License-Identifier: GPL-2.0-only OR MIT */

/*
 * This file is created based on MT8196 Functional Specification
 * Chapter number: 14.2.4
 */

#ifndef SOC_MEDIATEK_MT8196_MT6685_RTC_H
#define SOC_MEDIATEK_MT8196_MT6685_RTC_H

#define RG_BANK_FQMTR_RST		0x522
#define RG_BANK_FQMTR_RST_MASK		0x1
#define RG_BANK_FQMTR_RST_SHIFT		6

#define TOP_DIG_WPK			0x3a8
#define DIG_WPK_KEY_MASK		0xFF
#define DIG_WPK_KEY_SHIFT		0

#define TOP_DIG_WPK_H			0x3a9
#define DIG_WPK_KEY_H_MASK		0xFF
#define DIG_WPK_KEY_H_SHIFT		0

#define RG_FQMTR_CLK_CK_PDN_CLR		0x10d
#define RG_FQMTR_CLK_CK_PDN_MASK	0x1
#define RG_FQMTR_CLK_CK_PDN_SHIFT	5

#define RG_FQMTR_32K_CK_PDN_CLR		0x10d
#define RG_FQMTR_32K_CK_PDN_MASK	0x1
#define RG_FQMTR_32K_CK_PDN_SHIFT	4

#define RG_FQMTR_DCXO26M_EN		0x546
#define RG_FQMTR_DCXO26M_MASK		0x1
#define RG_FQMTR_DCXO26M_SHIFT		4

#define RG_FQMTR_WINSET			0x548

#define RG_FQMTR_TCKSEL			0x546
#define RG_FQMTR_TCKSEL_MASK		0x7
#define RG_FQMTR_TCKSEL_SHIFT		0

#define FQMTR_DCXO26M_EN		(1 << 4)

#define RG_FQMTR_EN			0x547
#define RG_FQMTR_EN_MASK		0x1
#define RG_FQMTR_EN_SHIFT		7

#define RG_FQMTR_BUSY			0x546
#define FQMTR_BUSY			(1 << 3)

#define RG_FQMTR_DATA			0x54a

#define RG_FQMTR_CLK_CK_PDN_SET		0x10c
#define RG_FQMTR_CLK_CK_PDN_MASK	0x1
#define RG_FQMTR_CLK_CK_PDN_SHIFT	5

#define RG_FQMTR_32K_CK_PDN_SET		0x10c
#define RG_FQMTR_32K_CK_PDN_MASK	0x1
#define RG_FQMTR_32K_CK_PDN_SHIFT	4

#define RG_FQMTR_CKSEL			0x111
#define FQMTR_FIX_CLK_26M		0
#define RG_FQMTR_CKSEL_MASK		0x7
#define RG_FQMTR_CKSEL_SHIFT		0

#define FQMTR_FQM26M_CK			4
#define FQMTR_DCXO_F32K_CK		1
#define FQMTR_FIX_CLK_EOSC_32K		2

#define OSC32CON_ANALOG_SETTING		(RTC_GP_OSC32_CON | RTC_EOSC32_CHOP_EN | \
					 RTC_EOSC32_VCT_EN | RTC_GPS_CKOUT_EN | \
					 RTC_EMBCK_SEL_OPTION | RTC_EMBCK_SEL_K_EOSC)
#define RTC_GP_OSC32_CON		(2U << (5 + 8))
#define RTC_EOSC32_CHOP_EN		(1 << (4 + 8))
#define RTC_EOSC32_VCT_EN		(1 << (3 + 8))
#define RTC_EMBCK_SEL_K_EOSC		(1U << 6)

#define RTC_XOSC32_LPEN			(1 << 2)
#define RTC_EOSC32_LPEN			(1 << 1)

#define RTC_BBPU_RESET_ALARM		(1 << 3)
#define RTC_BBPU_RESET_SPAR		(1 << 2)
#define RTC_BBPU_SPAR_SW		(1 << 1)

#define RTC_XOSC32_LPEN			(1 << 2)

#define RTC_PDN1_PWRON_TIME		(1 << 7)

#define RTC_WRTGR_SEC			0x618

#define RG_RTC_SEC_MCLK_PDN_MASK	0x1
#define RG_RTC_SEC_32K_CK_PDN_MASK	0x1
#define RG_RTC_SEC_32K_CK_PDN_SHIFT	3

#define RTC_SEC_CK_PDN			0x616
#define SCK_TOP_CKPDN_CON0_L		0x514
#define RTC_SEC_DSN_ID			0x600
#define RTC_SEC_DSN_REV0		0x602

#define RTC_TC_YEA_SEC			0x614
#define RTC_TC_MTH_SEC			0x612
#define RTC_TC_DOM_SEC			0x60e
#define RTC_TC_DOW_SEC			0x610
#define RTC_TC_HOU_SEC			0x60c
#define RTC_TC_MIN_SEC			0x60a
#define RTC_TC_SEC_SEC			0x608

#define RTC_K_EOSC32_VTCXO_ON_SEL	(1 << (7 + 8))
#define RTC_AL_YEA_MASK			(0x7F << 0)
#define RTC_K_EOSC_RSV_7		(1 << 15)
#define RTC_K_EOSC_RSV_6		(1 << 14)

#define RTC_POWER_DETECTED		(1 << (4 + 8))

#define RTC_K_EOSC_RSV_0		(1 << 8)
#define RTC_K_EOSC_RSV_1		(1 << 9)
#define RTC_K_EOSC_RSV_2		(1 << 10)

#define TMA_KEY				0x39e
#define TMA_KEY_MASK			0xFF
#define TMA_KEY_SHIFT			0
#define TMA_KEY_H			0x39f
#define	TMA_KEY_H_MASK			0xFF
#define TMA_KEY_H_SHIFT			0

#define RG_OCT1_RTC32K_1V8_0		0xa7
#define RG_OCT1_RTC32K_1V8_0_MASK	0x3
#define RG_OCT1_RTC32K_1V8_0_SHIFT	5

#define RG_OCT1_RTC32K_1V8_F		0xa8
#define RG_OCT1_RTC32K_1V8_F_MASK	0x3
#define RG_OCT1_RTC32K_1V8_F_SHIFT	1

#define SCK_TOP_CKSEL_CON		0x568
#define R_SCK32K_CK_MASK		0x1
#define R_SCK32K_CK_SHIFT		0

#define SCK_TOP_CKPDN_CON0_L_SET	0x515
#define RG_RTC_EOSC32_CK_PDN_MASK	0x1
#define RG_RTC_EOSC32_CK_PDN_SHIFT	2

#define RTC_TC_MTH_MASK			0xF

#define SCK_TOP_CKPDN_CON0_L_CLR	0x516
#define SCK_TOP_CKPDN_CON0_L_CLR_SHIFT	0

#define SCK_TOP_XTAL_SEL_ADDR		0x50c
#define SCK_TOP_XTAL_SEL_MASK		0x1
#define SCK_TOP_XTAL_SEL_SHIFT		0

/* Complete the RTC initialization process and register settings. */
void rtc_boot(void);

#endif /* SOC_MEDIATEK_MT8196_MT6685_RTC_H */
