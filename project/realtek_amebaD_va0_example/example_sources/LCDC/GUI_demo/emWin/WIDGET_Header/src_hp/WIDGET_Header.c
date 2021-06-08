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
File        : WIDGET_Header.c
Purpose     : Demonstrates the use of header widgets
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
---------------------------END-OF-HEADER------------------------------
*/
#include <stddef.h>
#include <string.h>
#include "GUI.h"
#include "HEADER.h"
#include "FRAMEWIN.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define MSG_CHANGE_MAIN_TEXT (WM_USER + 0)
#define MSG_CHANGE_INFO_TEXT (WM_USER + 1)

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 10)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static HEADER_Handle _hHeader;
static char _acMainText[100];
static char _acInfoText[100];

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*******************************************************************
*
*       _ChangeMainText
*
*  Sends a message to the background window and invalidate it, so
*  the callback of the background window display the new text.
*/
static void _ChangeMainText(char* pStr) {
  WM_MESSAGE Message;

  Message.MsgId  = MSG_CHANGE_MAIN_TEXT;
  Message.Data.p = pStr;
  WM_SendMessage(WM_HBKWIN, &Message);
  WM_InvalidateWindow(WM_HBKWIN);
}

/*******************************************************************
*
*       _ChangeInfoText
*
*  Sends a message to the background window and invalidate it, so
*  the callback of the background window display the new text.
*/
static void _ChangeInfoText(char* pStr) {
  WM_MESSAGE Message;

  Message.MsgId  = MSG_CHANGE_INFO_TEXT;
  Message.Data.p = pStr;
  WM_SendMessage(WM_HBKWIN, &Message);
  WM_InvalidateWindow(WM_HBKWIN);
}

/*******************************************************************
*
*       _cbBkWindow
*/
static void _cbBkWindow(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
    case MSG_CHANGE_MAIN_TEXT:
      strcpy(_acMainText, (char const *)pMsg->Data.p);
      WM_InvalidateWindow(pMsg->hWin);
      break;
    case MSG_CHANGE_INFO_TEXT:
      strcpy(_acInfoText, (char const *)pMsg->Data.p);
      WM_InvalidateWindow(pMsg->hWin);
      break;
    case WM_PAINT:
      GUI_SetBkColor(GUI_BLACK);
      GUI_Clear();
      GUI_SetColor(GUI_WHITE);
      GUI_SetFont(&GUI_Font24_ASCII);
      GUI_DispStringHCenterAt("HEADER Widget - Sample", 160, 5);
      GUI_SetFont(&GUI_Font8x16);
      GUI_DispStringAt(_acMainText, 5, 40);
      GUI_SetFont(&GUI_Font8x8);
      GUI_DispStringAt(_acInfoText, 5, 60);
      break;
    default:
      WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _OnPaint
*/
static void _OnPaint(void) {
  GUI_RECT Rect;

  GUI_SetBkColor(GUI_GRAY);
  GUI_Clear();
  WM_GetClientRect(&Rect);
  Rect.x1 = HEADER_GetItemWidth(_hHeader, 0);
  GUI_SetColor(GUI_RED);
  GUI_FillRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1);
  Rect.x0 = Rect.x1;
  Rect.x1 += HEADER_GetItemWidth(_hHeader, 1);
  GUI_SetColor(GUI_GREEN);
  GUI_FillRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1);
  Rect.x0 = Rect.x1;
  Rect.x1 += HEADER_GetItemWidth(_hHeader, 2);
  GUI_SetColor(GUI_BLUE);
  GUI_FillRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1);
}

/*********************************************************************
*
*       cbWindow
*/
static void _cbWindow(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
    case WM_PAINT:
      _OnPaint();
      break;
  }
  WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       _Demo
*/
static void _Demo(void) {
  int Key;
  int Cnt;
  char acInfoText[] = "-- sec to play with header control";

  Key = 0;
  Cnt = 10;
  _ChangeInfoText("HEADER_AddItem");
  HEADER_AddItem(_hHeader, 100, "Red"  , GUI_TA_VCENTER | GUI_TA_HCENTER);
  HEADER_AddItem(_hHeader,   0, "Green", GUI_TA_VCENTER | GUI_TA_HCENTER);
  HEADER_AddItem(_hHeader,   0, ":-)"  , GUI_TA_VCENTER | GUI_TA_HCENTER);
  GUI_Delay(750);
  _ChangeInfoText("HEADER_SetItemWidth");
  HEADER_SetItemWidth(_hHeader, 1, 60);
  GUI_Delay(750);
  _ChangeInfoText("HEADER_SetItemText");
  HEADER_SetItemWidth(_hHeader, 2, 100);
  HEADER_SetItemText(_hHeader, 2, "Blue");
  GUI_Delay(750);
  _ChangeInfoText("HEADER_SetFont");
  HEADER_SetFont(_hHeader, &GUI_Font8x8);
  GUI_Delay(750);
  _ChangeInfoText("HEADER_SetHeight");
  HEADER_SetHeight(_hHeader, 50);
  GUI_Delay(750);
  _ChangeInfoText("HEADER_SetTextColor");
  HEADER_SetTextColor(_hHeader, GUI_MAKE_COLOR(0x00cc00));
  GUI_Delay(750);
  _ChangeInfoText("HEADER_SetBkColor");
  HEADER_SetBkColor(_hHeader, GUI_DARKGRAY);
  GUI_Delay(750);
  _ChangeInfoText("HEADER_SetTextAlign");
  HEADER_SetTextAlign(_hHeader, 0, GUI_TA_HCENTER);
  while (!Key && (Cnt > 0)) {
    acInfoText[0] = '0' + (Cnt / 10);
    acInfoText[1] = '0' + (Cnt-- % 10);
    _ChangeInfoText(acInfoText);
    GUI_Delay(1000);
    Key = GUI_GetKey();
  }
}

/*********************************************************************
*
*       _DemoHeaderFrameWin
*/
static void _DemoHeaderFrameWin(void) {
  FRAMEWIN_Handle hFrameWin;

  _ChangeMainText("HEADER control inside a FRAMEWIN");
  hFrameWin = FRAMEWIN_Create("Title", _cbWindow, WM_CF_SHOW, 10, 80, 300, 140);
  FRAMEWIN_SetActive(hFrameWin, 1);
  _hHeader = HEADER_CreateAttached(WM_GetClientWindow(hFrameWin), 1234, 0);
  _Demo();
  WM_DeleteWindow(hFrameWin);
}

/*********************************************************************
*
*       _DemoHeaderWin
*/
static void _DemoHeaderWin(void) {
  WM_HWIN hWin;

  _ChangeMainText("HEADER control inside a window");
  hWin = WM_CreateWindow(10, 80, 300, 140, WM_CF_SHOW, _cbWindow, 0);
  _hHeader = HEADER_CreateAttached(hWin, 1234, 0);
  _Demo();
  WM_DeleteWindow(hWin);
}

/*********************************************************************
*
*       _DemoHeader
*/
static void _DemoHeader(void) {
  _ChangeMainText("HEADER control without parent");
  _hHeader = HEADER_Create(10, 80, 300, 0, 0, 1234, WM_CF_SHOW, 0);
  _Demo();
  WM_DeleteWindow(_hHeader);
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
  WM_EnableMemdev(WM_HBKWIN);
  WM_SetCreateFlags(WM_CF_MEMDEV);
  WM_SetCallback(WM_HBKWIN, _cbBkWindow);
  GUI_CURSOR_Show();
  while(1) {
    _DemoHeaderFrameWin();
    _DemoHeaderWin();
    _DemoHeader();
  }
}

/*************************** End of file ****************************/
