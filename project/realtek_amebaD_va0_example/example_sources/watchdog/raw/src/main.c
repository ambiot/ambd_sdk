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

#include "wdt_api.h"

#define RUN_CALLBACK_IF_WATCHDOG_BARKS (0)
#define printf	DBG_8195A

void dummy_task() {
    int i=0;
    for (i=0; i<50000000; i++)
        asm(" nop");
}

void small_task() {
    printf("\r\ndoing small task...\r\n");
    dummy_task();
    printf("refresh watchdog\r\n\r\n");
    WDG_Refresh();
}

void big_task() {
   int i=0;
   printf("\r\ndoing big task...\r\n");
    for (i=0; i<10; i++) {
        DiagPrintf("doing dummy task %d\r\n", i);
        dummy_task();
    }
    printf("refresh watchdog\r\n\r\n");
    WDG_Refresh();
}

void my_watchdog_irq_handler(uint32_t id) {
    printf("watchdog barks!!!\r\n");
    WDG_Cmd(DISABLE);
}

void main(void) {
    WDG_InitTypeDef WDG_InitStruct;
    u32 CountProcess;
    u32 DivFacProcess;

    WDG_Scalar(5000, &CountProcess, &DivFacProcess);

    WDG_InitStruct.CountProcess = CountProcess;
    WDG_InitStruct.DivFacProcess = DivFacProcess;

    WDG_Init(&WDG_InitStruct);

 #if RUN_CALLBACK_IF_WATCHDOG_BARKS
    WDG_IrqInit(my_watchdog_irq_handler, 0);
 #else
    // system would restart when watchdog barks
 #endif

    WDG_Cmd(ENABLE);

    small_task();
    big_task();

    while(1);
}
