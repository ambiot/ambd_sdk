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
File        : DIALOG_MessageBoxUser.c
Purpose     : Shows how to use a customized message box
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include "DIALOG.h"
#include "MESSAGEBOX.h"

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
static GUI_CONST_STORAGE unsigned char _ac_Font24_0043[ 48] = { // Code 0043, LATIN CAPITAL LETTER C
  ________,________,
  ________,________,
  _____XX_,________,
  ____X__X,________,
  ___X____,X_______,
  ___X____,X_______,
  __X__X__,X_______,
  __X__X_X,________,
  __X___X_,________,
  __X_____,________,
  _X______,________,
  _X______,________,
  _X______,________,
  _X____X_,________,
  __X___X_,________,
  __X__X__,________,
  ___XX___,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________};

static GUI_CONST_STORAGE unsigned char _ac_Font24_004B[ 48] = { // Code 004B, LATIN CAPITAL LETTER K
  ________,________,
  ________,________,
  ___X____,_X______,
  __X_X___,_X______,
  __X__X__,XX______,
  __X__X__,X_______,
  __X__X_X,________,
  ___X_XX_,________,
  ____XXX_,________,
  ____XX__,________,
  ____X_X_,________,
  ____X_X_,________,
  ___X__X_,________,
  ___X__X_,________,
  ___X__X_,X_______,
  X_X___X_,X_______,
  _XX___XX,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________};

static GUI_CONST_STORAGE unsigned char _ac_Font24_004D[ 48] = { // Code 004D, LATIN CAPITAL LETTER M
  ________,________,
  ________,________,
  _______X,___X____,
  _XXX__X_,X_X_X___,
  _X__XX__,XX__X___,
  _X__XX__,XX___X__,
  _X__X___,XX___X__,
  __X_X___,X___X___,
  ____X___,X___X___,
  ___XX___,X___X___,
  ___X____,X___X___,
  ___X___X,____X___,
  ___X___X,____X___,
  ___X___X,___X____,
  ___X___X,___X_X__,
  __X____X,___X_X__,
  ________,____X___,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________};

static GUI_CONST_STORAGE unsigned char _ac_Font24_004F[ 48] = { // Code 004F, LATIN CAPITAL LETTER O
  ________,________,
  ________,________,
  _____XX_,________,
  ____XX_X,________,
  ___XX__X,________,
  ___XX___,X_______,
  __X_X___,X_______,
  __X__X__,X_______,
  __X__X__,X_______,
  __X__X__,X_______,
  _X____X_,X_______,
  _X_____X,________,
  _X_____X,X_______,
  _X_____X,________,
  __X___X_,________,
  __X__X__,________,
  ___XX___,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________};

static GUI_CONST_STORAGE unsigned char _ac_Font24_0061[ 24] = { // Code 0061, LATIN SMALL LETTER A
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  __XX____,
  _X_XX___,
  X___X___,
  X___X___,
  X__XX_X_,
  X__XX_X_,
  _XX_XX__,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

static GUI_CONST_STORAGE unsigned char _ac_Font24_0065[ 24] = { // Code 0065, LATIN SMALL LETTER E
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX_____,
  X_X_____,
  X_X_____,
  X_X_____,
  XX_X____,
  X__X____,
  _XX_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

static GUI_CONST_STORAGE unsigned char _ac_Font24_0067[ 24] = { // Code 0067, LATIN SMALL LETTER G
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  __XX____,
  _X_XX___,
  X___X___,
  X___X___,
  X___XX__,
  X__X_X__,
  _XXXX___,
  ___X____,
  __XX____,
  _XX_____,
  X_X_____,
  X_X_____,
  X_X_____,
  XX______};

static GUI_CONST_STORAGE unsigned char _ac_Font24_0069[ 24] = { // Code 0069, LATIN SMALL LETTER I
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX_____,
  ________,
  ________,
  _X______,
  _X______,
  X_______,
  X_______,
  X_X_____,
  X_X_____,
  XX______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

static GUI_CONST_STORAGE unsigned char _ac_Font24_006E[ 24] = { // Code 006E, LATIN SMALL LETTER N
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  __X_XX__,
  _XXX_X__,
  X_XX_X__,
  X_X__X__,
  __X__X_X,
  __X__X_X,
  _____XX_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

static GUI_CONST_STORAGE unsigned char _ac_Font24_006F[ 24] = { // Code 006F, LATIN SMALL LETTER O
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  __XX____,
  _XXX____,
  X_X_X___,
  X_X_X___,
  X__XXX__,
  X__X____,
  _XX_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

static GUI_CONST_STORAGE unsigned char _ac_Font24_0070[ 24] = { // Code 0070, LATIN SMALL LETTER P
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX____,
  _X__X___,
  XX__X___,
  XX__X___,
  X___XX__,
  XX__XX__,
  X_XXX___,
  X_______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

static GUI_CONST_STORAGE unsigned char _ac_Font24_0073[ 24] = { // Code 0073, LATIN SMALL LETTER S
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _X______,
  _X______,
  X_X_____,
  X_X_____,
  ___XX___,
  X__XX___,
  _XXX____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

static GUI_CONST_STORAGE unsigned char _ac_Font24_0074[ 24] = { // Code 0074, LATIN SMALL LETTER T
  ________,
  ________,
  ___X____,
  ___X____,
  ___X____,
  __X_____,
  __X_____,
  __X_____,
  _XX_____,
  _XX_____,
  _X______,
  _X______,
  XX______,
  XX______,
  X__X____,
  X__X____,
  _XX_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

static GUI_CONST_STORAGE GUI_CHARINFO _Font24_CharInfo[13] = {
   {   9,   9,  2, _ac_Font24_0043 } // Code 0043
  ,{  10,  10,  2, _ac_Font24_004B } // Code 004B
  ,{  14,  14,  2, _ac_Font24_004D } // Code 004D
  ,{   9,   9,  2, _ac_Font24_004F } // Code 004F
  ,{   7,   7,  1, _ac_Font24_0061 } // Code 0061
  ,{   4,   4,  1, _ac_Font24_0065 } // Code 0065
  ,{   7,   7,  1, _ac_Font24_0067 } // Code 0067
  ,{   3,   3,  1, _ac_Font24_0069 } // Code 0069
  ,{   8,   8,  1, _ac_Font24_006E } // Code 006E
  ,{   6,   6,  1, _ac_Font24_006F } // Code 006F
  ,{   7,   7,  1, _ac_Font24_0070 } // Code 0070
  ,{   5,   5,  1, _ac_Font24_0073 } // Code 0073
  ,{   4,   4,  1, _ac_Font24_0074 } // Code 0074
};

static GUI_CONST_STORAGE GUI_FONT_PROP _Font24_Prop10 = {
   0x0073 // first character
  ,0x0074 // last character 
  ,&_Font24_CharInfo[ 11] // address of first character
  ,(GUI_CONST_STORAGE GUI_FONT_PROP *)0 // pointer to next GUI_FONT_PROP
};

static GUI_CONST_STORAGE GUI_FONT_PROP _Font24_Prop9 = {
   0x006E                 // first character
  ,0x0070                 // last character 
  ,&_Font24_CharInfo[  8] // address of first character
  ,&_Font24_Prop10        // pointer to next GUI_FONT_PROP
};

static GUI_CONST_STORAGE GUI_FONT_PROP _Font24_Prop8 = {
   0x0069                 // first character
  ,0x0069                 // last character 
  ,&_Font24_CharInfo[  7] // address of first character
  ,&_Font24_Prop9         // pointer to next GUI_FONT_PROP
};

static GUI_CONST_STORAGE GUI_FONT_PROP _Font24_Prop7 = {
   0x0067                 // first character
  ,0x0067                 // last character 
  ,&_Font24_CharInfo[  6] // address of first character
  ,&_Font24_Prop8         // pointer to next GUI_FONT_PROP
};

static GUI_CONST_STORAGE GUI_FONT_PROP _Font24_Prop6 = {
   0x0065                 // first character
  ,0x0065                 // last character 
  ,&_Font24_CharInfo[  5] // address of first character
  ,&_Font24_Prop7         // pointer to next GUI_FONT_PROP
};

static GUI_CONST_STORAGE GUI_FONT_PROP _Font24_Prop5 = {
   0x0061                 // first character
  ,0x0061                 // last character 
  ,&_Font24_CharInfo[  4] // address of first character
  ,&_Font24_Prop6         // pointer to next GUI_FONT_PROP
};

static GUI_CONST_STORAGE GUI_FONT_PROP _Font24_Prop4 = {
   0x004F                 // first character
  ,0x004F                 // last character 
  ,&_Font24_CharInfo[  3] // address of first character
  ,&_Font24_Prop5         // pointer to next GUI_FONT_PROP
};

static GUI_CONST_STORAGE GUI_FONT_PROP _Font24_Prop3 = {
   0x004D                 // first character
  ,0x004D                 // last character 
  ,&_Font24_CharInfo[  2] // address of first character
  ,&_Font24_Prop4         // pointer to next GUI_FONT_PROP
};

static GUI_CONST_STORAGE GUI_FONT_PROP _Font24_Prop2 = {
   0x004B                 // first character
  ,0x004B                 // last character 
  ,&_Font24_CharInfo[  1] // address of first character
  ,&_Font24_Prop3         // pointer to next GUI_FONT_PROP
};

static GUI_CONST_STORAGE GUI_FONT_PROP _Font24_Prop1 = {
   0x0043                 // first character
  ,0x0043                 // last character 
  ,&_Font24_CharInfo[  0] // address of first character
  ,&_Font24_Prop2         // pointer to next GUI_FONT_PROP
};

static GUI_CONST_STORAGE GUI_FONT GUI_Font24 = {
   GUI_FONTTYPE_PROP // type of font   
  ,24                // height of font 
  ,24                // space of font y
  ,1                 // magnification x
  ,1                 // magnification y
  ,{&_Font24_Prop1}
  ,17                // Baseline
  ,7                 // Height of lowercase characters
  ,14                // Height of capital characters
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _CreateMessageBox
*/
static WM_HWIN _CreateMessageBox(const char * sMessage, const char * sCaption, int Flags, const GUI_FONT * pFont) {
  WM_HWIN  hWin;
  WM_HWIN  hItem;
  GUI_RECT Rect;

  hWin = MESSAGEBOX_Create(sMessage, sCaption, Flags);
  //
  // Change font of message box window
  //
  FRAMEWIN_SetFont(hWin, pFont);
  //
  // Adjust size
  //
  WM_GetWindowRectEx(hWin, &Rect);
  WM_SetWindowPos(hWin, Rect.x0 - 15, 
                        Rect.y0 - 15, 
                        Rect.x1 - Rect.x0 + 1 + 30, 
                        Rect.y1 - Rect.y0 + 1 + 30);
  //
  // Change font of button widget
  //
  hItem = WM_GetDialogItem(hWin, GUI_ID_OK);
  BUTTON_SetFont(hItem, pFont);
  //
  // Adjust size of button widget
  //
  WM_GetWindowRectEx(hItem, &Rect);
  WM_SetWindowPos(hItem, Rect.x0, 
                         Rect.y0 + 10, 
                         Rect.x1 - Rect.x0 + 1 + 30, 
                         Rect.y1 - Rect.y0 + 1 +  5);
  //
  // Change font of text widget
  //
  hItem = WM_GetDialogItem(hWin, GUI_ID_TEXT0);
  TEXT_SetFont(hItem, pFont);
  //
  // Adjust size text widget
  //
  WM_GetWindowRectEx(hItem, &Rect);
  WM_SetWindowPos(hItem, Rect.x0, 
                         Rect.y0, 
                         Rect.x1 - Rect.x0 + 1 + 30, 
                         Rect.y1 - Rect.y0 + 1 + 12);
  return hWin;
}

/*********************************************************************
*
*       _EnableSkinning
*/
static void _EnableSkinning(void) {
  FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
  BUTTON_SetDefaultSkin  (BUTTON_SKIN_FLEX);
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
  _EnableSkinning();
  while (1) {
    GUI_SetFont(&GUI_Font20B_ASCII);
    GUI_DispStringHCenterAt("Application defined MESSAGEBOX", 160, 5);
    GUI_ExecCreatedDialog(_CreateMessageBox("Message", "Caption", 0, &GUI_Font24));
    GUI_Clear();
    GUI_Delay(1000);
  }
}

/*************************** End of file ****************************/
