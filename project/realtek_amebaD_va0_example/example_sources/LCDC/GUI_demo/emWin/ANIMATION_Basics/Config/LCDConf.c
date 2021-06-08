/**********************************************************************
*                 SEGGER Software GmbH                               *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2019  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.48 - Graphical user interface for embedded applications **
All  Intellectual Property rights in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product. This file may
only be used in accordance with the following terms:

The  software has  been licensed by SEGGER Software GmbH to Realtek 
Semiconductor Corp. at the address: Realtek Semiconductor Corp., 
Hsinchu Science Park, Innovation Rd. II 2, 300 Hsinchu city, Taiwan for 
the purposes  of  creating  libraries  for its Cortex-M series of 
Microcontroller Units designed, branded, marketed and manufactured by 
Realtek Semiconductor Corp. under the terms and conditions of an End 
User License Agreement supplied with the libraries.

Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
Licensing information
Licensor:                 SEGGER Software GmbH
Licensed to:              Realtek Semiconductor Corp., Hsinchu Science Park, Innovation Rd. II 2, 300 Hsinchu city, Taiwan
Licensed SEGGER software: emWin
License number:           GUI-00784
License model:            emWin Buyout Agreement, signed May 15th, 2019
Licensed platform:        Cortex-M series of Microcontroller Units designed, branded, marketed and manufactured by LICENSEE
----------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "LCDConf.h"
#include "GUIDRV_Lin.h"
#include "ameba_soc.h"

/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/
//
// Physical display size
//
#define XSIZE_PHYS			480
#define YSIZE_PHYS			272

//
// Physical display parameters
//
#define LCD_HSW				123
#define LCD_HFP				6
#define LCD_HBP				6
#define LCD_VSW				10
#define LCD_VFP				2
#define LCD_VBP				2
#define LCD_SyncMode		LCDC_RGB_DE_MODE
#define LCD_SampleEdge		LCDC_RGB_DCLK_FALLING_EDGE_FETCH
#define LCD_RefreshFreq		50

//
// Buffers
//
#define NUM_BUFFERS			3

int _PendingBuffer = -1;

//
// Define VRAM buffer
//
#define VRAM_ADDR			VRAMBuffer

#if defined(PSRAM_BUF_USED)
	PSRAM_BSS_SECTION __attribute__ ((aligned (64))) u16 VRAMBuffer[YSIZE_PHYS * XSIZE_PHYS * NUM_BUFFERS];
#else
	__attribute__ ((aligned (64))) u16 VRAMBuffer[YSIZE_PHYS * XSIZE_PHYS * NUM_BUFFERS];
#endif

//
// Color conversion
//
#define COLOR_CONVERSION GUICC_M565

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_LIN_16

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VRAM_ADDR
  #error VRAM buffer is not defined!
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

static void _ISR_EndOfFrame(void) {
	unsigned long Addr;

	LCDC_ClearINT(LCDC, LCDC_IT_FRDN);

	if (_PendingBuffer >= 0) {
		//
		// Calculate address of the given buffer
		//
		U32 Addr = VRAM_ADDR + YSIZE_PHYS * XSIZE_PHYS * _PendingBuffer;
		//
		// Make the given buffer visible
		//
		LCDC_DMAImageBaseAddrConfig(LCDC, Addr);
		//
		// Send a confirmation that the buffer is visible now
		//
		GUI_MULTIBUF_Confirm(_PendingBuffer);
	
		_PendingBuffer = -1;
	}
}

/*********************************************************************
*
*       _InitController
*
* Purpose:
*   Should initialize the display controller
*/
static void _InitController(void) {

	LCDC_RGBInitTypeDef LCDC_RGBInitStruct;
	
	/* Enable LCDC pinmux, default 16bit I/F */
	Pinmux_Config(_PA_19, PINMUX_FUNCTION_LCD);  /*D0*/
	Pinmux_Config(_PA_20, PINMUX_FUNCTION_LCD);  /*D1*/
	Pinmux_Config(_PA_23, PINMUX_FUNCTION_LCD);  /*D2*/	
	Pinmux_Config(_PA_24, PINMUX_FUNCTION_LCD);  /*D3*/
	Pinmux_Config(_PA_31, PINMUX_FUNCTION_LCD);  /*D4*/
	Pinmux_Config(_PB_0, PINMUX_FUNCTION_LCD);  /*D5*/
	Pinmux_Config(_PB_20, PINMUX_FUNCTION_LCD);  /*VSYNC, TE*/
	Pinmux_Config(_PB_22, PINMUX_FUNCTION_LCD);  /*RD, HSYNC, LATCH*/
	Pinmux_Config(_PB_23, PINMUX_FUNCTION_LCD);  /*WR, DCLK, LED_CLK*/
	Pinmux_Config(_PB_28, PINMUX_FUNCTION_LCD);  /*CS, ENABLE, OE*/

	/*load the RGB HV I/F default parameters*/
	LCDC_RGBStructInit(&LCDC_RGBInitStruct);

	/*configure image size, RGB timing parameters*/
	LCDC_RGBInitStruct.LCDC_RGBImgWidth = XSIZE_PHYS;
	LCDC_RGBInitStruct.LCDC_RGBImgHeight = YSIZE_PHYS;
	LCDC_RGBInitStruct.LCDC_RGBHSW = LCD_HSW;
	LCDC_RGBInitStruct.LCDC_RGBHFP = LCD_HFP;
	LCDC_RGBInitStruct.LCDC_RGBHBP = LCD_HBP;
	LCDC_RGBInitStruct.LCDC_RGBVSW = LCD_VSW;
	LCDC_RGBInitStruct.LCDC_RGBVFP = LCD_VFP;
	LCDC_RGBInitStruct.LCDC_RGBVBP = LCD_VBP;
	LCDC_RGBInitStruct.LCDC_RGBSyncMode = LCD_SyncMode;
	LCDC_RGBInitStruct.LCDC_RGBDclkActvEdge = LCD_SampleEdge;
	LCDC_RGBInitStruct.LCDC_RGBIfMode = LCDC_RGB_IF_6_BIT;
	LCDC_RGBInitStruct.LCDC_RGBRefreshFreq = LCD_RefreshFreq;
	
	LCDC_RGBInit(LCDC, &LCDC_RGBInitStruct);

	/*configure DMA burst size*/
	LCDC_DMAModeConfig(LCDC,2);

	/*configure base address*/
	LCDC_DMAImageBaseAddrConfig(LCDC, (u32)VRAM_ADDR);

	LCDC_INTConfig(LCDC, LCDC_IT_FRDN, ENABLE);
	InterruptRegister((IRQ_FUN)_ISR_EndOfFrame, LCDC_IRQ, NULL, 5);
	InterruptEn(LCDC_IRQ, 5);

	/*enable LCDC*/
	LCDC_Cmd(LCDC, ENABLE);
}

/*********************************************************************
*
*       _SetVRAMAddr
*
* Purpose:
*   Should set the frame buffer base address
*/
static void _SetVRAMAddr(void * pVRAM) {
  	LCDC_DMAImageBaseAddrConfig(LCDC, pVRAM);
}

/*********************************************************************
*
*       _SetOrg
*
* Purpose:
*   Should set the origin of the display typically by modifying the
*   frame buffer base address register
*/
static void _SetOrg(int xPos, int yPos) {
  /* TBD by customer */
}

/*********************************************************************
*
*       _SetLUTEntry
*
* Purpose:
*   Should set the desired LUT entry
*/
static void _SetLUTEntry(LCD_COLOR Color, U8 Pos) {
  /* TBD by customer */
}
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*   
*/
void LCD_X_Config(void) {
  //
  // At first enable multiple buffers
  //
  GUI_MULTIBUF_Config(NUM_BUFFERS);
  //
  // Set display driver and color conversion for 1st layer
  //
  GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // Display driver configuration
  //
  if (LCD_GetSwapXY()) {
    LCD_SetSizeEx (0, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(0, YSIZE_PHYS, XSIZE_PHYS);
  } else {
    LCD_SetSizeEx (0, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(0, XSIZE_PHYS, YSIZE_PHYS);
  }
  LCD_SetVRAMAddrEx(0, (void *)VRAM_ADDR);
  //
  // Set user palette data (only required if no fixed palette is used)
  //
  #if defined(PALETTE)
    LCD_SetLUTEx(0, PALETTE);
  #endif
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if 
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;

  switch (Cmd) {
  //
  // Required
  //
  case LCD_X_INITCONTROLLER: {
    //
    // Called during the initialization process in order to set up the
    // display controller and put it into operation. If the display
    // controller is not initialized by any external routine this needs
    // to be adapted by the customer...
    //
    _InitController();
    return 0;
  }
  case LCD_X_SETVRAMADDR: {
    //
    // Required for setting the address of the video RAM for drivers
    // with memory mapped video RAM which is passed in the 'pVRAM' element of p
    //
    LCD_X_SETVRAMADDR_INFO * p;
    p = (LCD_X_SETVRAMADDR_INFO *)pData;
  
    _SetVRAMAddr(p->pVRAM);
    return 0;
  }
  case LCD_X_SHOWBUFFER: {
	LCD_X_SHOWBUFFER_INFO * p;
	p = (LCD_X_SHOWBUFFER_INFO *)pData;
  
	_PendingBuffer = p->Index;
	break;
  }
  case LCD_X_SETORG: {
    //
    // Required for setting the display origin which is passed in the 'xPos' and 'yPos' element of p
    //
    LCD_X_SETORG_INFO * p;
    p = (LCD_X_SETORG_INFO *)pData;
    _SetOrg(p->xPos, p->yPos);
    return 0;
  }
  case LCD_X_SETLUTENTRY: {
    //
    // Required for setting a lookup table entry which is passed in the 'Pos' and 'Color' element of p
    //
    LCD_X_SETLUTENTRY_INFO * p;
    p = (LCD_X_SETLUTENTRY_INFO *)pData;
    _SetLUTEntry(p->Color, p->Pos);
    return 0;
  }
  case LCD_X_ON: {
    //
    // Required if the display controller should support switching on and off
    //
    return 0;
  }
  case LCD_X_OFF: {
    //
    // Required if the display controller should support switching on and off
    //
    // ...
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/
