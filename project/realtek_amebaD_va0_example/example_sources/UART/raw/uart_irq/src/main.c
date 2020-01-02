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
#include "main.h"

/*UART pin location:     
   KM4 UART0: 
   PA_18  (TX)
   PA_19  (RX)
   */
#define UART_TX    _PA_18
#define UART_RX    _PA_19
#define UART_DEV  UART0_DEV

volatile char rc=0;
volatile int tx_flag=0;

u32 uart_get_idx(UART_TypeDef* UartDEV)
{
	if(UartDEV==UART0_DEV){
		return 0;
    	}else if(UartDEV==UART1_DEV){
		return 1;
    	}else if(UartDEV==UART2_DEV){
		return 2;
    	}else {
		return 3;
    	}
}

void uart_send_string( char *pstr)
{
	unsigned int i=0;
	while (*(pstr+i) != 0) {
		while (!UART_Writable(UART_DEV));
		UART_CharPut(UART_DEV, *(pstr+i));
		i++;
	}
}

void uart_irq()
{
	int IntId;
	IntId= ((UART_IntStatus(UART_DEV))&RUART_IIR_INT_ID)>>1;
	if(IntId==RUART_RECEIVER_DATA_AVAILABLE||IntId==RUART_TIME_OUT_INDICATION){
		while(!UART_Readable(UART_DEV));
		UART_CharGet(UART_DEV, &rc);
		UART_CharPut(UART_DEV, rc);
		if(0!=tx_flag){
			UART_INTConfig(UART_DEV,RUART_IER_ETBEI, ENABLE);
		}
		DelayUs(1000);
	}
	if(IntId==RUART_TX_FIFO_EMPTY){
		if(rc!=0){
			uart_send_string("\r\n8195a$");
			rc=0;
			UART_INTConfig(UART_DEV,RUART_IER_ETBEI, DISABLE);
		}else{
			UART_INTConfig(UART_DEV,RUART_IER_ETBEI, DISABLE);
			}
	}
}

void main(void)
{
	UART_InitTypeDef  UART_InitStruct;
	int uart_index;
	uart_index=uart_get_idx(UART_DEV);

	//config pin*/
	Pinmux_Config(UART_TX, PINMUX_FUNCTION_UART);
	Pinmux_Config(UART_RX, PINMUX_FUNCTION_UART);
	PAD_PullCtrl(UART_TX, GPIO_PuPd_UP);   //Tx/Rx pin should pull up
	PAD_PullCtrl(UART_RX, GPIO_PuPd_UP);

	RCC_PeriphClockCmd(APBPeriph_UART0, APBPeriph_UART0_CLOCK, ENABLE);
	
	UART_StructInit(&UART_InitStruct);
	UART_InitStruct.Parity=RUART_PARITY_DISABLE;
	UART_Init(UART_DEV, &UART_InitStruct);
	UART_SetBaud(UART_DEV, 38400);
	UART_RxCmd(UART_DEV, ENABLE);

	uart_send_string("UART IRQ API Demo...\r\n");
	uart_send_string("Hello World!!\n");
	uart_send_string("\r\n8195a$");
	
	InterruptRegister((IRQ_FUN)uart_irq, UART_DEV_TABLE[uart_index].IrqNum, UART_DEV, 10);
	InterruptEn(UART_DEV_TABLE[uart_index].IrqNum, 10);
	UART_INTConfig(UART_DEV, RUART_IER_ERBI | RUART_IER_ELSI | RUART_IER_ETOI, ENABLE);
	tx_flag=1;

	while(1);
}




