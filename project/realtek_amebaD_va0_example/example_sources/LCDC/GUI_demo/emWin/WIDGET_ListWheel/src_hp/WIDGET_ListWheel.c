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
File        : WIDGET_ListWheel.c
Purpose     : Demonstrates using the LISTWHEEL widget
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include "GUI.h"
#include "LISTWHEEL.h"
#include "BUTTON.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define LEFT      (1 << 0)
#define MIDDLE    (1 << 1)
#define RIGHT     (1 << 2)
#define TOP       (1 << 3)
#define BOTTOM    (1 << 4)
#define LIGHTBLUE GUI_MAKE_COLOR(0xEE8822)
#define GET_MODE  (WM_USER + 0)
#define TRANS0    GUI_MAKE_COLOR(0x11000000)
#define TRANS1    GUI_MAKE_COLOR(0xEE000000)
#define TRANS2    GUI_MAKE_COLOR(0xFF000000)

#if (GUI_USE_ARGB == 1)
  #define COLOR_CONV GUICC_M8888I
#else
  #define COLOR_CONV GUICC_8888
#endif

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 400)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  WM_HWIN           hWin;
  GUI_MEMDEV_Handle hMemOverlay;
  GUI_MEMDEV_Handle hMemRBorder;
  GUI_MEMDEV_Handle hMemLBorder;
  const GUI_FONT GUI_UNI_PTR * pFont;
} WHEEL;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static GUI_CONST_STORAGE GUI_COLOR ColorsLogoSegger_36x18[] = {
#if (GUI_USE_ARGB == 1)
   0xFFFFFFFF,0xFF5F5F5F,0xFF9EA1CB,0xFF6E72B0
  ,0xFF444444,0xFF3D4396,0xFFDBDCEB,0xFF515151
  ,0xFF494F9D,0xFF6166AA,0xFF949494,0xFFF3F3F8
  ,0xFFBCBCBC,0xFF868ABD,0xFF6C6C6C,0xFFAFAFAF
  ,0xFF292929,0xFF363636,0xFF878787,0xFFB6B9D8
  ,0xFFCFD0E5,0xFFE7E8F2,0xFFD7D7D7,0xFF7A7EB7
  ,0xFFA1A1A1,0xFFAAADD1,0xFFC2C4DE,0xFFE4E4E4
  ,0xFF797979,0xFF555BA3,0xFF9295C4,0xFFF2F2F2
  ,0xFFCACACA
#else
   0xFFFFFF,0x5F5F5F,0xCBA19E,0xB0726E
  ,0x444444,0x96433D,0xEBDCDB,0x515151
  ,0x9D4F49,0xAA6661,0x949494,0xF8F3F3
  ,0xBCBCBC,0xBD8A86,0x6C6C6C,0xAFAFAF
  ,0x292929,0x363636,0x878787,0xD8B9B6
  ,0xE5D0CF,0xF2E8E7,0xD7D7D7,0xB77E7A
  ,0xA1A1A1,0xD1ADAA,0xDEC4C2,0xE4E4E4
  ,0x797979,0xA35B55,0xC49592,0xF2F2F2
  ,0xCACACA
#endif
};

static GUI_CONST_STORAGE GUI_LOGPALETTE PalLogoSegger_36x18 = {
  33,	// number of entries
  0, 	// No transparency
  &ColorsLogoSegger_36x18[0]
};

static GUI_CONST_STORAGE unsigned char acLogoSegger_36x18[] = {
  0x07, 0x04, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04, 0x07,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
  0x01, 0x15, 0x17, 0x0B, 0x00, 0x17, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x01, 0x15, 0x08, 0x0D, 0x00, 0x09, 0x09, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x01, 0x00, 0x13, 0x05, 0x13, 0x06, 0x08, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x01, 0x00, 0x00, 0x0D, 0x08, 0x06, 0x1A, 0x05, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x01, 0x14, 0x19, 0x0B, 0x09, 0x09, 0x0B, 0x1E, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x01, 0x14, 0x05, 0x06, 0x06, 0x08, 0x0D, 0x00, 0x09, 0x08, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x01,
  0x01, 0x14, 0x05, 0x1D, 0x0B, 0x13, 0x05, 0x1A, 0x15, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x01,
  0x01, 0x14, 0x05, 0x1D, 0x0B, 0x13, 0x05, 0x1A, 0x15, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x01,
  0x01, 0x14, 0x05, 0x06, 0x06, 0x08, 0x0D, 0x00, 0x09, 0x08, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x01,
  0x01, 0x14, 0x19, 0x0B, 0x09, 0x09, 0x0B, 0x1E, 0x05, 0x06, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x01, 0x00, 0x00, 0x0D, 0x08, 0x06, 0x1A, 0x05, 0x19, 0x0C, 0x11, 0x07, 0x01, 0x0A, 0x04, 0x01, 0x12, 0x18, 0x11, 0x04, 0x07, 0x1B, 0x04, 0x07, 0x10, 0x0C, 0x01, 0x07, 0x01, 0x0F, 0x10, 0x01, 0x11, 0x0C, 0x00, 0x01,
  0x01, 0x00, 0x13, 0x05, 0x13, 0x06, 0x08, 0x0D, 0x00, 0x0F, 0x11, 0x0E, 0x12, 0x0A, 0x04, 0x01, 0x0F, 0x11, 0x0C, 0x0F, 0x01, 0x12, 0x07, 0x16, 0x0E, 0x0C, 0x01, 0x07, 0x01, 0x16, 0x10, 0x0A, 0x07, 0x18, 0x00, 0x01,
  0x01, 0x15, 0x08, 0x0D, 0x00, 0x09, 0x09, 0x0B, 0x00, 0x0C, 0x0E, 0x18, 0x10, 0x0A, 0x01, 0x0A, 0x0C, 0x04, 0x0A, 0x0A, 0x10, 0x1C, 0x04, 0x0C, 0x11, 0x0A, 0x01, 0x1C, 0x0A, 0x1B, 0x10, 0x20, 0x04, 0x18, 0x00, 0x01,
  0x01, 0x15, 0x17, 0x0B, 0x00, 0x17, 0x06, 0x00, 0x00, 0x16, 0x0E, 0x01, 0x12, 0x0C, 0x01, 0x01, 0x0E, 0x16, 0x01, 0x01, 0x0E, 0x16, 0x12, 0x01, 0x0E, 0x0F, 0x12, 0x01, 0x01, 0x0F, 0x01, 0x00, 0x0A, 0x0F, 0x00, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
  0x07, 0x04, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04, 0x07
};

GUI_CONST_STORAGE GUI_BITMAP bmLogoSegger_36x18 = {
  36, // XSize
  18, // YSize
  36, // BytesPerLine
  8, // BitsPerPixel
  acLogoSegger_36x18,  // Pointer to picture data (indices)
  &PalLogoSegger_36x18  // Pointer to palette
};

/*********************************************************************
*
*       _FontBig
*/
//
// Start of unicode area <Basic Latin>
//
GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0020[  1] = { // Code 0020, SPACE
  0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0021[ 12] = { // Code 0021, EXCLAMATION MARK
  0xFF,
  0xFF,
  0xFF,
  0xEE,
  0xDD,
  0xCC,
  0xBB,
  0x99,
  0x89,
  0x00,
  0xFF,
  0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0022[ 12] = { // Code 0022, QUOTATION MARK
  0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF,
  0xEE, 0x00, 0xEE,
  0xBC, 0x00, 0xBC
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0023[ 60] = { // Code 0023, NUMBER SIGN
  0x00, 0x02, 0xFE, 0x2F, 0xE0,
  0x00, 0x06, 0xFA, 0x6F, 0xA0,
  0x00, 0x09, 0xF6, 0x9F, 0x60,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x00, 0x6F, 0xA6, 0xFA, 0x00,
  0x00, 0x9F, 0x69, 0xF6, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x06, 0xFA, 0x6F, 0xA0, 0x00,
  0x09, 0xF6, 0x9F, 0x60, 0x00,
  0x0D, 0xF2, 0xDF, 0x20, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0024[ 60] = { // Code 0024, DOLLAR SIGN
  0x00, 0x0F, 0x00, 0x00,
  0x07, 0xEF, 0xE7, 0x00,
  0x7F, 0xFF, 0xFF, 0x70,
  0xEF, 0x4F, 0x5F, 0xD0,
  0xFF, 0x0F, 0x00, 0x00,
  0xCF, 0xBF, 0x00, 0x00,
  0x4F, 0xFF, 0xC4, 0x00,
  0x03, 0xAF, 0xFF, 0x60,
  0x00, 0x0F, 0x8F, 0xE0,
  0xEF, 0x1F, 0x0F, 0xF0,
  0xAF, 0x7F, 0x3F, 0xD0,
  0x4F, 0xFF, 0xFF, 0x60,
  0x06, 0xDF, 0xD6, 0x00,
  0x00, 0x0F, 0x00, 0x00,
  0x00, 0x0F, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0025[ 96] = { // Code 0025, PERCENT SIGN
  0x1B, 0xFF, 0xB1, 0x00, 0x03, 0xFC, 0x00, 0x00,
  0xBF, 0x44, 0xFB, 0x00, 0x0C, 0xF4, 0x00, 0x00,
  0xFF, 0x00, 0xFF, 0x00, 0x6F, 0xA0, 0x00, 0x00,
  0xFF, 0x00, 0xFF, 0x01, 0xEF, 0x20, 0x00, 0x00,
  0xBF, 0x44, 0xFB, 0x08, 0xF7, 0x00, 0x00, 0x00,
  0x1B, 0xFF, 0xB1, 0x2F, 0xD0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xBF, 0x51, 0xBF, 0xFB, 0x10,
  0x00, 0x00, 0x04, 0xFB, 0x0B, 0xF4, 0x4F, 0xB0,
  0x00, 0x00, 0x0D, 0xF2, 0x0F, 0xF0, 0x0F, 0xF0,
  0x00, 0x00, 0x7F, 0x80, 0x0F, 0xF0, 0x0F, 0xF0,
  0x00, 0x02, 0xEE, 0x10, 0x0B, 0xF4, 0x4F, 0xB0,
  0x00, 0x0A, 0xF6, 0x00, 0x01, 0xBF, 0xFB, 0x10
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0026[ 72] = { // Code 0026, AMPERSAND
  0x01, 0x9E, 0xFE, 0x81, 0x00, 0x00,
  0x0A, 0xFF, 0xFF, 0xFA, 0x00, 0x00,
  0x0F, 0xF3, 0x04, 0xFF, 0x00, 0x00,
  0x0C, 0xF7, 0x05, 0xFD, 0x00, 0x00,
  0x04, 0xFF, 0xDF, 0xE4, 0x00, 0x00,
  0x03, 0xEF, 0xFE, 0x20, 0x00, 0x00,
  0x4F, 0xE9, 0xFF, 0x71, 0x85, 0x00,
  0xCF, 0x40, 0x8F, 0xFC, 0xFD, 0x00,
  0xFF, 0x00, 0x08, 0xFF, 0xF6, 0x00,
  0xDF, 0x80, 0x17, 0xFF, 0xFA, 0x10,
  0x6F, 0xFF, 0xFF, 0xFD, 0xFF, 0xA0,
  0x05, 0xBF, 0xFD, 0x60, 0x6C, 0x10
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0027[  4] = { // Code 0027, APOSTROPHE
  0xFF,
  0xFF,
  0xEE,
  0xBC
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0028[ 30] = { // Code 0028, LEFT PARENTHESIS
  0x04, 0xFB,
  0x0B, 0xF5,
  0x2F, 0xE0,
  0x7F, 0x90,
  0xBF, 0x50,
  0xDF, 0x20,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xDF, 0x20,
  0xAF, 0x50,
  0x6F, 0x90,
  0x2F, 0xD0,
  0x0B, 0xF4,
  0x04, 0xFB
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0029[ 30] = { // Code 0029, RIGHT PARENTHESIS
  0xBF, 0x40,
  0x5F, 0xB0,
  0x0E, 0xF2,
  0x09, 0xF7,
  0x05, 0xFB,
  0x02, 0xFD,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFE,
  0x02, 0xFC,
  0x05, 0xFA,
  0x09, 0xF6,
  0x0D, 0xF2,
  0x4F, 0xB0,
  0xBF, 0x40
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_002A[ 15] = { // Code 002A, ASTERISK
  0x00, 0xF0, 0x00,
  0xBA, 0xC9, 0xB0,
  0x28, 0xF8, 0x20,
  0x3E, 0x9E, 0x20,
  0x9B, 0x0B, 0x90
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_002B[ 32] = { // Code 002B, PLUS SIGN
  0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,
  0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_002C[  5] = { // Code 002C, COMMA
  0xFF,
  0xFF,
  0x0F,
  0x7B,
  0xB2
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_002D[  6] = { // Code 002D, HYPHEN-MINUS
  0xFF, 0xFF, 0xF0,
  0xFF, 0xFF, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_002E[  2] = { // Code 002E, FULL STOP
  0xFF,
  0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_002F[ 36] = { // Code 002F, SOLIDUS
  0x00, 0x2F, 0xD0,
  0x00, 0x6F, 0x90,
  0x00, 0xAF, 0x60,
  0x00, 0xEF, 0x20,
  0x02, 0xFD, 0x00,
  0x06, 0xF9, 0x00,
  0x0A, 0xF6, 0x00,
  0x0E, 0xF2, 0x00,
  0x2F, 0xD0, 0x00,
  0x6F, 0x90, 0x00,
  0xAF, 0x60, 0x00,
  0xEF, 0x20, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0030[ 48] = { // Code 0030, DIGIT ZERO
  0x02, 0xBF, 0xFB, 0x20,
  0x1E, 0xFF, 0xFF, 0xE1,
  0x8F, 0xB1, 0x1B, 0xF7,
  0xCF, 0x30, 0x03, 0xFC,
  0xEF, 0x10, 0x01, 0xFE,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xEF, 0x10, 0x01, 0xFE,
  0xCF, 0x30, 0x03, 0xFC,
  0x7F, 0xB1, 0x1B, 0xF8,
  0x1E, 0xFF, 0xFF, 0xE1,
  0x02, 0xAF, 0xFB, 0x20
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0031[ 36] = { // Code 0031, DIGIT ONE
  0x00, 0x1E, 0xF0,
  0x00, 0xAF, 0xF0,
  0x3C, 0xFF, 0xF0,
  0xFF, 0x6F, 0xF0,
  0xC4, 0x0F, 0xF0,
  0x00, 0x0F, 0xF0,
  0x00, 0x0F, 0xF0,
  0x00, 0x0F, 0xF0,
  0x00, 0x0F, 0xF0,
  0x00, 0x0F, 0xF0,
  0x00, 0x0F, 0xF0,
  0x00, 0x0F, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0032[ 48] = { // Code 0032, DIGIT TWO
  0x04, 0xBF, 0xFC, 0x50,
  0x4F, 0xFF, 0xFF, 0xF6,
  0xBF, 0x91, 0x07, 0xFD,
  0xCE, 0x10, 0x00, 0xFF,
  0x00, 0x00, 0x04, 0xFD,
  0x00, 0x00, 0x1D, 0xF7,
  0x00, 0x02, 0xDF, 0xA0,
  0x00, 0x3E, 0xFA, 0x00,
  0x03, 0xEF, 0x70, 0x00,
  0x1E, 0xF7, 0x00, 0x00,
  0x8F, 0xFF, 0xFF, 0xFF,
  0xEF, 0xFF, 0xFF, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0033[ 48] = { // Code 0033, DIGIT THREE
  0x05, 0xCF, 0xFD, 0x80,
  0x7F, 0xFF, 0xFF, 0xF8,
  0xCF, 0x91, 0x04, 0xFF,
  0x02, 0x00, 0x16, 0xFD,
  0x00, 0x0B, 0xFF, 0xE3,
  0x00, 0x0E, 0xFF, 0xE3,
  0x00, 0x01, 0x09, 0xFB,
  0x00, 0x00, 0x01, 0xFF,
  0xBE, 0x20, 0x01, 0xFF,
  0xBF, 0xA1, 0x1A, 0xFB,
  0x3E, 0xFF, 0xFF, 0xE3,
  0x03, 0xBF, 0xFB, 0x30
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0034[ 48] = { // Code 0034, DIGIT FOUR
  0x00, 0x00, 0x2E, 0xF0,
  0x00, 0x00, 0xBF, 0xF0,
  0x00, 0x06, 0xFF, 0xF0,
  0x00, 0x2E, 0xEF, 0xF0,
  0x00, 0xBF, 0x5F, 0xF0,
  0x05, 0xFA, 0x0F, 0xF0,
  0x1E, 0xE1, 0x0F, 0xF0,
  0xAF, 0x60, 0x0F, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,
  0x00, 0x00, 0x0F, 0xF0,
  0x00, 0x00, 0x0F, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0035[ 48] = { // Code 0035, DIGIT FIVE
  0x1F, 0xFF, 0xFF, 0xF0,
  0x3F, 0xFF, 0xFF, 0xF0,
  0x6F, 0xA0, 0x00, 0x00,
  0x8F, 0x70, 0x00, 0x00,
  0xAF, 0xEF, 0xFB, 0x30,
  0xCF, 0xFF, 0xFF, 0xF4,
  0xBE, 0x60, 0x19, 0xFB,
  0x00, 0x00, 0x01, 0xFF,
  0xBE, 0x20, 0x01, 0xFE,
  0xBF, 0xB1, 0x19, 0xFA,
  0x3F, 0xFF, 0xFF, 0xE2,
  0x03, 0xBF, 0xFB, 0x30
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0036[ 48] = { // Code 0036, DIGIT SIX
  0x01, 0x8D, 0xFD, 0x70,
  0x0B, 0xFF, 0xFF, 0xF7,
  0x6F, 0xB2, 0x05, 0xEC,
  0xBF, 0x20, 0x00, 0x00,
  0xEE, 0x7D, 0xFB, 0x30,
  0xFF, 0xFF, 0xFF, 0xF4,
  0xFF, 0x91, 0x19, 0xFB,
  0xEF, 0x10, 0x01, 0xFF,
  0xCF, 0x10, 0x00, 0xFF,
  0x7F, 0xA2, 0x08, 0xFB,
  0x1D, 0xFF, 0xFF, 0xF4,
  0x01, 0x9E, 0xFB, 0x40
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0037[ 48] = { // Code 0037, DIGIT SEVEN
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,
  0x00, 0x00, 0x1D, 0xF5,
  0x00, 0x00, 0x9F, 0x70,
  0x00, 0x02, 0xFD, 0x00,
  0x00, 0x08, 0xF7, 0x00,
  0x00, 0x0E, 0xF2, 0x00,
  0x00, 0x4F, 0xB0, 0x00,
  0x00, 0x8F, 0x70, 0x00,
  0x00, 0xBF, 0x40, 0x00,
  0x00, 0xDF, 0x10, 0x00,
  0x00, 0xFF, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0038[ 48] = { // Code 0038, DIGIT EIGHT
  0x06, 0xCF, 0xFC, 0x60,
  0x7F, 0xFF, 0xFF, 0xF7,
  0xEF, 0x71, 0x17, 0xFE,
  0xFF, 0x00, 0x00, 0xFF,
  0xBF, 0x71, 0x17, 0xFB,
  0x2C, 0xFF, 0xFF, 0xC1,
  0x3D, 0xFF, 0xFF, 0xD3,
  0xBF, 0x71, 0x18, 0xFC,
  0xFF, 0x00, 0x00, 0xFF,
  0xEF, 0x71, 0x17, 0xFD,
  0x6F, 0xFF, 0xFF, 0xF6,
  0x05, 0xCF, 0xFC, 0x50
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0039[ 48] = { // Code 0039, DIGIT NINE
  0x04, 0xBF, 0xE9, 0x10,
  0x4F, 0xFF, 0xFF, 0xD1,
  0xBF, 0x80, 0x2A, 0xF7,
  0xFF, 0x10, 0x01, 0xFC,
  0xFF, 0x10, 0x01, 0xFE,
  0xBF, 0x91, 0x19, 0xFF,
  0x4F, 0xFF, 0xFF, 0xFF,
  0x03, 0xBF, 0xC6, 0xEE,
  0x00, 0x00, 0x02, 0xFB,
  0xCE, 0x50, 0x2B, 0xF6,
  0x8F, 0xFF, 0xFF, 0xB0,
  0x08, 0xEF, 0xD8, 0x10
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_003A[  9] = { // Code 003A, COLON
  0xFF,
  0xFF,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xFF,
  0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_003B[ 12] = { // Code 003B, SEMICOLON
  0xFF,
  0xFF,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xFF,
  0xFF,
  0x1F,
  0x7B,
  0xB2
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_003C[ 36] = { // Code 003C, LESS-THAN SIGN
  0x00, 0x00, 0x00, 0x4B,
  0x00, 0x00, 0x4B, 0xFF,
  0x00, 0x4B, 0xFF, 0xA3,
  0x4B, 0xFE, 0x82, 0x00,
  0xFF, 0xD2, 0x00, 0x00,
  0x4B, 0xFF, 0x92, 0x00,
  0x00, 0x4B, 0xFF, 0xA3,
  0x00, 0x00, 0x4B, 0xFF,
  0x00, 0x00, 0x00, 0x4B
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_003D[ 30] = { // Code 003D, EQUALS SIGN
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_003E[ 36] = { // Code 003E, GREATER-THAN SIGN
  0xB4, 0x00, 0x00, 0x00,
  0xFF, 0xB4, 0x00, 0x00,
  0x3A, 0xFF, 0xB4, 0x00,
  0x00, 0x29, 0xFF, 0xB4,
  0x00, 0x00, 0x2D, 0xFF,
  0x00, 0x29, 0xFF, 0xA3,
  0x3A, 0xFF, 0xB3, 0x00,
  0xFF, 0xB4, 0x00, 0x00,
  0xB4, 0x00, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_003F[ 48] = { // Code 003F, QUESTION MARK
  0x03, 0xBF, 0xFB, 0x40,
  0x2E, 0xFF, 0xFF, 0xF4,
  0xAF, 0xB2, 0x07, 0xFC,
  0xEF, 0x20, 0x00, 0xFF,
  0x00, 0x00, 0x09, 0xFC,
  0x00, 0x01, 0xBF, 0xE3,
  0x00, 0x09, 0xFE, 0x30,
  0x00, 0x0E, 0xF4, 0x00,
  0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0040[128] = { // Code 0040, COMMERCIAL AT
  0x00, 0x00, 0x39, 0xDF, 0xFE, 0xA5, 0x00, 0x00,
  0x00, 0x1B, 0xFF, 0xFF, 0xFF, 0xFF, 0xB1, 0x00,
  0x01, 0xDF, 0xE7, 0x30, 0x02, 0x7E, 0xFC, 0x00,
  0x09, 0xFD, 0x3A, 0xFC, 0x5F, 0xF4, 0xEF, 0x60,
  0x3F, 0xF2, 0xBF, 0xFF, 0xEF, 0xE0, 0x6F, 0xB0,
  0x8F, 0x95, 0xFC, 0x15, 0xFF, 0xC0, 0x1F, 0xF0,
  0xCF, 0x4B, 0xF5, 0x00, 0xFF, 0x90, 0x0F, 0xF0,
  0xFF, 0x1E, 0xF1, 0x01, 0xFF, 0x60, 0x3F, 0xC0,
  0xFF, 0x0F, 0xF0, 0x05, 0xFF, 0x30, 0xBF, 0x70,
  0xEF, 0x1E, 0xF5, 0x2D, 0xFF, 0x19, 0xFD, 0x10,
  0xBF, 0x59, 0xFF, 0xFF, 0xFF, 0xFF, 0xD2, 0x00,
  0x6F, 0xC1, 0xAF, 0xB5, 0xEF, 0xC7, 0x10, 0x00,
  0x0D, 0xFA, 0x00, 0x00, 0x00, 0x00, 0x4F, 0xFB,
  0x03, 0xEF, 0xD6, 0x30, 0x01, 0x4A, 0xFF, 0xE2,
  0x00, 0x3D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x20,
  0x00, 0x00, 0x49, 0xCF, 0xFF, 0xDA, 0x40, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0041[ 72] = { // Code 0041, LATIN CAPITAL LETTER A
  0x00, 0x01, 0xFF, 0xE0, 0x00, 0x00,
  0x00, 0x05, 0xFF, 0xF5, 0x00, 0x00,
  0x00, 0x0B, 0xF9, 0xFA, 0x00, 0x00,
  0x00, 0x1F, 0xE1, 0xEF, 0x10, 0x00,
  0x00, 0x6F, 0xA0, 0x9F, 0x60, 0x00,
  0x00, 0xBF, 0x40, 0x4F, 0xB0, 0x00,
  0x02, 0xFE, 0x00, 0x0D, 0xF1, 0x00,
  0x07, 0xFF, 0xFF, 0xFF, 0xF7, 0x00,
  0x0C, 0xFF, 0xFF, 0xFF, 0xFB, 0x00,
  0x2F, 0xE0, 0x00, 0x00, 0xEF, 0x20,
  0x7F, 0x90, 0x00, 0x00, 0x8F, 0x70,
  0xCF, 0x40, 0x00, 0x00, 0x3F, 0xC0
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0042[ 60] = { // Code 0042, LATIN CAPITAL LETTER B
  0xFF, 0xFF, 0xFF, 0xD8, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0x80,
  0xFF, 0x00, 0x00, 0x6F, 0xE0,
  0xFF, 0x00, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x00, 0x7F, 0xC0,
  0xFF, 0xFF, 0xFF, 0xFF, 0x60,
  0xFF, 0xFF, 0xFF, 0xFF, 0xE3,
  0xFF, 0x00, 0x00, 0x28, 0xFC,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x17, 0xFD,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF6,
  0xFF, 0xFF, 0xFF, 0xFC, 0x60
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0043[ 60] = { // Code 0043, LATIN CAPITAL LETTER C
  0x00, 0x5B, 0xEF, 0xEA, 0x20,
  0x08, 0xFF, 0xFF, 0xFF, 0xE3,
  0x4F, 0xF8, 0x10, 0x4D, 0xFC,
  0xAF, 0xA0, 0x00, 0x03, 0xB4,
  0xDF, 0x40, 0x00, 0x00, 0x00,
  0xFF, 0x10, 0x00, 0x00, 0x00,
  0xFF, 0x10, 0x00, 0x00, 0x00,
  0xEF, 0x40, 0x00, 0x00, 0x00,
  0xAF, 0xA0, 0x00, 0x03, 0xB4,
  0x4F, 0xF7, 0x10, 0x4D, 0xFC,
  0x08, 0xFF, 0xFF, 0xFF, 0xE3,
  0x00, 0x5B, 0xFF, 0xDA, 0x20
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0044[ 60] = { // Code 0044, LATIN CAPITAL LETTER D
  0xFF, 0xFF, 0xFF, 0xC6, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0x90,
  0xFF, 0x00, 0x02, 0x7F, 0xF4,
  0xFF, 0x00, 0x00, 0x08, 0xFA,
  0xFF, 0x00, 0x00, 0x02, 0xFD,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x02, 0xFE,
  0xFF, 0x00, 0x00, 0x06, 0xFA,
  0xFF, 0x00, 0x01, 0x5E, 0xF4,
  0xFF, 0xFF, 0xFF, 0xFF, 0x90,
  0xFF, 0xFF, 0xFF, 0xC6, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0045[ 60] = { // Code 0045, LATIN CAPITAL LETTER E
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
  0xFF, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
  0xFF, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0046[ 48] = { // Code 0046, LATIN CAPITAL LETTER F
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0xFF, 0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xF0,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0047[ 72] = { // Code 0047, LATIN CAPITAL LETTER G
  0x00, 0x39, 0xDF, 0xFD, 0x92, 0x00,
  0x08, 0xFF, 0xFF, 0xFF, 0xFE, 0x30,
  0x5F, 0xF8, 0x20, 0x05, 0xEF, 0xC0,
  0xBF, 0x80, 0x00, 0x00, 0x3B, 0x40,
  0xEF, 0x20, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xF0,
  0xDF, 0x30, 0x00, 0xFF, 0xFF, 0xF0,
  0xAF, 0x80, 0x00, 0x00, 0x0F, 0xF0,
  0x4F, 0xF7, 0x20, 0x03, 0x9F, 0xF0,
  0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0x90,
  0x00, 0x39, 0xDF, 0xFC, 0x83, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0048[ 60] = { // Code 0048, LATIN CAPITAL LETTER H
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0049[ 12] = { // Code 0049, LATIN CAPITAL LETTER I
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_004A[ 48] = { // Code 004A, LATIN CAPITAL LETTER J
  0x00, 0x00, 0x00, 0xFF,
  0x00, 0x00, 0x00, 0xFF,
  0x00, 0x00, 0x00, 0xFF,
  0x00, 0x00, 0x00, 0xFF,
  0x00, 0x00, 0x00, 0xFF,
  0x00, 0x00, 0x00, 0xFF,
  0x00, 0x00, 0x00, 0xFF,
  0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x10, 0x01, 0xFF,
  0xCF, 0x91, 0x29, 0xFC,
  0x5F, 0xFF, 0xFF, 0xF5,
  0x05, 0xCF, 0xFB, 0x40
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_004B[ 72] = { // Code 004B, LATIN CAPITAL LETTER K
  0xFF, 0x00, 0x00, 0x07, 0xFD, 0x10,
  0xFF, 0x00, 0x00, 0x7F, 0xD1, 0x00,
  0xFF, 0x00, 0x07, 0xFD, 0x10, 0x00,
  0xFF, 0x00, 0x7F, 0xD1, 0x00, 0x00,
  0xFF, 0x07, 0xFF, 0x70, 0x00, 0x00,
  0xFF, 0x7F, 0xCF, 0xE1, 0x00, 0x00,
  0xFF, 0xFB, 0x1A, 0xF7, 0x00, 0x00,
  0xFF, 0xB1, 0x02, 0xFE, 0x10, 0x00,
  0xFF, 0x10, 0x00, 0x9F, 0x90, 0x00,
  0xFF, 0x00, 0x00, 0x1E, 0xF2, 0x00,
  0xFF, 0x00, 0x00, 0x07, 0xFA, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0xEF, 0x30
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_004C[ 48] = { // Code 004C, LATIN CAPITAL LETTER L
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_004D[ 72] = { // Code 004D, LATIN CAPITAL LETTER M
  0xFF, 0xF2, 0x00, 0x02, 0xFF, 0xF0,
  0xFF, 0xF7, 0x00, 0x07, 0xFF, 0xF0,
  0xFF, 0xFB, 0x00, 0x0B, 0xFF, 0xF0,
  0xFF, 0xBF, 0x10, 0x1F, 0xBF, 0xF0,
  0xFF, 0x6F, 0x60, 0x6F, 0x6F, 0xF0,
  0xFF, 0x2F, 0xA0, 0xAF, 0x2F, 0xF0,
  0xFF, 0x0D, 0xE1, 0xED, 0x0F, 0xF0,
  0xFF, 0x08, 0xF8, 0xF8, 0x0F, 0xF0,
  0xFF, 0x04, 0xFF, 0xF4, 0x0F, 0xF0,
  0xFF, 0x00, 0xEF, 0xE0, 0x0F, 0xF0,
  0xFF, 0x00, 0xAF, 0xA0, 0x0F, 0xF0,
  0xFF, 0x00, 0x5F, 0x50, 0x0F, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_004E[ 60] = { // Code 004E, LATIN CAPITAL LETTER N
  0xFF, 0x70, 0x00, 0x00, 0xFF,
  0xFF, 0xE2, 0x00, 0x00, 0xFF,
  0xFF, 0xFB, 0x00, 0x00, 0xFF,
  0xFF, 0xAF, 0x50, 0x00, 0xFF,
  0xFF, 0x1E, 0xE1, 0x00, 0xFF,
  0xFF, 0x05, 0xF9, 0x00, 0xFF,
  0xFF, 0x00, 0xAF, 0x40, 0xFF,
  0xFF, 0x00, 0x2E, 0xD1, 0xFF,
  0xFF, 0x00, 0x06, 0xF8, 0xFF,
  0xFF, 0x00, 0x00, 0xBF, 0xFF,
  0xFF, 0x00, 0x00, 0x2E, 0xFF,
  0xFF, 0x00, 0x00, 0x06, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_004F[ 72] = { // Code 004F, LATIN CAPITAL LETTER O
  0x00, 0x5B, 0xEF, 0xEB, 0x40, 0x00,
  0x08, 0xFF, 0xFF, 0xFF, 0xF8, 0x00,
  0x3F, 0xF7, 0x10, 0x17, 0xFF, 0x30,
  0xAF, 0x80, 0x00, 0x00, 0x7F, 0xA0,
  0xDF, 0x30, 0x00, 0x00, 0x1F, 0xD0,
  0xFF, 0x00, 0x00, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x00, 0x00, 0x0F, 0xF0,
  0xEF, 0x30, 0x00, 0x00, 0x1F, 0xD0,
  0xAF, 0x70, 0x00, 0x00, 0x7F, 0xA0,
  0x4F, 0xF7, 0x10, 0x17, 0xFF, 0x40,
  0x08, 0xFF, 0xFF, 0xFF, 0xF8, 0x00,
  0x00, 0x4B, 0xEF, 0xEB, 0x40, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0050[ 60] = { // Code 0050, LATIN CAPITAL LETTER P
  0xFF, 0xFF, 0xFF, 0xC7, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0x70,
  0xFF, 0x00, 0x02, 0x8F, 0xE0,
  0xFF, 0x00, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x02, 0x9F, 0xD0,
  0xFF, 0xFF, 0xFF, 0xFF, 0x50,
  0xFF, 0xFF, 0xFE, 0xB4, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0051[ 78] = { // Code 0051, LATIN CAPITAL LETTER Q
  0x00, 0x5B, 0xEF, 0xEB, 0x40, 0x00,
  0x08, 0xFF, 0xFF, 0xFF, 0xF8, 0x00,
  0x4F, 0xF7, 0x10, 0x16, 0xEF, 0x40,
  0xAF, 0x80, 0x00, 0x00, 0x7F, 0xA0,
  0xDF, 0x30, 0x00, 0x00, 0x2F, 0xD0,
  0xFF, 0x00, 0x00, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x00, 0x00, 0x0F, 0xF0,
  0xDF, 0x20, 0x00, 0x00, 0x4F, 0xE0,
  0xAF, 0x70, 0x0A, 0x92, 0xCF, 0xC0,
  0x4F, 0xF7, 0x14, 0xEF, 0xFF, 0x60,
  0x08, 0xFF, 0xFF, 0xFF, 0xFA, 0x00,
  0x00, 0x5B, 0xEF, 0xD6, 0xBD, 0x40,
  0x00, 0x00, 0x00, 0x00, 0x1A, 0x90
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0052[ 72] = { // Code 0052, LATIN CAPITAL LETTER R
  0xFF, 0xFF, 0xFF, 0xFC, 0x70, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0x00,
  0xFF, 0x00, 0x00, 0x19, 0xFE, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
  0xFF, 0x00, 0x00, 0x29, 0xFC, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF4, 0x00,
  0xFF, 0xFF, 0xFF, 0xF8, 0x20, 0x00,
  0xFF, 0x01, 0x6E, 0xFB, 0x10, 0x00,
  0xFF, 0x00, 0x04, 0xFF, 0xA0, 0x00,
  0xFF, 0x00, 0x00, 0x7F, 0xF5, 0x00,
  0xFF, 0x00, 0x00, 0x0C, 0xFE, 0x10,
  0xFF, 0x00, 0x00, 0x02, 0xFF, 0xA0
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0053[ 60] = { // Code 0053, LATIN CAPITAL LETTER S
  0x04, 0xBE, 0xFE, 0xA3, 0x00,
  0x6F, 0xFF, 0xFF, 0xFE, 0x30,
  0xDF, 0x92, 0x02, 0xBF, 0xB0,
  0xFF, 0x30, 0x00, 0x2F, 0xE0,
  0xBF, 0xFA, 0x50, 0x00, 0x00,
  0x1C, 0xFF, 0xFE, 0x92, 0x00,
  0x00, 0x5B, 0xFF, 0xFF, 0x40,
  0x00, 0x00, 0x15, 0xBF, 0xC0,
  0xEF, 0x20, 0x00, 0x1F, 0xF0,
  0xAF, 0xB3, 0x01, 0x9F, 0xD0,
  0x2E, 0xFF, 0xFF, 0xFF, 0x50,
  0x02, 0xAE, 0xFE, 0xB4, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0054[ 60] = { // Code 0054, LATIN CAPITAL LETTER T
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0055[ 60] = { // Code 0055, LATIN CAPITAL LETTER U
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0xFF,
  0xDF, 0x30, 0x00, 0x02, 0xFD,
  0xAF, 0xD3, 0x00, 0x3B, 0xFB,
  0x2E, 0xFF, 0xFF, 0xFF, 0xE3,
  0x02, 0x9D, 0xFF, 0xEA, 0x30
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0056[ 72] = { // Code 0056, LATIN CAPITAL LETTER V
  0xCF, 0x40, 0x00, 0x00, 0x4F, 0xC0,
  0x7F, 0xA0, 0x00, 0x00, 0xAF, 0x60,
  0x1F, 0xF1, 0x00, 0x01, 0xFF, 0x10,
  0x0A, 0xF6, 0x00, 0x06, 0xFA, 0x00,
  0x04, 0xFC, 0x00, 0x0C, 0xF4, 0x00,
  0x00, 0xEF, 0x30, 0x3F, 0xD0, 0x00,
  0x00, 0x8F, 0x80, 0x8F, 0x80, 0x00,
  0x00, 0x2F, 0xE0, 0xEF, 0x20, 0x00,
  0x00, 0x0C, 0xF9, 0xFB, 0x00, 0x00,
  0x00, 0x06, 0xFF, 0xF6, 0x00, 0x00,
  0x00, 0x01, 0xFF, 0xE1, 0x00, 0x00,
  0x00, 0x00, 0xAF, 0x90, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0057[108] = { // Code 0057, LATIN CAPITAL LETTER W
  0xDF, 0x30, 0x00, 0x0D, 0xFD, 0x00, 0x00, 0x3F, 0xD0,
  0x8F, 0x70, 0x00, 0x3F, 0xFF, 0x30, 0x00, 0x7F, 0x80,
  0x4F, 0xC0, 0x00, 0x8F, 0xFF, 0x80, 0x00, 0xCF, 0x40,
  0x0E, 0xF2, 0x00, 0xDF, 0xBF, 0xD0, 0x01, 0xFE, 0x00,
  0x0A, 0xF6, 0x03, 0xFF, 0x1F, 0xF3, 0x06, 0xFA, 0x00,
  0x06, 0xFA, 0x08, 0xFA, 0x0A, 0xF8, 0x0A, 0xF6, 0x00,
  0x01, 0xFE, 0x0D, 0xF5, 0x05, 0xFD, 0x0E, 0xF2, 0x00,
  0x00, 0xCF, 0x7F, 0xE0, 0x00, 0xEF, 0x7F, 0xC0, 0x00,
  0x00, 0x7F, 0xFF, 0xA0, 0x00, 0xAF, 0xEF, 0x80, 0x00,
  0x00, 0x3F, 0xFF, 0x50, 0x00, 0x5F, 0xFF, 0x30, 0x00,
  0x00, 0x0D, 0xFE, 0x00, 0x00, 0x0E, 0xFE, 0x00, 0x00,
  0x00, 0x09, 0xFA, 0x00, 0x00, 0x0A, 0xFA, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0058[ 72] = { // Code 0058, LATIN CAPITAL LETTER X
  0x3F, 0xE2, 0x00, 0x02, 0xEF, 0x30,
  0x08, 0xFB, 0x00, 0x0A, 0xF8, 0x00,
  0x00, 0xDF, 0x60, 0x5F, 0xD0, 0x00,
  0x00, 0x3F, 0xE2, 0xEF, 0x30, 0x00,
  0x00, 0x09, 0xFE, 0xF9, 0x00, 0x00,
  0x00, 0x01, 0xDF, 0xD1, 0x00, 0x00,
  0x00, 0x01, 0xDF, 0xD1, 0x00, 0x00,
  0x00, 0x09, 0xFF, 0xF9, 0x00, 0x00,
  0x00, 0x3F, 0xE2, 0xEF, 0x40, 0x00,
  0x00, 0xDF, 0x50, 0x5F, 0xD0, 0x00,
  0x08, 0xFB, 0x00, 0x0B, 0xF8, 0x00,
  0x3F, 0xE2, 0x00, 0x02, 0xEF, 0x30
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0059[ 72] = { // Code 0059, LATIN CAPITAL LETTER Y
  0x3F, 0xE1, 0x00, 0x00, 0x1E, 0xF3,
  0x08, 0xFA, 0x00, 0x00, 0xAF, 0x80,
  0x00, 0xDF, 0x40, 0x04, 0xFD, 0x00,
  0x00, 0x3F, 0xD0, 0x0D, 0xF4, 0x00,
  0x00, 0x09, 0xF7, 0x7F, 0x90, 0x00,
  0x00, 0x01, 0xDF, 0xFD, 0x10, 0x00,
  0x00, 0x00, 0x4F, 0xF4, 0x00, 0x00,
  0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00,
  0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00,
  0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00,
  0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00,
  0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_005A[ 60] = { // Code 005A, LATIN CAPITAL LETTER Z
  0x0F, 0xFF, 0xFF, 0xFF, 0xF0,
  0x0F, 0xFF, 0xFF, 0xFF, 0xA0,
  0x00, 0x00, 0x03, 0xFE, 0x10,
  0x00, 0x00, 0x0C, 0xF5, 0x00,
  0x00, 0x00, 0x8F, 0xB0, 0x00,
  0x00, 0x03, 0xFE, 0x20, 0x00,
  0x00, 0x1D, 0xF6, 0x00, 0x00,
  0x00, 0x9F, 0xB0, 0x00, 0x00,
  0x04, 0xFE, 0x20, 0x00, 0x00,
  0x1D, 0xF6, 0x00, 0x00, 0x00,
  0xAF, 0xFF, 0xFF, 0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_005B[ 30] = { // Code 005B, LEFT SQUARE BRACKET
  0xFF, 0xFF,
  0xFF, 0xFF,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0xFF,
  0xFF, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_005C[ 36] = { // Code 005C, REVERSE SOLIDUS
  0xEF, 0x20, 0x00,
  0xAF, 0x60, 0x00,
  0x6F, 0x90, 0x00,
  0x2F, 0xD0, 0x00,
  0x0E, 0xF2, 0x00,
  0x0A, 0xF6, 0x00,
  0x06, 0xF9, 0x00,
  0x02, 0xFD, 0x00,
  0x00, 0xEF, 0x20,
  0x00, 0xAF, 0x60,
  0x00, 0x6F, 0x90,
  0x00, 0x2F, 0xD0
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_005D[ 30] = { // Code 005D, RIGHT SQUARE BRACKET
  0xFF, 0xFF,
  0xFF, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0xFF, 0xFF,
  0xFF, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_005E[ 28] = { // Code 005E, CIRCUMFLEX ACCENT
  0x00, 0x3F, 0xF4, 0x00,
  0x00, 0xAF, 0xFB, 0x00,
  0x01, 0xFC, 0xCF, 0x20,
  0x08, 0xF6, 0x6F, 0x80,
  0x0E, 0xE1, 0x1E, 0xE0,
  0x5F, 0x90, 0x09, 0xF6,
  0xCF, 0x30, 0x03, 0xFC
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_005F[ 10] = { // Code 005F, LOW LINE
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0060[  4] = { // Code 0060, GRAVE ACCENT
  0x5E, 0xF4,
  0x01, 0xAB
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0061[ 36] = { // Code 0061, LATIN SMALL LETTER A
  0x18, 0xEF, 0xEB, 0x20,
  0x9F, 0xFF, 0xFF, 0xC0,
  0xEF, 0x50, 0x3F, 0xF0,
  0x01, 0x58, 0xCF, 0xF0,
  0x4E, 0xFF, 0xFF, 0xF0,
  0xDF, 0xA6, 0x2F, 0xF0,
  0xFF, 0x30, 0x6F, 0xF0,
  0xBF, 0xFF, 0xFE, 0xF2,
  0x1B, 0xFE, 0x93, 0xF9
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0062[ 48] = { // Code 0062, LATIN SMALL LETTER B
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x4C, 0xFC, 0x40,
  0xFF, 0xFF, 0xFF, 0xF4,
  0xFF, 0xA1, 0x1A, 0xFB,
  0xFF, 0x20, 0x02, 0xFE,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x20, 0x02, 0xFE,
  0xFF, 0xB1, 0x1A, 0xFA,
  0xFF, 0xFF, 0xFF, 0xF3,
  0xFF, 0x4C, 0xFD, 0x40
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0063[ 36] = { // Code 0063, LATIN SMALL LETTER C
  0x04, 0xCF, 0xE8, 0x00,
  0x3F, 0xFF, 0xFF, 0x70,
  0xBF, 0x91, 0x4F, 0xD0,
  0xEF, 0x10, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xEF, 0x10, 0x00, 0x00,
  0xBF, 0x90, 0x4F, 0xE0,
  0x3F, 0xFF, 0xFF, 0x80,
  0x04, 0xCF, 0xE8, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0064[ 48] = { // Code 0064, LATIN SMALL LETTER D
  0x00, 0x00, 0x00, 0xFF,
  0x00, 0x00, 0x00, 0xFF,
  0x00, 0x00, 0x00, 0xFF,
  0x04, 0xCF, 0xC4, 0xFF,
  0x4F, 0xFF, 0xFF, 0xFF,
  0xBF, 0xA1, 0x1A, 0xFF,
  0xEF, 0x20, 0x02, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xEF, 0x20, 0x02, 0xFF,
  0xAF, 0xA1, 0x1A, 0xFF,
  0x3F, 0xFF, 0xFF, 0xFF,
  0x04, 0xDF, 0xC4, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0065[ 36] = { // Code 0065, LATIN SMALL LETTER E
  0x04, 0xDF, 0xD5, 0x00,
  0x3F, 0xFF, 0xFF, 0x40,
  0xAF, 0x50, 0x4F, 0xB0,
  0xEF, 0xFF, 0xFF, 0xE0,
  0xFF, 0xFF, 0xFF, 0xF0,
  0xEF, 0x10, 0x00, 0x00,
  0xBF, 0x90, 0x5F, 0xD0,
  0x4F, 0xFF, 0xFF, 0x50,
  0x05, 0xCF, 0xE7, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0066[ 36] = { // Code 0066, LATIN SMALL LETTER F
  0x04, 0xCF, 0xFB,
  0x0E, 0xFF, 0xFA,
  0x0F, 0xF1, 0x01,
  0xFF, 0xFF, 0xF0,
  0xFF, 0xFF, 0xF0,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0067[ 48] = { // Code 0067, LATIN SMALL LETTER G
  0x04, 0xDF, 0xB2, 0xFF,
  0x4F, 0xFF, 0xFD, 0xFF,
  0xBF, 0xA1, 0x1B, 0xFF,
  0xEF, 0x20, 0x02, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xEF, 0x20, 0x02, 0xFF,
  0xBF, 0xA1, 0x1B, 0xFF,
  0x3F, 0xFF, 0xFC, 0xFF,
  0x05, 0xDF, 0xA1, 0xFF,
  0xFF, 0x40, 0x16, 0xFD,
  0xAF, 0xFF, 0xFF, 0xF7,
  0x19, 0xDF, 0xFD, 0x80
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0068[ 48] = { // Code 0068, LATIN SMALL LETTER H
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x09, 0xFE, 0x91,
  0xFF, 0x8F, 0xFF, 0xFA,
  0xFF, 0xA2, 0x06, 0xFE,
  0xFF, 0x20, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0069[ 12] = { // Code 0069, LATIN SMALL LETTER I
  0xFF,
  0xFF,
  0x00,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_006A[ 30] = { // Code 006A, LATIN SMALL LETTER J
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0x00,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x02, 0xFF,
  0xAF, 0xFC,
  0xCF, 0xD3
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_006B[ 48] = { // Code 006B, LATIN SMALL LETTER K
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x5F, 0xE2,
  0xFF, 0x05, 0xFE, 0x30,
  0xFF, 0x5F, 0xF4, 0x00,
  0xFF, 0xFF, 0xF2, 0x00,
  0xFF, 0xFE, 0xF9, 0x00,
  0xFF, 0x83, 0xFE, 0x10,
  0xFF, 0x00, 0xAF, 0x70,
  0xFF, 0x00, 0x3F, 0xD0,
  0xFF, 0x00, 0x0B, 0xF4
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_006C[ 12] = { // Code 006C, LATIN SMALL LETTER L
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_006D[ 54] = { // Code 006D, LATIN SMALL LETTER M
  0xFF, 0x4C, 0xFC, 0x14, 0xDF, 0xB2,
  0xFF, 0xFF, 0xFF, 0xCF, 0xFF, 0xFB,
  0xFF, 0x90, 0x5F, 0xF9, 0x05, 0xFF,
  0xFF, 0x10, 0x0F, 0xF2, 0x00, 0xFF,
  0xFF, 0x00, 0x0F, 0xF0, 0x00, 0xFF,
  0xFF, 0x00, 0x0F, 0xF0, 0x00, 0xFF,
  0xFF, 0x00, 0x0F, 0xF0, 0x00, 0xFF,
  0xFF, 0x00, 0x0F, 0xF0, 0x00, 0xFF,
  0xFF, 0x00, 0x0F, 0xF0, 0x00, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_006E[ 36] = { // Code 006E, LATIN SMALL LETTER N
  0xFF, 0x3B, 0xFE, 0xA1,
  0xFF, 0xEF, 0xFF, 0xFA,
  0xFF, 0xB2, 0x07, 0xFE,
  0xFF, 0x20, 0x01, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_006F[ 36] = { // Code 006F, LATIN SMALL LETTER O
  0x03, 0xBF, 0xFB, 0x20,
  0x2E, 0xFF, 0xFF, 0xE2,
  0x9F, 0xB1, 0x1B, 0xF9,
  0xEF, 0x20, 0x02, 0xFE,
  0xFF, 0x00, 0x00, 0xFF,
  0xEF, 0x20, 0x02, 0xFE,
  0xAF, 0xB1, 0x1B, 0xF9,
  0x2E, 0xFF, 0xFF, 0xE2,
  0x03, 0xBF, 0xFB, 0x20
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0070[ 48] = { // Code 0070, LATIN SMALL LETTER P
  0xFF, 0x4C, 0xFD, 0x40,
  0xFF, 0xFF, 0xFF, 0xF3,
  0xFF, 0xA1, 0x1A, 0xFB,
  0xFF, 0x20, 0x02, 0xFE,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x20, 0x02, 0xFE,
  0xFF, 0xB1, 0x1A, 0xFA,
  0xFF, 0xEF, 0xFF, 0xF3,
  0xFF, 0x3C, 0xFC, 0x40,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0071[ 48] = { // Code 0071, LATIN SMALL LETTER Q
  0x04, 0xCF, 0xD5, 0xFF,
  0x4F, 0xFF, 0xFF, 0xFF,
  0xBF, 0xA1, 0x1A, 0xFF,
  0xEF, 0x20, 0x02, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xEF, 0x20, 0x03, 0xFF,
  0xAF, 0xA1, 0x2B, 0xFF,
  0x3F, 0xFF, 0xFF, 0xFF,
  0x04, 0xCF, 0xC4, 0xFF,
  0x00, 0x00, 0x00, 0xFF,
  0x00, 0x00, 0x00, 0xFF,
  0x00, 0x00, 0x00, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0072[ 27] = { // Code 0072, LATIN SMALL LETTER R
  0xFF, 0x5E, 0xFB,
  0xFF, 0xFF, 0xFB,
  0xFF, 0xB1, 0x12,
  0xFF, 0x30, 0x00,
  0xFF, 0x10, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0073[ 36] = { // Code 0073, LATIN SMALL LETTER S
  0x01, 0xAE, 0xFD, 0x80,
  0x0B, 0xFF, 0xFF, 0xF8,
  0x0F, 0xF2, 0x05, 0xFE,
  0x0D, 0xFD, 0x95, 0x10,
  0x02, 0xCF, 0xFF, 0xE5,
  0x00, 0x02, 0x6A, 0xFE,
  0x0F, 0xF5, 0x03, 0xFF,
  0x0B, 0xFF, 0xFF, 0xFA,
  0x01, 0x8D, 0xFE, 0x91
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0074[ 36] = { // Code 0074, LATIN SMALL LETTER T
  0x04, 0xB0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0xFF, 0xFF, 0xF0,
  0xFF, 0xFF, 0xF0,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF1, 0x10,
  0x0D, 0xFF, 0xA0,
  0x05, 0xEF, 0xB0
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0075[ 36] = { // Code 0075, LATIN SMALL LETTER U
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x10, 0x02, 0xFF,
  0xEF, 0x70, 0x2A, 0xFF,
  0xAF, 0xFF, 0xFE, 0xFF,
  0x1A, 0xFF, 0xB3, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0076[ 45] = { // Code 0076, LATIN SMALL LETTER V
  0x5F, 0xA0, 0x00, 0xAF, 0x50,
  0x0E, 0xF1, 0x01, 0xFE, 0x00,
  0x0A, 0xF5, 0x05, 0xFA, 0x00,
  0x04, 0xFA, 0x0A, 0xF5, 0x00,
  0x00, 0xEF, 0x1F, 0xE0, 0x00,
  0x00, 0x9F, 0xAF, 0xA0, 0x00,
  0x00, 0x4F, 0xFF, 0x40, 0x00,
  0x00, 0x0D, 0xFE, 0x00, 0x00,
  0x00, 0x08, 0xF9, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0077[ 63] = { // Code 0077, LATIN SMALL LETTER W
  0xDF, 0x20, 0x0C, 0xFD, 0x00, 0x2F, 0xD0,
  0x9F, 0x60, 0x2F, 0xFF, 0x20, 0x6F, 0x90,
  0x5F, 0xA0, 0x7F, 0xFF, 0x70, 0xAF, 0x50,
  0x1F, 0xE0, 0xBF, 0xCF, 0xB0, 0xEF, 0x10,
  0x0C, 0xF3, 0xFF, 0x3F, 0xF3, 0xFC, 0x00,
  0x08, 0xFC, 0xFB, 0x0B, 0xFC, 0xF8, 0x00,
  0x04, 0xFF, 0xF7, 0x07, 0xFF, 0xF4, 0x00,
  0x01, 0xFF, 0xF2, 0x02, 0xFF, 0xF1, 0x00,
  0x00, 0xCF, 0xC0, 0x00, 0xBF, 0xC0, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0078[ 45] = { // Code 0078, LATIN SMALL LETTER X
  0x3F, 0xE1, 0x01, 0xDF, 0x30,
  0x08, 0xF8, 0x09, 0xF7, 0x00,
  0x01, 0xDF, 0x6F, 0xC0, 0x00,
  0x00, 0x4F, 0xFF, 0x30, 0x00,
  0x00, 0x0D, 0xFC, 0x00, 0x00,
  0x00, 0x6F, 0xFF, 0x60, 0x00,
  0x01, 0xEF, 0x9F, 0xE1, 0x00,
  0x09, 0xF9, 0x0A, 0xF9, 0x00,
  0x3F, 0xE1, 0x01, 0xEF, 0x30
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_0079[ 72] = { // Code 0079, LATIN SMALL LETTER Y
  0x1F, 0xE0, 0x00, 0x00, 0xEF, 0x10,
  0x0A, 0xF6, 0x00, 0x06, 0xFA, 0x00,
  0x04, 0xFC, 0x00, 0x0C, 0xF3, 0x00,
  0x00, 0xDF, 0x40, 0x4F, 0xC0, 0x00,
  0x00, 0x7F, 0xA0, 0xAF, 0x60, 0x00,
  0x00, 0x2F, 0xF4, 0xFE, 0x10, 0x00,
  0x00, 0x0B, 0xFE, 0xF9, 0x00, 0x00,
  0x00, 0x04, 0xFF, 0xF3, 0x00, 0x00,
  0x00, 0x00, 0xEF, 0xB0, 0x00, 0x00,
  0x00, 0x02, 0xEF, 0x60, 0x00, 0x00,
  0x00, 0xFF, 0xFE, 0x00, 0x00, 0x00,
  0x00, 0xEF, 0xC3, 0x00, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_007A[ 36] = { // Code 007A, LATIN SMALL LETTER Z
  0xFF, 0xFF, 0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xF0,
  0x00, 0x00, 0x8F, 0x70,
  0x00, 0x08, 0xF8, 0x00,
  0x00, 0x8F, 0x80, 0x00,
  0x08, 0xF8, 0x00, 0x00,
  0x7F, 0x80, 0x00, 0x00,
  0xFF, 0xFF, 0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_007B[ 45] = { // Code 007B, LEFT CURLY BRACKET
  0x00, 0x3B, 0xFF,
  0x00, 0xCF, 0xFF,
  0x00, 0xFF, 0x30,
  0x00, 0xFF, 0x00,
  0x01, 0xFF, 0x00,
  0x18, 0xFD, 0x00,
  0xFF, 0xE4, 0x00,
  0xFF, 0xE3, 0x00,
  0x18, 0xFB, 0x00,
  0x01, 0xFE, 0x00,
  0x00, 0xFF, 0x00,
  0x00, 0xFF, 0x00,
  0x00, 0xEF, 0x30,
  0x00, 0xBF, 0xFF,
  0x00, 0x2B, 0xEF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_007C[ 16] = { // Code 007C, VERTICAL LINE
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_007D[ 45] = { // Code 007D, RIGHT CURLY BRACKET
  0xFF, 0xB3, 0x00,
  0xFF, 0xFC, 0x00,
  0x03, 0xFF, 0x00,
  0x00, 0xFF, 0x00,
  0x00, 0xFF, 0x10,
  0x00, 0xCF, 0x81,
  0x00, 0x4E, 0xFF,
  0x00, 0x3E, 0xFF,
  0x00, 0xBF, 0x81,
  0x00, 0xFF, 0x10,
  0x00, 0xFF, 0x00,
  0x00, 0xFF, 0x00,
  0x03, 0xFE, 0x00,
  0xFF, 0xFB, 0x00,
  0xFE, 0xB2, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_Font20B_AA4_007E[ 15] = { // Code 007E, TILDE
  0x6D, 0xFE, 0x94, 0x02, 0xA0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
  0xA2, 0x03, 0x8D, 0xFC, 0x50
};

GUI_CONST_STORAGE GUI_CHARINFO_EXT GUI_Font20B_AA4_CharInfo[95] = {
   {   1,   1,   0,  15,   5, acGUI_Font20B_AA4_0020 } // Code 0020, SPACE
  ,{   2,  12,   2,   3,   6, acGUI_Font20B_AA4_0021 } // Code 0021, EXCLAMATION MARK
  ,{   6,   4,   1,   3,   8, acGUI_Font20B_AA4_0022 } // Code 0022, QUOTATION MARK
  ,{  10,  12,   0,   3,   9, acGUI_Font20B_AA4_0023 } // Code 0023, NUMBER SIGN
  ,{   7,  15,   1,   2,   9, acGUI_Font20B_AA4_0024 } // Code 0024, DOLLAR SIGN
  ,{  15,  12,   0,   3,  16, acGUI_Font20B_AA4_0025 } // Code 0025, PERCENT SIGN
  ,{  11,  12,   1,   3,  12, acGUI_Font20B_AA4_0026 } // Code 0026, AMPERSAND
  ,{   2,   4,   1,   3,   4, acGUI_Font20B_AA4_0027 } // Code 0027, APOSTROPHE
  ,{   4,  15,   1,   3,   6, acGUI_Font20B_AA4_0028 } // Code 0028, LEFT PARENTHESIS
  ,{   4,  15,   1,   3,   6, acGUI_Font20B_AA4_0029 } // Code 0029, RIGHT PARENTHESIS
  ,{   5,   5,   1,   3,   7, acGUI_Font20B_AA4_002A } // Code 002A, ASTERISK
  ,{   8,   8,   1,   5,  10, acGUI_Font20B_AA4_002B } // Code 002B, PLUS SIGN
  ,{   2,   5,   1,  13,   5, acGUI_Font20B_AA4_002C } // Code 002C, COMMA
  ,{   5,   2,   1,  10,   6, acGUI_Font20B_AA4_002D } // Code 002D, HYPHEN-MINUS
  ,{   2,   2,   1,  13,   5, acGUI_Font20B_AA4_002E } // Code 002E, FULL STOP
  ,{   5,  12,   0,   3,   5, acGUI_Font20B_AA4_002F } // Code 002F, SOLIDUS
  ,{   8,  12,   0,   3,   9, acGUI_Font20B_AA4_0030 } // Code 0030, DIGIT ZERO
  ,{   5,  12,   1,   3,   9, acGUI_Font20B_AA4_0031 } // Code 0031, DIGIT ONE
  ,{   8,  12,   0,   3,   9, acGUI_Font20B_AA4_0032 } // Code 0032, DIGIT TWO
  ,{   8,  12,   0,   3,   9, acGUI_Font20B_AA4_0033 } // Code 0033, DIGIT THREE
  ,{   8,  12,   0,   3,   9, acGUI_Font20B_AA4_0034 } // Code 0034, DIGIT FOUR
  ,{   8,  12,   0,   3,   9, acGUI_Font20B_AA4_0035 } // Code 0035, DIGIT FIVE
  ,{   8,  12,   0,   3,   9, acGUI_Font20B_AA4_0036 } // Code 0036, DIGIT SIX
  ,{   8,  12,   0,   3,   9, acGUI_Font20B_AA4_0037 } // Code 0037, DIGIT SEVEN
  ,{   8,  12,   0,   3,   9, acGUI_Font20B_AA4_0038 } // Code 0038, DIGIT EIGHT
  ,{   8,  12,   0,   3,   9, acGUI_Font20B_AA4_0039 } // Code 0039, DIGIT NINE
  ,{   2,   9,   2,   6,   6, acGUI_Font20B_AA4_003A } // Code 003A, COLON
  ,{   2,  12,   2,   6,   6, acGUI_Font20B_AA4_003B } // Code 003B, SEMICOLON
  ,{   8,   9,   0,   5,  10, acGUI_Font20B_AA4_003C } // Code 003C, LESS-THAN SIGN
  ,{   9,   6,   0,   6,  10, acGUI_Font20B_AA4_003D } // Code 003D, EQUALS SIGN
  ,{   8,   9,   0,   5,  10, acGUI_Font20B_AA4_003E } // Code 003E, GREATER-THAN SIGN
  ,{   8,  12,   1,   3,  10, acGUI_Font20B_AA4_003F } // Code 003F, QUESTION MARK
  ,{  16,  16,   1,   3,  17, acGUI_Font20B_AA4_0040 } // Code 0040, COMMERCIAL AT
  ,{  11,  12,   0,   3,  11, acGUI_Font20B_AA4_0041 } // Code 0041, LATIN CAPITAL LETTER A
  ,{  10,  12,   1,   3,  12, acGUI_Font20B_AA4_0042 } // Code 0042, LATIN CAPITAL LETTER B
  ,{  10,  12,   1,   3,  12, acGUI_Font20B_AA4_0043 } // Code 0043, LATIN CAPITAL LETTER C
  ,{  10,  12,   1,   3,  12, acGUI_Font20B_AA4_0044 } // Code 0044, LATIN CAPITAL LETTER D
  ,{   9,  12,   1,   3,  11, acGUI_Font20B_AA4_0045 } // Code 0045, LATIN CAPITAL LETTER E
  ,{   8,  12,   1,   3,  10, acGUI_Font20B_AA4_0046 } // Code 0046, LATIN CAPITAL LETTER F
  ,{  11,  12,   1,   3,  13, acGUI_Font20B_AA4_0047 } // Code 0047, LATIN CAPITAL LETTER G
  ,{  10,  12,   1,   3,  12, acGUI_Font20B_AA4_0048 } // Code 0048, LATIN CAPITAL LETTER H
  ,{   2,  12,   1,   3,   4, acGUI_Font20B_AA4_0049 } // Code 0049, LATIN CAPITAL LETTER I
  ,{   8,  12,   0,   3,   9, acGUI_Font20B_AA4_004A } // Code 004A, LATIN CAPITAL LETTER J
  ,{  11,  12,   1,   3,  12, acGUI_Font20B_AA4_004B } // Code 004B, LATIN CAPITAL LETTER K
  ,{   8,  12,   1,   3,  10, acGUI_Font20B_AA4_004C } // Code 004C, LATIN CAPITAL LETTER L
  ,{  11,  12,   1,   3,  13, acGUI_Font20B_AA4_004D } // Code 004D, LATIN CAPITAL LETTER M
  ,{  10,  12,   1,   3,  12, acGUI_Font20B_AA4_004E } // Code 004E, LATIN CAPITAL LETTER N
  ,{  11,  12,   1,   3,  13, acGUI_Font20B_AA4_004F } // Code 004F, LATIN CAPITAL LETTER O
  ,{   9,  12,   1,   3,  11, acGUI_Font20B_AA4_0050 } // Code 0050, LATIN CAPITAL LETTER P
  ,{  11,  13,   1,   3,  13, acGUI_Font20B_AA4_0051 } // Code 0051, LATIN CAPITAL LETTER Q
  ,{  11,  12,   1,   3,  12, acGUI_Font20B_AA4_0052 } // Code 0052, LATIN CAPITAL LETTER R
  ,{   9,  12,   1,   3,  11, acGUI_Font20B_AA4_0053 } // Code 0053, LATIN CAPITAL LETTER S
  ,{  10,  12,   0,   3,  10, acGUI_Font20B_AA4_0054 } // Code 0054, LATIN CAPITAL LETTER T
  ,{  10,  12,   1,   3,  12, acGUI_Font20B_AA4_0055 } // Code 0055, LATIN CAPITAL LETTER U
  ,{  11,  12,   0,   3,  11, acGUI_Font20B_AA4_0056 } // Code 0056, LATIN CAPITAL LETTER V
  ,{  17,  12,   0,   3,  17, acGUI_Font20B_AA4_0057 } // Code 0057, LATIN CAPITAL LETTER W
  ,{  11,  12,   0,   3,  11, acGUI_Font20B_AA4_0058 } // Code 0058, LATIN CAPITAL LETTER X
  ,{  12,  12,  -1,   3,  10, acGUI_Font20B_AA4_0059 } // Code 0059, LATIN CAPITAL LETTER Y
  ,{   9,  12,   0,   3,   9, acGUI_Font20B_AA4_005A } // Code 005A, LATIN CAPITAL LETTER Z
  ,{   4,  15,   1,   3,   6, acGUI_Font20B_AA4_005B } // Code 005B, LEFT SQUARE BRACKET
  ,{   5,  12,   0,   3,   5, acGUI_Font20B_AA4_005C } // Code 005C, REVERSE SOLIDUS
  ,{   4,  15,   1,   3,   6, acGUI_Font20B_AA4_005D } // Code 005D, RIGHT SQUARE BRACKET
  ,{   8,   7,   1,   3,  10, acGUI_Font20B_AA4_005E } // Code 005E, CIRCUMFLEX ACCENT
  ,{   9,   2,   0,  16,   9, acGUI_Font20B_AA4_005F } // Code 005F, LOW LINE
  ,{   4,   2,   0,   3,   6, acGUI_Font20B_AA4_0060 } // Code 0060, GRAVE ACCENT
  ,{   8,   9,   1,   6,   9, acGUI_Font20B_AA4_0061 } // Code 0061, LATIN SMALL LETTER A
  ,{   8,  12,   1,   3,  10, acGUI_Font20B_AA4_0062 } // Code 0062, LATIN SMALL LETTER B
  ,{   7,   9,   1,   6,   9, acGUI_Font20B_AA4_0063 } // Code 0063, LATIN SMALL LETTER C
  ,{   8,  12,   1,   3,  10, acGUI_Font20B_AA4_0064 } // Code 0064, LATIN SMALL LETTER D
  ,{   7,   9,   1,   6,   9, acGUI_Font20B_AA4_0065 } // Code 0065, LATIN SMALL LETTER E
  ,{   6,  12,   0,   3,   5, acGUI_Font20B_AA4_0066 } // Code 0066, LATIN SMALL LETTER F
  ,{   8,  12,   1,   6,  10, acGUI_Font20B_AA4_0067 } // Code 0067, LATIN SMALL LETTER G
  ,{   8,  12,   1,   3,  10, acGUI_Font20B_AA4_0068 } // Code 0068, LATIN SMALL LETTER H
  ,{   2,  12,   1,   3,   4, acGUI_Font20B_AA4_0069 } // Code 0069, LATIN SMALL LETTER I
  ,{   4,  15,  -1,   3,   4, acGUI_Font20B_AA4_006A } // Code 006A, LATIN SMALL LETTER J
  ,{   8,  12,   1,   3,   9, acGUI_Font20B_AA4_006B } // Code 006B, LATIN SMALL LETTER K
  ,{   2,  12,   1,   3,   4, acGUI_Font20B_AA4_006C } // Code 006C, LATIN SMALL LETTER L
  ,{  12,   9,   1,   6,  14, acGUI_Font20B_AA4_006D } // Code 006D, LATIN SMALL LETTER M
  ,{   8,   9,   1,   6,  10, acGUI_Font20B_AA4_006E } // Code 006E, LATIN SMALL LETTER N
  ,{   8,   9,   1,   6,  10, acGUI_Font20B_AA4_006F } // Code 006F, LATIN SMALL LETTER O
  ,{   8,  12,   1,   6,  10, acGUI_Font20B_AA4_0070 } // Code 0070, LATIN SMALL LETTER P
  ,{   8,  12,   1,   6,  10, acGUI_Font20B_AA4_0071 } // Code 0071, LATIN SMALL LETTER Q
  ,{   6,   9,   1,   6,   7, acGUI_Font20B_AA4_0072 } // Code 0072, LATIN SMALL LETTER R
  ,{   8,   9,   0,   6,   9, acGUI_Font20B_AA4_0073 } // Code 0073, LATIN SMALL LETTER S
  ,{   5,  12,   0,   3,   6, acGUI_Font20B_AA4_0074 } // Code 0074, LATIN SMALL LETTER T
  ,{   8,   9,   1,   6,  10, acGUI_Font20B_AA4_0075 } // Code 0075, LATIN SMALL LETTER U
  ,{   9,   9,   0,   6,   9, acGUI_Font20B_AA4_0076 } // Code 0076, LATIN SMALL LETTER V
  ,{  13,   9,   0,   6,  13, acGUI_Font20B_AA4_0077 } // Code 0077, LATIN SMALL LETTER W
  ,{   9,   9,   0,   6,   9, acGUI_Font20B_AA4_0078 } // Code 0078, LATIN SMALL LETTER X
  ,{  11,  12,  -1,   6,   9, acGUI_Font20B_AA4_0079 } // Code 0079, LATIN SMALL LETTER Y
  ,{   7,   9,   1,   6,   9, acGUI_Font20B_AA4_007A } // Code 007A, LATIN SMALL LETTER Z
  ,{   6,  15,   1,   3,   7, acGUI_Font20B_AA4_007B } // Code 007B, LEFT CURLY BRACKET
  ,{   2,  16,   1,   3,   4, acGUI_Font20B_AA4_007C } // Code 007C, VERTICAL LINE
  ,{   6,  15,   0,   3,   7, acGUI_Font20B_AA4_007D } // Code 007D, RIGHT CURLY BRACKET
  ,{   9,   3,   0,   8,  10, acGUI_Font20B_AA4_007E } // Code 007E, TILDE
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_Font20B_AA4_Prop1 = {
   0x0020 // first character
  ,0x007E // last character 
  ,&GUI_Font20B_AA4_CharInfo[  0] // address of first character
  ,(GUI_CONST_STORAGE GUI_FONT_PROP_EXT *)0 // pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT _FontBig = {
   GUI_FONTTYPE_PROP_AA4_EXT // type of font   
  ,19 // height of font 
  ,19 // space of font y
  ,1 // magnification x
  ,1 // magnification y
  ,{&GUI_Font20B_AA4_Prop1}
  ,19 // Baseline
  ,9 // Height of lowercase characters
  ,12 // Height of capital characters
};

/*********************************************************************
*
*       _FontSmall
*/
//
// Start of unicode area <Basic Latin>
//
GUI_CONST_STORAGE unsigned char acGUI_Font14_0020[ 14] = { // Code 0020, SPACE
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0021[ 14] = { // Code 0021, EXCLAMATION MARK
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  XX______,
  XX______,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0022[ 14] = { // Code 0022, QUOTATION MARK
  ________,
  ________,
  XX_XX___,
  XX_XX___,
  XX_XX___,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0023[ 14] = { // Code 0023, NUMBER SIGN
  ________,
  ________,
  __X__X__,
  __X__X__,
  XXXXXX__,
  _X__X___,
  _X__X___,
  XXXXXX__,
  _X__X___,
  X__X____,
  X__X____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0024[ 14] = { // Code 0024, DOLLAR SIGN
  ________,
  ___X____,
  __XXX___,
  _X_X_X__,
  _X_X____,
  _XXX____,
  __XXX___,
  ___XXX__,
  ___X_X__,
  _X_X_X__,
  __XXX___,
  ___X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0025[ 28] = { // Code 0025, PERCENT SIGN
  ________,________,
  ________,________,
  XXX__X__,________,
  X_X__X__,________,
  X_X_X___,________,
  X_X_X___,________,
  XXX_XXXX,________,
  ___X_X_X,________,
  ___X_X_X,________,
  __X__X_X,________,
  __X__XXX,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0026[ 28] = { // Code 0026, AMPERSAND
  ________,________,
  ________,________,
  __XXX___,________,
  _XX_XX__,________,
  _XX_XX__,________,
  __XXX___,________,
  _XXXX___,________,
  XX_XX_XX,________,
  XX__XXX_,________,
  XX__XXXX,________,
  _XXXX_XX,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0027[ 14] = { // Code 0027, APOSTROPHE
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0028[ 14] = { // Code 0028, LEFT PARENTHESIS
  ________,
  ________,
  __X_____,
  _XX_____,
  _X______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  _X______,
  _XX_____,
  __X_____,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0029[ 14] = { // Code 0029, RIGHT PARENTHESIS
  ________,
  ________,
  X_______,
  XX______,
  _X______,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _X______,
  XX______,
  X_______,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_002A[ 14] = { // Code 002A, ASTERISK
  ________,
  ________,
  __X_____,
  _XXX____,
  __X_____,
  _X_X____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_002B[ 14] = { // Code 002B, PLUS SIGN
  ________,
  ________,
  ________,
  ________,
  __XX____,
  __XX____,
  XXXXXX__,
  __XX____,
  __XX____,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_002C[ 14] = { // Code 002C, COMMA
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XX______,
  XX______,
  _X______,
  X_______,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_002D[ 14] = { // Code 002D, HYPHEN-MINUS
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XXX_____,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_002E[ 14] = { // Code 002E, FULL STOP
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XX______,
  XX______,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_002F[ 14] = { // Code 002F, SOLIDUS
  ________,
  ________,
  __X_____,
  __X_____,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  X_______,
  X_______,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0030[ 14] = { // Code 0030, DIGIT ZERO
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0031[ 14] = { // Code 0031, DIGIT ONE
  ________,
  ________,
  ___XX___,
  __XXX___,
  _XXXX___,
  _X_XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0032[ 14] = { // Code 0032, DIGIT TWO
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  ____XX__,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  XX______,
  XXXXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0033[ 14] = { // Code 0033, DIGIT THREE
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  ____XX__,
  __XXX___,
  ____XX__,
  ____XX__,
  ____XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0034[ 14] = { // Code 0034, DIGIT FOUR
  ________,
  ________,
  ___XX___,
  __XXX___,
  __XXX___,
  _X_XX___,
  _X_XX___,
  X__XX___,
  XXXXXX__,
  ___XX___,
  ___XX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0035[ 14] = { // Code 0035, DIGIT FIVE
  ________,
  ________,
  _XXXXX__,
  _XX_____,
  XX______,
  XXXXX___,
  XX__XX__,
  ____XX__,
  ____XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0036[ 14] = { // Code 0036, DIGIT SIX
  ________,
  ________,
  __XXX___,
  _X__XX__,
  XX______,
  XXXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0037[ 14] = { // Code 0037, DIGIT SEVEN
  ________,
  ________,
  XXXXXX__,
  ____XX__,
  ___XX___,
  ___XX___,
  __XX____,
  __XX____,
  _XX_____,
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0038[ 14] = { // Code 0038, DIGIT EIGHT
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0039[ 14] = { // Code 0039, DIGIT NINE
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXXX__,
  ____XX__,
  XX__X___,
  _XXX____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_003A[ 14] = { // Code 003A, COLON
  ________,
  ________,
  ________,
  ________,
  XX______,
  XX______,
  ________,
  ________,
  ________,
  XX______,
  XX______,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_003B[ 14] = { // Code 003B, SEMICOLON
  ________,
  ________,
  ________,
  ________,
  XX______,
  XX______,
  ________,
  ________,
  ________,
  XX______,
  XX______,
  _X______,
  X_______,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_003C[ 14] = { // Code 003C, LESS-THAN SIGN
  ________,
  ________,
  ________,
  _____X__,
  ___XXX__,
  _XXX____,
  XX______,
  _XXX____,
  ___XXX__,
  _____X__,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_003D[ 14] = { // Code 003D, EQUALS SIGN
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXXXX__,
  ________,
  XXXXXX__,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_003E[ 14] = { // Code 003E, GREATER-THAN SIGN
  ________,
  ________,
  ________,
  X_______,
  XXX_____,
  __XXX___,
  ____XX__,
  __XXX___,
  XXX_____,
  X_______,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_003F[ 14] = { // Code 003F, QUESTION MARK
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  ____XX__,
  ___XX___,
  __XX____,
  __XX____,
  ________,
  __XX____,
  __XX____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0040[ 28] = { // Code 0040, COMMERCIAL AT
  ________,________,
  ________,________,
  ___XXXXX,________,
  __XX____,XX______,
  _X__XX_X,XXX_____,
  _X_XXXXX,X_X_____,
  X_XX__XX,__X_____,
  X_XX__XX,__X_____,
  X_XX__XX,__X_____,
  X_XXXXXX,_X______,
  X__XX_XX,X_______,
  _X______,__X_____,
  __X_____,_X______,
  ___XXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0041[ 14] = { // Code 0041, LATIN CAPITAL LETTER A
  ________,
  ________,
  __XXX___,
  __XXX___,
  _XX_XX__,
  _XX_XX__,
  _XX_XX__,
  _XX_XX__,
  XXXXXXX_,
  XX___XX_,
  XX___XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0042[ 14] = { // Code 0042, LATIN CAPITAL LETTER B
  ________,
  ________,
  XXXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XXXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XXXXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0043[ 14] = { // Code 0043, LATIN CAPITAL LETTER C
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  _XX__XX_,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0044[ 14] = { // Code 0044, LATIN CAPITAL LETTER D
  ________,
  ________,
  XXXXX___,
  XX__XX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX__XX__,
  XXXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0045[ 14] = { // Code 0045, LATIN CAPITAL LETTER E
  ________,
  ________,
  XXXXXX__,
  XX______,
  XX______,
  XX______,
  XXXXXX__,
  XX______,
  XX______,
  XX______,
  XXXXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0046[ 14] = { // Code 0046, LATIN CAPITAL LETTER F
  ________,
  ________,
  XXXXX___,
  XX______,
  XX______,
  XX______,
  XXXXX___,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0047[ 14] = { // Code 0047, LATIN CAPITAL LETTER G
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  XX______,
  XX______,
  XX__XXX_,
  XX___XX_,
  XX___XX_,
  _XX__XX_,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0048[ 14] = { // Code 0048, LATIN CAPITAL LETTER H
  ________,
  ________,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XXXXXXX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0049[ 14] = { // Code 0049, LATIN CAPITAL LETTER I
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_004A[ 14] = { // Code 004A, LATIN CAPITAL LETTER J
  ________,
  ________,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_004B[ 14] = { // Code 004B, LATIN CAPITAL LETTER K
  ________,
  ________,
  XX___XX_,
  XX__XX__,
  XX_XX___,
  XXXXX___,
  XXXXXX__,
  XX__XX__,
  XX__XX__,
  XX___XX_,
  XX___XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_004C[ 14] = { // Code 004C, LATIN CAPITAL LETTER L
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XXXXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_004D[ 28] = { // Code 004D, LATIN CAPITAL LETTER M
  ________,________,
  ________,________,
  XXX___XX,X_______,
  XXX___XX,X_______,
  XXXX_XXX,X_______,
  XXXX_XXX,X_______,
  XX_X_X_X,X_______,
  XX_X_X_X,X_______,
  XX_XXX_X,X_______,
  XX_XXX_X,X_______,
  XX__X__X,X_______,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_004E[ 14] = { // Code 004E, LATIN CAPITAL LETTER N
  ________,
  ________,
  XX___XX_,
  XXX__XX_,
  XXX__XX_,
  XXXX_XX_,
  XX_X_XX_,
  XX_XXXX_,
  XX__XXX_,
  XX__XXX_,
  XX___XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_004F[ 28] = { // Code 004F, LATIN CAPITAL LETTER O
  ________,________,
  ________,________,
  __XXXX__,________,
  _XX__XX_,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  _XX__XX_,________,
  __XXXX__,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0050[ 14] = { // Code 0050, LATIN CAPITAL LETTER P
  ________,
  ________,
  XXXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XXXXXX__,
  XX______,
  XX______,
  XX______,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0051[ 28] = { // Code 0051, LATIN CAPITAL LETTER Q
  ________,________,
  ________,________,
  __XXXX__,________,
  _XX__XX_,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX__X_XX,________,
  _XX__XX_,________,
  __XXXXX_,________,
  _______X,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0052[ 14] = { // Code 0052, LATIN CAPITAL LETTER R
  ________,
  ________,
  XXXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XXXXXX__,
  XX__XX__,
  XX___XX_,
  XX___XX_,
  XX____XX,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0053[ 14] = { // Code 0053, LATIN CAPITAL LETTER S
  ________,
  ________,
  _XXXXX__,
  XX___XX_,
  XX______,
  XXXX____,
  _XXXXX__,
  ___XXXX_,
  _____XX_,
  XX___XX_,
  _XXXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0054[ 14] = { // Code 0054, LATIN CAPITAL LETTER T
  ________,
  ________,
  XXXXXX__,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0055[ 14] = { // Code 0055, LATIN CAPITAL LETTER U
  ________,
  ________,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _XXXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0056[ 28] = { // Code 0056, LATIN CAPITAL LETTER V
  ________,________,
  ________,________,
  XX_____X,X_______,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  __XX_XX_,________,
  __XX_XX_,________,
  __XX_XX_,________,
  ___XXX__,________,
  ___XXX__,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0057[ 28] = { // Code 0057, LATIN CAPITAL LETTER W
  ________,________,
  ________,________,
  XX___XXX,___XX___,
  XX___XXX,___XX___,
  _XX_XXXX,X_XX____,
  _XX_XX_X,X_XX____,
  _XX_XX_X,X_XX____,
  _XX_XX_X,X_XX____,
  __XXX___,XXX_____,
  __XXX___,XXX_____,
  __XXX___,XXX_____,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0058[ 14] = { // Code 0058, LATIN CAPITAL LETTER X
  ________,
  ________,
  XX___XX_,
  XX___XX_,
  _XX_XX__,
  _XXXXX__,
  __XXX___,
  _XXXXX__,
  _XX_XX__,
  XX___XX_,
  XX___XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0059[ 14] = { // Code 0059, LATIN CAPITAL LETTER Y
  ________,
  ________,
  XX____XX,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_005A[ 14] = { // Code 005A, LATIN CAPITAL LETTER Z
  ________,
  ________,
  XXXXXX__,
  ____XX__,
  ___XX___,
  __XX____,
  __XX____,
  _XX_____,
  XX______,
  XX______,
  XXXXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_005B[ 14] = { // Code 005B, LEFT SQUARE BRACKET
  ________,
  ________,
  XXX_____,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XXX_____,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_005C[ 14] = { // Code 005C, REVERSE SOLIDUS
  ________,
  ________,
  X_______,
  X_______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  __X_____,
  __X_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_005D[ 14] = { // Code 005D, RIGHT SQUARE BRACKET
  ________,
  ________,
  XXX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  XXX_____,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_005E[ 14] = { // Code 005E, CIRCUMFLEX ACCENT
  ________,
  ________,
  __XX____,
  __XX____,
  _XXXX___,
  _X__X___,
  XX__XX__,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_005F[ 14] = { // Code 005F, LOW LINE
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXXXXX_,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0060[ 14] = { // Code 0060, GRAVE ACCENT
  ________,
  ________,
  XX______,
  _XX_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0061[ 14] = { // Code 0061, LATIN SMALL LETTER A
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  X___XX__,
  __XXXX__,
  _XX_XX__,
  XX__XX__,
  XX__XX__,
  _XXXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0062[ 14] = { // Code 0062, LATIN SMALL LETTER B
  ________,
  ________,
  XX______,
  XX______,
  XX_XX___,
  XXX_XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XXX_XX__,
  XX_XX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0063[ 14] = { // Code 0063, LATIN SMALL LETTER C
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XX______,
  XX______,
  XX______,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0064[ 14] = { // Code 0064, LATIN SMALL LETTER D
  ________,
  ________,
  ____XX__,
  ____XX__,
  _XX_XX__,
  XX_XXX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX_XXX__,
  _XX_XX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0065[ 14] = { // Code 0065, LATIN SMALL LETTER E
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XXXXXX__,
  XX______,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0066[ 14] = { // Code 0066, LATIN SMALL LETTER F
  ________,
  ________,
  _XXX____,
  XX______,
  XXX_____,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0067[ 14] = { // Code 0067, LATIN SMALL LETTER G
  ________,
  ________,
  ________,
  ________,
  _XX_XX__,
  XX_XXX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX_XXX__,
  _XX_XX__,
  X___XX__,
  _XXXX___,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0068[ 14] = { // Code 0068, LATIN SMALL LETTER H
  ________,
  ________,
  XX______,
  XX______,
  XX_XX___,
  XXX_XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0069[ 14] = { // Code 0069, LATIN SMALL LETTER I
  ________,
  ________,
  XX______,
  ________,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_006A[ 14] = { // Code 006A, LATIN SMALL LETTER J
  ________,
  ________,
  XX______,
  ________,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  X_______,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_006B[ 14] = { // Code 006B, LATIN SMALL LETTER K
  ________,
  ________,
  XX______,
  XX______,
  XX__XX__,
  XX_XX___,
  XXXX____,
  XXXXX___,
  XX_XX___,
  XX__XX__,
  XX__XX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_006C[ 14] = { // Code 006C, LATIN SMALL LETTER L
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_006D[ 28] = { // Code 006D, LATIN SMALL LETTER M
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  XX_XXX_X,X_______,
  XXX_XXX_,XX______,
  XX__XX__,XX______,
  XX__XX__,XX______,
  XX__XX__,XX______,
  XX__XX__,XX______,
  XX__XX__,XX______,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_006E[ 14] = { // Code 006E, LATIN SMALL LETTER N
  ________,
  ________,
  ________,
  ________,
  XX_XX___,
  XXX_XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_006F[ 14] = { // Code 006F, LATIN SMALL LETTER O
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0070[ 14] = { // Code 0070, LATIN SMALL LETTER P
  ________,
  ________,
  ________,
  ________,
  XX_XX___,
  XXX_XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XXX_XX__,
  XX_XX___,
  XX______,
  XX______,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0071[ 14] = { // Code 0071, LATIN SMALL LETTER Q
  ________,
  ________,
  ________,
  ________,
  _XX_XX__,
  XX_XXX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX_XXX__,
  _XX_XX__,
  ____XX__,
  ____XX__,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0072[ 14] = { // Code 0072, LATIN SMALL LETTER R
  ________,
  ________,
  ________,
  ________,
  XXXX____,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0073[ 14] = { // Code 0073, LATIN SMALL LETTER S
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XXX_____,
  _XXXX___,
  ___XXX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0074[ 14] = { // Code 0074, LATIN SMALL LETTER T
  ________,
  ________,
  _X______,
  XX______,
  XXX_____,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0075[ 14] = { // Code 0075, LATIN SMALL LETTER U
  ________,
  ________,
  ________,
  ________,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX_XXX__,
  _XX_XX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0076[ 14] = { // Code 0076, LATIN SMALL LETTER V
  ________,
  ________,
  ________,
  ________,
  XX___XX_,
  XX___XX_,
  _XX_XX__,
  _XX_XX__,
  _XX_XX__,
  __XXX___,
  __XXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0077[ 28] = { // Code 0077, LATIN SMALL LETTER W
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  XX__X__X,X_______,
  XX_XXX_X,X_______,
  XX_XXX_X,X_______,
  XX_X_X_X,X_______,
  _XXX_XXX,________,
  _XXX_XXX,________,
  _XX___XX,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0078[ 14] = { // Code 0078, LATIN SMALL LETTER X
  ________,
  ________,
  ________,
  ________,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  __XX____,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_0079[ 14] = { // Code 0079, LATIN SMALL LETTER Y
  ________,
  ________,
  ________,
  ________,
  XX___XX_,
  XX___XX_,
  _XX_XX__,
  _XX_XX__,
  _XX_XX__,
  __XXX___,
  __XXX___,
  __XX____,
  _XX_____,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_007A[ 14] = { // Code 007A, LATIN SMALL LETTER Z
  ________,
  ________,
  ________,
  ________,
  XXXXX___,
  ___XX___,
  __XX____,
  _XX_____,
  _XX_____,
  XX______,
  XXXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_007B[ 14] = { // Code 007B, LEFT CURLY BRACKET
  ________,
  ________,
  __XXX___,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  XX______,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  __XXX___,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_007C[ 14] = { // Code 007C, VERTICAL LINE
  ________,
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_007D[ 14] = { // Code 007D, RIGHT CURLY BRACKET
  ________,
  ________,
  XX______,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  __XX____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  XX______,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_Font14_007E[ 14] = { // Code 007E, TILDE
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX__X__,
  X__XX___,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE GUI_CHARINFO GUI_Font14_CharInfo[95] = {
   {   3,   3,  1, acGUI_Font14_0020 } // Code 0020
  ,{   3,   3,  1, acGUI_Font14_0021 } // Code 0021
  ,{   6,   6,  1, acGUI_Font14_0022 } // Code 0022
  ,{   7,   7,  1, acGUI_Font14_0023 } // Code 0023
  ,{   7,   7,  1, acGUI_Font14_0024 } // Code 0024
  ,{   9,   9,  2, acGUI_Font14_0025 } // Code 0025
  ,{   9,   9,  2, acGUI_Font14_0026 } // Code 0026
  ,{   3,   3,  1, acGUI_Font14_0027 } // Code 0027
  ,{   4,   4,  1, acGUI_Font14_0028 } // Code 0028
  ,{   4,   4,  1, acGUI_Font14_0029 } // Code 0029
  ,{   5,   5,  1, acGUI_Font14_002A } // Code 002A
  ,{   7,   7,  1, acGUI_Font14_002B } // Code 002B
  ,{   3,   3,  1, acGUI_Font14_002C } // Code 002C
  ,{   4,   4,  1, acGUI_Font14_002D } // Code 002D
  ,{   3,   3,  1, acGUI_Font14_002E } // Code 002E
  ,{   3,   3,  1, acGUI_Font14_002F } // Code 002F
  ,{   7,   7,  1, acGUI_Font14_0030 } // Code 0030
  ,{   7,   7,  1, acGUI_Font14_0031 } // Code 0031
  ,{   7,   7,  1, acGUI_Font14_0032 } // Code 0032
  ,{   7,   7,  1, acGUI_Font14_0033 } // Code 0033
  ,{   7,   7,  1, acGUI_Font14_0034 } // Code 0034
  ,{   7,   7,  1, acGUI_Font14_0035 } // Code 0035
  ,{   7,   7,  1, acGUI_Font14_0036 } // Code 0036
  ,{   7,   7,  1, acGUI_Font14_0037 } // Code 0037
  ,{   7,   7,  1, acGUI_Font14_0038 } // Code 0038
  ,{   7,   7,  1, acGUI_Font14_0039 } // Code 0039
  ,{   3,   3,  1, acGUI_Font14_003A } // Code 003A
  ,{   3,   3,  1, acGUI_Font14_003B } // Code 003B
  ,{   7,   7,  1, acGUI_Font14_003C } // Code 003C
  ,{   7,   7,  1, acGUI_Font14_003D } // Code 003D
  ,{   7,   7,  1, acGUI_Font14_003E } // Code 003E
  ,{   7,   7,  1, acGUI_Font14_003F } // Code 003F
  ,{  12,  12,  2, acGUI_Font14_0040 } // Code 0040
  ,{   8,   8,  1, acGUI_Font14_0041 } // Code 0041
  ,{   8,   8,  1, acGUI_Font14_0042 } // Code 0042
  ,{   8,   8,  1, acGUI_Font14_0043 } // Code 0043
  ,{   8,   8,  1, acGUI_Font14_0044 } // Code 0044
  ,{   7,   7,  1, acGUI_Font14_0045 } // Code 0045
  ,{   6,   6,  1, acGUI_Font14_0046 } // Code 0046
  ,{   8,   8,  1, acGUI_Font14_0047 } // Code 0047
  ,{   8,   8,  1, acGUI_Font14_0048 } // Code 0048
  ,{   3,   3,  1, acGUI_Font14_0049 } // Code 0049
  ,{   7,   7,  1, acGUI_Font14_004A } // Code 004A
  ,{   8,   8,  1, acGUI_Font14_004B } // Code 004B
  ,{   7,   7,  1, acGUI_Font14_004C } // Code 004C
  ,{  10,  10,  2, acGUI_Font14_004D } // Code 004D
  ,{   8,   8,  1, acGUI_Font14_004E } // Code 004E
  ,{   9,   9,  2, acGUI_Font14_004F } // Code 004F
  ,{   8,   8,  1, acGUI_Font14_0050 } // Code 0050
  ,{   9,   9,  2, acGUI_Font14_0051 } // Code 0051
  ,{   8,   8,  1, acGUI_Font14_0052 } // Code 0052
  ,{   8,   8,  1, acGUI_Font14_0053 } // Code 0053
  ,{   7,   7,  1, acGUI_Font14_0054 } // Code 0054
  ,{   8,   8,  1, acGUI_Font14_0055 } // Code 0055
  ,{   9,   9,  2, acGUI_Font14_0056 } // Code 0056
  ,{  13,  13,  2, acGUI_Font14_0057 } // Code 0057
  ,{   8,   8,  1, acGUI_Font14_0058 } // Code 0058
  ,{   8,   8,  1, acGUI_Font14_0059 } // Code 0059
  ,{   7,   7,  1, acGUI_Font14_005A } // Code 005A
  ,{   4,   4,  1, acGUI_Font14_005B } // Code 005B
  ,{   3,   3,  1, acGUI_Font14_005C } // Code 005C
  ,{   4,   4,  1, acGUI_Font14_005D } // Code 005D
  ,{   7,   7,  1, acGUI_Font14_005E } // Code 005E
  ,{   7,   7,  1, acGUI_Font14_005F } // Code 005F
  ,{   4,   4,  1, acGUI_Font14_0060 } // Code 0060
  ,{   7,   7,  1, acGUI_Font14_0061 } // Code 0061
  ,{   7,   7,  1, acGUI_Font14_0062 } // Code 0062
  ,{   7,   7,  1, acGUI_Font14_0063 } // Code 0063
  ,{   7,   7,  1, acGUI_Font14_0064 } // Code 0064
  ,{   7,   7,  1, acGUI_Font14_0065 } // Code 0065
  ,{   4,   4,  1, acGUI_Font14_0066 } // Code 0066
  ,{   7,   7,  1, acGUI_Font14_0067 } // Code 0067
  ,{   7,   7,  1, acGUI_Font14_0068 } // Code 0068
  ,{   3,   3,  1, acGUI_Font14_0069 } // Code 0069
  ,{   3,   3,  1, acGUI_Font14_006A } // Code 006A
  ,{   7,   7,  1, acGUI_Font14_006B } // Code 006B
  ,{   3,   3,  1, acGUI_Font14_006C } // Code 006C
  ,{  11,  11,  2, acGUI_Font14_006D } // Code 006D
  ,{   7,   7,  1, acGUI_Font14_006E } // Code 006E
  ,{   7,   7,  1, acGUI_Font14_006F } // Code 006F
  ,{   7,   7,  1, acGUI_Font14_0070 } // Code 0070
  ,{   7,   7,  1, acGUI_Font14_0071 } // Code 0071
  ,{   5,   5,  1, acGUI_Font14_0072 } // Code 0072
  ,{   7,   7,  1, acGUI_Font14_0073 } // Code 0073
  ,{   4,   4,  1, acGUI_Font14_0074 } // Code 0074
  ,{   7,   7,  1, acGUI_Font14_0075 } // Code 0075
  ,{   7,   7,  1, acGUI_Font14_0076 } // Code 0076
  ,{  10,  10,  2, acGUI_Font14_0077 } // Code 0077
  ,{   7,   7,  1, acGUI_Font14_0078 } // Code 0078
  ,{   7,   7,  1, acGUI_Font14_0079 } // Code 0079
  ,{   6,   6,  1, acGUI_Font14_007A } // Code 007A
  ,{   5,   5,  1, acGUI_Font14_007B } // Code 007B
  ,{   3,   3,  1, acGUI_Font14_007C } // Code 007C
  ,{   5,   5,  1, acGUI_Font14_007D } // Code 007D
  ,{   7,   7,  1, acGUI_Font14_007E } // Code 007E
};

GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font14_Prop1 = {
   0x0020 // first character
  ,0x007E // last character 
  ,&GUI_Font14_CharInfo[  0] // address of first character
  ,(GUI_CONST_STORAGE GUI_FONT_PROP *)0 // pointer to next GUI_FONT_PROP
};

GUI_CONST_STORAGE GUI_FONT _FontSmall = {
   GUI_FONTTYPE_PROP // type of font   
  ,14 // height of font 
  ,14 // space of font y
  ,1 // magnification x
  ,1 // magnification y
  ,{&GUI_Font14_Prop1}
  ,11 // Baseline
  ,7 // Height of lowercase characters
  ,9 // Height of capital characters
};


/*********************************************************************
*
*       Data for wheels
*/
static char * _apYear[] = {
  "1990", "1991", "1992", "1993", "1994", "1995", "1996", "1997", "1998", "1999", "2000", "2001", "2002", "2003", "2004", "2005", "2006", "2007", "2008", "2009", "2010", "2011", "2012", "2013", "2014", "2015", "2016", "2017", "2018", "2019", "2020",
};

static char * _apMonth[] = {
  "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December",
};

static char * _apDay[] = {
  "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31",
};

static WHEEL _aWheel[3];

static int _aSelection[2][3] = {
  { 1, 2,  3},
  {16, 8, 13},
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _OwnerDraw
*/
static int _OwnerDraw(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  WM_HWIN   hWin;
  WHEEL   * pWheel;
  int       xPos;
  int       yPos;
  int       xSizeWin;
  int       ySizeWin;
  int       xSizeDev;

  hWin = pDrawItemInfo->hWin;
  //
  // Process messages
  //
  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_GET_XSIZE:
    //
    // Return x-size of item
    //
    return LISTWHEEL_OwnerDraw(pDrawItemInfo);
  case WIDGET_ITEM_GET_YSIZE:
    //
    // Return y-size of item
    //
    return LISTWHEEL_OwnerDraw(pDrawItemInfo);
  case WIDGET_ITEM_DRAW:
    //
    // Draw item
    //
    return LISTWHEEL_OwnerDraw(pDrawItemInfo);
  case WIDGET_ITEM_DRAW_BACKGROUND:
    xSizeWin = WM_GetWindowSizeX(hWin);
    ySizeWin = WM_GetWindowSizeY(hWin);
    //
    // Draw background
    //
    GUI_SetColor(GUI_MAKE_COLOR(0x00FFFFFF));
    GUI_FillRect(4, 0, xSizeWin - 5, ySizeWin - 1);
    break;
  case WIDGET_ITEM_DRAW_OVERLAY:
    LISTWHEEL_GetUserData(hWin, &pWheel, sizeof(pWheel));
    xPos     = WM_GetWindowOrgX(hWin);
    yPos     = WM_GetWindowOrgY(hWin);
    xSizeWin = WM_GetWindowSizeX(hWin);
    xSizeDev = GUI_MEMDEV_GetXSize(pWheel->hMemRBorder);
    //
    // Draw border
    //
    GUI_MEMDEV_WriteAt(pWheel->hMemLBorder, xPos, yPos);
    GUI_MEMDEV_WriteAt(pWheel->hMemRBorder, xPos + xSizeWin - xSizeDev, yPos);
    //
    // Draw overlay
    //
    GUI_MEMDEV_WriteAt(pWheel->hMemOverlay, xPos, yPos);
    break;
  }
  return 0;
}

/*********************************************************************
*
*       _RoundUpCorners
*/
static void _RoundUpCorners(GUI_MEMDEV_Handle hMem, int Side, int r, int vMask) {
  GUI_MEMDEV_Handle hMemPrev;
  I32 rr;
  int i;
  int y;
  int x;
  int xs;
  int xe;
  int xSize;
  int ySize;
  int x1;
  int y1;

  xSize    = GUI_MEMDEV_GetXSize(hMem);
  ySize    = GUI_MEMDEV_GetYSize(hMem);
  hMemPrev = GUI_MEMDEV_Select(hMem);
  x1       = xSize - 1;
  y1       = ySize - 1;
  rr       = (I32)r * r;
  y        = r;
  GUI_SetColor(GUI_MAKE_COLOR(0xFF000000));
  for (i = 0; i <= r; i++, y--) {
    x = (int)sqrt((float)(rr - (I32)y * y));
    if (Side & LEFT) {
      xs = 0;
      xe = r - x - 1;
      if (x != r) {
        if (vMask & TOP) {
          GUI_DrawHLine(i,      xs, xe);
        }
        if (vMask & BOTTOM) {
          GUI_DrawHLine(y1 - i, xs, xe);
        }
      }
    }
    if (Side & RIGHT) {
      xs = x1 - r + x + 1;
      xe = x1;
      if (x != r) {
        if (vMask & TOP) {
          GUI_DrawHLine(i,      xs, xe);
        }
        if (vMask & BOTTOM) {
          GUI_DrawHLine(y1 - i, xs, xe);
        }
      }
    }
  }
  GUI_MEMDEV_Select(hMemPrev);
}

/*********************************************************************
*
*       _CreateDecoration
*/
static void _CreateDecoration(int xSize, int ySize, int LineHeight, WHEEL * pWheel) {
  GUI_MEMDEV_Handle hMemPrev;
  GUI_MEMDEV_Handle hMemRBorder;
  GUI_MEMDEV_Handle hMemLBorder;
  GUI_MEMDEV_Handle hMemOverlay;

  //
  // Create left border
  //
  hMemLBorder = GUI_MEMDEV_CreateFixed(0, 0, 4, ySize, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_32, COLOR_CONV);
  hMemPrev = GUI_MEMDEV_Select(hMemLBorder);
  GUI_SetColor(GUI_BLACK);
  GUI_DrawVLine(0, 0, ySize - 1);
  GUI_SetColor(GUI_MAKE_COLOR(0x00CCCCCC));
  GUI_FillRect(1, 0, 3, ySize - 1);
  //
  // Create right border
  //
  hMemRBorder = GUI_MEMDEV_CreateFixed(0, 0, 4, ySize, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_32, COLOR_CONV);
  GUI_MEMDEV_Select(hMemRBorder);
  GUI_SetColor(GUI_BLACK);
  GUI_DrawVLine(3, 0, ySize - 1);
  GUI_SetColor(GUI_LIGHTGRAY);
  GUI_FillRect(0, 0, 2, ySize - 1);
  //
  // Create overlay device
  //
  hMemOverlay = GUI_MEMDEV_CreateFixed(0, 0, xSize, ySize, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_32, COLOR_CONV);
  GUI_MEMDEV_Select(hMemOverlay);
  //
  // Gray gradients at top
  //
  GUI_DrawGradientV(0,                0,                   xSize - 1, (ySize * 2) / 10 - 1,               TRANS0,     TRANS1);
  GUI_DrawGradientV(0, (ySize * 2) / 10,                   xSize - 1, (ySize / 2) - (LineHeight / 2) - 1, TRANS1,     TRANS2);
  //
  // Gray gradients at bottom
  //
  GUI_DrawGradientV(0, (ySize / 2) + (LineHeight / 2),     xSize - 1, (ySize / 2) + (LineHeight / 2) + 2, GUI_MAKE_COLOR(0x88000000), TRANS2);
  GUI_DrawGradientV(0, (ySize / 2) + (LineHeight / 2) + 3, xSize - 1, ySize - (ySize * 2) / 10 - 1,       TRANS2,     TRANS1);
  GUI_DrawGradientV(0, ySize - (ySize * 2) / 10,           xSize - 1, ySize - 1,                          TRANS1,     TRANS0);
  GUI_DrawGradientV(0, ySize - 1,                          xSize - 1, ySize - 1,                          GUI_MAKE_COLOR(0x33000000), GUI_MAKE_COLOR(0x33000000));
  //
  // Translucent glass effect in the middle
  //
  GUI_SetColor(GUI_MAKE_COLOR(0x80000000));
  GUI_DrawHLine((ySize / 2) - (LineHeight / 2),     0, xSize - 1);
  GUI_SetColor(GUI_MAKE_COLOR(0x44000000));
  GUI_DrawHLine((ySize / 2) + (LineHeight / 2) - 1, 0, xSize - 1);
  GUI_DrawGradientV(1, (ySize / 2) - (LineHeight / 2) + 1, xSize - 2, (ySize / 2) - 1,                    GUI_MAKE_COLOR(0x88FFFFFF), GUI_MAKE_COLOR(0x55AAAAAA));
  GUI_DrawGradientV(1, (ySize / 2),                        xSize - 2, (ySize / 2) + (LineHeight / 2) - 2, GUI_MAKE_COLOR(0xBB000000), GUI_MAKE_COLOR(0xBB000000));
  GUI_MEMDEV_Select(hMemPrev);
  //
  // Store result
  //
  pWheel->hMemLBorder = hMemLBorder;
  pWheel->hMemRBorder = hMemRBorder;
  pWheel->hMemOverlay = hMemOverlay;
}

/*********************************************************************
*
*       _CreateListWheel
*/
static int _CreateListWheel(int x, int y, int xSize, int ySize, int Id, char ** apText, int NumItems, int TextAlign, WM_HWIN hParent, WHEEL * pWheel) {
  const GUI_FONT GUI_UNI_PTR * pFont;
  WM_HWIN                      hWin;
  int                          i;
  int                          LineHeight;

  //
  // Create LISTWHEEL object
  //
  pFont         = &_FontBig;
  LineHeight    = 30;
  pWheel->pFont = pFont;
  hWin          = LISTWHEEL_CreateUser(x, y, xSize, ySize, hParent, WM_CF_SHOW | WM_CF_HASTRANS, 0, Id, NULL, sizeof(void *));
  LISTWHEEL_SetFont(hWin, &_FontBig);
  LISTWHEEL_SetTextAlign(hWin, TextAlign);
  LISTWHEEL_SetSnapPosition(hWin, (ySize - LineHeight) / 2);
  LISTWHEEL_SetOwnerDraw(hWin, _OwnerDraw);
  LISTWHEEL_SetUserData(hWin, &pWheel, sizeof(pWheel));
  LISTWHEEL_SetLineHeight(hWin, LineHeight);
  LISTWHEEL_SetTextColor(hWin, LISTWHEEL_CI_SEL, LIGHTBLUE);
  for (i = 0; i < NumItems; i++) {
    LISTWHEEL_AddString(hWin, *(apText + i));
  }
  if (TextAlign & GUI_TA_RIGHT) {
    LISTWHEEL_SetRBorder(hWin, 10);
  }
  //
  // Create overlay devices
  //
  _CreateDecoration(xSize, ySize, LineHeight, pWheel);
  //
  // Fill WHEEL structure
  //
  pWheel->hWin = hWin;
  return 0;
}

/*********************************************************************
*
*       _cbBkWheel
*/
static void _cbBkWheel(WM_MESSAGE * pMsg) {
  WM_HWIN hParent;
  int     xSize;
  int     ySize;

  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    hParent    = WM_GetParent(pMsg->hWin);
    pMsg->hWin = hParent;
    WM_SendMessage(hParent, pMsg);
    break;
  case WM_PAINT:
    xSize = WM_GetWindowSizeX(pMsg->hWin);
    ySize = WM_GetWindowSizeY(pMsg->hWin);
    GUI_DrawGradientV(0, 0, xSize - 1, ySize - 1, GUI_MAKE_COLOR(0xb1b1b1), GUI_MAKE_COLOR(0x0d0d0d));
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _CreateAreaDevices
*/
static void _CreateAreaDevices(int xPos, int yPos, int xSize, int ySize, int r, int Location, GUI_MEMDEV_Handle * phMem) {
  GUI_MEMDEV_Handle hMemPrev;
  int               i;

  *(phMem + 0) = GUI_MEMDEV_CreateFixed(xPos, yPos, xSize, ySize, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_32, COLOR_CONV);
  *(phMem + 1) = GUI_MEMDEV_CreateFixed(xPos, yPos, xSize, ySize, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_32, COLOR_CONV);
  for (i = 0; i < 2; i++) {
    hMemPrev = GUI_MEMDEV_Select(*(phMem + i));
    if (i) {
      GUI_DrawGradientV(0, 0, xSize - 1, ySize - 1, GUI_MAKE_COLOR(0xFFBB55), LIGHTBLUE);
    } else {
      GUI_SetBkColor(GUI_WHITE);
      GUI_Clear();
    }
    GUI_SetColor(GUI_GRAY);
    if (Location == (TOP | BOTTOM)) {
      GUI_DrawRoundedRect(0, 0, xSize - 1, ySize - 1, r);
      _RoundUpCorners(*(phMem + i), LEFT | RIGHT,  r, TOP | BOTTOM);
    } else {
      if (Location & TOP) {
        GUI_DrawRoundedRect(0, 0, xSize - 1, ySize + r, r);
        GUI_DrawHLine(yPos + ySize - 1, xPos, xPos + xSize - 1);
        _RoundUpCorners(*(phMem + i), LEFT | RIGHT,  r, TOP);
      }
      if (Location & BOTTOM) {
        GUI_DrawRoundedRect(0, -r, xSize - 1, ySize - 1, r);
        _RoundUpCorners(*(phMem + i), LEFT | RIGHT,  r, BOTTOM);
      }
    }
    GUI_MEMDEV_Select(hMemPrev);
  }
}

/*********************************************************************
*
*       _cbBkWin
*/
static void _cbBkWin(WM_MESSAGE * pMsg) {
  static GUI_MEMDEV_Handle          ahMemStart[2][2];
  static int                        Selection;
  static int                        Mode = 1;
  const WM_PID_STATE_CHANGED_INFO * pState;
  const GUI_COLOR                   aTextColor[] = {GUI_BLACK, GUI_WHITE};
  int                               NCode;
  int                               Id;
  int                               i;
  int                               j;
  int                               Index;
  int                               x;
  int                               y;
  int                               yPos;
  const char * apText[] = {
    "Start:",
    "End:",
  };
  
  switch (pMsg->MsgId) {
  case GET_MODE:
    //
    // Return current state
    //
    pMsg->Data.v = Mode;
    return;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch (NCode) {
    case WM_NOTIFICATION_RELEASED:
      //
      // Manage auto mode
      //
      switch (Id) {
      case GUI_ID_BUTTON0:
        Mode ^= 1;
        if (Mode) {
          BUTTON_SetText(pMsg->hWinSrc, "Cancel");
        } else {
          BUTTON_SetText(pMsg->hWinSrc, "Auto");
        }
        break;
      }
      break;
    case WM_NOTIFICATION_SEL_CHANGED:
      //
      // React on LISTWHEEL notifications
      //
      switch (Id) {
      case GUI_ID_LISTWHEEL0:
      case GUI_ID_LISTWHEEL1:
      case GUI_ID_LISTWHEEL2:
        Index = Id - GUI_ID_LISTWHEEL0;
        _aSelection[Selection][Index] = LISTWHEEL_GetPos(_aWheel[Index].hWin);
        WM_InvalidateWindow(pMsg->hWin);
        break;
      }
    }
    break;
  case WM_PID_STATE_CHANGED:
    //
    // React on pressing data areas
    //
    pState = (const WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
    if ((pState->StatePrev == 0) && (pState->State == 1)) {
      x = pState->x;
      y = pState->y;
      if ((x >= 10) && (x <= 230)) {
        for (j = 0; j < 2; j++) {
          if ((y >= (75 + j * 40)) && (y < 75 + (j + 1) * 40)) {
            if (Selection != j) {
              Selection = j;
              for (i = 0; i < 3; i++) {
                LISTWHEEL_MoveToPos(_aWheel[i].hWin, _aSelection[Selection][i]);
              }
              WM_InvalidateWindow(pMsg->hWin);
            }
          }
        }
      }
    }
    break;
  case WM_PAINT:
    //
    // Create memory devices (if required)
    //
    if (ahMemStart[0][0] == 0) {
      _CreateAreaDevices(0, 0, 220, 35, 8, TOP,    &ahMemStart[0][0]);
      _CreateAreaDevices(0, 0, 220, 35, 8, BOTTOM, &ahMemStart[1][0]);
    }
    //
    // Fill background
    //
    GUI_DrawGradientV(0,   0, 239,  23, GUI_MAKE_COLOR(0xCCCCCC), GUI_MAKE_COLOR(0xCCCCCC));
    GUI_DrawGradientV(0,  24, 239,  24, GUI_MAKE_COLOR(0x666666), GUI_MAKE_COLOR(0x666666));
    GUI_DrawGradientV(0,  25, 239,  25, GUI_MAKE_COLOR(0xDDDDDD), GUI_MAKE_COLOR(0xDDDDDD));
    GUI_DrawGradientV(0,  26, 239,  68, GUI_MAKE_COLOR(0xCCCCCC), GUI_MAKE_COLOR(0xBBAA88));
    GUI_DrawGradientV(0,  69, 239,  69, GUI_MAKE_COLOR(0x666666), GUI_MAKE_COLOR(0x666666));
    GUI_DrawGradientV(0,  70, 239, 158, GUI_MAKE_COLOR(0xCCCCCC), GUI_MAKE_COLOR(0xCCCCCC));
    GUI_DrawGradientV(0, 159, 239, 159, GUI_MAKE_COLOR(0x666666), GUI_MAKE_COLOR(0x666666));
    GUI_DrawGradientV(0, 160, 239, 160, GUI_MAKE_COLOR(0xDDDDDD), GUI_MAKE_COLOR(0xDDDDDD));
    GUI_DrawGradientV(0, 161, 239, 319, GUI_MAKE_COLOR(0xBBBBBB), GUI_MAKE_COLOR(0x000000));
    //
    // Draw logo
    //
    GUI_DrawBitmap(&bmLogoSegger_36x18, 10, 3);
    //
    // Draw sample text with 3D effect
    //
    GUI_SetFont(&_FontBig);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetColor(GUI_WHITE);
    GUI_DispStringHCenterAt("Tryout LISTWHEEL", 143, 4);
    GUI_SetColor(GUI_BLACK);
    GUI_DispStringHCenterAt("Tryout LISTWHEEL", 143, 3);
    //
    // Draw "Start & End" with 3D effect
    //
    GUI_SetFont(&_FontBig);
    GUI_SetColor(GUI_BLACK);
    GUI_DispStringHCenterAt("Start & End", 120, 37);
    GUI_SetColor(GUI_WHITE);
    GUI_DispStringHCenterAt("Start & End", 120, 38);
    GUI_SetFont(&_FontBig);
    GUI_SetColor(GUI_BLACK);
    for (i = 0; i < 2; i++) {
      yPos = 80 + 35 * i;
      Index = (Selection == i) ? 1 : 0;
      GUI_MEMDEV_WriteAt(ahMemStart[i][Index], 10, yPos);
      GUI_SetColor(aTextColor[Index]);
      yPos += 8;
      GUI_DispStringAt(apText[i], 15, yPos);
      GUI_GotoXY(70, yPos);
      GUI_DispDecMin(_aSelection[i][0] + 1);
      GUI_DispChar('.');
      GUI_DispStringHCenterAt(_apMonth[_aSelection[i][1]],  137, yPos);
      GUI_DispStringAt(_apYear [_aSelection[i][2]], 185, yPos);
    }
    return;
  }
  WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       _CreateButtonDevices
*/
static void _CreateButtonDevices(int xPos, int yPos, int xSize, int ySize, int r, GUI_MEMDEV_Handle * phMem) {
  GUI_MEMDEV_Handle hMemPrev;
  int               i;

  *(phMem + 0) = GUI_MEMDEV_CreateFixed(xPos, yPos, xSize, ySize, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_32, COLOR_CONV);
  *(phMem + 1) = GUI_MEMDEV_CreateFixed(xPos, yPos, xSize, ySize, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_32, COLOR_CONV);
  for (i = 0; i < 2; i++) {
    hMemPrev = GUI_MEMDEV_Select(*(phMem + i));
    if (i) {
      GUI_DrawGradientV(0, 0, xSize - 1, ySize - 1, GUI_MAKE_COLOR(0xFFBB55), LIGHTBLUE);
    } else {
      GUI_DrawGradientV(0, 0, xSize - 1, ySize - 1, LIGHTBLUE, GUI_MAKE_COLOR(0xFFBB55));
    }
    GUI_SetColor(GUI_LIGHTGRAY);
    GUI_DrawRoundedRect(0, 0, xSize - 1, ySize - 1, r);
    GUI_SetColor(GUI_GRAY);
    GUI_DrawRoundedRect(0, 0, xSize - 1, ySize - 2, r);
    _RoundUpCorners(*(phMem + i), LEFT | RIGHT,  r, TOP | BOTTOM);
    GUI_MEMDEV_Select(hMemPrev);
  }
}

/*********************************************************************
*
*       _cbButton
*/
static void _cbButton(WM_MESSAGE * pMsg) {
  static GUI_MEMDEV_Handle ahMem[2];
  GUI_RECT                 Rect;
  WM_HWIN                  hWin;
  char                     acText[20];
  int                      xSize;
  int                      ySize;
  int                      Index;
  int                      xPos;
  int                      yPos;
  int                      Len;

  hWin = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    BUTTON_GetText(hWin, acText, sizeof(acText));
    xPos  = WM_GetWindowOrgX(hWin);
    yPos  = WM_GetWindowOrgY(hWin);
    xSize = WM_GetWindowSizeX(hWin);
    ySize = WM_GetWindowSizeY(hWin);
    if (ahMem[0] == 0) {
      _CreateButtonDevices(xPos, yPos, xSize, ySize, 5, ahMem);
      _RoundUpCorners(ahMem[0], LEFT | RIGHT, 5, TOP | BOTTOM);
      _RoundUpCorners(ahMem[1], LEFT | RIGHT, 5, TOP | BOTTOM);
    }
    Index = BUTTON_IsPressed(hWin);
    GUI_MEMDEV_WriteAt(ahMem[Index], xPos, yPos);
    Len = GUI__strlen(acText);
    GUI_SetTextMode(GUI_TM_TRANS);
    Rect.x0 = 0;
    Rect.y0 = Index - 1;
    Rect.x1 = xSize - 1;
    Rect.y1 = ySize - 1 + Index - 1;
    GUI_SetFont(&_FontSmall);
    GUI_SetColor(GUI_BLACK);
    GUI_DispStringInRectMax(acText, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER, Len);
    Rect.y0++;
    Rect.y1++;
    GUI_SetColor(GUI_WHITE);
    GUI_DispStringInRectMax(acText, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER, Len);
    break;
  default:
    BUTTON_Callback(pMsg);
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  GUI_PID_STATE PID_State = {0};
  WM_MESSAGE    Msg = {0};
  WM_HWIN       hBkWheel;
  WM_HWIN       hButton0;
  WM_HWIN       hButton1;
  int           i;
  int           TimeNextEvent;
  int           TimeCurrent;
  int           Animation;
  int           Velocity;
  int           ayPos[] = { 80, 120 };

  TimeNextEvent = 0;
  Animation     = 0;
 
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  WM_SetCallback(WM_HBKWIN, _cbBkWin);
  //
  // Create buttons
  //
  hButton0 = BUTTON_CreateEx(10, 35, 50, 25, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_BUTTON0);
  BUTTON_SetText(hButton0, "Cancel");
  WM_SetCallback(hButton0, _cbButton);
  WM_DisableMemdev(hButton0);
  WM_SetHasTrans(hButton0);

  hButton1 = BUTTON_CreateEx(180, 35, 50, 25, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_BUTTON1);
  BUTTON_SetText(hButton1, "Save");
  WM_SetCallback(hButton1, _cbButton);
  WM_DisableMemdev(hButton1);
  WM_SetHasTrans(hButton1);
  //
  // Create a non transparent background window for the LISTWHEELS
  //
  hBkWheel = WM_CreateWindowAsChild(15, 170, 210, 140, WM_HBKWIN, WM_CF_SHOW, _cbBkWheel, 0);
  //
  // Create the LISTWHEELS
  //
  _CreateListWheel(  0, 0,  40, 140, GUI_ID_LISTWHEEL0, _apDay,   GUI_COUNTOF(_apDay),   GUI_TA_VCENTER | GUI_TA_HCENTER, hBkWheel, &_aWheel[0]);
  _CreateListWheel( 40, 0, 110, 140, GUI_ID_LISTWHEEL1, _apMonth, GUI_COUNTOF(_apMonth), GUI_TA_VCENTER | GUI_TA_RIGHT,   hBkWheel, &_aWheel[1]);
  _CreateListWheel(150, 0,  60, 140, GUI_ID_LISTWHEEL2, _apYear,  GUI_COUNTOF(_apYear),  GUI_TA_VCENTER | GUI_TA_HCENTER, hBkWheel, &_aWheel[2]);
  for (i = 0; i < 3; i++) {
    LISTWHEEL_MoveToPos(_aWheel[i].hWin, _aSelection[0][i]);
  }
  //
  // Round the corners of the memory devices
  //
  _RoundUpCorners(_aWheel[0].hMemOverlay, LEFT,  4, TOP | BOTTOM);
  _RoundUpCorners(_aWheel[0].hMemLBorder, LEFT,  4, TOP | BOTTOM);
  _RoundUpCorners(_aWheel[2].hMemOverlay, RIGHT, 4, TOP | BOTTOM);
  _RoundUpCorners(_aWheel[2].hMemRBorder, RIGHT, 4, TOP | BOTTOM);
  //
  // Loop
  //
  Msg.MsgId = GET_MODE;
  Msg.hWin  = hButton0;
  while (1) {
    GUI_Delay(100);
    //
    // Animation
    //
    WM_SendMessage(WM_HBKWIN, &Msg);
    if (Msg.Data.v) {
      TimeCurrent = GUI_GetTime();
      if (TimeNextEvent == 0) {
        Animation     = 4;
        TimeNextEvent = TimeCurrent + 3000;
      }
      if (TimeCurrent >= TimeNextEvent) {
        switch (Animation) {
        case 0:
          PID_State.x = 160;
          PID_State.y = ayPos[0];
          PID_State.Pressed = 1;
          GUI_PID_StoreState(&PID_State);
          GUI_Delay(100);
          PID_State.Pressed = 0;
          GUI_PID_StoreState(&PID_State);
          TimeNextEvent = TimeCurrent + 3000;
          break;
        case 1:
        case 2:
        case 3:
          Velocity = (rand() % 200) - 100;
          LISTWHEEL_SetVelocity(_aWheel[Animation - 1].hWin, Velocity);
          TimeNextEvent = TimeCurrent + ((Animation == 3) ? 2000 : 500);
          break;
        case 4:
          PID_State.x = 160;
          PID_State.y = ayPos[1];
          PID_State.Pressed = 1;
          GUI_PID_StoreState(&PID_State);
          GUI_Delay(100);
          PID_State.Pressed = 0;
          GUI_PID_StoreState(&PID_State);
          TimeNextEvent = TimeCurrent + 3000;
          break;
        case 5:
        case 6:
        case 7:
          Velocity = (rand() % 200) - 100;
          LISTWHEEL_SetVelocity(_aWheel[Animation - 5].hWin, Velocity);
          TimeNextEvent = TimeCurrent + ((Animation == 7) ? 2000 : 500);
          break;
        }
        Animation = (Animation < 7) ? Animation + 1 : 0;
      }
    }
  }
}

/*************************** End of file ****************************/
