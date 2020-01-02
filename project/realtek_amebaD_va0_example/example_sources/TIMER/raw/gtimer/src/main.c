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

#define GPIO_LED_PIN1       _PA_12
#define GPIO_LED_PIN2       _PB_5
#define GTIMER_PERIOD_IDX		2	//gtimer2
#define GTIMER_ONESHOT_IDX	3	//gtimer3
#define GTIMER_PERIOD_US		1000000	//us
#define GTIMER_ONESHOT_US		500000	//us

volatile uint32_t time2_expired=0;

void timer1_timeout_handler(uint32_t id)
{
	RTIM_TimeBaseInitTypeDef * gtimer = (RTIM_TimeBaseInitTypeDef *) id;

	GPIO_WriteBit(GPIO_LED_PIN1, !GPIO_ReadDataBit(GPIO_LED_PIN1));
	RTIM_INTClear(TIMx[gtimer->TIM_Idx]);
}

void timer2_timeout_handler(uint32_t id)
{
	RTIM_TimeBaseInitTypeDef * gtimer = (RTIM_TimeBaseInitTypeDef *) id;

	time2_expired = 1;
	RTIM_INTClear(TIMx[gtimer->TIM_Idx]);
	RTIM_Cmd(TIMx[gtimer->TIM_Idx], DISABLE);
}

void gpio_ctrl_led_config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct1;
	GPIO_InitTypeDef GPIO_InitStruct2;

	GPIO_InitStruct1.GPIO_Pin = GPIO_LED_PIN1;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct2.GPIO_Pin = GPIO_LED_PIN2;
	GPIO_InitStruct2.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(&GPIO_InitStruct2);
}

void raw_gtimer_demo(void)
{
	RTIM_TimeBaseInitTypeDef TIM_InitStruct1;
	RTIM_TimeBaseInitTypeDef TIM_InitStruct2;
	
	//Init LED control pin
	gpio_ctrl_led_config();

	//initial a periodical gimer
	RTIM_TimeBaseStructInit(&TIM_InitStruct1);
	TIM_InitStruct1.TIM_Idx = GTIMER_PERIOD_IDX;
	TIM_InitStruct1.TIM_Period = GTIMER_PERIOD_US/1000000*32768 - 1;
	
	RTIM_TimeBaseInit(TIMx[GTIMER_PERIOD_IDX], (&TIM_InitStruct1), TIMx_irq[GTIMER_PERIOD_IDX], (IRQ_FUN) timer1_timeout_handler, (u32) (&TIM_InitStruct1));
	RTIM_INTConfig(TIMx[GTIMER_PERIOD_IDX], TIM_IT_Update, ENABLE);
	RTIM_Cmd(TIMx[GTIMER_PERIOD_IDX], ENABLE);

	//initial a oneshort gimer and re-trigger it in while loop
	RTIM_TimeBaseStructInit(&TIM_InitStruct2);
	TIM_InitStruct2.TIM_Idx = GTIMER_ONESHOT_IDX;
	TIM_InitStruct2.TIM_Period = (u32)((float)GTIMER_ONESHOT_US/1000000*32767);
	
	RTIM_TimeBaseInit(TIMx[GTIMER_ONESHOT_IDX], (&TIM_InitStruct2), TIMx_irq[GTIMER_ONESHOT_IDX], (IRQ_FUN) timer2_timeout_handler, (u32) &TIM_InitStruct2);
	time2_expired = 0;
	RTIM_INTConfig(TIMx[GTIMER_ONESHOT_IDX], TIM_IT_Update, ENABLE);
	RTIM_Cmd(TIMx[GTIMER_ONESHOT_IDX], ENABLE);

	while(1){
		if (time2_expired) {
			GPIO_WriteBit(GPIO_LED_PIN2, !GPIO_ReadDataBit(GPIO_LED_PIN2));
			time2_expired = 0;
			RTIM_Cmd(TIMx[GTIMER_ONESHOT_IDX], ENABLE);
		}
	}
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	if (pdTRUE != xTaskCreate( (TaskFunction_t)raw_gtimer_demo, "RAW_GTIMER_DEMO_TASK", (2048 /4), (void *)NULL, (tskIDLE_PRIORITY + 1), NULL))
	{
		DiagPrintf("Create RAW_GTIMER_DEMO_TASK Err!!\n");
	}
	
	vTaskStartScheduler();
}

