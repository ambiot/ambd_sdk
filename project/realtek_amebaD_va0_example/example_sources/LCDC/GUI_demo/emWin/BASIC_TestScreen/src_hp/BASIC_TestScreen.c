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
File        : BASIC_TestScreen.c
Purpose     : Draws a simple test screen
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include "GUI.h"

/*******************************************************************
*
*       Public Code
*
********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  GUI_RECT Rect = { 0, 0, 49, 49 };
  GUI_COLOR aColor[] = { GUI_RED, GUI_GREEN, GUI_BLUE };
  char * apColor[GUI_COUNTOF(aColor)] = { "Red", "Green", "Blue" };
  int i;

  GUI_SetTextMode(GUI_TM_TRANS);
  for (i = 0; i < GUI_COUNTOF(aColor); i++) {
    GUI_SetColor(aColor[i]);
    GUI_FillRectEx(&Rect);
    GUI_SetColor(GUI_WHITE);
    GUI_DispStringInRect(apColor[i], &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    GUI_MoveRect(&Rect, Rect.x1 - Rect.x0 + 1, Rect.y1 - Rect.y0 + 1);
  }
  GUI_MoveRect(&Rect, -(Rect.x1 - Rect.x0 + 1), -(Rect.y1 - Rect.y0 + 1));
  GUI_SetColor(GUI_WHITE);
  GUI_DrawLine(0, ((Rect.y1 - Rect.y0 + 1) << 1) - 1, ((Rect.x1 - Rect.x0 + 1) << 1) - 1, 0);
  GUI_DispStringAt("Test", 0, (Rect.y0 + Rect.y1) >> 1);
  GUI_DispStringAt("Test", (Rect.x0 + Rect.x1) >> 1, 0);
  GUI_InvertRect(10, 10, Rect.x1 - 10, Rect.y1 - 10);
  while (1) {
    GUI_Exec();
  }
}

/*************************** End of file ****************************/
