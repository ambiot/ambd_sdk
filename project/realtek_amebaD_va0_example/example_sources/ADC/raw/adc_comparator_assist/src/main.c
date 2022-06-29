/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "ameba_soc.h"

/*
 * OFFSET:   10 times of sample data at 0.000v, 10*value(0.000v)
 * GAIN_DIV: 10 times of value(1.000v)-value(0.000v) or value(2.000v)-value(1.000v) or value(3.000v)-value(2.000v)
 */
/* Normal channel*/
u16 OFFSET;
u16 GAIN_DIV;
#define AD2MV(ad,offset,gain) ((10 * ad - offset) * 1000 / gain)

void CMPIrqHandle(void)
{
	u16 value, data, ch_idx;
	int vol;
	u32 sts = CMP_GetISR();

	while(ADC_Readable() == 0);
	
	value = ADC_Read();
	
	ch_idx = (value & BIT_MASK_DAT_CHID) >> 12;
	data = value & BIT_MASK_DAT_GLOBAL;
	vol = AD2MV(data, OFFSET, GAIN_DIV);

	DiagPrintf("AD%d:%x = %d mv\n", ch_idx, data, vol);

	CMP_INTClearPendingBit(sts);
}

VOID main (VOID)
{
	u8 EfuseBuf[2];
	u32 index;
	u32 addressOffset = 0x1D0;
	u32 addressGain = 0x1D2;

	u16 i;


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
		DiagPrintf("Default OFFSET!\n");
	}

	if (GAIN_DIV == 0xFFFF) {
		GAIN_DIV = 0x2F12;
		DiagPrintf("Default GAIN_DIV!\n");
	}

	DiagPrintf("OFFSET = %x\n", OFFSET);
	DiagPrintf("GAIN_DIV = %x\n", GAIN_DIV);

	ADC_InitTypeDef ADC_InitStruct;
	CMP_InitTypeDef CMP_InitStruct;
	
	/* Initialize ADC to comparator-assist mode. ADC is in low-power mode until Comparator 
	send wakeup signal to ADC */
	ADC_StructInit(&ADC_InitStruct);
	ADC_InitStruct.ADC_OpMode = ADC_COMP_ASSIST_MODE;
	ADC_InitStruct.ADC_ChIDEn = ENABLE; /* MSB 4bit is channel index*/
	ADC_Init(&ADC_InitStruct);

	ADC_Cmd(ENABLE);

	/* Initialize Comparator to timer-trigger mode to scan channels */
	CMP_StructInit(&CMP_InitStruct);
	for(i = 0; i < 4; i++) {
		CMP_InitStruct.CMP_ChanCtrl[i].CMP_Ref0 = 10;
		CMP_InitStruct.CMP_ChanCtrl[i].CMP_Ref1 = 20;

		/* wake up system and ADC when Vin > 1v (Vref0) && Vin < 2v (Vref1)*/
		CMP_InitStruct.CMP_ChanCtrl[i].CMP_WakeType = COMP_WK_SYS| COMP_WK_ADC;
		CMP_InitStruct.CMP_ChanCtrl[i].CMP_WakeSysCtrl = COMP_WITHIN_REF0_AND_REF1;
		CMP_InitStruct.CMP_ChanCtrl[i].CMP_WakeADCCtrl = COMP_WITHIN_REF0_AND_REF1;
	}

	CMP_Init(&CMP_InitStruct);
	CMP_Cmd(ENABLE);
	CMP_TimerTrigCmd(3, 100, ENABLE);

	/* When input voltage of each channel (0~4) matches the criteria, comparator will send
	wakeup signal to system and trigger ADC to sample */
	InterruptRegister((IRQ_FUN)CMPIrqHandle, ADC_COMP_IRQ, NULL, 10);
	InterruptEn(ADC_COMP_IRQ, 10);

	while(1);	
}
