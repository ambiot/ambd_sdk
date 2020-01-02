/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "device.h"
#include "analogin_api.h"
#include <sys_api.h>

/*
 * OFFSET:   10 times of sample data at 0.000v, 10*value(0.000v)
 * GAIN_DIV: 10 times of value(1.000v)-value(0.000v) or value(2.000v)-value(1.000v) or value(3.000v)-value(2.000v)
 */
/* Normal channel*/
u16 OFFSET;
u16 GAIN_DIV;
#define AD2MV(ad,offset,gain) ((10 * ad - offset) * 1000 / gain)

#define BUF_SIZE	256
u16 BufferForADCRx[BUF_SIZE];

VOID 
main (
    VOID
)
{
	u8 EfuseBuf[2];
	u32 index;
	u32 addressOffset = 0x1D0;
	u32 addressGain = 0x1D2;

	u16 data, ch_idx, i;
	int vol;
	
	for (index = 0; index< 2; index++) {
		EFUSERead8(0, addressOffset+index, EfuseBuf + index, L25EOUTVOLTAGE);
	}
	OFFSET = EfuseBuf[1]<<8|EfuseBuf[0];

	for (index = 0; index< 2; index++) {
		EFUSERead8(0, addressGain+index, EfuseBuf + index, L25EOUTVOLTAGE);
	}
	GAIN_DIV = EfuseBuf[1]<<8|EfuseBuf[0];

	if (OFFSET == 0xFFFF) {
		OFFSET = 0x9B0;
		DBG_8195A("Default OFFSET!\n");
	}

	if (GAIN_DIV == 0xFFFF) {
		GAIN_DIV = 0x2F12;
		DBG_8195A("Default GAIN_DIV!\n");
	}

	DBG_8195A("OFFSET = %x\n", OFFSET);
	DBG_8195A("GAIN_DIV = %x\n", GAIN_DIV);

	ADC_InitTypeDef ADC_InitStruct; 
	
	/* Initialize ADC to auto mode to get continuous sample data */
	ADC_StructInit(&ADC_InitStruct);
	ADC_InitStruct.ADC_OpMode = ADC_AUTO_MODE;
	ADC_InitStruct.ADC_CvlistLen = 2; 	/* ADC_CvlistLen should be channel number -1*/
	ADC_InitStruct.ADC_Cvlist[0] = ADC_CH1;
	ADC_InitStruct.ADC_Cvlist[1] = ADC_CH2;
	ADC_InitStruct.ADC_Cvlist[2] = ADC_CH3;
	ADC_InitStruct.ADC_ChIDEn = ENABLE; /* MSB 4bit is channel index*/
	ADC_Init(&ADC_InitStruct);

	ADC_Cmd(ENABLE);

	/* Continuous Read data in auto mode */
	ADC_ReceiveBuf(BufferForADCRx, BUF_SIZE);

	for(i = 0; i < BUF_SIZE; i++) {
		
		ch_idx = (BufferForADCRx[i] & BIT_MASK_DAT_CHID) >> 12;
		data = BufferForADCRx[i] & BIT_MASK_DAT_GLOBAL;
		vol = AD2MV(data, OFFSET, GAIN_DIV);

		DBG_8195A("AD%d:%x = %d mv\n", ch_idx, data, vol);
	}

	while(1);
}
