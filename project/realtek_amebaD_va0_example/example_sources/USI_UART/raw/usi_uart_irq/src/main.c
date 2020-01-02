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
   KM4 USI UART: 
   PB_20  (TX)
   PB_21  (RX)
   */
#define UART_TX    _PB_20
#define UART_RX    _PB_21
#define USI_DEV        USI0_DEV

volatile char rc=0;
volatile int tx_flag=0;

void uart_send_string( char *pstr)
{
	unsigned int i=0;
	while (*(pstr+i) != 0) {
		while (!USI_UARTWritable(USI_DEV));
		USI_UARTCharPut(USI_DEV, *(pstr+i));
		i++;
	}
}

void uart_irq()
{
	u32 IntId;
	IntId = USI_UARTIntStatus(USI_DEV);
		
	if((IntId&USI_RXFIFO_ALMOST_FULL_INTS)||(IntId&USI_RXFIFO_TM_OUT_INTS)){
		while(!USI_UARTReadable(USI_DEV));
		USI_UARTCharGet(USI_DEV, &rc);
		USI_UARTCharPut(USI_DEV, rc);
		if(0!=tx_flag){
			USI_UARTINTConfig(USI_DEV,USI_TX_FIFO_ALMOST_EMPTY_INTER, ENABLE);
		}
		DelayUs(1000);
	}
	if((IntId&USI_TXFIFO_ALMOST_EMTY_INTS)){
		if(rc!=0){
			uart_send_string("\r\n8195a$");
			rc=0;
			USI_UARTINTConfig(USI_DEV,USI_TX_FIFO_ALMOST_EMPTY_INTER, DISABLE);
		}else{
			USI_UARTINTConfig(USI_DEV,USI_TX_FIFO_ALMOST_EMPTY_INTER, DISABLE);
			}
	}
}

void main(void)
{
	USI_UARTInitTypeDef USI_UARTInitStruct;
	int usi_uart_index;
	usi_uart_index=0;
	u32 LineSts=0;

	//config pin*/
	Pinmux_Config(UART_TX, PINMUX_FUNCTION_UART);
	Pinmux_Config(UART_RX, PINMUX_FUNCTION_UART);
	PAD_PullCtrl(UART_TX, GPIO_PuPd_UP);   //Tx/Rx pin should pull up
	PAD_PullCtrl(UART_RX, GPIO_PuPd_UP);

	RCC_PeriphClockCmd(APBPeriph_USI_REG, APBPeriph_USI_CLOCK, ENABLE);
	
	USI_UARTStructInit(&USI_UARTInitStruct);
	USI_UARTInitStruct.USI_UARTParity=USI_RUART_PARITY_DISABLE;
	USI_UARTInitStruct.USI_UARTRxFifoTrigLevel=1;
	USI_UARTInit(USI_DEV, &USI_UARTInitStruct);
	USI_UARTSetBaud(USI_DEV, 38400);
	USI_UARTRxCmd(USI_DEV, ENABLE);

	uart_send_string("UART IRQ API Demo...\r\n");
	uart_send_string("Hello World!!\n");
	uart_send_string("\r\n8195a$");
	
	InterruptRegister((IRQ_FUN)uart_irq, USI_DEV_TABLE[usi_uart_index].IrqNum, USI_DEV, 10);
	InterruptEn(USI_DEV_TABLE[usi_uart_index].IrqNum, 10);
	LineSts = USI_TX_FIFO_OVERFLOW_INTER | USI_RX_FIFO_OVERFLOW_INTER | USI_UART_PARITY_ERROR_INTER | USI_UART_STOP_ERROR_INTER;
	USI_UARTINTConfig(USI_DEV, USI_TX_FIFO_ALMOST_EMPTY_INTER|USI_RX_FIFO_ALMOST_FULL_INTER | USI_RX_FIFO_TIMEOUT_INTER|LineSts, ENABLE);
	tx_flag=1;

	while(1);
}




