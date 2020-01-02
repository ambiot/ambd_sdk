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
#include "gpio_irq_api.h"   // mbed
#include "diag.h"
#include "us_ticker_api.h"
#include "main.h"

#define GPIO_OUT_PIN        PB_5
#define GPIO_IRQ_PIN        PA_12

gpio_t gpio_out;
gpio_irq_t gpio_irq;
volatile char irq_rise;


void gpio_demo_irq_handler (uint32_t id, gpio_irq_event event)
{
    static unsigned int rise_time;
    static unsigned int fall_time;

    if (irq_rise) {
        rise_time = us_ticker_read();
        // Changed as Falling Edge Trigger
        gpio_irq_set_event(&gpio_irq, IRQ_FALL);
        irq_rise = 0;
    } else {
        fall_time = us_ticker_read();
        // Changed as Rising Edge Trigger
        gpio_irq_set_event(&gpio_irq, IRQ_RISE);
        irq_rise = 1;

        DBG_8195A("%d\n", (fall_time-rise_time));
    }
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{

    // Init LED control pin
    gpio_init(&gpio_out, GPIO_OUT_PIN);
    gpio_dir(&gpio_out, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&gpio_out, PullNone);     // No pull
    gpio_write(&gpio_out, 0);

    // Initial Push Button pin as interrupt source
    gpio_irq_init(&gpio_irq, GPIO_IRQ_PIN, gpio_demo_irq_handler, (uint32_t)(&gpio_irq));
    gpio_irq_set(&gpio_irq, IRQ_RISE, 1);   // Falling Edge Trigger
    irq_rise = 1;
    gpio_irq_pull_ctrl(&gpio_irq, PullNone);
    gpio_irq_enable(&gpio_irq);

    while(1) {
        wait_ms(500);
        gpio_write(&gpio_out, 1);
        wait_us(1000);
        gpio_write(&gpio_out, 0);
    }
}

