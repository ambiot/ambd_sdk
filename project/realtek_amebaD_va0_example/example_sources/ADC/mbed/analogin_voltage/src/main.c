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

#define ADC_CALIBRATION		0

#if defined (__ICCARM__)
analogin_t   adc0;
analogin_t   adc2;
#else
volatile analogin_t   adc0;
volatile analogin_t   adc2;
#endif

void adc_delay(void)
{
    int i;
	for(i=0;i<1600000;i++)
		asm(" nop");
}

uint16_t adcdat0    = 0;
uint16_t adcdat2    = 0;

int32_t v_mv0;
int32_t v_mv2;

/*
 * OFFSET:   10 times of sample data at 0.000v, 10*value(0.000v)
 * GAIN_DIV: 10 times of value(1.000v)-value(0.000v) or value(2.000v)-value(1.000v) or value(3.000v)-value(2.000v)
 */
/* Normal channel*/
u16 OFFSET;
u16 GAIN_DIV;

#define AD2MV(ad,offset,gain) ((10 * ad - offset) * 1000 / gain)

VOID 
main (
    VOID
)
{
	u8 EfuseBuf[2];
	u32 index;
	u32 addressOffset = 0x1D0;
	u32 addressGain = 0x1D2;

	uint16_t offset, gain;
	
	for (index = 0; index< 2; index++) {
		EFUSE_PMAP_READ8(0, addressOffset+index, EfuseBuf + index, L25EOUTVOLTAGE);
	}
	OFFSET = EfuseBuf[1]<<8|EfuseBuf[0];

	for (index = 0; index< 2; index++) {
		EFUSE_PMAP_READ8(0, addressGain+index, EfuseBuf + index, L25EOUTVOLTAGE);
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
	
	analogin_init(&adc0, AD_1);
	analogin_init(&adc2, AD_3);
#if ADC_CALIBRATION
	sys_adc_calibration(0, &offset, &gain);
	DBG_8195A("ADC:offset = 0x%x, gain = 0x%x\n", offset, gain);
	if((offset==0xFFFF) || (gain==0xFFFF))
#endif
	{
		offset = OFFSET;
		gain = GAIN_DIV;
		DBG_8195A("ADC:offset = 0x%x, gain = 0x%x\n", offset, gain);
	}
	for (;;){
		adcdat0 = analogin_read_u16(&adc0);
		adcdat2 = analogin_read_u16(&adc2);

		v_mv0 = AD2MV(adcdat0, offset, gain);
		v_mv2 = AD2MV(adcdat2, offset, gain);

		DBG_8195A("AD0:%x = %d mv, AD2:%x = %d mv\n", adcdat0, v_mv0, adcdat2, v_mv2); 
		adc_delay();
	}
	analogin_deinit(&adc0);
	analogin_deinit(&adc2);
}
