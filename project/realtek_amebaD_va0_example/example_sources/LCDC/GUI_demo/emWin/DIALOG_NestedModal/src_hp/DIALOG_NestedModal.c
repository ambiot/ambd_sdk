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
File        : DIALOG_NestedModal.c
Purpose     : Creates a nested modal dialog after pressing a button
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "GUI.h"
#include "DIALOG.h"
#include "LISTVIEW.h"
#include "MESSAGEBOX.h"
#include "diag.h"

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
static char       _acVehicle[40];

static const char _acItems[][2][20] = {
  {"AUDI",      "A6"               },
  {"AUDI",      "A8"               },
  {"AUDI",      "Quattro"          },
  {"AUDI",      "TT"               },
  {"BMW",       "325xi"            },
  {"BMW",       "330i"             },
  {"BMW",       "745i"             },
  {"BMW",       "Mini Cooper"      },
  {"CHEVROLET", "Cavalier LS Sport"},
  {"CHEVROLET", "Corvette Z06"     },
  {"CHEVROLET", "Malibu LS"        },
  {"FERRARI",   "575M"             },
  {"FORD",      "Escort"           },
  {"FORD",      "Focus"            },
  {"HYUNDAI",   "Sonata"           },
  {"HYUNDAI",   "XG350"            },
  {"JAGUAR",    "VDP"              },
  {"JAGUAR",    "S-Type"           },
  {"MAZDA",     "MX-5"             },
  {"MERCEDES",  "S"                },
  {"MERCEDES",  "CL"               },
  {"PORSCHE",   "Boxster"          },
  {"",          ""                 }
};

/*********************************************************************
*
*       Dialog resource
*
**********************************************************************
*/
static const GUI_WIDGET_CREATE_INFO _aDialogOrder[] = {
  { FRAMEWIN_CreateIndirect, "Order vehicle",   0,                 20,  50, 280, 160, 0 },
  { TEXT_CreateIndirect,     "Selection",       0,                 37,  13,  80,  20, 0 },
  { TEXT_CreateIndirect,     "Drive",           0,                 10,  35,  80,  20, 0 },
  { TEXT_CreateIndirect,     "Front",           0,                 30,  51,  80,  20, 0 },
  { TEXT_CreateIndirect,     "Rear",            0,                 30,  66,  80,  20, 0 },
  { TEXT_CreateIndirect,     "Both",            0,                 30,  81,  80,  20, 0 },
  { TEXT_CreateIndirect,     "Color",           0,                108,  47,  80,  20, 0 },
  { TEXT_CreateIndirect,     "Options",         0,                 95,  77,  80,  20, 0 },
  { EDIT_CreateIndirect,     NULL,              GUI_ID_EDIT0,      85,  10, 180,  20, 0, 40},
  { RADIO_CreateIndirect,    NULL,              GUI_ID_RADIO0,     10,  50,   0,   0, 0, 0xF03 },
  { DROPDOWN_CreateIndirect, NULL,              GUI_ID_DROPDOWN0, 135,  45, 130,  45, 0 },
  { DROPDOWN_CreateIndirect, NULL,              GUI_ID_DROPDOWN1, 135,  75, 130,  45, 0 },
  { BUTTON_CreateIndirect,   "Select vehicle",  GUI_ID_BUTTON0,     6, 113, 100,  20, 0 },
  { BUTTON_CreateIndirect,   "OK",              GUI_ID_OK,        160, 113,  50,  20, 0 },
  { BUTTON_CreateIndirect,   "Cancel",          GUI_ID_CANCEL,    217, 113,  50,  20, 0 }
};

static const GUI_WIDGET_CREATE_INFO _aDialogSelect[] = {
  { FRAMEWIN_CreateIndirect, "Select vehicle",  0,                 55,  30, 210, 200, 0 },
  { TEXT_CreateIndirect,     "Available vehicles:", 0,              9,   6, 120,  20, 0 },
  { LISTVIEW_CreateIndirect, NULL,              GUI_ID_LISTVIEW0,   7,  20, 190, 120, 0 },
  { BUTTON_CreateIndirect,   "OK",              GUI_ID_OK,         90, 153,  50,  20, 0 },
  { BUTTON_CreateIndirect,   "Cancel",          GUI_ID_CANCEL,    147, 153,  50,  20, 0 }
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _AddListviewItem
*/
static void _AddListviewItem(LISTVIEW_Handle hObj, const char* pMake, const char* pModel) {
  unsigned NumItems;

  NumItems = LISTVIEW_GetNumRows(hObj);
  LISTVIEW_AddRow(hObj, NULL);
  LISTVIEW_SetItemText(hObj, 0, NumItems, pMake);
  LISTVIEW_SetItemText(hObj, 1, NumItems, pModel);  
}

/*********************************************************************
*
*       _InitDialogSelect
*/
static void _InitDialogSelect(WM_HWIN hWin) {
  WM_HWIN hItem;
  int     i;
  
  i = 0;
  //
  // Init framewindow
  //
  FRAMEWIN_SetFont(hWin, &GUI_Font10_ASCII);
  FRAMEWIN_SetTitleHeight(hWin, 14);
  FRAMEWIN_SetMoveable(hWin, 1);
  //
  // Init listbox items
  //
  hItem = WM_GetDialogItem(hWin, GUI_ID_LISTVIEW0);
  WM_SetScrollbarV(hItem, 1);
  LISTVIEW_SetGridVis(hItem, 1);
  LISTVIEW_SetLBorder(hItem, 3);
  LISTVIEW_SetRBorder(hItem, 3);
  LISTVIEW_AddColumn(hItem,  80, "Make",    GUI_TA_LEFT);
  LISTVIEW_AddColumn(hItem, 100, "Options", GUI_TA_LEFT);
  while (_acItems[i][0][0]) {
    _AddListviewItem(hItem, _acItems[i][0], _acItems[i][1]);
    i++;
  }
}

/*********************************************************************
*
*       _InitDialogOrder
*/
static void _InitDialogOrder(WM_HWIN hWin) {
  WM_HWIN hItem;

  //
  // Init framewindow
  //
  FRAMEWIN_SetFont(hWin, &GUI_Font10_ASCII);
  FRAMEWIN_SetTitleHeight(hWin, 14);
  FRAMEWIN_SetMoveable(hWin, 1);
  //
  // Init edit widget
  //
  hItem = WM_GetDialogItem(hWin, GUI_ID_EDIT0);
  WM_DisableWindow(hItem);
  //
  // Init dropdown box color
  //
  hItem = WM_GetDialogItem(hWin, GUI_ID_DROPDOWN0);
  DROPDOWN_AddString(hItem, "Blue");
  DROPDOWN_AddString(hItem, "Green");
  DROPDOWN_AddString(hItem, "Red");
  DROPDOWN_SetBkColor(hItem, 1, GUI_WHITE);
  DROPDOWN_SetTextColor(hItem, 1, GUI_BLACK);
  //
  // Init dropdown box model
  //
  hItem = WM_GetDialogItem(hWin, GUI_ID_DROPDOWN1);
  DROPDOWN_AddString(hItem, "Navigation system");
  DROPDOWN_AddString(hItem, "CD Player");
  DROPDOWN_AddString(hItem, "Other ...");
  DROPDOWN_SetBkColor(hItem, 1, GUI_WHITE);
  DROPDOWN_SetTextColor(hItem, 1, GUI_BLACK);
}

/*********************************************************************
*
*       _GetVehicle
*/
static int _GetVehicle(WM_HWIN hWin) {
  WM_HWIN hItem;
  int     CurSel;
  int     NumItems;

  hItem    = WM_GetDialogItem(hWin, GUI_ID_LISTVIEW0);
  NumItems = LISTVIEW_GetNumRows(hItem);
  CurSel   = LISTVIEW_GetSel(hItem);
  if ((CurSel >= 0) && (CurSel < NumItems)) {
    strcpy(_acVehicle, _acItems[CurSel][0]);
    strcat(_acVehicle, " ");
    strcat(_acVehicle, _acItems[CurSel][1]);

    hItem = WM_GetDialogItem(hWin, GUI_ID_EDIT0);
    EDIT_SetText(hItem, _acVehicle);
    return 1;
  }
  return 0;
}

/*********************************************************************
*
*       _MessageBox
*/
static void _MessageBox(const char* pText, const char* pCaption) {
  WM_HWIN hWin;

  hWin = MESSAGEBOX_Create(pText, pCaption, 0);
  WM_MakeModal(hWin);
  GUI_ExecCreatedDialog(hWin);
}

/*********************************************************************
*
*       _cbBkWindow
*/
static void _cbBkWindow(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_MAKE_COLOR(0x008000));
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_Clear();
    GUI_DispStringHCenterAt("DIALOG_NestedModal - Sample", 160, 10);
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbDialogSelect
*/
static void _cbDialogSelect(WM_MESSAGE* pMsg) {
  WM_HWIN hWin;

  hWin = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    _InitDialogSelect(hWin);
    WM_SetFocus(WM_GetDialogItem(hWin, GUI_ID_OK));
    break;
  case WM_NOTIFY_PARENT:
    if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
      int Id = WM_GetId(pMsg->hWinSrc);
      switch (Id) {
      case GUI_ID_OK:
        if (_GetVehicle(hWin) == 0) {
          _MessageBox("You have to select a vehicle!", "ERROR");
          WM_MakeModal(hWin);
          WM_SetFocus(hWin);
          break;
        }
      case GUI_ID_CANCEL:
        GUI_EndDialog(pMsg->hWin, 0);
        break;
      }
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbDialogOrder
*/
static void _cbDialogOrder(WM_MESSAGE* pMsg) {
  WM_HWIN hDlg;
  WM_HWIN hWin;

  hWin = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    _InitDialogOrder(hWin);
    WM_SetFocus(WM_GetDialogItem(hWin, GUI_ID_OK));
    break;
  case WM_NOTIFY_PARENT:
    if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
      int Id = WM_GetId(pMsg->hWinSrc);
      switch (Id) {
      case GUI_ID_BUTTON0:
        hDlg = GUI_CreateDialogBox(_aDialogSelect, GUI_COUNTOF(_aDialogSelect), &_cbDialogSelect, WM_HBKWIN, 0, 0); 
	DBG_8195A("2  ");
        WM_MakeModal(hDlg);
		DBG_8195A("3  ");
        GUI_ExecCreatedDialog(hDlg);
		DBG_8195A("4  ");
        WM_MakeModal(hWin);
		DBG_8195A("5  ");
        WM_SetFocus(hWin);
		DBG_8195A("6  ");
        hDlg = WM_GetDialogItem(hWin, GUI_ID_EDIT0);
		DBG_8195A("7  ");
        EDIT_SetText(hDlg, _acVehicle);
        break;
      case GUI_ID_OK:
      case GUI_ID_CANCEL:
        GUI_EndDialog(hWin, 0);
        break;
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
void MainTask(void);
void MainTask(void) {
  WM_HWIN hWin;
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  GUI_CURSOR_Show();
  WM_SetCreateFlags(WM_CF_MEMDEV);
  WM_EnableMemdev(WM_HBKWIN);
  WM_SetCallback(WM_HBKWIN, &_cbBkWindow);
  while (1) {
    hWin = GUI_CreateDialogBox(_aDialogOrder, GUI_COUNTOF(_aDialogOrder), &_cbDialogOrder, WM_HBKWIN, 0, 0); 
    WM_MakeModal(hWin);
    GUI_ExecCreatedDialog(hWin);
    GUI_Delay(1500);
  }
}

/*************************** End of file ****************************/

