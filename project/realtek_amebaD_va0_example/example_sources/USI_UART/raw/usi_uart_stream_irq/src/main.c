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
#include "main.h"

/*UART pin location:     
   KM4 USI UART: 
   PB_20  (TX)
   PB_21  (RX)
   */
#define UART_TX    _PB_20	//UART  TX
#define UART_RX    _PB_21	//UART  RX

#define USI_DEV        USI0_DEV
#define SRX_BUF_SZ 16

char rx_buf[SRX_BUF_SZ]={0};
volatile uint32_t tx_busy=0;
volatile uint32_t rx_done=0;

typedef struct
{
	USI_UARTInitTypeDef	USI_UARTInitStruct;
	int	TxCount;     // how many byte to TX
	int	RxCount;     // how many bytes to RX
	u8	*pTxBuf;
	u8	*pRxBuf;
	u8	UartIndex;
}UART_OBJ;

void uart_send_string_done()
{
	tx_busy = 0;
	USI_UARTINTConfig(USI_DEV, USI_TX_FIFO_ALMOST_EMPTY_INTER, DISABLE);
}

void uart_recv_string_done()
{
	rx_done = 1;
	USI_UARTINTConfig(USI_DEV, USI_RX_FIFO_ALMOST_FULL_INTER|USI_RX_FIFO_TIMEOUT_INTER, DISABLE);
}

u32 uart_irq(IN VOID *data)
{
	UART_OBJ *uart_obj=(UART_OBJ*) data;
	u32 IntId;
	volatile u8 reg_iir;
	int cnt=16;
	u32 TransCnt = 0;
	
	IntId = USI_UARTIntStatus(USI_DEV);

	if((IntId&USI_TXFIFO_ALMOST_EMTY_INTS)) {
		while(cnt>0&&uart_obj->TxCount>0){
			USI_UARTCharPut(USI_DEV, *uart_obj->pTxBuf);
			uart_obj->TxCount --;
			uart_obj->pTxBuf ++;
			cnt--;
		}
		if(0==uart_obj->TxCount){
			uart_send_string_done();
		}
	} else if ((IntId&USI_RXFIFO_ALMOST_FULL_INTS)||(IntId&USI_RXFIFO_TM_OUT_INTS)) {
		TransCnt=USI_UARTReceiveDataTO(USI_DEV, 
				uart_obj->pRxBuf, uart_obj->RxCount, 1);
		uart_obj->RxCount -= TransCnt;
		uart_obj->pRxBuf += TransCnt;
		if(0==uart_obj->RxCount){
			uart_recv_string_done();
		}
	} else {
		DiagPrintf("interrupt id=%d\n",IntId);
	}

	return 0;
}

void uart_int_send(UART_OBJ *uart_obj, char *pstr,u32 len)
{
	uart_obj->pTxBuf=pstr;
	uart_obj->TxCount=len;
	USI_UARTINTConfig(USI_DEV, USI_TX_FIFO_ALMOST_EMPTY_INTER, ENABLE);
}

void uart_int_recv(UART_OBJ * uart_obj, char*pstr,u32 len)
{  
	uart_obj->pRxBuf=pstr;
	uart_obj->RxCount=len;
	USI_UARTINTConfig(USI_DEV, USI_RX_FIFO_ALMOST_FULL_INTER|USI_RX_FIFO_TIMEOUT_INTER, ENABLE);
}

void uart_send_string(UART_OBJ * uart_obj,char* pstr)
{
	if (tx_busy) {
		return;
	}
	tx_busy = 1;
	uart_int_send(uart_obj, pstr, _strlen(pstr));
}

void main(void)
{
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
	USI_UARTInit(USI_DEV, &uart_obj.USI_UARTInitStruct);
	USI_UARTSetBaud(USI_DEV,38400);
	USI_UARTRxCmd(USI_DEV, ENABLE);

	InterruptRegister((IRQ_FUN)uart_irq, USI_DEV_TABLE[uart_obj.UartIndex].IrqNum, (u32)&uart_obj, 10);
	InterruptEn(USI_DEV_TABLE[uart_obj.UartIndex].IrqNum, 10);

	uart_int_recv(&uart_obj,rx_buf,8);

	while (1) {

#if 0
		if (!tx_busy) {
			uart_send_string(uart_obj, "Hello! World!! :) \r\n");
		}
#endif
		if (rx_done) {
			uart_send_string(&uart_obj,rx_buf);            
			rx_done = 0;
			uart_int_recv(&uart_obj,rx_buf,8);
		}
	}
}


