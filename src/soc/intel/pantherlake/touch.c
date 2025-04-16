/* SPDX-License-Identifier: GPL-2.0-only */

#include <drivers/intel/touch/chip.h>
#include <soc/touch.h>

/* SoC-specific THC-I2C config */
const struct intel_thc_hidi2c_info *soc_get_thc_hidi2c_info(void)
{
	static const struct intel_thc_hidi2c_info soc_thc_hidi2c_info = {
		.connection_speed		= SOC_PTL_THC_I2C_CONNECTION_SPEED_FM,
		.addr_mode			= SOC_PTL_THC_I2C_ADDR_MODE,
		.sm_scl_high_period		= SOC_PTL_THC_I2C_SM_SCL_HIGH_PERIOD,
		.sm_scl_low_period		= SOC_PTL_THC_I2C_SM_SCL_LOW_PERIOD,
		.sm_sda_hold_tx_period		= SOC_PTL_THC_I2C_SM_SDA_HOLD_TX_PERIOD,
		.sm_sda_hold_rx_period		= SOC_PTL_THC_I2C_SM_SDA_HOLD_RX_PERIOD,
		.fm_scl_high_period		= SOC_PTL_THC_I2C_FM_SCL_HIGH_PERIOD,
		.fm_scl_low_period		= SOC_PTL_THC_I2C_FM_SCL_LOW_PERIOD,
		.fm_sda_hold_tx_period		= SOC_PTL_THC_I2C_FM_SDA_HOLD_TX_PERIOD,
		.fm_sda_hold_rx_period		= SOC_PTL_THC_I2C_FM_SDA_HOLD_RX_PERIOD,
		.suppressed_spikes_s_f_fp	= SOC_PTL_THC_I2C_SUPPRESSED_SPIKES_S_F_FP,
		.fmp_scl_high_period		= SOC_PTL_THC_I2C_FMP_SCL_HIGH_PERIOD,
		.fmp_scl_low_period		= SOC_PTL_THC_I2C_FMP_SCL_LOW_PERIOD,
		.fmp_sda_hold_tx_period		= SOC_PTL_THC_I2C_FMP_SDA_HOLD_TX_PERIOD,
		.fmp_sda_hold_rx_period		= SOC_PTL_THC_I2C_FMP_SDA_HOLD_RX_PERIOD,
		.hm_scl_high_period		= SOC_PTL_THC_I2C_HM_SCL_HIGH_PERIOD,
		.hm_scl_low_period		= SOC_PTL_THC_I2C_HM_SCL_LOW_PERIOD,
		.hm_sda_hold_tx_period		= SOC_PTL_THC_I2C_HM_SDA_HOLD_TX_PERIOD,
		.hm_sda_hold_rx_period		= SOC_PTL_THC_I2C_HM_SDA_HOLD_RX_PERIOD,
		.suppressed_spikes_h_fp		= SOC_PTL_THC_I2C_SUPPRESSED_SPIKES_H_FP,
	};
	return &soc_thc_hidi2c_info;
}

/* SoC-specific THC-SPI config */
const struct intel_thc_hidspi_info *soc_get_thc_hidspi_info(void)
{
	static const struct intel_thc_hidspi_info soc_thc_hidspi_info = {
		.connection_speed	= SOC_PTL_THC_CONNECTION_SPEED,
		.write_mode		= HIDSPI_WRITE_MODE_MULTI_SINGLE_SPI,
		.limit_packet_size	= SOC_PTL_THC_HIDSPI_LIMIT_PKT_SZ,
		.performance_limit	= SOC_PTL_THC_PERFORMANCE_LIMIT,
		.reset_sequencing_delay	= SOC_PTL_THC_RST_SEQ_DLY,
	};
	return &soc_thc_hidspi_info;
}
