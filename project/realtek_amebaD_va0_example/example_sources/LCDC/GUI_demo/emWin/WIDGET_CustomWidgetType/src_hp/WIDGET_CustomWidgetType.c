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
File        : WIDGET_CustomWidgetType.c
Purpose     : Guide on how to create a custom type of widget.
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
---------------------------END-OF-HEADER------------------------------
*/
#include <string.h>        // Definition of NULL
#include <stdlib.h>        // malloc() and free()
#include "GUI.h"
#include "WM.h"
#include "BUTTON.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
/*********************************************************************
*
*       Color indices
*/
#define MYWIDGET_CI_UNPRESSED 0
#define MYWIDGET_CI_PRESSED   1
#define MYWIDGET_CI_DISABLED  2

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*********************************************************************
*
*       Custom widget data (global)
*
**********************************************************************
*/
/*********************************************************************
*
*       Typedef
*/
typedef WM_HMEM MYWIDGET_Handle;

/*********************************************************************
*
*       MYWIDGET_Obj
*/
typedef struct {
  U8           Pressed;
  GUI_COLOR    aBkColor[3];
  GUI_COLOR    aTextColor[3];
  GUI_COLOR    FocusColor;
  const char * pText;
  int          NumExtraBytes;
} MYWIDGET_Obj;

/*********************************************************************
*
*       MYWIDGET_Default
*/
const MYWIDGET_Obj MYWIDGET_Default = {
    0,
  { GUI_DARKBLUE, GUI_LIGHTBLUE, GUI_GRAY },
  { GUI_WHITE,    GUI_DARKGRAY,  GUI_LIGHTGRAY },
    GUI_ORANGE,
    NULL,
    0
};

/*********************************************************************
*
*       Custom widget function prototypes (global)
*
**********************************************************************
*/
void            MYWIDGET_Callback   (WM_MESSAGE * pMsg);
int             MYWIDGET_GetUserData(MYWIDGET_Handle hWin, void * pDest, int SizeOfBuffer);
int             MYWIDGET_SetUserData(MYWIDGET_Handle hWin, void * pSrc,  int SizeOfBuffer);
MYWIDGET_Handle MYWIDGET_Create     (int x0, int y0, int xSize, int ySize, WM_HWIN hWinParent, U32 Style, const char * pText, WM_CALLBACK * pfCallback, int NumExtraBytes);

/*********************************************************************
*
*       Custom widget functions (global)
*
**********************************************************************
*/
/*********************************************************************
*
*       MYWIDGET_Callback
*/
void MYWIDGET_Callback(WM_MESSAGE * pMsg) {
  MYWIDGET_Handle   hWin;
  GUI_PID_STATE   * pState;
  MYWIDGET_Obj      MyWidget;
  GUI_RECT          WinRect;
  int               ColorIndex;
  U8                Pressed;

  hWin = pMsg->hWin;
  WM_GetWindowRectEx(hWin, &WinRect);
  GUI_MoveRect(&WinRect, -WinRect.x0, -WinRect.y0);
  WM_GetUserData(hWin, &MyWidget, sizeof(MYWIDGET_Obj));
  switch (pMsg->MsgId) {
  case WM_PAINT:
    if (WM_IsEnabled(hWin)) {
      if (MyWidget.Pressed) {
        ColorIndex = MYWIDGET_CI_PRESSED;
      } else {
        ColorIndex = MYWIDGET_CI_UNPRESSED;
      }
    } else {
      ColorIndex = MYWIDGET_CI_DISABLED;
    }
    GUI_SetColor(MyWidget.aBkColor[ColorIndex]);
    GUI_FillRectEx(&WinRect);
    if (WM_HasFocus(hWin)) {
      GUI_SetColor(MyWidget.FocusColor);
      GUI_DrawRectEx(&WinRect);
    }
    GUI_SetColor(MyWidget.aTextColor[ColorIndex]);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_DispStringInRect(MyWidget.pText, &WinRect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    break;
  case WM_TOUCH:
    pState = (GUI_PID_STATE *)pMsg->Data.p;
    if (pState) {
      Pressed = pState->Pressed;
    } else {
      Pressed = 0;
    }
    if (MyWidget.Pressed != Pressed) {
      MyWidget.Pressed = Pressed;
      WM_SetUserData(hWin, &MyWidget, sizeof(MYWIDGET_Obj));
      if (Pressed) {
        WM_SetFocus(hWin);
      }
      WM_InvalidateWindow(hWin);
    }
    break;
  case WM_SET_FOCUS:
    if (pMsg->Data.v) {
      pMsg->Data.v = 0;
    } 
    WM_InvalidateWindow(hWin);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       MYWIDGET_GetUserData
*/
int MYWIDGET_GetUserData(MYWIDGET_Handle hWin, void * pDest, int SizeOfBuffer) {
  MYWIDGET_Obj   MyWidget;
  int            NumBytes;
  U8           * pExtraBytes;

  if (SizeOfBuffer <= 0) {
    return 0;
  }
  WM_GetUserData(hWin, &MyWidget, sizeof(MYWIDGET_Obj));
  pExtraBytes = (U8 *)malloc(sizeof(MYWIDGET_Obj) + MyWidget.NumExtraBytes);
  if (pExtraBytes) {
    WM_GetUserData(hWin, pExtraBytes, sizeof(MYWIDGET_Obj) + MyWidget.NumExtraBytes);
    if (SizeOfBuffer >= MyWidget.NumExtraBytes) {
      NumBytes = MyWidget.NumExtraBytes;
    } else {
      NumBytes = SizeOfBuffer;
    }
    GUI_MEMCPY(pDest, pExtraBytes + sizeof(MYWIDGET_Obj), NumBytes);
    free(pExtraBytes);
    return NumBytes;
  }
  return 0;
}

/*********************************************************************
*
*       MYWIDGET_SetUserData
*/
int MYWIDGET_SetUserData(MYWIDGET_Handle hWin, void * pSrc, int SizeOfBuffer) {
  MYWIDGET_Obj   MyWidget;
  int            NumBytes;
  U8           * pExtraBytes;

  if (SizeOfBuffer <= 0) {
    return 1;
  }
  WM_GetUserData(hWin, &MyWidget, sizeof(MYWIDGET_Obj));
  pExtraBytes = (U8 *)malloc(sizeof(MYWIDGET_Obj) + MyWidget.NumExtraBytes);
  if (pExtraBytes) {
    WM_GetUserData(hWin, pExtraBytes, sizeof(MYWIDGET_Obj) + MyWidget.NumExtraBytes);
    if (SizeOfBuffer >= MyWidget.NumExtraBytes) {
      NumBytes = MyWidget.NumExtraBytes;
    } else {
      NumBytes = SizeOfBuffer;
    }
    GUI_MEMCPY(pExtraBytes + sizeof(MYWIDGET_Obj), pSrc, NumBytes);
    WM_SetUserData(hWin, pExtraBytes, sizeof(MYWIDGET_Obj) + MyWidget.NumExtraBytes);
    free(pExtraBytes);
    return 0;
  }
  return 1;
}

/*********************************************************************
*
*       MYWIDGET_Create
*/
MYWIDGET_Handle MYWIDGET_Create(int x0, int y0, int xSize, int ySize, WM_HWIN hWinParent, U32 Style, const char * pText, WM_CALLBACK * pfCallback, int NumExtraBytes) {
  MYWIDGET_Handle   hWin;
  MYWIDGET_Obj      MyWidget;
  WM_CALLBACK     * pfUsed;

  if (pfCallback) {
    pfUsed = pfCallback;
  } else {
    pfUsed = MYWIDGET_Callback;
  }
  MyWidget               = MYWIDGET_Default;
  MyWidget.NumExtraBytes = NumExtraBytes;
  if (pText) {
    MyWidget.pText = pText;
  }
  hWin = WM_CreateWindowAsChild(x0, y0, xSize, ySize, hWinParent, Style, pfUsed, sizeof(MYWIDGET_Obj) + NumExtraBytes);
  WM_SetUserData(hWin, &MyWidget, sizeof(MYWIDGET_Obj));
  return hWin;
}

/*********************************************************************
*
*       End-user application
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbMyWidget
*/
static void _cbMyWidget(WM_MESSAGE * pMsg) {
  GUI_RECT WinRect;
  char     acText[20] = { 0 };

  switch (pMsg->MsgId) {
  case WM_PAINT:
    MYWIDGET_Callback(pMsg);
    MYWIDGET_GetUserData(pMsg->hWin, acText, sizeof(acText));
    GUI_SetColor(GUI_WHITE);
    GUI_SetTextMode(GUI_TM_TRANS);
    WM_GetWindowRectEx(pMsg->hWin, &WinRect);
    GUI_MoveRect(&WinRect, -WinRect.x0, -WinRect.y0);
    GUI_DispStringInRect(acText, &WinRect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    break;
  default:
    MYWIDGET_Callback(pMsg);
  }
}

/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  MYWIDGET_Handle hMyWidget;
  char            acExtraBytes[] = "Extrabytes";

  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  hMyWidget = MYWIDGET_Create(10, 10, 100, 50, WM_HBKWIN, WM_CF_SHOW, NULL, _cbMyWidget, strlen(acExtraBytes));
  MYWIDGET_SetUserData(hMyWidget, acExtraBytes, strlen(acExtraBytes));
  BUTTON_Create(10, 100, 100, 50, 0, WM_CF_SHOW);
  while (1) {
    GUI_Delay(100);
  }
}

/*************************** End of file ****************************/
