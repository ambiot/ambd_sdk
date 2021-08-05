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
#define ClockDivider	20
#define TEST_BUF_SIZE	8192 //for dma mode, buffer size should be multiple of 32-byte

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
// SPI1 (S1)
#define SPI1_MOSI  PB_4
#define SPI1_MISO  PB_5
#define SPI1_SCLK  PB_6
#define SPI1_CS    PB_7

/* for dma mode, start address of buffer should be 32-byte aligned*/
u8 MasterTxBuf[TEST_BUF_SIZE] __attribute__((aligned(32)));

typedef struct {
	GDMA_InitTypeDef SSITxGdmaInitStruct;
	
	SPI_TypeDef *spi_dev;

	u32   Index;
}SPI_OBJ;

SPI_OBJ spi_master;

volatile int MasterTxDone;

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
	MasterTxDone = 1;

	/* Set SSI DMA Disable */
	SSI_SetDmaEnable(spi_obj->spi_dev, DISABLE, BIT_SHIFT_DMACR_TDMAE);
	GDMA_ChnlFree(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
}

void Spi_free(SPI_OBJ* spi_obj)
{
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

void spi_singleblock_task(void* param)
{

	u32 SclkPhase = SCPH_TOGGLES_IN_MIDDLE; // SCPH_TOGGLES_IN_MIDDLE or SCPH_TOGGLES_AT_START
	u32 SclkPolarity = SCPOL_INACTIVE_IS_LOW; // SCPOL_INACTIVE_IS_LOW or SCPOL_INACTIVE_IS_HIGH
	int i = 0;

	/* SSI1 Basic Configuration ssi1 as master */
	/* init SPI1 */
	SSI_InitTypeDef SSI_InitStruct;

	spi_master.Index = 0x1;
	spi_master.spi_dev = SPI_DEV_TABLE[spi_master.Index].SPIx;

	SSI_StructInit(&SSI_InitStruct);
	RCC_PeriphClockCmd(APBPeriph_SPI1, APBPeriph_SPI1_CLOCK, ENABLE);
	Pinmux_Config(SPI1_MOSI, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(SPI1_MISO, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(SPI1_SCLK, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(SPI1_CS, PINMUX_FUNCTION_SPIM);
	/* for cases when SPI0 is as master 
	if( spi_master.Index == 0)  
		SSI_SetRole(spi_master.spi_dev, SSI_MASTER); */
	SSI_InitStruct.SPI_Role = SSI_MASTER;
	SSI_Init(spi_master.spi_dev, &SSI_InitStruct);

	/* set format */
	SSI_SetSclkPhase(spi_master.spi_dev, SclkPhase);
	SSI_SetSclkPolarity(spi_master.spi_dev, SclkPolarity);
	SSI_SetDataFrameSize(spi_master.spi_dev, DataFrameSize-1);

	/* set frequency */
	SSI_SetBaudDiv(spi_master.spi_dev, ClockDivider); // IpClk of SPI1 is 50MHz, IpClk of SPI0 is 100MHz

	_memset(MasterTxBuf, 0, TEST_BUF_SIZE);
	for(i = 0; i < TEST_BUF_SIZE;i++) {
		*((u8*)MasterTxBuf + i) = i;
		}

	DiagPrintf("----------------------------------------\n");
	
	MasterTxDone = 0;

	SSI_SetDmaEnable(spi_master.spi_dev, ENABLE, BIT_SHIFT_DMACR_TDMAE);
	SSI_TXGDMA_Init(spi_master.Index, &spi_master.SSITxGdmaInitStruct, &spi_master, 
		(IRQ_FUN) Ssi_dma_tx_irq, (u8*) MasterTxBuf, TEST_BUF_SIZE);
	NVIC_SetPriority(GDMA_GetIrqNum(0, spi_master.SSITxGdmaInitStruct.GDMA_ChNum), 10);  


	i=0;
	while(MasterTxDone == 0) {
		DelayMs(100);
		i++;
		if (i>150) {
			DiagPrintf("SPI Timeout\r\n");
			break;
		}
	}

	Spi_free(&spi_master);


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
	if(xTaskCreate(spi_singleblock_task, ((const char*)"spi_singleblock_task"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		DiagPrintf("\n\r%s xTaskCreate(spi_singleblock_task) failed", __FUNCTION__);

	vTaskStartScheduler();
	while(1){
		vTaskDelay( 1000 / portTICK_RATE_MS );
	}
	
}

