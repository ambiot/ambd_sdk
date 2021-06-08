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
#define dfs_mask		0xFF
#define ClockDivider	10
#define TEST_BUF_SIZE	512

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

SRAM_NOCACHE_DATA_SECTION u8 MasterTxBuf[TEST_BUF_SIZE];
SRAM_NOCACHE_DATA_SECTION u8 MasterRxBuf[TEST_BUF_SIZE];
SRAM_NOCACHE_DATA_SECTION u8 SlaveTxBuf[TEST_BUF_SIZE];
SRAM_NOCACHE_DATA_SECTION u8 SlaveRxBuf[TEST_BUF_SIZE];

volatile int MasterTxDone;
volatile int MasterRxDone;
volatile int SlaveTxDone;
volatile int SlaveRxDone;


typedef struct {
	IRQn_Type   IrqNum;
	SPI_TypeDef *spi_dev;
	
	void *RxData;
	void *TxData;
	u32  RxLength;
	u32  TxLength;

	u32   Index;
	u32   Role;
}SPI_OBJ;

SPI_OBJ spi_master;
SPI_OBJ spi_slave;

static u32  ssi_interrupt(void *Adaptor)
{
	SPI_OBJ* spi_obj = (SPI_OBJ*) Adaptor;
	u32 InterruptStatus = SSI_GetIsr(spi_obj->spi_dev);

	SSI_SetIsrClean(spi_obj->spi_dev, InterruptStatus);

	if (InterruptStatus & (BIT_ISR_TXOIS | BIT_ISR_RXUIS | BIT_ISR_RXOIS | BIT_ISR_MSTIS)) {
		DBG_PRINTF(MODULE_SPI, LEVEL_INFO, "[INT] Tx/Rx Warning %x \n", InterruptStatus);
	}

	if ((InterruptStatus & BIT_ISR_RXFIS) ) {
		u32 TransLen = 0;

		TransLen = SSI_ReceiveData(spi_obj->spi_dev, spi_obj->RxData, spi_obj->RxLength);
		spi_obj->RxLength -= TransLen;
		if (DataFrameSize > 8) {
			// 16~9 bits mode
			spi_obj->RxData = (void*)(((u16*)spi_obj->RxData) + TransLen);
		} else {
			// 8~4 bits mode
			spi_obj->RxData = (void*)(((u8*)spi_obj->RxData) + TransLen);
		}
		
		if (spi_obj->RxLength == 0) {
			SSI_INTConfig(spi_obj->spi_dev, (BIT_IMR_RXFIM | BIT_IMR_RXOIM | BIT_IMR_RXUIM), DISABLE);
			if (spi_obj->Index == 0)
				SlaveRxDone = 1;
			else
				MasterRxDone = 1;
		}
	}

	if (InterruptStatus & BIT_ISR_TXEIS) {
		u32 TransLen = 0;
		volatile u32 bus_busy;
		u32 i;

		TransLen = SSI_SendData(spi_obj->spi_dev, spi_obj->TxData,
			spi_obj->TxLength, spi_obj->Role);

		spi_obj->TxLength -= TransLen;
		if (spi_obj->TxData != NULL) {
			if (DataFrameSize > 8) {
				// 16~9 bits mode
				spi_obj->TxData = (void*)(((u16*)spi_obj->TxData) + TransLen);
			} else {
				// 8~4 bits mode
				spi_obj->TxData = (void*)(((u8*)spi_obj->TxData) + TransLen);
			}
		}
		/* all data write into fifo */
		if (spi_obj->TxLength == 0) {
			SSI_INTConfig(spi_obj->spi_dev, (BIT_IMR_TXOIM | BIT_IMR_TXEIM), DISABLE);
			// If it's not a dummy TX for master read SPI, then call the TX_done callback
			if (spi_obj->TxData != NULL) {
			if (spi_obj->Index == 0)
				SlaveTxDone = 1;
			else
				MasterTxDone = 1;
			}
		}
	}

	return 0;
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
		DBG_8195A("%x: %x ---- %x\n",Index, pSrc[Index] & dfs_mask, pDst[Index]);
	}
}

void Spi_free(SPI_OBJ* spi_obj)
{
	InterruptDis(spi_obj->IrqNum);
	InterruptUnRegister(spi_obj->IrqNum);
	SSI_INTConfig(spi_obj->spi_dev, (BIT_IMR_RXFIM | BIT_IMR_RXOIM | BIT_IMR_RXUIM), DISABLE);
	SSI_Cmd(spi_obj->spi_dev, DISABLE);
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

void Spi_slave_write_stream(SPI_OBJ *spi_obj, char *tx_buffer, uint32_t length)
{
	assert_param(length != 0);

	if (DataFrameSize > 8) {
		/*  16~9 bits mode */
		spi_obj->TxLength = length >> 1; // 2 bytes(16 bit) every transfer
	} else {
		/*  8~4 bits mode */
		spi_obj->TxLength = length; // 1 byte(8 bit) every transfer
	}
	spi_obj->TxData = (void*)tx_buffer;
	SSI_INTConfig(spi_obj->spi_dev, (BIT_IMR_TXOIM | BIT_IMR_TXEIM), ENABLE);
}

int32_t Spi_slave_read_stream(SPI_OBJ *spi_obj, char *rx_buffer, uint32_t length)
{
	assert_param(length != 0);

	/*  As a Slave mode, if the peer(Master) side is power off, the BUSY flag is always on */
	if (SSI_Busy(spi_obj->spi_dev)) {		
		DBG_PRINTF(MODULE_SPI, LEVEL_WARN, "HalSsiIntRead: SSI is busy\n");
		return _FALSE;
	}

	if (DataFrameSize > 8) {
		/*  16~9 bits mode */
		spi_obj->RxLength = length >> 1; // 2 bytes(16 bit) every transfer
	} else {
		/*  8~4 bits mode */
		spi_obj->RxLength = length; // 1 byte(8 bit) every transfer
	}
	spi_obj->RxData = (void*)rx_buffer;
	SSI_INTConfig(spi_obj->spi_dev, (BIT_IMR_RXFIM | BIT_IMR_RXOIM | BIT_IMR_RXUIM), ENABLE);
}

void Spi_master_write_read_stream(SPI_OBJ *spi_obj, char *tx_buffer, char *rx_buffer, uint32_t length)
{
	assert_param(length != 0);

	// wait bus idle
	while(SSI_Busy(spi_obj->spi_dev));

	if (DataFrameSize > 8) {
		/*  16~9 bits mode */
		spi_obj->RxLength = length >> 1; // 2 bytes(16 bit) every transfer
		spi_obj->TxLength = length >> 1; // 2 bytes(16 bit) every transfer
	} else {
		/*  8~4 bits mode */
		spi_obj->RxLength = length; // 1 byte(8 bit) every transfer
		spi_obj->TxLength = length; // 1 byte(8 bit) every transfer
	}
	spi_obj->RxData = rx_buffer;
	spi_obj->TxData = (void*)tx_buffer;
	SSI_INTConfig(spi_obj->spi_dev, (BIT_IMR_RXFIM | BIT_IMR_RXOIM | BIT_IMR_RXUIM | BIT_IMR_TXOIM | BIT_IMR_TXEIM), ENABLE);
}

void Spi_master_read_stream(SPI_OBJ *spi_obj, char *rx_buffer, uint32_t length)
{
	assert_param(length != 0);
	
	// wait bus idle
	while(SSI_Busy(spi_obj->spi_dev));

	if (DataFrameSize > 8) {
		/*  16~9 bits mode */
		spi_obj->RxLength = length >> 1; // 2 bytes(16 bit) every transfer
	} else {
		/*  8~4 bits mode */
		spi_obj->RxLength = length; // 1 byte(8 bit) every transfer
	}
	spi_obj->RxData = rx_buffer;
	SSI_INTConfig(spi_obj->spi_dev, (BIT_IMR_RXFIM | BIT_IMR_RXOIM | BIT_IMR_RXUIM), ENABLE);

		/* as Master mode, it need to push data to TX FIFO to generate clock out
		then the slave can transmit data out */
		// send some dummy data out

	if (DataFrameSize > 8) {
		/*  16~9 bits mode */
		spi_obj->TxLength = length >> 1; // 2 bytes(16 bit) every transfer
	} else {
		/*  8~4 bits mode */
		spi_obj->TxLength = length; // 1 byte(8 bit) every transfer
	}
	spi_obj->TxData = (void*)NULL;
	SSI_INTConfig(spi_obj->spi_dev, (BIT_IMR_TXOIM | BIT_IMR_TXEIM), ENABLE);
}

void spi_interrupt_task(void* param)
{

	u32 SclkPhase = SCPH_TOGGLES_IN_MIDDLE; // SCPH_TOGGLES_IN_MIDDLE or SCPH_TOGGLES_AT_START
	u32 SclkPolarity = SCPOL_INACTIVE_IS_LOW; // SCPOL_INACTIVE_IS_LOW or SCPOL_INACTIVE_IS_HIGH
	int i = 0;
	int result1 = 1;
	int result2 = 1;
	int result3 = 1;

    /* SPI1 is as Master */
	/* init SPI1 */
	spi_master.Index = 0x1;

	SSI_InitTypeDef SSI_InitStructM;
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
	spi_master.Role = SSI_MASTER;

	spi_master.IrqNum = SPI_DEV_TABLE[spi_master.Index].IrqNum;
	InterruptRegister((IRQ_FUN)ssi_interrupt, spi_master.IrqNum, (u32)&spi_master, 10);
	InterruptEn(spi_master.IrqNum, 10);
		
	SSI_Init(spi_master.spi_dev, &SSI_InitStructM);

	/* set format */
	SSI_SetSclkPhase(spi_master.spi_dev, SclkPhase);
	SSI_SetSclkPolarity(spi_master.spi_dev, SclkPolarity);
	SSI_SetDataFrameSize(spi_master.spi_dev, DataFrameSize-1);

	/* set frequency */
	SSI_SetBaudDiv(SPI1_DEV, ClockDivider); // IpClk of SPI1 is 50MHz, IpClk of SPI0 is 100MHz

	/* SPI0 is as Slave */
	/* init SPI0 */
	spi_slave.Index = 0x0;
	spi_slave.spi_dev = SPI_DEV_TABLE[spi_slave.Index].SPIx;

	SSI_InitTypeDef SSI_InitStructS;
	SSI_StructInit(&SSI_InitStructS);

	RCC_PeriphClockCmd(APBPeriph_SPI0, APBPeriph_SPI0_CLOCK, ENABLE);
	Pinmux_Config(SPI0_MOSI, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(SPI0_MISO, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(SPI0_SCLK, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(SPI0_CS, PINMUX_FUNCTION_SPIS);

	SSI_SetRole(spi_slave.spi_dev, SSI_SLAVE);
	SSI_InitStructS.SPI_Role = SSI_SLAVE;
	spi_slave.Role = SSI_SLAVE;

	spi_slave.IrqNum = SPI_DEV_TABLE[spi_slave.Index].IrqNum;
	InterruptRegister((IRQ_FUN)ssi_interrupt, spi_slave.IrqNum, (u32)&spi_slave, 10);
	InterruptEn(spi_slave.IrqNum, 10);
		
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
    DBG_8195A("------Master write/read, Slave read/write-------\n");
			
		MasterRxDone = 0;
		SlaveRxDone = 0;

		Spi_slave_read_stream(&spi_slave, SlaveRxBuf, TEST_BUF_SIZE);
		Spi_slave_write_stream(&spi_slave, SlaveTxBuf, TEST_BUF_SIZE);
		Spi_master_write_read_stream(&spi_master, MasterTxBuf, MasterRxBuf, TEST_BUF_SIZE);
		
		i=0;
	    while((MasterRxDone && SlaveRxDone) == 0) {
	        DelayMs(100);
	        i++;
	        if (i>150) {
	            DBG_8195A("SPI Slave Wait Timeout\r\n");
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
    DBG_8195A("-----------Master read, Slave write------------\n");
      
		MasterRxDone = 0;

		/* flush rx fifo */
		Spi_flush_rx_fifo(&spi_master);

	    Spi_slave_write_stream(&spi_slave, SlaveTxBuf, TEST_BUF_SIZE);
	    Spi_master_read_stream(&spi_master, MasterRxBuf, TEST_BUF_SIZE);

		i=0;
		while(MasterRxDone == 0) {
			DelayMs(100);
			i++;
			if (i>150) {
				DBG_8195A("SPI Master Wait Timeout\r\n");
				break;
			}
		}

		SsiPrint(SlaveTxBuf, MasterRxBuf, TEST_BUF_SIZE);
		result3 = SsiDataCompare(SlaveTxBuf, MasterRxBuf, TEST_BUF_SIZE);

	DBG_8195A("\r\nResult is %s\r\n", (result1 && result2 && result3) ? "success" : "fail");
	
	Spi_free(&spi_master);
	Spi_free(&spi_slave);

    DBG_8195A("SPI Demo finished.\n");

    vTaskDelete(NULL);

}

/**
  * @brief  Main program.
  * @param  None 
  * @retval None
  */
void main(void)
{
	if(xTaskCreate(spi_interrupt_task, ((const char*)"spi_interrupt_task"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(spi_interrupt_task) failed", __FUNCTION__);

        vTaskStartScheduler();
	while(1){
		vTaskDelay( 1000 / portTICK_RATE_MS );
	}
	
}

