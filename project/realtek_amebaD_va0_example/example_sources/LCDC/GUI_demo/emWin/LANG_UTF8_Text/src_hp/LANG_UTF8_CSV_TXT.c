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
File        : LANG_UTF8_CSV_TXT.c
Purpose     : Sample application which shows how language resource files
              can be used to display different languages using UTF-8.

              If executed in the emWin simulation (WIN32) environment,
              the application creates a CSV file and a text file in the
              same location the executable lies in. These files then
              are used to display texts written in different languages.

              If  executed on target hardware the application uses the
              arrays containing the file data directly.
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#ifndef SKIP_TEST

/*********************************************************************
*
*       Includes
*
**********************************************************************
*/
#ifdef WIN32
  #include <windows.h>   // File handling
#endif

#include <stdio.h>       // Definition of NULL
#include "GUI.h"
#include "GUI_Debug.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define HEIGHT_HEADLINE_1  40
#define HEIGHT_HEADLINE_2  20
#define HEIGHT_TOP         (HEIGHT_HEADLINE_1 + HEIGHT_HEADLINE_2)
#define NUM_LANGUAGES      3
#define NUM_ITEMS          5
#define NUM_FILES          2
#define BORDER_SIZE        2
#define XSIZE_MAX          480
#define YSIZE_MAX          360
#define XSIZE_MIN          320
#define YSIZE_MIN          240

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 10)

/*********************************************************************
*
*       _GUI_FontJapanese_headline16
*
**********************************************************************
*/
//
// Start of unicode area <CJK Unified Ideographs>
//
static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_headline16_65E5[ 28] = { // Code 65E5
  XX______,XX______,
  XXXXXXXX,XXX_____,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XXXXXXXX,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XXXXXXXX,XX______,
  XX______,XX______,
  XX______,________};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_headline16_672C[ 30] = { // Code 672C
  _______X,XX______,
  _______X,X_______,
  _______X,X____XX_,
  XXXXXXXX,XXXXXXXX,
  ______XX,XX______,
  _____XXX,XXX_____,
  _____XXX,XXX_____,
  ____XX_X,X_XX____,
  ___XX__X,X__XX___,
  __XX___X,XXX_XX__,
  _XX_XXXX,XXXX_XX_,
  XX_____X,X_____XX,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_headline16_8A9E[ 30] = { // Code 8A9E
  ___XX___,____XX__,
  _XXXXXXX,XXXXXXX_,
  ________,_XX_____,
  ____XX__,_XX_XX__,
  XXXXXXXX,XXXXXXX_,
  ________,XX__XX__,
  _XXXXX__,XX__XXXX,
  ______XX,XXXXXXXX,
  _XXXXX__,________,
  _______X,XXXXXX__,
  _XXXXX_X,X___XX__,
  _XX_XX_X,X___XX__,
  _XX_XX_X,X___XX__,
  _XXXXX_X,XXXXXX__,
  _XX_XX_X,X___XX__};

static GUI_CONST_STORAGE GUI_CHARINFO_EXT _GUI_FontJapanese_headline16_CharInfo[3] = {
   {  11,  14,   3,   1,  17, _acGUI_FontJapanese_headline16_65E5 } // Code 65E5
  ,{  16,  15,   0,   0,  17, _acGUI_FontJapanese_headline16_672C } // Code 672C
  ,{  16,  15,   0,   0,  17, _acGUI_FontJapanese_headline16_8A9E } // Code 8A9E
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_headline16_Prop3 = {
   0x8A9E                                      // first character
  ,0x8A9E                                      // Last character 
  ,&_GUI_FontJapanese_headline16_CharInfo[  2] // Address of first character
  ,(GUI_CONST_STORAGE GUI_FONT_PROP_EXT *)0    // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_headline16_Prop2 = {
   0x672C                                      // first character
  ,0x672C                                      // Last character 
  ,&_GUI_FontJapanese_headline16_CharInfo[  1] // Address of first character
  ,&_GUI_FontJapanese_headline16_Prop3         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_headline16_Prop1 = {
   0x65E5                                      // first character
  ,0x65E5                                      // Last character 
  ,&_GUI_FontJapanese_headline16_CharInfo[  0] // Address of first character
  ,&_GUI_FontJapanese_headline16_Prop2         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT _GUI_FontJapanese_headline16 = {
   GUI_FONTTYPE_PROP_EXT // type of font   
  ,16                    // Height of font 
  ,16                    // Space of font y
  ,1                     // Magnification x
  ,1                     // Magnification y
  ,{ &_GUI_FontJapanese_headline16_Prop1 }
  ,14                    // Baseline
  ,8                     // Height of lowercase characters
  ,13                    // Height of capital characters
};

/*********************************************************************
*
*       _GUI_FontJapanese_text16
*
**********************************************************************
*/
//
// Start of unicode area <Basic Latin>
//
static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_0057[ 13] = { // Code 0057, LATIN CAPITAL LETTER W
  XX_X_XX_,
  X__X__X_,
  X__X__X_,
  X__X__X_,
  X_X_X_X_,
  X_X_X_X_,
  X_X_X_X_,
  X_X_X_X_,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_0065[  8] = { // Code 0065, LATIN SMALL LETTER E
  __XX____,
  _X__X___,
  X____X__,
  XXXXXX__,
  X_______,
  X_______,
  _X___X__,
  __XXX___};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_0069[ 12] = { // Code 0069, LATIN SMALL LETTER I
  _X______,
  _X______,
  ________,
  ________,
  XX______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  XXX_____};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_006D[  8] = { // Code 006D, LATIN SMALL LETTER M
  X_X_XX__,
  XX_X__X_,
  X__X__X_,
  X__X__X_,
  X__X__X_,
  X__X__X_,
  X__X__X_,
  X_XX_XX_};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_006E[  8] = { // Code 006E, LATIN SMALL LETTER N
  XX_XX___,
  _XX__X__,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  XXX_XXX_};

//
// Start of unicode area <CJK Symbols and Punctuation>
//
static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_3005[ 20] = { // Code 3005, IDEOGRAPHIC ITERATION MARK
  ____XX__,________,
  ____X___,_X______,
  ___XXXXX,XXX_____,
  ___X____,_X______,
  __X_____,X_______,
  _X_____X,________,
  X__XX_X_,________,
  _____XX_,________,
  ______XX,________,
  _______X,________};

//
// Start of unicode area <Hiragana>
//
static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_3044[ 22] = { // Code 3044, HIRAGANA LETTER I
  X_______,________,
  _X______,_XX_____,
  _X______,___X____,
  _X______,____X___,
  _X______,_____X__,
  _X____X_,_____X__,
  _X___X__,_____X__,
  __X__X__,________,
  __X_X___,________,
  ___XX___,________,
  ____X___,________};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_3057[ 26] = { // Code 3057, HIRAGANA LETTER SI
  XX______,________,
  _XX_____,________,
  _X______,________,
  _X______,________,
  _X______,________,
  _X______,________,
  _X______,________,
  _X______,________,
  _X______,__X_____,
  _X______,_X______,
  _X______,X_______,
  __X___XX,________,
  ___XXX__,________};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_3059[ 30] = { // Code 3059, HIRAGANA LETTER SU
  _______X,X_______,
  ________,XX______,
  ________,X___X___,
  XX__XXXX,XXXXXX__,
  _XXX____,X_______,
  _____XX_,X_______,
  ____X__X,X_______,
  ____X___,X_______,
  ____X___,X_______,
  ____X__X,X_______,
  _____XX_,X_______,
  _______X,________,
  _______X,________,
  ______X_,________,
  _____X__,________};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_3066[ 24] = { // Code 3066, HIRAGANA LETTER TE
  X____XXX,XXXXX___,
  _XXXX___,XX______,
  _______X,________,
  ______X_,________,
  _____X__,________,
  _____X__,________,
  ____X___,________,
  ____X___,________,
  ____X___,________,
  _____X__,________,
  _____XX_,_X______,
  _______X,XXX_____};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_306A[ 28] = { // Code 306A, HIRAGANA LETTER NA
  __XX____,________,
  ___X____,________,
  X__X_XX_,_XX_____,
  _XXXXX__,___X____,
  __X_____,____X___,
  __X_____,_X_XX___,
  __X_____,X_______,
  _X______,X_______,
  _X______,X_______,
  XX______,X_______,
  X___XXXX,XX______,
  ___X____,X_XX____,
  ___X____,X__XX___,
  ____XXXX,________};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_306B[ 26] = { // Code 306B, HIRAGANA LETTER NI
  XX______,________,
  _XX_____,________,
  _X______,XXXX____,
  _X____XX,________,
  X_______,________,
  X_______,________,
  X_______,________,
  X__X____,________,
  X__X_X__,________,
  X_X__X__,________,
  X_X___XX,________,
  _XX_____,XXXXX___,
  __XX____,________};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_306F[ 26] = { // Code 306F, HIRAGANA LETTER HA
  XX______,_XX_____,
  _XX_____,__X_____,
  _X___X__,__XXX___,
  _X____XX,XXX_____,
  X_______,__X_____,
  X_______,__X_____,
  X_______,__X_____,
  X__X____,__X_____,
  X_X_____,__X_____,
  X_X___XX,XXX_____,
  XXX__X__,__XX____,
  _X___X__,__X_X___,
  _X____XX,XX______};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_307E[ 28] = { // Code 307E, HIRAGANA LETTER MA
  _____XX_,________,
  ______X_,________,
  X_____XX,XXXX____,
  _XXXXXX_,________,
  ______X_,________,
  ______X_,________,
  _X____XX,XXX_____,
  __XXXXX_,________,
  ______X_,________,
  ______X_,________,
  __XXXXXX,________,
  _X____X_,XX______,
  _X____X_,__XX____,
  __XXXX__,___X____};

//
// Start of unicode area <CJK Unified Ideographs>
//
static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_5BFE[ 30] = { // Code 5BFE
  ___XX___,____XX__,
  ___X____,____X___,
  ___X__X_,____X___,
  XXXXXXX_,____X___,
  _______X,XXXXXXX_,
  ____XX__,____X___,
  XX__X___,____X___,
  __X_X___,X___X___,
  ___X____,_X__X___,
  ___XX___,_X__X___,
  __X__X__,____X___,
  __X__X__,____X___,
  _X______,____X___,
  X_______,_XXXX___,
  ________,___X____};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_5FDC[ 30] = { // Code 5FDC
  _______X,X_______,
  _______X,_____X__,
  __XXXXXX,XXXXXXX_,
  __X_____,________,
  __X____X,________,
  __X_____,X_______,
  __X_____,X_______,
  __X___X_,________,
  __X_X_X_,___X____,
  __X_X_X_,____X___,
  __X_X_X_,_____X__,
  _X__X_X_,___X_X__,
  _X_X__X_,___X____,
  _X_____X,XXXX____,
  X_______,________};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_69D8[ 30] = { // Code 69D8
  __XX___X,___XX___,
  __X_____,X__X__X_,
  __X_X_XX,XXXXXXX_,
  XXXXX___,__X_____,
  __X____X,XXXXXX__,
  _XX_____,__X_____,
  _XXX____,__X__X__,
  _XX_X_XX,XXXXXXX_,
  X_X_X___,__X_____,
  X_X____X,X_X___X_,
  __X_____,_XXX_X__,
  __X_____,X_X_X___,
  __X___XX,__X__X__,
  __X___X_,XXX___X_,
  __X_____,_X______};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_8A00[ 30] = { // Code 8A00
  ________,X_______,
  __XXXXXX,XX______,
  ________,___X____,
  XXXXXXXX,XXXXX___,
  ________,________,
  __XXXXXX,XXX_____,
  ________,________,
  __XXXXXX,XXX_____,
  ________,________,
  ________,__X_____,
  __XXXXXX,XXXX____,
  __X_____,__X_____,
  __X_____,__X_____,
  __XXXXXX,XXX_____,
  __X_____,__X_____};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_8A9E[ 30] = { // Code 8A9E
  ___X____,____X___,
  _XXXX_XX,XXXXXX__,
  ________,_X______,
  ____X___,_X__X___,
  XXXXX_XX,XXXXXX__,
  ________,X___X___,
  _XXXX___,X___X_X_,
  ______XX,XXXXXXX_,
  _XXXX___,________,
  _______X,XXXXX___,
  _XXXX__X,____X___,
  _X__X__X,____X___,
  _X__X__X,____X___,
  _XXXX__X,XXXXX___,
  _X__X__X,____X___};

static GUI_CONST_STORAGE GUI_CHARINFO_EXT _GUI_FontJapanese_text16_CharInfo[19] = {
   {   7,  13,   0,   1,   8, _acGUI_FontJapanese_text16_0057 } // Code 0057, LATIN CAPITAL LETTER W
  ,{   6,   8,   1,   6,   8, _acGUI_FontJapanese_text16_0065 } // Code 0065, LATIN SMALL LETTER E
  ,{   3,  12,   2,   2,   8, _acGUI_FontJapanese_text16_0069 } // Code 0069, LATIN SMALL LETTER I
  ,{   7,   8,   0,   6,   8, _acGUI_FontJapanese_text16_006D } // Code 006D, LATIN SMALL LETTER M
  ,{   7,   8,   0,   6,   8, _acGUI_FontJapanese_text16_006E } // Code 006E, LATIN SMALL LETTER N
  ,{  11,  10,   2,   3,  16, _acGUI_FontJapanese_text16_3005 } // Code 3005, IDEOGRAPHIC ITERATION MARK
  ,{  14,  11,   0,   2,  16, _acGUI_FontJapanese_text16_3044 } // Code 3044, HIRAGANA LETTER I
  ,{  11,  13,   3,   1,  16, _acGUI_FontJapanese_text16_3057 } // Code 3057, HIRAGANA LETTER SI
  ,{  14,  15,   0,   0,  16, _acGUI_FontJapanese_text16_3059 } // Code 3059, HIRAGANA LETTER SU
  ,{  13,  12,   1,   2,  16, _acGUI_FontJapanese_text16_3066 } // Code 3066, HIRAGANA LETTER TE
  ,{  13,  14,   1,   0,  16, _acGUI_FontJapanese_text16_306A } // Code 306A, HIRAGANA LETTER NA
  ,{  13,  13,   1,   1,  16, _acGUI_FontJapanese_text16_306B } // Code 306B, HIRAGANA LETTER NI
  ,{  13,  13,   1,   1,  16, _acGUI_FontJapanese_text16_306F } // Code 306F, HIRAGANA LETTER HA
  ,{  12,  14,   1,   1,  16, _acGUI_FontJapanese_text16_307E } // Code 307E, HIRAGANA LETTER MA
  ,{  15,  15,   0,   0,  16, _acGUI_FontJapanese_text16_5BFE } // Code 5BFE
  ,{  15,  15,   0,   0,  16, _acGUI_FontJapanese_text16_5FDC } // Code 5FDC
  ,{  15,  15,   0,   0,  16, _acGUI_FontJapanese_text16_69D8 } // Code 69D8
  ,{  13,  15,   1,   0,  16, _acGUI_FontJapanese_text16_8A00 } // Code 8A00
  ,{  15,  15,   0,   0,  16, _acGUI_FontJapanese_text16_8A9E } // Code 8A9E
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop17 = {
   0x8A9E                                   // First character
  ,0x8A9E                                   // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[ 18]  // Address of first character
  ,(GUI_CONST_STORAGE GUI_FONT_PROP_EXT *)0 // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop16 = {
   0x8A00                                  // First character
  ,0x8A00                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[ 17] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop17        // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop15 = {
   0x69D8                                  // First character
  ,0x69D8                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[ 16] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop16        // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop14 = {
   0x5FDC                                  // First character
  ,0x5FDC                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[ 15] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop15        // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop13 = {
   0x5BFE                                  // First character
  ,0x5BFE                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[ 14] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop14        // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop12 = {
   0x307E                                  // First character
  ,0x307E                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[ 13] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop13        // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop11 = {
   0x306F                                  // First character
  ,0x306F                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[ 12] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop12        // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop10 = {
   0x306A                                  // First character
  ,0x306B                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[ 10] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop11        // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop9 = {
   0x3066                                  // First character
  ,0x3066                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[  9] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop10        // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop8 = {
   0x3059                                  // First character
  ,0x3059                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[  8] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop9         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop7 = {
   0x3057                                  // First character
  ,0x3057                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[  7] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop8         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop6 = {
   0x3044                                  // First character
  ,0x3044                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[  6] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop7         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop5 = {
   0x3005                                  // First character
  ,0x3005                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[  5] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop6         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop4 = {
   0x006D                                  // First character
  ,0x006E                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[  3] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop5         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop3 = {
   0x0069                                  // First character
  ,0x0069                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[  2] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop4         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop2 = {
   0x0065                                  // First character
  ,0x0065                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[  1] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop3         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop1 = {
   0x0057                                  // First character
  ,0x0057                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[  0] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop2         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT _GUI_FontJapanese_text16 = {
   GUI_FONTTYPE_PROP_EXT // type of font   
  ,16                    // Height of font 
  ,16                    // Space of font y
  ,1                     // Magnification x
  ,1                     // Magnification y
  ,{ &_GUI_FontJapanese_text16_Prop1 }
  ,14                    // Baseline
  ,8                     // Height of lowercase characters
  ,13                    // Height of capital characters
};

/*********************************************************************
*
*       Binary data to write resource files in WIN32
*
**********************************************************************
*/
static const U8 _acGUI_LANG_CSV_Ger_Eng[] = {
  0x22, 0x44, 0x65, 0x75, 0x74, 0x73, 0x63, 0x68, 0x22, 0x2C, 0x22, 0x45, 0x6E, 0x67, 0x6C, 0x69, 0x73, 0x68, 0x22, 0x0D, 0x0A,

  0x22, 0x65, 0x6D, 0x57, 0x69, 0x6E, 0x22, 0x2C, 0x22, 0x65, 0x6D, 0x57, 0x69, 0x6E, 0x22, 0x0D, 0x0A,
  0x22, 0x75, 0x6E, 0x74, 0x65, 0x72, 0x73, 0x74, 0xC3, 0xBC, 0x74, 0x7A, 0x74, 0x22, 0x2C, 0x22, 0x73, 0x75, 0x70, 0x70, 0x6F, 0x72, 0x74, 0x73, 0x22, 0x0D, 0x0A,
  0x22, 0x76, 0x65, 0x72, 0x73, 0x63, 0x68, 0x69, 0x65, 0x64, 0x65, 0x6E, 0x65, 0x22, 0x2C, 0x22, 0x64, 0x69, 0x66, 0x66, 0x65, 0x72, 0x65, 0x6E, 0x74, 0x22, 0x0D, 0x0A,
  0x22, 0x53, 0x70, 0x72, 0x61, 0x63, 0x68, 0x65, 0x6E, 0x22, 0x2C, 0x22, 0x6C, 0x61, 0x6E, 0x67, 0x75, 0x61, 0x67, 0x65, 0x73, 0x22//, 0x00
};

static const U8 _acGUI_LANG_TXT_Jap[] = {
  0xEF, 0xBB, 0xBF, 0xE6, 0x97, 0xA5, 0xE6, 0x9C, 0xAC, 0xE8, 0xAA, 0x9E, 0x0D, 0x0A,
  0x65, 0x6D, 0x57, 0x69, 0x6E, 0x0D, 0x0A,
  0xE3, 0x81, 0xAF, 0xE6, 0xA7, 0x98, 0xE3, 0x80, 0x85, 0xE3, 0x81, 0xAA, 0x0D, 0x0A,
  0xE8, 0xA8, 0x80, 0xE8, 0xAA, 0x9E, 0xE3, 0x81, 0xAB, 0x0D, 0x0A,
  0xE5, 0xAF, 0xBE, 0xE5, 0xBF, 0x9C, 0xE3, 0x81, 0x97, 0xE3, 0x81, 0xA6, 0xE3, 0x81, 0x84, 0xE3, 0x81, 0xBE, 0xE3, 0x81, 0x99
};

/*********************************************************************
*
*       Language source context
*
*  Description
*    Used to write the resource files in WIN32
*
**********************************************************************
*/
#ifdef WIN32
typedef struct {
  const U8   * pData;
  const U32    NumBytes;
} RES_FILE_DATA;

static RES_FILE_DATA _ResFileData[] = {
  { _acGUI_LANG_CSV_Ger_Eng, sizeof(_acGUI_LANG_CSV_Ger_Eng) },
  { _acGUI_LANG_TXT_Jap,     sizeof(_acGUI_LANG_TXT_Jap)     }
};
#endif

/*********************************************************************
*
*       Language resource context
*
*  Description
*    Used as file name transporter for the GetData()-function.
*
**********************************************************************
*/
#ifdef WIN32
typedef struct {
  const char * pFileName;
  const char * pExt;
} RES_FILE_NAME;

static RES_FILE_NAME _ResFileName[] = {
  { "_GUI_LANG_CSV_Ger_Eng", ".csv" },
  { "_GUI_LANG_TXT_Jap",     ".txt" }
};
#endif

/*********************************************************************
*
*       Language context
*
**********************************************************************
*/
typedef struct {
  const GUI_FONT * pFontHeadline;
  const GUI_FONT * pFontBody;
} LANG_CONTEXT;

static LANG_CONTEXT _Languages[] = {
  { &GUI_Font16B_1,                &GUI_Font16_1             },
  { &GUI_Font16B_1,                &GUI_Font16_1             },
  { &_GUI_FontJapanese_headline16, &_GUI_FontJapanese_text16 }
};

/*********************************************************************
*
*       _GetData
*/
#ifdef WIN32
static int _GetData(void * pVoid, const U8 ** ppData, unsigned NumBytes, U32 Off) {
  RES_FILE_NAME * pFileRes;
  HANDLE          hFile;
  DWORD           NumBytesRead;
  char            acDrive[_MAX_DRIVE];
  char            acPath[_MAX_PATH];
  char            acDir[_MAX_DIR];
  U8            * pData;

  pData    = (U8 *)*ppData;
  pFileRes = (RES_FILE_NAME *)pVoid;
  GetModuleFileName(NULL, acPath, FILENAME_MAX);
  _splitpath(acPath, acDrive, acDir, NULL, NULL);
  _makepath(acPath, acDrive, acDir, pFileRes->pFileName, pFileRes->pExt);
  hFile = CreateFile(acPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  if (SetFilePointer(hFile, Off, 0, FILE_BEGIN) == 0xFFFFFFFF) {
    CloseHandle(hFile);
    return 0;
  }
  if (!ReadFile(hFile, pData, NumBytes, &NumBytesRead, 0)) {
    CloseHandle(hFile);
    return 0;
  }
  if (NumBytesRead > NumBytes) {
    CloseHandle(hFile);
    return 0;
  }
  CloseHandle(hFile);
  return NumBytesRead;
}
#endif

/*********************************************************************
*
*       _CreateLanguageResources
*/
#ifdef WIN32
static void _CreateLanguageResources(void) {
  HANDLE hFile;
  char   acFileName[_MAX_FNAME];
  char   acDrive[_MAX_DRIVE];
  char   acPath[_MAX_PATH];
  char   acDir[_MAX_DIR];
  char   acExt[_MAX_EXT];
  U32    NumBytesWritten;
  U8     FileCnt;

  GetModuleFileName(NULL, acPath, FILENAME_MAX);
  _splitpath(acPath, acDrive, acDir, acFileName, acExt);
  for (FileCnt = 0; FileCnt < NUM_FILES; FileCnt++) {
    sprintf(acFileName, _ResFileName[FileCnt].pFileName);
    sprintf(acExt,      _ResFileName[FileCnt].pExt);
    _makepath(acPath, acDrive, acDir, acFileName, acExt);
    hFile = CreateFile(acPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile == INVALID_HANDLE_VALUE) {
      GUI_DEBUG_ERROROUT("File could not be created.");
    }
    WriteFile(hFile, _ResFileData[FileCnt].pData, _ResFileData[FileCnt].NumBytes, &NumBytesWritten, NULL);
    CloseHandle(hFile);
    if (_ResFileData[FileCnt].NumBytes != NumBytesWritten) {
      GUI_DEBUG_ERROROUT("File was not written properly.");
    }
  }
}
#endif

/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  const char * pText;
  GUI_RECT     Rect;
  U16          xSizeScreen;
  U16          ySizeScreen;
  U16          xSizeItem;
  U16          ySizeItem;
  U16          xSize;
  U16          ySize;
  U16          xOff;
  U16          yOff;
  U8           NumLanguagesCSV;
  U8           ItemCnt;
  U8           LangCnt;

  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  GUI_UC_SetEncodeUTF8();
  xSizeScreen = LCD_GetXSize();
  ySizeScreen = LCD_GetYSize();
  if ((xSizeScreen < XSIZE_MIN) || (ySizeScreen < YSIZE_MIN)) {
    GUI_DEBUG_ERROROUT("Inaccurate display size.");
  }
  //
  // Stretch the sample up to a size of #define XSIZE_MAX * YSIZE_MAX.
  // Above that display size the sample is centered on the according axis.
  //
  if (xSizeScreen > XSIZE_MAX) {
    xOff  = (xSizeScreen - XSIZE_MAX) / 2;
    xSize = XSIZE_MAX;
  } else {
    xOff  = 0;
    xSize = xSizeScreen;
  }
  if (ySizeScreen > YSIZE_MAX) {
    yOff  = (ySizeScreen - YSIZE_MAX) / 2;
    ySize = YSIZE_MAX;
  } else {
    yOff  = 0;
    ySize = ySizeScreen;
  }
#ifdef WIN32
  _CreateLanguageResources();
#endif
  //
  // Draw background
  //
  xSizeItem = xSize / NUM_LANGUAGES - 6;
  ySizeItem = (ySize - HEIGHT_TOP) / NUM_ITEMS;
  GUI_SetBkColor(GUI_DARKBLUE);
  GUI_Clear();
  GUI_DrawGradientV(0, HEIGHT_TOP, xSizeScreen - 1, ySizeScreen - 1, GUI_DARKBLUE, GUI_DARKGRAY);
  //
  // Draw frames
  //
  Rect.x0 = xOff + BORDER_SIZE;
  Rect.x1 = xOff + xSizeItem * 2 - BORDER_SIZE;
  Rect.y0 = yOff + HEIGHT_TOP + BORDER_SIZE;
  Rect.y1 = ySizeScreen - yOff - BORDER_SIZE - 1;
  GUI_DrawRectEx(&Rect);
  GUI_DrawHLine(Rect.y0 + ySizeItem, Rect.x0, Rect.x1);
  Rect.x0 = xOff + xSizeItem * 2 + BORDER_SIZE;
  Rect.x1 = xSizeScreen - xOff - BORDER_SIZE;
  GUI_DrawRectEx(&Rect);
  GUI_DrawHLine(Rect.y0 + ySizeItem, Rect.x0, Rect.x1);
  //
  // Display headlines
  //
  GUI_SetFont(&GUI_Font20B_ASCII);
  GUI_SetTextMode(GUI_TM_TRANS);
  Rect.x0 = xOff;
  Rect.x1 = xOff + xSize - 1;
  Rect.y0 = yOff;
  Rect.y1 = yOff + HEIGHT_HEADLINE_1 - 1;
  GUI_DispStringInRect("emWin - Language Resources", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
  GUI_SetFont(&GUI_Font13B_ASCII);
  Rect.x1 = xOff + xSizeItem * 2 - 1;
  Rect.y0 = yOff + HEIGHT_HEADLINE_1;
  Rect.y1 = yOff + HEIGHT_TOP    - 1;
  GUI_DispStringInRect("CSV file", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
  Rect.x0 = Rect.x1;
  Rect.x1 = xSizeScreen - xOff - 1;
  GUI_DispStringInRect("Text file", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
  //
  // Load resource files
  //
  GUI_LANG_SetMaxNumLang(NUM_LANGUAGES);
#ifdef WIN32
  NumLanguagesCSV = GUI_LANG_LoadCSVEx(_GetData, &_ResFileName[0]);
  GUI_LANG_LoadTextEx(_GetData, &_ResFileName[1], NumLanguagesCSV);
#else
  NumLanguagesCSV = GUI_LANG_LoadCSV(_acGUI_LANG_CSV_Ger_Eng, sizeof(_acGUI_LANG_CSV_Ger_Eng));
  GUI_LANG_LoadText(_acGUI_LANG_TXT_Jap, sizeof(_acGUI_LANG_TXT_Jap), NumLanguagesCSV);
#endif
  //
  // Display the resource text in the calculated rectangle
  // using the according font for headline and body.
  //
  for (LangCnt = 0; LangCnt < NUM_LANGUAGES; LangCnt++) {
    Rect.x0 = xOff + LangCnt * xSizeItem + ((LangCnt == (NUM_LANGUAGES - 1)) ? 5 : 0);
    Rect.x1 = (LangCnt == (NUM_LANGUAGES - 1)) ? xSize - 1 : Rect.x0 + xSizeItem;
    for (ItemCnt = 0; ItemCnt < NUM_ITEMS; ItemCnt++) {
      pText   = GUI_LANG_GetTextEx(ItemCnt, LangCnt);
      Rect.y0 = yOff + HEIGHT_TOP + (ItemCnt * ySizeItem);
      Rect.y1 = Rect.y0 + ySizeItem;
      if (ItemCnt == 0) {
        GUI_SetFont(_Languages[LangCnt].pFontHeadline);
      } else {
        GUI_SetFont(_Languages[LangCnt].pFontBody);
      }
      GUI_DispStringInRect(pText, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    }
  }
  while (1) {
    GUI_Delay(100);
  }
}

#endif

/*************************** End of file ****************************/
