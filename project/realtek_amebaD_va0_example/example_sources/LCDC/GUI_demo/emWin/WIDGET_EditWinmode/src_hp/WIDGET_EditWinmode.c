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
File        : WIDGET_EditWinmode.c
Purpose     : Demonstrates how to use a edit widget in 'windows' mode
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/
#include <stddef.h>
#include "GUI.h"
#include "WM.h"
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
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Edit winmode", 0,         90,  90, 140, 130, FRAMEWIN_CF_MOVEABLE},
  { EDIT_CreateIndirect,     NULL,     GUI_ID_EDIT0,    10,  10, 110,  20, 0, 15},
  { EDIT_CreateIndirect,     NULL,     GUI_ID_EDIT1,    10,  40, 110,  20, 0, 15},
  { BUTTON_CreateIndirect,   "Ok",     GUI_ID_OK,       10,  80,  50,  20 },
  { BUTTON_CreateIndirect,   "Cancel", GUI_ID_CANCEL,   70,  80,  50,  20 },
};

static WM_CALLBACK * _pEditCallback;

static char * _apExplain[] = {
  "This sample shows how to use edit widgets with a",
  "user defined callback function and how to set a",
  "user defined AddKey function. It selects the",
  "contents of the edit field on receiving the focus",
  "and overwrites the contents if a key other than",
  "a cursor key is pressed.",
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbEditAddKey
*
* Function description
*   This function is called by the edit widget if a character should be added to the contents of the widget.
*/
static void _cbEditAddKey(EDIT_Handle hObj, int Key) {
  char acBuffer[2] = {0};

  switch (Key) {
  case GUI_KEY_LEFT:
    EDIT_SetpfAddKeyEx(hObj, 0);                            // Clear user defined AddKey function
    EDIT_SetCursorAtChar(hObj, EDIT_GetNumChars(hObj) - 1); // Set cursor if GUI_KEY_LEFT has been pressed
    break;
  case GUI_KEY_RIGHT:
    EDIT_SetpfAddKeyEx(hObj, 0);                            // Clear user defined AddKey function
    EDIT_SetCursorAtChar(hObj, 1);                          // Set cursor if GUI_KEY_RIGHT has been pressed
    break;
  case GUI_KEY_UP:                                          // Do not react on GUI_KEY_UP and GUI_KEY_DOWN
  case GUI_KEY_DOWN:
    break;
  default:
    if (Key >= 0x20) {
      acBuffer[0] = (U8)Key;
      EDIT_SetpfAddKeyEx(hObj, 0);                          // Clear user defined AddKey function
      EDIT_SetText(hObj, acBuffer);                         // Overwrite contents of edit widget with pressed key
    }
  }
}

/*********************************************************************
*
*       _cbEdit
*
* Function description
*   New callback function of edit widgets which should work in 'windows' mode.
*/
static void _cbEdit(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
  case WM_PID_STATE_CHANGED:
    if (((const WM_PID_STATE_CHANGED_INFO*)pMsg->Data.p)->State) {
      return;            // Do not call edit callback
    }
    break;
  case WM_TOUCH:
    if (pMsg->Data.p) {  // Something happened in our area (pressed or released)
      const GUI_PID_STATE* pState;
      pState = (const GUI_PID_STATE*)pMsg->Data.p;
      if (pState->Pressed) {
        if (WM_GetFocussedWindow() != pMsg->hWin) {
          WM_SetFocus(pMsg->hWin);
          return;        // Do not call edit callback
        }
      }
    }
    break;
  case WM_SET_FOCUS:
    if (pMsg->Data.v == 1) {
      EDIT_SetpfAddKeyEx(pMsg->hWin, _cbEditAddKey); // Set function pointer for a user defined AddKey function
      EDIT_SetSel(pMsg->hWin, 0, -1);                // Select the whole contents of the edit field
    }
  }
  if (_pEditCallback) {
    _pEditCallback(pMsg);
  }
}

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  int     i;
  int     NCode;
  int     Id;
  WM_HWIN hDlg;
  WM_HWIN hItem;

  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    FRAMEWIN_SetFont(pMsg->hWin, &GUI_Font13_ASCII);
    FRAMEWIN_SetTextAlign(pMsg->hWin, GUI_TA_HCENTER);
    for (i = 0; i < 2; i++) {
      hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0 + i);  // Get the handle of the edit widget
      if (!_pEditCallback) {
        _pEditCallback = WM_SetCallback(hItem, _cbEdit); // Overwrite callback function and remember original function
      } else {
        WM_SetCallback(hItem, _cbEdit);                  // Overwrite callback function
      }
      EDIT_SetText(hItem, "Hello world!");               // Fill widget with text
      EDIT_SetpfAddKeyEx(hItem, _cbEditAddKey);          // Set function pointer for a user defined AddKey function
      EDIT_SetSel(hItem, 0, -1);                         // Select the whole contents of the edit field
    }
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);      // Id of widget
    NCode = pMsg->Data.v;                 // Notification code
    switch (NCode) {
      case WM_NOTIFICATION_RELEASED:      // React only if released
        if (Id == GUI_ID_OK) {            // OK Button
          GUI_EndDialog(hDlg, 0);
        }
        if (Id == GUI_ID_CANCEL) {        // Cancel Button
          GUI_EndDialog(hDlg, 1);
        }
        break;
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbDesktop
*
* Function description
*   This routine handles the drawing of the desktop window.
*/
static void _cbDesktop(WM_MESSAGE * pMsg) {
  unsigned i;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_RED);
    GUI_Clear();
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_DispStringHCenterAt("WIDGET_EditWinmode", 160, 5);
    GUI_DispNextLine();
    GUI_SetFont(GUI_DEFAULT_FONT);
    GUI_DispNextLine();
    for (i = 0; i < GUI_COUNTOF(_apExplain); i++) {
      GUI_DispStringHCenterAt(_apExplain[i], 160, GUI_GetDispPosY());
      GUI_DispNextLine();
    }
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

  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  WM_SetCallback(WM_HBKWIN, _cbDesktop);
  while(1) {
    GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialog, 0, 0, 0);
    GUI_Delay(1000);
  }
}

/*************************** End of file ****************************/

