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

#define DataFrameSize		8
#define TEST_BUF_SIZE	8400
#define BLOCK_SIZE 		2048  //number of bytes in a block

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

SRAM_NOCACHE_DATA_SECTION u8 MasterTxBuf[TEST_BUF_SIZE];

SPI_TypeDef *spi_master;
GDMA_InitTypeDef SSITxGdmaInitStruct;

volatile int MasterTxDone;
volatile int MultiTxDone;
u32 Gdma_BlockLen = 0;
static u32 If_single = TEST_BUF_SIZE % BLOCK_SIZE;


/* GDMA single block IRQ Handler */
void Gdma_singleblock_irq(void *Data)
{
	PGDMA_InitTypeDef GDMA_InitStruct = (PGDMA_InitTypeDef) Data;

	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
	GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, DISABLE);

	/*  Call user TX complete callback */
	MasterTxDone = 1;

	/* Set SSI DMA Disable */
	SSI_SetDmaEnable(spi_master, DISABLE, BIT_SHIFT_DMACR_TDMAE);
	GDMA_ChnlFree(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
}

void Gdma_multiblock_irq(VOID *Data)
{
	PGDMA_InitTypeDef GDMA_InitStruct = (PGDMA_InitTypeDef) Data;
	u8 *pSrcData = NULL, *pDstData = NULL;
	u8 IsrTypeMap = 0;
	u8 this_is_last_two = 0;

	if (GDMA_InitStruct->MaxMuliBlock == GDMA_InitStruct->MuliBlockCunt + 2)
		this_is_last_two = 1;

	// Clean Auto Reload Bit
	if (this_is_last_two) {
		GDMA_ChCleanAutoReload(0, GDMA_InitStruct->GDMA_ChNum, CLEAN_RELOAD_SRC_DST);
	}
	pSrcData = (u8*)(GDMA_InitStruct->GDMA_SrcAddr + BLOCK_SIZE*(GDMA_InitStruct->MuliBlockCunt));
	pDstData = (u8*)GDMA_InitStruct->GDMA_DstAddr ;
	

	/* reload cache from sram before use the DMA destination data */
	DCache_Invalidate(((u32)pDstData & CACHE_LINE_ADDR_MSK), (BLOCK_SIZE + CACHE_LINE_SIZE));

//	for(int num = 0;num < BLOCK_SIZE; num++){
//		DBG_8195A( "\r\src: %d\n" ,*(pSrcData+num));  
//		}

	DCache_Clean(pDstData, (BLOCK_SIZE + CACHE_LINE_SIZE));

	//Clear Pending ISR, next block will start transfer
	IsrTypeMap = GDMA_ClearINT(0, GDMA_InitStruct->GDMA_ChNum);

	if (IsrTypeMap & BlockType) {
//		DBG_8195A("DMA Block %d\n",GDMA_InitStruct->MuliBlockCunt);
		GDMA_InitStruct->MuliBlockCunt++;
	}

	//last IRQ is TransferType in multi-block
	if (IsrTypeMap & TransferType) {
//		DBG_8195A("DMA Block %d\n",GDMA_InitStruct->MuliBlockCunt);
//		DBG_8195A("DMA data complete MaxMuliBlock:%d \n", GDMA_InitStruct->MaxMuliBlock);
		if (!If_single) {
			MasterTxDone = 1;
		} else {
			MultiTxDone = 1;
		}
		GDMA_ChnlFree(0, GDMA_InitStruct->GDMA_ChNum);
	}
}

BOOL SSI_Multi_TXGDMA_Init(PGDMA_InitTypeDef GDMA_InitStruct, void *CallbackData, IRQ_FUN CallbackFunc, u8 *pTxData, u32 Length)
{
	SPI_TypeDef *SPIx = SPI_DEV_TABLE[1].SPIx;
	u8 GdmaChnl;
	IRQn_Type   IrqNum;

	assert_param(GDMA_InitStruct != NULL);

	GdmaChnl = GDMA_ChnlAlloc(0, CallbackFunc, (u32)CallbackData, 12);//ACUT is 0x10, BCUT is 12
	if (GdmaChnl == 0xFF) {
		// No Available DMA channel
		return _FALSE;
	}

	_memset((void *)GDMA_InitStruct, 0, sizeof(GDMA_InitTypeDef));

	GDMA_InitStruct->GDMA_DIR      = TTFCMemToPeri;
	GDMA_InitStruct->GDMA_DstHandshakeInterface   = SPI_DEV_TABLE[1].Tx_HandshakeInterface;
	GDMA_InitStruct->GDMA_DstAddr = (u32)&SPI_DEV_TABLE[1].SPIx->DR;
	GDMA_InitStruct->GDMA_Index   = 0;
	GDMA_InitStruct->GDMA_ChNum       = GdmaChnl;
	GDMA_InitStruct->GDMA_IsrType = (BlockType|TransferType|ErrType);

	GDMA_InitStruct->GDMA_SrcMsize   = MsizeOne;
	GDMA_InitStruct->GDMA_DstMsize  = MsizeFour;
	GDMA_InitStruct->GDMA_SrcDataWidth = TrWidthFourBytes;
	GDMA_InitStruct->GDMA_DstDataWidth = TrWidthOneByte;
	GDMA_InitStruct->GDMA_DstInc = NoChange;
	GDMA_InitStruct->GDMA_SrcInc = IncType;
	
	/*  Cofigure GDMA transfer */
	if (DataFrameSize > 8) {
		/*  16~9 bits mode */
		if (((Length & 0x03)==0) && (((u32)(pTxData) & 0x03)==0)) {
			/*  4-bytes aligned, move 4 bytes each transfer */
			GDMA_InitStruct->GDMA_SrcMsize   = MsizeFour;
			GDMA_InitStruct->GDMA_SrcDataWidth = TrWidthFourBytes;
			GDMA_InitStruct->GDMA_DstMsize  = MsizeEight;
			GDMA_InitStruct->GDMA_DstDataWidth = TrWidthTwoBytes;
		} else if (((Length & 0x01)==0) && (((u32)(pTxData) & 0x01)==0)) {
			/*  2-bytes aligned, move 2 bytes each transfer */
			GDMA_InitStruct->GDMA_SrcMsize   = MsizeEight;
			GDMA_InitStruct->GDMA_SrcDataWidth = TrWidthTwoBytes;
			GDMA_InitStruct->GDMA_DstMsize  = MsizeEight;
			GDMA_InitStruct->GDMA_DstDataWidth = TrWidthTwoBytes;
		} else {
			DBG_8195A("SSI_TXGDMA_Init: Aligment Err: pTxData=0x%x,  Length=%d\n", pTxData, Length);
			return _FALSE;
		}
	} else {
		/*  8~4 bits mode */
		if (((Length & 0x03)==0) && (((u32)(pTxData) & 0x03)==0)) {
			/*  4-bytes aligned, move 4 bytes each transfer */
			GDMA_InitStruct->GDMA_SrcMsize   = MsizeOne;
			GDMA_InitStruct->GDMA_SrcDataWidth = TrWidthFourBytes;
		} else {
			GDMA_InitStruct->GDMA_SrcMsize   = MsizeFour;
			GDMA_InitStruct->GDMA_SrcDataWidth = TrWidthOneByte;
		}
		GDMA_InitStruct->GDMA_DstMsize  = MsizeFour;
		GDMA_InitStruct->GDMA_DstDataWidth =  TrWidthOneByte;
	}
	GDMA_InitStruct->GDMA_BlockSize = BLOCK_SIZE  >> GDMA_InitStruct->GDMA_SrcDataWidth; //based on src width
	assert_param(GDMA_InitStruct->GDMA_BlockSize <= 4096);

//	DBG_8195A("BlockSize = %d\n", GDMA_InitStruct->GDMA_BlockSize);

	GDMA_ChnlRegister(0, GDMA_InitStruct->GDMA_ChNum);
	GDMA_InitStruct->MuliBlockCunt = 0;
	GDMA_InitStruct->MaxMuliBlock = Length / BLOCK_SIZE;  //number of blocks
	GDMA_InitStruct->GDMA_ReloadSrc = 0;
	GDMA_InitStruct->GDMA_ReloadDst = 1;
	GDMA_InitStruct->GDMA_SrcAddr = (u32)pTxData;

	IrqNum = GDMA_GetIrqNum(0, GDMA_InitStruct->GDMA_ChNum);
	InterruptRegister((IRQ_FUN)Gdma_multiblock_irq, IrqNum, (u32)GDMA_InitStruct, 10);
	InterruptEn(IrqNum, 10);

	/*  Enable GDMA for TX */
	GDMA_Init(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, GDMA_InitStruct);
	GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, ENABLE);

	return _TRUE;
}

void Spi_free(SPI_TypeDef *spi_dev)
{
	PGDMA_InitTypeDef GDMA_Tx = &SSITxGdmaInitStruct;
	
	/* Set SSI Tx DMA Disable */
	SSI_SetDmaEnable(spi_dev, DISABLE, BIT_SHIFT_DMACR_TDMAE);
	
	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_Tx->GDMA_Index, GDMA_Tx->GDMA_ChNum);
	GDMA_ChCleanAutoReload(GDMA_Tx->GDMA_Index, GDMA_Tx->GDMA_ChNum, CLEAN_RELOAD_SRC_DST);
	GDMA_Cmd(GDMA_Tx->GDMA_Index, GDMA_Tx->GDMA_ChNum, DISABLE);
	GDMA_ChnlFree(GDMA_Tx->GDMA_Index, GDMA_Tx->GDMA_ChNum);
	
	SSI_Cmd(spi_dev, DISABLE);
}

/**
  * @brief  Main program.
  * @param  None 
  * @retval None
  */

void main(void)
{
	int i = 0;	

	 /* SSI1 Basic Configuration ssi1 as master */
	/* init master */
	spi_master = SPI_DEV_TABLE[1].SPIx;
	SSI_InitTypeDef SSI_InitStruct;
	SSI_StructInit(&SSI_InitStruct);
	SSI_InitStruct.SPI_SclkPhase  = SCPH_TOGGLES_IN_MIDDLE;
	SSI_InitStruct.SPI_SclkPolarity = SCPOL_INACTIVE_IS_LOW;
	SSI_InitStruct.SPI_DataFrameSize = DataFrameSize - 1;
	SSI_InitStruct.SPI_ClockDivider  = 10; // IpClk of SPI1 is 50MHz, IpClk of SPI0 is 100MHz

	RCC_PeriphClockCmd(APBPeriph_SPI1, APBPeriph_SPI1_CLOCK, ENABLE);
	Pinmux_Config(SPI1_MOSI, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(SPI1_MISO, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(SPI1_SCLK, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(SPI1_CS, PINMUX_FUNCTION_SPIM);

	//SSI_SetRole(SPI0_DEV, SSI_MASTER); // for cases when SPI0 is as master
	SSI_InitStruct.SPI_Role = SSI_MASTER;
	SSI_Init(spi_master, &SSI_InitStruct);

	_memset(MasterTxBuf, 0, TEST_BUF_SIZE);	
	for(i = 0; i < TEST_BUF_SIZE;i++) {
		*((u8*)MasterTxBuf + i) = i;
	}
	
	DBG_8195A("----------------------------------------\n");

	MasterTxDone = 0;
	MultiTxDone  = 0;

	SSI_SetDmaEnable(spi_master, ENABLE, BIT_SHIFT_DMACR_TDMAE);
	SSI_Multi_TXGDMA_Init(&SSITxGdmaInitStruct, spi_master, (IRQ_FUN) Gdma_multiblock_irq, MasterTxBuf, TEST_BUF_SIZE);
	NVIC_SetPriority(GDMA_GetIrqNum(0, SSITxGdmaInitStruct.GDMA_ChNum), 10);

	/*using single block to transfer the remaining data*/
	i = 0;
	if (If_single) {
		while(MultiTxDone == 0) {
			DelayMs(5);
			i++;
			if (i>3000) {
				DBG_8195A("SPI Multi Block Timeout\r\n");
			break;
			}
		}
		SSI_TXGDMA_Init(1, &SSITxGdmaInitStruct, &SSITxGdmaInitStruct, (IRQ_FUN) Gdma_singleblock_irq, (u8*) (MasterTxBuf + TEST_BUF_SIZE - If_single), If_single);
		NVIC_SetPriority(GDMA_GetIrqNum(0, SSITxGdmaInitStruct.GDMA_ChNum), 10);
	}

	i=0;
	while(MasterTxDone == 0) {
		DelayMs(100);
		i++;
		if (i>150) {
		    DBG_8195A("SPI Timeout\r\n");
		    break;
		}
	}
	
	Spi_free(spi_master);

	DBG_8195A("SPI Demo finished.\n");

	for(;;);

}

