/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/azalia_device.h>

const u32 cim_verb_data[] = {
	/* Realtek, ALC245 */
	0x10ec0245, /* Vendor ID */
	0x1558a763, /* Subsystem ID */
	40, /* Number of entries */
	AZALIA_SUBVENDOR(0, 0x1558a763),
	AZALIA_RESET(1),
	AZALIA_PIN_CFG(0, 0x12, 0x90a60130),
	AZALIA_PIN_CFG(0, 0x13, 0x40000000),
	AZALIA_PIN_CFG(0, 0x14, 0x90170110),
	AZALIA_PIN_CFG(0, 0x17, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x18, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x19, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x1a, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x1b, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x1d, 0x40789b2d),
	AZALIA_PIN_CFG(0, 0x1e, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x21, 0x04211020),

	0x5B50006,	0x5B40011,	0x205001A,	0x204810B,
	0x205004A,	0x2042010,	0x2050038,	0x2047909,
	0x5C50000,	0x5C43D82,	0x5C50000,	0x5C43D82,
	0x5350000,	0x534201A,	0x5350000,	0x534201A,
	0x535001D,	0x5340800,	0x535001E,	0x5340800,
	0x5350003,	0x5341EC4,	0x5350004,	0x5340000,
	0x5450000,	0x5442000,	0x545001D,	0x5440800,
	0x545001E,	0x5440800,	0x5450003,	0x5441EC4,
	0x5450004,	0x5440000,	0x5350000,	0x534A01A,
	0x205003C,	0x204F175,	0x205003C,	0x204F135,
	0x2050040,	0x2048800,	0x5A50001,	0x5A4001F,
	0x2050010,	0x2040020,	0x2050010,	0x2040020,
	0x205006B,	0x204A390,	0x205006B,	0x204A390,
	0x205006C,	0x2040C9E,	0x205006D,	0x2040C00,
	0x170500,	0x170500,	0x5A50004,	0x5A40113,
	0x2050008,	0x2046A8C,	0x2050076,	0x204F000,
	0x205000E,	0x20465C0,	0x2050033,	0x2048580,
	0x2050069,	0x204FDA8,	0x2050068,	0x2040000,
	0x2050003,	0x2040002,	0x2050069,	0x2040000,
	0x2050068,	0x2040001,	0x205002E,	0x204290E,
	0x2236100,	0x2235100,	0x920011,	0x970610,
	0x936000,	0x935000,	0x205000D,	0x204A020,
	0x220011,	0x270610,	0x23A046,	0x239046,
	0x173B000,	0x1770740,	0x5A50001,	0x5A4001F,
	0x5C5000F,	0x5C40003,	0x2050036,	0x20437D7,
	0x143B000,	0x1470740,	0x2050010,	0x2040020,
	0x1470C02,	0x1470C02,	0x1470C02,	0x1470C02,

	/* Intel Meteor Lake HDMI */
	0x8086281d, /* Vendor ID */
	0x80860101, /* Subsystem ID */
	10, /* Number of entries */
	AZALIA_SUBVENDOR(2, 0x80860101),
	AZALIA_PIN_CFG(2, 0x04, 0x18560010),
	AZALIA_PIN_CFG(2, 0x06, 0x18560010),
	AZALIA_PIN_CFG(2, 0x08, 0x18560010),
	AZALIA_PIN_CFG(2, 0x0a, 0x18560010),
	AZALIA_PIN_CFG(2, 0x0b, 0x18560010),
	AZALIA_PIN_CFG(2, 0x0c, 0x18560010),
	AZALIA_PIN_CFG(2, 0x0d, 0x18560010),
	AZALIA_PIN_CFG(2, 0x0e, 0x18560010),
	AZALIA_PIN_CFG(2, 0x0f, 0x18560010),
};

const u32 pc_beep_verbs[] = {};

AZALIA_ARRAY_SIZES;
