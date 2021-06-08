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

extern GPIO_TypeDef* PORT_AB[2];
#define CACHE_WRITE_ACTION (0)

void gpio_demo_raw(void)
{
	GPIO_InitTypeDef GPIO_InitStruct_LED;
	GPIO_InitTypeDef GPIO_InitStruct_PUSHBT;

#if defined(CACHE_WRITE_ACTION) && (CACHE_WRITE_ACTION == 1)
	u8 port_num = PORT_NUM(GPIO_LED_PIN);
	u8 pin_num  = PIN_NUM(GPIO_LED_PIN);
	u32 RegValue;
	GPIO_TypeDef* GPIO = PORT_AB[port_num];
#endif

	// init LED control pin
	GPIO_InitStruct_LED.GPIO_Pin = GPIO_LED_PIN;
	GPIO_InitStruct_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(&GPIO_InitStruct_LED);

	// init Push Button pin
	GPIO_InitStruct_PUSHBT.GPIO_Pin = GPIO_PUSHBT_PIN;
	GPIO_InitStruct_PUSHBT.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct_PUSHBT.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(&GPIO_InitStruct_PUSHBT);

	while (1) {
#if defined(CACHE_WRITE_ACTION) && (CACHE_WRITE_ACTION == 1)
		if (GPIO_ReadDataBit(GPIO_PUSHBT_PIN)) {
			// turn off LED
			RegValue =  GPIO->PORT[0].DR;
			RegValue &= ~(1 << pin_num);
			GPIO->PORT[0].DR = RegValue;
		} else {
			// turn on LED
			RegValue =  GPIO->PORT[0].DR;
			RegValue |= (1<< pin_num);
			GPIO->PORT[0].DR = RegValue;
		}
#else
		if (GPIO_ReadDataBit(GPIO_PUSHBT_PIN)) {
			// turn on LED
			GPIO_WriteBit(GPIO_LED_PIN, 1);
		} else {
			// turn off LED
			GPIO_WriteBit(GPIO_LED_PIN, 0);
		}
#endif
	}
}

void main(void)
{
	if (pdTRUE != xTaskCreate( (TaskFunction_t)gpio_demo_raw, "RAW_GPIO_DEMO_TASK", (2048 /4), (void *)NULL, (tskIDLE_PRIORITY + 1), NULL))
	{
		DiagPrintf("Create RAW_GPIO_DEMO_TASK Err!!\n");
	}
	
	vTaskStartScheduler();
}

