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
File        : WIDGET_Multiedit.c
Purpose     : Demonstrates the use of the MULTIEDIT widget.
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( ) 
----------------------------------------------------------------------
*/
#include "GUI.h"
#include "MULTIEDIT.h"
#include "FRAMEWIN.h"
#include "BUTTON.h"

#include <string.h>

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define SPEED         1000

#define MIN_SIZE_X    200
#define MIN_SIZE_Y     80

#define RESIZE_X      (1<<0)
#define RESIZE_Y      (1<<1)
#define REPOS_X       (1<<2)
#define REPOS_Y       (1<<3)

#define ID_NONEWRAP   (GUI_ID_USER + 0)
#define ID_WORDWRAP   (GUI_ID_USER + 1)
#define ID_CHARWRAP   (GUI_ID_USER + 2)
#define ID_OVERWRITE  (GUI_ID_USER + 3)
#define ID_READONLY   (GUI_ID_USER + 4)
#define ID_PASSWORD   (GUI_ID_USER + 5)

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 20)

/*********************************************************************
*
*       static data
*
**********************************************************************
*/
static WM_CALLBACK* _pcbFrameWin;
static WM_CALLBACK* _pcbFrameWinClient;
static WM_CALLBACK* _pcbMultiEdit;
static WM_HWIN      _hMEdit, _hFrame, _hClient;
static WM_HWIN      _hWrapButton;
static int          _CaptureX;
static int          _CaptureY;
static int          _HasCaptured;
static int          _ReadOnly;
static int          _Overwrite;
static int          _Password;
static char         _acInfoText[100] = {0};

/*********************************************************************
*
*       static code, helpers
*
**********************************************************************
*/
/*********************************************************************
*
*       _ChangeInfoText
*/
static int _ChangeInfoText(const char* pString, int Delay) {
  if (_hFrame) {
    GUI_Delay((int)(Delay * 0.75));
    strcpy(_acInfoText, pString);
    WM_InvalidateWindow(WM_HBKWIN);
  }
  if (_hFrame) {
    GUI_Delay(Delay);
    return 0;
  } 
  return 1;
}

/*********************************************************************
*
*       _SetCapture
*/
static void _SetCapture(FRAMEWIN_Handle hWin, int x, int y, int Mode) {
  if ((_HasCaptured & REPOS_X) == 0) {
    _CaptureX = x;
  }
  if ((_HasCaptured & REPOS_Y) == 0) {
    _CaptureY = y;
  }
  if (!_HasCaptured) {
    WM_SetCapture(hWin, 1);
    _HasCaptured = Mode;
  }
}

/*********************************************************************
*
*       _ChangeWindowPosSize
*/
static void _ChangeWindowPosSize(FRAMEWIN_Handle hWin, int* px, int* py) {
  int dx;
  int dy;
  GUI_RECT Rect;

  dx = 0;
  dy = 0;
  WM_GetClientRectEx(hWin, &Rect);
  //
  // Calculate new size of window
  //
  if (_HasCaptured & RESIZE_X) {
    dx = (_HasCaptured & REPOS_X) ? (_CaptureX - *px) : (*px - _CaptureX);
  }
  if (_HasCaptured & RESIZE_Y) {
    dy = (_HasCaptured & REPOS_Y) ? (_CaptureY - *py) : (*py - _CaptureY);
  }
  //
  // Check the minimal size of window
  //
  if ((Rect.x1 + dx + 1) < MIN_SIZE_X) {
    dx = MIN_SIZE_X - (Rect.x1 + 1);
    *px = _CaptureX;
  }
  if ((Rect.y1 + dy + 1) < MIN_SIZE_Y) {
    dy = MIN_SIZE_Y - (Rect.y1 + 1);
    *py = _CaptureY;
  }
  //
  // Set new window position
  //
  if (_HasCaptured & REPOS_X) {
    WM_MoveWindow(hWin, -dx, 0);
  }
  if (_HasCaptured & REPOS_Y) {
    WM_MoveWindow(hWin, 0, -dy);
  }
  //
  // Set new window size
  //
  WM_ResizeWindow(hWin, dx, dy);
}

/*********************************************************************
*
*       _OnTouch
*/
static int _OnTouch(FRAMEWIN_Handle hWin, WM_MESSAGE* pMsg) {
  if (pMsg->Data.p) {  // Something happened in our area (pressed or released)
    GUI_PID_STATE* pState;
    pState = (GUI_PID_STATE*)pMsg->Data.p;
    if (pState->Pressed) {
      int x, y;
      x = pState->x;
      y = pState->y;
      if (WM_HasCaptured(hWin) == 0) {
        GUI_RECT Rect;
        int Mode = 0;
        int BorderSize = 4;
        WM_GetClientRectEx(hWin, &Rect);
        if (x > (Rect.x1 - BorderSize)) {
          Mode |= RESIZE_X;
        } else if (x < BorderSize) {
          Mode |= RESIZE_X | REPOS_X;
        }
        if (y > (Rect.y1 - BorderSize)) {
          Mode |= RESIZE_Y;
        } else if (y < BorderSize) {
          Mode |= RESIZE_Y | REPOS_Y;
        }
        if (Mode) {
          WM_SetFocus(hWin);
          WM_BringToTop(hWin);
          _SetCapture(hWin, x, y, Mode);
          return 1;
        }
      } else if (_HasCaptured) {
        _ChangeWindowPosSize(hWin, &x, &y);
        _SetCapture(hWin, x, y, 0);
        return 1;
      }
    }
  }
  _HasCaptured = 0;
  return 0;
}

/*********************************************************************
*
*       _CreateLButton
*/
static WM_HWIN _CreateLButton(const char* pText, int x, int w, int h, WM_HWIN hParent, int Id) {
  WM_HWIN hButton;
  GUI_RECT Rect;

  WM_GetClientRectEx(hParent, &Rect);
  hButton = BUTTON_CreateEx(x, Rect.y1 - h + 1, w, h, hParent, WM_CF_SHOW | WM_CF_ANCHOR_BOTTOM, 0, Id);
  BUTTON_SetText(hButton, pText);
  BUTTON_SetFont(hButton, &GUI_Font8_ASCII);
  return hButton;
}

/*********************************************************************
*
*       _CreateRButton
*/
static WM_HWIN _CreateRButton(const char* pText, int x, int w, int h, WM_HWIN hParent, int Id) {
  WM_HWIN hButton;
  GUI_RECT Rect;

  WM_GetClientRectEx(hParent, &Rect);
  hButton = BUTTON_CreateEx(Rect.x1 - x - w + 1, Rect.y1 - h + 1, w, h, hParent,
                            WM_CF_SHOW | WM_CF_ANCHOR_BOTTOM | WM_CF_ANCHOR_RIGHT, 0, Id);
  BUTTON_SetText(hButton, pText);
  BUTTON_SetFont(hButton, &GUI_Font8_ASCII);
  return hButton;
}

/*********************************************************************
*
*       _SetButtonState
*/
static void _SetButtonState(WM_HWIN hButton, int State) {
  if (State) {
    BUTTON_SetTextColor(hButton, 0, GUI_MAKE_COLOR(0x0040F0));
    BUTTON_SetTextColor(hButton, 1, GUI_MAKE_COLOR(0x0040F0));
  } else {
    BUTTON_SetTextColor(hButton, 0, GUI_BLACK);
    BUTTON_SetTextColor(hButton, 1, GUI_BLACK);
  }
}

/*********************************************************************
*
*       static code, callbacks
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbBkWin
*/
static void _cbBkWin(WM_MESSAGE* pMsg) {
  switch(pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_MAKE_COLOR(0x00A000));
    GUI_SetColor(GUI_WHITE);
    GUI_Clear();
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_DispStringHCenterAt("MULTIEDIT - Sample", 160, 5);
    GUI_SetFont(&GUI_Font8x16);
    GUI_DispStringAt(_acInfoText, 0, 30);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbMultiEdit
*/
static void _cbMultiEdit(WM_MESSAGE* pMsg) {
  if (pMsg->MsgId == WM_KEY) {
    if (((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt > 0) {
      int Key = ((WM_KEY_INFO*)(pMsg->Data.p))->Key;
      if (Key == GUI_KEY_INSERT) {
        WM_HWIN hWin;
        hWin = WM_GetDialogItem(WM_GetParent(pMsg->hWin), ID_OVERWRITE);
        _Overwrite ^= 1;
        _SetButtonState(hWin, _Overwrite);
      }
    }
  }
  if (_pcbMultiEdit) {
    (*_pcbMultiEdit)(pMsg);
  }
}

/*********************************************************************
*
*       _cbFrameWin
*/
static void _cbFrameWin(WM_MESSAGE* pMsg) {
  switch(pMsg->MsgId) {
  case WM_TOUCH:
    if (FRAMEWIN_IsMinimized(pMsg->hWin) == 0) {
      if (_OnTouch(pMsg->hWin, pMsg)) {
        return;
      }
    }
    break;
  case WM_DELETE:
    _hFrame      = 0;
    _hClient     = 0;
    _hMEdit      = 0;
    _hWrapButton = 0;
    break;
  }
  if (_pcbFrameWin) {
    (*_pcbFrameWin)(pMsg);
  }
}

/*********************************************************************
*
*       _cbFrameWinClient
*/
static void _cbFrameWinClient(WM_MESSAGE* pMsg) {
  switch(pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
      int Id = WM_GetId(pMsg->hWinSrc);
      if ((Id >= ID_NONEWRAP) && (Id <= ID_CHARWRAP)) {
        _SetButtonState(_hWrapButton, 0);
        if (Id == ID_NONEWRAP) {
          MULTIEDIT_SetWrapNone(_hMEdit);
        } else if (Id == ID_WORDWRAP) {
          MULTIEDIT_SetWrapWord(_hMEdit);
        } else if (Id == ID_CHARWRAP) {
          MULTIEDIT_SetWrapChar(_hMEdit);
        }
        _hWrapButton = pMsg->hWinSrc;
        _SetButtonState(_hWrapButton, 1);
      } else if (Id == ID_OVERWRITE) {
        _Overwrite ^= 1;
        MULTIEDIT_SetInsertMode(_hMEdit, 1 - _Overwrite);
        _SetButtonState(pMsg->hWinSrc, _Overwrite);
      } else if (Id == ID_READONLY) {
        _ReadOnly ^= 1;
        MULTIEDIT_SetReadOnly(_hMEdit, _ReadOnly);
        _SetButtonState(pMsg->hWinSrc, _ReadOnly);
      } else if (Id == ID_PASSWORD) {
        _Password ^= 1;
        MULTIEDIT_SetPasswordMode(_hMEdit, _Password);
        _SetButtonState(pMsg->hWinSrc, _Password);
      }
    }
    return;
  }
  if (_pcbFrameWinClient) {
    (*_pcbFrameWinClient)(pMsg);
  }
}

/*********************************************************************
*
*       _DemoMultiedit
*/
static void _DemoMultiedit(void) {
  GUI_RECT Rect;
  int WinFlags;

  _hFrame    = 1;
  _Overwrite = 0;
  _ReadOnly  = 0;
  _Password  = 0;
  /* Create framewin */
  _ChangeInfoText("Create framewin", SPEED);
  _hFrame = FRAMEWIN_CreateEx(50, 80, 220, 120, WM_HBKWIN, WM_CF_SHOW, 0, 0, "Notepad", 0);
  _hClient = WM_GetClientWindow(_hFrame);
  _pcbFrameWin       = WM_SetCallback(_hFrame,  _cbFrameWin);
  _pcbFrameWinClient = WM_SetCallback(_hClient, _cbFrameWinClient);
  /* Set framewin properties */
  FRAMEWIN_SetMoveable(_hFrame, 1);
  FRAMEWIN_SetActive(_hFrame, 1);
  FRAMEWIN_SetTextAlign(_hFrame, GUI_TA_HCENTER | GUI_TA_VCENTER);
  FRAMEWIN_SetFont(_hFrame, &GUI_Font8x12_ASCII);
  FRAMEWIN_SetTitleHeight(_hFrame, 16);
  /* Add framewin buttons */
  if (_ChangeInfoText("Add framewin buttons", SPEED)) return;
  FRAMEWIN_AddCloseButton(_hFrame, FRAMEWIN_BUTTON_LEFT,  0);
  FRAMEWIN_AddMaxButton(_hFrame, FRAMEWIN_BUTTON_RIGHT, 0);
  FRAMEWIN_AddMinButton(_hFrame, FRAMEWIN_BUTTON_RIGHT, 1);
  WM_InvalidateWindow(_hFrame);
  /* Create buttons */
  if (_ChangeInfoText("Add option buttons", SPEED)) return;
  _hWrapButton = _CreateLButton("None",   0, 36, 16, _hClient, ID_NONEWRAP);
  _CreateLButton("Word",  37, 36, 16, _hClient, ID_WORDWRAP);
  _CreateLButton("Char",  74, 36, 16, _hClient, ID_CHARWRAP);
  _CreateRButton("PSW",   61, 30, 16, _hClient, ID_PASSWORD);
  _CreateRButton("OVR",   31, 30, 16, _hClient, ID_OVERWRITE);
  _CreateRButton("R/O",    0, 30, 16, _hClient, ID_READONLY);
  _SetButtonState(_hWrapButton, 1);
  /* Create multiedit */
  if (_ChangeInfoText("using\nMULTIEDIT_CreateEx", SPEED)) return;
  WinFlags = WM_CF_SHOW | WM_CF_ANCHOR_RIGHT | WM_CF_ANCHOR_LEFT | WM_CF_ANCHOR_TOP | WM_CF_ANCHOR_BOTTOM;
  WM_GetClientRectEx(_hClient, &Rect);
  _hMEdit = MULTIEDIT_CreateEx(0, 0, 0, Rect.y1 - 16 + 1, _hClient, WinFlags, MULTIEDIT_CF_INSERT, 0, 0, "");
  _pcbMultiEdit = WM_SetCallback(_hMEdit,  _cbMultiEdit);
  MULTIEDIT_SetAutoScrollH(_hMEdit, 1);
  MULTIEDIT_SetAutoScrollV(_hMEdit, 1);
  WM_SetFocus(_hMEdit);
  if (_ChangeInfoText("using\nMULTIEDIT_SetText", SPEED)) return;
  MULTIEDIT_SetText(_hMEdit, "This sample demonstrates the use of a multiedit widget!");
  if (_ChangeInfoText("using\nMULTIEDIT_SetFont", SPEED)) return;
  MULTIEDIT_SetFont(_hMEdit, &GUI_Font16_1);
  if (_ChangeInfoText("using\nMULTIEDIT_SetTextColor", SPEED)) return;
  MULTIEDIT_SetTextColor(_hMEdit, 0, GUI_MAKE_COLOR(0xE00000));
  if (_ChangeInfoText("using\nMULTIEDIT_SetBkColor", SPEED)) return;
  MULTIEDIT_SetBkColor(_hMEdit, 0, GUI_MAKE_COLOR(0xD0FFFF));
  if (_ChangeInfoText("using\nMULTIEDIT_SetWrapWord", SPEED)) return;
  MULTIEDIT_SetWrapWord(_hMEdit);
  _SetButtonState(_hWrapButton, 0);
  _hWrapButton = WM_GetDialogItem(_hClient, ID_WORDWRAP);
  _SetButtonState(_hWrapButton, 1);
  if (_ChangeInfoText("using\nMULTIEDIT_SetHBorder", SPEED)) return;
  MULTIEDIT_SetHBorder(_hMEdit, 3);
  if (_ChangeInfoText("using\nMULTIEDIT_SetPrompt", SPEED)) return;
  MULTIEDIT_SetPrompt(_hMEdit, "Type: ");
  if (_ChangeInfoText("Play with multiedit...", SPEED)) return;
  while (_hFrame) {
    GUI_Delay(100);
  }
}

/*********************************************************************
*
*       public code
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
  #if GUI_SUPPORT_MEMDEV
    WM_SetCreateFlags(WM_CF_MEMDEV);
  #endif
  GUI_CURSOR_Show();
  WM_SetCallback(WM_HBKWIN, _cbBkWin);
  while(1) {
    _DemoMultiedit();
    *_acInfoText = 0;
    WM_InvalidateWindow(WM_HBKWIN);
    GUI_Delay(SPEED);
  }
}

/*************************** End of file ****************************/
