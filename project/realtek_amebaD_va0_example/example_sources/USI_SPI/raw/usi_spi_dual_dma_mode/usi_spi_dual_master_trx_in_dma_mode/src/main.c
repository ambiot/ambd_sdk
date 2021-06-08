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

#define TEST_BUF_SIZE	256 //for dma mode, buffer size should be multiple of 32-byte
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

/* for dma mode, start address of buffer should be 32-byte aligned*/
u8 MasterTxBuf[TEST_BUF_SIZE] __attribute__((aligned(32)));
u8 MasterRxBuf[TEST_BUF_SIZE] __attribute__((aligned(32)));

#define USI_SPI_DMA_RX_EN           (1<<0)
#define USI_SPI_DMA_TX_EN           (1<<1)

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


/* To Empty Rx FIFO */
void USISsiFlushRxFifo(P_USISSI_OBJ pHalSsiAdaptor)
{
	u32 rx_fifo_level;
	u32 i;

	while(USI_SSI_Readable(pHalSsiAdaptor->usi_dev)){
		rx_fifo_level = USI_SSI_GetRxCount(pHalSsiAdaptor->usi_dev);
		for(i = 0; i < rx_fifo_level; i++) {
			USI_SSI_ReadData(pHalSsiAdaptor->usi_dev);
		}
	}
}


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
	u32 Length = pUSISsiObj->RxLength;
	u32* pRxData = pUSISsiObj->RxData;
	PGDMA_InitTypeDef GDMA_InitStruct;

	GDMA_InitStruct = &pUSISsiObj->USISsiRxGdmaInitStruct;

	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
	GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, DISABLE);

	DCache_Invalidate((u32) pRxData, Length);

	USI_SSI_SetDmaEnable(pUSISsiObj->usi_dev, DISABLE, USI_RX_DMA_ENABLE);
	
	/*  RX complete callback */
	RxCompleteFlag = 1;

	GDMA_ChnlFree(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
}


void USISsiMasterWriteReadStreamDma(P_USISSI_OBJ pUSISsiObj, char *tx_buffer, char *rx_buffer, u32 length)
{
	assert_param(length != 0);
	assert_param(tx_buffer != NULL);
	assert_param(rx_buffer != NULL);
	
	pUSISsiObj->RxLength = length;
	pUSISsiObj->RxData = (void*)rx_buffer;

	USI_SSI_RXGDMA_Init(0, &pUSISsiObj->USISsiRxGdmaInitStruct, pUSISsiObj, (IRQ_FUN)USISsiDmaRxIrqHandle, rx_buffer, length);
	USI_SSI_SetDmaEnable(pUSISsiObj->usi_dev, ENABLE, USI_RX_DMA_ENABLE);

	pUSISsiObj->TxLength = length;
	pUSISsiObj->TxData = (void*)tx_buffer;
	
	USI_SSI_SetDmaEnable(pUSISsiObj->usi_dev, ENABLE, USI_TX_DMA_ENABLE);
	USI_SSI_TXGDMA_Init(0, &pUSISsiObj->USISsiTxGdmaInitStruct, pUSISsiObj, (IRQ_FUN)USISsiDmaTxIrqHandle, tx_buffer, length);
}


void USISsiMasterReadStreamDma(P_USISSI_OBJ pUSISsiObj, char *rx_buffer, u32 length)
{
	assert_param(length != 0);
	assert_param(rx_buffer != NULL);
	
	pUSISsiObj->RxLength = length;
	pUSISsiObj->RxData = (void*)rx_buffer;

	USI_SSI_RXGDMA_Init(0, &pUSISsiObj->USISsiRxGdmaInitStruct, pUSISsiObj, (IRQ_FUN)USISsiDmaRxIrqHandle, rx_buffer, length);
	USI_SSI_SetDmaEnable(pUSISsiObj->usi_dev, ENABLE, USI_RX_DMA_ENABLE);
	
	/* as Master mode, it need to push data to TX FIFO to generate clock out then the slave can transmit data out */
	// send one dummy data out
	USI_SSI_SetReadLen(pUSISsiObj->usi_dev, length);
	USI_SSI_WriteData(pUSISsiObj->usi_dev, (u32)0);
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


void usi_spi_dma_task(void* param)
{

	u32 SclkPhase = USI_SPI_SCPH_TOGGLES_IN_MIDDLE;
	u32 SclkPolarity = USI_SPI_SCPOL_INACTIVE_IS_LOW;
	u32 ClockDivider = 500; // an even value between 2 and 65534
	int i = 0;
	int result1 = 1;
	int result2 = 1;


	/* init USI_SPI as Master*/
	USI_SSI_InitTypeDef USI_SSI_InitStruct;
	
	RCC_PeriphClockCmd(APBPeriph_USI_REG, APBPeriph_USI_CLOCK, ENABLE);
	Pinmux_Config(USI_SPI_MOSI, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(USI_SPI_MISO, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(USI_SPI_CS, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(USI_SPI_SCLK, PINMUX_FUNCTION_SPIM);

	USI_SSI_StructInit(&USI_SSI_InitStruct);	
	USI_SSI_InitStruct.USI_SPI_Role = USI_SPI_MASTER;
	USI_SSI_InitStruct.USI_SPI_ClockDivider = ClockDivider;
	USI_SSI_InitStruct.USI_SPI_SclkPhase = SclkPhase;
	USI_SSI_InitStruct.USI_SPI_SclkPolarity = SclkPolarity;
	USI_SSI_InitStruct.USI_SPI_DataFrameSize = DataFrameSize - 1;
	USI_SSI_Init(USI0_DEV, &USI_SSI_InitStruct);

	P_USISSI_OBJ pUSISsiObj = &USISsiObj;
	pUSISsiObj->usi_dev = USI0_DEV;


	_memset(MasterTxBuf, 0, TEST_BUF_SIZE);
	_memset(MasterRxBuf, 0, TEST_BUF_SIZE);

	for(i = 0; i < TEST_BUF_SIZE;i++) {
		*((u8*)MasterTxBuf + i) = i;
		}

	/**
	* Master write/read
	*/
	DBG_8195A("----------- Master write/read -----------\n");

		RxCompleteFlag = 0;
		TxCompleteFlag = 0;

		USISsiMasterWriteReadStreamDma(pUSISsiObj, MasterTxBuf, MasterRxBuf, TEST_BUF_SIZE);

		i=0;
		while((TxCompleteFlag && RxCompleteFlag) == 0) {
			DelayMs(100);
			i++;
			if (i>150) {
				DBG_8195A("USI SPI Master Wait Timeout\r\n");
				break;
			}
		}
		
		//USISsiPrint(MasterTxBuf, MasterRxBuf, TEST_BUF_SIZE);
		result1 = USISsiDataCompare(MasterTxBuf, MasterRxBuf, TEST_BUF_SIZE);

	/**
	* Master read
	*/
	DBG_8195A("----------- Master read -----------\n");

		RxCompleteFlag = 0;

		/* flush rx fifo */
		USISsiFlushRxFifo(pUSISsiObj);

		USI_SSI_TRxPath_Cmd(pUSISsiObj->usi_dev, USI_SPI_TX_ENABLE, DISABLE);
		USISsiMasterReadStreamDma(pUSISsiObj, MasterRxBuf, TEST_BUF_SIZE);

		i=0;
		while(RxCompleteFlag == 0) {
			DelayMs(100);
			i++;
			if (i>150) {
				DBG_8195A("USI SPI Master Timeout\r\n");
				break;
			}
		}

		//USISsiPrint(MasterTxBuf, MasterRxBuf, TEST_BUF_SIZE);
		result2 = USISsiDataCompare(MasterTxBuf, MasterRxBuf, TEST_BUF_SIZE);


	/* free USI_SPI */
	USISsiFree(pUSISsiObj);

	DBG_8195A("USI SPI Master Demo Finished.\n");
	DBG_8195A("\r\nMaster Result is %s\r\n", (result1 && result2) ? "success" : "fail");

	vTaskDelete(NULL);

}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	if(xTaskCreate(usi_spi_dma_task, ((const char*)"usi_spi_dma_task"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(usi_spi_dma_task) failed", __FUNCTION__);

	vTaskStartScheduler();
	while(1){
		vTaskDelay( 1000 / portTICK_RATE_MS );
	}
	
}

