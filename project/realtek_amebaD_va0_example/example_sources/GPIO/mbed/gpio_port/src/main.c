/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "device.h"
#include "port_api.h"   // mbed
#include "PortNames.h"   // mbed
#include "main.h"
#include "sys_api.h" 

#define PORT_OUTPUT_TEST    1   //1: output test, 0: input test

#define LED_PATTERN_NUM     12

port_t port0;
const uint32_t led_pattern[LED_PATTERN_NUM]={0x20FF000, 0x20FE000, 0x20FD000, 0x20FB000, 0x20F7000, 0x20EF000, 0x20DF000, 0x20BF000, 0x207F000, 0x00FF000, 0x20FF000, 0x0000000};

extern void wait_ms(u32);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
#if PORT_OUTPUT_TEST

void main(void)
{
    int i;
    unsigned int pin_mask;

    pin_mask = 0x20FF000;    // each bit map to 1 pin: 0: pin disable, 1: pin enable
    port_init(&port0, PortA, pin_mask, PIN_OUTPUT);
	port_mode(&port0, PullNone);

    while(1){
        for (i=0;i<LED_PATTERN_NUM;i++) {
            port_write(&port0, led_pattern[i]);
            wait_ms(1000);
        }
    }
}

#else

void main(void)
{
    int i;
    unsigned int pin_mask;
    int value_new, value_tmp, value_old;
    int stable;

    pin_mask = 0x20FF000;    // each bit map to 1 pin: 0: pin disable, 1: pin enable
    port_init(&port0, PortA, pin_mask, PIN_INPUT);
	port_mode(&port0, PullNone);

    value_old = port_read(&port0); 
    while(1){
        // De-bonse
        value_new = port_read(&port0); 
        stable = 0;
        while (stable < 3){
            value_tmp = port_read(&port0); 
            if (value_new != value_tmp) {
                value_new = value_tmp;
                stable = 0;
            }
            else {
                stable++;
            }
        } 

        if (value_old != value_new) {
            DBG_8195A("0x%x\r\n", value_new);
            value_old = value_new;
        }
        wait_ms(50);
    }
}

#endif
