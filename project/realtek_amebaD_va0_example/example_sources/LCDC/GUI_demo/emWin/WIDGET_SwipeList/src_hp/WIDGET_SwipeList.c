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
File        : WIDGET_Spinbox.c
Purpose     : Shows how to use the SPINBOX widget.
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
---------------------------END-OF-HEADER------------------------------
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
#define RECOMMENDED_MEMORY (1024L * 10)

#define COLOR_GREEN     GUI_MAKE_COLOR(0x14FF39)  // Define a color
#define NUM_SEPARATORS  3                         // Number of available separators
#define NUM_ITEMS       5                         // Number of available items

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
//
// This array contains information about each item
//
static const char * paItemText[3][5] = {
  {
  "Wifi",
  "Mobile Data",
  "Bluetooth",
  "Hot Spot",
  "Mobil",
  },
  {
  "Brightness",
  "Background",
  "Idle",
  "Night Mode",
  "Font Size",
  },
  {
  "Account",
  "Sound",
  "Memory",
  "Alert",
  "Clock",
  },
};

//
// Information about the separators
//
static const char * paSeperatorText[] = {
  "Network",
  "Display",
  "Settings"
};

/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  WM_HWIN hSwipelist;
  WM_HWIN hItem;
  int     i;
  int     j;


  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  WM_MOTION_Enable(1);              // Enable motion support
  WM_SetBkWindowColor(GUI_BLACK);   // Set a default background color
  //
  // Set default color for selected items and separators
  //
  SWIPELIST_SetDefaultBkColor(SWIPELIST_CI_BK_ITEM_SEL, COLOR_GREEN);
  SWIPELIST_SetDefaultBkColor(SWIPELIST_CI_BK_SEP_ITEM, GUI_DARKGRAY);
  //
  // Create a swipelist
  //
  hSwipelist = SWIPELIST_CreateEx(10, 10, 200, 220, WM_HBKWIN, WM_CF_SHOW, 0, 0);
  WM_MOTION_SetMoveable(hSwipelist, WM_CF_MOTION_Y, 1);
  //
  // Add separators and five items under each
  //
  for (j = 0; j < NUM_SEPARATORS; j++) {
    SWIPELIST_AddSepItem(hSwipelist, paSeperatorText[j], 35);
    for (i = 0; i < NUM_ITEMS; i++) {
      SWIPELIST_AddItem(hSwipelist, paItemText[j][i], 35);
    }
  }
  //
  // Attaching a checkbox to each of the first five items
  //
  for (i = 0; i < 5; i++) {
    hItem = CHECKBOX_Create(0, 0, 15, 15, WM_HBKWIN, 0, WM_CF_SHOW);
    SWIPELIST_ItemAttachWindow(hSwipelist, 1 + i, hItem, 180, 10);
  }
  while (1) {
    GUI_Delay(100);
  }
}

/*************************** End of file ****************************/

