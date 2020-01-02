#include "platform_stdlib.h"
#include "basic_types.h"
#include "diag.h"
#include "ameba_soc.h"
#include "rtl8721d_lcdc.h"
#include "bsp_rgb_lcd.h"

void app_init_psram(void)
{
	u32 temp;
	PCTL_InitTypeDef  PCTL_InitStruct;

	/*set rwds pull down*/
	temp = HAL_READ32(PINMUX_REG_BASE, 0x104);
	temp &= ~(PAD_BIT_PULL_UP_RESISTOR_EN | PAD_BIT_PULL_DOWN_RESISTOR_EN);
	temp |= PAD_BIT_PULL_DOWN_RESISTOR_EN;
	HAL_WRITE32(PINMUX_REG_BASE, 0x104, temp);

	PSRAM_CTRL_StructInit(&PCTL_InitStruct);
	PSRAM_CTRL_Init(&PCTL_InitStruct);

	PSRAM_PHY_REG_Write(REG_PSRAM_CAL_PARA, 0x02030310);

	/*check psram valid*/
	HAL_WRITE32(PSRAM_BASE, 0, 0);
	assert_param(0 == HAL_READ32(PSRAM_BASE, 0));

	if(SYSCFG_CUT_VERSION_A != SYSCFG_CUTVersion()) {
		if(_FALSE == PSRAM_calibration())
			return;

		if(FALSE == psram_dev_config.psram_dev_cal_enable) {
			temp = PSRAM_PHY_REG_Read(REG_PSRAM_CAL_CTRL);
			temp &= (~BIT_PSRAM_CFG_CAL_EN);
			PSRAM_PHY_REG_Write(REG_PSRAM_CAL_CTRL, temp);
		}
	}

	/*init psram bss area*/
	memset(__psram_bss_start__, 0, __psram_bss_end__ - __psram_bss_start__);
}

void main(void)
{
	app_init_psram();
	u32 i,j,Temp;
	u16 RGBBuf[3]={RED, GREEN, BLUE};
	u16 x1,y1;
	u8 TestStrings[]="RGB-DISPLAY-TEST";
	
	/*pinmux config*/
	u16 Pin_Func = PINMUX_FUNCTION_LCD;
	Pinmux_Config(_PA_19, Pin_Func);  /*D0*/
	Pinmux_Config(_PA_20, Pin_Func);  /*D1*/
	Pinmux_Config(_PA_23, Pin_Func);  /*D2*/	
	Pinmux_Config(_PA_24, Pin_Func);  /*D3*/
	Pinmux_Config(_PA_31, Pin_Func);  /*D4*/
	Pinmux_Config(_PB_0, Pin_Func);  /*D5*/
	Pinmux_Config(_PB_20, Pin_Func);  /*VSYNC*/
	Pinmux_Config(_PB_22, Pin_Func);  /*HSYNC*/
	Pinmux_Config(_PB_23, Pin_Func);  /*DCLK*/
	Pinmux_Config(_PB_28, Pin_Func);  /*ENABLE*/

	RgbLcdInit();
	RgbLcdDisplayDir(HORIZONTAL_SCREEN);
	RgbLcdDisplaySwitch(RGB_LCD_OPEN);
	RgbLcdSetBkColor( WHITE);
	RgbLcdClear();
	
	while(1) {
		/*draw point*/
		RgbLcdSetBkColor( WHITE);
		RgbLcdClear();
		DelayUs(1000000);
		RgbLcdSetColor( BLUE);
		for(i=0; i<RgbLcdDev.Height;i++) {
			for(j=0; j<RgbLcdDev.Width;j++) {
				RgbLcdDrawPoint(j,i);
				DelayUs(10);
			}
		}
		RgbLcdClear();
		DelayUs(500000);
		
		/*draw circle*/
		RgbLcdSetColor( YELLOW);
		for(i=0;i< ((RgbLcdDev.Width/2>RgbLcdDev.Height/2)?RgbLcdDev.Height/2:RgbLcdDev.Width/2);i++) {
			x1 = RgbLcdDev.Width/2;
			y1 = RgbLcdDev.Height/2;		
			RgbLcdDrawCircle(x1,y1,i);
			DelayUs(2500);
		}
		DelayUs(200000);
		RgbLcdClear();
		DelayUs(500000);
		
		/*fill color play*/
		Temp = RgbLcdDev.Height/3;
		for(i=0; i<3;i++) {
			RgbLcdSetColor(RGBBuf[i]);
			RgbLcdFill(0, i*Temp, RgbLcdDev.Width-1,(i+1)*Temp-1);
			DelayUs(300000);
		}
		RgbLcdClear();
		DelayUs(1000000);
		
		/*show strings*/
		RgbLcdSetBkColor( BLACK);
		RgbLcdClear();
		RgbLcdSetColor( GREEN);
		RgbLcdShowString(0, 0, RgbLcdDev.Width-1, RgbLcdDev.Height-1, 24, TestStrings);
		DelayUs(2000000);
	}
}

