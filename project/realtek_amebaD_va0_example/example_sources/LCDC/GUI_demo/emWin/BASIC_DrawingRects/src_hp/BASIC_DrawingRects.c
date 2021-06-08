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
File        : BASIC_DrawingRects.c
Purpose     : Filling screen with random rectangles
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include <stdlib.h>
#include "GUI.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

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
  const U32 aColor[] = {
    GUI_BLUE        ,    GUI_GREEN       ,    GUI_RED         ,    GUI_CYAN        ,    GUI_MAGENTA     ,    GUI_YELLOW      ,
    GUI_LIGHTBLUE   ,    GUI_LIGHTGREEN  ,    GUI_LIGHTRED    ,    GUI_LIGHTCYAN   ,    GUI_LIGHTMAGENTA,    GUI_LIGHTYELLOW ,
    GUI_DARKBLUE    ,    GUI_DARKGREEN   ,    GUI_DARKRED     ,    GUI_DARKCYAN    ,    GUI_DARKMAGENTA ,    GUI_DARKYELLOW  ,
  };
  int x0;
  int y0;
  int Index;
  int xSize;
  int ySize;
  int xSizeRect;
  int ySizeRect;

  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();
  while (1) {
    x0 = rand() % xSize;
    y0 = rand() % ySize;
    xSizeRect = rand() % (xSize - x0);
    ySizeRect = rand() % (ySize - y0);
    Index = (unsigned)rand() % GUI_COUNTOF(aColor);
    GUI_SetColor(aColor[Index]);
    GUI_FillRect(x0, y0, x0 + xSizeRect - 1, y0 + ySizeRect - 1);
  }
}

/*************************** End of file ****************************/
