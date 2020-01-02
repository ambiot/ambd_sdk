/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2014 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "device.h"
#include "diag.h"
#include "main.h"
#include "rtl8721d_usi_ssi.h"

#define TEST_BUF_SIZE	256
#define DataFrameSize		8
#define dfs_mask			0xFF	

/*USI_SPI pin location:

		PA_25  (MOSI)
		PA_26  (MISO)
		PA_30  (SCLK)
		PA_28  (CS)
*/

#define USI_SPI_MOSI	PA_25
#define USI_SPI_MISO	PA_26
#define USI_SPI_SCLK	PA_30
#define USI_SPI_CS	PA_28

SRAM_NOCACHE_DATA_SECTION u8 SlaveTxBuf[TEST_BUF_SIZE];
SRAM_NOCACHE_DATA_SECTION u8 SlaveRxBuf[TEST_BUF_SIZE];

typedef struct {
	USI_TypeDef *usi_dev;

	void *RxData;
	void *TxData;
	u32  RxLength;
	u32  TxLength;

	GDMA_InitTypeDef USISsiTxGdmaInitStruct;
	GDMA_InitTypeDef USISsiRxGdmaInitStruct;

	u32   Role;
}USISSI_OBJ, *P_USISSI_OBJ;

USISSI_OBJ USISsiObj;


/* Complete Flag of TRx */
volatile int RxCompleteFlag;
volatile int TxCompleteFlag;


BOOL USISsiDataCompare(u8 *pSrc, u8 *pDst, u32 Length)
{
	int Index;
	u8 res = _TRUE;
	
	for (Index = 0; Index < Length; ++Index){
		if((pSrc[Index] & dfs_mask)!= pDst[Index]) {
			res = _FALSE;
		}
	}

	return res;
}


void USISsiPrint(u8 *pSrc, u8 *pDst, u32 Length)
{
	int Index;

	for(Index = 0; Index < Length; Index++){
		DBG_8195A("%x: %x ---- %x\n",Index, pSrc[Index] & dfs_mask, pDst[Index]);
	}
}


/* GDMA Tx IRQ Handler */
static void USISsiDmaTxIrqHandle (P_USISSI_OBJ pUSISsiObj)
{
	PGDMA_InitTypeDef GDMA_InitStruct;

	GDMA_InitStruct = &pUSISsiObj->USISsiTxGdmaInitStruct;

	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
	GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, DISABLE);

	/*  TX complete callback */
	TxCompleteFlag = 1;

	USI_SSI_SetDmaEnable(pUSISsiObj->usi_dev, DISABLE, USI_TX_DMA_ENABLE);

	GDMA_ChnlFree(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
}


/* GDMA Rx IRQ Handler */
static void USISsiDmaRxIrqHandle (P_USISSI_OBJ pUSISsiObj)
{
	PGDMA_InitTypeDef GDMA_InitStruct;

	GDMA_InitStruct = &pUSISsiObj->USISsiRxGdmaInitStruct;

	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
	GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, DISABLE);

	USI_SSI_SetDmaEnable(pUSISsiObj->usi_dev, DISABLE, USI_RX_DMA_ENABLE);
	
	/*  RX complete callback */
	RxCompleteFlag = 1;

	GDMA_ChnlFree(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
}

void USISsiSlaveReadStreamDma(P_USISSI_OBJ pUSISsiObj, char *rx_buffer, u32 length)
{
	assert_param(length != 0);
	assert_param(rx_buffer != NULL);
	
	pUSISsiObj->RxLength = length;
	pUSISsiObj->RxData = (void*)rx_buffer;

	USI_SSI_RXGDMA_Init(0, &pUSISsiObj->USISsiRxGdmaInitStruct, pUSISsiObj, USISsiDmaRxIrqHandle, rx_buffer, length);
	USI_SSI_SetDmaEnable(pUSISsiObj->usi_dev, ENABLE, USI_RX_DMA_ENABLE);
}


void USISsiSlaveWriteStreamDma(P_USISSI_OBJ pUSISsiObj, char *tx_buffer, u32 length)
{
	assert_param(length != 0);
	assert_param(tx_buffer != NULL);
	
	pUSISsiObj->RxLength = length;
	pUSISsiObj->RxData = (void*)tx_buffer;

	USI_SSI_TXGDMA_Init(0, &pUSISsiObj->USISsiTxGdmaInitStruct, pUSISsiObj, USISsiDmaTxIrqHandle, tx_buffer, length);
	USI_SSI_SetDmaEnable(pUSISsiObj->usi_dev, ENABLE, USI_TX_DMA_ENABLE);
}


void USISsiFree(P_USISSI_OBJ pUSISsiObj)
{
	PGDMA_InitTypeDef GDMA_Tx;
	GDMA_Tx = &pUSISsiObj->USISsiTxGdmaInitStruct;
	/* Set USI_SSI Tx DMA Disable */
	USI_SSI_SetDmaEnable(pUSISsiObj->usi_dev, DISABLE, USI_TX_DMA_ENABLE);
	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_Tx->GDMA_Index, GDMA_Tx->GDMA_ChNum);
	GDMA_ChCleanAutoReload(GDMA_Tx->GDMA_Index, GDMA_Tx->GDMA_ChNum, CLEAN_RELOAD_SRC_DST);
	GDMA_Cmd(GDMA_Tx->GDMA_Index, GDMA_Tx->GDMA_ChNum, DISABLE);
	GDMA_ChnlFree(GDMA_Tx->GDMA_Index, GDMA_Tx->GDMA_ChNum);

	PGDMA_InitTypeDef GDMA_Rx;
	GDMA_Rx = &pUSISsiObj->USISsiRxGdmaInitStruct;
	/* Set USI_SSI Rx DMA Disable */
	USI_SSI_SetDmaEnable(pUSISsiObj->usi_dev, DISABLE, USI_RX_DMA_ENABLE);
	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_Rx->GDMA_Index, GDMA_Rx->GDMA_ChNum);
	GDMA_ChCleanAutoReload(GDMA_Rx->GDMA_Index, GDMA_Rx->GDMA_ChNum, CLEAN_RELOAD_SRC_DST);
	GDMA_Cmd(GDMA_Rx->GDMA_Index, GDMA_Rx->GDMA_ChNum, DISABLE);
	GDMA_ChnlFree(GDMA_Rx->GDMA_Index, GDMA_Rx->GDMA_ChNum);
}


void main(void)
{

	u32 SclkPhase = USI_SPI_SCPH_TOGGLES_IN_MIDDLE;
	u32 SclkPolarity = USI_SPI_SCPOL_INACTIVE_IS_LOW;
	int i = 0;
	int result = 1;


	/* init USI_SPI as Slave*/
	USI_SSI_InitTypeDef USI_SSI_InitStruct;
	
	RCC_PeriphClockCmd(APBPeriph_USI_REG, APBPeriph_USI_CLOCK, ENABLE);
	Pinmux_Config(USI_SPI_MOSI, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(USI_SPI_MISO, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(USI_SPI_CS, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(USI_SPI_SCLK, PINMUX_FUNCTION_SPIS);

	if (SclkPolarity == USI_SPI_SCPOL_INACTIVE_IS_LOW) {
		/* CS pull high, CLK pull low */
		PAD_PullCtrl(USI_SPI_CS, GPIO_PuPd_UP);
		PAD_PullCtrl(USI_SPI_SCLK, GPIO_PuPd_DOWN);
	} else {
		/* CS pull high, CLK pull high */
		PAD_PullCtrl(USI_SPI_CS, GPIO_PuPd_UP);
		PAD_PullCtrl(USI_SPI_SCLK, GPIO_PuPd_UP);
	}

	USI_SSI_StructInit(&USI_SSI_InitStruct);	
	USI_SSI_InitStruct.USI_SPI_Role = USI_SPI_SLAVE;
	USI_SSI_InitStruct.USI_SPI_SclkPhase = SclkPhase;
	USI_SSI_InitStruct.USI_SPI_SclkPolarity = SclkPolarity;
	USI_SSI_InitStruct.USI_SPI_DataFrameSize = DataFrameSize - 1;
	USI_SSI_Init(USI0_DEV, &USI_SSI_InitStruct);

	P_USISSI_OBJ pUSISsiObj = &USISsiObj;
	pUSISsiObj->usi_dev = USI0_DEV;


	_memset(SlaveTxBuf, 0, TEST_BUF_SIZE);
	_memset(SlaveRxBuf, 0, TEST_BUF_SIZE);

	for(i = 0; i < TEST_BUF_SIZE;i++) {
		*((u8*)SlaveTxBuf + i) = i;
		}

	/**
	* Slave write/read
	*/
	DBG_8195A("----------- Slave write/read -----------\n");

		RxCompleteFlag = 0;
		TxCompleteFlag = 0;

		USISsiSlaveReadStreamDma(pUSISsiObj, SlaveRxBuf, TEST_BUF_SIZE);
		USISsiSlaveWriteStreamDma(pUSISsiObj, SlaveTxBuf, TEST_BUF_SIZE);

		i=0;
		while(RxCompleteFlag == 0) {
			DelayMs(100);
			i++;
			if (i>150) {
				DBG_8195A("USI SPI Slave Wait Timeout\r\n");
				break;
			}
		}
		
		//USISsiPrint(SlaveTxBuf, SlaveRxBuf, TEST_BUF_SIZE);
		result = USISsiDataCompare(SlaveTxBuf, SlaveRxBuf, TEST_BUF_SIZE);

	/**
	* Slave write
	*/
	DBG_8195A("----------- Slave write -----------\n");

		TxCompleteFlag = 0;

		USISsiSlaveWriteStreamDma(pUSISsiObj, SlaveTxBuf, TEST_BUF_SIZE);

		i=0;
		while(TxCompleteFlag == 0) {
			DelayMs(100);
			i++;
			if (i>150) {
				DBG_8195A("USI SPI Slave Timeout\r\n");
				result = 0;
				break;
			}
		}


	/* free USI_SPI */
	USISsiFree(pUSISsiObj);

	DBG_8195A("USI SPI Slave Demo Finished.\n");
	DBG_8195A("\r\nSlave Result is %s\r\n", result ? "success" : "fail");
	for(;;);

}

