/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2015 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "device.h"
#include "diag.h"
#include "main.h"

#define GPIO_IRQ_LEVEL_PIN        _PA_12
#define GPIO_SIGNAL_SOURCE        _PB_5

void gpio_level_irq_handler (uint32_t id, u32 event)
{
	GPIO_InitTypeDef * gpio_id = (GPIO_InitTypeDef *) id;
	u32 level = gpio_id->GPIO_ITPolarity;

	// Disable level irq because the irq will keep triggered when it keeps in same level.
	GPIO_INTConfig(GPIO_IRQ_LEVEL_PIN, DISABLE);

	// make some software de-bounce here if the signal source is not stable.
	if (level == GPIO_INT_POLARITY_ACTIVE_LOW) {
		DBG_8195A("low level event\r\n");

        	// Change to listen to high level event
		gpio_id->GPIO_ITPolarity = GPIO_INT_POLARITY_ACTIVE_HIGH;
		GPIO_INTMode(GPIO_IRQ_LEVEL_PIN, ENABLE, gpio_id->GPIO_ITTrigger, gpio_id->GPIO_ITPolarity, GPIO_INT_DEBOUNCE_ENABLE);
	} else  if (level == GPIO_INT_POLARITY_ACTIVE_HIGH) {
		DBG_8195A("high level event\r\n");

		// Change to listen to low level event
		gpio_id->GPIO_ITPolarity = GPIO_INT_POLARITY_ACTIVE_LOW;
		GPIO_INTMode(GPIO_IRQ_LEVEL_PIN, ENABLE, gpio_id->GPIO_ITTrigger, gpio_id->GPIO_ITPolarity, GPIO_INT_DEBOUNCE_ENABLE);
	}
	
	//Delay 2 debounce clock for clearing level int status when set gpio_polarity
	DelayUs(61);

	GPIO_INTConfig(GPIO_IRQ_LEVEL_PIN, ENABLE);
}

void main(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct_Source;
	GPIO_InitTypeDef GPIO_InitStruct_IRQ;
	u8 port_num;
	int i;
	
	//init gpio pin as irq level int mode
	GPIO_INTConfig(GPIO_IRQ_LEVEL_PIN, DISABLE);
	GPIO_InitStruct_IRQ.GPIO_Pin = GPIO_IRQ_LEVEL_PIN;
	GPIO_InitStruct_IRQ.GPIO_Mode = GPIO_Mode_INT;
	GPIO_InitStruct_IRQ.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct_IRQ.GPIO_ITTrigger = GPIO_INT_Trigger_LEVEL;
	GPIO_InitStruct_IRQ.GPIO_ITPolarity = GPIO_INT_POLARITY_ACTIVE_LOW;
	GPIO_InitStruct_IRQ.GPIO_ITDebounce = GPIO_INT_DEBOUNCE_ENABLE;

	port_num =  PORT_NUM(GPIO_IRQ_LEVEL_PIN);
	if (port_num == GPIO_PORT_A) {
		InterruptRegister(GPIO_INTHandler, GPIOA_IRQ, GPIOA_BASE, 10);		
		InterruptEn(GPIOA_IRQ, 10);
	} else {
		InterruptRegister(GPIO_INTHandler, GPIOB_IRQ, GPIOB_BASE, 10);		
		InterruptEn(GPIOB_IRQ, 10);
	}
 
	GPIO_Init(&GPIO_InitStruct_IRQ);
	GPIO_UserRegIrq(GPIO_IRQ_LEVEL_PIN, gpio_level_irq_handler, (&GPIO_InitStruct_IRQ));
	GPIO_INTConfig(GPIO_IRQ_LEVEL_PIN, ENABLE);
	
	// init gpio source pin
	GPIO_InitStruct_Source.GPIO_Pin = GPIO_SIGNAL_SOURCE;
	GPIO_InitStruct_Source.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(&GPIO_InitStruct_Source);

	while (1) {
		GPIO_WriteBit(GPIO_SIGNAL_SOURCE, 1);
		for (i=0; i<20000000; i++) asm("nop");
		GPIO_WriteBit(GPIO_SIGNAL_SOURCE, 0);
		for (i=0; i<20000000; i++) asm("nop");
	}
}

