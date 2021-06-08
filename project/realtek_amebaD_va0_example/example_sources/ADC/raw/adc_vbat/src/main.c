/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "rtl8721d.h"

#define VBAT_CH			ADC_CH7
#define ADC_TIM_IDX		2
#define PERIOD_MS		500

/*
 * OFFSET:   10 times of sample data at 0.000v, 10*value(0.000v)
 * GAIN_DIV: 10 times of value(1.000v)-value(0.000v) or value(2.000v)-value(1.000v) or value(3.000v)-value(2.000v)
 */
u16 OFFSET;
u16 GAIN_DIV;
#define AD2MV(ad,offset,gain)	(((10 * ad) -offset) * 1000 / gain)	

void adc_irq_handle(void)
{
	u32 status = ADC_GetISR();
	u32 cnt;
	u16 value;
	int32_t vol;

	if(status & BIT_ADC_IT_FIFO_FULL_STS) {
		cnt = ADC_GetRxCount();

		while(cnt--) {
			value = ADC_Read();
			vol = AD2MV(value, OFFSET, GAIN_DIV);
			DBG_8195A("ADC_Vbat: 0x%x = %d mv\n", value, vol);
		}
	}

	ADC_INTClearPendingBits(status);
}

void adc_vbat_demo(void)
{
	DBG_8195A("adc vbat init start\n");

	ADC_InitTypeDef ADC_InitStruct;

	ADC_StructInit(&ADC_InitStruct);
	ADC_InitStruct.ADC_OpMode = ADC_TIM_TRI_MODE;
	ADC_InitStruct.ADC_CvlistLen = 0;
	ADC_InitStruct.ADC_Cvlist[0]= VBAT_CH;

	ADC_Init(&ADC_InitStruct);
	ADC_INTConfig(BIT_ADC_IT_FIFO_FULL_EN, ENABLE);

	InterruptRegister((IRQ_FUN)adc_irq_handle, ADC_IRQ, NULL, 10);
	InterruptEn(ADC_IRQ, 10);

	ADC_Cmd(ENABLE);
	ADC_TimerTrigCmd(ADC_TIM_IDX, PERIOD_MS, ENABLE);

	DBG_8195A("adc vbat init done\n");
	
	vTaskDelete(NULL);
}

VOID main (VOID)
{
	u8 EfuseBuf[2];
	u32 index;
	u32 addressOffset = 0x1D4;
	u32 addressGain = 0x1D6;


	for (index = 0; index< 2; index++) {
		EFUSERead8(0, addressOffset+index, EfuseBuf + index, L25EOUTVOLTAGE);
	}
	OFFSET = EfuseBuf[1]<<8|EfuseBuf[0];

	for (index = 0; index< 2; index++) {
		EFUSERead8(0, addressGain+index, EfuseBuf + index, L25EOUTVOLTAGE);
	}
	GAIN_DIV = EfuseBuf[1]<<8|EfuseBuf[0];

	if (OFFSET == 0xFFFF) {
		OFFSET = 0x9C4;
		DBG_8195A("Default OFFSET!\n");
	}

	if (GAIN_DIV == 0xFFFF) {
		GAIN_DIV = 7860;
		DBG_8195A("Default GAIN_DIV!\n");
	}

	DBG_8195A("OFFSET = %x\n", OFFSET);
	DBG_8195A("GAIN_DIV = %x\n", GAIN_DIV);
	
	if(xTaskCreate( (TaskFunction_t)adc_vbat_demo, "ADC VBAT DEMO", (2048/4), NULL, (tskIDLE_PRIORITY + 1), NULL)!= pdPASS) {
			DBG_8195A("Cannot create ADC Vbat demo task\n\r");
	}

	vTaskStartScheduler();

	while(1);
}


