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
File        : WIDGET_Effect.c
Purpose     : Example demonstrating the use of a widget effects
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/
#include <stddef.h>
#include <string.h>
#include "GUI.h"
#include "DIALOG.h"
#include "PROGBAR.h"
#include "LISTVIEW.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define NUM_WIDGETS GUI_COUNTOF(_aID)

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 30)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

//
// Dialog resource of main dialog box
//
static const GUI_WIDGET_CREATE_INFO _aDlgWidgets[] = {
  { WINDOW_CreateIndirect,    "",             0,                   0,   0, 499, 239, 0                         },
  { TEXT_CreateIndirect,      "Progress bar", GUI_ID_TEXT0,       10,   5, 100,  15, TEXT_CF_HCENTER           },
  { PROGBAR_CreateIndirect,   NULL,           GUI_ID_PROGBAR0,    10,  20, 100,  20                            },
  { TEXT_CreateIndirect,      "Button",       GUI_ID_TEXT0,       10,  50, 100,  15, TEXT_CF_HCENTER           },
  { BUTTON_CreateIndirect,    "Button",       GUI_ID_BUTTON0,     10,  65, 100,  20                            },
  { TEXT_CreateIndirect,      "Dropdown",     GUI_ID_TEXT0,       10,  95, 100,  15, TEXT_CF_HCENTER           },
  { DROPDOWN_CreateIndirect,  NULL,           GUI_ID_DROPDOWN0,   10, 110, 100,  65, DROPDOWN_CF_AUTOSCROLLBAR },
  { TEXT_CreateIndirect,      "Edit",         GUI_ID_TEXT0,      120,   5, 100,  15, TEXT_CF_HCENTER           },
  { EDIT_CreateIndirect,      NULL,           GUI_ID_EDIT0,      120,  20, 100,  20                            },
  { TEXT_CreateIndirect,      "Listbox",      GUI_ID_TEXT0,      120,  50, 100,  15, TEXT_CF_HCENTER           },
  { LISTBOX_CreateIndirect,   "",             GUI_ID_LISTBOX0,   120,  65, 100, 125, 0, 0                      },
  { TEXT_CreateIndirect,      "Listview",     GUI_ID_TEXT0,      230,   5, 100,  15, TEXT_CF_HCENTER           },
  { LISTVIEW_CreateIndirect,  NULL,           GUI_ID_LISTVIEW0,  230,  20, 100, 100, 0                         },
  { TEXT_CreateIndirect,      "Multiedit",    GUI_ID_TEXT0,      230, 130, 100,  15, TEXT_CF_HCENTER           },
  { MULTIEDIT_CreateIndirect, "",             GUI_ID_MULTIEDIT0, 230, 145, 100,  45, 0, 0                      },
  { TEXT_CreateIndirect,      "Scrollbars",   GUI_ID_TEXT0,      340,   5,  70,  15, TEXT_CF_HCENTER           },
  { SCROLLBAR_CreateIndirect, NULL,           GUI_ID_SCROLLBAR0, 340, 175,  70,  15, 0                         },
  { SCROLLBAR_CreateIndirect, NULL,           GUI_ID_SCROLLBAR1, 340,  20,  20, 140, SCROLLBAR_CF_VERTICAL     },
  { SCROLLBAR_CreateIndirect, NULL,           GUI_ID_SCROLLBAR2, 370,  20,  40, 140, SCROLLBAR_CF_VERTICAL     },
  { TEXT_CreateIndirect,      "Sliders",      GUI_ID_TEXT0,      420,   5,  70,  15, TEXT_CF_HCENTER           },
  { SLIDER_CreateIndirect,    NULL,           GUI_ID_SLIDER0,    420, 175,  70,  15, 0                         },
  { SLIDER_CreateIndirect,    NULL,           GUI_ID_SLIDER1,    420,  20,  20, 140, SLIDER_CF_VERTICAL        },
  { SLIDER_CreateIndirect,    NULL,           GUI_ID_SLIDER2,    450,  20,  40, 140, SLIDER_CF_VERTICAL        },
};

//
// Dialog resource of options dialog box
//
static const GUI_WIDGET_CREATE_INFO _aDlgOptions[] = {
  { FRAMEWIN_CreateIndirect, "Effect", 0,             10, 30,  65, 95, 0                    },
  { CHECKBOX_CreateIndirect, NULL,     GUI_ID_CHECK0,  2,  2,   0,  0                       },
  { RADIO_CreateIndirect,    NULL,     GUI_ID_RADIO0,  0, 20,   0,  0, 0,            0x1003 },
  { TEXT_CreateIndirect,     "Auto",   GUI_ID_TEXT0,  22,  4, 100, 15, TEXT_CF_LEFT         },
  { TEXT_CreateIndirect,     "3D",     GUI_ID_TEXT0,  17, 22, 100, 15, TEXT_CF_LEFT         },
  { TEXT_CreateIndirect,     "Simple", GUI_ID_TEXT0,  17, 38, 100, 15, TEXT_CF_LEFT         },
  { TEXT_CreateIndirect,     "None",   GUI_ID_TEXT0,  17, 54, 100, 15, TEXT_CF_LEFT         },
};

//
// Array of widget ID's
//
static int _aID[] = {
  GUI_ID_BUTTON0,    GUI_ID_EDIT0,     GUI_ID_LISTBOX0,   GUI_ID_PROGBAR0,   GUI_ID_LISTVIEW0,
  GUI_ID_MULTIEDIT0, GUI_ID_DROPDOWN0, GUI_ID_SCROLLBAR0, GUI_ID_SCROLLBAR1, GUI_ID_SCROLLBAR2,
  GUI_ID_SLIDER0,    GUI_ID_SLIDER1,   GUI_ID_SLIDER2
};

//
// Array of widget handles
//
static WM_HWIN _ahWin[GUI_COUNTOF(_aID)];

//
// Makes it easier to access the array _ahWin
//
enum {
  BUTTON0,    EDIT0,     LISTBOX0,   PROGBAR0,   LISTVIEW0,
  MULTIEDIT0, DROPDOWN0, SCROLLBAR0, SCROLLBAR1, SCROLLBAR2,
  SLIDER0,    SLIDER1,   SLIDER2
};

//
// Array of available effects
//
const WIDGET_EFFECT * _apEffect[] = {
  &WIDGET_Effect_3D,     
  &WIDGET_Effect_Simple, 
  &WIDGET_Effect_None
};

//
// Array of strings used to label the frame window
//
const char * _asEffect[] = {
  "Widget effect: 3D",
  "Widget effect: Simple", 
  "Widget effect: None"
};

static WM_HWIN _hDlg;
static WM_HWIN _hFrameWin;
static int     _AutoMode = 1;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _SetWidgetEffect
*
* Function description
*   Sets the effect for the given widget and its child windows
*/
static void _SetWidgetEffect(WM_HWIN hWin, const WIDGET_EFFECT * pEffect) {
  WM_HWIN hChild;

  if (hWin) {
    WIDGET_SetEffect(hWin, pEffect);
    //
    // Iterate over the child windows
    //
    hChild = WM_GetFirstChild(hWin);
    while (hChild) {
      WIDGET_SetEffect(hChild, pEffect);
      hChild = WM_GetNextSibling(hChild);
    }
  }
}

/*********************************************************************
*
*       _SetEffect
*/
static void _SetEffect(int Index) {
  const WIDGET_EFFECT * pEffect;
  U32                   i;

  pEffect = _apEffect[Index];
  WIDGET_SetDefaultEffect(pEffect);
  FRAMEWIN_SetText(_hFrameWin, _asEffect[Index]);
  //
  // Iterate over all dialog widgets
  //
  for (i = 0; i < NUM_WIDGETS; i++) {
    _SetWidgetEffect(_ahWin[i], _apEffect[Index]);
  }
}

/*********************************************************************
*
*       _cbBkWindow
*/
static void _cbBkWindow(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_BLUE);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_DispStringHCenterAt("WIDGET_Effect - Sample", 160, 5);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbCallbackWidgets
*
* Function description
*   Initializes the widgets of the main dialog box
*/
static void _cbCallbackWidgets(WM_MESSAGE * pMsg) {
  WM_HWIN hDlg;
  char    acBuffer[10];
  int     Len;
  U32     i;
  U32     j;

  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Get handles of widgets
    //
    for (i = 0; i < NUM_WIDGETS; i++) {
      _ahWin[i] = WM_GetDialogItem(hDlg, _aID[i]);
    }
    //
    // Init dropdown widget
    //
    for (i = 0; i < 8; i++) {
      strcpy(acBuffer, "Item x");
      Len = strlen(acBuffer);
      acBuffer[Len - 1] = '1' + i;
      DROPDOWN_AddString(_ahWin[DROPDOWN0], acBuffer);
    }
    //
    // Init edit widget
    //
    EDIT_SetText(_ahWin[EDIT0], "Edit");
    //
    // Init listbox widget
    //
    LISTBOX_SetAutoScrollV(_ahWin[LISTBOX0], 1);
    for (i = 0; i < 4; i++) {
      strcpy(acBuffer, "Item x");
      Len = strlen(acBuffer);
      acBuffer[Len - 1] = '1' + i;
      LISTBOX_AddString(_ahWin[LISTBOX0], acBuffer);
    }
    //
    // Init listview widget
    //
    for (i = 0; i < 2; i++) {
      strcpy(acBuffer, "Col. x");
      Len = strlen(acBuffer);
      acBuffer[Len - 1] = '1' + i;
      LISTVIEW_AddColumn(_ahWin[LISTVIEW0], 40, acBuffer, GUI_TA_CENTER);
    }
    for (i = 0; i < 9; i++) {
      LISTVIEW_AddRow(_ahWin[LISTVIEW0], NULL);
      for (j = 0; j < LISTVIEW_GetNumColumns(_ahWin[LISTVIEW0]); j++) {
        strcpy(acBuffer, "Rx / Cx");
        acBuffer[1] = '1' + i;
        acBuffer[6] = '1' + j;
        LISTVIEW_SetItemText(_ahWin[LISTVIEW0], j, i, acBuffer);
      }
    }
    LISTVIEW_SetGridVis(_ahWin[LISTVIEW0], 1);
    SCROLLBAR_CreateAttached(_ahWin[LISTVIEW0], SCROLLBAR_CF_VERTICAL);
    //
    // Init multiedit widget
    //
    MULTIEDIT_SetText(_ahWin[MULTIEDIT0], "This text could be modified by the MULTIEDIT widget");
    MULTIEDIT_SetWrapWord(_ahWin[MULTIEDIT0]);
    MULTIEDIT_SetAutoScrollV(_ahWin[MULTIEDIT0], 1);
    //
    // Init progbar widget
    //
    WIDGET_SetEffect(_ahWin[PROGBAR0], &WIDGET_Effect_3D);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbCallbackFramewin
*
* Function description
*   Handles the scroll messages of the scrollbar
*/
static void _cbCallbackFramewin(WM_MESSAGE * pMsg) {
  WM_SCROLL_STATE ScrollState;
  WM_HWIN         hDlg;
  int             xPos;
  int             yPos;

  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    if (pMsg->Data.v == WM_NOTIFICATION_VALUE_CHANGED) {
      if (pMsg->hWinSrc == WM_GetScrollbarH(hDlg)) {
        WM_GetScrollState(pMsg->hWinSrc, &ScrollState);
        xPos = WM_GetWindowOrgX(WM_GetParent(_hDlg)) - ScrollState.v;
        yPos = WM_GetWindowOrgY(_hDlg);
        WM_MoveTo(_hDlg, xPos, yPos);
      }
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbCallbackOptions
*
* Function description
*   Callback of the options dialog box, sets the widget effects
*/
static void _cbCallbackOptions(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  WM_HWIN hDlg;

  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK0);
    CHECKBOX_Check(hItem);
    break;
  case WM_NOTIFY_PARENT:
    if (pMsg->Data.v == WM_NOTIFICATION_VALUE_CHANGED) {
      hItem = WM_GetDialogItem(hDlg, GUI_ID_RADIO0);
      if (pMsg->hWinSrc == hItem) {
        _SetEffect(RADIO_GetValue(hItem));
      }
    } else if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
      hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK0);
      if (pMsg->hWinSrc == hItem) {
        _AutoMode = CHECKBOX_IsChecked(hItem);
      }
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
  WM_SCROLL_STATE ScrollState;
  GUI_RECT RectClient;
  GUI_RECT RectDlg;
  WM_HWIN  hDlgOptions;
  WM_HWIN  hScrollbar;
  WM_HWIN  hScroll;
  WM_HWIN  hWin;
  U32      IndexEffect;
  int      ButtonState;
  int      DropdownState;
  int      ProgbarValue;
  int      ProgbarInc;
  int      SliderValue;
  int      SliderInc;
  int      ScrollbarValue;
  int      ScrollbarInc;
  int      Index;
  int      Cnt;
  int      Inc;
  int      Vz;

  IndexEffect    = 0;
  ButtonState    = 0;
  DropdownState  = 0;
  ProgbarValue   = 0;
  ProgbarInc     = 1;
  SliderValue    = 0;
  SliderInc      = 1;
  ScrollbarValue = 0;
  ScrollbarInc   = 1;
  Cnt            = 0;
  Vz             = 1;

  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  GUI_CURSOR_Show();
  WM_SetCallback(WM_HBKWIN, _cbBkWindow);
  WM_SetCreateFlags(WM_CF_MEMDEV);  // Use memory devices on all windows to avoid flicker
  WM_EnableMemdev(WM_HBKWIN);       // Enable use of memory devices for desktop windows
  //
  // Create framewindow and set its properties
  //
  _hFrameWin = FRAMEWIN_CreateEx(0, 0, 320, 240, 0, WM_CF_SHOW, 0, 0, "", _cbCallbackFramewin);
  FRAMEWIN_SetMoveable(_hFrameWin, 1);
  FRAMEWIN_SetText(_hFrameWin, _asEffect[0]);
  FRAMEWIN_SetFont(_hFrameWin, &GUI_Font13B_ASCII);
  //
  // Create main dialog window as child from framewindows client window
  //
  _hDlg = GUI_CreateDialogBox(_aDlgWidgets, GUI_COUNTOF(_aDlgWidgets), _cbCallbackWidgets, WM_GetClientWindow(_hFrameWin), 0, 0);
  //
  // Attach scrollbar to framewindows client window and set its properties
  //
  hScrollbar = SCROLLBAR_CreateAttached(WM_GetClientWindow(_hFrameWin), 0);
  WM_GetWindowRectEx(_hDlg, &RectDlg);
  WM_GetClientRectEx(WM_GetClientWindow(_hFrameWin), &RectClient);
  SCROLLBAR_SetNumItems(hScrollbar, RectDlg.x1);
  SCROLLBAR_SetPageSize(hScrollbar, RectClient.x1);
  //
  // Create options dialog with 'stay on top' and 'moveable' attribute
  //
  hDlgOptions = GUI_CreateDialogBox(_aDlgOptions, GUI_COUNTOF(_aDlgOptions), _cbCallbackOptions, WM_HBKWIN, 0, 0);
  FRAMEWIN_SetMoveable(hDlgOptions, 1);
  WM_SetStayOnTop(hDlgOptions, 1);
  //
  // Main loop for modifying the widgets
  //
  while (1) {
    if (_AutoMode) {
      Cnt++;
      //
      // Modify progbar
      //
      if ((Cnt % 2) == 0) {
        ProgbarValue += ProgbarInc;
        if ((ProgbarValue == 110) || (ProgbarValue == -10)) {
          ProgbarInc *= -1;
        }
        PROGBAR_SetValue(_ahWin[PROGBAR0], ProgbarValue);
      }
      //
      // Modify slider
      //
      if ((Cnt % 2) == 0) {
        SliderValue += SliderInc;
        if ((SliderValue == 100) || (SliderValue == 0)) {
          SliderInc *= -1;
        }
        SLIDER_SetValue(_ahWin[SLIDER0], SliderValue);
        SLIDER_SetValue(_ahWin[SLIDER1], SliderValue);
        SLIDER_SetValue(_ahWin[SLIDER2], SliderValue);
      }
      //
      // Modify scrollbar
      //
      if ((Cnt % 3) == 0) {
        ScrollbarValue += ScrollbarInc;
        if ((ScrollbarValue == 90) || (ScrollbarValue == 0)) {
          ScrollbarInc *= -1;
        }
        SCROLLBAR_SetValue(_ahWin[SCROLLBAR0], ScrollbarValue);
        SCROLLBAR_SetValue(_ahWin[SCROLLBAR1], ScrollbarValue);
        SCROLLBAR_SetValue(_ahWin[SCROLLBAR2], ScrollbarValue);
      }
      //
      // Modify dropdown
      //
      if ((Cnt % 120) == 0) {
        DropdownState ^= 1;
        if (DropdownState) {
          DROPDOWN_Expand(_ahWin[DROPDOWN0]);
        } else {
          DROPDOWN_Collapse(_ahWin[DROPDOWN0]);
        }
      }
      //
      // Modify button
      //
      if ((Cnt % 40) == 0) {
        ButtonState ^= 1;
        BUTTON_SetPressed(_ahWin[BUTTON0], ButtonState);
      }
      //
      // Move window
      //
      if ((Cnt % 1200) == 0) {
        hScroll = WM_GetScrollbarH(WM_GetClientWindow(_hFrameWin));
        WM_GetScrollState(hScroll, &ScrollState);
        Inc = (ScrollState.NumItems - ScrollState.PageSize) / 2;
        ScrollState.v += Inc * Vz;
        if ((ScrollState.v >= Inc * 2) || (ScrollState.v <= 0)) {
          Vz *= -1;
        }
        SCROLLBAR_SetValue(hScroll, ScrollState.v);
      }
      //
      // Change effect
      //
      if ((Cnt % 400) == 0) {
        IndexEffect++;
        Index = IndexEffect % GUI_COUNTOF(_apEffect);
        _SetEffect(Index);
        hWin = WM_GetDialogItem(hDlgOptions, GUI_ID_RADIO0);
        RADIO_SetValue(hWin, Index);
      }
    }
    GUI_Delay(10);
  }
}

/*************************** End of file ****************************/
