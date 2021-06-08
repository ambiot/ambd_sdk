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
File        : DIALOG_MultiEdit.c
Purpose     : Example demonstrating the use of a MULTIEDIT widget
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/
#include <stddef.h>
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
#define RECOMMENDED_MEMORY (1024L * 20)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static int _Password = 0;
static int _RdOnly   = 0;
static int _RTF8     = 0;

/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created manually, but could also be created by a GUI-builder.
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect,  "MultiEdit sample",        0,                   3,   3, 314, 234, FRAMEWIN_CF_MOVEABLE },
  { MULTIEDIT_CreateIndirect, "Suspend",                 GUI_ID_MULTIEDIT0,   5,   5, 152, 120, 0, 0 },
//
// Read only check box
//
  { CHECKBOX_CreateIndirect,  0,                         GUI_ID_CHECK0,       5, 110,   0,   0 },
  { TEXT_CreateIndirect,      "R/O",                     0,                  25, 110,  50,  15, TEXT_CF_LEFT },
//
// UTF8 check box
//
  { CHECKBOX_CreateIndirect,  0,                         GUI_ID_CHECK1,      50, 110,   0,   0 },
  { TEXT_CreateIndirect,      "UTF8",                    0,                  70, 110,  50,  15, TEXT_CF_LEFT },
//
// Password mode check box
//
  { CHECKBOX_CreateIndirect,  0,                         GUI_ID_CHECK2,     102, 110,   0,   0 },
  { TEXT_CreateIndirect,      "Passw.",                  0,                 122, 110,  50,  15, TEXT_CF_LEFT },
//
// Radio button for scroll mode
//
  { TEXT_CreateIndirect,      "H",                       0,                 241,   3,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "V",                       0,                 257,   3,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "Scroll",                  0,                 272,   3,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "Auto",                    0,                 272,  17,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "Off",                     0,                 272,  32,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "On",                      0,                 272,  47,  50,  15, TEXT_CF_LEFT },
  { RADIO_CreateIndirect,      NULL,                     GUI_ID_RADIO0,     236,  16,   0,   0, 0, 0x0f03 },
  { RADIO_CreateIndirect,      NULL,                     GUI_ID_RADIO1,     252,  16,   0,   0, 0, 0x0f03 },
//
// Radio button for effect type
//
  { TEXT_CreateIndirect,      "Effect",                    0,               169,   3,  60,  15, TEXT_CF_LEFT },
  { RADIO_CreateIndirect,      NULL,                     GUI_ID_RADIO3,     165,  16,  51,   0, 0, 0x0f03 },
//
// Radio button for wrap mode
//
  { TEXT_CreateIndirect,      "Wrap",                    0,                 159, 155,  60,  15, TEXT_CF_LEFT },
  { RADIO_CreateIndirect,      NULL,                     GUI_ID_RADIO2,     155, 168,  47,   0, 0, 0x0d03 },
//
// Prompt
//
  { TEXT_CreateIndirect,      "Prompt:",                 0,                 167,  65,  50,  15, TEXT_CF_LEFT },
  { EDIT_CreateIndirect,      "Prompt:",                 GUI_ID_EDIT0,      212,  65,  45,  15, TEXT_CF_LEFT },
  { BUTTON_CreateIndirect,    "Set",                     GUI_ID_BUTTON1,    262,  65,  35,  15 },
//
// Cursor offset
//
  { TEXT_CreateIndirect,      "CurOff:",                 0,                 167,  83,  50,  15, TEXT_CF_LEFT },
  { EDIT_CreateIndirect,      0,                         GUI_ID_EDIT1,      212,  83,  45,  15, TEXT_CF_LEFT, 3 },
  { BUTTON_CreateIndirect,    "Set",                     GUI_ID_BUTTON2,    262,  83,  35,  15 },
//
// Window size
//
  { TEXT_CreateIndirect,      "Window size",             0,                 167, 102,  60,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "Y: ",                     0,                 167, 114,  60,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "X: ",                     0,                 167, 133,  60,  15, TEXT_CF_LEFT },
  { SLIDER_CreateIndirect,    NULL,                      GUI_ID_SLIDER0,    182, 114, 115,  20, 0},
  { SLIDER_CreateIndirect,    NULL,                      GUI_ID_SLIDER1,    182, 133, 115,  20, 0},
//
// HBorder
//
  { TEXT_CreateIndirect,      "HBorder",                 0,                 207, 151,  60,  15, TEXT_CF_LEFT },
  { SLIDER_CreateIndirect,    NULL,                      GUI_ID_SLIDER2,    207, 163,  90,  20, 0},
//
// MaxNumChars
//
  { TEXT_CreateIndirect,      "NumChars",                0,                 207, 181,  60,  15, TEXT_CF_LEFT },
  { SLIDER_CreateIndirect,    NULL,                      GUI_ID_SLIDER3,    207, 193,  90,  20, 0},
//
// Set font
//
  { BUTTON_CreateIndirect,    "Monosp. Font",            GUI_ID_BUTTON6,      5, 130,  78,  20 },
  { BUTTON_CreateIndirect,    "Prop. Font",              GUI_ID_BUTTON7,     88, 130,  68,  20 },
//
// Set text
  { BUTTON_CreateIndirect,    "Short\nText",             GUI_ID_BUTTON3,      5, 155,  47,  30 },
  { BUTTON_CreateIndirect,    "Long\nText",              GUI_ID_BUTTON4,     57, 155,  47,  30 },
  { BUTTON_CreateIndirect,    "Add\nText",               GUI_ID_BUTTON5,    107, 155,  47,  30 },
//
// Add. buttons
//
  { BUTTON_CreateIndirect,    "OK",                      GUI_ID_OK,           5, 190,  47,  20 },
  { BUTTON_CreateIndirect,    "Cancel",                  GUI_ID_CANCEL,      57, 190,  47,  20 },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbBkWindow
*/
static void _cbBkWindow(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_RED);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_DispStringHCenterAt("WIDGET_MultiEdit", 160, 5);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbCallback
*/
static void _cbCallback(WM_MESSAGE * pMsg) {
  int     NCode;
  int     Id;
  int     Sel;
  char    ac[80];
  WM_HWIN hDlg;
  WM_HWIN hMulti;
  WM_HWIN hItem;

  hDlg   = pMsg->hWin;
  hMulti = WM_GetDialogItem(hDlg, GUI_ID_MULTIEDIT0);
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    hItem = WM_GetDialogItem(hDlg, GUI_ID_SLIDER0);
    SLIDER_SetRange(hItem, 1, 100);
    SLIDER_SetValue(hItem, 100);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_SLIDER1);
    SLIDER_SetRange(hItem, 1, 152);
    SLIDER_SetValue(hItem, 152);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_SLIDER2);
    SLIDER_SetRange(hItem, 0, 5);
    SLIDER_SetValue(hItem, 2);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_SLIDER3);
    SLIDER_SetRange(hItem, 0, 100);
    SLIDER_SetValue(hItem, 0);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);
    EDIT_SetDecMode(hItem, 0, 0, 1000, 0, 0);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_RADIO2);
    RADIO_SetText(hItem, "None", 0);
    RADIO_SetText(hItem, "Char", 1);
    RADIO_SetText(hItem, "Word", 2);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_RADIO3);
    RADIO_SetText(hItem, "None",   0);
    RADIO_SetText(hItem, "Simple", 1);
    RADIO_SetText(hItem, "3D",     2);
    RADIO_SetValue(hItem, 2);
    RADIO_SetTextColor(hItem, GUI_BLUE);
    MULTIEDIT_EnableBlink(hMulti, 300, 1);
    MULTIEDIT_SetFont(hMulti, &GUI_Font8x16);
    MULTIEDIT_SetBkColor(hMulti, 0, GUI_YELLOW);
    MULTIEDIT_SetTextColor(hMulti, 0, GUI_BLUE);
    MULTIEDIT_SetAutoScrollV(hMulti, 1);
    MULTIEDIT_SetInsertMode(hMulti, 1);
    MULTIEDIT_SetPrompt(hMulti, "C:\\>");
    MULTIEDIT_SetHBorder(hMulti, 2);
    MULTIEDIT_SetText(hMulti, "Multiedit - long line 12345678901234567890\nThis demonstrates the use of a MULTIEDIT widget");
    MULTIEDIT_AddKey(hMulti, 'A');
    MULTIEDIT_AddKey(hMulti, 'B');
    MULTIEDIT_AddKey(hMulti, 'C');
    MULTIEDIT_AddKey(hMulti, GUI_KEY_ENTER);
    MULTIEDIT_SetAutoScrollH(hMulti, 1);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_BUTTON5);
    BUTTON_SetFocussable(hItem, 0);
    break;
  case WM_KEY:
    switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) {
    case GUI_KEY_ESCAPE:
      GUI_EndDialog(hDlg, 1);
      break;
    case GUI_KEY_ENTER:
      GUI_EndDialog(hDlg, 0);
      break;
    }
    break;
  case WM_NOTIFY_PARENT:
    Id     = WM_GetId(pMsg->hWinSrc);
    NCode  = pMsg->Data.v;
    hItem  = WM_GetDialogItem(hDlg, Id);
    switch (NCode) {
    case WM_NOTIFICATION_VALUE_CHANGED:
      switch (Id) {
      case GUI_ID_SLIDER0:
        Sel = SLIDER_GetValue(hItem);
        WM_SetYSize(hMulti, Sel);
        break;
      case GUI_ID_SLIDER1:
        Sel = SLIDER_GetValue(hItem);
        WM_SetXSize(hMulti, Sel);
        break;
      case GUI_ID_SLIDER2:
        Sel = SLIDER_GetValue(hItem);
        MULTIEDIT_SetHBorder(hMulti, Sel);
        break;
      case GUI_ID_SLIDER3:
        Sel = SLIDER_GetValue(hItem);
        MULTIEDIT_SetMaxNumChars(hMulti, Sel);
        break;
      case GUI_ID_RADIO0:
        //
        // Horizontal scrollbar
        //
        Sel = RADIO_GetValue(hItem);
        switch (Sel) {
        case 0:
          MULTIEDIT_SetAutoScrollH(hMulti, 1);           // Auto
          break;
        case 1:
          MULTIEDIT_SetAutoScrollH(hMulti, 0);           // Off
          WM_SetScrollbarH(hMulti, 0);
          break;
        case 2:
          MULTIEDIT_SetAutoScrollH(hMulti, 0);           // On
          WM_SetScrollbarH(hMulti, 1);
          break;
        }
        break;
      case GUI_ID_RADIO1:
        //
        // Vertical scrollbar
        //
        Sel = RADIO_GetValue(hItem);
        switch (Sel) {
        case 0:
          MULTIEDIT_SetAutoScrollV(hMulti, 1);
          break;
        case 1:
          MULTIEDIT_SetAutoScrollV(hMulti, 0);
          WM_SetScrollbarV(hMulti, 0);
          break;
        case 2:
          MULTIEDIT_SetAutoScrollV(hMulti, 0);
          WM_SetScrollbarV(hMulti, 1);
          break;
        }
        break;
      case GUI_ID_RADIO2:
        //
        // Wrap
        //
        Sel = RADIO_GetValue(hItem);
        switch (Sel) {
        case 0:
          MULTIEDIT_SetWrapNone(hMulti);
          break;
        case 1:
          MULTIEDIT_SetWrapChar(hMulti);
          break;
        case 2:
          MULTIEDIT_SetWrapWord(hMulti);
          break;
        }
        break;
      case GUI_ID_RADIO3:
        //
        // Effect type
        //
        Sel = RADIO_GetValue(hItem);
        switch (Sel) {
        case 0:
          WIDGET_SetEffect(hMulti, &WIDGET_Effect_None);
          break;
        case 1:
          WIDGET_SetEffect(hMulti, &WIDGET_Effect_Simple);
          break;
        case 2:
          WIDGET_SetEffect(hMulti, &WIDGET_Effect_3D);
          break;
        }
        break;
      }
      break;
      case WM_NOTIFICATION_RELEASED:      // React only if released
        WM_GetDialogItem(hDlg, Id);
        switch (Id) {
        case GUI_ID_OK:
          GUI_EndDialog(hDlg, 0);
          break;
        case GUI_ID_CANCEL:
          GUI_EndDialog(hDlg, 1);
          break;
        case GUI_ID_CHECK0:
          _RdOnly ^= 1;
          MULTIEDIT_SetReadOnly(hMulti, _RdOnly);
          break;
        case GUI_ID_CHECK1:
          _RTF8 ^= 1;
          if (_RTF8) {
            GUI_UC_SetEncodeUTF8();
          } else {
            GUI_UC_SetEncodeNone();
          }
          WM_InvalidateWindow(hMulti);
          break;
        case GUI_ID_CHECK2:
          _Password ^= 1;
          MULTIEDIT_SetPasswordMode(hMulti, _Password);
          break;
        case GUI_ID_BUTTON1:
          hItem  = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
          EDIT_GetText(hItem, &ac[0], sizeof(ac));
          MULTIEDIT_SetPrompt(hMulti, ac);
          break;
        case GUI_ID_BUTTON2:
          hItem  = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);
          MULTIEDIT_SetCursorOffset(hMulti, EDIT_GetValue(hItem));
          WM_SetFocus(hMulti);
          break;
        case GUI_ID_BUTTON3:
          MULTIEDIT_SetText(hMulti, "Short text");
          break;
        case GUI_ID_BUTTON4:
          MULTIEDIT_SetText(hMulti, "Long text\n123456789012345678901234567890\nLast line\n");
          break;
        case GUI_ID_BUTTON5:
          MULTIEDIT_AddText(hMulti, "Added");
          break;
        case GUI_ID_BUTTON6:
          MULTIEDIT_SetFont(hMulti, &GUI_Font8x16);
          break;
        case GUI_ID_BUTTON7:
          MULTIEDIT_SetFont(hMulti, &GUI_Font16_1);
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
  WM_SetCallback(WM_HBKWIN, _cbBkWindow);
  WM_SetCreateFlags(WM_CF_MEMDEV);  // Use memory devices on all windows to avoid flicker
  while (1) {
    GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbCallback, 0, 0, 0);
    GUI_Delay(1000);
  }
}

/*************************** End of file ****************************/
