/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2014 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "device.h"
#include "main.h"
#include "Rtl8721d_ssi.h"

#define SPI_IS_AS_MASTER	0
#define TEST_BUF_SIZE		2048
#define DataFrameSize		8
#define ClockDivider 		10
#define TEST_LOOP			100

#define SPI_GPIO_CS0 PA_12
#define SPI_GPIO_CS1 PA_13

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
#if SPI_IS_AS_MASTER
 //SPI1 (S1)
#define SPI1_MOSI  PB_4
#define SPI1_MISO  PB_5
#define SPI1_SCLK  PB_6
#define SPI1_CS    PB_7 
#else
 //SPI0 (S1)
#define SPI0_MOSI  PA_16
#define SPI0_MISO  PA_17
#define SPI0_SCLK  PA_18
#define SPI0_CS    PA_19
#endif

SRAM_NOCACHE_DATA_SECTION u16 TestBuf[TEST_BUF_SIZE];
volatile int TrDone;

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

#if SPI_IS_AS_MASTER
SPI_OBJ spi_master;
#else
SPI_OBJ spi_slave;
#endif

static u32 spi_interrupt(void *Adaptor)
{
	SPI_OBJ *spi_obj=(SPI_OBJ*) Adaptor;
	u32 InterruptStatus = SSI_GetIsr(spi_obj->spi_dev);
	SSI_SetIsrClean(spi_obj->spi_dev, InterruptStatus);

	if (InterruptStatus & (BIT_ISR_TXOIS | BIT_ISR_RXUIS | BIT_ISR_RXOIS | BIT_ISR_MSTIS)) {
		DBG_8195A("[INT] Tx/Rx Warning %x ", InterruptStatus);
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
			TrDone = 1;
		}
	}
	if (InterruptStatus & BIT_ISR_TXEIS) {
		u32 TransLen = 0;
		volatile u32 bus_busy;
		u32 i;

		TransLen = SSI_SendData(spi_obj->spi_dev, spi_obj->TxData, spi_obj->TxLength, spi_obj->Role);
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
			TrDone = 1;

		}
	}
	return 0;
}

void Spi_free(SPI_OBJ* spi_obj)
{
	InterruptDis(spi_obj->IrqNum);
	InterruptUnRegister(spi_obj->IrqNum);
	SSI_INTConfig(spi_obj->spi_dev, (BIT_IMR_RXFIM | BIT_IMR_RXOIM | BIT_IMR_RXUIM), DISABLE);
	SSI_Cmd(spi_obj->spi_dev, DISABLE);
}

void dump_data(const u8 *start, u32 size, char * strHeader)
{
	int row, column, index, index2, max;
	u8 *buf, *line;

	if(!start ||(size==0))
	        return;

	line = (u8*)start;

	/*
	16 bytes per line
	*/
	if (strHeader)
	   DBG_8195A ("%s", strHeader);

	column = size % 16;
	row = (size / 16) + 1;
	for (index = 0; index < row; index++, line += 16) 
	{
		buf = (u8*)line;

		max = (index == row - 1) ? column : 16;
		if ( max==0 ) break; /* If we need not dump this line, break it. */

		DBG_8195A ("\n[%08x] ", line);

		//Hex
		for (index2 = 0; index2 < max; index2++)
		{
		    if (index2 == 8)
		    DBG_8195A ("  ");
		    DBG_8195A ("%02x ", (u8) buf[index2]);
		}

		if (max != 16)
		{
		    if (max < 8)
		        DBG_8195A ("  ");
		    for (index2 = 16 - max; index2 > 0; index2--)
		        DBG_8195A ("   ");
		}

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

void Spi_master_write_stream(SPI_OBJ *spi_obj, char *tx_buffer, uint32_t length)
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

void Spi_slave_read_stream(SPI_OBJ *spi_obj, char *rx_buffer, uint32_t length)
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


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	u32 SclkPhase = SCPH_TOGGLES_IN_MIDDLE; // SCPH_TOGGLES_IN_MIDDLE or SCPH_TOGGLES_AT_START
	u32 SclkPolarity = SCPOL_INACTIVE_IS_LOW; // SCPOL_INACTIVE_IS_LOW or SCPOL_INACTIVE_IS_HIGH
	int Counter = 0;
    int i;

#if SPI_IS_AS_MASTER

	/* init gpio */
	GPIO_InitTypeDef  GPIO_InitStructM1;
	GPIO_InitStructM1.GPIO_Pin = SPI_GPIO_CS0;
	GPIO_InitStructM1.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructM1.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(&GPIO_InitStructM1);

	GPIO_WriteBit(SPI_GPIO_CS0, 1); // Initialize GPIO Pin to high
	GPIO_Direction(SPI_GPIO_CS0, GPIO_Mode_OUT); // Direction: Output
	PAD_PullCtrl(SPI_GPIO_CS0, GPIO_PuPd_NOPULL); // No pull

	/* init gpio */
	GPIO_InitTypeDef  GPIO_InitStructM2;
	GPIO_InitStructM2.GPIO_Pin = SPI_GPIO_CS1;
	GPIO_InitStructM2.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructM2.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(&GPIO_InitStructM2);
	
	GPIO_WriteBit(SPI_GPIO_CS1, 1); // Initialize GPIO Pin to high
	GPIO_Direction(SPI_GPIO_CS1, GPIO_Mode_OUT); // Direction: Output	
	PAD_PullCtrl(SPI_GPIO_CS1, GPIO_PuPd_NOPULL); // No pull

    /* SPI1 is as Master */
	spi_master.Index = 1;
	spi_master.spi_dev = SPI1_DEV;
	spi_master.Role = SSI_MASTER;

	/* init SPI1 */
	SSI_InitTypeDef SSI_InitStructM;
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
	
	spi_master.IrqNum = SPI_DEV_TABLE[spi_master.Index].IrqNum;
	InterruptRegister((IRQ_FUN)spi_interrupt, spi_master.IrqNum, (u32)&spi_master, 10);
	InterruptEn(spi_master.IrqNum, 10);
		
	SSI_Init(spi_master.spi_dev, &SSI_InitStructM);	


	/* set format */
	SSI_SetSclkPhase(spi_master.spi_dev, SclkPhase);
	SSI_SetSclkPolarity(spi_master.spi_dev, SclkPolarity);
	SSI_SetDataFrameSize(spi_master.spi_dev, DataFrameSize-1);
	
	PAD_PullCtrl((u32)SPI1_SCLK, GPIO_PuPd_UP);
	PAD_PullCtrl((u32)SPI_GPIO_CS0, GPIO_PuPd_UP);
	PAD_PullCtrl((u32)SPI_GPIO_CS1, GPIO_PuPd_UP);


	/* set frequency */
	SSI_SetBaudDiv(spi_master.spi_dev, ClockDivider); // IpClk of SPI1 is 50MHz, IpClk of SPI0 is 100MHz


    while (Counter < TEST_LOOP) {
        DBG_8195A("======= Test Loop %d =======\r\n", Counter);

        if(Counter % 2){
            for (i=0;i<TEST_BUF_SIZE;i++) {
                if (DataFrameSize > 8)
					*((u16*)TestBuf + i) = i;
				else
					*((u8*)TestBuf + i) = i;
            }
		GPIO_WriteBit(SPI_GPIO_CS0, 0);
		GPIO_WriteBit(SPI_GPIO_CS1, 1);
            // wait Slave ready
            DelayMs(1000);
        }
        else{
            for (i=0;i<TEST_BUF_SIZE;i++) {
                if (DataFrameSize > 8)
					*((u16*)TestBuf + i) = ~i;
				else
					*((u8*)TestBuf + i) = ~i;
            }

		GPIO_WriteBit(SPI_GPIO_CS0, 1);
		GPIO_WriteBit(SPI_GPIO_CS1, 0);
            // wait Slave ready
            DelayMs(1000);
        } 
	
        DBG_8195A("SPI Master Write Test==>\r\n");
        TrDone = 0;

 		Spi_master_write_stream(&spi_master, TestBuf, TEST_BUF_SIZE);


        i=0;
        DBG_8195A("SPI Master Wait Write Done...\r\n");
        while(TrDone == 0) {
            DelayMs(100);
            i++;
        }
        DBG_8195A("SPI Master Write Done!!\r\n");
		if(Counter % 2){
			GPIO_WriteBit(SPI_GPIO_CS0, 1);
			GPIO_WriteBit(SPI_GPIO_CS1, 0);
		} 		
		else{
			GPIO_WriteBit(SPI_GPIO_CS0, 0);
			GPIO_WriteBit(SPI_GPIO_CS1, 1);
			}
		DelayMs(4000);
		Counter++;
    }
	/* free spi master */
	Spi_free(&spi_master);

    DBG_8195A("SPI Master Test <==\r\n");


#else
	spi_slave.Index = 0;
	spi_slave.spi_dev = SPI0_DEV;
	spi_slave.Role = SSI_SLAVE;
	/* init spi slave */
	SSI_InitTypeDef SSI_InitStructS;
	SSI_StructInit(&SSI_InitStructS);
	RCC_PeriphClockCmd(APBPeriph_SPI0, APBPeriph_SPI0_CLOCK, ENABLE);
	Pinmux_Config(SPI0_MOSI, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(SPI0_MISO, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(SPI0_SCLK, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(SPI0_CS, PINMUX_FUNCTION_SPIS);
	
	SSI_SetRole(spi_slave.spi_dev, SSI_SLAVE);
	SSI_InitStructS.SPI_Role = SSI_SLAVE;
	spi_slave.IrqNum = SPI_DEV_TABLE[spi_slave.Index].IrqNum;
	InterruptRegister((IRQ_FUN)spi_interrupt, spi_slave.IrqNum, (u32)&spi_slave, 10);
	InterruptEn(spi_slave.IrqNum, 10);
	SSI_Init(spi_slave.spi_dev, &SSI_InitStructS);

	/* set format */
	SSI_SetSclkPhase(spi_slave.spi_dev, SclkPhase);
	SSI_SetSclkPolarity(spi_slave.spi_dev, SclkPolarity);
	SSI_SetDataFrameSize(spi_slave.spi_dev, DataFrameSize-1);

	if (SclkPolarity == SCPOL_INACTIVE_IS_LOW) {
	PAD_PullCtrl((u32)SPI0_SCLK, GPIO_PuPd_DOWN);}
	

    while (SSI_Busy(spi_slave.spi_dev)) {
        DBG_8195A("Wait SPI Bus Ready...\r\n");
        DelayMs(1000);
    }

    while (Counter < TEST_LOOP) {
        DBG_8195A("======= Test Loop %d =======\r\n", Counter);
        _memset(TestBuf, 0, TEST_BUF_SIZE);
		DBG_8195A("SPI Slave Read Test ==>\r\n");
		
        TrDone = 0;

		/* flush rx fifo */
		Spi_flush_rx_fifo(&spi_slave);

		Spi_slave_read_stream(&spi_slave, TestBuf, TEST_BUF_SIZE);


		i=0;
		DBG_8195A("SPI Slave Wait Read Done...\r\n");
		while(TrDone == 0) {
			DelayMs(100);
			i++;

			if (i>150) {
				DBG_8195A("SPI Slave Wait Timeout\r\n");
				break;
			}
		}

		dump_data(TestBuf, TEST_BUF_SIZE, "SPI Slave Read Data:");

		Counter++;
    }
	/* free spi slave */
	Spi_free(&spi_slave);
	
#endif

    DBG_8195A("SPI Demo finished.\n");
    for(;;);
}
