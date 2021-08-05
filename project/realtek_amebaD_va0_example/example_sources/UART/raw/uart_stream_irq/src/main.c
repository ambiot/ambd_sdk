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
   KM4 UART0: 
   PA_18  (TX)
   PA_19  (RX)
   */
#define UART_TX    _PA_18	//UART0  TX
#define UART_RX    _PA_19	//UART0  RX
#define UART_DEV  UART0_DEV

#define SRX_BUF_SZ 16

char rx_buf[SRX_BUF_SZ]={0};
volatile uint32_t tx_busy=0;
volatile uint32_t rx_done=0;

typedef struct
{
	UART_InitTypeDef  UART_InitStruct;
	int	TxCount;     // how many byte to TX
	int	RxCount;     // how many bytes to RX
	u8	*pTxBuf;
	u8	*pRxBuf;
	u8	UartIndex;
}UART_OBJ;


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

void uart_send_string_done()
{
	tx_busy = 0;
	UART_INTConfig(UART_DEV, RUART_IER_ETBEI, DISABLE);
}

void uart_recv_string_done()
{
	rx_done = 1;
	UART_INTConfig(UART_DEV, RUART_IER_ERBI|RUART_IER_ETOI, DISABLE);
}

u32 uart_irq(IN VOID *data)
{
	UART_OBJ *uart_obj=(UART_OBJ*) data;
	int IntId;
	volatile u8 reg_iir;
	int cnt=16;
	u32 TransCnt = 0;
	
	reg_iir = UART_IntStatus(UART_DEV);
	IntId= (reg_iir&RUART_IIR_INT_ID)>>1;
	
	if ((reg_iir & RUART_IIR_INT_PEND) != 0) {
		// No pending IRQ
		return 0;
	}

	switch(IntId){
		
	case RUART_TX_FIFO_EMPTY:
		while(cnt>0&&uart_obj->TxCount>0){
			UART_CharPut(UART_DEV, *uart_obj->pTxBuf);
			uart_obj->TxCount --;
			uart_obj->pTxBuf ++;
			cnt--;
		}
		if(0==uart_obj->TxCount){
			uart_send_string_done();
		}
	break;
	
	case RUART_RECEIVER_DATA_AVAILABLE:
	case RUART_TIME_OUT_INDICATION:
		TransCnt=UART_ReceiveDataTO(UART_DEV, 
				uart_obj->pRxBuf, uart_obj->RxCount, 1);
		uart_obj->RxCount -= TransCnt;
		uart_obj->pRxBuf += TransCnt;
		if(0==uart_obj->RxCount){
			uart_recv_string_done();
		}
	break;

	default:
		DiagPrintf("interrupt id=%d\n",IntId);
	}
	return 0;
}

void uart_int_send(UART_OBJ *uart_obj, char *pstr,u32 len)
{
	uart_obj->pTxBuf=pstr;
	uart_obj->TxCount=len;
	UART_INTConfig(UART_DEV, RUART_IER_ETBEI, ENABLE);
}

void uart_int_recv(UART_OBJ * uart_obj, char*pstr,u32 len)
{  
	uart_obj->pRxBuf=pstr;
	uart_obj->RxCount=len;
	UART_INTConfig(UART_DEV, RUART_IER_ERBI|RUART_IER_ETOI, ENABLE);
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
	uart_obj.UartIndex=uart_get_idx(UART_DEV);
	uart_obj.RxCount=0;
	uart_obj.TxCount=0;
	
	//config pin*/
	Pinmux_Config(UART_TX, PINMUX_FUNCTION_UART);
	Pinmux_Config(UART_RX, PINMUX_FUNCTION_UART);
	PAD_PullCtrl(UART_TX, GPIO_PuPd_UP);   //Tx/Rx pin should pull up
	PAD_PullCtrl(UART_RX, GPIO_PuPd_UP);

	RCC_PeriphClockCmd(APBPeriph_UART0, APBPeriph_UART0_CLOCK, ENABLE);

	UART_StructInit(&uart_obj.UART_InitStruct);
	uart_obj.UART_InitStruct.Parity=RUART_PARITY_DISABLE;
	UART_Init(UART_DEV, &uart_obj.UART_InitStruct);
	UART_SetBaud(UART_DEV,38400);
	UART_RxCmd(UART_DEV, ENABLE);

	InterruptRegister((IRQ_FUN)uart_irq, UART_DEV_TABLE[uart_obj.UartIndex].IrqNum, (u32)&uart_obj, 10);
	InterruptEn(UART_DEV_TABLE[uart_obj.UartIndex].IrqNum, 10);

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


