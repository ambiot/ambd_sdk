/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */


#include "device.h"
#include "ameba_soc.h"
#include "rtl8721d_uart.h"

/*UART pin location:     
   KM4 UART0: 
   PA_18  (TX)
   PA_19  (RX)
   */
#define UART_TX    _PA_18
#define UART_RX    _PA_19
#define UART_DEV   UART0_DEV  //choose uart 

UART_InitTypeDef  UART_InitStruct;

void uart_send_string( char *pstr)
{
	unsigned int i=0;
	while (*(pstr+i) != 0) {
		while (!UART_Writable(UART_DEV));
		UART_CharPut(UART_DEV, *(pstr+i));
      		  i++;
	}
}

void main(void)
{
	char rc='0';
	
	/*config pin*/
	Pinmux_Config(UART_TX, PINMUX_FUNCTION_UART);
	Pinmux_Config(UART_RX, PINMUX_FUNCTION_UART);
	PAD_PullCtrl(UART_TX, GPIO_PuPd_UP);   //Tx/Rx pin should pull up
	PAD_PullCtrl(UART_RX, GPIO_PuPd_UP);
	
	/*choose clock source*/
	RCC_PeriphClockSource_UART(UART_DEV, UART_RX_CLK_XTAL_40M);
	
	UART_StructInit(&UART_InitStruct);
	UART_InitStruct.Parity=RUART_PARITY_DISABLE;
	UART_Init(UART_DEV, &UART_InitStruct);
	UART_SetBaud(UART_DEV, 38400);
	UART_RxCmd(UART_DEV, ENABLE);

	uart_send_string( "UART API Demo...\r\n");
	uart_send_string( "Hello World!!\r\n");

	while(1){
		uart_send_string("\r\n8195a$");
		while(!UART_Readable(UART_DEV));
		UART_CharGet(UART_DEV, &rc);

		while(!UART_Writable(UART_DEV));
		UART_CharPut(UART_DEV, rc);
    }
}

