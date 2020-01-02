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
#include "spi_api.h"
#include "spi_ex_api.h"
#include "gpio_api.h"

#define SPI_IS_AS_MASTER    1
#define TEST_BUF_SIZE       2048
#define SCLK_FREQ           1000000
#define TEST_LOOP           100

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

gpio_t spi_cs0;
gpio_t spi_cs1;

extern void wait_ms(int);

char TestBuf[TEST_BUF_SIZE];
volatile int TrDone;

void master_tr_done_callback(void *pdata, SpiIrq event)
{
    TrDone = 1;
}

void slave_tr_done_callback(void *pdata, SpiIrq event)
{
    TrDone = 1;
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

    DBG_8195A ("\n");
    return;
}

#if SPI_IS_AS_MASTER
spi_t spi_master;
#else
spi_t spi_slave;
#endif
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
    int Counter = 0;
    int i;

#if SPI_IS_AS_MASTER
    gpio_init(&spi_cs0, SPI_GPIO_CS0);
    gpio_write(&spi_cs0, 1);//Initialize GPIO Pin to high 
    gpio_dir(&spi_cs0, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&spi_cs0, PullNone);     // No pull

    gpio_init(&spi_cs1, SPI_GPIO_CS1);
    gpio_write(&spi_cs1, 1);//Initialize GPIO Pin to high 
    gpio_dir(&spi_cs1, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&spi_cs1, PullNone);     // No pull
    
	spi_master.spi_idx=MBED_SPI1;
    spi_init(&spi_master, SPI1_MOSI, SPI1_MISO, SPI1_SCLK, SPI1_CS);
    spi_frequency(&spi_master, SCLK_FREQ);
    spi_format(&spi_master, 8, (SPI_SCLK_IDLE_LOW|SPI_SCLK_TOGGLE_START) , 0);


    while (Counter < TEST_LOOP) {
        DBG_8195A("======= Test Loop %d =======\r\n", Counter);

        if(Counter % 2){
            for (i=0;i<TEST_BUF_SIZE;i++) {
                TestBuf[i] = i;
            }
	    gpio_write(&spi_cs0, 0);
	    gpio_write(&spi_cs1, 1);
            // wait Slave ready
            wait_ms(1000);
        }
        else{
            for (i=0;i<TEST_BUF_SIZE;i++) {
                TestBuf[i] = ~i;
            }
	    gpio_write(&spi_cs0, 1);
	    gpio_write(&spi_cs1, 0);
            // wait Slave ready
            wait_ms(1000);

        }

        spi_irq_hook(&spi_master, (spi_irq_handler)master_tr_done_callback, (uint32_t)&spi_master);
        DBG_8195A("SPI Master Write Test==>\r\n");
        TrDone = 0;

        spi_master_write_stream(&spi_master, TestBuf, TEST_BUF_SIZE);

        i=0;
        DBG_8195A("SPI Master Wait Write Done...\r\n");
        while(TrDone == 0) {
            wait_ms(10);
            i++;
        }
        DBG_8195A("SPI Master Write Done!!\r\n");
		if(Counter % 2){
		gpio_write(&spi_cs0, 1);
		gpio_write(&spi_cs1, 0);
		}
		else{
		gpio_write(&spi_cs0, 0);
		gpio_write(&spi_cs1, 1);
		}
		wait_ms(4000);
		Counter++;
	}
	spi_free(&spi_master);
	DBG_8195A("SPI Master Test <==\r\n");

#else
	spi_slave.spi_idx=MBED_SPI0;
    spi_init(&spi_slave, SPI0_MOSI, SPI0_MISO, SPI0_SCLK, SPI0_CS);
    spi_format(&spi_slave, 8, (SPI_SCLK_IDLE_LOW|SPI_SCLK_TOGGLE_START) , 1);

    while (spi_busy(&spi_slave)) {
        DBG_8195A("Wait SPI Bus Ready...\r\n");
        wait_ms(1000);
    }

    while (Counter < TEST_LOOP) {
        DBG_8195A("======= Test Loop %d =======\r\n", Counter);
        _memset(TestBuf, 0, TEST_BUF_SIZE);
        DBG_8195A("SPI Slave Read Test ==>\r\n");
        spi_irq_hook(&spi_slave, (spi_irq_handler)slave_tr_done_callback, (uint32_t)&spi_slave);
        TrDone = 0;
        spi_flush_rx_fifo(&spi_slave);

        spi_slave_read_stream(&spi_slave, TestBuf, TEST_BUF_SIZE);

        i=0;
        DBG_8195A("SPI Slave Wait Read Done...\r\n");
        while(TrDone == 0) {
            wait_ms(100);
            i++;
            if (i>150) {
                DBG_8195A("SPI Slave Wait Timeout\r\n");
                break;
            }
        }
        dump_data(TestBuf, TEST_BUF_SIZE, "SPI Slave Read Data:");

        Counter++;
    }
    spi_free(&spi_slave);
#endif

    DBG_8195A("SPI Demo finished.\n");
    for(;;);
}
