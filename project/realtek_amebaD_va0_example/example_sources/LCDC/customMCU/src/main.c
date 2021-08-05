
#include "ameba_soc.h"
#include "ftl_int.h"
#include "main.h"
#include "bsp_touch.h"

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
	u32 i,j,k,l;
	u16 ColorBuf[14]={WHITE, BLACK, BLUE, BRED, GRED, GBLUE, RED, MAGENTA, GREEN, CYAN, YELLOW, BROWN, BRRED, GRAY};
	u16 RGBBuf[3]={RED, GREEN, BLUE};
	u16 x1,y1,x2,y2;
	u32 Temp;
	u32 xTemp, yTemp;
	u8 TestStrings[]="NOW-TOUCH-PAD-TEST-NOW-TOUCH-PAD-TEST-NOW-TOUCH-PAD-TEST";
	u16 TempColor;

	 app_init_psram();

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

	lcddev.McuLcdBitMode = MCU_LCD_8BIT_IF;

	bsp_touch__init();
	BSP_LCD_Init();
		
		DiagPrintf("draw point test\n");
		/*-------------------------draw point*/
		LCD_Clear(WHITE);
		for(i=0; i<lcddev.height;i++) {
			for(j=0; j<lcddev.width;j++) {
				LCD_Fast_DrawPoint(j,i,RED);
				HalDelayUs(10);
			}
		}
		HalDelayUs(1000);
		LCD_Clear(WHITE);

				DiagPrintf("draw line test\n");
		/*-------------------------draw line*/
		POINT_COLOR = BLUE;
		for(i=0;i<100;i++) {
			x1 = Rand()%lcddev.width;
			y1 = Rand()%lcddev.height;
			x2 = Rand()%lcddev.width;
			y2 = Rand()%lcddev.height;			
			LCD_DrawLine(x1,y1,x2,y2);
			HalDelayUs(5000);
		}
		LCD_Clear(WHITE);

		DiagPrintf("draw circle test\n");
		/*draw circle*/
		POINT_COLOR = BLUE;
		for(i=0;i< ((lcddev.width/2>lcddev.height/2)?lcddev.height/2:lcddev.width/2);i++) {
			x1 = lcddev.width/2;
			y1 = lcddev.height/2;		
			LCD_Draw_Circle(x1,y1,i);
			HalDelayUs(2500);
		}
		LCD_Clear(WHITE);
		for(i=0;i<100;i++) {
			x1 = Rand()%lcddev.width;
			y1 = Rand()%lcddev.height;
			xTemp = (lcddev.width-x1)>x1?x1:(lcddev.width-x1);
			yTemp = (lcddev.height-y1)>y1?y1:(lcddev.height-y1);
			LCD_Draw_Circle(x1,y1,(xTemp>yTemp)?yTemp:xTemp);
			HalDelayUs(5000);
		}

		DiagPrintf("fill color test\n");
		/*fill color*/
		Temp = lcddev.height/3;
		for(i=0; i<3;i++) {
			LCD_Fill(0, i*Temp, lcddev.width-1,(i+1)*Temp-1, RGBBuf[i]);
			HalDelayUs(300000);
		}
		LCD_Clear(WHITE);
		/*configure color*/
		POINT_COLOR = RED;
		BACK_COLOR = WHITE;

		/*show strings*/
		LCD_ShowString(0, 0, lcddev.width-1, lcddev.height-1, 24, TestStrings);
		HalDelayUs(500000);

		int pointx, pointy;
		POINT_COLOR = RED;
		
	while(1){
		xpt2046_touch_data.state = TOUCH_RELEASE ;

		bsp_touch__scan();
		//DiagPrintf("state:%d\n", xpt2046_touch_data.state);
		
		if(xpt2046_touch_data.state == TOUCH_PRESS){

			pointx = xpt2046_touch_data.x;
			pointy  = xpt2046_touch_data.y;
			
			//DiagPrintf("point: %d,%d\n", pointx, pointy);
			LCD_Draw_Circle(pointx, pointy, 1);
			LCD_Draw_Circle(pointx, pointy, 2);
			LCD_Fast_DrawPoint(pointx, pointy, RED);

		}
		//DelayMs(10);
	}
}
