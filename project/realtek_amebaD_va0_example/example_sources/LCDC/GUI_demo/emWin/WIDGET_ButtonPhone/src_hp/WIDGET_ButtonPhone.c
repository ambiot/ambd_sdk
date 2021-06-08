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
File        : WIDGET_PhoneButton.c
Purpose     : Example demonstrating the use of a BUTTON widget
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/
#include "GUI.h"
#include "BUTTON.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*******************************************************************
*
*       static variables
*
********************************************************************
*/
/*******************************************************************
*
*       Bitmap data, 3 phone logos
*/
static const GUI_COLOR Colors[] = { GUI_MAKE_COLOR(0x000000), GUI_MAKE_COLOR(0xFFFFFF) };

static const GUI_LOGPALETTE Palette = { 2, 1, Colors };

static const unsigned char acPhone0[] = {
  ________, ________, ________, ________,
  ________, ________, ________, ________,
  ________, ________, ________, ________,
  ________, ________, ________, ________,
  ________, ________, ________, ________,
  ________, ________, ________, ________,
  ________, ________, ________, ________,
  ________, ________, ________, ________,
  ________, ________, ________, ________,
  ________, ________, ________, ________,
  ________, ________, ________, ________,
  _____XXX, XXXXXXXX, XXXXXXXX, XXX_____,
  ___XXXXX, XXXXXXXX, XXXXXXXX, XXXXX___,
  __XXXXXX, XXXXXXXX, XXXXXXXX, XXXXXX__,
  _XXXXXXX, X_______, _______X, XXXXXXX_,
  _XXXXXXX, X__XX___, ___XX__X, XXXXXXX_,
  _XXXXXXX, X__XX___, ___XX__X, XXXXXXX_,
  _XXXXXXX, X__XX___, ___XX__X, XXXXXXX_,
  ________, ___XX___, ___XX___, ________,
  _______X, XXXXXXXX, XXXXXXXX, X_______,
  ______XX, XXXXXXXX, XXXXXXXX, XX______,
  _____XXX, XXXX__X_, _X__XXXX, XXX_____,
  ____XXXX, XXXX__X_, _X__XXXX, XXXX____,
  ___XXXXX, XXXXXXXX, XXXXXXXX, XXXXX___,
  ___XXXXX, XXXX__X_, _X__XXXX, XXXXX___,
  ___XXXXX, XXXX__X_, _X__XXXX, XXXXX___,
  ___XXXXX, XXXXXXXX, XXXXXXXX, XXXXX___,
  ___XXXXX, XXXX__X_, _X__XXXX, XXXXX___,
  ___XXXXX, XXXX__X_, _X__XXXX, XXXXX___,
  ___XXXXX, XXXXXXXX, XXXXXXXX, XXXXX___,
  ___XXXXX, XXXXXXXX, XXXXXXXX, XXXXX___
};

static const unsigned char acPhone1[] = {
  ________, ________, ________, ________,
  ______XX, X_______, ________, ________,
  ____XXXX, XXXXX___, ________, ________,
  ____XXXX, XXXXXXX_, ________, ________,
  ___XXXXX, XXXXXXXX, X_______, ________,
  ___XXXXX, XXXXXXXX, XXX_____, ________,
  _____XXX, XXXX_XXX, XXXXX___, ________,
  _______X, XXXX___X, XXXXXXX_, ________,
  ________, _XX_____, _XXXXXXX, X_______,
  ________, ________, ___XXXXX, XXX_____,
  ________, ________, _____XXX, XXXXX___,
  ________, ________, _______X, XXXXXX__,
  ________, ________, ________, XXXXXXX_,
  ________, ________, ________, XXXXXXX_,
  ________, ________, _______X, XXXXXXXX,
  ________, ___XX___, ___XX__X, XXXXXXXX,
  ________, ___XX___, ___XX___, _XXXXXXX,
  ________, ___XX___, ___XX___, ___XXXX_,
  ________, ___XX___, ___XX___, _____XX_,
  _______X, XXXXXXXX, XXXXXXXX, X_______,
  ______XX, XXXXXXXX, XXXXXXXX, XX______,
  _____XXX, XXXX__X_, _X__XXXX, XXX_____,
  ____XXXX, XXXX__X_, _X__XXXX, XXXX____,
  ___XXXXX, XXXXXXXX, XXXXXXXX, XXXXX___,
  ___XXXXX, XXXX__X_, _X__XXXX, XXXXX___,
  ___XXXXX, XXXX__X_, _X__XXXX, XXXXX___,
  ___XXXXX, XXXXXXXX, XXXXXXXX, XXXXX___,
  ___XXXXX, XXXX__X_, _X__XXXX, XXXXX___,
  ___XXXXX, XXXX__X_, _X__XXXX, XXXXX___,
  ___XXXXX, XXXXXXXX, XXXXXXXX, XXXXX___,
  ___XXXXX, XXXXXXXX, XXXXXXXX, XXXXX___
};

static const unsigned char acPhone2[] = {
  ________, ________, ________, ________,
  ________, ________, _______X, XX______,
  ________, ________, ___XXXXX, XXXX____,
  ________, ________, _XXXXXXX, XXXX____,
  ________, _______X, XXXXXXXX, XXXXX___,
  ________, _____XXX, XXXXXXXX, XXXXX___,
  ________, ___XXXXX, XXX_XXXX, XXX_____,
  ________, _XXXXXXX, X___XXXX, X_______,
  _______X, XXXXXXX_, _____XX_, ________,
  _____XXX, XXXXX___, ________, ________,
  ___XXXXX, XXX_____, ________, ________,
  __XXXXXX, X_______, ________, ________,
  _XXXXXXX, ________, ________, ________,
  _XXXXXXX, ________, ________, ________,
  XXXXXXXX, X_______, ________, ________,
  XXXXXXXX, X__XX___, ___XX___, ________,
  XXXXXXX_, ___XX___, ___XX___, ________,
  _XXXX___, ___XX___, ___XX___, ________,
  _XX_____, ___XX___, ___XX___, ________,
  _______X, XXXXXXXX, XXXXXXXX, X_______,
  ______XX, XXXXXXXX, XXXXXXXX, XX______,
  _____XXX, XXXX__X_, _X__XXXX, XXX_____,
  ____XXXX, XXXX__X_, _X__XXXX, XXXX____,
  ___XXXXX, XXXXXXXX, XXXXXXXX, XXXXX___,
  ___XXXXX, XXXX__X_, _X__XXXX, XXXXX___,
  ___XXXXX, XXXX__X_, _X__XXXX, XXXXX___,
  ___XXXXX, XXXXXXXX, XXXXXXXX, XXXXX___,
  ___XXXXX, XXXX__X_, _X__XXXX, XXXXX___,
  ___XXXXX, XXXX__X_, _X__XXXX, XXXXX___,
  ___XXXXX, XXXXXXXX, XXXXXXXX, XXXXX___,
  ___XXXXX, XXXXXXXX, XXXXXXXX, XXXXX___
};

static const GUI_BITMAP bm_1bpp_0 = { 32, 31, 4, 1, acPhone0, &Palette};
static const GUI_BITMAP bm_1bpp_1 = { 32, 31, 4, 1, acPhone1, &Palette};
static const GUI_BITMAP bm_1bpp_2 = { 32, 31, 4, 1, acPhone2, &Palette};

/*******************************************************************
*
*       static code
*
********************************************************************
*/
/*******************************************************************
*
*       _Wait
*/
static int _Wait(int Delay) {
  int EndTime;
  int r;

  r = 1;
  EndTime = GUI_GetTime() + Delay;
  while (GUI_GetTime() < EndTime) {
    GUI_Exec();
    if (GUI_GetKey() == GUI_ID_OK) {
      r = 0;
      break;
    }
  }
  return r;
}

/*******************************************************************
*
*       _DemoButton
*/
static void _DemoButton(void) {
  BUTTON_Handle hButton;

  GUI_SetFont(&GUI_Font8x16);
  GUI_DispStringHCenterAt("Click on phone button...", 160,80);
  GUI_Delay(500);
  //
  // Create the button and modify its attributes
  //
  hButton = BUTTON_Create(142, 100, 36, 40, GUI_ID_OK, WM_CF_SHOW);
  BUTTON_SetBkColor (hButton, 1, GUI_RED);
  //
  // Loop until button is pressed
  //
  while (1) {
    BUTTON_SetBitmapEx(hButton, 0, &bm_1bpp_1, 2, 4);
    BUTTON_SetBitmapEx(hButton, 1, &bm_1bpp_1, 2, 4);
    if (!_Wait(50)) break;
    BUTTON_SetBitmapEx(hButton, 0, &bm_1bpp_0, 2, 4);
    BUTTON_SetBitmapEx(hButton, 1, &bm_1bpp_0, 2, 4);
    if (!_Wait(45)) break;
    BUTTON_SetBitmapEx(hButton, 0, &bm_1bpp_2, 2, 4);
    BUTTON_SetBitmapEx(hButton, 1, &bm_1bpp_2, 2, 4);
    if (!_Wait(50)) break;
    BUTTON_SetBitmapEx(hButton, 0, &bm_1bpp_0, 2, 4);
    BUTTON_SetBitmapEx(hButton, 1, &bm_1bpp_0, 2, 4);
    if (!_Wait(45)) break;
  }
  BUTTON_SetBitmapEx(hButton, 0, &bm_1bpp_1, 2, 4);
  BUTTON_SetBitmapEx(hButton, 1, &bm_1bpp_1, 2, 4);
  GUI_ClearRect(0, 80, 319, 120);
  GUI_DispStringHCenterAt("You have answered the telephone", 160, 145);
  GUI_Delay(2000);
  //
  // Delete button object
  //
  WM_DeleteWindow(hButton);
  GUI_ClearRect(0, 50, 319, 239);
  GUI_Delay(400);
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
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("WIDGET_PhoneButton - Sample", 160, 5);
  while (1) {
    _DemoButton();
  }
}

/*************************** End of file ****************************/

