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
   KM4 USI UART: 
   PB_20  (TX)
   PB_21  (RX)
   */
#define UART_TX    _PB_20	//UART  TX
#define UART_RX    _PB_21   //UART  RX
#define USI_DEV        USI0_DEV

/* 100 bytes data, 500 clocks, provide buadrate/2 frequency */
#define SREAM_LEN 128
char sim_clock[SREAM_LEN+1];
volatile uint32_t is_stop = 0;
USI_UARTInitTypeDef	USI_UARTInitStruct;
GDMA_InitTypeDef GDMA_InitStruct;

void uart_clock_send_string_done(void);


void dma_free(void)
{	
	u8  IsrTypeMap;
	GDMA_Cmd(GDMA_InitStruct.GDMA_Index, GDMA_InitStruct.GDMA_ChNum, DISABLE);
	// Clear Pending ISR
	IsrTypeMap = GDMA_ClearINT(GDMA_InitStruct.GDMA_Index, GDMA_InitStruct.GDMA_ChNum);
	GDMA_ChnlFree(GDMA_InitStruct.GDMA_Index, GDMA_InitStruct.GDMA_ChNum);
	USI_UARTTXDMACmd(USI_DEV, DISABLE);
}

void uart_clock_send_string(USI_TypeDef* UartDEV, char *pstr)
{
	int32_t ret=0;
	u32 UartIndex;
	UartIndex=0;
	
	USI_UARTTXDMAConfig(UartDEV, 8);
	USI_UARTTXDMACmd(UartDEV, ENABLE);
	ret=USI_UARTTXGDMA_Init(UartIndex, &GDMA_InitStruct, USI_DEV, (IRQ_FUN)uart_clock_send_string_done, pstr, _strlen(pstr));
	NVIC_SetPriority(GDMA_GetIrqNum(0, GDMA_InitStruct.GDMA_ChNum), 12);	
 
	if (ret == 0) {
		DiagPrintf("%s Error(%d)\n", __FUNCTION__, ret);        
	}
}

void uart_clock_send_string_done()
{
	dma_free();
	if(!is_stop){
		uart_clock_send_string(USI_DEV, sim_clock);
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

	RCC_PeriphClockCmd(APBPeriph_USI_REG, APBPeriph_USI_CLOCK, ENABLE);
	
   	USI_UARTDeInit(USI_DEV);
	USI_UARTStructInit(&USI_UARTInitStruct);
	USI_UARTInitStruct.USI_UARTParity=RUART_PARITY_DISABLE;
	USI_UARTInit(USI_DEV, &USI_UARTInitStruct);
	USI_UARTSetBaud(USI_DEV, rate*2);
	USI_UARTRxCmd(USI_DEV, ENABLE);
}

void uart_clock_on(void)
{
	is_stop = 0;
	uart_clock_send_string(USI_DEV, sim_clock);
}

void uart_clock_off(void)
{
	is_stop = 1;
	USI_UARTINTConfig(USI_DEV, USI_TX_FIFO_ALMOST_EMPTY_INTER, DISABLE);
	dma_free();
	USI_UARTClearTxFifo(USI_DEV);	
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

