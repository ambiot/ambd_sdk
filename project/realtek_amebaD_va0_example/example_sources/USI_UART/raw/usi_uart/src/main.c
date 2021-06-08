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
#include "rtl8721d_usi_uart.h"

/*UART pin location:     
   KM4 USI-UART: 
   PB_20  (TX)
   PB_21  (RX)
   */
#define UART_TX    _PB_20
#define UART_RX    _PB_21
#define USI_DEV   USI0_DEV  //choose usi uart 

USI_UARTInitTypeDef	USI_UARTInitStruct;

void usi_uart_send_string( char *pstr)
{
	unsigned int i=0;
	while (*(pstr+i) != 0) {
		while (!USI_UARTWritable(USI_DEV));
		USI_UARTCharPut(USI_DEV, *(pstr+i));
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
	
	USI_UARTStructInit(&USI_UARTInitStruct);
	USI_UARTInitStruct.USI_UARTParity=USI_RUART_PARITY_DISABLE;
	USI_UARTInit(USI_DEV, &USI_UARTInitStruct);
	USI_UARTSetBaud(USI_DEV, 38400);
	USI_UARTRxCmd(USI_DEV, ENABLE);

	usi_uart_send_string( "\n\rUART API Demo...\r\n");
	usi_uart_send_string( "Hello World!!\r\n");

	while(1){
		usi_uart_send_string("\r\n8195a$");
		while(!USI_UARTReadable(USI_DEV));
		USI_UARTCharGet(USI_DEV, &rc);

		while(!USI_UARTWritable(USI_DEV));
		USI_UARTCharPut(USI_DEV, rc);
    }
}

