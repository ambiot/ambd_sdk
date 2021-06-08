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
File        : AA_HiResAntialiasing.c
Purpose     : Demonstrates high resolution antialiasing
Requirements: WindowManager - ( )
              MemoryDevices - (x)
              AntiAliasing  - (x)
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include "GUI.h"

/*******************************************************************
*
*       Defines
*
********************************************************************
*/
#define countof(Obj) (sizeof(Obj)/sizeof(Obj[0]))

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 20)

/*******************************************************************
*
*       static variables
*
********************************************************************
*/

static const GUI_POINT _aPointer[] = {
  { 0,  3},
  {85,  1},
  {90,  0},
  {85, -1},
  { 0, -3}
};

static GUI_POINT _aPointerHiRes[countof(_aPointer)];

typedef struct {
  GUI_AUTODEV_INFO AutoInfo;
  GUI_POINT aPoints[countof(_aPointer)];
  int Factor;
} PARAM;

/*******************************************************************
*
*       Static functions
*
********************************************************************
*/
/*******************************************************************
*
*       _DrawHiRes
*
* Function description
*   This function draws the high resolution pointer
*/
static void _DrawHiRes(void * p) {
  PARAM * pParam = (PARAM *)p;
  if (pParam->AutoInfo.DrawFixed) {
    GUI_ClearRect(60, 60, 159, 159);
  }
  GUI_AA_FillPolygon(pParam->aPoints, 
                     countof(_aPointer), 
                     65  * pParam->Factor, 
                     155 * pParam->Factor);
}

/*******************************************************************
*
*       _Draw
*
* Function description
*   This function draws the non high resolution pointer
*/
static void _Draw(void * p) {
  PARAM * pParam = (PARAM *)p;
  if (pParam->AutoInfo.DrawFixed) {
    GUI_ClearRect(160, 60, 259, 159);
  }
  GUI_AA_FillPolygon(pParam->aPoints, countof(_aPointer), 165, 155);
}

/*******************************************************************
*
*       _ShowHiresAntialiasing
*
* Function description
*   This function creates the memory auto devices and handle the
*   rotation of the pointers
*/
static void _ShowHiresAntialiasing(void) {
  GUI_AUTODEV aAuto[2];
  PARAM       Param;
  unsigned         i;

  Param.Factor = 3;
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  GUI_SetTextAlign(GUI_TA_HCENTER);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringAt("AA_HiResAntialiasing - Sample", 160, 5);
  GUI_SetFont(&GUI_Font6x8);
  GUI_DispStringHCenterAt("Using\nhigh\nresolution\nmode", 110, 180);
  GUI_DispStringHCenterAt("Not using\nhigh\nresolution\nmode", 210, 180);
  //
  // Create GUI_AUTODEV objects
  //
  for (i = 0; i < countof(aAuto); i++) {
    GUI_MEMDEV_CreateAuto(&aAuto[i]);
  }
  //
  // Calculate pointer for high resolution
  //
  for (i = 0; i < countof(_aPointer); i++) {
    _aPointerHiRes[i].x = _aPointer[i].x * Param.Factor;
    _aPointerHiRes[i].y = _aPointer[i].y * Param.Factor;
  }
  GUI_AA_SetFactor(Param.Factor); /* Set antialiasing factor */
  while (1) {
    for (i = 0; i < 1800; i++) {
      float Angle = (i >= 900) ? 1800 - i : i;
      Angle *= 3.1415926f / 1800;
      //
      // Draw pointer with high resolution
      //
      GUI_AA_EnableHiRes();
      GUI_RotatePolygon(Param.aPoints, _aPointerHiRes, countof(_aPointer), Angle);
      GUI_MEMDEV_DrawAuto(&aAuto[0], &Param.AutoInfo, _DrawHiRes, &Param);
      //
      // Draw pointer without high resolution
      //
      GUI_AA_DisableHiRes();
      GUI_RotatePolygon(Param.aPoints, _aPointer, countof(_aPointer), Angle);
      GUI_MEMDEV_DrawAuto(&aAuto[1], &Param.AutoInfo, _Draw, &Param);
      GUI_Delay(2);
    }
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
  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  _ShowHiresAntialiasing();
}

/*************************** End of file ****************************/

