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

#define FakeMbedAPI  1

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


spi_t spi_master;
spi_t spi_slave;

static void spi_task(void* param)
{
#if FakeMbedAPI

	/* SPI1 is as Master */
	spi_master.spi_idx=MBED_SPI1;
	spi_init(&spi_master, SPI1_MOSI, SPI1_MISO, SPI1_SCLK, SPI1_CS);
	spi_format(&spi_master, 8, 0, 0);
	spi_frequency(&spi_master, 200000);
	/* SPI0 is as Slave */
	spi_slave.spi_idx=MBED_SPI0;
	spi_init(&spi_slave,  SPI0_MOSI, SPI0_MISO, SPI0_SCLK, SPI0_CS);
	spi_format(&spi_slave, 8, 0, 1);

	int TestingTimes = 10;
	int Counter		 = 0;
	int TestData 	 = 0;
	int ReadData	 = 0;

	int result = 1;

	/**
	* Master read/write, Slave read/write
	*/
	DiagPrintf("--------------------------------------------------------\n");
	for(Counter = 0, TestData=0x01; Counter < TestingTimes; Counter++)
	{
		ReadData = spi_master_write(&spi_master, TestData);
		DiagPrintf("Master write: %02X, read: %02X\n", TestData, ReadData);
		if (TestData - 1 != ReadData) {
			result = 0;
		}

		TestData++;

		spi_slave_write(&spi_slave, TestData);
		ReadData = spi_slave_read(&spi_slave);
		DiagPrintf("Slave  write: %02X, read: %02X\n", TestData, ReadData);
		if (TestData - 1 != ReadData) {
			result = 0;
		}

		TestData++;
	}

	/**
	* Master write, Slave read
	*/
	DiagPrintf("--------------------------------------------------------\n");
	for(Counter = 0, TestData=0xFF; Counter < TestingTimes; Counter++)
	{
		spi_master_write(&spi_master, TestData);
		ReadData = spi_slave_read(&spi_slave);
		DiagPrintf("Master write: %02X\n", TestData);
		DiagPrintf("Slave  read : %02X\n", ReadData);
		if (TestData != ReadData) {
			result = 0;
		}

		TestData--;
	}

	spi_free(&spi_master);
	spi_free(&spi_slave);

	DiagPrintf("SPI Demo finished.\n");

	DiagPrintf("\r\nResult is %s\r\n", (result) ? "success" : "fail");
	for(;;);

#else  // mbed SPI API emulation

#endif

	vTaskDelete(NULL);
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	if(xTaskCreate(spi_task, ((const char*)"spi_task"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		DiagPrintf("\n\r%s xTaskCreate(spi_task) failed", __FUNCTION__);

	vTaskStartScheduler();
	while(1){
		vTaskDelay( 1000 / portTICK_RATE_MS );
	}
	
}

