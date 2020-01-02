#include "platform_stdlib.h"
#include "basic_types.h"
#include "diag.h"
#include "ameba_soc.h"
#include "rtl8721d_lcdc.h"
#include "bsp_mcu_lcd.h"


#define LCD_W    240
#define LCD_H     320

PSRAM_BSS_SECTION
__attribute__ ((aligned (4)))
u8 Lcd_ImgBuffer[LCD_W*LCD_H*2];

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
	u32 TempDot;
	u16* pImgBuf16bit;
	u16 RGBBuf[3]={RED, GREEN, BLUE};
	u32 i;
	u32 TestCnt=0;
	u32 Index;
	
	/*PSRAM */
	app_init_psram();
	
	/*pinmux config*/
	u16 Pin_Func = PINMUX_FUNCTION_LCD;
	Pinmux_Config(_PA_19, Pin_Func);  /*D0*/
	Pinmux_Config(_PA_20, Pin_Func);  /*D1*/
	Pinmux_Config(_PA_23, Pin_Func);  /*D2*/	
	Pinmux_Config(_PA_24, Pin_Func);  /*D3*/
	Pinmux_Config(_PA_31, Pin_Func);  /*D4*/
	Pinmux_Config(_PB_0, Pin_Func);  /*D5*/
	Pinmux_Config(_PA_30, Pin_Func);  /*D6*/
	Pinmux_Config(_PA_28, Pin_Func);  /*D7*/
	Pinmux_Config(_PB_20, Pin_Func);  /*TE/VSYNC*/
	Pinmux_Config(_PB_21, Pin_Func);  /*RS*/
	Pinmux_Config(_PB_22, Pin_Func);  /*RD*/
	Pinmux_Config(_PB_23, Pin_Func);  /*WR*/
	Pinmux_Config(_PB_28, Pin_Func);  /*CS*/


	/*firstly, initialize the LCDC in MCU IO mode to configure the LCM*/
	LCDC_MCUInitTypeDef LCDC_MCUInitStruct;

	/*arrange default parameters*/
	LCDC_MCUStructInit(&LCDC_MCUInitStruct);

	LCDC_MCUInitStruct.LCDC_MCUIfMode = LCDC_MCU_IF_8_BIT;
	LCDC_MCUInitStruct.LCDC_MCURdAcvWidth = 4;
	LCDC_MCUInitStruct.LCDC_MCURdInacvWidth = 4;
	LCDC_MCUInitStruct.LCDC_MCUWrPulWidth = 6;   /*write pulse width = 6*10 ns*/

	LCDC_MCUInit(LCDC, &LCDC_MCUInitStruct);

	/*enable LCDC*/
	LCDC_Cmd(LCDC, ENABLE);		

	ILI9341_Init();

	LCD_Display_Dir(0);
	LCD_Clear(WHITE);

	/*set the image range*/
	LCD_SetWindow(0, 0, LCD_W - 1, LCD_H - 1);
	LCD_WriteRAM_Prepare();
	/* wait for I/O mode tx complete */
	DelayMs(10);

	/*switch to trigger DMA mode*/
	LCDC_Cmd(LCDC, DISABLE);		
	
	LCDC_MCUStructInit(&LCDC_MCUInitStruct);

	/*configure MCU VSYNC parameters*/
	LCDC_MCUInitStruct.LCDC_MCUIfMode = LCDC_MCU_IF_8_BIT;
	LCDC_MCUInitStruct.LCDC_MCUMode = LCDC_MCU_DMA_MODE;
	LCDC_MCUInitStruct.LCDC_MCUDMAMode = LCDC_TRIGGER_DMA_MODE;
	LCDC_MCUInitStruct.LCDC_MCUImgHeight = LCD_H;
	LCDC_MCUInitStruct.LCDC_MCUImgWidth = LCD_W;
	LCDC_MCUInitStruct.LCDC_MCUSyncMode = LCDC_MCU_SYNC_WITH_INTERNAL_CLK;

	LCDC_MCUInit(LCDC, &LCDC_MCUInitStruct);

	/*configure DMA parameters: burst size, image base address*/
	LCDC_DMAModeConfig(LCDC, 2);

	/*initialize the image buffer*/
	TempDot = LCD_H*LCD_W;

	pImgBuf16bit = (u16 *)&Lcd_ImgBuffer[0];

	/*arrange image base address*/
	LCDC_DMAImageBaseAddrConfig(LCDC, (u32)&Lcd_ImgBuffer[0]);

	/*enable LCDC*/
	LCDC_Cmd(LCDC, ENABLE);	

	/*trigger DMA to transfer image data to LCM*/
	while(1) {
		Index = TestCnt%3;
		TestCnt++;
		for(i=0; i<TempDot; i++) {
			pImgBuf16bit[i] = RGBBuf[Index];
		}

		LCDC_MCUDMATrigger(LCDC);
		HalDelayUs(300000);
	}
}

