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
#include "rtl8721d_ssi.h"

#define DataFrameSize	8
#define dfs_mask 		0xFF
#define ClockDivider	20
#define TEST_BUF_SIZE	512 //for dma mode, buffer size should be multiple of 32-byte

/*SPIx pin location:

SPI0:

	S0: PB_18  (MOSI)
		PB_19  (MISO)
		PB_20  (SCLK)
		PB_21  (CS)


	S1: PA_16  (MOSI)
		PA_17  (MISO)
		PA_18  (SCLK)
		PA_19  (CS)

SPI1:

	S0: PA_12  (MOSI)
		PA_13  (MISO)
		PA_14  (SCLK)
		PA_15  (CS)

	S1: PB_4  (MOSI)
		PB_5  (MISO)
		PB_6  (SCLK)
		PB_7  (CS)
*/
// SPI0 (S1)
#define SPI0_MOSI  PA_16
#define SPI0_MISO  PA_17
#define SPI0_SCLK  PA_18
#define SPI0_CS    PA_19

// SPI1 (S1)
#define SPI1_MOSI  PB_4
#define SPI1_MISO  PB_5
#define SPI1_SCLK  PB_6
#define SPI1_CS    PB_7

/* for dma mode, start address of buffer should be 32-byte aligned*/
u8 MasterTxBuf[TEST_BUF_SIZE] __attribute__((aligned(32)));
u8 MasterRxBuf[TEST_BUF_SIZE] __attribute__((aligned(32)));
u8 SlaveTxBuf[TEST_BUF_SIZE] __attribute__((aligned(32)));
u8 SlaveRxBuf[TEST_BUF_SIZE] __attribute__((aligned(32)));

volatile int MasterTxDone;
volatile int MasterRxDone;
volatile int SlaveTxDone;
volatile int SlaveRxDone;

typedef struct {
	GDMA_InitTypeDef SSITxGdmaInitStruct;
	GDMA_InitTypeDef SSIRxGdmaInitStruct;
	
	SPI_TypeDef *spi_dev;
	
	void *RxData;
	void *TxData;
	u32  RxLength;
	u32  TxLength;

	u32   Index;
}SPI_OBJ;

SPI_OBJ spi_master;
SPI_OBJ spi_slave;

typedef enum {
    SpiRxIrq,
    SpiTxIrq
} SpiIrq;

/* GDMA IRQ Handler */
void Ssi_dma_tx_irq(void *Data)
{
	SPI_OBJ* spi_obj = (SPI_OBJ*) Data;
	PGDMA_InitTypeDef GDMA_InitStruct;

	GDMA_InitStruct = &spi_obj->SSITxGdmaInitStruct;
	
	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
	GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, DISABLE);

	/*  Call user TX complete callback */
	if (spi_obj->Index == 0)
		SlaveTxDone = 1;
	else 
		MasterTxDone = 1;

	/* Set SSI DMA Disable */
	SSI_SetDmaEnable(spi_obj->spi_dev, DISABLE, BIT_SHIFT_DMACR_TDMAE);
	GDMA_ChnlFree(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
}

void Ssi_dma_rx_irq(void *Data)
{
	SPI_OBJ* spi_obj = (SPI_OBJ*) Data;
	u32 Length = spi_obj->RxLength;
	u32* pRxData = spi_obj->RxData;
	PGDMA_InitTypeDef GDMA_InitStruct;

	GDMA_InitStruct = &spi_obj->SSIRxGdmaInitStruct;

	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
	GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, DISABLE);

	DCache_Invalidate((u32) pRxData, Length);

	/*  Call user RX complete callback */
	if (spi_obj->Index == 0)
		SlaveRxDone = 1;
	else 
		MasterRxDone = 1;

	/* Set SSI DMA Disable */
	SSI_SetDmaEnable(spi_obj->spi_dev, DISABLE, BIT_SHIFT_DMACR_RDMAE);

	GDMA_ChnlFree(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
}

BOOL SsiDataCompare(u8 *pSrc, u8 *pDst, u32 Length)
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

void SsiPrint(u8 *pSrc, u8 *pDst, u32 Length)
{
	int Index;

	for(Index = 0;Index < Length; Index++){
		DiagPrintf("%x: %x ---- %x\n",Index, pSrc[Index] & dfs_mask, pDst[Index]);
	}
}

void Spi_flush_rx_fifo (SPI_OBJ* spi_obj)
{
	u32 rx_fifo_level;
	u32 j;

	while(SSI_Readable(spi_obj->spi_dev)){
		rx_fifo_level = SSI_GetRxCount(spi_obj->spi_dev);
		for(j=0;j<rx_fifo_level;j++) {
			SSI_ReadData(spi_obj->spi_dev);
		}
	}	
}

void Spi_free(SPI_OBJ* spi_obj)
{
	PGDMA_InitTypeDef GDMA_Rx = &spi_obj->SSIRxGdmaInitStruct;
	
	/* Set SSI Rx DMA Disable */
	SSI_SetDmaEnable(spi_obj->spi_dev, DISABLE, BIT_SHIFT_DMACR_RDMAE);
	
	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_Rx->GDMA_Index, GDMA_Rx->GDMA_ChNum);
	GDMA_ChCleanAutoReload(GDMA_Rx->GDMA_Index, GDMA_Rx->GDMA_ChNum, CLEAN_RELOAD_SRC_DST);
	GDMA_Cmd(GDMA_Rx->GDMA_Index, GDMA_Rx->GDMA_ChNum, DISABLE);
	GDMA_ChnlFree(GDMA_Rx->GDMA_Index, GDMA_Rx->GDMA_ChNum);

	PGDMA_InitTypeDef GDMA_Tx = &spi_obj->SSITxGdmaInitStruct;
	
	/* Set SSI Tx DMA Disable */
	SSI_SetDmaEnable(spi_obj->spi_dev, DISABLE, BIT_SHIFT_DMACR_TDMAE);
	
	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_Tx->GDMA_Index, GDMA_Tx->GDMA_ChNum);
	GDMA_ChCleanAutoReload(GDMA_Tx->GDMA_Index, GDMA_Tx->GDMA_ChNum, CLEAN_RELOAD_SRC_DST);
	GDMA_Cmd(GDMA_Tx->GDMA_Index, GDMA_Tx->GDMA_ChNum, DISABLE);
	GDMA_ChnlFree(GDMA_Tx->GDMA_Index, GDMA_Tx->GDMA_ChNum);
	
	SSI_Cmd(spi_obj->spi_dev, DISABLE);
}

void Spi_slave_read_stream_dma(SPI_OBJ *spi_obj, char *rx_buffer, uint32_t length)
{
	assert_param(length != 0);
	assert_param(rx_buffer != NULL);
	
	spi_obj->RxLength = length;
	spi_obj->RxData = (void*)rx_buffer;

	SSI_RXGDMA_Init(spi_obj->Index, &spi_obj->SSIRxGdmaInitStruct, (void*)spi_obj, (IRQ_FUN) Ssi_dma_rx_irq, rx_buffer, length);
	NVIC_SetPriority(GDMA_GetIrqNum(0, spi_obj->SSIRxGdmaInitStruct.GDMA_ChNum), 11);		
	/* Set SSI DMA Enable */
	SSI_SetDmaEnable(spi_obj->spi_dev, ENABLE, BIT_SHIFT_DMACR_RDMAE);
}

void Spi_slave_write_stream_dma(SPI_OBJ *spi_obj, char *tx_buffer, uint32_t length)
{
	assert_param(length != 0);
	assert_param(tx_buffer != NULL);

	spi_obj->TxLength = length;
	spi_obj->TxData = (void*)tx_buffer;

	SSI_SetDmaEnable(spi_obj->spi_dev, ENABLE, BIT_SHIFT_DMACR_TDMAE);
	SSI_TXGDMA_Init(spi_obj->Index, &spi_obj->SSITxGdmaInitStruct, (void*)spi_obj, (IRQ_FUN) Ssi_dma_tx_irq, tx_buffer, length);
	NVIC_SetPriority(GDMA_GetIrqNum(0, spi_obj->SSITxGdmaInitStruct.GDMA_ChNum), 10); 
}

void Spi_master_read_stream_dma(SPI_OBJ *spi_obj, char *rx_buffer, uint32_t length)
{
	assert_param(length != 0);
	assert_param(rx_buffer != NULL);

	spi_obj->RxLength = length;
	spi_obj->RxData = (void*)rx_buffer;

	SSI_RXGDMA_Init(spi_obj->Index, &spi_obj->SSIRxGdmaInitStruct, (void*)spi_obj, (IRQ_FUN) Ssi_dma_rx_irq, rx_buffer, length);
	NVIC_SetPriority(GDMA_GetIrqNum(0, spi_obj->SSIRxGdmaInitStruct.GDMA_ChNum), 11); 	
	/* Set SSI DMA Enable */
	SSI_SetDmaEnable(spi_obj->spi_dev, ENABLE, BIT_SHIFT_DMACR_RDMAE);

	spi_obj->TxLength = length;
	spi_obj->TxData = (void*)SlaveTxBuf;
	
	SSI_SetDmaEnable(spi_obj->spi_dev, ENABLE, BIT_SHIFT_DMACR_TDMAE);
	SSI_TXGDMA_Init(spi_obj->Index, &spi_obj->SSITxGdmaInitStruct, (void*)spi_obj, (IRQ_FUN) Ssi_dma_tx_irq, SlaveTxBuf, length);
	NVIC_SetPriority(GDMA_GetIrqNum(0, spi_obj->SSITxGdmaInitStruct.GDMA_ChNum), 10); 
} 

void Spi_master_write_read_stream_dma(SPI_OBJ *spi_obj, char *tx_buffer, char *rx_buffer, uint32_t length)
{
	assert_param(length != 0);
	assert_param(tx_buffer != NULL);
	assert_param(rx_buffer != NULL);
	
	spi_obj->RxLength = length;
	spi_obj->RxData = (void*)rx_buffer;
	spi_obj->TxLength = length;
	spi_obj->TxData = (void*)tx_buffer;

	SSI_RXGDMA_Init(spi_obj->Index, &spi_obj->SSIRxGdmaInitStruct, (void*)spi_obj, (IRQ_FUN) Ssi_dma_rx_irq, rx_buffer, length);
	NVIC_SetPriority(GDMA_GetIrqNum(0, spi_obj->SSIRxGdmaInitStruct.GDMA_ChNum), 11);	
	
	SSI_SetDmaEnable(spi_obj->spi_dev, ENABLE, BIT_SHIFT_DMACR_RDMAE);

	SSI_SetDmaEnable(spi_obj->spi_dev, ENABLE, BIT_SHIFT_DMACR_TDMAE);
	SSI_TXGDMA_Init(spi_obj->Index, &spi_obj->SSITxGdmaInitStruct, (void*)spi_obj, (IRQ_FUN) Ssi_dma_tx_irq, tx_buffer, length);
	NVIC_SetPriority(GDMA_GetIrqNum(0, spi_obj->SSITxGdmaInitStruct.GDMA_ChNum), 10); 
} 

void spi_dma_task(void* param)
{

	u32 SclkPhase = SCPH_TOGGLES_IN_MIDDLE; // SCPH_TOGGLES_IN_MIDDLE or SCPH_TOGGLES_AT_START
	u32 SclkPolarity = SCPOL_INACTIVE_IS_LOW; // SCPOL_INACTIVE_IS_LOW or SCPOL_INACTIVE_IS_HIGH
	int i = 0;
	int result1 = 1;
	int result2 = 1;
	int result3 = 1;

    /* SPI1 is as Master */

	/* init SPI1 */
	SSI_InitTypeDef SSI_InitStructM;
	
	spi_master.Index = 0x1;
	spi_master.spi_dev = SPI_DEV_TABLE[spi_master.Index].SPIx;

	SSI_StructInit(&SSI_InitStructM);
	RCC_PeriphClockCmd(APBPeriph_SPI1, APBPeriph_SPI1_CLOCK, ENABLE);
	Pinmux_Config(SPI1_MOSI, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(SPI1_MISO, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(SPI1_SCLK, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(SPI1_CS, PINMUX_FUNCTION_SPIM);
	/* for cases when SPI0 is as master 
	if( spi_master.Index == 0)  
		SSI_SetRole(spi_master.spi_dev, SSI_MASTER); */
	SSI_InitStructM.SPI_Role = SSI_MASTER;

	SSI_Init(spi_master.spi_dev, &SSI_InitStructM);
 
	/* set format */
	SSI_SetSclkPhase(spi_master.spi_dev, SclkPhase);
	SSI_SetSclkPolarity(spi_master.spi_dev, SclkPolarity);
	SSI_SetDataFrameSize(spi_master.spi_dev, DataFrameSize-1);

	/* set frequency */
	SSI_SetBaudDiv(spi_master.spi_dev, ClockDivider); // IpClk of SPI1 is 50MHz, IpClk of SPI0 is 100MHz

	/* SPI0 is as Slave */
	/* init SPI0 */
	SSI_InitTypeDef SSI_InitStructS;

	spi_slave.Index = 0x0;
	spi_slave.spi_dev = SPI_DEV_TABLE[spi_slave.Index].SPIx;
	
	SSI_StructInit(&SSI_InitStructS);
	RCC_PeriphClockCmd(APBPeriph_SPI0, APBPeriph_SPI0_CLOCK, ENABLE);
	Pinmux_Config(SPI0_MOSI, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(SPI0_MISO, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(SPI0_SCLK, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(SPI0_CS, PINMUX_FUNCTION_SPIS);

	SSI_SetRole(spi_slave.spi_dev, SSI_SLAVE);
	SSI_InitStructS.SPI_Role = SSI_SLAVE;		
	SSI_Init(spi_slave.spi_dev, &SSI_InitStructS);

	/* set format */
	SSI_SetSclkPhase(spi_slave.spi_dev, SclkPhase);
	SSI_SetSclkPolarity(spi_slave.spi_dev, SclkPolarity);
	SSI_SetDataFrameSize(spi_slave.spi_dev, DataFrameSize-1);

	if (SclkPolarity == SCPOL_INACTIVE_IS_LOW) {
			PAD_PullCtrl((u32)SPI0_SCLK, GPIO_PuPd_DOWN);
		}
		else {
			PAD_PullCtrl((u32)SPI0_SCLK, GPIO_PuPd_UP);
		}

	_memset(MasterTxBuf, 0, TEST_BUF_SIZE);
	_memset(MasterRxBuf, 0, TEST_BUF_SIZE);
	_memset(SlaveTxBuf, 0, TEST_BUF_SIZE);
	_memset(SlaveRxBuf, 0, TEST_BUF_SIZE);
	
	for(i = 0; i < TEST_BUF_SIZE;i++) {
		*((u8*)MasterTxBuf + i) = i;
		}
	
	for(i = 0; i < TEST_BUF_SIZE;i++) {
		*((u8*)SlaveTxBuf + i) = i;
		}

	/**
	 * Master write/read, Slave read/write
	 */
	DiagPrintf("------Master write/read, Slave read/write-------\n");
		
		MasterRxDone = 0;
		SlaveRxDone = 0;
		MasterTxDone = 0;
		MasterTxDone = 0;

		Spi_slave_read_stream_dma(&spi_slave, SlaveRxBuf, TEST_BUF_SIZE);	
		Spi_slave_write_stream_dma(&spi_slave, SlaveTxBuf, TEST_BUF_SIZE);
		Spi_master_write_read_stream_dma(&spi_master, MasterTxBuf, MasterRxBuf, TEST_BUF_SIZE);
		

		i=0;
	    while((MasterRxDone && SlaveRxDone) == 0) {
	        DelayMs(100);
	        i++;
	        if (i>150) {
	            DiagPrintf("SPI Wait Timeout\r\n");
	            break;
	        }
	    }

		SsiPrint(MasterTxBuf, SlaveRxBuf, TEST_BUF_SIZE);
		result1 = SsiDataCompare(MasterTxBuf, SlaveRxBuf, TEST_BUF_SIZE);
		SsiPrint(SlaveTxBuf, MasterRxBuf, TEST_BUF_SIZE);
		result2 = SsiDataCompare(SlaveTxBuf, MasterRxBuf, TEST_BUF_SIZE);
		
	/**
	 * Master read, Slave write
	 */
	DiagPrintf("-----------Master read, Slave write------------\n");
  
		MasterRxDone = 0;
		MasterTxDone = 0;

		/* flush rx fifo */
		Spi_flush_rx_fifo(&spi_master);

		Spi_slave_write_stream_dma(&spi_slave, SlaveTxBuf, TEST_BUF_SIZE);
		Spi_master_read_stream_dma(&spi_master, MasterRxBuf, TEST_BUF_SIZE);


		i=0;
		while(MasterRxDone == 0) {
		    DelayMs(100);
		    i++;
		    if (i>150) {
		        DiagPrintf("SPI Master Wait Timeout\r\n");
		        break;
		    }
		}

		SsiPrint(SlaveTxBuf, MasterRxBuf, TEST_BUF_SIZE);
		result3 = SsiDataCompare(SlaveTxBuf, MasterRxBuf, TEST_BUF_SIZE);
		
	DiagPrintf("\r\nResult is %s\r\n", (result1 && result2 && result3) ? "success" : "fail");
	
	Spi_free(&spi_master);
	Spi_free(&spi_slave);

	DiagPrintf("SPI Demo finished.\n");

	vTaskDelete(NULL);

}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	if(xTaskCreate(spi_dma_task, ((const char*)"spi_dma_task"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		DiagPrintf("\n\r%s xTaskCreate(spi_dma_task) failed", __FUNCTION__);

	vTaskStartScheduler();
	while(1){
		vTaskDelay( 1000 / portTICK_RATE_MS );
	}
	
}

