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

int led_ctrl = 1;

void gpio_demo_irq_handler (uint32_t id, u32 event)
{
    gpio_t *gpio_led;

    DBG_8195A("%s==>\n", __FUNCTION__);
    gpio_led = (gpio_t *)id;

    led_ctrl = !led_ctrl;
    GPIO_WriteBit(GPIO_LED_PIN, led_ctrl);
}

void raw_gpio_irq_demo(void)
{
	GPIO_InitTypeDef GPIO_InitStruct_LED;
	GPIO_InitTypeDef GPIO_InitStruct_PUSHBT;
	u32 port_num; 

	// Init LED control pin
	GPIO_InitStruct_LED.GPIO_Pin = GPIO_LED_PIN;
	GPIO_InitStruct_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(&GPIO_InitStruct_LED);

	// Init Push Button pin
	GPIO_INTConfig(GPIO_PUSHBT_PIN, DISABLE);
	port_num = PORT_NUM(GPIO_PUSHBT_PIN);
	
	GPIO_InitStruct_PUSHBT.GPIO_Pin = GPIO_PUSHBT_PIN;
	GPIO_InitStruct_PUSHBT.GPIO_Mode = GPIO_Mode_INT;
	GPIO_InitStruct_PUSHBT.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct_PUSHBT.GPIO_ITTrigger = GPIO_INT_Trigger_EDGE;
	GPIO_InitStruct_PUSHBT.GPIO_ITPolarity = GPIO_INT_POLARITY_ACTIVE_LOW;

	if (port_num == GPIO_PORT_A) {
		InterruptRegister((IRQ_FUN)GPIO_INTHandler, GPIOA_IRQ, (u32)GPIOA_BASE, 10);		
		InterruptEn(GPIOA_IRQ, 10);
	} else if (port_num == GPIO_PORT_B) {
		InterruptRegister((IRQ_FUN)GPIO_INTHandler, GPIOB_IRQ, (u32)GPIOB_BASE, 10);		
		InterruptEn(GPIOB_IRQ, 10);
	}

	GPIO_Init(&GPIO_InitStruct_PUSHBT);
	GPIO_UserRegIrq(GPIO_PUSHBT_PIN, (void *)gpio_demo_irq_handler, &GPIO_InitStruct_PUSHBT);
	GPIO_INTConfig(GPIO_PUSHBT_PIN, ENABLE);

	GPIO_WriteBit(GPIO_LED_PIN, led_ctrl);
	
	while (1);
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	if (pdTRUE != xTaskCreate( (TaskFunction_t)raw_gpio_irq_demo, "RAW_GPIO_IRQ_DEMO_TASK", (2048 /4), (void *)NULL, (tskIDLE_PRIORITY + 1), NULL))
	{
		DiagPrintf("Create RAW_GPIO_IRQ_DEMO_TASK Err!!\n");
	}
	
	vTaskStartScheduler();
}

