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
File        : WIDGET_ProgbarCustomSkin.c
Purpose     : Example demonstrating the LISTBOX widget
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/
#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define RR_ADD  1   // Value which needs to substracted of a rounded rect to fit into a window
#define RADIUS  20  // Radius used for the rounded rects

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _CustomSkin
*
*  Function description
*    This function handles the drawing of the PROGBAR widget.
*
*  Parameters
*    pDrawItemInfo - A WIDGET_ITEM_DRAW_INFO structure which contains
*                    information about the window which should be drawn,
*                    which part and the properties of this part.
*/
static int _CustomSkin(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  GUI_RECT                Rect;
  GUI_RECT                UserRect;

  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_CREATE:
    return PROGBAR_DrawSkinFlex(pDrawItemInfo);
  case WIDGET_ITEM_DRAW_BACKGROUND:
    //
    // Receive the area of the PROGBAR widget
    //
    WM_GetClientRectEx(pDrawItemInfo->hWin, &Rect);
    //
    // Adapt the rectangle to be used for rounded rects
    //
    Rect.x0 += RR_ADD;
    Rect.y0 += RR_ADD;
    Rect.x1 -= RR_ADD;
    Rect.y1 -= RR_ADD;
    //
    // Draw a green rounded rect over the complete area, this gets (partially) overwritten by a white one
    //
    GUI_SetColor(GUI_GREEN);
    GUI_FillRoundedRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1, RADIUS);
    //
    // Set a user cliprect
    //
    UserRect.x0 = pDrawItemInfo->x0;
    UserRect.y0 = pDrawItemInfo->y0;
    UserRect.x1 = pDrawItemInfo->x1;
    UserRect.y1 = pDrawItemInfo->y1;
    WM_SetUserClipRect(&UserRect);
    //
    // Draw a white rounded rect over the whole PROGBAR area, but the drawing will be visible only in
    // the area of the cliprect. The size of the cliprect will decrease over time and the white rect
    // will get smaller.
    //
    GUI_SetColor(GUI_WHITE);
    GUI_FillRoundedRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1, RADIUS);
    //
    // Very important, restore the the clipping area
    //
    WM_SetUserClipRect(NULL);
    //
    // Almost done, just a draw a red frame over the whole area
    //
    GUI_SetColor(GUI_RED);
    GUI_DrawRoundedRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1, RADIUS);
    return 0;
  case WIDGET_ITEM_DRAW_FRAME:
    //
    // We handle the frame on our own, so we return 0
    //
    return 0;
  case WIDGET_ITEM_DRAW_TEXT:
    //
    // Handle the drawing of the text by the default skinning routine.
    // This case could be commented. Just left it here to show this command
    // is available.
    //
    return PROGBAR_DrawSkinFlex(pDrawItemInfo);
  default:
    //
    // Anything not handled here will be handled by the default skinning routine.
    //
    return PROGBAR_DrawSkinFlex(pDrawItemInfo);
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
  PROGBAR_Handle hProg;
  int            Min;
  int            Max;
  int            Value;

  //
  // Set up some variables
  //
  Min   = 0;
  Max   = 100;
  Value = Min;
  //
  // Enable automatic use of memory devices
  //
  
  //
  // Initialize GUI
  //
  //
  // Set back ground color for the desktop window
  //
  WM_SetDesktopColor(GUI_BLACK);
  //
  // Create a progressbar
  //
  hProg = PROGBAR_CreateEx(10, 10, 150, 100, WM_HBKWIN, WM_CF_SHOW, PROGBAR_CF_HORIZONTAL, 0);
  //
  // Set minimal and maximal value of the PROGBAR widget
  //
  PROGBAR_SetMinMax(hProg, Min, Max);
  //
  // Set a custom skin, see above
  //
  PROGBAR_SetSkin(hProg, _CustomSkin);
  //
  // Set back ground of the PROGBAR widget to invisible
  //
  WM_SetHasTrans(hProg);
  while (1) {
    PROGBAR_SetValue(hProg, Value);
    Value++;
    if (Value > Max) {
      Value = Min;
    }
    GUI_Delay(50);
  }
}

/*************************** End of file ****************************/
