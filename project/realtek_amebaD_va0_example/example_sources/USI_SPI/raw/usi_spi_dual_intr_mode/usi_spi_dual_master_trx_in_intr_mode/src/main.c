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

SRAM_NOCACHE_DATA_SECTION u8 MasterTxBuf[TEST_BUF_SIZE];
SRAM_NOCACHE_DATA_SECTION u8 MasterRxBuf[TEST_BUF_SIZE];

typedef struct {
	USI_TypeDef *usi_dev;

	void *RxData;
	void *TxData;
	u32  RxLength;
	u32  TxLength;

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


static u32 USISsiInterruptHandle(void *Adaptor)
{
	P_USISSI_OBJ usi_ssi_adapter = (P_USISSI_OBJ) Adaptor;
	u32 InterruptStatus = USI_SSI_GetIsr(usi_ssi_adapter->usi_dev);

	USI_SSI_SetIsrClean(usi_ssi_adapter->usi_dev, InterruptStatus);

	if (InterruptStatus & (USI_TXFIFO_OVERFLOW_INTS | USI_RXFIFO_UNDERFLOW_INTS | \
		                         USI_RXFIFO_OVERFLOW_INTS | USI_SPI_RX_DATA_FRM_ERR_INTS)) {
		DBG_PRINTF(MODULE_SPI, LEVEL_INFO, "[INT] Tx/Rx Warning %x \n", InterruptStatus);
	}

	if ((InterruptStatus & USI_RXFIFO_ALMOST_FULL_INTS) ) {
		u32 TransLen = 0;

		TransLen = USI_SSI_ReceiveData(usi_ssi_adapter->usi_dev, usi_ssi_adapter->RxData, usi_ssi_adapter->RxLength);
		usi_ssi_adapter->RxLength -= TransLen;
		if (DataFrameSize > 8) {
			// 16~9 bits mode
			usi_ssi_adapter->RxData = (void*)(((u16*)usi_ssi_adapter->RxData) + TransLen);
		} else {
			// 8~4 bits mode
			usi_ssi_adapter->RxData = (void*)(((u8*)usi_ssi_adapter->RxData) + TransLen);
		}

		if (usi_ssi_adapter->RxLength == 0) {
			USI_SSI_INTConfig(usi_ssi_adapter->usi_dev, (USI_RXFIFO_ALMOST_FULL_INTR_EN | \
				USI_RXFIFO_OVERFLOW_INTR_EN | USI_RXFIFO_UNDERFLOW_INTR_EN), DISABLE);
			RxCompleteFlag = 1;
		}
	}

	if (InterruptStatus & USI_TXFIFO_ALMOST_EMTY_INTS) {

		u32 TransLen = 0;

		TransLen = USI_SSI_SendData(usi_ssi_adapter->usi_dev, usi_ssi_adapter->TxData,
			usi_ssi_adapter->TxLength, usi_ssi_adapter->Role);

		usi_ssi_adapter->TxLength -= TransLen;
		if (DataFrameSize > 8) {
			// 16~9 bits mode
			usi_ssi_adapter->TxData = (void*)(((u16*)usi_ssi_adapter->TxData) + TransLen);
		} else {
			// 8~4 bits mode
			usi_ssi_adapter->TxData = (void*)(((u8*)usi_ssi_adapter->TxData) + TransLen);
		}
				
		if (usi_ssi_adapter->TxLength == 0) {
			USI_SSI_INTConfig(usi_ssi_adapter->usi_dev, (USI_TXFIFO_OVERFLOW_INTR_EN | \
				USI_TXFIFO_ALMOST_EMTY_INTR_EN), DISABLE);
			// If it's not a dummy TX for master read SPI, then call the TX_done callback
			if (usi_ssi_adapter->TxData != NULL) {
				TxCompleteFlag = 1;
			}
		}
	}

	return 0;
}


void USISsiMasterWriteReadStream(P_USISSI_OBJ pUSISsiObj, char *tx_buffer, char *rx_buffer, u32 length)
{
	assert_param(length != 0);

	// wait bus idle
	while(USI_SSI_Busy(pUSISsiObj->usi_dev));

	if (DataFrameSize > 8) {
		/*  16~9 bits mode */
		pUSISsiObj->RxLength = length >> 1; // 2 bytes(16 bit) every transfer
		pUSISsiObj->TxLength = length >> 1; // 2 bytes(16 bit) every transfer
	} else {
		/*  8~4 bits mode */
		pUSISsiObj->RxLength = length; // 1 byte(8 bit) every transfer
		pUSISsiObj->TxLength = length; // 1 byte(8 bit) every transfer
	}
	pUSISsiObj->RxData = rx_buffer;
	pUSISsiObj->TxData = (void*)tx_buffer;
	USI_SSI_INTConfig(pUSISsiObj->usi_dev, (USI_RXFIFO_ALMOST_FULL_INTR_EN | \
		USI_RXFIFO_OVERFLOW_INTR_EN | USI_RXFIFO_UNDERFLOW_INTR_EN | \
		USI_TXFIFO_OVERFLOW_INTR_EN | USI_TXFIFO_ALMOST_EMTY_INTR_EN), ENABLE);
}


void USISsiMasterReadStream(P_USISSI_OBJ pUSISsiObj, char *rx_buffer, u32 length)
{
	assert_param(length != 0);
	
	// wait bus idle
	while(USI_SSI_Busy(pUSISsiObj->usi_dev));

	if (DataFrameSize > 8) {
		/*  16~9 bits mode */
		pUSISsiObj->RxLength = length >> 1; // 2 bytes(16 bit) every transfer
	} else {
		/*  8~4 bits mode */
		pUSISsiObj->RxLength = length; // 1 byte(8 bit) every transfer
	}
	pUSISsiObj->RxData = rx_buffer;
	USI_SSI_INTConfig(pUSISsiObj->usi_dev, (USI_RXFIFO_ALMOST_FULL_INTR_EN | \
		USI_RXFIFO_OVERFLOW_INTR_EN | USI_RXFIFO_UNDERFLOW_INTR_EN), ENABLE);

	/* as Master mode, it need to push data to TX FIFO to generate clock out 
	then the slave can transmit data out */
	// send one dummy data out
	USI_SSI_SetReadLen(pUSISsiObj->usi_dev, length);
	USI_SSI_WriteData(pUSISsiObj->usi_dev, (u32)0);
}


void USISsiFree(P_USISSI_OBJ pUSISsiObj)
{
	InterruptDis(USI_DEV_TABLE[0].IrqNum);
	InterruptUnRegister(USI_DEV_TABLE[0].IrqNum);
	USI_SSI_INTConfig(pUSISsiObj->usi_dev, (USI_RXFIFO_ALMOST_FULL_INTR_EN | \
		USI_RXFIFO_OVERFLOW_INTR_EN | USI_RXFIFO_UNDERFLOW_INTR_EN), DISABLE);
	USI_SSI_Cmd(pUSISsiObj->usi_dev, DISABLE);
}


void usi_spi_interrupt_task(void* param)
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

	InterruptRegister((IRQ_FUN)USISsiInterruptHandle, USI_DEV_TABLE[0].IrqNum, (u32)pUSISsiObj, 10);
	InterruptEn(USI_DEV_TABLE[0].IrqNum, 10);


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

		USISsiMasterWriteReadStream(pUSISsiObj, MasterTxBuf, MasterRxBuf, TEST_BUF_SIZE);

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
		USISsiMasterReadStream(pUSISsiObj, MasterRxBuf, TEST_BUF_SIZE);

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
	if(xTaskCreate(usi_spi_interrupt_task, ((const char*)"usi_spi_interrupt_task"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(usi_spi_interrupt_task) failed", __FUNCTION__);

	vTaskStartScheduler();
	while(1){
		vTaskDelay( 1000 / portTICK_RATE_MS );
	}
	
}