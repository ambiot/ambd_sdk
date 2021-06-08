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
 
/*UART pin location:     
   USI UART: 
   PB_20  (TX)
   PB_21  (RX)
   */
#define UART_TX    PB_20//UART  TX
#define UART_RX    PB_21	//UART  RX 
#define USI_DEV        USI0_DEV
#define SRX_BUF_SZ 	100

char rx_buf[SRX_BUF_SZ]={0};
volatile uint32_t tx_busy=0;
volatile uint32_t rx_done=0;

typedef struct
{
	USI_UARTInitTypeDef USI_UARTInitStruct;
	int TxCount;
	int RxCount;
	u8 *pTxBuf;
	u8 *pRxBuf;
	u8  UartIndex;
}UART_OBJ;

void uart_send_string_done()
{
	tx_busy = 0;
	USI_UARTINTConfig(USI0_DEV, USI_TX_FIFO_ALMOST_EMPTY_INTER, DISABLE);
}

void uart_recv_string_done()
{
	rx_done = 1;
	USI_UARTINTConfig(USI0_DEV, USI_RX_FIFO_ALMOST_FULL_INTER|USI_RX_FIFO_TIMEOUT_INTER, DISABLE);
}

u32 uart_irq(IN VOID *data)
{
	UART_OBJ *uart_obj=(UART_OBJ*) data;
	int IntId;
	IntId= USI_UARTIntStatus(USI0_DEV);
	USI_UARTClearAllIntStatus(USI0_DEV);
	
	if((IntId&USI_TXFIFO_ALMOST_EMTY_INTS)){
		u32 TransCnt=USI_UARTSendDataTO(USI0_DEV, 
				uart_obj->pTxBuf, uart_obj->TxCount, 1);
		uart_obj->TxCount -= TransCnt;
		uart_obj->pTxBuf += TransCnt;
 		if(0==uart_obj->TxCount) {
 			uart_send_string_done();
 		}
	}
	else if((IntId&USI_RXFIFO_ALMOST_FULL_INTS)||(IntId&USI_RXFIFO_TM_OUT_INTS)){
		u32 TransCnt=USI_UARTReceiveDataTO(USI0_DEV, 
				uart_obj->pRxBuf, uart_obj->RxCount, 1);
		uart_obj->RxCount -= TransCnt;
		uart_obj->pRxBuf += TransCnt;
		if(0==uart_obj->RxCount){
			uart_recv_string_done();
		}
	}
	else{}
	return 0;
}
void uart_int_send(UART_OBJ *uart_obj, char *pstr,u32 len)
{
	uart_obj->pTxBuf=pstr;
	uart_obj->TxCount=len;
	USI_UARTINTConfig(USI0_DEV, USI_TX_FIFO_ALMOST_EMPTY_INTER, ENABLE);
}

u32 uart_int_recv(UART_OBJ * uart_obj, char*pstr,u32 len,u32 timeout_ms,void *force_cs)
{  
	rx_done=0;
	u32 startcount=SYSTIMER_TickGet();
	void (*task_yield) (void);
	uart_obj->pRxBuf=pstr;
	uart_obj->RxCount=len;
	USI_UARTINTConfig(USI0_DEV, USI_RX_FIFO_ALMOST_FULL_INTER|USI_RX_FIFO_TIMEOUT_INTER, ENABLE);
	if(uart_obj->RxCount>0){
		task_yield=(void(*)(void)) force_cs;
		while(1){
			if(rx_done!=1){
				/*time out*/
				if(SYSTIMER_GetPassTime(startcount)>timeout_ms){
					USI_UARTINTConfig(USI0_DEV, USI_RX_FIFO_ALMOST_FULL_INTER|USI_RX_FIFO_TIMEOUT_INTER, DISABLE);
					USI_UARTClearRxFifo(USI0_DEV);
					break;
				}
				if(NULL!=task_yield){
					task_yield();
				}
			}else{
				break;
			}
		}
	}
	return( len - uart_obj->RxCount);
}

void uart_send_string(UART_OBJ * uart_obj,char* pstr)
{
	if (tx_busy) {
		return;
		}
		tx_busy = 1;
		uart_int_send(uart_obj, pstr, _strlen(pstr));
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
	int ret;
	UART_OBJ uart_obj;
	uart_obj.UartIndex=0;
	uart_obj.RxCount=0;
	uart_obj.TxCount=0;
	
	//config pin*/
	Pinmux_Config(UART_TX, PINMUX_FUNCTION_UART);
	Pinmux_Config(UART_RX, PINMUX_FUNCTION_UART);
	PAD_PullCtrl(UART_TX, GPIO_PuPd_UP);   //Tx/Rx pin should pull up
	PAD_PullCtrl(UART_RX, GPIO_PuPd_UP);

	RCC_PeriphClockCmd(APBPeriph_USI_REG, APBPeriph_USI_CLOCK, ENABLE);

	USI_UARTStructInit(&uart_obj.USI_UARTInitStruct);
	uart_obj.USI_UARTInitStruct.USI_UARTParity=USI_RUART_PARITY_DISABLE;
	uart_obj.USI_UARTInitStruct.USI_UARTRxFifoTrigLevel=1;
	USI_UARTInit(USI0_DEV, &uart_obj.USI_UARTInitStruct);
	USI_UARTSetBaud(USI0_DEV,38400);
	USI_UARTRxCmd(USI0_DEV, ENABLE);

	InterruptRegister((IRQ_FUN)uart_irq, USI_DEV_TABLE[uart_obj.UartIndex].IrqNum, (u32)&uart_obj, 10);
	InterruptEn(USI_DEV_TABLE[uart_obj.UartIndex].IrqNum, 10);

	while (1) {
        // expect to receive maximum 13 bytes with timeout 1000ms
        // If you don't know what is Task Yield or no RTOS, then just keep the last argument is NULL
        	ret = uart_int_recv(&uart_obj, rx_buf, 13, 1000,(void *)Release_CPU );

		if (ret < 13) {
			DBG_8195A("Serial Rcv Timeout, Got %d bytes\n", ret);
		}else if(ret==13){
			DBG_8195A("Recv all 13 Bytes");
		}else{
			DBG_8195A("!!!!!!!!!!!!!!!!!!Recv: %d\n", ret);
			vTaskDelay(1000);
		}

		if (ret > 0) {
			DBG_8195A("send received strings: \n");
			rx_buf[ret] = 0x00; // end of string
			uart_send_string(&uart_obj, rx_buf);
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


