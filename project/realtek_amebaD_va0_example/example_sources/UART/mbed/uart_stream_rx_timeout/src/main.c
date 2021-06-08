/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "device.h"
#include "serial_api.h"
#include "serial_ex_api.h"
#include "task.h"
//#include "main.h"
 
//UART pin location:     
//KM4 UART0: 
//PA_18  (TX)
//PA_19  (RX)
 
#define UART_TX    PA_18	//UART0  TX
#define UART_RX    PA_19	//UART0  RX 

#define SRX_BUF_SZ 100

//SRAM_NOCACHE_DATA_SECTION
char rx_buf[SRX_BUF_SZ]={0};
volatile uint32_t tx_busy=0;
volatile uint32_t rx_done=0;

void uart_send_string_done(uint32_t id)
{
	serial_t    *sobj = (void*)id;
	tx_busy = 0;
}

void uart_send_string(serial_t *sobj, char *pstr)
{
	int32_t ret=0;

	if (tx_busy) {
		return;
	}

	tx_busy = 1;
	ret = serial_send_stream(sobj, pstr, _strlen(pstr));
	if (ret != 0) {
		DBG_8195A("%s Error(%d)\n", __FUNCTION__, ret);
		tx_busy = 0;
	}
}

void Release_CPU()
{
	// while waitting UART transfer done, try to wakeup other task
#if 1
	// make this task to sleep, so other task can wakeup
	vTaskDelay(10 / portTICK_RATE_MS);
#else
	 // force the OS scheduler to do a context switch, but if the
	// priority of this task is the highest then no other task can wake up
	taskYIELD();
#endif
}

void uart_test_demo(void *param)
{
	serial_t    sobj;
	int ret;

	serial_init(&sobj,UART_TX,UART_RX);
	serial_baud(&sobj,38400);
	serial_format(&sobj, 8, ParityNone, 1);

	serial_send_comp_handler(&sobj, (void*)uart_send_string_done, (uint32_t) &sobj);

	while (1) {
        // expect to receive maximum 13 bytes with timeout 1000ms
    #if 1
        // If you don't know what is Task Yield or no RTOS, then just keep the last argument is NULL
        ret = serial_recv_stream_timeout(&sobj, rx_buf, 13, 1000,(void *)Release_CPU );
    #else
        // Do Task Yield while waitting UART RX done
        ret = serial_recv_stream_timeout(&sobj, rx_buf, 13, 1000, Release_CPU);
    #endif
	
        if (ret < 100) {
		DBG_8195A("Serial Rcv Timeout, Got %d bytes\n", ret);
        }

        if (ret > 0) {
		rx_buf[ret] = 0x00; // end of string
		uart_send_string(&sobj, rx_buf);
        }
    }
}

void main(void)
{
	// create demo Task
	if(xTaskCreate( (TaskFunction_t)uart_test_demo, "uart test demo", (2048/2), (void *)NULL, (tskIDLE_PRIORITY + 1), NULL)!= pdPASS) {
		DBG_8195A("Cannot create uart test demo task\n\r");
		goto end_demo;
	}

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


