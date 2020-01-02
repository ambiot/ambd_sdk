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

void main(void)
{

	u32 SclkPhase = USI_SPI_SCPH_TOGGLES_IN_MIDDLE;
	u32 SclkPolarity = USI_SPI_SCPOL_INACTIVE_IS_LOW;
	int TestingTimes = 10;
	int Counter = 0;
	int TestData = 0;
	int ReadData = 0;
	int result = 1;

	/* init USI_SPI as Slave*/
	USI_SSI_InitTypeDef USI_SSI_InitStruct;

	RCC_PeriphClockCmd(APBPeriph_USI_REG, APBPeriph_USI_CLOCK, ENABLE);
	Pinmux_Config(USI_SPI_MOSI, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(USI_SPI_MISO, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(USI_SPI_CS, PINMUX_FUNCTION_SPIS);
	Pinmux_Config(USI_SPI_SCLK, PINMUX_FUNCTION_SPIS);
	
	if (SclkPolarity == USI_SPI_SCPOL_INACTIVE_IS_LOW) {
		/* CS pull high, CLK pull low */
		PAD_PullCtrl(USI_SPI_CS, GPIO_PuPd_UP);
		PAD_PullCtrl(USI_SPI_SCLK, GPIO_PuPd_DOWN);
	} else {
		/* CS pull high, CLK pull high */
		PAD_PullCtrl(USI_SPI_CS, GPIO_PuPd_UP);
		PAD_PullCtrl(USI_SPI_SCLK, GPIO_PuPd_UP);
	}

	USI_SSI_StructInit(&USI_SSI_InitStruct);
	USI_SSI_InitStruct.USI_SPI_Role = USI_SPI_SLAVE;
	USI_SSI_InitStruct.USI_SPI_SclkPhase = SclkPhase;
	USI_SSI_InitStruct.USI_SPI_SclkPolarity = SclkPolarity;
	USI_SSI_InitStruct.USI_SPI_DataFrameSize = USI_SPI_DFS_8_BITS;
	USI_SSI_Init(USI0_DEV, &USI_SSI_InitStruct);

	/**
	* Slave write/read
	*/
	DBG_8195A("----------- Slave write/read -----------\n");
	for(Counter = 0, TestData = 0x01; Counter < TestingTimes; Counter++)
	{

		/* slave write */
		while (!USI_SSI_Writeable(USI0_DEV));
		USI_SSI_WriteData(USI0_DEV, TestData);

		/* slave read */
		while (!USI_SSI_Readable(USI0_DEV));
		ReadData = (int)USI_SSI_ReadData(USI0_DEV);

		DBG_8195A("Slave write: %x, read: %x\n", TestData, ReadData);
		if (TestData != ReadData) {
			result = 0;
		}
		TestData++;
	}

	/* free USI_SPI */
	USI_SSI_Cmd(USI0_DEV, DISABLE);

	DBG_8195A("USI SPI Slave Demo Finished.\n");
	DBG_8195A("\r\nSlave Result is %s\r\n", (result) ? "success" : "fail");
	for(;;);

}

