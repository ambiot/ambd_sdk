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
#include "spi_api.h"
#include "spi_ex_api.h"
#include "wait_api.h"

#define DataFrameSize	8
#define dfs_mask		0xFF
#define Mode			0
#define SCLK_FREQ		100000
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

SRAM_NOCACHE_DATA_SECTION u16 MasterTxBuf[TEST_BUF_SIZE];
SRAM_NOCACHE_DATA_SECTION u16 MasterRxBuf[TEST_BUF_SIZE];
SRAM_NOCACHE_DATA_SECTION u16 SlaveTxBuf[TEST_BUF_SIZE];
SRAM_NOCACHE_DATA_SECTION u16 SlaveRxBuf[TEST_BUF_SIZE];

volatile int MasterTxDone;
volatile int MasterRxDone;
volatile int SlaveTxDone;
volatile int SlaveRxDone;

void Master_tr_done_callback(void *pdata, SpiIrq event)
{
	switch(event){
		case SpiRxIrq:
			MasterRxDone = 1;
			break;
		case SpiTxIrq:
			MasterTxDone = 1;
			break;
		default:
			DiagPrintf("unknown interrput evnent!\n");
	}
}

void Slave_tr_done_callback(void *pdata, SpiIrq event)
{
	switch(event){
		case SpiRxIrq:
			SlaveRxDone = 1;
			break;
		case SpiTxIrq:
			SlaveTxDone = 1;
			break;
		default:
			DiagPrintf("unknown interrput evnent!\n");
	}
}

BOOL SsiDataCompare(u16 *pSrc, u16 *pDst, u32 Length)
{
	int Index;
	u8 *PSrc_8 = (u8*)pSrc;
	u8 *PDst_8 = (u8*)pDst;
	u8 res = _TRUE;
	
	if(DataFrameSize > 8) {
		for (Index = 0; Index < Length; ++Index){
			if ((pSrc[Index] & dfs_mask)!= pDst[Index]) {
				DiagPrintf("%x: %x ---- %x\n",Index, pSrc[Index] & dfs_mask, pDst[Index]);
				res = _FALSE;
			}
		}
	} else {
		for (Index = 0; Index < Length; ++Index){
			if((PSrc_8[Index] & dfs_mask)!= PDst_8[Index]) {
				DiagPrintf("%x: %x ---- %x\n",Index, PSrc_8[Index] & dfs_mask, PDst_8[Index]);
				res = _FALSE;
			}
		}
	}
	return res;
}

void SsiPrint(u16 *pSrc, u16 *pDst, u32 Length)
{
	int Index;
	u8 *PSrc_8 = (u8*)pSrc;
	u8 *PDst_8 = (u8*)pDst;

	for(Index = 0;Index < Length; Index++){
		if(DataFrameSize > 8)
			DiagPrintf("%x: %x ---- %x\n",Index, pSrc[Index] & dfs_mask, pDst[Index]);
		else
			DiagPrintf("%x: %x ---- %x\n",Index, PSrc_8[Index] & dfs_mask, PDst_8[Index]);
	}
} 

spi_t spi_master;
spi_t spi_slave;

void spi_interrupt_task(void* param)
{

	/* SPI1 is as Master */
	spi_master.spi_idx=MBED_SPI1;
	spi_init(&spi_master, SPI1_MOSI, SPI1_MISO, SPI1_SCLK, SPI1_CS);
	spi_format(&spi_master, DataFrameSize, Mode, 0);
	spi_frequency(&spi_master, SCLK_FREQ);
	/* SPI0 is as Slave */
	spi_slave.spi_idx=MBED_SPI0;
	spi_init(&spi_slave,  SPI0_MOSI, SPI0_MISO, SPI0_SCLK, SPI0_CS);
	spi_format(&spi_slave, DataFrameSize, Mode, 1);

	int i=0;
	int result1 = 1;
	int result2 = 1;
	int result3 = 1;
	u32 trans_bytes = (DataFrameSize > 8) ? (TEST_BUF_SIZE * 2) : TEST_BUF_SIZE;

	_memset(MasterTxBuf, 0, TEST_BUF_SIZE);
	_memset(MasterRxBuf, 0, TEST_BUF_SIZE);
	_memset(SlaveTxBuf, 0, TEST_BUF_SIZE);
	_memset(SlaveRxBuf, 0, TEST_BUF_SIZE);
	
	for(i = 0; i < TEST_BUF_SIZE;i++) {
		if (DataFrameSize > 8)
			*((u16*)MasterTxBuf + i) = i;
		else
			*((u8*)MasterTxBuf + i) = i;
		}
	
	for(i = 0; i < TEST_BUF_SIZE;i++) {
		if (DataFrameSize > 8)
			*((u16*)SlaveTxBuf + i) = i;
		else
			*((u8*)SlaveTxBuf + i) = i;
		}


	/**
	* Master write/read, Slave read/write
	*/
	DiagPrintf("------Master write/read, Slave read/write-------\n");
	
		spi_irq_hook(&spi_master,(spi_irq_handler) Master_tr_done_callback, (uint32_t)&spi_master);
		spi_irq_hook(&spi_slave,(spi_irq_handler) Slave_tr_done_callback, (uint32_t)&spi_slave);
		
		MasterRxDone = 0;
		SlaveRxDone = 0;

		spi_slave_read_stream(&spi_slave, (char*)SlaveRxBuf, trans_bytes);
		spi_slave_write_stream(&spi_slave, (char*)SlaveTxBuf, trans_bytes);
		spi_master_write_read_stream(&spi_master, (char*)MasterTxBuf, (char*)MasterRxBuf, trans_bytes);
		

		i=0;
		while((MasterRxDone && SlaveRxDone) == 0) {
			wait_ms(100);
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
	
		spi_irq_hook(&spi_master,(spi_irq_handler) Master_tr_done_callback, (uint32_t)&spi_master);

		MasterRxDone = 0;

		spi_flush_rx_fifo(&spi_master);

		spi_slave_write_stream(&spi_slave, (char*)SlaveTxBuf, trans_bytes);
		spi_master_read_stream(&spi_master, (char*)MasterRxBuf, trans_bytes);

		i=0;
		while(MasterRxDone == 0) {
			wait_ms(100);
			i++;
			if (i>150) {
				DiagPrintf("SPI Master Wait Timeout\r\n");
				break;
			}
		}

		SsiPrint(SlaveTxBuf, MasterRxBuf, TEST_BUF_SIZE);
		result3 = SsiDataCompare(SlaveTxBuf, MasterRxBuf, TEST_BUF_SIZE);

	DiagPrintf("\r\nResult is %s\r\n", (result1 && result2 && result3) ? "success" : "fail");
	
	spi_free(&spi_master);
	spi_free(&spi_slave);

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
	if(xTaskCreate(spi_interrupt_task, ((const char*)"spi_interrupt_task"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		DiagPrintf("\n\r%s xTaskCreate(spi_interrupt_task) failed", __FUNCTION__);

        vTaskStartScheduler();
	while(1){
		vTaskDelay( 1000 / portTICK_RATE_MS );
	}
	
}