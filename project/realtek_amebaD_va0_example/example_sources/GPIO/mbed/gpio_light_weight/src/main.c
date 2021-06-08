/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "device.h"
#include "gpio_api.h"   // mbed
#include "main.h"

#define GPIO_LED_PIN       PB_5
#define GPIO_PUSHBT_PIN    PA_12

extern GPIO_TypeDef* PORT_AB[2];

/*  You can improve time cost of gpio write by import source code of
 *  function "gpio_direct_write" based on your needs.
 *  In this example, enable CACHE_WRITE_ACTION as demonstration.
 */
#define CACHE_WRITE_ACTION (0)

void main(void)
{
    gpio_t gpio_led;
    gpio_t gpio_btn;

    // Init LED control pin
    gpio_init(&gpio_led, GPIO_LED_PIN);
    gpio_dir(&gpio_led, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&gpio_led, PullNone);     // No pull

    // Initial Push Button pin
    gpio_init(&gpio_btn, GPIO_PUSHBT_PIN);
    gpio_dir(&gpio_btn, PIN_INPUT);     // Direction: Input
    gpio_mode(&gpio_btn, PullUp);       // Pull-High

#if defined(CACHE_WRITE_ACTION) && (CACHE_WRITE_ACTION == 1)
    u8 port_num = PORT_NUM(gpio_led.pin);
    u8 pin_num  = PIN_NUM(gpio_led.pin);
    u32 RegValue;
    GPIO_TypeDef* GPIO = PORT_AB[port_num];
#endif

    while(1){
#if defined(CACHE_WRITE_ACTION) && (CACHE_WRITE_ACTION == 1)
        if (gpio_read(&gpio_btn)) {
            // turn off LED
            RegValue =  GPIO->PORT[port_num].DR;
            RegValue &= ~(1 << pin_num);
            GPIO->PORT[port_num].DR = RegValue;
        } else {
            // turn on LED
            RegValue =  GPIO->PORT[port_num].DR;
            RegValue |= (1<< pin_num);
            GPIO->PORT[port_num].DR = RegValue;
        }
#else
        if (gpio_read(&gpio_btn)) {
            // turn off LED
            gpio_direct_write(&gpio_led, 0);
        } else {
            // turn on LED
            gpio_direct_write(&gpio_led, 1);
        }
#endif
    }
}

