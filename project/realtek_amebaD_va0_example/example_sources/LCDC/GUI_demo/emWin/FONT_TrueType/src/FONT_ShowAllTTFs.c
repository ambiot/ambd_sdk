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
File        : FONT_ShowAllTTFs.c
Purpose     : Demonstrates the use of TTF font files
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - (x)

----------------------------------------------------------------------
*/

#ifndef SKIP_TEST

#include <stdio.h>
#include "GUI.h"

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

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static unsigned     _aHeight  [] = {16, 20, 32, 48};   // Array of heights used to show text
static GUI_TTF_CS   _aCS      [GUI_COUNTOF(_aHeight)]; // Each GUI font needs its own GUI_TTF_CS structure
static GUI_FONT     _aFont    [GUI_COUNTOF(_aHeight)]; // Array of GUI fonts
static char         _acFamily [200];
static char         _acStyle  [200];

extern const unsigned char _acTimesNewRoman[14028UL + 1];


/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _ShowText
*/
static void _ShowText(void) {
  int i;

  GUI_Clear();
  i = 0;
  GUI_TTF_GetFamilyName(&_aFont[i], _acFamily, sizeof(_acFamily));
  GUI_TTF_GetStyleName(&_aFont[i],  _acStyle,  sizeof(_acStyle));
  GUI_SetFont(&GUI_Font20_1);
  GUI_DispString(_acFamily);
  GUI_DispString(", ");
  GUI_DispString(_acStyle);
  GUI_DispNextLine();
  GUI_DrawHLine(GUI_GetDispPosY(), 0, 0xfff);
  GUI_SetFont(&_aFont[i]);
  GUI_DispString("abcdefghijklmnopqrstuvwxyz\n");
  GUI_DispString("ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
  GUI_DispString("123456789.:,;(:*!?')\n");
  GUI_DrawHLine(GUI_GetDispPosY(), 0, 0xfff);
  for (i = 0; i < GUI_COUNTOF(_aHeight); i++) {
    GUI_SetFont(&_aFont[i]);
    GUI_DispString("The quick brown fox jumps over the lazy dog. 1234567890\n");
  }
  GUI_Delay(1000);
}

/*********************************************************************
*
*       _CreateFonts
*/
static int _CreateFonts(const U8 * pData, U32 NumBytes) {
  int i;
  GUI_TTF_DATA TTF_Data;        // Only one GUI_TTF_DATA structure is used per font face

  TTF_Data.pData    = pData;    // Set pointer to file data
  TTF_Data.NumBytes = NumBytes; // Set size of file
  for (i = 0; i < GUI_COUNTOF(_aHeight); i++) {
    //
    // Initialize GUI_TTF_CS members
    //
    _aCS[i].PixelHeight = _aHeight[i];
    _aCS[i].pTTF        = &TTF_Data;
    //
    // Create GUI font
    //
    if (GUI_TTF_CreateFontAA(&_aFont[i], &_aCS[i])) {
      return 1;
    }
  }
  return 0;
}

/*********************************************************************
*
*       _cbFontDemo
*
* Function description
*   The function uses the given pointer to a true type font for creating
*   a couple of GUI fonts and showing the outline of the TTF font.
*
* Parameters:
*   pData    - Location of font file
*   NumBytes - Size of font file
*/
static void _cbFontDemo(const U8 * pData, U32 NumBytes) {
  _CreateFonts(pData, NumBytes); // Create fonts
  _ShowText();                   // Show some text
  GUI_TTF_DestroyCache();        // Clear the TTF cache
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
  char acPath[200];

  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  //
  // Set colors and text mode
  //
  GUI_SetBkColor(GUI_WHITE);
  GUI_SetColor(GUI_BLACK);
  GUI_SetTextMode(GUI_TM_TRANS);
  //
  // Call _cbFontDemo for ttf file
  //
  _cbFontDemo(_acTimesNewRoman, sizeof(_acTimesNewRoman));

  while (1) ;
}

#endif

/*************************** End of file ****************************/
