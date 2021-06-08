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
File        : Setup.c
Purpose     : TBD
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"
#include "setup.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
/*********************************************************************
*
*       Dialog IDs
*/
#define ID_FRAMEWIN              1

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static char    _IsInited;
static WM_HWIN _hDlg;
static WM_HWIN _hPrevWin;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Setup",   ID_FRAMEWIN,     0, 272, 320, 240, 0},
  { CHECKBOX_CreateIndirect, NULL,      GUI_ID_CHECK0,  50,  40, 150,   0 },
  { CHECKBOX_CreateIndirect, NULL,      GUI_ID_CHECK1,  50,  70, 150,   0 },
  { CHECKBOX_CreateIndirect, NULL,      GUI_ID_CHECK2,  50, 100, 150,   0 },
  { TEXT_CreateIndirect,     "User ID:",0,              50, 130,  40,  20, TEXT_CF_LEFT | TEXT_CF_VCENTER },
  { EDIT_CreateIndirect,     NULL,      GUI_ID_EDIT0,   95, 130, 100,  20 },
  { BUTTON_CreateIndirect,   "OK",      GUI_ID_OK,     230, 140,  60,  20 },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbCallback
*/
static void _cbCallback(WM_MESSAGE * pMsg) {
  WM_HWIN hDlg, hWinSrc, hItem;
  int Id, NCode;
  hWinSrc = pMsg->hWinSrc;
  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    FRAMEWIN_SetFont(hDlg, &GUI_Font24B_ASCII);
    FRAMEWIN_SetTextAlign(hDlg, GUI_TA_HCENTER);
    FRAMEWIN_SetClientColor(hDlg, GUI_RED);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK0); CHECKBOX_SetText(hItem, "Enable alarm");
    hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK1); CHECKBOX_SetText(hItem, "Enable display lighting");
    hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK2); CHECKBOX_SetText(hItem, "Enable color mode");
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(hWinSrc);      /* Id of widget */
    NCode = pMsg->Data.v;                 /* Notification code */
    if (NCode == WM_NOTIFICATION_RELEASED) {      /* React only if released */
      if (Id == GUI_ID_OK) {            /* OK Button */
        GUI_SetOrg(0, 0);
        WM_SetFocus(_hPrevWin);
      }
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _Init
*/
static void _Init(void) {
  if (_IsInited) {
    return;
  }
  _IsInited = 1;
  CHECKBOX_SetDefaultTextColor(GUI_WHITE);
  CHECKBOX_SetDefaultBkColor(GUI_INVALID_COLOR);
  CHECKBOX_SetDefaultFocusColor(GUI_WHITE);
  TEXT_SetDefaultTextColor(GUI_WHITE);
  _hDlg = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       ExecSetup
*/
void ExecSetup(void) {
  _hPrevWin = WM_GetFocussedWindow();
  _Init();
  GUI_SetOrg(0, 272);
  WM_SetFocus(_hDlg);
}


