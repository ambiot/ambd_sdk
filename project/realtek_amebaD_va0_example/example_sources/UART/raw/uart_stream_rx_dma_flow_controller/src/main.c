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
//#include "main.h"


/*UART pin location:     
   KM4 UART0: 
   PA_18  (TX)
   PA_19  (RX)
   */
#define UART_TX    _PA_18//UART0  TX
#define UART_RX    _PA_19  //UART0  RX
#define UART_DEV  UART0_DEV

#define SRX_BUF_SZ 32*5      /*note that dma mode buffer length should be integral multiple of 32 bytes*/
char rx_buf[SRX_BUF_SZ]__attribute__((aligned(32)))={0};  /*note that dma mode buffer address should be 32 bytes aligned*/

UART_InitTypeDef UART_InitStruct;
GDMA_InitTypeDef GDMA_InitStruct;

volatile u32 tx_busy=0;
volatile u32 rx_done=0;
volatile u32 wait_rx=0;

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

void dma_free(void)
{	
	u8  IsrTypeMap;
	GDMA_ChCleanAutoReload(GDMA_InitStruct.GDMA_Index, GDMA_InitStruct.GDMA_ChNum, CLEAN_RELOAD_SRC);
	GDMA_Cmd(GDMA_InitStruct.GDMA_Index, GDMA_InitStruct.GDMA_ChNum, DISABLE);
	IsrTypeMap = GDMA_ClearINT(GDMA_InitStruct.GDMA_Index, GDMA_InitStruct.GDMA_ChNum);
	GDMA_ChnlFree(GDMA_InitStruct.GDMA_Index, GDMA_InitStruct.GDMA_ChNum);
	UART_INTConfig(UART_DEV, RUART_IER_ERBI | RUART_IER_ELSI |RUART_IER_ETOI, DISABLE);
	UART_TXDMACmd(UART_DEV, DISABLE);	
	UART_RXDMACmd(UART_DEV, DISABLE);
}

void uart_send_string_done(void)
{
	dma_free();
	tx_busy = 0;
}

void uart_recv_string_done(void)
{
	DCache_Invalidate((u32)rx_buf, SRX_BUF_SZ);  /*!!!To solve the cache consistency problem, DMA mode need it!!!*/
	dma_free();
	rx_done = 1;
	wait_rx=0;
	tx_busy=1;
}

void uart_dma_send(char *pstr,u32 len)
{
	int ret;
	u32 UartIndex;
	UartIndex=uart_get_idx(UART_DEV);
	
	UART_TXDMAConfig(UART_DEV, 8);
	UART_TXDMACmd(UART_DEV, ENABLE);
	ret= UART_TXGDMA_Init(UartIndex, &GDMA_InitStruct,
		UART_DEV, (IRQ_FUN)uart_send_string_done, pstr, len);
	NVIC_SetPriority(GDMA_GetIrqNum(0, GDMA_InitStruct.GDMA_ChNum), 12);	

	 if (!ret ) {
		DiagPrintf("%s Error(%d)\n", __FUNCTION__, ret);        
		tx_busy = 0;
	}
}

u32 uart_dma_recv_flow_controller(u8 * pstr)
{
	wait_rx=1;
	int ret;
	u32 UartIndex;
	UartIndex=uart_get_idx(UART_DEV);
	UART_INTConfig(UART_DEV, (RUART_IER_ERBI | RUART_IER_ELSI | RUART_IER_ETOI), DISABLE);
	UART_RXDMAConfig(UART_DEV, 4);
	UART_RXDMACmd(UART_DEV, ENABLE);

	ret= UART_RXGDMA_Init(UartIndex,  &GDMA_InitStruct,
		UART_DEV, (IRQ_FUN)uart_recv_string_done, pstr, 0);
	NVIC_SetPriority(GDMA_GetIrqNum(0, GDMA_InitStruct.GDMA_ChNum), 12);
	return ret;
}

void uart_send_string(u8 *pstr)
{
	int32_t ret=0;
	uart_dma_send( pstr, _strlen(pstr));
}

void maintask(void)
{
	int ret;
	int i=0;
	int len;

	//config pin*/
	Pinmux_Config(UART_TX, PINMUX_FUNCTION_UART);
	Pinmux_Config(UART_RX, PINMUX_FUNCTION_UART);
	PAD_PullCtrl(UART_TX, GPIO_PuPd_UP);   //Tx/Rx pin should pull up
	PAD_PullCtrl(UART_RX, GPIO_PuPd_UP);

	RCC_PeriphClockCmd(APBPeriph_UART0, APBPeriph_UART0_CLOCK, ENABLE);
	
	UART_StructInit(&UART_InitStruct);
	UART_InitStruct.Parity=RUART_PARITY_DISABLE;
	
	/*set timeout 64~65535 bit time, time in second=RxTimeOutCnt/baudrate*/
	UART_InitStruct.RxTimeOutCnt=60000;
	UART_Init(UART_DEV,&UART_InitStruct);
	UART_SetBaud(UART_DEV, 38400);
	UART_RxCmd(UART_DEV, ENABLE);

	for(i=0;i<SRX_BUF_SZ;i++){
		rx_buf[i]=0;
    	}
	while (1) {
		if (rx_done) {
			uart_send_string( rx_buf);            
			rx_done = 0;        
		}
		if(0==wait_rx&&0==tx_busy){
			ret=uart_dma_recv_flow_controller(rx_buf);
		}
	}
}

void main(void)
{
	if (pdTRUE != xTaskCreate( (TaskFunction_t)maintask, "RAW_GTIMER_DEMO_TASK", (2048 /4), (void *)NULL, (tskIDLE_PRIORITY + 1), NULL))
	{
		DiagPrintf("Create RAW_GTIMER_DEMO_TASK Err!!\n");
	}
	
	vTaskStartScheduler();
}

