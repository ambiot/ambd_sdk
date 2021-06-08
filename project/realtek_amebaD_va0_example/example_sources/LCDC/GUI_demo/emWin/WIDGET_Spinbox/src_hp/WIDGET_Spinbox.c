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
File        : WIDGET_Spinbox.c
Purpose     : Shows how to use the SPINBOX widget.
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
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
static const GUI_WIDGET_CREATE_INFO _aDialogSpinbox[] = {
  { FRAMEWIN_CreateIndirect, "Spinbox",           0,                30,  -20,   330,  220, 0, 0, 0 },
  { TEXT_CreateIndirect,     "Step value",        GUI_ID_TEXT0,     20,  15,    80,   51,  0, 0, 0 },
  { TEXT_CreateIndirect,     "Editmode \"Step\"", GUI_ID_TEXT1,     20,  70,    80,   51,  0, 0, 0 },
  { TEXT_CreateIndirect,     "Editmode \"Edit\"", GUI_ID_TEXT2,     20,  125,   80,   51,  0, 0, 0 },
  { SPINBOX_CreateIndirect,  NULL,                GUI_ID_SPINBOX0, 130,  15,    100,  51,  0, 0, 0 },
  { SPINBOX_CreateIndirect,  NULL,                GUI_ID_SPINBOX1, 130,  70,    100,  51,  0, 0, 0 },
  { SPINBOX_CreateIndirect,  NULL,                GUI_ID_SPINBOX2, 130,  125,   100,  51,  0, 0, 0 },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbBk
*/
static void _cbBk(WM_MESSAGE * pMsg) {
  int xSize;
  int ySize;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    xSize = LCD_GetXSize();
    ySize = LCD_GetYSize();
    GUI_DrawGradientV(0, 0, xSize, ySize, GUI_BLUE, GUI_BLACK);
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_DispStringHCenterAt("WIDGET_Spinbox - Sample", xSize / 2, 5);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbClient
*/
static void _cbClient(WM_MESSAGE * pMsg) {
  EDIT_Handle hEdit;
  WM_HWIN     hItem;
  int         Value;
  int         NCode;
  int         Id;

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    FRAMEWIN_SetFont(pMsg->hWin, GUI_FONT_16B_ASCII);
    FRAMEWIN_SetSkin(pMsg->hWin, FRAMEWIN_SKIN_FLEX);
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0);
    TEXT_SetTextAlign(hItem, GUI_TA_VCENTER | GUI_TA_RIGHT);
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1);
    TEXT_SetTextAlign(hItem, GUI_TA_VCENTER | GUI_TA_RIGHT);
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT2);
    TEXT_SetTextAlign(hItem, GUI_TA_VCENTER | GUI_TA_RIGHT);
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_SPINBOX0);
    SPINBOX_SetSkin(hItem, SPINBOX_SKIN_FLEX);
    hEdit = SPINBOX_GetEditHandle(hItem);
    EDIT_SetDecMode(hEdit, 1, 1, 10, 0, 0);
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_SPINBOX1);
    SPINBOX_SetSkin(hItem, SPINBOX_SKIN_FLEX);
    hEdit = SPINBOX_GetEditHandle(hItem);
    EDIT_SetDecMode(hEdit, 1, 0, 99999, 0, 0);
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_SPINBOX2);
    SPINBOX_SetSkin(hItem, SPINBOX_SKIN_FLEX);
    SPINBOX_SetEditMode(hItem, SPINBOX_EM_EDIT);
    SPINBOX_SetRange(hItem, 0, 99999);
    break;
  case WM_NOTIFY_PARENT:
    NCode = pMsg->Data.v;
    switch (NCode) {
    case WM_NOTIFICATION_VALUE_CHANGED:
      Id = WM_GetId(pMsg->hWinSrc);
      if (Id == GUI_ID_SPINBOX0) {
        Value = SPINBOX_GetValue(pMsg->hWinSrc);
        hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_SPINBOX1);
        SPINBOX_SetStep(hItem, Value);
      }
      break;
    default:
      WM_DefaultProc(pMsg);
    }
    break;
  case WM_PAINT:
    GUI_SetBkColor(GUI_MAKE_COLOR(0xAE9E8D));
    GUI_Clear();
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
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  WM_SetCallback(WM_HBKWIN, _cbBk);
  TEXT_SetDefaultTextColor(GUI_WHITE);
  GUI_CreateDialogBox(_aDialogSpinbox, GUI_COUNTOF(_aDialogSpinbox), _cbClient,  WM_HBKWIN,  30,  60);
  while (1) {
    GUI_Delay(100);
  }
}

/*************************** End of file ****************************/
