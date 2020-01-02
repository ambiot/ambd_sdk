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

#define PORT_OUTPUT_TEST    1   // 1: output test, 0: input test

#define LED_PATTERN_NUM     12

const uint32_t led_pattern[LED_PATTERN_NUM]={0x20FF000, 0x20FE000, 0x20FD000, 0x20FB000, 0x20F7000, 0x20EF000, 0x20DF000, 0x20BF000, 0x207F000, 0x00FF000, 0x20FF000, 0x0000000};

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
#if PORT_OUTPUT_TEST

void main(void)
{
	unsigned int pin_mask;
	u32 pin_num = 32;
	int pin_index;
	int i;
	
	pin_mask = 0x20FF000; //each bit map to one pin: 0: pin disable; 1: pin enable
	GPIO_PortDirection(GPIO_PORT_A, pin_mask, GPIO_Mode_OUT);
	for (pin_index=0; pin_index<pin_num; pin_index++) {
		if (pin_mask & BIT(pin_index))
			PAD_PullCtrl((GPIO_PORT_A<<5 |pin_index), GPIO_PuPd_NOPULL);
	}

	while(1) {
		for (i=0; i<LED_PATTERN_NUM; i++) {
			GPIO_PortWrite(GPIO_PORT_A, pin_mask, led_pattern[i]);
			DelayMs(1000);
		}
	}
}

#else

void main(void)
{
	int i, pin_index;
	unsigned int pin_mask;
	u32 pin_num = 32;
	int value_new, value_tmp, value_old;
	int stable;

	pin_mask = 0x20FF000;    // each bit map to 1 pin: 0: pin disable, 1: pin enable

	GPIO_PortDirection(GPIO_PORT_A, pin_mask, GPIO_Mode_IN);
	for (pin_index=0; pin_index<pin_num; pin_index++) {
		if (pin_mask & BIT(pin_index))
			PAD_PullCtrl((GPIO_PORT_A<<5 |pin_index), GPIO_PuPd_NOPULL);
	}
 
	value_old = GPIO_PortRead(GPIO_PORT_A, pin_mask);
	value_old &= pin_mask;
	while(1){
        // De-bonse
		value_new = GPIO_PortRead(GPIO_PORT_A, pin_mask);
		value_new &= pin_mask;
		
		stable = 0;
		while (stable < 3){
			value_tmp = GPIO_PortRead(GPIO_PORT_A, pin_mask); 
			value_tmp &= pin_mask;	
			if (value_new != value_tmp) {
				value_new = value_tmp;
				stable = 0;
			} else {
				stable++;
			}
		} 

		if (value_old != value_new) {
			DBG_8195A("0x%x\r\n", value_new);
			value_old = value_new;
		}
		DelayMs(50);
    }
}

#endif
