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
File        : BASIC_DrawSplines.c
Purpose     : Drawing colored splines
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include "GUI.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define TEMP_MULTIPLY   5

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static const int _axi[] = {
  0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240
};

static const int _ayi[3][13] = {
  { 8, 7, 6, 7, 8, 11, 14, 16, 18, 16, 13, 9, 7 },
  { 7, 7, 6, 6, 8, 11, 14, 15, 15, 14, 13, 8, 7 },
  { 7, 6, 5, 4, 5,  8,  9, 12, 14, 12, 11, 8, 6 }
};

static GUI_COLOR _aColor[] = {
  GUI_RED, GUI_GREEN, GUI_LIGHTBLUE
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawSplines
*/
static void _DrawSplines(void) {
  GUI_HMEM hSpline;
  U32 NumPoints;
  int aTemp[3][13];
  unsigned i, j;
  
  for (i = 0; i < GUI_COUNTOF(_ayi); i++) {
    for (j = 0; j < GUI_COUNTOF(_ayi[i]); j++) {
      aTemp[i][j] = _ayi[i][j] * TEMP_MULTIPLY * -1;
    }
    NumPoints = GUI_COUNTOF(_axi);
    hSpline = GUI_SPLINE_Create(_axi, aTemp[i], NumPoints);
    GUI_SetColor(_aColor[i]);
    GUI_SetDrawMode(GUI_DM_TRANS);
    GUI_SPLINE_DrawAA(hSpline, 20, 100, 0);
    GUI_SPLINE_DrawAA(hSpline, 20, 150, 3);
    GUI_SetDrawMode(GUI_DM_NORMAL);
    GUI_SPLINE_DrawAA(hSpline, 20, 200, 0);
    GUI_SPLINE_DrawAA(hSpline, 20, 250, 3);
    GUI_SPLINE_Delete(hSpline);
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
  _DrawSplines();
  while (1) {
    GUI_Delay(100);
  }
}

/*************************** End of file ****************************/
