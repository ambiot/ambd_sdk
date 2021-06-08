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

#define GPIO_LED_PIN       _PB_5
#define GPIO_PUSHBT_PIN    _PA_12

void raw_gpio_demo(void)
{
	GPIO_InitTypeDef GPIO_InitStruct_LED;
	GPIO_InitTypeDef GPIO_InitStruct_PUSHBT;

	// Init LED control pin
	GPIO_InitStruct_LED.GPIO_Pin = GPIO_LED_PIN;
	GPIO_InitStruct_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(&GPIO_InitStruct_LED);

	// Init Push Button pin
	GPIO_InitStruct_PUSHBT.GPIO_Pin = GPIO_PUSHBT_PIN;
	GPIO_InitStruct_PUSHBT.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct_PUSHBT.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(&GPIO_InitStruct_PUSHBT);

	while (1) {
		if (GPIO_ReadDataBit(GPIO_PUSHBT_PIN)) {
			//turn off LED
			GPIO_WriteBit(GPIO_LED_PIN, 0);
		} else {
			// turn on LED
			GPIO_WriteBit(GPIO_LED_PIN, 1);
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
	if (pdTRUE != xTaskCreate( (TaskFunction_t)raw_gpio_demo, "RAW_GPIO_DEMO_TASK", (2048 /4), (void *)NULL, (tskIDLE_PRIORITY + 1), NULL))
	{
		DiagPrintf("Create RAW_GPIO_DEMO_TASK Err!!\n");
	}
	
	vTaskStartScheduler();
}

