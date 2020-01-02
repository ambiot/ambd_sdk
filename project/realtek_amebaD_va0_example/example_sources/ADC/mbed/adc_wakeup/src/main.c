/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "device.h"
#include "analogin_api.h"
#include <sys_api.h>

u32 adc_buf[8];

void adc_isr(void *Data)
{
	u32 isr = 0;
	u32 i = 0;

	isr = ADC_GetISR();
	if (isr & BIT_ADC_FIFO_THRESHOLD) {
		for(i = 0; i < 8; i++) {
			adc_buf[i] = (u32)ADC_Read();
		}
	}

	ADC_INTClear();
}

static u32 adc_suspend(u32 expected_idle_time )
{
	ADC_INTClear();
	ADC_Cmd(ENABLE);

	return TRUE;
}

static u32 adc_resume(u32 expected_idle_time)
{	
	u32 i = 0;
	ADC_Cmd(DISABLE);
	for (i = 0; i < 8; i += 2) {
		DBG_8195A("%08x, %08x\n", adc_buf[i], adc_buf[i + 1]);
		adc_buf[i] = 0;
		adc_buf[i+1] = 0;
	}
	
	return TRUE;
}

VOID adc_wakeup (VOID)
{
	ADC_InitTypeDef ADCInitStruct;
	
	/* ADC Interrupt Initialization */
	InterruptRegister((IRQ_FUN)&adc_isr, ADC_IRQ, (u32)NULL, 5);
	InterruptEn(ADC_IRQ, 5);

	/* To release ADC delta sigma clock gating */
	PLL2_Set(BIT_SYS_SYSPLL_CK_ADC_EN, ENABLE);

	/* Turn on ADC active clock */
	RCC_PeriphClockCmd(APBPeriph_ADC, APBPeriph_ADC_CLOCK, ENABLE);

	ADC_InitStruct(&ADCInitStruct);
	ADCInitStruct.ADC_BurstSz = 8;
	ADCInitStruct.ADC_OneShotTD = 8; /* means 4 times */
	ADC_Init(&ADCInitStruct);
	ADC_SetOneShot(ENABLE, 100, ADCInitStruct.ADC_OneShotTD); /* 100 will task 200ms */

	pmu_register_sleep_callback(PMU_ADC_DEVICE, (PSM_HOOK_FUN)adc_suspend, (void*)NULL, (PSM_HOOK_FUN)adc_resume, (void*)NULL);

	pmu_set_sysactive_time(1000);
	pmu_release_wakelock(PMU_OS);

	vTaskDelete(NULL);
}

void main(void)
{
	if(xTaskCreate( (TaskFunction_t)adc_wakeup, "ADC WAKEUP DEMO", (2048/4), NULL, (tskIDLE_PRIORITY + 1), NULL)!= pdPASS) {
			DBG_8195A("Cannot create ADC wakeup demo task\n\r");
	}

	vTaskStartScheduler();

	while(1);
}



