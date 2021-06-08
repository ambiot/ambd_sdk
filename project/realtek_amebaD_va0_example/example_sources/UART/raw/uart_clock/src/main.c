/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2015 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "device.h"
#include "main.h"


/*UART pin location:     
   KM4 UART0: 
   PA_18  (TX)
   PA_19  (RX)
   */
#define UART_TX    _PA_18	//UART0  TX
#define UART_RX    _PA_19   //UART0  RX
#define UART_DEV UART0_DEV

/* 100 bytes data, 500 clocks, provide buadrate/2 frequency */
#define SREAM_LEN 128
char sim_clock[SREAM_LEN+1];
volatile uint32_t is_stop = 0;
UART_InitTypeDef  UART_InitStruct;
GDMA_InitTypeDef GDMA_InitStruct;

void uart_clock_send_string_done(void);

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
	GDMA_Cmd(GDMA_InitStruct.GDMA_Index, GDMA_InitStruct.GDMA_ChNum, DISABLE);
	// Clear Pending ISR
	IsrTypeMap = GDMA_ClearINT(GDMA_InitStruct.GDMA_Index, GDMA_InitStruct.GDMA_ChNum);
	GDMA_ChnlFree(GDMA_InitStruct.GDMA_Index, GDMA_InitStruct.GDMA_ChNum);
	UART_TXDMACmd(UART_DEV, DISABLE);
}

void uart_clock_send_string(UART_TypeDef* UartDEV, char *pstr)
{
	int32_t ret=0;
	u32 UartIndex;
	UartIndex=uart_get_idx(UartDEV);
	
	UART_TXDMAConfig(UartDEV, 8);
	UART_TXDMACmd(UartDEV, ENABLE);
	ret= UART_TXGDMA_Init(UartIndex, &GDMA_InitStruct, UART_DEV, (IRQ_FUN)uart_clock_send_string_done,pstr,_strlen(pstr));
	NVIC_SetPriority(GDMA_GetIrqNum(0, GDMA_InitStruct.GDMA_ChNum), 12);	
 
	if (ret == 0) {
		DBG_8195A("%s Error(%d)\n", __FUNCTION__, ret);        
	}
}

void uart_clock_send_string_done()
{
	dma_free();
	if(!is_stop){
		uart_clock_send_string(UART_DEV, sim_clock);
	}
}
void uart_clock_init(int rate)
{
	int ret;
	int i;
	for (i=0;i<SREAM_LEN;i++) {
		sim_clock[i] = 0x55;
	}
	sim_clock[i] = 0;
    
	//config pin*/
	Pinmux_Config(UART_TX, PINMUX_FUNCTION_UART);
	Pinmux_Config(UART_RX, PINMUX_FUNCTION_UART);
	PAD_PullCtrl(UART_TX, GPIO_PuPd_UP);   //Tx/Rx pin should pull up
	PAD_PullCtrl(UART_RX, GPIO_PuPd_UP);

	RCC_PeriphClockCmd(APBPeriph_UART0, APBPeriph_UART0_CLOCK, ENABLE);
    
	UART_StructInit(&UART_InitStruct);
	UART_InitStruct.Parity=RUART_PARITY_DISABLE;
	UART_Init(UART_DEV, &UART_InitStruct);
	UART_SetBaud(UART_DEV, rate*2);
	UART_RxCmd(UART_DEV, ENABLE);
}

void uart_clock_on(void)
{
	is_stop = 0;
	uart_clock_send_string(UART_DEV, sim_clock);
}

void uart_clock_off(void)
{
	is_stop = 1;
	UART_INTConfig(UART_DEV, RUART_IER_ETBEI, DISABLE);
	dma_free();
	UART_ClearTxFifo(UART_DEV);	
}

void main(void)
{
	// only support 33kHz, 36kHz, 36.7kHz 38kHz, 40kHz, 56kHz
	uart_clock_init(40000);
	
	while(1) {
		uart_clock_on();
		/*set clock time*/
		DelayMs(2000);
		uart_clock_off();
		DelayMs(3000);        
	}
}


