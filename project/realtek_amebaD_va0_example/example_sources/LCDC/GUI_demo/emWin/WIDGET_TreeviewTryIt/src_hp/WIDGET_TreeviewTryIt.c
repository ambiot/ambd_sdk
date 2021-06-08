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
File        : WIDGET_TreeviewTryIt.c
Purpose     : Demonstrates the use of the TREEVIEW widget
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include <stddef.h>
#include "DIALOG.h"
#include "TREEVIEW.h"
#include "MULTIPAGE.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define NUM_CHILD_NODES 3
#define NUM_CHILD_ITEMS 6
#define TREEVIEW_DEPTH  5

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 80)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/*********************************************************************
*
*       _aMain
*
* Description
*   Main window containing the two treeviews and a multipage widget
*/
static const GUI_WIDGET_CREATE_INFO _aMain[] = {
  { WINDOW_CreateIndirect,    NULL,                0,                   0,   0, 320, 240 },
  { TEXT_CreateIndirect,      "Treeview TryIt",    GUI_ID_TEXT0,      160,   0, 160,  20 },
  { TREEVIEW_CreateIndirect,  NULL,                GUI_ID_TREEVIEW0,    0,   0, 160, 220 },
  { TREEVIEW_CreateIndirect,  NULL,                GUI_ID_TREEVIEW1,    0, 220, 160,  20 },
  { MULTIPAGE_CreateIndirect, NULL,                GUI_ID_MULTIPAGE0, 160,  20, 160, 220 },
};

/*********************************************************************
*
*       _aPage0
*
* Description
*   First page of the multipage widget for setting the widget properties
*/
static const GUI_WIDGET_CREATE_INFO _aPage0[] = {
  { WINDOW_CreateIndirect,    NULL,                0,                   0,   0, 156, 192 },
  { TEXT_CreateIndirect,      "Selection",         0,                   5,  10, 100,  15 },
  { RADIO_CreateIndirect,     NULL,                GUI_ID_RADIO0,       5,  30, 100,   0, 0, 2 },
  { TEXT_CreateIndirect,      "Lines",             0,                   5,  70, 100,  15 },
  { RADIO_CreateIndirect,     NULL,                GUI_ID_RADIO1,       5,  90, 100,   0, 0, 2 },
  { TEXT_CreateIndirect,      "Font",              0,                   5, 130, 100,  15 },
  { RADIO_CreateIndirect,     NULL,                GUI_ID_RADIO4,       5, 150, 100,   0, 0, 2 },
  { TEXT_CreateIndirect,      "H",                 0,                  92,  10,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "V",                 0,                 107,  10,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "Scroll",            0,                 122,  10,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "Auto",              0,                 122,  30,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "Off",               0,                 122,  50,  50,  15, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,      "On",                0,                 122,  70,  50,  15, TEXT_CF_LEFT },
  { RADIO_CreateIndirect,      NULL,               GUI_ID_RADIO2,      87,  30,   0,   0, 0, 3 },
  { RADIO_CreateIndirect,      NULL,               GUI_ID_RADIO3,     102,  30,   0,   0, 0, 3 },
};

/*********************************************************************
*
*       _aPage1
*
* Description
*   Second page of the multipage widget for playing with the data
*/
static const GUI_WIDGET_CREATE_INFO _aPage1[] = {
  { WINDOW_CreateIndirect,    NULL,                0,                   0,   0, 156, 192 },
  { BUTTON_CreateIndirect,    "Delete item",       GUI_ID_BUTTON0,      5,  10, 140,  18 },
  { BUTTON_CreateIndirect,    "Detach item",       GUI_ID_BUTTON1,      5,  28, 140,  18 },
  { BUTTON_CreateIndirect,    "Attach item",       GUI_ID_BUTTON2,      5,  46, 140,  18 },
  { BUTTON_CreateIndirect,    "Move up",           GUI_ID_BUTTON3,      5,  64, 140,  18 },
  { BUTTON_CreateIndirect,    "Move down",         GUI_ID_BUTTON4,      5,  82, 140,  18 },
  { BUTTON_CreateIndirect,    "New node",          GUI_ID_BUTTON5,      5, 100, 140,  18 },
  { BUTTON_CreateIndirect,    "New leaf",          GUI_ID_BUTTON6,      5, 118, 140,  18 },
  { BUTTON_CreateIndirect,    "Set leaf bitmap",   GUI_ID_BUTTON7,      5, 136, 140,  18 },
  { BUTTON_CreateIndirect,    "Set open bitmap",   GUI_ID_BUTTON8,      5, 154, 140,  18 },
  { BUTTON_CreateIndirect,    "Set closed bitmap", GUI_ID_BUTTON9,      5, 172, 140,  18 },
};

/*********************************************************************
*
*       _bmSmilie
*/
static const GUI_COLOR _ColorsSmilie[] = {
#if (GUI_USE_ARGB == 1)
     0xFFFFFFFF,0xFF000000,0xFF70FF70
#else
     0xFFFFFF,0x000000,0x70FF70
#endif
};

static const GUI_LOGPALETTE _PalSmilie = {
  3,	// Number of entries
  1, 	// Has transparency
  &_ColorsSmilie[0]
};

static const unsigned char _acSmilie[] = {
  0x00, 0x55, 0x40, 0x00,
  0x01, 0xAA, 0x90, 0x00,
  0x06, 0xAA, 0xA4, 0x00,
  0x19, 0x6A, 0x59, 0x00,
  0x69, 0x6A, 0x5A, 0x40,
  0x6A, 0xA6, 0xAA, 0x40,
  0x6A, 0xA6, 0xAA, 0x40,
  0x6A, 0xA6, 0xAA, 0x40,
  0x6A, 0xAA, 0xAA, 0x40,
  0x1A, 0x6A, 0x69, 0x00,
  0x06, 0x95, 0xA4, 0x00,
  0x01, 0xAA, 0x90, 0x00,
  0x00, 0x55, 0x40, 0x00
};

static const GUI_BITMAP _bmSmilie = {
 13,          // XSize
 13,          // YSize
 4,           // BytesPerLine
 2,           // BitsPerPixel
 _acSmilie,   // Pointer to picture data (indices)
 &_PalSmilie  // Pointer to palette
};

/*********************************************************************
*
*       _bmBookOpen
*/
static GUI_CONST_STORAGE GUI_COLOR _ColorsBookOpen[] = {
#if (GUI_USE_ARGB == 1)
     0xFFFF0000,0xFFFFFFFF,0xFF000000,0xFF008000
    ,0xFF808080,0xFFC0C0C0
#else
     0x0000FF,0xFFFFFF,0x000000,0x008000
    ,0x808080,0xC0C0C0
#endif
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalBookOpen = {
  6,	// Number of entries
  1, 	// Has transparency
  &_ColorsBookOpen[0]
};

static GUI_CONST_STORAGE unsigned char _acBookOpen[] = {
  0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x04, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x23, 0x15, 0x40, 0x00, 0x04, 0x44, 0x00, 0x00,
  0x23, 0x11, 0x40, 0x04, 0x41, 0x14, 0x00, 0x00,
  0x23, 0x11, 0x54, 0x41, 0x11, 0x14, 0x22, 0x00,
  0x23, 0x11, 0x12, 0x51, 0x11, 0x14, 0x13, 0x20,
  0x23, 0x11, 0x12, 0x51, 0x11, 0x14, 0x13, 0x20,
  0x23, 0x11, 0x12, 0x51, 0x11, 0x14, 0x13, 0x20,
  0x23, 0x11, 0x12, 0x51, 0x11, 0x14, 0x13, 0x20,
  0x23, 0x11, 0x12, 0x51, 0x11, 0x14, 0x13, 0x20,
  0x23, 0x31, 0x12, 0x51, 0x11, 0x45, 0x13, 0x20,
  0x02, 0x33, 0x12, 0x51, 0x44, 0x51, 0x13, 0x20,
  0x00, 0x23, 0x12, 0x44, 0x51, 0x11, 0x13, 0x20,
  0x00, 0x02, 0x33, 0x33, 0x33, 0x33, 0x33, 0x20,
  0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x22, 0x20
};

GUI_CONST_STORAGE GUI_BITMAP _bmBookOpen = {
  15,            // XSize
  15,            // YSize
  8,             // BytesPerLine
  4,             // BitsPerPixel
  _acBookOpen,   // Pointer to picture data (indices)
  &_PalBookOpen  // Pointer to palette
};

/*********************************************************************
*
*       _bmBookClosed
*/
static GUI_CONST_STORAGE GUI_COLOR _ColorsBookClosed[] = {
#if (GUI_USE_ARGB == 1)
     0xFFFF0000,0xFF008000,0xFF000000,0xFFC0C0C0
#else
     0x0000FF,0x008000,0x000000,0xC0C0C0
#endif
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalBookClosed = {
  4,	// Number of entries
  1, 	// Has transparency
  &_ColorsBookClosed[0]
};

static GUI_CONST_STORAGE unsigned char _acBookClosed[] = {
  0x00, 0x02, 0x80, 0x00,
  0x00, 0x29, 0x60, 0x00,
  0x02, 0x95, 0x58, 0x00,
  0x29, 0x55, 0x56, 0x00,
  0x95, 0x55, 0x55, 0x80,
  0xA5, 0x55, 0x55, 0x60,
  0x99, 0x55, 0x55, 0x58,
  0x96, 0x55, 0x55, 0x5A,
  0x95, 0x95, 0x55, 0xAC,
  0x25, 0x65, 0x5A, 0xFC,
  0x09, 0x59, 0xAF, 0xFA,
  0x02, 0x56, 0xFF, 0xE8,
  0x00, 0x96, 0xFE, 0x80,
  0x00, 0x26, 0xE8, 0x00,
  0x00, 0x0A, 0x80, 0x00
};

GUI_CONST_STORAGE GUI_BITMAP _bmBookClosed = {
  16,              // XSize
  15,              // YSize
  4,               // BytesPerLine
  2,               // BitsPerPixel
  _acBookClosed,   // Pointer to picture data (indices)
  &_PalBookClosed  // Pointer to palette
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbPage0
*
* Function description
*   Callback routine for the first page of the multipage widget
*/
static void _cbPage0(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  WM_HWIN hDlg;
  WM_HWIN hTree;
  int     Sel;
  int     NCode;
  int     Id;

  hDlg  = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    hTree = WM_GetDialogItem(WM_GetFirstChild(WM_HBKWIN), GUI_ID_TREEVIEW0);
    Id    = WM_GetId(pMsg->hWinSrc);      // Id of widget
    NCode = pMsg->Data.v;                 // Notification code
    hItem = WM_GetDialogItem(hDlg, Id);
    switch (Id) {
    case GUI_ID_RADIO0:                   // Select the selection mode
      switch (NCode) {
      case WM_NOTIFICATION_VALUE_CHANGED:
        Sel = RADIO_GetValue(hItem);
        TREEVIEW_SetSelMode(hTree, (Sel == 1) ? TREEVIEW_SELMODE_ROW : TREEVIEW_SELMODE_TEXT);
        break;
      }
      break;
    case GUI_ID_RADIO1:                   // Set the visibility of the lines
      switch (NCode) {
      case WM_NOTIFICATION_VALUE_CHANGED:
        Sel = RADIO_GetValue(hItem);
        TREEVIEW_SetHasLines(hTree, (Sel == 1) ? 1 : 0);
        break;
      }
      break;
    case GUI_ID_RADIO2:                   // Manage horizontal scrollbar
      switch (NCode) {
      case WM_NOTIFICATION_VALUE_CHANGED:
        Sel = RADIO_GetValue(hItem);
        if (Sel == 1) {
          WM_SetScrollbarH(hTree, 0);
        }
        TREEVIEW_SetAutoScrollH(hTree, (Sel == 0) ? 1 : 0);
        if (Sel == 2) {
          SCROLLBAR_CreateAttached(hTree, 0);
        }
        break;
      }
      break;
    case GUI_ID_RADIO3:                   // Manage vertical scrollbar
      switch (NCode) {
      case WM_NOTIFICATION_VALUE_CHANGED:
        Sel = RADIO_GetValue(hItem);
        if (Sel == 1) {
          WM_SetScrollbarV(hTree, 0);
        }
        TREEVIEW_SetAutoScrollV(hTree, (Sel == 0) ? 1 : 0);
        if (Sel == 2) {
          SCROLLBAR_CreateAttached(hTree, WIDGET_CF_VERTICAL);
        }
        break;
      }
      break;
    case GUI_ID_RADIO4:                   // Manage font
      switch (NCode) {
      case WM_NOTIFICATION_VALUE_CHANGED:
        Sel = RADIO_GetValue(hItem);
        TREEVIEW_SetFont(hTree, (Sel == 1) ? &GUI_Font24B_1: &GUI_Font13_1);
        break;
      }
      break;
    }
    break;
  case WM_INIT_DIALOG:                    // Initialize the items of the dialog
    hItem = WM_GetDialogItem(hDlg, GUI_ID_RADIO0);
    RADIO_SetText(hItem, "Text select", 0);
    RADIO_SetText(hItem, "Row select",  1);
    RADIO_SetValue(hItem, 1);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_RADIO1);
    RADIO_SetText(hItem, "Off", 0);
    RADIO_SetText(hItem, "On",  1);
    RADIO_SetValue(hItem, 1);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_RADIO4);
    RADIO_SetText(hItem, "Small font", 0);
    RADIO_SetText(hItem, "Large font",  1);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbPage1
*
* Function description
*   Callback routine for the second page of the multipage widget
*/
static void _cbPage1(WM_MESSAGE * pMsg) {
  TREEVIEW_ITEM_Handle hTVI0;
  TREEVIEW_ITEM_Handle hTVI1;
  TREEVIEW_ITEM_INFO   ItemInfo;
  WM_HWIN              hItem;
  WM_HWIN              hDlg;
  WM_HWIN              hTree0;
  WM_HWIN              hTree1;
  int                  i;
  int                  NCode;
  int                  Id;

  hDlg  = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    hTree0= WM_GetDialogItem(WM_GetFirstChild(WM_HBKWIN), GUI_ID_TREEVIEW0);
    hTree1= WM_GetDialogItem(WM_GetFirstChild(WM_HBKWIN), GUI_ID_TREEVIEW1);
    Id    = WM_GetId(pMsg->hWinSrc);      // Id of widget
    NCode = pMsg->Data.v;                 // Notification code
    WM_GetDialogItem(hDlg, Id);
    switch (Id) {
    case GUI_ID_BUTTON0:                  // Delete
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hTVI0 = TREEVIEW_GetSel(hTree0);
        if (hTVI0) {
          TREEVIEW_ITEM_Delete(hTVI0);
        } else {
          GUI_MessageBox("No item selected!", "Info", GUI_MESSAGEBOX_CF_MODAL);
          WM_SetFocus(hTree0);
        }
        break;
      }
      break;
    case GUI_ID_BUTTON1:                  // Detach
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hTVI1 = TREEVIEW_GetItem(hTree1, 0, TREEVIEW_GET_FIRST);
        if (hTVI1) {
          TREEVIEW_ITEM_Delete(hTVI1);
        }
        hTVI0 = TREEVIEW_GetSel(hTree0);
        TREEVIEW_ITEM_Detach(hTVI0);
        TREEVIEW_AttachItem(hTree1, hTVI0, 0, TREEVIEW_GET_FIRST);
        break;
      }
      break;
    case GUI_ID_BUTTON2:                  // Attach
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hTVI1 = TREEVIEW_GetItem(hTree1, 0, TREEVIEW_GET_FIRST);
        if (hTVI1) {
          hTVI0 = TREEVIEW_GetSel(hTree0);
          TREEVIEW_ITEM_Detach(hTVI1);
          if (hTVI0) {
            TREEVIEW_AttachItem(hTree0, hTVI1, hTVI0, TREEVIEW_INSERT_ABOVE);
          } else {
            TREEVIEW_AttachItem(hTree0, hTVI1,     0, 0);
          }
        } else {
          GUI_MessageBox("No item in buffer!", "Info", GUI_MESSAGEBOX_CF_MODAL);
          WM_SetFocus(hTree0);
        }
        break;
      }
      break;
    case GUI_ID_BUTTON3:                  // Move up
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hTVI0 = TREEVIEW_GetSel(hTree0);
        if (hTVI0) {
          hTVI1 = TREEVIEW_GetItem(hTree0, hTVI0, TREEVIEW_GET_PREV_SIBLING);
          if (hTVI1) {
            TREEVIEW_ITEM_Detach(hTVI0);
            TREEVIEW_AttachItem(hTree0, hTVI0, hTVI1, TREEVIEW_INSERT_ABOVE);
            TREEVIEW_SetSel(hTree0, hTVI0);
          } else {
            GUI_MessageBox("Item is already on top!", "Info", GUI_MESSAGEBOX_CF_MODAL);
            WM_SetFocus(hTree0);
          }
        }
        break;
      }
      break;
    case GUI_ID_BUTTON4:                  // Move down
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hTVI0 = TREEVIEW_GetSel(hTree0);
        if (hTVI0) {
          hTVI1 = TREEVIEW_GetItem(hTree0, hTVI0, TREEVIEW_GET_NEXT_SIBLING);
          if (hTVI1) {
            TREEVIEW_ITEM_Detach(hTVI0);
            TREEVIEW_AttachItem(hTree0, hTVI0, hTVI1, TREEVIEW_INSERT_BELOW);
            TREEVIEW_SetSel(hTree0, hTVI0);
          } else {
            GUI_MessageBox("Item is already on bottom!", "Info", GUI_MESSAGEBOX_CF_MODAL);
            WM_SetFocus(hTree0);
          }
        }
        break;
      }
      break;
    case GUI_ID_BUTTON5:                   // New node
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hTVI0 = TREEVIEW_GetSel(hTree0);
        if (hTVI0) {
          TREEVIEW_ITEM_GetInfo(hTVI0, &ItemInfo);
          if (ItemInfo.IsNode) {
            hTVI0 = TREEVIEW_InsertItem(hTree0, TREEVIEW_ITEM_TYPE_NODE, hTVI0, TREEVIEW_INSERT_BELOW,  "New node");
          } else {
            hTVI0 = TREEVIEW_InsertItem(hTree0, TREEVIEW_ITEM_TYPE_NODE, hTVI0, TREEVIEW_INSERT_ABOVE,  "New node");
          }
        } else {
          hTVI0 = TREEVIEW_InsertItem(hTree0, TREEVIEW_ITEM_TYPE_NODE, 0, 0,  "New node");
        }
        hTVI0 = TREEVIEW_InsertItem(hTree0, TREEVIEW_ITEM_TYPE_LEAF, hTVI0, TREEVIEW_INSERT_FIRST_CHILD, "New.A");
        hTVI0 = TREEVIEW_InsertItem(hTree0, TREEVIEW_ITEM_TYPE_LEAF, hTVI0, TREEVIEW_INSERT_BELOW,  "New.B");
        hTVI0 = TREEVIEW_InsertItem(hTree0, TREEVIEW_ITEM_TYPE_LEAF, hTVI0, TREEVIEW_INSERT_BELOW,  "New.C");
        TREEVIEW_InsertItem(hTree0, TREEVIEW_ITEM_TYPE_LEAF, hTVI0, TREEVIEW_INSERT_BELOW,  "New.D");
        break;
      }
      break;
    case GUI_ID_BUTTON6:                  // New leaf
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hTVI0 = TREEVIEW_GetSel(hTree0);
        if (hTVI0) {
          TREEVIEW_ITEM_GetInfo(hTVI0, &ItemInfo);
          TREEVIEW_InsertItem(hTree0, TREEVIEW_ITEM_TYPE_LEAF, hTVI0, TREEVIEW_INSERT_BELOW,  "New leaf");
        } else {
          TREEVIEW_InsertItem(hTree0, TREEVIEW_ITEM_TYPE_LEAF, 0, 0,  "New leaf");
        }
        break;
      }
      break;
    case GUI_ID_BUTTON7:                  // Leaf bitmap
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hTVI0 = TREEVIEW_GetSel(hTree0);
        if (hTVI0) {
          TREEVIEW_ITEM_GetInfo(hTVI0, &ItemInfo);
          if (ItemInfo.IsNode == 0) {
            TREEVIEW_ITEM_SetImage(hTVI0, TREEVIEW_BI_LEAF, &_bmSmilie);
          } else {
            GUI_MessageBox("Item is not a leaf!", "Info", GUI_MESSAGEBOX_CF_MODAL);
            WM_SetFocus(hTree0);
          }
        } else {
          GUI_MessageBox("No item selected!", "Info", GUI_MESSAGEBOX_CF_MODAL);
          WM_SetFocus(hTree0);
        }
        break;
      }
      break;
    case GUI_ID_BUTTON8:                  // Open bitmap
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hTVI0 = TREEVIEW_GetSel(hTree0);
        if (hTVI0) {
          TREEVIEW_ITEM_GetInfo(hTVI0, &ItemInfo);
          if (ItemInfo.IsNode) {
            TREEVIEW_ITEM_SetImage(hTVI0, TREEVIEW_BI_OPEN, &_bmBookOpen);
          } else {
            GUI_MessageBox("Item is not a node!", "Info", GUI_MESSAGEBOX_CF_MODAL);
            WM_SetFocus(hTree0);
          }
        } else {
          GUI_MessageBox("No item selected!", "Info", GUI_MESSAGEBOX_CF_MODAL);
          WM_SetFocus(hTree0);
        }
        break;
      }
      break;
    case GUI_ID_BUTTON9:                  // Closed bitmap
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
        hTVI0 = TREEVIEW_GetSel(hTree0);
        if (hTVI0) {
          TREEVIEW_ITEM_GetInfo(hTVI0, &ItemInfo);
          if (ItemInfo.IsNode) {
            TREEVIEW_ITEM_SetImage(hTVI0, TREEVIEW_BI_CLOSED, &_bmBookClosed);
          } else {
            GUI_MessageBox("Item is not a node!", "Info", GUI_MESSAGEBOX_CF_MODAL);
            WM_SetFocus(hTree0);
          }
        } else {
          GUI_MessageBox("No item selected!", "Info", GUI_MESSAGEBOX_CF_MODAL);
          WM_SetFocus(hTree0);
        }
        break;
      }
      break;
    }
    break;
  case WM_INIT_DIALOG:                    // Initialize the items of the dialog
    for (i = GUI_ID_BUTTON0; i <= GUI_ID_BUTTON9; i++) {
      hItem = WM_GetDialogItem(hDlg, i);
      if (hItem) {
        BUTTON_SetFocussable(hItem, 0);   // So the focus remains on the treeview after pressing the buttons
      }
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _InitMultipage
*
* Function description
*   Creates the pages of the multipage widget
*/
static void _InitMultipage(WM_HWIN hWin) {
  WM_HWIN hPage0;
  WM_HWIN hPage1;

  hPage0 = GUI_CreateDialogBox(_aPage0, GUI_COUNTOF(_aPage0), _cbPage0, WM_UNATTACHED, 0, 0);
  MULTIPAGE_AddPage(hWin, hPage0, "Properties");
  hPage1 = GUI_CreateDialogBox(_aPage1, GUI_COUNTOF(_aPage1), _cbPage1, WM_UNATTACHED, 0, 0);
  MULTIPAGE_AddPage(hWin, hPage1, "Data");
}

/*********************************************************************
*
*       _FillNode
*
* Function description
*   Recursive filling of node
*
* Parameters
*   hTree     - obvious
*   NumNodes  - Number of child nodes to be created at each node
*   NumLeaves - Number of leaves to be created at each node
*   MaxDepth  - Maximum depth (1.1.1.1.1.....)
*   CurDepth  - Current depth
*   acBuffer  - String to be used for TREEVIEW items
*   p         - Pointer into to string to be used for numbering
*
* Return value
*   0 on success, 1 on error
*/
static int _FillNode(WM_HWIN hTree, TREEVIEW_ITEM_Handle hNode, int NumChildNodes, int NumChildItems, int MaxDepth, int Depth, char * p) {
  static char acBuffer[(TREEVIEW_DEPTH << 1) + 1];
  TREEVIEW_ITEM_Handle hItem;
  int                  i;
  int                  j;
  int                  Position;

  hItem = 0;
  if (p == NULL) {
    p = acBuffer;
  }
  *(p + 1) = 0;
  *p = '0' - 1;
  if (--Depth) {
    //
    // Create nodes
    //
    for (i = 0; i < NumChildNodes; i++) {
      (*p)++;
      Position = hItem ? TREEVIEW_INSERT_BELOW : TREEVIEW_INSERT_FIRST_CHILD;
      hItem = TREEVIEW_ITEM_Create(1, acBuffer, 0);
      if (hItem == 0) {
        return 1;  // Error
      }
      TREEVIEW_AttachItem(hTree, hItem, hNode, Position);
      hNode = hItem;
      *(p + 1) = '.';
      p += 2;
      _FillNode(hTree, hNode, NumChildNodes, NumChildItems, MaxDepth, Depth, p);
      p -= 2;
      *(p + 1) = 0;
    }
  }
  //
  // Create leaves
  //
  for (j = 0; j < NumChildItems; j++) {
    (*p)++;
    Position = hItem ? TREEVIEW_INSERT_BELOW : TREEVIEW_INSERT_FIRST_CHILD;
    hItem = TREEVIEW_ITEM_Create(0, acBuffer, 0);
    if (hItem == 0) {
      return 1;    // Error
    }
    TREEVIEW_AttachItem(hTree, hItem, hNode, Position);
    hNode = hItem;
  }
  return 0;
}

/*********************************************************************
*
*       _InitTreeview
*
* Function description
*   Adds some data to the treeview widget
*/
static int _InitTreeview(WM_HWIN hTree) {
  TREEVIEW_ITEM_Handle hNode;
  int r;

  hNode = TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_NODE, 0, 0, "Tree");
  r = _FillNode(hTree, hNode, NUM_CHILD_NODES, NUM_CHILD_ITEMS, TREEVIEW_DEPTH, TREEVIEW_DEPTH, NULL);
  if (r) {
    //
    // Error message
    //
    WM_DeleteWindow(hTree);
    GUI_MessageBox("Error", "Not enough memory available!", 0);
    return 1;      // Error
  }
  TREEVIEW_SetAutoScrollH(hTree, 1);
  TREEVIEW_SetAutoScrollV(hTree, 1);
  TREEVIEW_ITEM_Expand(hNode);
  return 0;
}

/*********************************************************************
*
*       _cbMain
*
* Function description
*   Callback routine of main window
*/
static void _cbMain(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  WM_HWIN hDlg;

  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    hItem = WM_GetDialogItem(hDlg, GUI_ID_TEXT0);
    TEXT_SetFont(hItem, &GUI_Font20B_ASCII);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_MULTIPAGE0);
    _InitMultipage(hItem);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_TREEVIEW0);
    _InitTreeview(hItem);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_TREEVIEW1);
    WM_DisableWindow(hItem);
    break;
  case WM_PAINT:
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
  WM_HWIN hItem;
  WM_HWIN hDlg;
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  #if GUI_SUPPORT_CURSOR
    GUI_CURSOR_Show();
  #endif
  #if GUI_SUPPORT_MEMDEV
    WM_SetCreateFlags(WM_CF_MEMDEV);
  #endif
  hDlg = GUI_CreateDialogBox(_aMain, GUI_COUNTOF(_aMain), _cbMain, 0, 0, 0);
  hItem = WM_GetDialogItem(hDlg, GUI_ID_TREEVIEW0);
  if (hItem == 0) {
    WM_DeleteWindow(hDlg);
  } else {
    WM_SetFocus(hItem);
    while (1) {
      GUI_Delay(100);
    }
  }
}

/*************************** End of file ****************************/
