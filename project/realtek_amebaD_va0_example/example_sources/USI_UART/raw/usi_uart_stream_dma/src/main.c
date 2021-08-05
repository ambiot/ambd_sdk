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

/*UART pin location:     
   KM4 UART0: 
   PB_20  (TX)
   PB_21  (RX)
   */
#define UART_TX    _PB_20//UART  TX
#define UART_RX    _PB_21  //UART  RX
#define USI_DEV        USI0_DEV

#define SRX_BUF_SZ 32*5      /*note that dma mode buffer length should be integral multiple of 32 bytes*/
char rx_buf[SRX_BUF_SZ]__attribute__((aligned(32)))={0};  /*note that dma mode buffer address should be 32 bytes aligned*/

volatile uint32_t tx_busy=0;
volatile uint32_t rx_done=0;
USI_UARTInitTypeDef	USI_UARTInitStruct;
GDMA_InitTypeDef GDMA_InitStruct;

void dma_free(void)
{	
	u8  IsrTypeMap;
	GDMA_Cmd(GDMA_InitStruct.GDMA_Index, GDMA_InitStruct.GDMA_ChNum, DISABLE);
	IsrTypeMap = GDMA_ClearINT(GDMA_InitStruct.GDMA_Index, GDMA_InitStruct.GDMA_ChNum);
	GDMA_ChnlFree(GDMA_InitStruct.GDMA_Index, GDMA_InitStruct.GDMA_ChNum);
	USI_UARTTXDMACmd(USI_DEV, DISABLE);	
	USI_UARTRXDMACmd(USI_DEV, DISABLE);
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
}

void uart_dma_send(char *pstr,u32 len)
{
	int ret;
	u32 UartIndex;
	UartIndex=0;
	
	USI_UARTTXDMAConfig(USI_DEV, 8);
	USI_UARTTXDMACmd(USI_DEV, ENABLE);
	ret= USI_UARTTXGDMA_Init(UartIndex, &GDMA_InitStruct,
		USI_DEV, (IRQ_FUN)uart_send_string_done, pstr, len);
	NVIC_SetPriority(GDMA_GetIrqNum(0, GDMA_InitStruct.GDMA_ChNum), 12);	

	if (!ret ) {
		DiagPrintf("%s Error(%d)\n", __FUNCTION__, ret);        
		tx_busy = 0;
	}
}

u32 uart_dma_recv(u8 *pstr,u32 len)
{
	int ret;
	u32 UartIndex;
	UartIndex=0;
	USI_UARTINTConfig(USI_DEV, USI_RX_FIFO_ALMOST_FULL_INTER, DISABLE);
	USI_UARTRXDMAConfig(USI_DEV, 4);
	USI_UARTRXDMACmd(USI_DEV, ENABLE);

	ret= USI_UARTRXGDMA_Init(UartIndex,  &GDMA_InitStruct,
		USI_DEV, (IRQ_FUN)uart_recv_string_done, pstr, len);
	NVIC_SetPriority(GDMA_GetIrqNum(0, GDMA_InitStruct.GDMA_ChNum), 12);
	return ret;
}

void uart_send_string(char *pstr)
{		
	if (tx_busy) {
		return;
	}
	tx_busy = 1;
	uart_dma_send(pstr,_strlen(pstr));
}

void main(void)
{
	int ret;
	int i=0;
	int len;

	//config pin*/
	Pinmux_Config(UART_TX, PINMUX_FUNCTION_UART);
	Pinmux_Config(UART_RX, PINMUX_FUNCTION_UART);
	PAD_PullCtrl(UART_TX, GPIO_PuPd_UP);   //Tx/Rx pin should pull up
	PAD_PullCtrl(UART_RX, GPIO_PuPd_UP);

	RCC_PeriphClockCmd(APBPeriph_USI_REG, APBPeriph_USI_CLOCK, ENABLE);

	USI_UARTDeInit(USI_DEV);
	USI_UARTStructInit(&USI_UARTInitStruct);
	USI_UARTInitStruct.USI_UARTParity=USI_RUART_PARITY_DISABLE;
	USI_UARTInit(USI_DEV, &USI_UARTInitStruct);
	USI_UARTSetBaud(USI_DEV, 38400);
	USI_UARTRxCmd(USI_DEV, ENABLE);

	for(i=0;i<SRX_BUF_SZ;i++){
		rx_buf[i]=0;
    	}
	i=0;
	DiagPrintf("receive 13 bytes\r\n");
	ret=uart_dma_recv(rx_buf,13);
	
	 if (!ret) {
		DiagPrintf(" %s: Recv Error(%d)\n", __FUNCTION__, ret);        
		rx_done = 1;
	}

	while (1) {
		if (rx_done) {
			uart_send_string(rx_buf);            
			rx_done = 0;            
            		len = (i+3)%15+1;
           	 	i++;
	    		if(len == 0) {
	        		len = 1;
	    		}
            /* Wait for inputing x character to initiate DMA. 
               8 for this example*/
               	DiagPrintf("rx_len=%d\r\n", len);
			ret = uart_dma_recv(rx_buf, len);
			rx_buf[len] = 0;    // end of string

			if (!ret) {
				DiagPrintf(" %s: Recv Error(%d)\n", __FUNCTION__, ret);        
				rx_done = 1;
			}
		}
	}
}


