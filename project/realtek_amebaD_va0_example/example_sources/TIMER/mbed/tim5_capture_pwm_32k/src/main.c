/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "ameba_soc.h"
#include "main.h"

#define PWM_PERIOD	40000000/32768

u32 capture_chn = 1;
u32 cnt = 0;
u32 val1, val2;

VOID tim5_capture_ISR(u32 channel)
{	
	cnt++;
	if(cnt % 2){
		val1 = RTIM_CCRxGet(TIM5, channel) & 0xffff;
	}
	else{
		val2 = RTIM_CCRxGet(TIM5, channel) & 0xffff;
		cnt = 0;

		if(val2 > val1)
			DBG_8195A("frequency: %d\n", 40000000/(val2 - val1));
		else
			DBG_8195A("frequency: %d\n", 40000000/(PWM_PERIOD + 1 - val1 + val2));
	}

	RTIM_INTClear(TIM5);
}

void tim5_gen_pwm_32k()
{
	int pwm_chan = 0;
	RTIM_TimeBaseInitTypeDef TIM_InitStruct_temp;
	TIM_CCInitTypeDef TIM_CCInitStruct;

	RTIM_TimeBaseStructInit(&TIM_InitStruct_temp);
	TIM_InitStruct_temp.TIM_Idx = 5;
	TIM_InitStruct_temp.TIM_Period = PWM_PERIOD;
	RTIM_TimeBaseInit(TIM5, &TIM_InitStruct_temp, TIMER5_IRQ, (IRQ_FUN)tim5_capture_ISR, capture_chn);

	/* channel 0 output 32KHz pwm*/
	RTIM_CCStructInit(&TIM_CCInitStruct);
	RTIM_CCxInit(TIM5, &TIM_CCInitStruct, pwm_chan);
	RTIM_CCRxSet(TIM5, PWM_PERIOD / 2 + 1, pwm_chan);
	RTIM_CCxCmd(TIM5, pwm_chan, TIM_CCx_Enable);

	Pinmux_Config(_PA_12, PINMUX_FUNCTION_PWM_HS);
	RTIM_Cmd(TIM5, ENABLE);
}

void tim5_capture_32k()
{
	TIM_CCInitTypeDef TIM_CCInitStruct;
	
	RTIM_CCStructInit(&TIM_CCInitStruct);
	TIM_CCInitStruct.TIM_CCMode = TIM_CCMode_Inputcapture;
	
	RTIM_CCxInit(TIM5, &TIM_CCInitStruct, capture_chn);
	RTIM_CCxCmd(TIM5, capture_chn, TIM_CCx_Enable);

	Pinmux_Config(_PB_5, PINMUX_FUNCTION_TIMINPUT_HS);
	PAD_PullCtrl(_PB_5, GPIO_PuPd_UP);

	RTIM_INTConfig(TIM5, TIM_IT_CCx[capture_chn], ENABLE);
	RTIM_Cmd(TIM5, ENABLE);
}

void tim5_capture_pwm(void)
{
	/* TIM5 generate 32760Hz pwm wave, channel0 output pwm*/
	tim5_gen_pwm_32k();

	/* TIM5 channel1 capture pwm rising edge*/
	tim5_capture_32k();

	vTaskDelete(NULL);
}


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	if(xTaskCreate( (TaskFunction_t)tim5_capture_pwm, "TIM5 CAPTURE PWM DEMO", (2048/4), NULL, (tskIDLE_PRIORITY + 1), NULL)!= pdPASS) {
			DBG_8195A("Cannot create tim5 capture pwm demo task\n\r");
	}

	vTaskStartScheduler();

	while(1);
}


