
#include "ameba_soc.h"
#include "tjpgd.h"
#include "bsp_rgb_lcd.h"

typedef struct {
	UINT wfbuf;    /* Width of the frame buffer [pix] */
	UINT flash_addr;
	UINT fptr;
} IODEV;

void Pinmux_LCDCCtrl(u32  PinLocation, BOOL   Operation)
{
	u16 Pin_Func = PINMUX_FUNCTION_GPIO;
	
	if (Operation)
		Pin_Func = PINMUX_FUNCTION_LCD;

	Pinmux_Config(_PA_19, Pin_Func);  /*D0*/
	Pinmux_Config(_PA_20, Pin_Func);  /*D1*/
	Pinmux_Config(_PA_23, Pin_Func);  /*D2*/	
	Pinmux_Config(_PA_24, Pin_Func);  /*D3*/
	Pinmux_Config(_PA_25, Pin_Func);  /*D9*/
	Pinmux_Config(_PA_26, Pin_Func);  /*D8*/
	Pinmux_Config(_PA_28, Pin_Func);  /*D7*/
	Pinmux_Config(_PA_30, Pin_Func);  /*D6*/
	Pinmux_Config(_PA_31, Pin_Func);  /*D4*/
	Pinmux_Config(_PB_0, Pin_Func);  /*D5*/
	Pinmux_Config(_PB_8, Pin_Func);  /*D10*/
	Pinmux_Config(_PB_9, Pin_Func);  /*D11*/
	Pinmux_Config(_PB_10, Pin_Func);  /*D12*/
	Pinmux_Config(_PB_11, Pin_Func);  /*D13*/
	Pinmux_Config(_PB_18, Pin_Func);  /*D14*/
	Pinmux_Config(_PB_19, Pin_Func);  /*D15*/
	Pinmux_Config(_PB_20, Pin_Func);  /*VSYNC, TE*/
	Pinmux_Config(_PB_21, Pin_Func);  /*RS*/
	Pinmux_Config(_PB_22, Pin_Func);  /*RD, HSYNC, LATCH*/
	Pinmux_Config(_PB_23, Pin_Func);  /*WR, DCLK, LED_CLK*/
	Pinmux_Config(_PB_28, Pin_Func);  /*CS, ENABLE, OE*/
}

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

/**
  * @brief 		User defined input funciton
  * @param		jd: pointer to JDEC structure. 
  *				buff: pointer to buffer to save the read data
  *				nbyte: read size
  * @retval read size
  */
UINT JpgDec_in_func(JDEC* jd, BYTE* buff, UINT nbyte)
{
    IODEV *dev = (IODEV*)jd->device;   /* Device identifier for the session (5th argument of jd_prepare function) */

    if (buff) {
        /* Read bytes from input stream */
		flash_stream_read(NULL ,dev->flash_addr + dev->fptr, nbyte, buff);
		dev->fptr += nbyte;

		return nbyte;
    } else {
        /* Remove bytes from input stream */
		dev->fptr += nbyte;
    }
	return nbyte;
}

/**
  * @brief 		User defined output funciton
  * @param		jd: pointer to JDEC structure. 
  *				bitmap: pointer to the buffer of decompressed RGB data
  *				rect: the rectanglar range of decompressed area
  * @retval 1
  */
UINT JpgDec_out_func(JDEC* jd, void* bitmap, JRECT* rect)
{
    IODEV *dev = (IODEV*)jd->device;
    BYTE *src, *dst;
    UINT y, bws, bwd;

    /* Put progress indicator */
    if (rect->left == 0) {
        //printf("\r%d%%", (rect->top << jd->scale) * 100UL / jd->height);
    }

	RgbLcdShowBitmap(rect->left, 
					   rect->top, 
					   rect->right - rect->left + 1, 
					   rect->bottom - rect->top + 1, 
					   (u16*)bitmap);

    return 1;    /* Continue to decompress */
}

void JpgDec_task(void)
{
    void *work = NULL;       /* Pointer to the decompressor work area */
    JDEC jdec;        /* Decompression object */
    JRESULT res;      /* Result code of TJpgDec API */
    IODEV devid;      /* User defined device identifier */
	u32 buf_size = 3100;

	/* Configure IO device. flash_addr indicate the JPG file location.
	  To run this demo, it is necessary to burn a .jpg file to this address. */
	devid.flash_addr = 0x00106000;
	devid.fptr = 0;
	
	if(HAL_READ32(SPI_FLASH_BASE, devid.flash_addr) == 0xFFFFFFFF) {
		printf("JPG doesn't exist. Please download JPG file to address 0x%x !!\n", SPI_FLASH_BASE + devid.flash_addr);
		goto exit;
	}

	/* Init PSRAM which provides LCDC buffer */
	app_init_psram();

	/* Init LCDC*/
	Pinmux_LCDCCtrl(PINMUX_S0, ON);
	RgbLcdInit();
	RgbLcdDisplayDir(HORIZONTAL_SCREEN);
	RgbLcdDisplaySwitch(RGB_LCD_OPEN);
	RgbLcdSetBkColor(WHITE);
	RgbLcdClear();

    /* Allocate a work area for TJpgDec */
    work = pvPortMalloc(buf_size);

    /* Prepare to decompress */
    res = jd_prepare(&jdec, JpgDec_in_func, work, buf_size, &devid);
	
    if (res == JDR_OK) {
        /* Ready to dcompress. Image info is available here. */
        printf("Image dimensions: %d by %d.\n", jdec.width, jdec.height);
        devid.wfbuf = jdec.width;

		/* Start to decompress with 1/1 scaling */
        res = jd_decomp(&jdec, JpgDec_out_func, 0);
        if (res == JDR_OK) {
            printf("Decompression succeeded\n");
        } else {
            printf("Failed to decompress: rc=%d\n", res);
        }
    } else {
        printf("Failed to prepare: rc=%d\n", res);
    }

exit:
	if(work != NULL)
	    vPortFree(work);             /* Discard work area */

    vTaskDelete(NULL);
}

void main(void)
{
	xTaskCreate((TaskFunction_t )JpgDec_task, 
				(const char*)"Jpg_decoder", 
				(uint16_t		)2048, 
				(void*			)NULL, 
				(UBaseType_t	)tskIDLE_PRIORITY + 1, 
				(TaskHandle_t*	)NULL);

	vTaskStartScheduler();
}

