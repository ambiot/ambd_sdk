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
File        : WIDGET_ListView.c
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
#include "LISTVIEW.h"
#include "FRAMEWIN.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define SPEED 650
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
static const GUI_COLOR Colors[]      = { GUI_BLACK, GUI_BLUE };

static const GUI_LOGPALETTE Palette  = { 
  2,     /* bps */
  1,     /* transparency */
  Colors /* pointer to colors */
};

static const unsigned char acBarCode[] = {
  _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_, ________, ________, ________, ________, _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_,
  _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_, ________, ________, ________, ________, _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_,
  _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_, ________, ________, ________, ________, _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_,
  _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_, ________, ________, ________, ________, _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_,
  _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_, ________, ________, ________, ________, _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_,
  _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_, ________, ________, ________, ________, _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_,
  _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_, ________, ________, ________, ________, _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_,
  _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_, ________, ________, ________, ________, _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_,
  _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_, ________, ________, ________, ________, _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_,
  _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_, ________, ________, ________, ________, _XXX_X__, XXX__XX_, X_X_X_XX, __X_XXX_,
};

static const GUI_BITMAP bmBarCode = { 96, 10, 12, 1, acBarCode, &Palette};

static const char * _aTable_1[][3] = {
  { "623499-0010001", "1", "Item 1" },
  { "623499-0010002", "2", "Item 2" },
  { "623499-0010003", "3", "Item 3" },
  { "623499-0010004", "4", "Item 4" },
  { "623499-0010005", "5", "Item 5" },
  { "623499-0010006", "6", "Item 6" },
  { "623499-0010007", "7", "Item 7" },
  { "623499-0010008", "8", "Item 8" }
};

static const char * _aTable_2[][3] = {
  { "111111-1111111", "100-A", "Item AAA" },
  { "222222-2222222", "100-B", "Item BBB" },
  { "333333-3333333", "100-C", "Item CCC" },
  { "444444-4444444", "100-D", "Item DDD" },
  { "555555-5555555", "100-E", "Item EEE" },
  { "666666-6666666", "100-F", "Item FFF" },
  { "777777-7777777", "100-G", "Item GGG" },
  { "888888-8888888", "100-H", "Item HHH" }
};

static LISTVIEW_Handle _hListView;

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
  GUI_Delay(SPEED);
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
      GUI_DispStringHCenterAt("LISTVIEW Widget - Sample", 160, 5);
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
*       _Demo
*/
static void _Demo(void) {
  unsigned int i;
  unsigned int j;

  int Key = 0;
  int Cnt = 15;
  char acInfoText[] = "-- sec to play with header control";
  HEADER_Handle hHeader;
  hHeader = LISTVIEW_GetHeader(_hListView);
  WM_SetFocus(_hListView);
  _ChangeInfoText("LISTVIEW_AddColumn");
  LISTVIEW_AddColumn(_hListView, 100, "EAN",         GUI_TA_CENTER);
  GUI_Delay(SPEED / 2);
  LISTVIEW_AddColumn(_hListView,  50, "Order #\0x0", GUI_TA_CENTER);
  GUI_Delay(SPEED / 2);
  LISTVIEW_AddColumn(_hListView, 100, "Description", GUI_TA_CENTER);
  GUI_Delay(SPEED / 2);
  _ChangeInfoText("SCROLLBAR_CreateAttached");
  SCROLLBAR_CreateAttached(_hListView, SCROLLBAR_CF_VERTICAL);
  GUI_Delay(SPEED / 2);
  _ChangeInfoText("LISTVIEW_AddRow");
  for (i = 0; i < GUI_COUNTOF(_aTable_1); i++) {
    LISTVIEW_AddRow(_hListView, _aTable_1[i]);
    GUI_Delay(SPEED / 3);
  }
  _ChangeInfoText("LISTVIEW_IncSel");
  for (i = 0; i < LISTVIEW_GetNumRows(_hListView); i++) {
    LISTVIEW_IncSel(_hListView);
    GUI_Delay(SPEED / 4);
  }
  GUI_Delay(SPEED / 4);
  _ChangeInfoText("LISTVIEW_DecSel");
  for (i = 0; i < LISTVIEW_GetNumRows(_hListView); i++) {
    LISTVIEW_DecSel(_hListView);
    GUI_Delay(SPEED / 4);
  }
  GUI_Delay(SPEED / 4);
  _ChangeInfoText("LISTVIEW_SetTextAlign");
  LISTVIEW_SetTextAlign(_hListView, 0, GUI_TA_RIGHT);
  GUI_Delay((int)(SPEED * 0.7));
  _ChangeInfoText("LISTVIEW_SetColumnWidth");
  LISTVIEW_SetColumnWidth(_hListView, 1, 70);
  GUI_Delay((int)(SPEED * 0.7));
  _ChangeInfoText("HEADER_SetTextColor");
  HEADER_SetTextColor(hHeader, GUI_BLUE);
  GUI_Delay((int)(SPEED * 0.7));
  _ChangeInfoText("LISTVIEW_SetItemText");
  for (i = 0; i < GUI_COUNTOF(_aTable_2); i++) {
    for (j = 0; j < GUI_COUNTOF(_aTable_2[i]); j++) {
      LISTVIEW_SetItemText(_hListView, j, i, _aTable_2[i][j]);
    }
  }
  GUI_Delay(SPEED / 2);
  _ChangeInfoText("LISTVIEW_SetBkColor");
  LISTVIEW_SetBkColor(_hListView, 0, GUI_YELLOW);
  GUI_Delay((int)(SPEED * 0.7));
  _ChangeInfoText("LISTVIEW_SetGridVis");
  LISTVIEW_SetGridVis(_hListView, 1);
  GUI_Delay((int)(SPEED * 0.7));
  _ChangeInfoText("HEADER_SetHeight");
  HEADER_SetHeight(hHeader, 30);
  GUI_Delay((int)(SPEED * 0.7));
  _ChangeInfoText("HEADER_SetBitmapEx");
  HEADER_SetBitmap(hHeader, 0, &bmBarCode);
  GUI_Delay((int)(SPEED * 0.7));
  while ((Key != GUI_KEY_ENTER) && (Cnt > 0)) {
    acInfoText[0] = '0' + (Cnt / 10);
    acInfoText[1] = '0' + (Cnt-- % 10);
    _ChangeInfoText(acInfoText);
    GUI_Delay(1000);
    Key = GUI_GetKey();
  }
}

/*********************************************************************
*
*       _DemoListView
*/
static void _DemoListView(void) {
  _ChangeMainText("LISTVIEW control without parent");
  _ChangeInfoText("LISTVIEW_Create");
  _hListView = LISTVIEW_Create(10, 80, 300, 89, 0, 1234, WM_CF_SHOW, 0);
  GUI_Delay(SPEED / 2);
  _Demo();
  _ChangeInfoText("WM_DeleteWindow");
  WM_DeleteWindow(_hListView);
  GUI_Delay(SPEED);
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
    _DemoListView();
  }
}

/*************************** End of file ****************************/

