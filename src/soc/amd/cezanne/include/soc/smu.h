/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef AMD_CEZANNE_SMU_H
#define AMD_CEZANNE_SMU_H

/* SMU mailbox register offsets in SMN */
#define SMN_SMU_MESG_ID		0x3b10528
#define SMN_SMU_MESG_RESP	0x3b10564
#define SMN_SMU_MESG_ARGS_BASE	0x3b10998

#define SMU_NUM_ARGS		6

enum smu_message_id {
	SMC_MSG_S3ENTRY = 0x0b,
	SMC_MSG_USBS3ENTRY = 0x27,
};

/*
 * Request the SMU put system into S3, S4, or S5. On entry, SlpTyp determines S-State and
 * SlpTypeEn gets set by the SMU. Function does not return if successful.
 */
void smu_sx_entry(void);

#endif /* AMD_CEZANNE_SMU_H */
