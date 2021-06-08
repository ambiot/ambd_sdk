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
File        : About.c
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
static WM_HWIN _hPrevWin;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "About", ID_FRAMEWIN,   0, 272*2, 320, 240, 0},
  { BUTTON_CreateIndirect,   "OK",    GUI_ID_OK,   230, 140,  60,  20 },
};

static const char _aExplain[] = {
  "This sample shows how to use the virtual screen\n"
  "support for switching between different screens.\n"
  "It can be used as a starting point for developing\n"
  "your own application."
};

/********************************************************************
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
  WM_HWIN hDlg, hWinSrc;
  int Id, NCode;
  GUI_RECT Rect;
  Rect.x0 = 10;
  Rect.y0 = 10;
  Rect.x1 = 300;
  Rect.y1 = 200;
  hWinSrc = pMsg->hWinSrc;
  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    WM_MakeModal(hDlg);
    FRAMEWIN_SetFont(hDlg, &GUI_Font24B_ASCII);
    FRAMEWIN_SetTextAlign(hDlg, GUI_TA_HCENTER);
    FRAMEWIN_SetClientColor(hDlg, GUI_GREEN);
    break;
  case WM_PAINT:
    GUI_SetColor(GUI_BLACK);
    GUI_SetFont(&GUI_Font16_ASCII);
    GUI_DispStringInRect(&_aExplain[0], &Rect, GUI_TA_LEFT);
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(hWinSrc);                    /* Id of widget */
    NCode = pMsg->Data.v;                         /* Notification code */
    if (NCode == WM_NOTIFICATION_RELEASED) {      /* React only if released */
      if (Id == GUI_ID_OK) {                      /* OK Button */
        GUI_EndDialog(hDlg, 0);
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
*       ExecAbout
*/
void ExecAbout(void) {
  _hPrevWin = WM_GetFocussedWindow();
  GUI_SetOrg(0, 272*2);
  GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
  GUI_SetOrg(0, 0);

}


