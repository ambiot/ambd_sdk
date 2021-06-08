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
File        : WIDGET_Window.c
Purpose     : Example demonstrating the use of a WINDOW widget
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
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
#define RECOMMENDED_MEMORY (1024L * 5)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/*********************************************************************
*
*       _aDialog
*
* Function description
*   Dialog resource using a WINDOW widget
*/
static const GUI_WIDGET_CREATE_INFO _aDialog[] = {
  { WINDOW_CreateIndirect, "",       0,               0,  0,   260, 200, 0               },
  { TEXT_CreateIndirect,   "Dialog", 0,               80, 5,   100, 20,  TEXT_CF_HCENTER },
  { BUTTON_CreateIndirect, "Close",  GUI_ID_BUTTON0,  80, 160, 100, 20,  0               }
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbDialog
*
* Function description
*   Callback routine of the dialog
*/
static void _cbDialog(WM_MESSAGE *pMsg) {
  int NCode;
  int Id;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_GREEN);
    GUI_Clear();
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);    // Id of widget
    NCode = pMsg->Data.v;               // Notification code
    switch (NCode) {
    case WM_NOTIFICATION_RELEASED:      // React only if released
      switch (Id) {
      case GUI_ID_BUTTON0:
        GUI_EndDialog(pMsg->hWin, 0);
        break;
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
  while(1) {
    GUI_DispStringHCenterAt("WIDGET_Window sample\nshows how to use a WINDOW widget", 160, 5);
    GUI_ExecDialogBox(_aDialog, GUI_COUNTOF(_aDialog), _cbDialog, WM_HBKWIN, 30, 30);
    GUI_Clear();
    GUI_DispStringHCenterAt("Dialog has been closed", 160, 5);
    GUI_Delay(1000);
    GUI_Clear();
  }
}

/*************************** End of file ****************************/
