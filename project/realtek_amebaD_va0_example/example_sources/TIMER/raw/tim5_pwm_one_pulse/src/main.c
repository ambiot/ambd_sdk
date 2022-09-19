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

#define PWM_PERIOD	99

static GPIO_InitTypeDef GPIO_InitStruct;

void tim5_gen_pwm_one_pulse(void)
{
	int pwm_chan = 1;
	RTIM_TimeBaseInitTypeDef TIM_InitStruct_temp;
	TIM_CCInitTypeDef TIM_CCInitStruct;

	RTIM_TimeBaseStructInit(&TIM_InitStruct_temp);
	TIM_InitStruct_temp.TIM_Idx = 5;
	TIM_InitStruct_temp.TIM_Prescaler = 199;
	TIM_InitStruct_temp.TIM_Period = PWM_PERIOD;
	RTIM_TimeBaseInit(TIM5, &TIM_InitStruct_temp, TIMER5_IRQ, NULL, 0);
	/*enable one pulse mode*/
	RTIM_SetOnePulseOutputMode(TIM5, TIM_OPMode_Single, TIM_OPMode_ETP_negative);

	RTIM_CCStructInit(&TIM_CCInitStruct);
	RTIM_CCxInit(TIM5, &TIM_CCInitStruct, pwm_chan);
	RTIM_CCRxSet(TIM5, PWM_PERIOD / 2 + 1, pwm_chan);
	RTIM_CCxCmd(TIM5, pwm_chan, TIM_CCx_Enable);

	Pinmux_Config(_PA_13, PINMUX_FUNCTION_PWM_HS);
	RTIM_Cmd(TIM5, ENABLE);

	/*one pulse mode trigger pin*/
	Pinmux_Config(_PB_5, PINMUX_FUNCTION_TIMINPUT_HS); 
	PAD_PullCtrl(_PB_5, GPIO_PuPd_UP);
}

void gpio_int_ISR (u32 data, u32 event)
{
	GPIO_InitTypeDef *gpio_irq_pin = (GPIO_InitTypeDef *)data;
		
	DiagPrintf("%s pin:%d ==> event=%d\n", __FUNCTION__, gpio_irq_pin->GPIO_Pin, event);    
}

void gpio_interrupt_enable(void)
{
	u32 GPIO_Pin = _PA_12;
		
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INT;
	GPIO_InitStruct.GPIO_ITTrigger= GPIO_INT_Trigger_EDGE;
	GPIO_InitStruct.GPIO_ITPolarity = GPIO_INT_POLARITY_ACTIVE_HIGH;
	GPIO_InitStruct.GPIO_ITDebounce = GPIO_INT_DEBOUNCE_ENABLE;
		
	InterruptRegister(GPIO_INTHandler, GPIOA_IRQ, (u32)GPIOA_BASE, 10);		
	InterruptEn(GPIOA_IRQ, 10);
	
	GPIO_Init(&GPIO_InitStruct);
	GPIO_UserRegIrq(GPIO_Pin, (void*)gpio_int_ISR, &GPIO_InitStruct);
	
	GPIO_INTConfig(GPIO_Pin, ENABLE);

}

void tim5_pwm_one_pulse(void)
{
	/* generate one pulse mode pwm wave*/
	tim5_gen_pwm_one_pulse();

	/* enable gpio interrupt*/
	gpio_interrupt_enable();

	vTaskDelete(NULL);
}


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	if(xTaskCreate( (TaskFunction_t)tim5_pwm_one_pulse, "TIM5 PWM ONE PULSE DEMO", (2048/4), NULL, (tskIDLE_PRIORITY + 1), NULL)!= pdPASS) {
			DiagPrintf("Cannot create tim5 pwm one pulse mode demo task\n\r");
	}

	vTaskStartScheduler();
}


