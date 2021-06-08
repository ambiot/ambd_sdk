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
File        : WIDGET_Menu.c
Purpose     : Shows how to work with menu widget
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include <stdio.h>
#include "GUI.h"
#include "DIALOG.h"
#include "MENU.h"
#include "MESSAGEBOX.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
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
#define RECOMMENDED_MEMORY (1024L * 10)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static WM_HWIN _hMenu;
static WM_HWIN _hText;
static WM_HWIN _hFrame;

static char * _paDescription[] = {
  "Creates a new file",
  "Opens an existing file",
  "Closes the file",
  "Quits the application",
  " ",
  "Opens file 1",
  "Opens file 2",
  "Opens file 3",
  "Opens file 4",
  "Undoes the last action",
  "Redoes the previously undone action",
  "Copies to clipboard",
  "Inserts contents of clipboard",
  "Deletes the selection",
  "Displays program information"
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
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
*
* Function description
*   Creates the menu widget
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
  _AddMenuItem(hMenuRecent, 0,           "File 1",   ID_MENU_RECENT_0,    0);
  _AddMenuItem(hMenuRecent, 0,           "File 2",   ID_MENU_RECENT_1,    0);
  _AddMenuItem(hMenuRecent, 0,           "File 3",   ID_MENU_RECENT_2,    0);
  _AddMenuItem(hMenuRecent, 0,           "File 4",   ID_MENU_RECENT_3,    0);
  //
  // Add menu items to menu 'File'
  //
  _AddMenuItem(hMenuFile,   0,           "New",      ID_MENU_FILE_NEW,    0);
  _AddMenuItem(hMenuFile,   0,           "Open",     ID_MENU_FILE_OPEN,   0);
  _AddMenuItem(hMenuFile,   0,           "Close",    ID_MENU_FILE_CLOSE,  MENU_IF_DISABLED);
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
  FRAMEWIN_AddMenu(hParent, hMenu);
  return hMenu;
}

/*********************************************************************
*
*       _DrawGradientV
*
* Function description
*   Draws a vertical gradient
*/
static void _DrawGradientV(int x0, int y0, int x1, int y1, GUI_COLOR Color0, GUI_COLOR Color1) {
  int r0;
  int g0;
  int b0;
  int r1;
  int g1;
  int b1;
  int y;
  int ySize;
  int r;
  int g;
  U32 a;
  I32 b;
  int Diff;

  ySize = y1 - y0 + 1;
  a     = 
  r0    = (Color0 >>  0) & 0x000000ff;
  g0    = (Color0 >>  8) & 0x000000ff;
  b0    = (Color0 >> 16) & 0x000000ff;
  r1    = (Color1 >>  0) & 0x000000ff;
  g1    = (Color1 >>  8) & 0x000000ff;
  b1    = (Color1 >> 16) & 0x000000ff;
  for (y = y0; y <= y1; y++) {
    GUI_COLOR Color;
    Diff = y - y0;
    r = r0 + (r1 - r0) * Diff / ySize;
    g = g0 + (g1 - g0) * Diff / ySize;
    b = b0 + (b1 - b0) * Diff / ySize;
    Color = r | (g << 8) | (b << 16);
    #if (GUI_USE_ARGB == 1)
      Color |= 0xFF000000;
    #endif
    GUI_SetColor(Color);
    GUI_DrawHLine(y, x0, x1);
  }
}

/*********************************************************************
*
*       _MessageBox
*
* Function description
*   Creates and executes a modal message box
*/
static void _MessageBox(const char * pText, const char * pCaption) {
  WM_HWIN hBox;

  hBox = MESSAGEBOX_Create(pText, pCaption, GUI_MESSAGEBOX_CF_MODAL | GUI_MESSAGEBOX_CF_MOVEABLE);
  WM_SetStayOnTop(hBox, 1);
  WM_BringToTop(hBox);
  GUI_ExecCreatedDialog(hBox);
  WM_SetFocus(_hMenu);
  MENU_SetSel(_hMenu, -1);
}

/*********************************************************************
*
*       _cbClient
*
* Function description
*   Callback routine of client window which 'owns' the menu widget
*   and the status bar
*/
static void _cbClient(WM_MESSAGE * pMsg) {
  char acBuffer[50];
  int             Index;
  int             xSize;
  int             ySize;
  int             xPos;
  int             yPos;
  WM_HWIN         hWin;
  WM_HWIN         hClient;
  MENU_MSG_DATA * pData;
  MENU_ITEM_DATA  Data;

  hWin = pMsg->hWin;
  hClient = WM_GetClientWindow(hWin);
  xSize = WM_GetWindowSizeX(hClient);
  ySize = WM_GetWindowSizeY(hClient);
  switch (pMsg->MsgId) {
  case WM_SIZE:
    //
    // Adjusts text widget on changinmg the size
    //
    xPos = WM_GetWindowOrgX(hClient);
    yPos = WM_GetWindowOrgY(hClient);
    WM_SetWindowPos(_hText, xPos + 4, yPos + ySize - 10, xSize, 10);
    TEXT_SetText(_hText, "Ready");
    break;
  case WM_PAINT:
    //
    // Draws the background of the client window
    //
    _DrawGradientV(0, 0, xSize - 1, ySize - 12 - 1, GUI_WHITE, GUI_LIGHTBLUE);
    GUI_SetColor(GUI_LIGHTGRAY);
    GUI_FillRect(0, ySize - 12, xSize - 1, ySize - 1);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetColor(GUI_BLACK);
    GUI_SetFont(&GUI_Font24B_ASCII);
    GUI_DispStringHCenterAt(
      "MENU widget sample"
      , xSize / 2, 40);
    GUI_SetFont(&GUI_Font16B_ASCII);
    GUI_DispStringHCenterAt(
      "The sample shows how to use the MENU\n"
      "widget. Use the keyboard or the pointer\n"
      "input device for playing with the widget.\n"
      "On highlighting a menu item the status\n"
      "bar shows a small description. On selecting\n"
      "a menu item a message box will be shown."
      , xSize / 2, 70);
    break;
  case WM_MENU:
    pData = (MENU_MSG_DATA*)pMsg->Data.p;
    switch (pData->MsgType) {
    case MENU_ON_ITEMPRESSED:
      //
      // This message is send regardless of the item state is disabled or not
      //
      MENU_GetItem(pMsg->hWinSrc, pData->ItemId, &Data);
      if (Data.Flags & MENU_IF_DISABLED) {
        _MessageBox("The pressed item was disabled", "Message");
      }
      break;
    case MENU_ON_ITEMACTIVATE:
      //
      // This message is send on highlighting a menu item
      //
      Index = pData->ItemId - ID_MENU_FILE_NEW;
      if (Index >= 0) {
        TEXT_SetText(_hText, _paDescription[pData->ItemId - ID_MENU_FILE_NEW]);
      } else {
        TEXT_SetText(_hText, "Ready");
      }
      break;
    case MENU_ON_ITEMSELECT:
      //
      // This message is send only if an enabled item has been selected
      //
      sprintf(acBuffer, "ID of the selected\nitem is 0x%X", pData->ItemId);
      _MessageBox(acBuffer, "Message");
      break;
    }
  }
  WM_DefaultProc(pMsg);
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
  int     xSize;
  int     ySize;
  WM_HWIN hClient;
 
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  WM_SetDesktopColor(GUI_BLACK);
  MENU_SetDefaultEffect(&WIDGET_Effect_3D1L);
  //
  // Create frame window
  //
  _hFrame = FRAMEWIN_CreateEx(10, 10, 300, 220, WM_HBKWIN, WM_CF_SHOW, FRAMEWIN_CF_MOVEABLE, 0, "Application with menu", _cbClient);
  FRAMEWIN_SetFont(_hFrame, &GUI_Font13_ASCII);
  FRAMEWIN_AddMaxButton(_hFrame, FRAMEWIN_BUTTON_RIGHT, 0);
  FRAMEWIN_AddMinButton(_hFrame, FRAMEWIN_BUTTON_RIGHT, 2);
  //
  // Create menu widget
  //
  _hMenu = _CreateMenu(_hFrame);
  //
  // Create text widget as simple status bar
  //
  hClient = WM_GetClientWindow(_hFrame);
  xSize   = WM_GetWindowSizeX(hClient);
  ySize   = WM_GetWindowSizeY(hClient);
  _hText  = TEXT_CreateEx(4, ySize - 10, xSize, 10, hClient, WM_CF_SHOW, 0, GUI_ID_TEXT0, "Ready");
  TEXT_SetFont(_hText, &GUI_Font8_ASCII);
  //
  // Set keyboard focus to menu widget
  //
  WM_SetFocus(_hMenu);
  MENU_SetSel(_hMenu, -1);
  while (1) {
    GUI_Delay(100);
  }
}

/*************************** End of file ****************************/
