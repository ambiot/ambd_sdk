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
File        : MEMDEV_UseDataPointer.c
Purpose     : Shows the use of GUI_MEMDEV_GetDataPtr()
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "DIALOG.h"

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 50)

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbWin
*
* Function description
*   Callback routine of window which draws the content of the memory device
*/
static void _cbWin(WM_MESSAGE * pMsg) {
  GUI_MEMDEV_Handle hMem;
  WM_HWIN           hWin;
  int               xPos;
  int               yPos;
  int               xSize;
  int               ySize;

  hWin = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    //
    // Get window position
    //
    xPos  = WM_GetWindowOrgX(hWin);
    yPos  = WM_GetWindowOrgY(hWin);
    xSize = WM_GetWindowSizeX(hWin);
    ySize = WM_GetWindowSizeY(hWin);
    //
    // Draw memory device
    //
    WINDOW_GetUserData(hWin, &hMem, sizeof(hMem));
    GUI_MEMDEV_WriteAt(hMem, xPos, yPos);
    //
    // Draw surrounding frame
    //
    GUI_DrawRect(0, 0, xSize - 1, ySize - 1);
    break;
  }
}

/*********************************************************************
*
*       _cbBk
*
* Function description
*   Callback routine of desktop window
*/
static void _cbBk(WM_MESSAGE * pMsg) {
  int xSize;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    xSize = LCD_GetXSize();
    GUI_SetBkColor(GUI_DARKBLUE);
    GUI_Clear();
    GUI_SetFont(GUI_FONT_20_ASCII);
    GUI_DispStringHCenterAt("Sample shows usage of", xSize / 2, 5);
    GUI_DispStringHCenterAt("GUI_MEMDEV_GetDataPtr()", xSize / 2, 25);
    break;
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
  WM_HWIN hWin;
  GUI_MEMDEV_Handle   hMemWin;  // Memory device to be used in window
  GUI_MEMDEV_Handle   hMemDraw; // Memory device for drawing operation
  GUI_RECT            Rect;
  U32               * pDataWin;
  U32               * pDataDraw;
  int                 i;
  int                 yPos;
  int                 Cnt;
  int                 xSizeWindow;
  int                 ySizeWindow;
  int                 xPosWindow;
  int                 yPosWindow;
  int                 xSizeDisplay;
  int                 ySizeDisplay;

  xSizeDisplay = 480;
  ySizeDisplay = 272;
  xSizeWindow = 100;
  ySizeWindow = 100;
  xPosWindow = (xSizeDisplay - xSizeWindow) / 2;
  yPosWindow = (ySizeDisplay - ySizeWindow) / 2;
  Cnt = 0;
  Rect.y0 = 0;
  Rect.y1 = ySizeWindow - 1;

  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  WM_SetCallback(WM_HBKWIN, _cbBk);
  //
  // Create window
  //
  hWin = WINDOW_CreateUser(xPosWindow, yPosWindow, xSizeWindow, ySizeWindow, 0, WM_CF_SHOW, 0, 0, _cbWin, sizeof(hMemWin));
  //
  // Create a memory device for the window
  //
  hMemWin = GUI_MEMDEV_CreateFixed(0, 0, 100, 100, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_32, GUICC_8888);
  //
  // Attach memory device to window data
  //
  WINDOW_SetUserData(hWin, &hMemWin, sizeof(hMemWin));
  //
  // Create small memory device for drawing one line of gradient data
  // representing the real data to be used
  //
  hMemDraw = GUI_MEMDEV_CreateFixed(xPosWindow, yPosWindow, 1, ySizeWindow, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_32, GUICC_8888);
  //
  // Initialize random value
  //
  yPos = rand() % ySizeWindow;
  while (1) {
    //
    // Create some data to be added to the windows memory device
    //
    GUI_MEMDEV_Select(hMemDraw);
    GUI_DrawGradientV(xPosWindow, yPosWindow, xPosWindow, yPosWindow + yPos, GUI_RED, GUI_YELLOW);
    GUI_MEMDEV_Select(0);
    //
    // Get data pointers immediately before accessing data
    //
    pDataWin  = (U32 *)GUI_MEMDEV_GetDataPtr(hMemWin);
    pDataDraw = (U32 *)GUI_MEMDEV_GetDataPtr(hMemDraw);
    //
    // Initially clear memory device
    //
    if (Cnt == 0) {
      memset(pDataWin, 0, sizeof(U32) * xSizeWindow * ySizeWindow);
      WM_InvalidateWindow(hWin);
    }
    //
    // Copy data from drawing device into windows memory device
    //
    for (i = 0, pDataWin += xSizeWindow * (ySizeWindow - 1) + Cnt; i <= yPos; i++, pDataWin -= xSizeWindow, pDataDraw++) {
      *pDataWin = *pDataDraw;
    }
    //
    // Optimized invalidating, only the new line will be drawn
    //
    Rect.x0 = Rect.x1 = Cnt;
    WM_InvalidateRect(hWin, &Rect);
    //
    // Increment counter
    //
    Cnt++;
    Cnt = (Cnt >= 100) ? 0 : Cnt;
    //
    // Modify random value
    //
    yPos += (rand() % 5) - 2;
    yPos = (yPos < 0) ? 0 : (yPos >= ySizeWindow) ? ySizeWindow - 1 : yPos;
    //
    // Wait a while and redraw window
    //
    GUI_Delay(50);
  }
}

/*************************** End of file ****************************/
