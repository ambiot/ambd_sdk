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

/* Vbat channel */
u16 OFFSET;
u16 GAIN_DIV;
#define AD2MV(ad,offset,gain) ((10 * ad -offset) * 1000 / gain)

void adc_delay(void)
{
    	int i;
	for(i=0;i<1600000;i++)
		asm(" nop");
}

void adc_vbat_en(void)
{
	uint16_t adc_read = 0;
	int32_t voltage;
	analogin_t   adc_vbat;

	analogin_init(&adc_vbat, AD_7);

	DiagPrintf("ADC:offset = 0x%x, gain = 0x%x\n", OFFSET, GAIN_DIV);

	for (;;){
		adc_read = analogin_read_u16(&adc_vbat);

		voltage = AD2MV(adc_read, OFFSET, GAIN_DIV);

		DiagPrintf("ADC_Vbat: 0x%x = %d mv\n", adc_read, voltage); 
		adc_delay();
	}
	analogin_deinit(&adc_vbat);

	vTaskDelete(NULL);
}

VOID main (VOID)
{
	u8 EfuseBuf[2];
	u32 index;
	u32 addressOffset = 0x1D4;
	u32 addressGain = 0x1D6;


	for (index = 0; index< 2; index++) {
		EFUSE_PMAP_READ8(0, addressOffset+index, EfuseBuf + index, L25EOUTVOLTAGE);
	}
	OFFSET = EfuseBuf[1]<<8|EfuseBuf[0];

	for (index = 0; index< 2; index++) {
		EFUSE_PMAP_READ8(0, addressGain+index, EfuseBuf + index, L25EOUTVOLTAGE);
	}
	GAIN_DIV = EfuseBuf[1]<<8|EfuseBuf[0];

	if (OFFSET == 0xFFFF) {
		OFFSET = 0x9C4;
		DiagPrintf("Default OFFSET!\n");
	}

	if (GAIN_DIV == 0xFFFF) {
		GAIN_DIV = 7860;
		DiagPrintf("Default GAIN_DIV!\n");
	}

	DiagPrintf("OFFSET = %x\n", OFFSET);
	DiagPrintf("GAIN_DIV = %x\n", GAIN_DIV);

	if(xTaskCreate( (TaskFunction_t)adc_vbat_en, "ADC VBAT DEMO", (2048/4), NULL, (tskIDLE_PRIORITY + 1), NULL)!= pdPASS) {
			DiagPrintf("Cannot create ADC Vbat demo task\n\r");
	}

	vTaskStartScheduler();

	while(1);
}


