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
File        : WIDGET_NumPad.c
Purpose     : Shows how to use a numpad as input device on a touch screen
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
---------------------------END-OF-HEADER------------------------------
*/

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
//
// Bitmap data for arrow keys
//
static GUI_CONST_STORAGE GUI_COLOR _aColorsArrow[] = {
  GUI_MAKE_COLOR(0xFFFFFF), GUI_MAKE_COLOR(0x000000)
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalArrow = {
  2,	/* number of entries */
  1, 	/* No transparency */
  &_aColorsArrow[0]
};

static GUI_CONST_STORAGE unsigned char _acArrowRight[] = {
  ____XX__, ________,
  ____XXXX, ________,
  XXXXXXXX, XX______,
  ____XXXX, ________,
  ____XX__, ________
};

static GUI_CONST_STORAGE unsigned char _acArrowLeft[] = {
  ____XX__, ________,
  __XXXX__, ________,
  XXXXXXXX, XX______,
  __XXXX__, ________,
  ____XX__, ________
};

static GUI_CONST_STORAGE GUI_BITMAP _bmArrowRight = {
  10,            /* XSize */
  5,             /* YSize */
  2,             /* BytesPerLine */
  1,             /* BitsPerPixel */
  _acArrowRight, /* Pointer to picture data (indices) */
  &_PalArrow     /* Pointer to palette */
};

static GUI_CONST_STORAGE GUI_BITMAP _bmArrowLeft = {
  10,            /* XSize */
  5,             /* YSize */
  2,             /* BytesPerLine */
  1,             /* BitsPerPixel */
  _acArrowLeft,  /* Pointer to picture data (indices) */
  &_PalArrow     /* Pointer to palette */
};
//
// Array of keys
//
static int _aKey[] = {GUI_KEY_DELETE, GUI_KEY_TAB, GUI_KEY_LEFT, GUI_KEY_RIGHT};

//
// Dialog resource of numpad
//
static const GUI_WIDGET_CREATE_INFO _aDialogNumPad[] = {
//
//  Function                 Text      Id                 Px     Py    Dx    Dy
//
  { WINDOW_CreateIndirect,   0,        0,                  305,  50,   155,  180},
  { BUTTON_CreateIndirect,   "7",      GUI_ID_USER +  7,   5,    5,    45,   30},
  { BUTTON_CreateIndirect,   "8",      GUI_ID_USER +  8,   55,   5,    45,   30},
  { BUTTON_CreateIndirect,   "9",      GUI_ID_USER +  9,   105,  5,    45,   30},
  { BUTTON_CreateIndirect,   "4",      GUI_ID_USER +  4,   5,    40,   45,   30},
  { BUTTON_CreateIndirect,   "5",      GUI_ID_USER +  5,   55,   40,   45,   30},
  { BUTTON_CreateIndirect,   "6",      GUI_ID_USER +  6,   105,  40,   45,   30},
  { BUTTON_CreateIndirect,   "1",      GUI_ID_USER +  1,   5,    75,   45,   30},
  { BUTTON_CreateIndirect,   "2",      GUI_ID_USER +  2,   55,   75,   45,   30},
  { BUTTON_CreateIndirect,   "3",      GUI_ID_USER +  3,   105,  75,   45,   30},
  { BUTTON_CreateIndirect,   "0",      GUI_ID_USER +  0,   5,    110,  45,   30},
  { BUTTON_CreateIndirect,   ".",      GUI_ID_USER + 10,   55,   110,  45,   30},
  { BUTTON_CreateIndirect,   "Del",    GUI_ID_USER + 11,   105,  110,  45,   30},
  { BUTTON_CreateIndirect,   "Tab",    GUI_ID_USER + 12,   5,    145,  45,   30},
  { BUTTON_CreateIndirect,   0,        GUI_ID_USER + 13,   55,   145,  45,   30},
  { BUTTON_CreateIndirect,   0,        GUI_ID_USER + 14,   105,  145,  45,   30},
};

//
// Dialog resource of user dialog
//
static const GUI_WIDGET_CREATE_INFO _aDialogUser[] = {
//
//  Function                 Text      Id                 Px   Py   Dx   Dy
//
  { FRAMEWIN_CreateIndirect, "Dialog", 0,                 40,  90, 140, 115, FRAMEWIN_CF_MOVEABLE},
  { EDIT_CreateIndirect,     0,        GUI_ID_EDIT0,      10,  10, 110,  20, 0, 12},
  { EDIT_CreateIndirect,     0,        GUI_ID_EDIT1,      10,  40, 110,  20, 0, 12},
  { BUTTON_CreateIndirect,   "Ok",     GUI_ID_OK,         10,  70,  50,  20 },
  { BUTTON_CreateIndirect,   "Cancel", GUI_ID_CANCEL,     70,  70,  50,  20 },
};

//
// Title of sample
//
static char _aTitle[] = {"WIDGET_NumPad"};

//
// Explanation of sample
//
static char * _apExplain[] = {
  "This sample shows how to use a numpad as input",
  "device. This can be useful if no keyboard",
  "is available and the user should edit numeric",
  "values or text on a touch screen.",
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbDialogNumPad
*
* Function description
*   Callback function of the numpad.
*/
static void _cbDialogNumPad(WM_MESSAGE * pMsg) {
  GUI_RECT r;
  unsigned i;
  int      NCode;
  unsigned Id;
  int      Pressed;
  WM_HWIN  hDlg;
  WM_HWIN  hItem;

  Pressed = 0;
  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    WM_GetClientRect(&r);
    GUI_SetColor(GUI_MAKE_COLOR(0x000000));
    GUI_DrawRect(r.x0, r.y0, r.x1, r.y1);          /* Draw rectangle around it */
    /* Draw the bright sides */
    GUI_SetColor(GUI_MAKE_COLOR(0xffffff));
    GUI_DrawHLine(r.y0 + 1, r.x0 + 1, r.x1 - 2);   /* Draw top line */
    GUI_DrawVLine(r.x0 + 1, r.y0 + 1, r.y1 - 2);
    /* Draw the dark sides */
    GUI_SetColor(GUI_MAKE_COLOR(0x555555));
    GUI_DrawHLine(r.y1-1, r.x0 + 1, r.x1 - 1);
    GUI_DrawVLine(r.x1-1, r.y0 + 1, r.y1 - 2);
    break;
  case WM_INIT_DIALOG:
    for (i = 0; i < GUI_COUNTOF(_aDialogNumPad) - 1; i++) {
      hItem = WM_GetDialogItem(hDlg, GUI_ID_USER + i);
      BUTTON_SetFocussable(hItem, 0);                       /* Set all buttons non focussable */
      switch (i) {
      case 13:
        BUTTON_SetBitmapEx(hItem, 0, &_bmArrowLeft, 17, 15);  /* Set bitmap for arrow left button (unpressed) */
        BUTTON_SetBitmapEx(hItem, 1, &_bmArrowLeft, 17, 15);  /* Set bitmap for arrow left button (pressed) */
        break;
      case 14:
        BUTTON_SetBitmapEx(hItem, 0, &_bmArrowRight, 17, 15); /* Set bitmap for arrow right button (unpressed) */
        BUTTON_SetBitmapEx(hItem, 1, &_bmArrowRight, 17, 15); /* Set bitmap for arrow right button (pressed) */
        break;
      }
    }
    WM_GetDialogItem(hDlg, GUI_ID_USER + 12);
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
    NCode = pMsg->Data.v;                 /* Notification code */
    switch (NCode) {
    case WM_NOTIFICATION_CLICKED:
      Pressed = 1;
    case WM_NOTIFICATION_RELEASED:
      if ((Id >= GUI_ID_USER) && (Id <= (GUI_ID_USER + GUI_COUNTOF(_aDialogNumPad) - 1))) {
        int Key;
        if (Id < GUI_ID_USER + 11) {
          char acBuffer[10];
          BUTTON_GetText(pMsg->hWinSrc, acBuffer, sizeof(acBuffer)); /* Get the text of the button */
          Key = acBuffer[0];
        } else {
          Key = _aKey[Id - GUI_ID_USER - 11];                        /* Get the text from the array */
        }
        GUI_SendKeyMsg(Key, Pressed);                                /* Send a key message to the focussed window */
      }
      break;
    }
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbDialogUser
*
* Purpose:
*   Callback function of the user dialog.
*/
static void _cbDialogUser(WM_MESSAGE * pMsg) {
  int      i;
  int      NCode;
  int      Id;
  WM_HWIN  hDlg;
  WM_HWIN  hItem;

  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    for (i = 0; i < 2; i++) {
      hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0 + i);  /* Get the handle of the edit widget */
      EDIT_SetText(hItem, "12345678");                   /* Set text */
    }
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
    NCode = pMsg->Data.v;                 /* Notification code */
    switch (NCode) {
      case WM_NOTIFICATION_RELEASED:      /* React only if released */
        if (Id == GUI_ID_OK) {            /* OK Button */
          GUI_EndDialog(hDlg, 0);
        }
        if (Id == GUI_ID_CANCEL) {        /* Cancel Button */
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
    GUI_DispStringHCenterAt(_aTitle, 160, 5);
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
*       Exported code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  WM_HWIN hNumPad;

  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available.");
    return;
  }
  WM_SetCallback(WM_HBKWIN, _cbDesktop);
  hNumPad = GUI_CreateDialogBox(_aDialogNumPad,
                                GUI_COUNTOF(_aDialogNumPad),
                                _cbDialogNumPad, WM_HBKWIN, 0, 0); /* Create the numpad dialog */
  WM_SetStayOnTop(hNumPad, 1);
  while (1) {
    GUI_ExecDialogBox(_aDialogUser,
                      GUI_COUNTOF(_aDialogUser),
                      _cbDialogUser, WM_HBKWIN, 0, 0);             /* Execute the user dialog */
    GUI_Delay(1000);
  }
}

/*************************** End of file ****************************/

