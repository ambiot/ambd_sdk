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
//KM4 UART0
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
#include "serial_api.h"
#include "serial_ex_api.h"
#include "main.h"

#define UART_TX    	_PA_18	//UART0  TX
#define UART_RX    	_PA_19	//UART0  RX
#define UART_RTS  	_PA_16	//UART0  RTS
#define UART_CTS   	_PA_17	//UART0  CTS

#define UART_BUF_SIZE   1000
unsigned char buffer[UART_BUF_SIZE];
serial_t sobj;

void uart_send_string(serial_t *sobj, char *pstr)
{
	unsigned int i=0;
	while (*(pstr+i) != 0) {
		serial_putc(sobj, *(pstr+i));
		i++;
	}
}

void main(void)
{
	// sample text
	char rc;
	int i,j;
	int rx_side=0;

	/*UART0  used*/
	sobj.uart_idx = 0;

	// mbed uart test
	//pin_mode(UART_RX, PullUp); 
	serial_init(&sobj,UART_TX,UART_RX);
	serial_baud(&sobj,38400);
	serial_format(&sobj, 8, ParityNone, 1);
	serial_rx_fifo_level(&sobj, FifoLvHalf);
	serial_set_flow_control(&sobj, FlowControlNone, 0, 0);    // Pin assignment can be ignored when autoflow control function is disabled
	DBG_8195A("CHANGE");
	for (i=0;i<1000;i++) {
		// Tide Break
		DBG_8195A("Wait peer ready...\r\n");
		serial_putc(&sobj, i+1);
		if (serial_readable(&sobj)) {
			rc = (int)serial_getc(&sobj);
			if (rc > i) {
				rx_side = 1;
			} else {
				rx_side = 0;
			}
			break;
		}
		DelayMs(100);
	}

	serial_clear_rx(&sobj);
	// Enable flow control 
	serial_set_flow_control(&sobj, FlowControlRTSCTS, UART_RTS, UART_CTS);    // Pin assignment is ignored

	if (rx_side) {
		DBG_8195A("UART Flow Control: RX ==>\r\n");
		_memset(buffer, 0, UART_BUF_SIZE);
		i = 0;
		j = 0;
		while (1) {
			if (serial_readable(&sobj)) {
				buffer[i] = serial_getc(&sobj);
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
		DelayMs(500);
		serial_putc(&sobj, 255);
		DelayMs(500);

		for (i=0;i<UART_BUF_SIZE;i++) {
			buffer[i] = 0x30 + (i%10);
		}
		for (i=0;i<UART_BUF_SIZE;i++) {
			serial_putc(&sobj, buffer[i]);
		}
	}
	DBG_8195A("UART Flow Control Test Done!\r\n");
	while (1);
}

