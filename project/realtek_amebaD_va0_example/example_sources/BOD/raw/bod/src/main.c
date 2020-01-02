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

#define BOD_INTR_MODE

static void bod_irq_handler(void)
{
	BOR_ClearINT();
	DBG_8195A("BOD_INTR\n");
}

void bod_intr_test(void)
{
	/*clear pending bod interrupt*/
	BOR_ClearINT();

	/*register BOD interrupt handler*/
	InterruptRegister(bod_irq_handler, BOR2_IRQ_LP, NULL, 10);
	InterruptEn(BOR2_IRQ_LP, 10);

	BOR_ThresholdSet(BOR_TH_LOW6, BOR_TH_HIGH7);
	BOR_ModeSet(BOR_INTR, ENABLE);

	DBG_8195A("Supply 2.5V voltage will cause bod interrupt!!!\n");

	vTaskDelete(NULL);
}

void bod_reset_test(void)
{
	BOR_ThresholdSet(BOR_TH_LOW6, BOR_TH_HIGH7);
	BOR_ModeSet(BOR_RESET, ENABLE);

	DBG_8195A("Supply 2.1V voltage and then recover voltage to above 2.5V will cause bod reset!!!\n");

	vTaskDelete(NULL);
}

void main(void)
{
	// create demo Task
#ifdef BOD_INTR_MODE
	if(xTaskCreate( (TaskFunction_t)bod_intr_test, "BOD DEMO", (2048/4), NULL, (tskIDLE_PRIORITY + 1), NULL)!= pdPASS) {
		DBG_8195A("Cannot create bod interrupt demo task\n\r");
		goto end_demo;
	}
#else
	if(xTaskCreate( (TaskFunction_t)bod_reset_test, "BOD DEMO", (2048/4), NULL, (tskIDLE_PRIORITY + 1), NULL)!= pdPASS) {
		DBG_8195A("Cannot create bod reset demo task\n\r");
		goto end_demo;
	}
#endif

#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
	#ifdef PLATFORM_FREERTOS
	vTaskStartScheduler();
	#endif
#else
	#error !!!Need FREERTOS!!!
#endif

end_demo:	
	while(1);
}
