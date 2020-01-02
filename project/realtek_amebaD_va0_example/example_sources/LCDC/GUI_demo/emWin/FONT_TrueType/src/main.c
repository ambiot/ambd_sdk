
#include "ameba_soc.h"
#include "main.h"
#include "GUI.h"

#if defined ( __ICCARM__ )
#pragma section=".image2.psram.bss"

SECTION(".data") u8* __psram_bss_start__;
SECTION(".data") u8* __psram_bss_end__;
#endif

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

#if defined ( __ICCARM__ )
	__psram_bss_start__ = (u8*)__section_begin(".image2.psram.bss");
	__psram_bss_end__   = (u8*)__section_end(".image2.psram.bss");	
#endif

	/*init psram bss area*/
	memset(__psram_bss_start__, 0, __psram_bss_end__ - __psram_bss_start__);

}

int main(void)
{
	if(TRUE == psram_dev_config.psram_dev_enable) {
		app_init_psram();
	}

	if (xTaskCreate((TaskFunction_t )MainTask,(const char*)"MainTask", 4096, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(MainTask) failed", __FUNCTION__);


	//DBG_8195A("M4U:%d \n", RTIM_GetCount(TIMM05));
	/* Enable Schedule, Start Kernel */
	vTaskStartScheduler();
}

