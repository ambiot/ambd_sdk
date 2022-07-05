/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from Realtek
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "ameba_audio_driver"
//#define LOG_NDEBUG 0

#include "hal_audio_debug.h"
#include "ameba_audio_driver.h"
#include "hardware/audio/audio_hw_utils.h"
#include "hardware/audio/audio_hw_types.h"

#include "rl6548.h"

#define ENABLE_EXT_AMP 0
#define REG_DUMP 0


enum
{
	SP_CODEC_INITED,
	SP_CODEC_DEINITED
};

static int sp_codec_state = SP_CODEC_DEINITED;
static int sp_codec_inited_cnt = 0;

extern BOOL AUDIO_SP_TXGDMA_Restart(uint8_t GDMA_Index, uint8_t GDMA_ChNum, uint32_t TX_addr, uint32_t TX_length);
extern BOOL AUDIO_SP_RXGDMA_Restart(u8 GDMA_Index, u8 GDMA_ChNum, u32 RX_addr, u32 RX_length);

static u32 get_ameba_channel(uint32_t channel_count)
{
	u32 tmp;
	switch (channel_count) {
	case 1:
		tmp = CH_MONO;
		break;
	case 2:
	case 4:
		tmp = CH_STEREO;
		break;
	default:
		HAL_AUDIO_ERROR("invalid format");
		return -1;
	}
	return tmp;
}

static int get_ameba_format(AudioHwFormat format)
{
	int tmp = -1;
	switch (format) {
	case AUDIO_HW_FORMAT_PCM_24_BIT:
		tmp = WL_24;
		break;
	case AUDIO_HW_FORMAT_PCM_16_BIT:
		tmp = WL_16;
		break;
	default:
		HAL_AUDIO_ERROR("invalid format");
		return -1;
	}
	return tmp;
}

static int get_ameba_codec_rate(u32 rate)
{
	int tmp = -1;
	switch (rate) {
	case 8000:
		tmp = SR_8K;
		break;
	case 16000:
		tmp = SR_16K;
		break;
	case 32000:
		tmp = SR_32K;
		break;
	case 44100:
		tmp = SR_44P1K;
		break;
	case 48000:
		tmp = SR_48K;
		break;
	case 96000:
		tmp = SR_96K;
		break;
	default:
		HAL_AUDIO_ERROR("invalid rate");
		return -1;
	}
	return tmp;
}

static u32 get_ameba_div(u32 rate)
{
	u32 div;
	switch(rate) {
		case SR_48K:
			div = 8;
			break;
		case SR_96K:
			div = 4;
			break;
		case SR_32K:
			div = 12;
			break;
		case SR_16K:
			div = 24;
			break;
		case SR_8K:
			div = 48;
			break;
		case SR_44P1K:
			div = 4;
			break;
		default:
			DBG_8195A("sample rate not supported!!\n");
			break;
	}

	return div;
}

#if REG_DUMP

void gdma_dump(u8 GDMA_ChNum)
{
	GDMA_TypeDef *GDMA = ((GDMA_TypeDef *) GDMA_BASE);

	DBG_8195A("GDMA->CH[%d].SAR:%x\r\n", GDMA_ChNum, GDMA->CH[GDMA_ChNum].SAR);
	DBG_8195A("GDMA->CH[%d].DAR:%x\r\n", GDMA_ChNum, GDMA->CH[GDMA_ChNum].DAR);
	DBG_8195A("GDMA->CH[%d].CTL_LOW:%x\r\n", GDMA_ChNum, GDMA->CH[GDMA_ChNum].CTL_LOW);
	DBG_8195A("GDMA->CH[%d].CTL_HIGH:%x\r\n", GDMA_ChNum, GDMA->CH[GDMA_ChNum].CTL_HIGH);
	DBG_8195A("GDMA->CH[%d].CFG_LOW:%x\r\n", GDMA_ChNum, GDMA->CH[GDMA_ChNum].CFG_LOW);
	DBG_8195A("GDMA->CH[%d].CFG_HIGH:%x\r\n", GDMA_ChNum, GDMA->CH[GDMA_ChNum].CFG_HIGH);
	DBG_8195A("GDMA->CH[%d].ChEnReg:%x\r\n", GDMA_ChNum, GDMA->ChEnReg);

	DBG_8195A("GDMA->CH[%d].MASK_TFR:%x\r\n", GDMA_ChNum, GDMA->MASK_TFR);
	DBG_8195A("GDMA->CH[%d].MASK_BLOCK:%x\r\n", GDMA_ChNum, GDMA->MASK_BLOCK);
	DBG_8195A("GDMA->CH[%d].MASK_ERR:%x\r\n", GDMA_ChNum, GDMA->MASK_ERR);
	DBG_8195A("GDMA->CH[%d].STATUS_BLOCK:%x\r\n", GDMA_ChNum, GDMA->STATUS_BLOCK);

}

static void dump_sport_regs(u32 SPORTx)
{
	u32 tmp;
	AUDIO_SPORT_TypeDef *sportx = (AUDIO_SPORT_TypeDef *)SPORTx;
	tmp = sportx->SP_REG_MUX;
	DBG_8195A("REG_SP_REG_MUX:%x \n", tmp);
	tmp = sportx->SP_CTRL0;
	DBG_8195A("REG_SP_CTRL0:%x \n", tmp);
	tmp = sportx->SP_CTRL1;
	DBG_8195A("REG_SP_CTRL1:%x \n", tmp);
	tmp = sportx->SP_INT_CTRL;
	DBG_8195A("REG_SP_INT_CTRL:%x \n", tmp);
	tmp = sportx->RSVD0;
	DBG_8195A("REG_RSVD0:%x \n", tmp);
	tmp = sportx->SP_TRX_COUNTER_STATUS;
	DBG_8195A("REG_SP_TRX_COUNTER_STATUS:%x \n", tmp);
	tmp = sportx->SP_ERR;
	DBG_8195A("REG_SP_ERR:%x \n", tmp);
	tmp = sportx->SP_SR_TX_BCLK;
	DBG_8195A("REG_SP_SR_TX_BCLK:%x \n", tmp);
	tmp = sportx->SP_TX_LRCLK;
	DBG_8195A("REG_SP_TX_LRCLK:%x \n", tmp);
	tmp = sportx->SP_FIFO_CTRL;
	DBG_8195A("REG_SP_FIFO_CTRL:%x \n", tmp);
	tmp = sportx->SP_FORMAT;
	DBG_8195A("REG_SP_FORMAT:%x \n", tmp);
	tmp = sportx->SP_RX_BCLK;
	DBG_8195A("REG_SP_RX_BCLK:%x \n", tmp);
	tmp = sportx->SP_RX_LRCLK;
	DBG_8195A("REG_SP_RX_LRCLK:%x \n", tmp);
	tmp = sportx->SP_DSP_COUNTER;
	DBG_8195A("REG_SP_DSP_COUNTER:%x \n", tmp);
	tmp = sportx->RSVD1;
	DBG_8195A("REG_RSVD1:%x \n", tmp);
	tmp = sportx->SP_DIRECT_CTRL0;
	DBG_8195A("REG_SP_DIRECT_CTRL0:%x \n", tmp);
	tmp = sportx->RSVD2;
	DBG_8195A("REG_RSVD2:%x \n", tmp);
	tmp = sportx->SP_FIFO_IRQ;
	DBG_8195A("REG_SP_FIFO_IRQ:%x \n", tmp);
	tmp = sportx->SP_DIRECT_CTRL1;
	DBG_8195A("REG_SP_DIRECT_CTRL1:%x \n", tmp);
	tmp = sportx->SP_DIRECT_CTRL2;
	DBG_8195A("REG_SP_DIRECT_CTRL2:%x \n", tmp);
	tmp = sportx->RSVD3;
	DBG_8195A("REG_RSVD3:%x \n", tmp);
	tmp = sportx->SP_DIRECT_CTRL3;
	DBG_8195A("REG_SP_DIRECT_CTRL3:%x \n", tmp);
	tmp = sportx->SP_DIRECT_CTRL4;
	DBG_8195A("REG_SP_DIRECT_CTRL4:%x \n", tmp);
	tmp = sportx->SP_RX_COUNTER1;
	DBG_8195A("REG_SP_RX_COUNTER1:%x \n", tmp);
	tmp = sportx->SP_RX_COUNTER2;
	DBG_8195A("REG_SP_RX_COUNTER2:%x \n", tmp);
	tmp = sportx->SP_TX_FIFO_0_WR_ADDR;
	DBG_8195A("REG_SP_TX_FIFO_0_WR_ADDR:%x \n", tmp);
	tmp = sportx->SP_RX_FIFO_0_RD_ADDR;
	DBG_8195A("REG_SP_RX_FIFO_0_RD_ADDR:%x \n", tmp);
	tmp = sportx->SP_TX_FIFO_1_WR_ADDR;
	DBG_8195A("REG_SP_TX_FIFO_1_WR_ADDR:%x \n", tmp);
	tmp = sportx->SP_RX_FIFO_1_RD_ADDR;
	DBG_8195A("REG_SP_RX_FIFO_1_RD_ADDR:%x \n", tmp);

}

static void dump_codec_regs(void)
{
	u32 tmp;

	tmp = AUD_ANALOG->AUD_ADDA_CTL;
	DBG_8195A("ADDA_CTL:%x \n", tmp);
	tmp = AUD_ANALOG->AUD_HPO_CTL;
	DBG_8195A("HPO_CTL:%x \n", tmp);
	tmp = AUD_ANALOG->AUD_MICBIAS_CTL0;
	DBG_8195A("MICBIAS_CTL0:%x \n", tmp);
	tmp = AUD_ANALOG->AUD_MICBIAS_CTL1;
	DBG_8195A("MICBIAS_CTL1:%x \n", tmp);
	tmp = AUD_ANALOG->AUD_MICBST_CTL0;
	DBG_8195A("MICBST_CTL0:%x \n", tmp);
	tmp = AUD_ANALOG->AUD_MICBST_CTL1;
	DBG_8195A("MICBST_CTL1:%x \n", tmp);
	tmp = AUD_ANALOG->RSVD0;
	DBG_8195A("ANALOG_RSVD0:%x \n", tmp);
	tmp = AUD_ANALOG->AUD_DTS_CTL;
	DBG_8195A("DTS_CTL:%x \n", tmp);
	tmp = AUD_ANALOG->AUD_MBIAS_CTL0;
	DBG_8195A("MBIAS_CTL0:%x \n", tmp);
	tmp = AUD_ANALOG->AUD_MBIAS_CTL1;
	DBG_8195A("MBIAS_CTL1:%x \n", tmp);
	tmp = AUD_ANALOG->AUD_MBIAS_CTL2;
	DBG_8195A("MBIAS_CTL2:%x \n", tmp);
	tmp = AUD_ANALOG->AUD_HPO_BIAS_CTL;
	DBG_8195A("HPO_BIAS_CTL:%x \n", tmp);

	/***digital reg dump***/
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_AUDIO_CONTROL_0);
	DBG_8195A("CODEC_AUDIO_CONTROL_0:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_AUDIO_CONTROL_1);
	DBG_8195A("CODEC_AUDIO_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_CLOCK_CONTROL_1);
	DBG_8195A("CODEC_CLOCK_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_CLOCK_CONTROL_2);
	DBG_8195A("CODEC_CLOCK_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_CLOCK_CONTROL_3);
	DBG_8195A("CODEC_CLOCK_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_CLOCK_CONTROL_4);
	DBG_8195A("CODEC_CLOCK_CONTROL_4:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_CLOCK_CONTROL_5);
	DBG_8195A("CODEC_CLOCK_CONTROL_5:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_CLOCK_CONTROL_6);
	DBG_8195A("CODEC_CLOCK_CONTROL_5:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_CLOCK_CONTROL_7);
	DBG_8195A("CODEC_CLOCK_CONTROL_5:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_I2S_0_CONTROL);
	DBG_8195A("CODEC_I2S_0_CONTROL:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_I2S_0_CONTROL_1);
	DBG_8195A("CODEC_I2S_0_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_I2S_1_CONTROL);
	DBG_8195A("CODEC_I2S_1_CONTROL:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_I2S_1_CONTROL_1);
	DBG_8195A("CODEC_I2S_1_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_I2S_AD_SEL_CONTROL);
	DBG_8195A("CODEC_I2S_AD_SEL_CONTROL:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_ADC_0_CONTROL_0);
	DBG_8195A("CODEC_ADC_0_CONTROL_0:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_ADC_1_CONTROL_0);
	DBG_8195A("CODEC_ADC_1_CONTROL_0:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_ADC_2_CONTROL_0);
	DBG_8195A("CODEC_ADC_2_CONTROL_0:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_ADC_3_CONTROL_0);
	DBG_8195A("CODEC_ADC_3_CONTROL_0:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_ADC_4_CONTROL_0);
	DBG_8195A("CODEC_ADC_4_CONTROL_0:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_ADC_5_CONTROL_0);
	DBG_8195A("CODEC_ADC_5_CONTROL_0:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_ADC_6_CONTROL_0);
	DBG_8195A("CODEC_ADC_6_CONTROL_0:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_ADC_0_CONTROL_1);
	DBG_8195A("CODEC_ADC_0_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_ADC_1_CONTROL_1);
	DBG_8195A("CODEC_ADC_1_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_ADC_2_CONTROL_1);
	DBG_8195A("CODEC_ADC_2_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_ADC_3_CONTROL_1);
	DBG_8195A("CODEC_ADC_3_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_ADC_4_CONTROL_1);
	DBG_8195A("CODEC_ADC_4_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_ADC_5_CONTROL_1);
	DBG_8195A("CODEC_ADC_5_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_ADC_6_CONTROL_1);
	DBG_8195A("CODEC_ADC_6_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_DAC_L_CONTROL_0);
	DBG_8195A("CODEC_DAC_L_CONTROL_0:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_DAC_L_CONTROL_1);
	DBG_8195A("CODEC_DAC_L_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_DAC_L_CONTROL_2);
	DBG_8195A("CODEC_DAC_L_CONTROL_2:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_DAC_R_CONTROL_0);
	DBG_8195A("CODEC_DAC_R_CONTROL_0:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_DAC_R_CONTROL_1);
	DBG_8195A("CODEC_DAC_R_CONTROL_1:%x \n", tmp);
	tmp = HAL_READ32(AUDIO_REG_BASE, CODEC_DAC_R_CONTROL_2);
	DBG_8195A("CODEC_DAC_R_CONTROL_2:%x \n", tmp);

}

#endif

/*****************************************************************************************
 * *************************************SP/CODEC******************************************
 * ***************************************************************************************/
static void ameba_sp_codec_init(struct stream * stream, struct stream_config config)
{
	if (stream == NULL) {
		HAL_AUDIO_INFO("ameba_sp_codec_init stream is NULL, return");
		return;
	}

	sp_codec_inited_cnt++;
	HAL_AUDIO_INFO("ameba_sp_codec_init cnt: %d", sp_codec_inited_cnt);

	if (sp_codec_state == SP_CODEC_DEINITED) {
		u32 div, sample_rate, word_len, mono_stereo;

		PLL_I2S_Set(ENABLE);		//enable 98.304MHz PLL. needed if fs=8k/16k/32k/48k/96k
		PLL_PCM_Set(ENABLE);		//enable 45.1584MHz PLL. needed if fs=44.1k/8.2k

		sample_rate = get_ameba_codec_rate(config.rate);
		word_len = get_ameba_format(config.format);
		mono_stereo = get_ameba_channel(config.channels);

		if(sample_rate != SR_44P1K) {
			PLL_Sel(PLL_I2S);
		} else {
			PLL_Sel(PLL_PCM);
		}

		RCC_PeriphClockCmd(APBPeriph_AUDIOC, APBPeriph_AUDIOC_CLOCK, ENABLE);
		RCC_PeriphClockCmd(APBPeriph_SPORT, APBPeriph_SPORT_CLOCK, ENABLE);

		div = get_ameba_div(sample_rate);

		PLL_Div(div);

		Pinmux_Config(_PA_28, PINMUX_FUNCTION_GPIO);  //audio switch
		PAD_PullCtrl(_PA_28, GPIO_PuPd_DOWN);
		Pinmux_Config(_PB_6, PINMUX_FUNCTION_GPIO);       //audio amplifier shutdown
		PAD_PullCtrl(_PB_6, GPIO_PuPd_DOWN);
		PAD_CMD(_PA_1, DISABLE);
		PAD_CMD(_PA_2, DISABLE);
		PAD_CMD(_PB_30, DISABLE);
		PAD_CMD(_PB_31, DISABLE);

		HAL_AUDIO_INFO("ameba_sp_codec_init sample_rate: %d, word_len: %d, mono_stereo:%d, div:%d", sample_rate, word_len, mono_stereo, div);

		// ex:  SR_16K      WL_16      CH_STEREO
		CODEC_Init(sample_rate, word_len, mono_stereo, APP_LINE_OUT|APP_AMIC_IN);

		/*configure Sport according to the parameters*/
		AUDIO_SP_StructInit(&stream->SP_InitStruct);
		stream->SP_InitStruct.SP_MonoStereo= mono_stereo;
		stream->SP_InitStruct.SP_WordLen = word_len;
		stream->SP_InitStruct.SP_SelRxCh = SP_RX_CH_RR;

		AUDIO_SP_Init(AUDIO_SPORT_DEV, &stream->SP_InitStruct);

		sp_codec_state = SP_CODEC_INITED;

		/*GPIO 拉高*/
		GPIO_InitTypeDef GPIO_InitStruct_Temp;
		GPIO_InitStruct_Temp.GPIO_Pin = _PB_28;
		GPIO_InitStruct_Temp.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_Init(&GPIO_InitStruct_Temp);
		DelayMs(10);
		GPIO_WriteBit(_PB_28, 1);

	}
}


static void ameba_sp_codec_deinit(struct stream * stream)
{
	if (stream == NULL) {
		HAL_AUDIO_INFO("ameba_sp_codec_deinit stream is NULL, return");
		return;
	}

	sp_codec_inited_cnt--;
	HAL_AUDIO_INFO("ameba_sp_codec_deinit cnt: %d", sp_codec_inited_cnt);

	if (sp_codec_state == SP_CODEC_INITED && sp_codec_inited_cnt == 0) {
		HAL_AUDIO_INFO("sp_codec_deinit");

		RCC_PeriphClockCmd(APBPeriph_SPORT, APBPeriph_SPORT_CLOCK, DISABLE);
		RCC_PeriphClockCmd(APBPeriph_AUDIOC, APBPeriph_AUDIOC_CLOCK, DISABLE);
		CODEC_DeInit(APP_LINE_OUT|APP_AMIC_IN);

		PLL_I2S_Set(DISABLE);
		PLL_PCM_Set(DISABLE);

		sp_codec_state = SP_CODEC_DEINITED;
	}
}

/*****************************************************************************************
 * *************************************playback******************************************
 * ***************************************************************************************/

struct stream *stream_tx_init(struct stream_config config)
{
	HAL_AUDIO_INFO("[TX]stream_tx_init");
	struct stream *stream_out;
	stream_out = calloc(1, sizeof(struct stream));
	if (!stream_out) {
		HAL_AUDIO_INFO("[TX]calloc stream fail");
		return NULL;
	}

	stream_out->direction = STREAM_OUT;

	ameba_sp_codec_init(stream_out, config);

	CODEC_SetVolume(0xA0, 0xA0);

	stream_out->sport_dev_num = 0;
	stream_out->stream_buffer = create_circular_buffer();
	circular_alloc_buffer(stream_out->stream_buffer, config.period_size * config.frame_size * config.period_count);

	stream_out->gdma_count = 0;
	stream_out->gdma_irq_count = 0;
	stream_out->start_gdma = false;
	stream_out->restart_by_write = false;
	stream_out->SPGdmaStruct = calloc(1, sizeof(struct gdma_callback_data));
	if (!stream_out->SPGdmaStruct) {
		HAL_AUDIO_ERROR("calloc SPGdmaStruct fail");
		return NULL;
	}
	stream_out->SPGdmaStruct->own_stream = stream_out;
	stream_out->period_bytes = config.period_size * config.frame_size;
	stream_out->sem_should_post = false;
	rtw_mutex_init(&stream_out->lock);
	rtw_init_sema(&stream_out->sem, 0);

	HAL_AUDIO_INFO("[TX]stream out successfully inited, peroid_bytes: %u", stream_out->period_bytes);

	return stream_out;

}

//gdma done moving one period size data IRQ. Data is gdma_callback_data
uint32_t stream_period_tx_complete(void *Data)
{
	u32 tx_addr;
	u32 tx_length;
	//HAL_AUDIO_INFO("[TX]stream_period_tx_complete");

	struct gdma_callback_data *gdata = (struct gdma_callback_data *) Data;
	PGDMA_InitTypeDef GDMA_InitStruct;
	GDMA_InitStruct = &(gdata->SpTxGdmaInitStruct);
	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
	//u32 temp_isr = GDMA_ClearINT(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
	//HAL_AUDIO_INFO("[TX] irq: %ld", temp_isr);

	//to be done  Data should be a struct involve stream
	struct stream *stream_out = gdata->own_stream;
	update_tx_readptr_after_gdma_transfer(stream_out->stream_buffer, stream_out->period_bytes);
	stream_out->gdma_irq_count ++;

	if (stream_out->restart_by_write == true) {
		return 0;
	}

	if (get_available_buffer_size(stream_out->stream_buffer) == stream_out->stream_buffer->capacity ||
		get_buffer_remain_data_size(stream_out->stream_buffer) < stream_out->period_bytes) {
		//HAL_AUDIO_INFO("[TX]buffer empty,underrun");
		stream_out->restart_by_write = true;
	} else {
		//HAL_AUDIO_INFO("[TX]AUDIO_SP_TXGDMA_Restart");
		tx_addr = (u32)(stream_out->stream_buffer->raw_data + get_tx_readptr(stream_out->stream_buffer));
		tx_length = stream_out->period_bytes;
		AUDIO_SP_TXGDMA_Restart(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, tx_addr, tx_length);
		stream_out->gdma_count ++;
	}

	if (stream_out->sem_should_post) {
		rtw_up_sema_from_isr(&stream_out->sem);
		//printf("post sem\n");
	}

	return 0;
}

void stream_tx_start(struct stream *stream_out)
{
	HAL_AUDIO_INFO("stream_tx_start");
	if (stream_out->sport_dev_num == 0) {
		//HAL_AUDIO_INFO("[TX]stream_tx_start");
		//AUDIO_SP_DmaCmd(AUDIO_SPORT0_DEV, ENABLE);
		//AUDIO_SP_TXStart(AUDIO_SPORT0_DEV, ENABLE);
	} else {
		HAL_AUDIO_ERROR("unsupported sport num for tx");
	}
}

int stream_tx_write(struct stream *stream_out, const void *data, unsigned int bytes)
{
	unsigned int bytes_left_to_write = bytes;
	unsigned int bytes_written = 0;

	u32 tx_addr;

	//HAL_AUDIO_INFO("[TX]stream_tx_write");
	while (bytes_left_to_write != 0) {
		bytes_written = circular_buffer_write(stream_out->stream_buffer, (u8 *)data + bytes - bytes_left_to_write, bytes_left_to_write);

		if (!stream_out->start_gdma) {
			//HAL_AUDIO_INFO("[TX]stream_out->period_bytes:%d, remain size:%d", stream_out->period_bytes, get_buffer_remain_data_size(stream_out->stream_buffer));
			if (get_buffer_remain_data_size(stream_out->stream_buffer) >= stream_out->period_bytes) {
				stream_out->start_gdma = true;
				tx_addr = (u32)(stream_out->stream_buffer->raw_data + get_tx_readptr(stream_out->stream_buffer));

				AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, ENABLE);
				AUDIO_SP_TxStart(AUDIO_SPORT_DEV, ENABLE);

				AUDIO_SP_TXGDMA_Init(0, &(stream_out->SPGdmaStruct->SpTxGdmaInitStruct), stream_out->SPGdmaStruct, (IRQ_FUN)stream_period_tx_complete, (u8*)tx_addr,
										stream_out->period_bytes);

				stream_out->gdma_count ++;

				HAL_AUDIO_INFO("[TX] gdma init: index:%d, chNum:%d", stream_out->SPGdmaStruct->SpTxGdmaInitStruct.GDMA_Index, stream_out->SPGdmaStruct->SpTxGdmaInitStruct.GDMA_ChNum);

#if REG_DUMP
				gdma_dump(stream_out->SPGdmaStruct->SpTxGdmaInitStruct.GDMA_ChNum);
				dump_sport_regs(SPORT0_REG_BASE);
				dump_codec_regs();
#endif
			}
		}

		if (stream_out->restart_by_write) {
			if (get_buffer_remain_data_size(stream_out->stream_buffer) >= stream_out->period_bytes) {
				stream_out->restart_by_write = false;
				tx_addr = (u32)(stream_out->stream_buffer->raw_data + get_tx_readptr(stream_out->stream_buffer));
				//HAL_AUDIO_INFO("[TX] restart gdma at rp:%u", get_tx_readptr(stream_out->stream_buffer));
				AUDIO_SP_TXGDMA_Restart(stream_out->SPGdmaStruct->SpTxGdmaInitStruct.GDMA_Index, stream_out->SPGdmaStruct->SpTxGdmaInitStruct.GDMA_ChNum, tx_addr,
										stream_out->period_bytes);
				stream_out->gdma_count ++;
			}
		}

		bytes_left_to_write -= bytes_written;

		if (get_available_buffer_size(stream_out->stream_buffer) < bytes_left_to_write) {
			stream_out->sem_should_post = true;
			rtw_down_sema(&stream_out->sem);
		}
		stream_out->sem_should_post = false;
	}

	//HAL_AUDIO_INFO("[TX]stream_tx_write Exit");
	return 0;
}

void stream_tx_close(struct stream *stream_out)
{
	if (stream_out) {
		HAL_AUDIO_INFO("[TX]stream_tx_close");
		do {
			DelayMs(4);//test: sleep 4ms
			//HAL_AUDIO_INFO("[TX]waiting for tx to complete");
		} while (stream_out->gdma_count != stream_out->gdma_irq_count);
		//HAL_AUDIO_INFO("[TX] dma clear: index:%d, chNum:%d", stream_out->SPGdmaStruct->SpTxGdmaInitStruct.GDMA_Index, stream_out->SPGdmaStruct->SpTxGdmaInitStruct.GDMA_ChNum);

		DelayMs(10);

		GDMA_ClearINT(stream_out->SPGdmaStruct->SpTxGdmaInitStruct.GDMA_Index, stream_out->SPGdmaStruct->SpTxGdmaInitStruct.GDMA_ChNum);
		GDMA_Cmd(stream_out->SPGdmaStruct->SpTxGdmaInitStruct.GDMA_Index, stream_out->SPGdmaStruct->SpTxGdmaInitStruct.GDMA_ChNum, DISABLE);
		GDMA_ChnlFree(stream_out->SPGdmaStruct->SpTxGdmaInitStruct.GDMA_Index, stream_out->SPGdmaStruct->SpTxGdmaInitStruct.GDMA_ChNum);
		AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, DISABLE);
		AUDIO_SP_TxStart(AUDIO_SPORT_DEV, DISABLE);

		ameba_sp_codec_deinit(stream_out);

		rtw_mutex_free(&stream_out->lock);
		rtw_free_sema(&stream_out->sem);
		release_circular_buffer(stream_out->stream_buffer);
		if (stream_out->SPGdmaStruct) {
			free(stream_out->SPGdmaStruct);
			stream_out->SPGdmaStruct = NULL;
		}
		free(stream_out);
		stream_out = NULL;
	}
	HAL_AUDIO_INFO("[TX] exit");
}

/*****************************************************************************************
 * **************************************capture******************************************
 * ***************************************************************************************/

struct stream *stream_rx_init(struct stream_config config)
{
	struct stream *stream_in;

	stream_in = calloc(1, sizeof(struct stream));
	if (!stream_in) {
		HAL_AUDIO_INFO("[RX]calloc stream in fail");
		return NULL;
	}

	stream_in->direction = STREAM_IN;

	ameba_sp_codec_init(stream_in, config);

	u32 mic_bias_reg  = AUDIO_SI_ReadReg(0X02);
	mic_bias_reg &= (~(1 << 10));
	mic_bias_reg |= (3 << 13);
	AUDIO_SI_WriteReg(0x02, mic_bias_reg);

	//20dB amic boost
	uint32_t reg_value = 0;
	reg_value = AUDIO_SI_ReadReg(0X03);
	reg_value &= (~0xf);
	reg_value |= 5;
	AUDIO_SI_WriteReg(0x03, reg_value);
	/*差分*/
	reg_value = AUDIO_SI_ReadReg(HPO_MIC_CTRL);
	reg_value &= ~(1 << BIT_HPO_SEL);
	AUDIO_SI_WriteReg(HPO_MIC_CTRL, reg_value);
	DBG_8195A("HPO_MIC_CTRL: 08x%\n", HPO_MIC_CTRL);
	reg_value = AUDIO_SI_ReadReg(GEN_CTRL);
	reg_value &= ~(1 << BIT_DAC_R_POW);
	AUDIO_SI_WriteReg(GEN_CTRL, reg_value);
	reg_value = AUDIO_SI_ReadReg(HPO_MIC_CTRL);
	reg_value &= ~(1 << BIT_HPO_R_POW);
	AUDIO_SI_WriteReg(HPO_MIC_CTRL, reg_value);

	//mute L channel
	reg_value = AUDIO_SI_ReadReg(MICBST_CTRL);
	reg_value |= (3 << BIT_MICBST_MUTE_L);
	AUDIO_SI_WriteReg(MICBST_CTRL, reg_value);

	stream_in->sport_dev_num = 1;
	stream_in->stream_buffer = create_circular_buffer();
	circular_alloc_buffer(stream_in->stream_buffer, config.period_size * config.frame_size * config.period_count);

	stream_in->gdma_count = 0;
	stream_in->gdma_irq_count = 0;
	stream_in->start_gdma = false;
	stream_in->restart_by_read = false;
	stream_in->gdma_should_stop = false;
	stream_in->SPGdmaStruct = calloc(1, sizeof(struct gdma_callback_data));
	if (!stream_in->SPGdmaStruct) {
		HAL_AUDIO_ERROR("calloc SPGdmaStruct fail");
		return NULL;
	}
	stream_in->SPGdmaStruct->own_stream = stream_in;
	stream_in->period_bytes = config.period_size * config.frame_size;
	rtw_mutex_init(&stream_in->lock);

	HAL_AUDIO_INFO("[RX]stream in successfully inited,peroid_bytes: %u", stream_in->period_bytes);
	return stream_in;

}

void stream_rx_sel_sdm_num_for_ad_channel(struct stream *stream_in, u32 ad_channel, u32 sdm_num)
{
	(void) stream_in;

	/*AUDIO_CODEC_SelADCSrcToAmic(ad_channel + 1, sdm_num);	*/

}

//gdma done moving one period size data IRQ. Data is gdma_callback_data
uint32_t stream_period_rx_complete(void *Data)
{
	u32 rx_addr;
	u32 rx_length;
	//HAL_AUDIO_INFO("[RX]stream_period_rx_complete");

	struct gdma_callback_data *gdata = (struct gdma_callback_data *) Data;
	PGDMA_InitTypeDef GDMA_InitStruct;
	GDMA_InitStruct = &(gdata->SpRxGdmaInitStruct);
	/* Clear Pending ISR */
	DCache_Invalidate(GDMA_InitStruct->GDMA_DstAddr, GDMA_InitStruct->GDMA_BlockSize<<2);
	GDMA_ClearINT(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);

	//to be done  Data should be a struct involve stream
	struct stream *stream_in = gdata->own_stream;
	update_rx_writeptr_after_gdma_transfer(stream_in->stream_buffer, stream_in->period_bytes);
	stream_in->gdma_irq_count ++;
	//HAL_AUDIO_INFO("[RX] irq:%ld, irq_count:%ld", irq, stream_in->gdma_irq_count);

	if (stream_in->restart_by_read == true) {
		return 0;
	}

	if (get_available_buffer_size(stream_in->stream_buffer) == 0) {
		HAL_AUDIO_INFO("buffer full, overrun");
		stream_in->restart_by_read = true;
	} else {
		rx_addr = (u32)(stream_in->stream_buffer->raw_data + get_rx_writeptr(stream_in->stream_buffer));
		rx_length = stream_in->period_bytes;
		if ((get_available_buffer_size(stream_in->stream_buffer) >= rx_length) && !(stream_in->gdma_should_stop)) {
			AUDIO_SP_RXGDMA_Restart(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, rx_addr, rx_length);
			stream_in->gdma_count ++;
			//HAL_AUDIO_INFO("[RX] res gdma_count:%ld", stream_in->gdma_count);
		} else {
			stream_in->restart_by_read = true;
		}
	}

	return 0;
}

void stream_rx_start(struct stream *stream_in)
{
	u32 rx_addr;

	HAL_AUDIO_INFO("[RX] stream_rx_start");
	stream_in->gdma_should_stop = false;

	if (!stream_in->start_gdma) {
		stream_in->start_gdma = true;
		rx_addr = (u32)(stream_in->stream_buffer->raw_data + get_rx_writeptr(stream_in->stream_buffer));
		/*
		AUDIO_SP_RXGDMA_Init(1, GDMA_INT, &(stream_in->SPGdmaStruct->SpRxGdmaInitStruct), stream_in->SPGdmaStruct, (IRQ_FUN)stream_period_rx_complete, (u8 *)rx_addr,
							 stream_in->period_bytes);
		*/
		AUDIO_SP_RdmaCmd(AUDIO_SPORT_DEV, ENABLE);
		AUDIO_SP_RxStart(AUDIO_SPORT_DEV, ENABLE);
		AUDIO_SP_RXGDMA_Init(0, &(stream_in->SPGdmaStruct->SpRxGdmaInitStruct), stream_in->SPGdmaStruct, (IRQ_FUN)stream_period_rx_complete, (u8*)rx_addr,
						 stream_in->period_bytes);
		stream_in->gdma_count ++;
		HAL_AUDIO_INFO("[RX] gdma init: index:%d, chNum:%d", stream_in->SPGdmaStruct->SpRxGdmaInitStruct.GDMA_Index, stream_in->SPGdmaStruct->SpRxGdmaInitStruct.GDMA_ChNum);
	}
}

int stream_rx_read(struct stream *stream_in, void *data, unsigned int bytes)
{
	u32 rx_addr;

	unsigned int bytes_to_read = bytes;
	unsigned int bytes_read = 0;
	//HAL_AUDIO_INFO("[RX] stream_rx_read bytes: %d", bytes);

	while (bytes_to_read != 0) {
		bytes_read = circular_buffer_read(stream_in->stream_buffer, (u8 *)data + bytes - bytes_to_read, bytes_to_read);
		bytes_to_read -= bytes_read;
	}

	if (stream_in->restart_by_read) {
		if (get_available_buffer_size(stream_in->stream_buffer) >= stream_in->period_bytes) {
			stream_in->restart_by_read = false;
			rx_addr = (u32)(stream_in->stream_buffer->raw_data + get_rx_writeptr(stream_in->stream_buffer));
			AUDIO_SP_RXGDMA_Restart(stream_in->SPGdmaStruct->SpRxGdmaInitStruct.GDMA_Index, stream_in->SPGdmaStruct->SpRxGdmaInitStruct.GDMA_ChNum, rx_addr,
									stream_in->period_bytes);
			stream_in->gdma_count ++;
			HAL_AUDIO_INFO("[RX] restart gdma at wp:%u,count:%ld", get_rx_writeptr(stream_in->stream_buffer), stream_in->gdma_count);
		}
	}

	return 0;
}

void stream_rx_close(struct stream *stream_in)
{
	if (stream_in) {
		//HAL_AUDIO_INFO("[RX] stream_rx_close");
		stream_in->gdma_should_stop = true;
		do {
			DelayMs(4);//test: sleep 4ms
			//HAL_AUDIO_INFO("[RX] waiting for rx to complete");
		} while (stream_in->gdma_count != stream_in->gdma_irq_count);

		GDMA_ClearINT(stream_in->SPGdmaStruct->SpRxGdmaInitStruct.GDMA_Index, stream_in->SPGdmaStruct->SpRxGdmaInitStruct.GDMA_ChNum);
		GDMA_Cmd(stream_in->SPGdmaStruct->SpRxGdmaInitStruct.GDMA_Index, stream_in->SPGdmaStruct->SpRxGdmaInitStruct.GDMA_ChNum, DISABLE);
		GDMA_ChnlFree(stream_in->SPGdmaStruct->SpRxGdmaInitStruct.GDMA_Index, stream_in->SPGdmaStruct->SpRxGdmaInitStruct.GDMA_ChNum);
		AUDIO_SP_RdmaCmd(AUDIO_SPORT_DEV, DISABLE);
		AUDIO_SP_RxStart(AUDIO_SPORT_DEV, DISABLE);

		ameba_sp_codec_deinit(stream_in);

		rtw_mutex_free(&stream_in->lock);
		release_circular_buffer(stream_in->stream_buffer);
		if (stream_in->SPGdmaStruct) {
			free(stream_in->SPGdmaStruct);
			stream_in->SPGdmaStruct = NULL;
		}
		free(stream_in);
		stream_in = NULL;

	}
	HAL_AUDIO_INFO("[RX] exit");
}
