/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

// This example demo the function of Auto Flow control
// Please connect 2 board to run this example.
// Board1   <----->    Board2
// PA18      <----->     PA19
// PA19      <----->     PA18
// PA16      <----->     PA17
// PA17      <----->     PA16
// GND      <----->     GND

// The first started board will be the TX side, the other one will be the RX side
// The RX side will make some delay every 16-bytes received, 
// by this way we can trigger the flow control mechanism.

#include "device.h"

#include "main.h"

#define UART_TX    	_PA_18	//UART0  TX
#define UART_RX    	_PA_19	//UART0  RX
#define UART_RTS  	_PA_16	//UART0  RTS
#define UART_CTS   	_PA_17	//UART0  CTS
#define UART_DEV        UART0_DEV

#define UART_BUF_SIZE   1000
unsigned char buffer[UART_BUF_SIZE];

UART_InitTypeDef  UART_InitStruct;

void main(void)
{
	char rc;
	int i,j;
	int rx_side=0;

	//config pin*/
	Pinmux_Config(UART_TX, PINMUX_FUNCTION_UART);
	Pinmux_Config(UART_RX, PINMUX_FUNCTION_UART);
	PAD_PullCtrl(UART_TX, GPIO_PuPd_UP);   //Tx/Rx pin should pull up
	PAD_PullCtrl(UART_RX, GPIO_PuPd_UP);
    
	/*set peripheral clock and IP clock*/
	RCC_PeriphClockCmd(APBPeriph_UART0, APBPeriph_UART0_CLOCK, ENABLE);
    
	UART_StructInit(&UART_InitStruct);
	UART_InitStruct.Parity=RUART_PARITY_DISABLE;
	//enable auto flow control but not config rts/cts
	UART_InitStruct.FlowControl=ENABLE;
	UART_Init(UART_DEV, &UART_InitStruct);
	UART_SetBaud(UART_DEV, 38400);
	UART_RxCmd(UART_DEV, ENABLE);

	for (i=0;i<128;i++) {
		// Tide Break
		DBG_8195A("Wait peer ready...\r\n");
		UART_CharPut(UART_DEV, i+1);
		if (UART_Readable( UART_DEV)) {
			UART_CharGet(UART_DEV,&rc);
			if (rc > i) {
				rx_side = 1;
			} else {
				rx_side = 0;
			}
			break;
		}
		DelayMs(100);
	}
	UART_ClearRxFifo(UART_DEV);
	// config rts/cts to enable auto flow control 
	Pinmux_Config(_PA_16, PINMUX_FUNCTION_UART_RTSCTS); 	/*RTS*/
	Pinmux_Config(_PA_17, PINMUX_FUNCTION_UART_RTSCTS); 	/*CTS*/

	if (rx_side) {
		DBG_8195A("UART Flow Control: RX ==>\r\n");
		_memset(buffer, 0, UART_BUF_SIZE);	
		i = 0;
		j = 0;
		while (1) {
			if (UART_Readable(UART_DEV)) {
				UART_CharGet(UART_DEV, buffer+i);
				i++;
				if (i == UART_BUF_SIZE) {
                   			 break;
                		}
				if ((i&0xf) == 0) {
					// Make some delay to cause the RX FIFO full and then trigger flow controll
					DelayMs(100);
                    			DBG_8195A("UART RX got %d bytes\r\n", i);
                		}
				j=0;
			} else {
				DelayMs(10);
				j++;
				if (j== 1000) {
					DBG_8195A("UART RX Failed, Got %d bytes\r\n", i);
					break;
				}
			}            
		}
	} else {
		DBG_8195A("UART Flow Control: TX ==>\r\n");
		DelayMs(400);
		/*send large number to make peer device be rx side */
		UART_CharPut(UART_DEV, 255);
		DelayMs(100);
        
		for (i=0;i<UART_BUF_SIZE;i++) {
			buffer[i] =0x30 + (i%10);
		}
        
		for (i=0;i<UART_BUF_SIZE;i++) {
			while(!UART_Writable(UART_DEV));
			UART_CharPut(UART_DEV, buffer[i]);
		}
	}
	DBG_8195A("UART Flow Control Test Done!\r\n");
	while (1);
}

