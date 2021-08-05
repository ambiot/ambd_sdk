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

void spi_task(void* param)
{

	u32 SclkPhase = SCPH_TOGGLES_IN_MIDDLE; // SCPH_TOGGLES_IN_MIDDLE or SCPH_TOGGLES_AT_START
	u32 SclkPolarity = SCPOL_INACTIVE_IS_LOW; // SCPOL_INACTIVE_IS_LOW or SCPOL_INACTIVE_IS_HIGH
	u32 ClockDivider = 500; // an even value between 2 and 65534
	int TestingTimes = 10;
	int Counter	= 0;
	int TestData = 0;
	int ReadData = 0;
	int result = 1;


	/* SPI1 is as Master and SPI0 is as Slave */

	/* init SPI1 */
	SSI_InitTypeDef SSI_InitStructM;
	SSI_StructInit(&SSI_InitStructM);

	RCC_PeriphClockCmd(APBPeriph_SPI1, APBPeriph_SPI1_CLOCK, ENABLE);
	Pinmux_Config(SPI1_MOSI, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(SPI1_MISO, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(SPI1_SCLK, PINMUX_FUNCTION_SPIM);
	Pinmux_Config(SPI1_CS, PINMUX_FUNCTION_SPIM);
	
	//SSI_SetRole(SPI0_DEV, SSI_MASTER); // for cases when SPI0 is as master
	SSI_InitStructM.SPI_Role = SSI_MASTER;
	SSI_Init(SPI1_DEV, &SSI_InitStructM);

	/* set format */
	SSI_SetSclkPhase(SPI1_DEV, SclkPhase);
	SSI_SetSclkPolarity(SPI1_DEV, SclkPolarity);
	SSI_SetDataFrameSize(SPI1_DEV, DFS_8_BITS);

	PAD_PullCtrl((u32)SPI1_SCLK, GPIO_PuPd_UP);

	/* set frequency */
	SSI_SetBaudDiv(SPI1_DEV, ClockDivider); // IpClk of SPI1 is 50MHz, IpClk of SPI0 is 100MHz

	/* init SPI0 */
	SSI_InitTypeDef SSI_InitStructS;
	SSI_StructInit(&SSI_InitStructS);

	RCC_PeriphClockCmd(APBPeriph_SPI0, APBPeriph_SPI0_CLOCK, ENABLE);
	Pinmux_Config(SPI0_MOSI, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(SPI0_MISO, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(SPI0_SCLK, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(SPI0_CS, PINMUX_FUNCTION_SPIS);

	SSI_InitStructS.SPI_Role = SSI_SLAVE;	
	SSI_Init(SPI0_DEV, &SSI_InitStructS);

	/* set format */
	SSI_SetRole(SPI0_DEV, SSI_SLAVE);
	SSI_SetSclkPhase(SPI0_DEV, SclkPhase);
	SSI_SetSclkPolarity(SPI0_DEV, SclkPolarity);
	SSI_SetDataFrameSize(SPI0_DEV, DFS_8_BITS);

	if (SclkPolarity == SCPOL_INACTIVE_IS_LOW)
		PAD_PullCtrl((u32)SPI0_SCLK, GPIO_PuPd_DOWN);


	/**
	* Master read/write, Slave read/write
	*/
	DiagPrintf("--------------------------------------------------------\n");
	for(Counter = 0, TestData = 0x01; Counter < TestingTimes; Counter++)
	{
		/* master write */
		while (!SSI_Writeable(SPI1_DEV));
		SSI_WriteData(SPI1_DEV, TestData);

		/* master read */
		while (!SSI_Readable(SPI1_DEV));
		ReadData = (int)SSI_ReadData(SPI1_DEV);

		DiagPrintf("Master write: %02X, read: %02X\n", TestData, ReadData);
		if (TestData - 1 != ReadData) {
			result = 0;
		}
		TestData++;

		/* slave write */
		while (!SSI_Writeable(SPI0_DEV));
		SSI_WriteData(SPI0_DEV, TestData);

		/* slave read */
		while (!SSI_Readable(SPI0_DEV));
		ReadData = (int)SSI_ReadData(SPI0_DEV);

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
	for(Counter = 0, TestData = 0xFF; Counter < TestingTimes; Counter++)
	{
		/* master write */
		while (!SSI_Writeable(SPI1_DEV));
		SSI_WriteData(SPI1_DEV, TestData);

		/* slave read */
		while (!SSI_Readable(SPI0_DEV));
		ReadData = (int)SSI_ReadData(SPI0_DEV);

		DiagPrintf("Master write: %02X\n", TestData);
		DiagPrintf("Slave  read : %02X\n", ReadData);
		if (TestData != ReadData) {
			result = 0;
		}

		TestData--;
	}

	/* free SPI1 */
	SSI_Cmd(SPI1_DEV, DISABLE);
	/* free SPI0 */
	SSI_Cmd(SPI0_DEV, DISABLE);

	DiagPrintf("SPI Demo finished.\n");
	DiagPrintf("\r\nResult is %s\r\n", (result) ? "success" : "fail");

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

