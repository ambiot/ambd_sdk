/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "device.h"
#include "main.h"

#define KM0_PWM_TIM_IN_USE		0	// 1:use KM0 PWM timer, 0: use KM4 PWM timer

#define PWM_TIMER	5
#define PWM_PERIOD  20000
#define PWM_PRESCALER	12
#define PWM_STEP    (PWM_PERIOD/20)

int pwms[4]={0, PWM_PERIOD/4, PWM_PERIOD/2, PWM_PERIOD/4*3};
int steps[4]={PWM_STEP,PWM_STEP,PWM_STEP,PWM_STEP};

#if (defined(KM0_PWM_TIM_IN_USE) && (KM0_PWM_TIM_IN_USE == 1))
#define TIM5				TIMM05
#define TIMx_irq			TIMx_irq_LP
#define PINMUX_FUNCTION_PWM_HS		PINMUX_FUNCTION_PWM_LP
u8 PWM_pin2chan[4][2]={
//pwm channel pin, channel num
	{_PA_12, 0},
	{_PA_13, 1},
	{_PB_4, 2},
	{_PB_5, 3}
};
#else
u8 PWM_pin2chan[4][2]={
	{_PA_12, 0},
	{_PA_13, 1},
	{_PB_4, 8},
	{_PB_5, 9}
};
#endif

void pwm_delay(void)
{
	int i;
	for(i=0;i<10000000;i++)
		asm(" nop");
}

void raw_pwm_demo(void)
{
	RTIM_TimeBaseInitTypeDef		RTIM_InitStruct;
	TIM_CCInitTypeDef		TIM_CCInitStruct;
	int pwm_chan=0;
	int i;

	RTIM_TimeBaseStructInit(&RTIM_InitStruct);
	RTIM_InitStruct.TIM_Idx = PWM_TIMER;
	RTIM_InitStruct.TIM_Prescaler = PWM_PRESCALER;
	RTIM_InitStruct.TIM_Period = PWM_PERIOD;

	RTIM_TimeBaseInit(TIM5, (&RTIM_InitStruct), TIMx_irq[5], NULL, NULL);

	for(pwm_chan=0; pwm_chan<4; pwm_chan++){
		RTIM_CCStructInit(&TIM_CCInitStruct);
		RTIM_CCxInit(TIM5, &TIM_CCInitStruct, PWM_pin2chan[pwm_chan][1]);
		RTIM_CCRxSet(TIM5, pwms[pwm_chan], PWM_pin2chan[pwm_chan][1]);
		RTIM_CCxCmd(TIM5, PWM_pin2chan[pwm_chan][1], TIM_CCx_Enable);

		Pinmux_Config(PWM_pin2chan[pwm_chan][0], PINMUX_FUNCTION_PWM_HS);
	}

	RTIM_Cmd(TIM5, ENABLE);

	while (1) {        
		for (i=0; i<4; i++) {
			RTIM_CCRxSet(TIM5, pwms[i], PWM_pin2chan[i][1]);

			pwms[i] += steps[i];
			if (pwms[i] >= PWM_PERIOD) {
				steps[i] = -PWM_STEP;
				pwms[i] = PWM_PERIOD;
			}

			if (pwms[i] <= 0) {
				steps[i] = PWM_STEP;
				pwms[i] = 0;
			}
		}
		pwm_delay();
	}
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
//int main_app(IN u16 argc, IN u8 *argv[])
void main(void)
{
	if (pdTRUE != xTaskCreate( (TaskFunction_t)raw_pwm_demo, "RAW_PWM_DEMO_TASK", (2048 /4), (void *)NULL, (tskIDLE_PRIORITY + 1), NULL))
	{
		DiagPrintf("Create RAW_PWM_DEMO_TASK Err!!\n");
	}
	
	vTaskStartScheduler();
}

