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
File        : WIDGET_SchemeSmall.c
Purpose     : Example demonstrating the use of widget effects
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "GUI.h"
#include "DIALOG.h"

#if !defined(WIDGET_USE_SCHEME_SMALL)
  #error Wrong scheme selected!
#endif

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define NUM_WIDGETS         GUI_COUNTOF(_aID)
#define ID_MENU             (GUI_ID_USER +  0)
#define ID_MENU_FILE_NEW    (GUI_ID_USER +  1)
#define ID_MENU_FILE_OPEN   (GUI_ID_USER +  2)
#define ID_MENU_FILE_CLOSE  (GUI_ID_USER +  3)
#define ID_MENU_FILE_EXIT   (GUI_ID_USER +  4)
#define ID_MENU_FILE_RECENT (GUI_ID_USER +  5)
#define ID_MENU_RECENT_0    (GUI_ID_USER +  6)
#define ID_MENU_RECENT_1    (GUI_ID_USER +  7)
#define ID_MENU_RECENT_2    (GUI_ID_USER +  8)
#define ID_MENU_RECENT_3    (GUI_ID_USER +  9)
#define ID_MENU_EDIT_UNDO   (GUI_ID_USER + 10)
#define ID_MENU_EDIT_REDO   (GUI_ID_USER + 11)
#define ID_MENU_EDIT_COPY   (GUI_ID_USER + 12)
#define ID_MENU_EDIT_PASTE  (GUI_ID_USER + 13)
#define ID_MENU_EDIT_DELETE (GUI_ID_USER + 14)
#define ID_MENU_HELP_ABOUT  (GUI_ID_USER + 15)

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 60)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
//
// Makes it easier to access the array _ahWin
//
enum {
  BUTTON0,    EDIT0,      LISTBOX0,   PROGBAR0,
  LISTVIEW0,  MULTIEDIT0, DROPDOWN0,  SCROLLBAR0,
  SCROLLBAR1, SCROLLBAR2, SLIDER0,    SLIDER1,
  SLIDER2,    GRAPH0,     MULTIPAGE0
};

//
// Dialog resource of main dialog box
//
static const GUI_WIDGET_CREATE_INFO _aDlgWidgets[] = {
  { WINDOW_CreateIndirect,    "",             0,                    0,   0, 690, 435, 0},
  { TEXT_CreateIndirect,      "Progress bar",  GUI_ID_TEXT0,       10,  35, 120,  25, TEXT_CF_HCENTER},
  { PROGBAR_CreateIndirect,   NULL,            GUI_ID_PROGBAR0,    10,  60, 120,  25 },
  { TEXT_CreateIndirect,      "Button",        GUI_ID_TEXT0,       10,  90, 120,  25, TEXT_CF_HCENTER},
  { BUTTON_CreateIndirect,    "Button",        GUI_ID_BUTTON0,     10, 115, 120,  25 },
  { TEXT_CreateIndirect,      "Dropdown",      GUI_ID_TEXT0,       10, 145, 120,  25, TEXT_CF_HCENTER},
  { DROPDOWN_CreateIndirect,  NULL,            GUI_ID_DROPDOWN0,   10, 170, 120,  85, DROPDOWN_CF_AUTOSCROLLBAR},
  { TEXT_CreateIndirect,      "Edit",          GUI_ID_TEXT0,      150,  35, 120,  25, TEXT_CF_HCENTER},
  { EDIT_CreateIndirect,      NULL,            GUI_ID_EDIT0,      150,  60, 120,  25 },
  { TEXT_CreateIndirect,      "Listbox",       GUI_ID_TEXT0,      150,  90, 120,  25, TEXT_CF_HCENTER},
  { LISTBOX_CreateIndirect,   "",              GUI_ID_LISTBOX0,   150, 115, 120, 165, 0, 0 },
  { TEXT_CreateIndirect,      "Listview",      GUI_ID_TEXT0,      290,  35, 150,  25, TEXT_CF_HCENTER},
  { LISTVIEW_CreateIndirect,  NULL,            GUI_ID_LISTVIEW0,  290,  60, 150, 135, 0 },
  { TEXT_CreateIndirect,      "Multiedit",     GUI_ID_TEXT0,      290, 200, 150,  25, TEXT_CF_HCENTER},
  { MULTIEDIT_CreateIndirect, "",              GUI_ID_MULTIEDIT0, 290, 225, 150,  60, 0, 0 },
  { TEXT_CreateIndirect,      "Scrollbars",    GUI_ID_TEXT0,      460,  35, 100,  25, TEXT_CF_HCENTER},
  { SCROLLBAR_CreateIndirect, NULL,            GUI_ID_SCROLLBAR1, 460,  60,  20, 200, SCROLLBAR_CF_VERTICAL },
  { SCROLLBAR_CreateIndirect, NULL,            GUI_ID_SCROLLBAR2, 490,  60,  70, 200, SCROLLBAR_CF_VERTICAL },
  { SCROLLBAR_CreateIndirect, NULL,            GUI_ID_SCROLLBAR0, 460, 270, 100,  15, 0 },
  { TEXT_CreateIndirect,      "Sliders",       GUI_ID_TEXT0,      580,  35, 100,  25, TEXT_CF_HCENTER},
  { SLIDER_CreateIndirect,    NULL,            GUI_ID_SLIDER1,    580,  60,  20, 200, SLIDER_CF_VERTICAL },
  { SLIDER_CreateIndirect,    NULL,            GUI_ID_SLIDER2,    610,  60,  70, 200, SLIDER_CF_VERTICAL },
  { SLIDER_CreateIndirect,    NULL,            GUI_ID_SLIDER0,    580, 270, 100,  15, 0 },
  { TEXT_CreateIndirect,      "Graph",         GUI_ID_TEXT0,      210, 300, 175,  25, TEXT_CF_HCENTER},
  { GRAPH_CreateIndirect,     0,               GUI_ID_GRAPH0,     210, 325, 175, 100 },
  { TEXT_CreateIndirect,      "Multipage",     GUI_ID_TEXT0,      400, 300, 220,  25, TEXT_CF_HCENTER},
  { MULTIPAGE_CreateIndirect, "Multipage",     GUI_ID_MULTIPAGE0, 400, 325, 220, 100 },
};

//
// Dialog resource of options dialog box
//
static const GUI_WIDGET_CREATE_INFO _aDlgOptions[] = {
  { FRAMEWIN_CreateIndirect, "Effect", 0,             10, 325, 185, 120, 0, 0      },
  { CHECKBOX_CreateIndirect, NULL,     GUI_ID_CHECK0, 0,  2,   90,  0,   0, 0      },
  { RADIO_CreateIndirect,    NULL,     GUI_ID_RADIO0, 80, 2,   95,  100, 0, 0x1e03 },
};

//
// Dialog resource of first multipage window
//
static const GUI_WIDGET_CREATE_INFO _aDialogCreate1[] = {
  { WINDOW_CreateIndirect, "Dialog 1", 0,              0, 0,  260, 100, 0            },
  { TEXT_CreateIndirect,   "Dialog 1", 0,              5, 5,  80,  25,  TEXT_CF_LEFT },
  { BUTTON_CreateIndirect, "Button",   GUI_ID_BUTTON0, 5, 30, 80,  25,  0            },
};

//
// Dialog resource of second multipage window
//
static const GUI_WIDGET_CREATE_INFO _aDialogCreate2[] = {
  { WINDOW_CreateIndirect, "Dialog 2", 0,              0, 0,  260, 100, 0            },
  { TEXT_CreateIndirect,   "Dialog 2", 0,              5, 5,  80,  25,  TEXT_CF_LEFT },
  { SLIDER_CreateIndirect, "",         GUI_ID_SLIDER0, 5, 30, 200, 40,  0            },
};

//
// Array of widget ID's
//
static int _aID[] = {
  GUI_ID_BUTTON0,    GUI_ID_EDIT0,      GUI_ID_LISTBOX0,   GUI_ID_PROGBAR0,
  GUI_ID_LISTVIEW0,  GUI_ID_MULTIEDIT0, GUI_ID_DROPDOWN0,  GUI_ID_SCROLLBAR0,
  GUI_ID_SCROLLBAR1, GUI_ID_SCROLLBAR2, GUI_ID_SLIDER0,    GUI_ID_SLIDER1,
  GUI_ID_SLIDER2,    GUI_ID_GRAPH0,     GUI_ID_MULTIPAGE0
};

//
// Array of widget handles
//
static WM_HWIN _ahWin[GUI_COUNTOF(_aID)];

//
// Array of available effects
//
static const WIDGET_EFFECT * _apEffect[] = {
  &WIDGET_Effect_3D,     
  &WIDGET_Effect_Simple, 
  &WIDGET_Effect_None
};

//
// Array of strings used to label the frame window
//
static const char * _apEffects[] = {
  "Widget effect: 3D",
  "Widget effect: Simple", 
  "Widget effect: None"
};

//
// Used for graph widget
//
static I16               _aValue[3];                                           // Array of values to be added
static GRAPH_DATA_Handle _ahData[3];                                           // Array of handles for the GRAPH_DATA objects
static GUI_COLOR         _aColor[]   = { GUI_RED, GUI_GREEN, GUI_LIGHTBLUE };  // Array of colors for the GRAPH_DATA objects
static WM_HWIN           _hDlg;
static WM_HWIN           _hFrameWin;
static int               _AutoMode   = 1;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _AddValues
*
* Function description
*   This routine calculates new random values in dependence of the
*   previous added values and adds them to the GRAPH_DATA objects.
*/
static void _AddValues(int MaxValue) {
  int Add;
  int Vz;
  int i;

  for (i = 0; i < (int)GUI_COUNTOF(_aValue); i++) {
    Add = rand() % (2 + i * i);
    Vz  = ((rand() % 2) * 2) - 1;
    _aValue[i] += Add * Vz;
    if (_aValue[i] > MaxValue) {
      _aValue[i] = MaxValue;
    } else if (_aValue[i] < 0) {
      _aValue[i] = 0;
    }
    GRAPH_DATA_YT_AddValue(_ahData[i], _aValue[i]);
  }
}

/*********************************************************************
*
*       _SetWidgetEffect
*
* Function description
*   Sets the effect for the given widget and recursive for its child windows.
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
      _SetWidgetEffect(hChild, pEffect);
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
  unsigned              i;

  pEffect = _apEffect[Index];
  WIDGET_SetDefaultEffect(pEffect);
  FRAMEWIN_SetText(_hFrameWin, _apEffects[Index]);
  //
  // Iterate over all dialog widgets
  //
  for (i = 0; i < NUM_WIDGETS; i++) {
    _SetWidgetEffect(_ahWin[i], _apEffect[Index]);
  }
}

/*********************************************************************
*
*       _AddMenuItem
*/
static void _AddMenuItem(MENU_Handle hMenu, MENU_Handle hSubmenu, const char* pText, U16 Id, U16 Flags) {
  MENU_ITEM_DATA Item;

  Item.pText    = pText;
  Item.hSubmenu = hSubmenu;
  Item.Flags    = Flags;
  Item.Id       = Id;
  MENU_AddItem(hMenu, &Item);
}

/*********************************************************************
*
*       _CreateMenu
*/
static WM_HWIN _CreateMenu(WM_HWIN hParent) {
  MENU_Handle hMenu;
  MENU_Handle hMenuFile;
  MENU_Handle hMenuEdit;
  MENU_Handle hMenuHelp;
  MENU_Handle hMenuRecent;

  //
  // Create main menu
  //
  hMenu       = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_HORIZONTAL, ID_MENU);
  //
  // Create sub menus
  //
  hMenuFile   = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_VERTICAL, 0);
  hMenuEdit   = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_VERTICAL, 0);
  hMenuHelp   = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_VERTICAL, 0);
  hMenuRecent = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_VERTICAL, 0);
  //
  // Add menu items to menu 'Recent'
  //
  _AddMenuItem(hMenuRecent, 0,           "File 0",   ID_MENU_RECENT_0,    0);
  _AddMenuItem(hMenuRecent, 0,           "File 1",   ID_MENU_RECENT_1,    0);
  _AddMenuItem(hMenuRecent, 0,           "File 2",   ID_MENU_RECENT_2,    0);
  _AddMenuItem(hMenuRecent, 0,           "File 3",   ID_MENU_RECENT_3,    0);
  //
  // Add menu items to menu 'File'
  //
  _AddMenuItem(hMenuFile,   0,           "New",      ID_MENU_FILE_NEW,    0);
  _AddMenuItem(hMenuFile,   0,           "Open",     ID_MENU_FILE_OPEN,   0);
  _AddMenuItem(hMenuFile,   0,           "Close",    ID_MENU_FILE_CLOSE,  0);
  _AddMenuItem(hMenuFile,   0,           0,          0,                   MENU_IF_SEPARATOR);
  _AddMenuItem(hMenuFile,   hMenuRecent, "Files...", ID_MENU_FILE_RECENT, 0);
  _AddMenuItem(hMenuFile,   0,           0,          0,                   MENU_IF_SEPARATOR);
  _AddMenuItem(hMenuFile,   0,           "Exit",     ID_MENU_FILE_EXIT,   0);
  //
  // Add menu items to menu 'Edit'
  //
  _AddMenuItem(hMenuEdit,   0,           "Undo",     ID_MENU_EDIT_UNDO,   0);
  _AddMenuItem(hMenuEdit,   0,           "Redo",     ID_MENU_EDIT_REDO,   0);
  _AddMenuItem(hMenuEdit,   0,           0,          0,                   MENU_IF_SEPARATOR);
  _AddMenuItem(hMenuEdit,   0,           "Copy",     ID_MENU_EDIT_COPY,   0);
  _AddMenuItem(hMenuEdit,   0,           "Paste",    ID_MENU_EDIT_PASTE,  0);
  _AddMenuItem(hMenuEdit,   0,           "Delete",   ID_MENU_EDIT_DELETE, 0);
  //
  // Add menu items to menu 'Help'
  //
  _AddMenuItem(hMenuHelp,   0,           "About",    ID_MENU_HELP_ABOUT,  0);
  //
  // Add menu items to main menu
  //
  _AddMenuItem(hMenu,       hMenuFile,   "File",     0,                   0);
  _AddMenuItem(hMenu,       hMenuEdit,   "Edit",     0,                   0);
  _AddMenuItem(hMenu,       hMenuHelp,   "Help",     0,                   0);
  //
  // Attach menu to parent window
  //
  MENU_Attach(hMenu, hParent, 0, 0, WM_GetWindowSizeX(hParent), 0, 0);
  return hMenu;
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
*       _cbDialogPage
*
* Function description
*   Dialog routine for multi page windows
*/
static void _cbDialogPage(WM_MESSAGE * pMsg) {
  WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       _cbCallbackWidgets
*
* Function description
*   Initializes the widgets of the main dialog box
*/
static void _cbCallbackWidgets(WM_MESSAGE * pMsg) {
  GRAPH_SCALE_Handle hScaleH;
  GRAPH_SCALE_Handle hScaleV;
  unsigned           i;
  WM_HWIN            hDlg;
  WM_HWIN            hMultipageDialog;
  char               acBuffer[10];
  int                Len;
  int                j;

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
        sDiagPrintf(acBuffer, "Item x");
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
        sDiagPrintf(acBuffer, "Item x");
        Len = strlen(acBuffer);
        acBuffer[Len - 1] = '1' + i;
        LISTBOX_AddString(_ahWin[LISTBOX0], acBuffer);
      }
      //
      // Init listview widget
      //
      for (i = 0; i < 2; i++) {
        sDiagPrintf(acBuffer, "Col. x");
        Len = strlen(acBuffer);
        acBuffer[Len - 1] = '1' + i;
        LISTVIEW_AddColumn(_ahWin[LISTVIEW0], 60, acBuffer, GUI_TA_CENTER);
      }
      for (i = 0; i < 9; i++) {
        LISTVIEW_AddRow(_ahWin[LISTVIEW0], NULL);
        for (j = 0; j < (int)LISTVIEW_GetNumColumns(_ahWin[LISTVIEW0]); j++) {
          sDiagPrintf(acBuffer, "Rx/Cx");
          acBuffer[1] = '1' + i;
          acBuffer[4] = '1' + j;
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
      //
      // Init graph widget
      //
      for (i = 0; i < GUI_COUNTOF(_aColor); i++) {
        _aValue[i] = rand() % 95;
        _ahData[i] = GRAPH_DATA_YT_Create(_aColor[i], 500, 0, 0);
        GRAPH_AttachData(_ahWin[GRAPH0], _ahData[i]);
      }
      GRAPH_SetGridDistY(_ahWin[GRAPH0], 25);
      GRAPH_SetGridVis(_ahWin[GRAPH0], 1);
      GRAPH_SetGridFixedX(_ahWin[GRAPH0], 1);
      GRAPH_SetBorder(_ahWin[GRAPH0], 20, 4, 5, 4);
      //
      // Create and add vertical scale of graph widget
      //
      hScaleV = GRAPH_SCALE_Create(18, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 25);
      GRAPH_SCALE_SetTextColor(hScaleV, GUI_RED);
      GRAPH_AttachScale(_ahWin[GRAPH0], hScaleV);
      //
      // Create and add horizontal scale of graph widget
      //
      hScaleH = GRAPH_SCALE_Create(46, GUI_TA_HCENTER | GUI_TA_VCENTER, GRAPH_SCALE_CF_HORIZONTAL, 50);
      GRAPH_SCALE_SetTextColor(hScaleH, GUI_DARKGREEN);
      GRAPH_AttachScale(_ahWin[GRAPH0], hScaleH);
      //
      // Init multipage widget
      //
      hMultipageDialog = GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialogPage, WM_UNATTACHED, 0, 0);
      MULTIPAGE_AddPage(_ahWin[MULTIPAGE0], hMultipageDialog, "Page 1");
      hMultipageDialog = GUI_CreateDialogBox(_aDialogCreate2, GUI_COUNTOF(_aDialogCreate2), _cbDialogPage, WM_UNATTACHED, 0, 0);
      MULTIPAGE_AddPage(_ahWin[MULTIPAGE0], hMultipageDialog, "Page 2");
      //
      // Create and attach menu
      //
      _CreateMenu(hDlg);
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
  WM_HWIN hDlg;
  WM_HWIN hItem;

  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
      //
      // Init check box
      //
      hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK0);
      CHECKBOX_Check(hItem);
      CHECKBOX_SetText(hItem, "Auto");
      //
      // Init radio button
      //
      hItem = WM_GetDialogItem(hDlg, GUI_ID_RADIO0);
      RADIO_SetText(hItem, "3D",     0);
      RADIO_SetText(hItem, "Simple", 1);
      RADIO_SetText(hItem, "None",   2);
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
  GUI_RECT        RectDlg;
  GUI_RECT        RectClient;
  unsigned        IndexEffect;
  WM_HWIN         hDlgOptions;
  WM_HWIN         hScrollbar;
  WM_HWIN         hScroll;
  WM_HWIN         hWin;
  char            acBuffer[100];
  int             Cnt;
  int             ButtonState;
  int             DropdownState;
  int             ProgbarValue;
  int             ProgbarInc;
  int             SliderValue;
  int             SliderInc;
  int             ScrollbarValue;
  int             ScrollbarInc;
  int             ListViewInc;
  int             ListBoxInc;
  int             MultiEditInc;
  int             Index;
  int             Inc;
  int             Len;
  int             Sel;
  int             Vz;
  int             j;

  Cnt            = 0;
  IndexEffect    = 0;
  ButtonState    = 0;
  DropdownState  = 0;
  ProgbarValue   = 0;
  ProgbarInc     = 1;
  SliderValue    = 0;
  SliderInc      = 1;
  ScrollbarValue = 0;
  ScrollbarInc   = 1;
  ListViewInc    = 1;
  ListBoxInc     = 1;
  MultiEditInc   = 1;
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
  _hFrameWin = FRAMEWIN_CreateEx(0, 0, 640, 480, 0, WM_CF_SHOW, 0, 0, "", _cbCallbackFramewin);
  FRAMEWIN_SetMoveable(_hFrameWin, 1);
  FRAMEWIN_SetText(_hFrameWin, _apEffects[0]);
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
        for (j = 0; j < 3; j++) {
          SLIDER_SetValue(_ahWin[SLIDER0 + j], SliderValue);
        }
      }
      //
      // Modify scrollbar
      //
      if ((Cnt % 3) == 0) {
        ScrollbarValue += ScrollbarInc;
        if ((ScrollbarValue == 90) || (ScrollbarValue == 0)) {
          ScrollbarInc *= -1;
        }
        for (j = 0; j < 3; j++) {
          SCROLLBAR_SetValue(_ahWin[SCROLLBAR0 + j], ScrollbarValue);
        }
      }
      //
      // Modify multipage
      //
      if ((Cnt % 120) == 0) {
        MULTIPAGE_SelectPage(_ahWin[MULTIPAGE0], MULTIPAGE_GetSelection(_ahWin[MULTIPAGE0]) ^ 1);
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
      // Modify listbox
      //
      if ((Cnt % 30) == 0) {
        Sel = LISTBOX_GetSel(_ahWin[LISTBOX0]);
        if (Sel < 0) {
          Sel = 0;
        }
        LISTBOX_SetSel(_ahWin[LISTBOX0], Sel + ListBoxInc);
        Sel = LISTBOX_GetSel(_ahWin[LISTBOX0]);
        if ((Sel == (int)LISTBOX_GetNumItems(_ahWin[LISTBOX0]) - 1) || (Sel == 0)) {
          ListBoxInc *= -1;
        }
      }
      //
      // Modify listview
      //
      if ((Cnt % 50) == 0) {
        Sel = LISTVIEW_GetSel(_ahWin[LISTVIEW0]);
        if (Sel < 0) {
          Sel = 0;
        }
        LISTVIEW_SetSel(_ahWin[LISTVIEW0], Sel + ListViewInc);
        Sel = LISTVIEW_GetSel(_ahWin[LISTVIEW0]);
        if ((Sel == (int)LISTVIEW_GetNumRows(_ahWin[LISTVIEW0]) - 1) || (Sel == 0)) {
          ListViewInc *= -1;
        }
      }
      //
      // Modify multiedit
      //
      if ((Cnt % 5) == 0) {
        MULTIEDIT_SetCursorOffset(_ahWin[MULTIEDIT0], MULTIEDIT_GetCursorCharPos(_ahWin[MULTIEDIT0]) + MultiEditInc);
        MULTIEDIT_GetText(_ahWin[MULTIEDIT0], acBuffer, sizeof(acBuffer));
        Sel = MULTIEDIT_GetCursorCharPos(_ahWin[MULTIEDIT0]);
        Len = strlen(acBuffer);
        if ((Sel == (Len - 1)) || (Sel == 0)) {
          MultiEditInc *= -1;
        }
        if (!DropdownState) {
          WM_SetFocus(_ahWin[MULTIEDIT0]);
        }
      }
      //
      // Modify graph
      //
      _AddValues(95);
      //
      // Move window
      //
      if ((Cnt % 1200) == 0) {
        hScroll = WM_GetScrollbarH(WM_GetClientWindow(_hFrameWin));
        WM_GetScrollState(hScroll, &ScrollState);
        Inc     = (ScrollState.NumItems - ScrollState.PageSize) / 2;
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
    //
    // Wait a while
    //
    GUI_Delay(10);
  }
}

/*************************** End of file ****************************/
