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
File        : WM_Sample.c
Purpose     : Demonstrates the window manager
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include <string.h>
#include "GUI.h"
#include "WM.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define MSG_CHANGE_TEXT (WM_USER + 0)
#define SPEED           1250

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*******************************************************************
*
*       Static variables
*
********************************************************************
*/
//
// Text
//
static char _acInfoText[40];
//
// Colors
//
static GUI_COLOR _WindowColor1 = GUI_GREEN;
static GUI_COLOR _FrameColor1  = GUI_BLUE;
static GUI_COLOR _WindowColor2 = GUI_RED;
static GUI_COLOR _FrameColor2  = GUI_YELLOW;
static GUI_COLOR _ChildColor   = GUI_YELLOW;
static GUI_COLOR _ChildFrame   = GUI_BLACK;
//
// Callback
//
static WM_CALLBACK * _cbBkWindowOld;
//
// Handles
//
static WM_HWIN _hWindow1;
static WM_HWIN _hWindow2;
static WM_HWIN _hChild;

/*******************************************************************
*
*       Static code, helper functions
*
********************************************************************
*/
/*******************************************************************
*
*       _ChangeInfoText
*
* Function description
*   Sends a message to the background window and invalidate it, so
*   the callback of the background window display the new text.
*/
static void _ChangeInfoText(char * pStr) {
  WM_MESSAGE Message;

  Message.MsgId  = MSG_CHANGE_TEXT;
  Message.Data.p = pStr;
  WM_SendMessage(WM_HBKWIN, &Message);
  WM_InvalidateWindow(WM_HBKWIN);
}

/*******************************************************************
*
*       _DrawInfoText
*
* Function description
*   Drawes the info text directly on the display. This function is for
*   the moments when no callback is set.
*/
static void _DrawInfoText(char * pStr) {
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("WindowManager - Sample", 160, 5);
  GUI_SetFont(&GUI_Font8x16);
  GUI_DispStringAtCEOL(pStr, 5, 40);
}

/*******************************************************************
*
*       _LiftUp
*/
static void _LiftUp(int dy) {
  int i;
  int tm;

  for (i = 0; i < (dy/4); i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1, 0, -4);
    WM_MoveWindow(_hWindow2, 0, -4);
    while ((GUI_GetTime() - tm) < 20) {
      WM_Exec();
    }
  }
}

/*******************************************************************
*
*       _LiftDown
*/
static void _LiftDown(int dy) {
  int i;
  int tm;

  for (i = 0; i < (dy/4); i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1, 0, 4);
    WM_MoveWindow(_hWindow2, 0, 4);
    while ((GUI_GetTime() - tm) < 20) {
      WM_Exec();
    }
  }
}

/*******************************************************************
*
*       Static code, callbacks for windows
*
********************************************************************
*/
/*******************************************************************
*
*       _cbBkWindow
*/
static void _cbBkWindow(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
  case MSG_CHANGE_TEXT:
    strcpy(_acInfoText, (char const *)pMsg->Data.p);
  case WM_PAINT:
    GUI_SetBkColor(GUI_BLACK);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_DispStringHCenterAt("WindowManager - Sample", 160, 5);
    GUI_SetFont(&GUI_Font8x16);
    GUI_DispStringAt(_acInfoText, 5, 40);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _cbWindow1
*/
static void _cbWindow1(WM_MESSAGE * pMsg) {
  GUI_RECT Rect;
  int      x;
  int      y;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    WM_GetInsideRect(&Rect);
    GUI_SetBkColor(_WindowColor1);
    GUI_SetColor(_FrameColor1);
    GUI_ClearRectEx(&Rect);
    GUI_DrawRectEx(&Rect);
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    x = WM_GetWindowSizeX(pMsg->hWin);
    y = WM_GetWindowSizeY(pMsg->hWin);
    GUI_DispStringHCenterAt("Window 1", x / 2, (y / 2) - 12);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _cbWindow2
*/
static void _cbWindow2(WM_MESSAGE * pMsg) {
  GUI_RECT Rect;
  int      x;
  int      y;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    WM_GetInsideRect(&Rect);
    GUI_SetBkColor(_WindowColor2);
    GUI_SetColor(_FrameColor2);
    GUI_ClearRectEx(&Rect);
    GUI_DrawRectEx(&Rect);
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    x = WM_GetWindowSizeX(pMsg->hWin);
    y = WM_GetWindowSizeY(pMsg->hWin);
    GUI_DispStringHCenterAt("Window 2", x / 2, (y / 4) - 12);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _cbChild
*/
static void _cbChild(WM_MESSAGE * pMsg) {
  GUI_RECT Rect;
  int      x;
  int      y;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    WM_GetInsideRect(&Rect);
    GUI_SetBkColor(_ChildColor);
    GUI_SetColor(_ChildFrame);
    GUI_ClearRectEx(&Rect);
    GUI_DrawRectEx(&Rect);
    GUI_SetColor(GUI_RED);
    GUI_SetFont(&GUI_Font24_ASCII);
    x = WM_GetWindowSizeX(pMsg->hWin);
    y = WM_GetWindowSizeY(pMsg->hWin);
    GUI_DispStringHCenterAt("Child window", x / 2, (y / 2) - 12);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _cbDemoCallback1
*/
static void _cbDemoCallback1(WM_MESSAGE * pMsg) {
  int x;
  int y;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_GREEN);
    GUI_Clear();
    GUI_SetColor(GUI_RED);
    GUI_SetFont(&GUI_FontComic18B_1);
    x = WM_GetWindowSizeX(pMsg->hWin);
    y = WM_GetWindowSizeY(pMsg->hWin);
    GUI_DispStringHCenterAt("Window 1\nanother Callback", x / 2, (y / 2) - 18);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _cbDemoCallback2
*/
static void _cbDemoCallback2(WM_MESSAGE * pMsg) {
  int x;
  int y;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_MAGENTA);
    GUI_Clear();
    GUI_SetColor(GUI_YELLOW);
    GUI_SetFont(&GUI_FontComic18B_1);
    x = WM_GetWindowSizeX(pMsg->hWin);
    y = WM_GetWindowSizeY(pMsg->hWin);
    GUI_DispStringHCenterAt("Window 2\nanother Callback", x / 2, (y / 4) - 18);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       Static code, functions for demo
*
********************************************************************
*/
/*******************************************************************
*
*       _DemoSetDesktopColor
*
* Function description
*   Demonstrates the use of WM_SetDesktopColor
*/
static void _DemoSetDesktopColor(void) {
  GUI_SetBkColor(GUI_BLUE);
  GUI_Clear();
  _DrawInfoText("WM_SetDesktopColor()");
  GUI_Delay(SPEED*3/2);
  WM_SetDesktopColor(GUI_BLACK);
  GUI_Delay(SPEED/2);
  //
  // Set background color and invalidate desktop color.
  // This is needed for the later redrawing demo.
  //
  GUI_SetBkColor(GUI_BLACK);
  WM_SetDesktopColor(GUI_INVALID_COLOR);
}

/*******************************************************************
*
*       _DemoCreateWindow
*
* Function description
*   Demonstrates the use of WM_CreateWindow
*/
static void _DemoCreateWindow(void) {
  //
  // Set callback for background window
  //
  _cbBkWindowOld = WM_SetCallback(WM_HBKWIN, _cbBkWindow);
  //
  // Create windows
  //
  _ChangeInfoText("WM_CreateWindow()");
  GUI_Delay(SPEED);
  _hWindow1 = WM_CreateWindow( 50,  70, 165, 100, WM_CF_SHOW | WM_CF_MEMDEV, _cbWindow1, 0);
  GUI_Delay(SPEED/3);
  _hWindow2 = WM_CreateWindow(105, 125, 165, 100, WM_CF_SHOW | WM_CF_MEMDEV, _cbWindow2, 0);
  GUI_Delay(SPEED);
}

/*******************************************************************
*
*       _DemoCreateWindowAsChild
*
* Function description
*   Demonstrates the use of WM_CreateWindowAsChild
*/
static void _DemoCreateWindowAsChild(void) {
  //
  // Create windows
  //
  _ChangeInfoText("WM_CreateWindowAsChild()");
  GUI_Delay(SPEED);
  _hChild = WM_CreateWindowAsChild(10, 50, 145, 40, _hWindow2, WM_CF_SHOW | WM_CF_MEMDEV, _cbChild, 0);
  GUI_Delay(SPEED);
}

/*******************************************************************
*
*       _DemoInvalidateWindow
*
* Function description
*   Demonstrates the use of WM_InvalidateWindow
*/
static void _DemoInvalidateWindow(void) {
  _ChangeInfoText("WM_InvalidateWindow()");
  _WindowColor1 = GUI_BLUE;
  _FrameColor1  = GUI_GREEN;
  GUI_Delay(SPEED);
  WM_InvalidateWindow(_hWindow1);
  GUI_Delay(SPEED);
}

/*******************************************************************
*
*       _DemoBringToTop
*
* Function description
*   Demonstrates the use of WM_BringToTop
*/
static void _DemoBringToTop(void) {
  _ChangeInfoText("WM_BringToTop()");
  GUI_Delay(SPEED);
  WM_BringToTop(_hWindow1);    
  GUI_Delay(SPEED);
}

/*******************************************************************
*
*       _DemoMoveTo
*
* Function description
*   Demonstrates the use of WM_MoveTo
*/
static void _DemoMoveTo(void) {
  int i;
  int tm;
  int tDiff;

  _ChangeInfoText("WM_MoveTo()");
  GUI_Delay(SPEED);
  for (i = 1; i < 56; i++) {
    tm = GUI_GetTime();
    WM_MoveTo(_hWindow1,  50 + i,  70 + i);
    WM_MoveTo(_hWindow2, 105 - i, 125 - i);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 1; i < 56; i++) {
    tm = GUI_GetTime();
    WM_MoveTo(_hWindow1, 105 - i, 125 - i);
    WM_MoveTo(_hWindow2,  50 + i,  70 + i);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  GUI_Delay(SPEED);
}

/*******************************************************************
*
*       _DemoBringToBottom
*
* Function description
*   Demonstrates the use of WM_BringToBottom
*/
static void _DemoBringToBottom(void) {
  _ChangeInfoText("WM_BringToBottom()");
  GUI_Delay(SPEED);
  WM_BringToBottom(_hWindow1);
  GUI_Delay(SPEED);
}

/*******************************************************************
*
*       _DemoMoveWindow
*
* Function description
*   Demonstrates the use of WM_MoveWindow
*/
static void _DemoMoveWindow(void) {
  int i;
  int tm;
  int tDiff;

  _ChangeInfoText("WM_MoveWindow()");
  GUI_Delay(SPEED);
  for (i = 0; i < 55; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1,  1,  1);
    WM_MoveWindow(_hWindow2, -1, -1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 55; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1, -1, -1);
    WM_MoveWindow(_hWindow2,  1,  1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  GUI_Delay(SPEED);
}

/*******************************************************************
*
*       _DemoHideShowParent
*
* Function description
*   Demonstrates the use of WM_HideWindow and WM_ShowWindow
*/
static void _DemoHideShowParent(void) {
  _ChangeInfoText("WM_HideWindow(Parent)");
  GUI_Delay(SPEED);
  WM_HideWindow(_hWindow2);
  GUI_Delay(SPEED/3);
  WM_HideWindow(_hWindow1);
  GUI_Delay(SPEED);
  _ChangeInfoText("WM_ShowWindow(Parent)");
  GUI_Delay(SPEED);
  WM_ShowWindow(_hWindow1);
  GUI_Delay(SPEED/3);
  WM_ShowWindow(_hWindow2);
  GUI_Delay(SPEED);
}

/*******************************************************************
*
*       _DemoHideShowChild
*
* Function description
*   Demonstrates the use of WM_HideWindow and WM_ShowWindow
*/
static void _DemoHideShowChild(void) {
  _ChangeInfoText("WM_HideWindow(Child)");
  GUI_Delay(SPEED);
  WM_HideWindow(_hChild);
  GUI_Delay(SPEED);
  _ChangeInfoText("WM_ShowWindow(Child)");
  GUI_Delay(SPEED);
  WM_ShowWindow(_hChild);
  GUI_Delay(SPEED);
}

/*******************************************************************
*
*       _DemoClipping
*
* Function description
*   Demonstrates clipping at parent borders
*/
static void _DemoClipping(void) {
  int i;
  int tm;
  int tDiff;

  _ChangeInfoText("Demonstrating clipping of child");
  GUI_Delay(SPEED);
  for (i = 0; i < 25; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hChild,  1,  0);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 25; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hChild,  0,  1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 50; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hChild, -1,  0);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 25; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hChild,  0, -1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 25; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hChild,  1,  0);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  GUI_Delay(SPEED);
}

/*******************************************************************
*
*       _DemoRedrawing
*
* Function description
*   Demonstrates how useful can be a callback
*/
static void _DemoRedrawing(void) {
  int i;
  int tm;
  int tDiff;

  _ChangeInfoText("Demonstrating redrawing");
  GUI_Delay(SPEED);
  _LiftUp(40);
  GUI_Delay(SPEED/3);
  _ChangeInfoText("Using a callback for redrawing");
  GUI_Delay(SPEED/3);
  for (i = 0; i < 55; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1,  1,  1);
    WM_MoveWindow(_hWindow2, -1, -1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 55; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1, -1, -1);
    WM_MoveWindow(_hWindow2,  1,  1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  GUI_Delay(SPEED/4);
  _LiftDown(30);
  GUI_Delay(SPEED/2);
  _ChangeInfoText("Without redrawing");
  GUI_Delay(SPEED);
  _LiftUp(30);
  GUI_Delay(SPEED/4);
  WM_SetCallback(WM_HBKWIN, _cbBkWindowOld);
  for (i = 0; i < 55; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1,  1,  1);
    WM_MoveWindow(_hWindow2, -1, -1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 55; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1, -1, -1);
    WM_MoveWindow(_hWindow2,  1,  1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  GUI_Delay(SPEED/3);
  WM_SetCallback(WM_HBKWIN, _cbBkWindow);
  _LiftDown(40);
  GUI_Delay(SPEED);
}

/*******************************************************************
*
*       _DemoResizeWindow
*
* Function description
*   Demonstrates the use of WM_ResizeWindow
*/
static void _DemoResizeWindow(void) {
  int i;
  int tm;
  int tDiff;

  _ChangeInfoText("WM_ResizeWindow()");
  GUI_Delay(SPEED);
  _LiftUp(30);
  for (i = 0; i < 20; i++) {
    tm = GUI_GetTime();
    WM_ResizeWindow(_hWindow1,  1,  1);
    WM_ResizeWindow(_hWindow2, -1, -1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 40; i++) {
    tm = GUI_GetTime();
    WM_ResizeWindow(_hWindow1, -1, -1);
    WM_ResizeWindow(_hWindow2,  1,  1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 20; i++) {
    tm = GUI_GetTime();
    WM_ResizeWindow(_hWindow1,  1,  1);
    WM_ResizeWindow(_hWindow2, -1, -1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  _LiftDown(30);
  GUI_Delay(SPEED);
}

/*******************************************************************
*
*       _DemoSetCallback
*
* Function description
*   Demonstrates the use of WM_SetCallback
*/
static void _DemoSetCallback(void) {
  _ChangeInfoText("WM_SetCallback()");
  GUI_Delay(SPEED);
  WM_SetCallback(_hWindow1, _cbDemoCallback1);
  WM_InvalidateWindow(_hWindow1);
  GUI_Delay(SPEED/2);
  WM_SetCallback(_hWindow2, _cbDemoCallback2);
  WM_InvalidateWindow(_hWindow2);
  GUI_Delay(SPEED*3);
  WM_SetCallback(_hWindow1, _cbWindow1);
  WM_InvalidateWindow(_hWindow1);
  GUI_Delay(SPEED/2);
  WM_SetCallback(_hWindow2, _cbWindow2);
  WM_InvalidateWindow(_hWindow2);
  GUI_Delay(SPEED);
}

/*******************************************************************
*
*       _DemoDeleteWindow
*
* Function description
*   Demonstrates the use of WM_DeleteWindow
*/
static void _DemoDeleteWindow(void) {
  _ChangeInfoText("WM_DeleteWindow()");
  GUI_Delay(SPEED);
  WM_DeleteWindow(_hWindow2);
  GUI_Delay(SPEED/3);
  WM_DeleteWindow(_hWindow1);
  GUI_Delay(SPEED);
  _ChangeInfoText("");
  GUI_Delay(SPEED);
  //
  // Restore background callback and window colors
  //
  WM_SetCallback(WM_HBKWIN, _cbBkWindowOld);
  _WindowColor1 = GUI_GREEN;
  _WindowColor2 = GUI_RED;
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
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  GUI_SetBkColor(GUI_BLACK);
  WM_SetCreateFlags(WM_CF_MEMDEV);
  WM_EnableMemdev(WM_HBKWIN);
  while (1) {
    _DemoSetDesktopColor();
    _DemoCreateWindow();
    _DemoCreateWindowAsChild();
    _DemoInvalidateWindow();
    _DemoBringToTop();
    _DemoMoveTo();
    _DemoBringToBottom();
    _DemoMoveWindow();
    _DemoHideShowParent();
    _DemoHideShowChild();
    _DemoClipping();
    _DemoRedrawing();
    _DemoResizeWindow();
    _DemoSetCallback();
    _DemoDeleteWindow();
  }
}

/*************************** End of file ****************************/
