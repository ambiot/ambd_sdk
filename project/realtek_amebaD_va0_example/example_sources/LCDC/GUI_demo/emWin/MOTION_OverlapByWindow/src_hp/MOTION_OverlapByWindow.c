/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2018  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.48 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only  be used  in accordance  with  a license  and should  not be  re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : MOTION_MovingWindow.c
Purpose     : Shows how to use simple motion support
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

/*********************************************************************
*
*       Includes
*
**********************************************************************
*/
#include "WM.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
#define OVERLAP 140
#define NUM_PAGES 4

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbWin
*/
static void _cbWin(WM_MESSAGE * pMsg) {
  GUI_RECT Rect;
  WM_MOTION_INFO * pInfo;
  static int xPos;
  int i, xDist, xSize, xMin, xMax, Overlap;

  switch (pMsg->MsgId) {
  case WM_MOTION:
    pInfo = (WM_MOTION_INFO *)pMsg->Data.p;
    switch (pInfo->Cmd) {
    case WM_MOTION_INIT:
      WM_GetClientRectEx(pMsg->hWin, &Rect);
	  //
	  // Enable motion support
	  //
      pInfo->Flags = WM_CF_MOTION_X | WM_MOTION_MANAGE_BY_WINDOW;
      pInfo->SnapX = Rect.x1 + 1;
	  //
	  // Allow overlapping
	  //
      pInfo->Overlap = OVERLAP;
      break;
    case WM_MOTION_MOVE:
	  //
	  // Move 'content' of window
	  //
      xSize = LCD_GetXSize();
      xPos += pInfo->dx;
	  //
	  // Use 'IsDragging' for determining if PID is pressed
	  //
      if (pInfo->IsDragging) {
        pInfo->IsOutside = ((xPos < -((xSize * (NUM_PAGES - 1)))) || (xPos > 0)) ? 1 : 0;
        Overlap = pInfo->Overlap;
      } else {
        Overlap = pInfo->Overlap * pInfo->IsOutside;
      }
	  //
	  // Determine if dragging operation is 'outside'
	  //
      xMin = (int)(((xSize * (NUM_PAGES - 1)) + Overlap) * -1);
      xMax = Overlap;
      if (xPos < xMin) {
        xPos = xMin;
        pInfo->StopMotion = pInfo->IsDragging ^ 1;
      } else if (xPos > xMax) {
        xPos = xMax;
        pInfo->StopMotion = pInfo->IsDragging ^ 1;
      }
	  //
	  // Make sure window will be repainted
	  //
      WM_InvalidateWindow(pMsg->hWin);
      break;
    case WM_MOTION_GETPOS:
      pInfo->xPos = xPos;
      break;
    }
    break;
  case WM_PAINT:
    //
	// Draw 'content' of window
	//
    GUI_Clear();
    WM_GetClientRect(&Rect);
    xDist = Rect.x1 + 1;
    for (i = 0; i < NUM_PAGES; i++) {
      GUI_DrawRect(i * xDist + xPos, 0, (i + 1) * xDist + xPos - 1, Rect.y1);
      GUI_SetFont(GUI_FONT_32B_ASCII);
      GUI_DispStringAt("Page #", i * xDist + xPos + 40, Rect.y1 / 2 - 16);
      GUI_DispDecMin(i);
    }
    break;
  default:
    WM_DefaultProc(pMsg);
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
  int xSize, ySize;


  //
  // Limit desktop window to physical display size
  //
  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();
  WM_SetSize(WM_HBKWIN, xSize, ySize);
  //
  // Make sure background is black
  //
  WM_SetDesktopColor(GUI_BLACK);
  //
  // Enable motion support
  //
  WM_MOTION_Enable(1);
  //
  // Create window without motion support...
  //
  WM_CreateWindowAsChild(0, 0, xSize, ySize, WM_HBKWIN, WM_CF_SHOW, _cbWin, 0);
  //
  // ...and keep demo alive
  //
  while (1) {
    GUI_Delay(100);
  }
}

/*************************** End of file ****************************/
