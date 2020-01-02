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
File        : FONT_Arabic.c
Purpose     : Shows how to draw text in thai language
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

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

/*******************************************************************
*
*       Static data
*
********************************************************************
*/
/*******************************************************************
*
*       Arabic font
*/
//
// Start of unicode area <Basic Latin>
//
GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0020[  1] = { // code 0020, SPACE
  ________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0021[ 15] = { // code 0021, EXCLAMATION MARK
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0022[  5] = { // code 0022, QUOTATION MARK
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0023[ 30] = { // code 0023, NUMBER SIGN
  ____XX__,_XX_____,
  ____XX__,_XX_____,
  ____XX__,XXX_____,
  ___XX___,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____,
  ___XX___,XX______,
  __XX___X,X_______,
  __XX___X,X_______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____,
  __XX___X,X_______,
  _XXX__XX,________,
  _XX___XX,________,
  _XX___XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0024[ 36] = { // code 0024, DOLLAR SIGN
  ____X___,________,
  __XXXXX_,________,
  _XXXXXXX,________,
  XXX_X_XX,X_______,
  XX__X__X,X_______,
  XX__X___,________,
  XXX_X___,________,
  _XXXXX__,________,
  ___XXXXX,________,
  ____X_XX,X_______,
  ____X__X,X_______,
  ____X__X,X_______,
  XX__X__X,X_______,
  XXX_X_XX,X_______,
  _XXXXXXX,________,
  __XXXXX_,________,
  ____X___,________,
  ____X___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0025[ 45] = { // code 0025, PERCENT SIGN
  __XXX___,____XX__,________,
  _XX_XX__,___XX___,________,
  XX___XX_,___XX___,________,
  XX___XX_,__XX____,________,
  XX___XX_,__XX____,________,
  XX___XX_,_XX_____,________,
  _XX_XX__,XX______,________,
  __XXX___,XX__XXX_,________,
  _______X,X__XX_XX,________,
  _______X,X_XX___X,X_______,
  ______XX,__XX___X,X_______,
  ______XX,__XX___X,X_______,
  _____XX_,__XX___X,X_______,
  ____XX__,___XX_XX,________,
  ____XX__,____XXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0026[ 30] = { // code 0026, AMPERSAND
  ____XXXX,________,
  ___XXXXX,X_______,
  __XX____,XX______,
  __XX____,XX______,
  __XX___X,X_______,
  ___XX_XX,________,
  ___XXXX_,________,
  __XXXXX_,________,
  _XX__XXX,__XX____,
  XX____XX,X_XX____,
  XX_____X,XXX_____,
  XX______,XX______,
  XXX____X,XXX_____,
  _XXXXXXX,X_XX____,
  __XXXXX_,___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0027[  5] = { // code 0027, APOSTROPHE
  XX______,
  XX______,
  XX______,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0028[ 19] = { // code 0028, LEFT PARENTHESIS
  ____X___,
  ___X____,
  __XX____,
  __X_____,
  _XX_____,
  _XX_____,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  _XX_____,
  _XX_____,
  __X_____,
  __XX____,
  ___X____,
  ____X___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0029[ 19] = { // code 0029, RIGHT PARENTHESIS
  X_______,
  _X______,
  _XX_____,
  __X_____,
  __XX____,
  __XX____,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  __XX____,
  __XX____,
  __X_____,
  _XX_____,
  _X______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_002A[  6] = { // code 002A, ASTERISK
  ___XX___,
  ___XX___,
  XXXXXXXX,
  ___XX___,
  __XXXX__,
  _XX__XX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_002B[ 20] = { // code 002B, PLUS SIGN
  ____XX__,________,
  ____XX__,________,
  ____XX__,________,
  ____XX__,________,
  XXXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XX__,________,
  ____XX__,________,
  ____XX__,________,
  ____XX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_002C[  5] = { // code 002C, COMMA
  XX______,
  XX______,
  _X______,
  _X______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_002D[  2] = { // code 002D, HYPHEN-MINUS
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_002E[  2] = { // code 002E, FULL STOP
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_002F[ 15] = { // code 002F, SOLIDUS
  ____XX__,
  ____XX__,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  __XX____,
  __XX____,
  __XX____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0030[ 30] = { // code 0030, DIGIT ZERO
  __XXXXX_,________,
  _XXXXXXX,X_______,
  _XX____X,X_______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  _XX____X,X_______,
  _XXXXXXX,X_______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0031[ 15] = { // code 0031, DIGIT ONE
  ____XX__,
  ____XX__,
  __XXXX__,
  _XXXXX__,
  XX__XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0032[ 30] = { // code 0032, DIGIT TWO
  __XXXXXX,________,
  _XXXXXXX,X_______,
  XXX____X,XX______,
  XX______,XX______,
  ________,XX______,
  ________,XX______,
  _______X,X_______,
  _______X,X_______,
  ______XX,________,
  ____XXX_,________,
  ___XXX__,________,
  __XX____,________,
  _XX_____,________,
  XXXXXXXX,XX______,
  XXXXXXXX,XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0033[ 30] = { // code 0033, DIGIT THREE
  __XXXXX_,________,
  _XXXXXXX,________,
  XXX___XX,X_______,
  XX_____X,X_______,
  _______X,X_______,
  ______XX,________,
  ____XXX_,________,
  ____XXXX,X_______,
  _______X,XX______,
  ________,XX______,
  ________,XX______,
  XX______,XX______,
  XXX____X,X_______,
  _XXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0034[ 30] = { // code 0034, DIGIT FOUR
  _______X,________,
  ______XX,________,
  _____XXX,________,
  ____XXXX,________,
  ___XX_XX,________,
  ___XX_XX,________,
  __XX__XX,________,
  _XX___XX,________,
  XX____XX,________,
  XXXXXXXX,XX______,
  XXXXXXXX,XX______,
  ______XX,________,
  ______XX,________,
  ______XX,________,
  ______XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0035[ 30] = { // code 0035, DIGIT FIVE
  __XXXXXX,X_______,
  __XXXXXX,X_______,
  _XX_____,________,
  _XX_____,________,
  _XX_____,________,
  _XX_XXXX,________,
  XXXXXXXX,X_______,
  XX_____X,XX______,
  ________,XX______,
  ________,XX______,
  ________,XX______,
  XX______,XX______,
  XXX____X,X_______,
  _XXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0036[ 30] = { // code 0036, DIGIT SIX
  ___XXXXX,________,
  __XXXXXX,X_______,
  _XX____X,XX______,
  _XX_____,XX______,
  XX______,________,
  XX__XXXX,________,
  XXXXXXXX,X_______,
  XXX____X,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  _XX____X,X_______,
  __XXXXXX,X_______,
  ___XXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0037[ 30] = { // code 0037, DIGIT SEVEN
  XXXXXXXX,XX______,
  XXXXXXXX,XX______,
  _______X,X_______,
  ______XX,________,
  ______XX,________,
  _____XX_,________,
  _____XX_,________,
  ____XX__,________,
  ____XX__,________,
  ___XX___,________,
  ___XX___,________,
  ___XX___,________,
  __XX____,________,
  __XX____,________,
  __XX____,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0038[ 30] = { // code 0038, DIGIT EIGHT
  ___XXXX_,________,
  __XXXXXX,________,
  _XX____X,X_______,
  _XX____X,X_______,
  _XX____X,X_______,
  _XX____X,X_______,
  __XXXXXX,________,
  __XXXXXX,________,
  _XX____X,X_______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XXX____X,XX______,
  _XXXXXXX,X_______,
  __XXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0039[ 30] = { // code 0039, DIGIT NINE
  ___XXXX_,________,
  _XXXXXXX,________,
  _XX____X,X_______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  _XX____X,XX______,
  _XXXXXXX,XX______,
  __XXXX__,XX______,
  ________,XX______,
  XX_____X,X_______,
  XXX____X,X_______,
  _XXXXXXX,________,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_003A[ 11] = { // code 003A, COLON
  XX______,
  XX______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_003B[ 14] = { // code 003B, SEMICOLON
  XX______,
  XX______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XX______,
  XX______,
  _X______,
  _X______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_003C[ 22] = { // code 003C, LESS-THAN SIGN
  ________,_X______,
  _______X,XX______,
  _____XXX,X_______,
  ___XXXX_,________,
  _XXX____,________,
  XX______,________,
  _XXX____,________,
  ___XXXX_,________,
  _____XXX,X_______,
  _______X,XX______,
  ________,_X______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_003D[ 14] = { // code 003D, EQUALS SIGN
  XXXXXXXX,XX______,
  XXXXXXXX,XX______,
  ________,________,
  ________,________,
  ________,________,
  XXXXXXXX,XX______,
  XXXXXXXX,XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_003E[ 22] = { // code 003E, GREATER-THAN SIGN
  X_______,________,
  XXX_____,________,
  _XXXX___,________,
  ___XXXX_,________,
  ______XX,X_______,
  ________,XX______,
  ______XX,X_______,
  ___XXXX_,________,
  _XXXX___,________,
  XXX_____,________,
  X_______,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_003F[ 30] = { // code 003F, QUESTION MARK
  __XXXXXX,________,
  _XXXXXXX,X_______,
  XXX____X,XX______,
  XX______,XX______,
  ________,XX______,
  _______X,X_______,
  ______XX,X_______,
  _____XXX,________,
  ____XXX_,________,
  ____XX__,________,
  ____XX__,________,
  ________,________,
  ________,________,
  ____XX__,________,
  ____XX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0040[ 57] = { // code 0040, COMMERCIAL AT
  _______X,XXXXXX__,________,
  ____XXXX,XXXXXXXX,________,
  ___XXXX_,_____XXX,X_______,
  __XXX___,_______X,XX______,
  __XX____,XXX__XX_,XX______,
  _XX___XX,XXXX_XX_,XXX_____,
  _XX__XXX,___XXX__,_XX_____,
  XX___XX_,____XX__,_XX_____,
  XX__XX__,____XX__,_XX_____,
  XX__XX__,____XX__,_XX_____,
  XX__XX__,____X___,XXX_____,
  XX__XX__,___XX___,XX______,
  XX__XXX_,__XXX__X,X_______,
  _XX__XXX,XXXXXXXX,________,
  _XXX__XX,XX_XXXX_,_XX_____,
  __XXX___,________,XX______,
  ___XXXX_,______XX,X_______,
  ____XXXX,XXXXXXXX,________,
  ______XX,XXXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0041[ 30] = { // code 0041, LATIN CAPITAL LETTER A
  _____XXX,________,
  _____XXX,________,
  ____XX_X,X_______,
  ____XX_X,X_______,
  ____XX_X,X_______,
  ___XX___,XX______,
  ___XX___,XX______,
  ___XX___,XX______,
  __XXXXXX,XXX_____,
  __XXXXXX,XXX_____,
  _XX_____,__XX____,
  _XX_____,__XX____,
  _XX_____,__XX____,
  XX______,___XX___,
  XX______,___XX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0042[ 30] = { // code 0042, LATIN CAPITAL LETTER B
  XXXXXXXX,________,
  XXXXXXXX,X_______,
  XX_____X,XX______,
  XX______,XX______,
  XX______,XX______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______,
  XX______,XX______,
  XX______,_XX_____,
  XX______,_XX_____,
  XX______,_XX_____,
  XX______,XXX_____,
  XXXXXXXX,XX______,
  XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0043[ 30] = { // code 0043, LATIN CAPITAL LETTER C
  ____XXXX,XX______,
  __XXXXXX,XXX_____,
  __XXX___,_XXX____,
  _XX_____,__XXX___,
  XXX_____,___XX___,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XXX_____,___XX___,
  _XX_____,__XX____,
  _XXXX___,_XXX____,
  __XXXXXX,XXX_____,
  ____XXXX,XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0044[ 30] = { // code 0044, LATIN CAPITAL LETTER D
  XXXXXXXX,________,
  XXXXXXXX,XX______,
  XX______,XXX_____,
  XX______,_XX_____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,_XX_____,
  XX______,XXX_____,
  XXXXXXXX,XX______,
  XXXXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0045[ 30] = { // code 0045, LATIN CAPITAL LETTER E
  XXXXXXXX,XXX_____,
  XXXXXXXX,XXX_____,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XXXXXXXX,XX______,
  XXXXXXXX,XX______,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XXXXXXXX,XXX_____,
  XXXXXXXX,XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0046[ 30] = { // code 0046, LATIN CAPITAL LETTER F
  XXXXXXXX,XX______,
  XXXXXXXX,XX______,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0047[ 30] = { // code 0047, LATIN CAPITAL LETTER G
  ____XXXX,XXX_____,
  ___XXXXX,XXXX____,
  __XXX___,__XXX___,
  _XX_____,___XXX__,
  _XX_____,____X___,
  XX______,________,
  XX______,________,
  XX_____X,XXXXXX__,
  XX_____X,XXXXXX__,
  XX______,____XX__,
  _XX_____,____XX__,
  _XX_____,____XX__,
  __XXX___,__XXXX__,
  ___XXXXX,XXXXX___,
  _____XXX,XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0048[ 30] = { // code 0048, LATIN CAPITAL LETTER H
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0049[ 15] = { // code 0049, LATIN CAPITAL LETTER I
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_004A[ 15] = { // code 004A, LATIN CAPITAL LETTER J
  ______XX,
  ______XX,
  ______XX,
  ______XX,
  ______XX,
  ______XX,
  ______XX,
  ______XX,
  ______XX,
  ______XX,
  XX____XX,
  XX____XX,
  XXX__XXX,
  _XXXXXX_,
  __XXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_004B[ 30] = { // code 004B, LATIN CAPITAL LETTER K
  XX______,XXX_____,
  XX_____X,XX______,
  XX____XX,X_______,
  XX___XXX,________,
  XX__XXX_,________,
  XX_XXX__,________,
  XX_XXX__,________,
  XXXXXX__,________,
  XXX_XXX_,________,
  XX___XXX,________,
  XX____XX,X_______,
  XX_____X,X_______,
  XX_____X,XX______,
  XX______,XXX_____,
  XX______,_XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_004C[ 30] = { // code 004C, LATIN CAPITAL LETTER L
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_004D[ 30] = { // code 004D, LATIN CAPITAL LETTER M
  XXX_____,____XXX_,
  XXXX____,___XXXX_,
  XXXX____,___XXXX_,
  XX_X____,___X_XX_,
  XX_XX___,__XX_XX_,
  XX_XX___,__XX_XX_,
  XX__X___,__X__XX_,
  XX__XX__,_XX__XX_,
  XX__XX__,_XX__XX_,
  XX___X__,_X___XX_,
  XX___XX_,XX___XX_,
  XX___XX_,XX___XX_,
  XX____X_,X____XX_,
  XX____XX,X____XX_,
  XX____XX,X____XX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_004E[ 30] = { // code 004E, LATIN CAPITAL LETTER N
  XX______,__XX____,
  XXX_____,__XX____,
  XXXX____,__XX____,
  XXXX____,__XX____,
  XX_XX___,__XX____,
  XX__XX__,__XX____,
  XX__XX__,__XX____,
  XX___XX_,__XX____,
  XX____XX,__XX____,
  XX____XX,__XX____,
  XX_____X,X_XX____,
  XX______,XXXX____,
  XX______,XXXX____,
  XX______,_XXX____,
  XX______,__XX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_004F[ 30] = { // code 004F, LATIN CAPITAL LETTER O
  ____XXXX,XX______,
  ___XXXXX,XXX_____,
  __XXX___,_XXX____,
  _XX_____,___XX___,
  XXX_____,___XXX__,
  XX______,____XX__,
  XX______,____XX__,
  XX______,____XX__,
  XX______,____XX__,
  XX______,____XX__,
  XXX_____,___XXX__,
  _XX_____,___XX___,
  __XXX___,_XXX____,
  ___XXXXX,XXX_____,
  ____XXXX,XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0050[ 30] = { // code 0050, LATIN CAPITAL LETTER P
  XXXXXXXX,X_______,
  XXXXXXXX,XX______,
  XX______,XXX_____,
  XX______,_XX_____,
  XX______,_XX_____,
  XX______,_XX_____,
  XX______,XXX_____,
  XXXXXXXX,XX______,
  XXXXXXXX,X_______,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0051[ 32] = { // code 0051, LATIN CAPITAL LETTER Q
  ____XXXX,XX______,
  ___XXXXX,XXXX____,
  __XXX___,_XXXX___,
  _XX_____,___XX___,
  XXX_____,___XXX__,
  XX______,____XX__,
  XX______,____XX__,
  XX______,____XX__,
  XX______,____XX__,
  XX______,____XX__,
  XXX_____,___XX___,
  _XX____X,XX_XX___,
  __XXX___,_XXX____,
  ___XXXXX,XXXXX___,
  ____XXXX,XX_XXX__,
  ________,_____X__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0052[ 30] = { // code 0052, LATIN CAPITAL LETTER R
  XXXXXXXX,X_______,
  XXXXXXXX,XX______,
  XX______,XXX_____,
  XX______,_XX_____,
  XX______,_XX_____,
  XX______,XXX_____,
  XXXXXXXX,XX______,
  XXXXXXXX,X_______,
  XX____XX,________,
  XX____XX,X_______,
  XX_____X,X_______,
  XX_____X,XX______,
  XX______,XXX_____,
  XX______,_XX_____,
  XX______,_XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0053[ 30] = { // code 0053, LATIN CAPITAL LETTER S
  ____XXXX,X_______,
  __XXXXXX,XXX_____,
  _XXX____,_XXX____,
  _XX_____,__XX____,
  _XX_____,________,
  _XXX____,________,
  __XXXXXX,________,
  ____XXXX,XX______,
  ________,XXX_____,
  ________,__XX____,
  XX______,__XX____,
  XXX_____,__XX____,
  _XXX____,_XXX____,
  __XXXXXX,XXX_____,
  ___XXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0054[ 30] = { // code 0054, LATIN CAPITAL LETTER T
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0055[ 30] = { // code 0055, LATIN CAPITAL LETTER U
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XX______,__XX____,
  XXX_____,_XXX____,
  _XXX____,XXX_____,
  __XXXXXX,XX______,
  ___XXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0056[ 30] = { // code 0056, LATIN CAPITAL LETTER V
  XX______,___XX___,
  XXX_____,__XXX___,
  _XX_____,__XX____,
  _XX_____,__XX____,
  _XXX____,_XXX____,
  __XX____,_XX_____,
  __XX____,_XX_____,
  __XXX___,XXX_____,
  ___XX___,XX______,
  ___XX___,XX______,
  ___XXX_X,XX______,
  ____XX_X,X_______,
  ____XX_X,X_______,
  ____XXXX,X_______,
  _____XXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0057[ 45] = { // code 0057, LATIN CAPITAL LETTER W
  XX______,_XXX____,___XX___,
  XX______,_XXX____,___XX___,
  _XX_____,XX_XX___,__XX____,
  _XX_____,XX_XX___,__XX____,
  _XX_____,XX_XX___,__XX____,
  _XXX____,XX__X___,_XXX____,
  __XX___X,X___XX__,_XX_____,
  __XX___X,X___XX__,_XX_____,
  __XX___X,X___XX__,_XX_____,
  ___XX_XX,_____XX_,XX______,
  ___XX_XX,_____XX_,XX______,
  ___XX_XX,_____XX_,XX______,
  ___XX_XX,_____XX_,XX______,
  ____XXX_,______XX,X_______,
  ____XXX_,______XX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0058[ 30] = { // code 0058, LATIN CAPITAL LETTER X
  _XXX____,__XXX___,
  __XXX___,_XXX____,
  ___XX___,_XX_____,
  ____XX__,XX______,
  ____XX__,XX______,
  _____XXX,X_______,
  ______XX,________,
  _____XXX,X_______,
  _____XXX,X_______,
  ____XX_X,XX______,
  ___XXX__,XXX_____,
  ___XX___,_XX_____,
  __XX____,__XX____,
  _XXX____,__XXX___,
  XXX_____,___XXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0059[ 30] = { // code 0059, LATIN CAPITAL LETTER Y
  XXX_____,___XXX__,
  _XX_____,___XX___,
  __XX____,__XX____,
  __XXX___,_XXX____,
  ___XXX__,XXX_____,
  ____XX__,XX______,
  _____XXX,X_______,
  _____XXX,X_______,
  ______XX,________,
  ______XX,________,
  ______XX,________,
  ______XX,________,
  ______XX,________,
  ______XX,________,
  ______XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_005A[ 30] = { // code 005A, LATIN CAPITAL LETTER Z
  _XXXXXXX,XXXX____,
  _XXXXXXX,XXXX____,
  ________,_XX_____,
  ________,XX______,
  _______X,X_______,
  _______X,X_______,
  ______XX,________,
  _____XX_,________,
  ____XX__,________,
  ___XX___,________,
  ___XX___,________,
  __XX____,________,
  _XX_____,________,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_005B[ 19] = { // code 005B, LEFT SQUARE BRACKET
  XXXX____,
  XXXX____,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XXXX____,
  XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_005C[ 15] = { // code 005C, REVERSE SOLIDUS
  XX______,
  XX______,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  __XX____,
  __XX____,
  __XX____,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ____XX__,
  ____XX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_005D[ 19] = { // code 005D, RIGHT SQUARE BRACKET
  XXXX____,
  XXXX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  XXXX____,
  XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_005E[  8] = { // code 005E, CIRCUMFLEX ACCENT
  ___XX___,
  __XXXX__,
  __XXXX__,
  __XXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  XX____XX};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_005F[  4] = { // code 005F, LOW LINE
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0060[  3] = { // code 0060, GRAVE ACCENT
  XX______,
  _XX_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0061[ 22] = { // code 0061, LATIN SMALL LETTER A
  __XXXXXX,________,
  XXXXXXXX,X_______,
  XX_____X,X_______,
  _______X,X_______,
  ____XXXX,X_______,
  _XXXXXXX,X_______,
  XXXX___X,X_______,
  XX_____X,X_______,
  XX____XX,X_______,
  XXXXXXXX,X_______,
  _XXXXX__,XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0062[ 30] = { // code 0062, LATIN SMALL LETTER B
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX_XXXX_,________,
  XXXXXXXX,________,
  XXX___XX,________,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XXX___XX,________,
  XXXXXXXX,________,
  XX_XXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0063[ 22] = { // code 0063, LATIN SMALL LETTER C
  ___XXXX_,________,
  _XXXXXXX,________,
  _XX___XX,X_______,
  XX_____X,X_______,
  XX______,________,
  XX______,________,
  XX______,________,
  XX_____X,X_______,
  _XX___XX,X_______,
  _XXXXXXX,________,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0064[ 30] = { // code 0064, LATIN SMALL LETTER D
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  __XXXX_X,X_______,
  _XXXXXXX,X_______,
  _XX___XX,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  _XX___XX,X_______,
  _XXXXXXX,X_______,
  __XXXX_X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0065[ 22] = { // code 0065, LATIN SMALL LETTER E
  ___XXXX_,________,
  _XXXXXXX,X_______,
  _XX____X,X_______,
  XX______,XX______,
  XXXXXXXX,XX______,
  XXXXXXXX,XX______,
  XX______,________,
  XX______,________,
  _XX____X,XX______,
  _XXXXXXX,X_______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0066[ 15] = { // code 0066, LATIN SMALL LETTER F
  ___XXXX_,
  __XXXXX_,
  __XX____,
  __XX____,
  XXXXXX__,
  XXXXXX__,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0067[ 30] = { // code 0067, LATIN SMALL LETTER G
  __XXXX_X,X_______,
  _XXXXXXX,X_______,
  _XX___XX,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  _XX___XX,X_______,
  _XXXXXXX,X_______,
  __XXXX_X,X_______,
  _______X,X_______,
  XX____XX,X_______,
  XXXXXXXX,________,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0068[ 30] = { // code 0068, LATIN SMALL LETTER H
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX_XXXX_,________,
  XXXXXXXX,________,
  XXX___XX,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0069[ 15] = { // code 0069, LATIN SMALL LETTER I
  XX______,
  XX______,
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_006A[ 19] = { // code 006A, LATIN SMALL LETTER J
  __XX____,
  __XX____,
  ________,
  ________,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  XXXX____,
  XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_006B[ 30] = { // code 006B, LATIN SMALL LETTER K
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX____XX,X_______,
  XX___XXX,________,
  XX__XXX_,________,
  XX_XXX__,________,
  XXXXX___,________,
  XXXXXX__,________,
  XX__XX__,________,
  XX___XX_,________,
  XX___XXX,________,
  XX____XX,________,
  XX____XX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_006C[ 15] = { // code 006C, LATIN SMALL LETTER L
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_006D[ 22] = { // code 006D, LATIN SMALL LETTER M
  XX_XXXX_,_XXXX___,
  XXXXXXX_,XXXXXX__,
  XXX___XX,X___XX__,
  XX____XX,____XX__,
  XX____XX,____XX__,
  XX____XX,____XX__,
  XX____XX,____XX__,
  XX____XX,____XX__,
  XX____XX,____XX__,
  XX____XX,____XX__,
  XX____XX,____XX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_006E[ 22] = { // code 006E, LATIN SMALL LETTER N
  XX_XXXX_,________,
  XXXXXXXX,________,
  XXX___XX,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_006F[ 22] = { // code 006F, LATIN SMALL LETTER O
  ___XXXX_,________,
  _XXXXXXX,X_______,
  _XX____X,X_______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  _XX____X,X_______,
  _XXXXXXX,X_______,
  ___XXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0070[ 30] = { // code 0070, LATIN SMALL LETTER P
  XX_XXXX_,________,
  XXXXXXXX,________,
  XXX___XX,________,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XXX___XX,________,
  XXXXXXXX,________,
  XX_XXXX_,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0071[ 30] = { // code 0071, LATIN SMALL LETTER Q
  __XXXX_X,X_______,
  _XXXXXXX,X_______,
  _XX___XX,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  _XX___XX,X_______,
  _XXXXXXX,X_______,
  __XXXX_X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0072[ 11] = { // code 0072, LATIN SMALL LETTER R
  XX_XXX__,
  XXXXXX__,
  XXX_____,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0073[ 22] = { // code 0073, LATIN SMALL LETTER S
  __XXXXX_,________,
  _XXXXXXX,________,
  XX_____X,X_______,
  XX______,________,
  XXXXX___,________,
  _XXXXXXX,________,
  _____XXX,X_______,
  _______X,X_______,
  XX_____X,X_______,
  _XXXXXXX,________,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0074[ 15] = { // code 0074, LATIN SMALL LETTER T
  __X_____,
  _XX_____,
  _XX_____,
  _XX_____,
  XXXXX___,
  XXXXX___,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XXXX___,
  __XXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0075[ 22] = { // code 0075, LATIN SMALL LETTER U
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XXX___XX,X_______,
  _XXXXXXX,X_______,
  __XXXX_X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0076[ 22] = { // code 0076, LATIN SMALL LETTER V
  XX______,_XX_____,
  XX______,_XX_____,
  _XX_____,XX______,
  _XX_____,XX______,
  __XX___X,X_______,
  __XX___X,X_______,
  ___XX_XX,________,
  ___XX_XX,________,
  ____XXX_,________,
  ____XXX_,________,
  _____X__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0077[ 33] = { // code 0077, LATIN SMALL LETTER W
  _XX_____,X_____XX,________,
  _XX____X,XX____XX,________,
  __X____X,XX____X_,________,
  __XX___X,_X___XX_,________,
  __XX__XX,_XX__XX_,________,
  ___XX_XX,_XX_XX__,________,
  ___XX_XX,_XX_XX__,________,
  ____X_X_,__X_X___,________,
  ____XXX_,__XXX___,________,
  ____XXX_,__XXX___,________,
  _____XX_,__XX____,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0078[ 22] = { // code 0078, LATIN SMALL LETTER X
  XXX____X,XX______,
  _XX____X,X_______,
  __XX__XX,________,
  __XX__XX,________,
  ___XXXX_,________,
  ____XX__,________,
  ___XXXX_,________,
  __XX__XX,________,
  __XX__XX,________,
  _XX____X,X_______,
  XXX____X,XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0079[ 30] = { // code 0079, LATIN SMALL LETTER Y
  XX_____X,X_______,
  XX_____X,X_______,
  _XX___XX,________,
  _XX___XX,________,
  _XXX__XX,________,
  __XX__XX,________,
  __XX_XX_,________,
  ___XXXX_,________,
  ___XXXX_,________,
  ____XX__,________,
  ____XX__,________,
  ____XX__,________,
  ___XX___,________,
  XXXXX___,________,
  XXXX____,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_007A[ 22] = { // code 007A, LATIN SMALL LETTER Z
  _XXXXXXX,X_______,
  _XXXXXXX,X_______,
  ______XX,X_______,
  _____XXX,________,
  ____XXX_,________,
  ___XXX__,________,
  __XXX___,________,
  _XXX____,________,
  XXX_____,________,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_007B[ 19] = { // code 007B, LEFT CURLY BRACKET
  ___XXX__,
  __XXXX__,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  _XXX____,
  XXX_____,
  XXX_____,
  _XX_____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XXXX__,
  ___XXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_007C[ 20] = { // code 007C, VERTICAL LINE
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_007D[ 19] = { // code 007D, RIGHT CURLY BRACKET
  XXX_____,
  XXXX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XXX___,
  ___XXX__,
  ___XXX__,
  __XXX___,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  XXXX____,
  XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_007E[  8] = { // code 007E, TILDE
  _XXX____,________,
  XXXXXX__,_X______,
  X___XXXX,XX______,
  ______XX,X_______};

//
// Start of unicode area <Hebrew (Basic and Extended)>
//
GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05B0[  3] = { // code 05B0, HEBREW POINT SHEVA
  X_______,
  ________,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05B1[  3] = { // code 05B1, HEBREW POINT HATAF SEGOL
  X_X_X___,
  ________,
  _X__X___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05B2[  3] = { // code 05B2, HEBREW POINT HATAF PATAH
  XXX_X___,
  ________,
  ____X___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05B3[  3] = { // code 05B3, HEBREW POINT HATAF QAMATS
  XXX_X___,
  _X______,
  ____X___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05B4[  1] = { // code 05B4, HEBREW POINT HIRIQ
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05B5[  1] = { // code 05B5, HEBREW POINT TSERE
  X_X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05B6[  3] = { // code 05B6, HEBREW POINT SEGOL
  X_X_____,
  ________,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05B7[  1] = { // code 05B7, HEBREW POINT PATAH
  XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05B8[  3] = { // code 05B8, HEBREW POINT QAMATS
  XXX_____,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05B9[  1] = { // code 05B9, HEBREW POINT HOLAM
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05BA[  1] = { // code 05BA
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05BB[  3] = { // code 05BB, HEBREW POINT QUBUTS
  X_______,
  __X_____,
  ____X___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05BC[  1] = { // code 05BC, HEBREW POINT DAGESH OR MAPIQ
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05BD[  3] = { // code 05BD, HEBREW POINT METEG
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05BE[  2] = { // code 05BE, HEBREW PUNCTUATION MAQAF
  XXXXX___,
  XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05BF[  1] = { // code 05BF, HEBREW POINT RAFE
  XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05C0[ 13] = { // code 05C0, HEBREW PUNCTUATION PASEQ
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05C1[  1] = { // code 05C1, HEBREW POINT SHIN DOT
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05C2[  1] = { // code 05C2, HEBREW POINT SIN DOT
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05C3[ 11] = { // code 05C3, HEBREW PUNCTUATION SOF PASUQ
  XX______,
  XX______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05D0[ 22] = { // code 05D0, HEBREW LETTER ALEF
  XX______,XX______,
  _XX_____,XX______,
  __XX____,XX______,
  ___XX__X,XX______,
  _XXXXX_X,X_______,
  _XX_XXXX,________,
  _XX__XX_,________,
  XX____XX,________,
  XX_____X,X_______,
  XX______,XX______,
  XX______,_XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05D1[ 22] = { // code 05D1, HEBREW LETTER BET
  XXXXX___,________,
  XXXXXX__,________,
  ____XXX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05D2[ 11] = { // code 05D2, HEBREW LETTER GIMEL
  _XXXX___,
  _XXXXX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  __XXXX__,
  _XXXXX__,
  _XX_XX__,
  XX___XX_,
  XX___XX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05D3[ 22] = { // code 05D3, HEBREW LETTER DALET
  XXXXXXXX,X_______,
  XXXXXXXX,X_______,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________,
  _____XX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05D4[ 22] = { // code 05D4, HEBREW LETTER HE
  XXXXXXX_,________,
  XXXXXXXX,________,
  ______XX,X_______,
  _______X,X_______,
  _______X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05D5[ 11] = { // code 05D5, HEBREW LETTER VAV
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05D6[ 11] = { // code 05D6, HEBREW LETTER ZAYIN
  XXXXXX__,
  XXXXXX__,
  __XX____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05D7[ 22] = { // code 05D7, HEBREW LETTER HET
  XXXXXXX_,________,
  XXXXXXXX,________,
  XX____XX,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05D8[ 11] = { // code 05D8, HEBREW LETTER TET
  XX__XXX_,
  XX_XXXXX,
  XX_X__XX,
  XX____XX,
  XX____XX,
  XX____XX,
  XX____XX,
  XX____XX,
  XXX__XXX,
  _XXXXXX_,
  __XXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05D9[  6] = { // code 05D9, HEBREW LETTER YOD
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05DA[ 30] = { // code 05DA, HEBREW LETTER FINAL KAF
  XXXXXX__,________,
  XXXXXXXX,________,
  _____XXX,________,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05DB[ 11] = { // code 05DB, HEBREW LETTER KAF
  XXXXX___,
  XXXXXX__,
  ____XXX_,
  _____XXX,
  ______XX,
  ______XX,
  ______XX,
  _____XXX,
  ____XXX_,
  XXXXXX__,
  XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05DC[ 15] = { // code 05DC, HEBREW LETTER LAMED
  XX______,
  XX______,
  XX______,
  XX______,
  XXXXXXXX,
  XXXXXXXX,
  ______XX,
  ______XX,
  ______XX,
  _____XX_,
  _____XX_,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05DD[ 22] = { // code 05DD, HEBREW LETTER FINAL MEM
  XXXXXXX_,________,
  XXXXXXXX,________,
  XX____XX,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05DE[ 22] = { // code 05DE, HEBREW LETTER MEM
  _XX__XXX,X_______,
  _XX_XXXX,XX______,
  __XXXX__,XXX_____,
  __XXX___,_XX_____,
  __XX____,_XX_____,
  __XX____,_XX_____,
  __XX____,_XX_____,
  __XX____,_XX_____,
  __X_____,_XX_____,
  _XX__XXX,XXX_____,
  _XX__XXX,XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05DF[ 15] = { // code 05DF, HEBREW LETTER FINAL NUN
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05E0[ 11] = { // code 05E0, HEBREW LETTER NUN
  XXXX____,
  XXXXX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  XXXXX___,
  XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05E1[ 22] = { // code 05E1, HEBREW LETTER SAMEKH
  ___XXXX_,________,
  _XXXXXXX,X_______,
  _XX____X,X_______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  XX______,XX______,
  _XX____X,X_______,
  _XXXXXXX,X_______,
  ___XXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05E2[ 24] = { // code 05E2, HEBREW LETTER AYIN
  _XX____X,X_______,
  _XX____X,X_______,
  _XX____X,X_______,
  __XX___X,X_______,
  __XX___X,X_______,
  __XX___X,X_______,
  __XX___X,X_______,
  __XX__XX,________,
  __XX_XXX,________,
  __XXXXX_,________,
  XXXXX___,________,
  XX______,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05E3[ 30] = { // code 05E3, HEBREW LETTER FINAL PE
  _XXXXX__,________,
  XXXXXXXX,________,
  XX____XX,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  XXXX___X,X_______,
  _XXX___X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05E4[ 22] = { // code 05E4, HEBREW LETTER PE
  _XXXXX__,________,
  XXXXXXXX,________,
  XX____XX,________,
  XX_____X,X_______,
  XXXX___X,X_______,
  _XXX___X,X_______,
  _______X,X_______,
  ______XX,X_______,
  X____XXX,________,
  XXXXXXX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05E5[ 30] = { // code 05E5, HEBREW LETTER FINAL TSADI
  XX_____X,X_______,
  XXX____X,X_______,
  _XX____X,X_______,
  _XXX__XX,X_______,
  __XX_XXX,________,
  __XXXXX_,________,
  ___XXX__,________,
  ___XX___,________,
  ___XX___,________,
  ___XX___,________,
  ___XX___,________,
  ___XX___,________,
  ___XX___,________,
  ___XX___,________,
  ___XX___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05E6[ 22] = { // code 05E6, HEBREW LETTER TSADI
  XX_____X,X_______,
  _XX____X,X_______,
  __XX___X,X_______,
  __XX___X,X_______,
  ___XX_XX,________,
  ____XXX_,________,
  _____X__,________,
  _____XX_,________,
  ______XX,________,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05E7[ 30] = { // code 05E7, HEBREW LETTER QOF
  XXXXXXXX,X_______,
  XXXXXXXX,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  XX____XX,________,
  XX____XX,________,
  XX___XX_,________,
  XX___XX_,________,
  XX___XX_,________,
  XX___XX_,________,
  XX______,________,
  XX______,________,
  XX______,________,
  XX______,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05E8[ 22] = { // code 05E8, HEBREW LETTER RESH
  XXXXXX__,________,
  XXXXXXXX,________,
  _____XXX,________,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05E9[ 22] = { // code 05E9, HEBREW LETTER SHIN
  XX____XX,___XX___,
  XX____XX,___XX___,
  XX____XX,___XX___,
  XX____XX,___XX___,
  XX___XX_,___XX___,
  XXXXXXX_,__XX____,
  _XX_____,__XX____,
  _XX_____,__XX____,
  _XXX____,XXX_____,
  __XXXXXX,XXX_____,
  ____XXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05EA[ 22] = { // code 05EA, HEBREW LETTER TAV
  XXXXXXXX,X_______,
  XXXXXXXX,XX______,
  ___XX___,XXX_____,
  ___XX___,_XX_____,
  ___XX___,_XX_____,
  ___XX___,_XX_____,
  ___XX___,_XX_____,
  ___XX___,_XX_____,
  ___XX___,_XX_____,
  XXXXX___,_XX_____,
  XXXX____,_XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05F0[ 11] = { // code 05F0, HEBREW LIGATURE YIDDISH DOUBLE VAV
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05F1[ 11] = { // code 05F1, HEBREW LIGATURE YIDDISH VAV YOD
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _____XX_,
  _____XX_,
  _____XX_,
  _____XX_,
  _____XX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05F2[  6] = { // code 05F2, HEBREW LIGATURE YIDDISH DOUBLE YOD
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05F3[  4] = { // code 05F3, HEBREW PUNCTUATION GERESH
  _XX_____,
  _X______,
  XX______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_05F4[  4] = { // code 05F4, HEBREW PUNCTUATION GERSHAYIM
  _XX__XX_,
  _X___X__,
  XX__XX__,
  X___X___};

//
// Start of unicode area <Arabic (Basic and Extended)>
//
GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_060C[  6] = { // code 060C, ARABIC COMMA
  _X______,
  X_______,
  X_______,
  XX______,
  XXX_____,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_061B[  9] = { // code 061B, ARABIC SEMICOLON
  _X______,
  X_______,
  X_______,
  XX______,
  XXX_____,
  _XX_____,
  ________,
  _XX_____,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_061F[ 12] = { // code 061F, ARABIC QUESTION MARK
  _XXXX___,
  XX___X__,
  XX__XX__,
  XX__XX__,
  XXX_____,
  _XXX____,
  __XX____,
  ___X____,
  ___X____,
  ________,
  __XX____,
  __XX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0621[  8] = { // code 0621, ARABIC LETTER HAMZA
  __XX____,
  _XXXX___,
  X_______,
  XX__XX__,
  XXXXXX__,
  _XXXX___,
  _XX_____,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0622[ 14] = { // code 0622, ARABIC LETTER ALEF WITH MADDA ABOVE
  XXXX____,
  ________,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0623[ 15] = { // code 0623, ARABIC LETTER ALEF WITH HAMZA ABOVE
  _XX_____,
  X_______,
  _XX_____,
  X_______,
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0624[ 17] = { // code 0624, ARABIC LETTER WAW WITH HAMZA ABOVE
  ___XX___,
  __X_____,
  ___XX___,
  __X_____,
  ________,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0625[ 17] = { // code 0625, ARABIC LETTER ALEF WITH HAMZA BELOW
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  ________,
  _XX_____,
  X_______,
  _XX_____,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0626[ 26] = { // code 0626, ARABIC LETTER YEH WITH HAMZA ABOVE
  _XX_____,________,
  X_______,________,
  _XX_____,_XXX____,
  X_______,XXXX____,
  _______X,X__X____,
  _X_____X,________,
  X_____X_,________,
  X_____XX,XXX_____,
  X_____XX,XXX_____,
  X_______,__X_____,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  _XXXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0627[ 12] = { // code 0627, ARABIC LETTER ALEF
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0628[ 22] = { // code 0628, ARABIC LETTER BEH
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__,
  ________,________,
  ________,________,
  ______XX,________,
  ______XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0629[ 11] = { // code 0629, ARABIC LETTER TEH MARBUTA
  __XX____,
  XXXX____,
  XX______,
  ________,
  _X______,
  _XXX____,
  _XXXX___,
  X___X___,
  X___X___,
  XXXXX___,
  XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_062A[ 20] = { // code 062A, ARABIC LETTER TEH
  _______X,X_______,
  _____XXX,X_______,
  _____XX_,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_062B[ 22] = { // code 062B, ARABIC LETTER THEH
  _____XX_,________,
  _____X_X,X_______,
  ______X_,X_______,
  _____XX_,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_062C[ 26] = { // code 062C, ARABIC LETTER JEEM
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X______,________,
  X_____XX,________,
  X_____XX,________,
  X_______,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_062D[ 26] = { // code 062D, ARABIC LETTER HAH
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_062E[ 34] = { // code 062E, ARABIC LETTER KHAH
  _____XX_,________,
  _____XX_,________,
  ________,________,
  ________,________,
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_062F[  9] = { // code 062F, ARABIC LETTER DAL
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0630[ 13] = { // code 0630, ARABIC LETTER THAL
  _XX_____,
  _XX_____,
  ________,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0631[ 22] = { // code 0631, ARABIC LETTER REH
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0632[ 30] = { // code 0632, ARABIC LETTER ZAIN
  _____XX_,________,
  _____XX_,________,
  ________,________,
  ________,________,
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0633[ 22] = { // code 0633, ARABIC LETTER SEEN
  ________,X_____X_,
  ________,XX__X_XX,
  _X______,XX__X__X,
  _X______,_X__X__X,
  X_______,_XXXXXXX,
  X_______,_XXX_XXX,
  X_______,_X______,
  X_______,XX______,
  XX_____X,X_______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0634[ 32] = { // code 0634, ARABIC LETTER SHEEN
  ________,___XX___,
  ________,___X_XX_,
  ________,____X_X_,
  ________,___XX___,
  ________,________,
  ________,X_____X_,
  ________,XX__X_XX,
  _X______,XX__X__X,
  _X______,_X__X__X,
  X_______,_XXXXXXX,
  X_______,_XXX_XXX,
  X_______,_X______,
  X_______,XX______,
  XX_____X,X_______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0635[ 33] = { // code 0635, ARABIC LETTER SAD
  ________,X_______,_XXXX___,
  ________,XX______,XXXXXX__,
  _X______,XX____XX,____XX__,
  _X______,_X___X__,____XX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_X______,________,
  X_______,XX______,________,
  XX_____X,X_______,________,
  XXXXXXXX,X_______,________,
  __XXXXX_,________,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0636[ 42] = { // code 0636, ARABIC LETTER DAD
  ________,_____XX_,________,
  ________,_____XX_,________,
  ________,________,________,
  ________,X_______,_XXXX___,
  ________,XX______,XXXXXX__,
  _X______,XX____XX,____XX__,
  _X______,_X___X__,____XX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_X______,________,
  X_______,XX______,________,
  XX_____X,X_______,________,
  XXXXXXXX,X_______,________,
  __XXXXX_,________,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0637[ 26] = { // code 0637, ARABIC LETTER TAH
  ___X____,________,
  ___XXX__,________,
  ____XX__,________,
  ____X___,________,
  ____XX__,________,
  _____X__,________,
  _____X__,________,
  _____X__,XXXX____,
  _____X_X,XXXXX___,
  _____XX_,___XX___,
  ____X___,___XX___,
  XXXXXXXX,XXXXX___,
  XXXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0638[ 26] = { // code 0638, ARABIC LETTER ZAH
  ___X____,________,
  ___XXX__,________,
  ____XX__,XX______,
  ____X___,XX______,
  ____XX__,________,
  _____X__,________,
  _____X__,________,
  _____X__,XXXX____,
  _____X_X,XXXXX___,
  _____XX_,___XX___,
  ____X___,___XX___,
  XXXXXXXX,XXXXX___,
  XXXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0639[ 34] = { // code 0639, ARABIC LETTER AIN
  __XXX___,________,
  _XXXXXX_,________,
  XXX_____,________,
  X_______,________,
  X_______,X_______,
  XXX__XXX,X_______,
  _XXXXXX_,________,
  __XXX___,________,
  __X_____,________,
  _X______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  XXXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_063A[ 42] = { // code 063A, ARABIC LETTER GHAIN
  ___XX___,________,
  ___XX___,________,
  ________,________,
  ________,________,
  __XXX___,________,
  _XXXXXX_,________,
  XXX_____,________,
  X_______,________,
  X_______,X_______,
  XXX__XXX,X_______,
  _XXXXXX_,________,
  __XXX___,________,
  __X_____,________,
  _X______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  XXXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0640[  2] = { // code 0640, ARABIC TATWEEL
  XXXXX___,
  XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0641[ 33] = { // code 0641, ARABIC LETTER FEH
  ________,_____XX_,________,
  ________,_____XX_,________,
  ________,________,________,
  ________,________,________,
  _X______,______XX,________,
  X_______,_____XXX,X_______,
  X_______,_____X__,X_______,
  X_______,_____X__,X_______,
  XXX_____,______XX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ___XXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0642[ 34] = { // code 0642, ARABIC LETTER QAF
  _______X,X_______,
  _____XXX,X_______,
  _____XX_,________,
  ________,________,
  ________,________,
  _______X,XX______,
  _______X,XX______,
  ______X_,_XX_____,
  _X____X_,_XX_____,
  _X____XX,XXX_____,
  X______X,XXX_____,
  X_______,__X_____,
  X_______,__X_____,
  X_______,_XX_____,
  XX______,XXX_____,
  _XXXXXXX,XX______,
  __XXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0643[ 26] = { // code 0643, ARABIC LETTER KAF
  ________,__XX____,
  ________,__XXX___,
  ________,___XX___,
  _______X,___X____,
  _____XX_,___X____,
  _____XXX,X__X____,
  ________,X__X____,
  _X_____X,X___X___,
  X___XXXX,____X___,
  X_______,____X___,
  XX______,____X___,
  XXXXXXXX,XXXXX___,
  _XXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0644[ 32] = { // code 0644, ARABIC LETTER LAM
  ________,X_______,
  ________,XX______,
  ________,XX______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  __X_____,_X______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0645[ 12] = { // code 0645, ARABIC LETTER MEEM
  __XXX___,
  _XXXXX__,
  ____XXX_,
  __XXXXX_,
  _XXXXXX_,
  XX______,
  X_______,
  X_______,
  X_______,
  _X______,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0646[ 28] = { // code 0646, ARABIC LETTER NOON
  ____XX__,________,
  ____XX__,________,
  ________,________,
  ________,X_______,
  ________,XX______,
  _X______,XX______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,XX______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0647[  7] = { // code 0647, ARABIC LETTER HEH
  _X______,
  _XXX____,
  _XXXX___,
  X___X___,
  X___X___,
  XXXXX___,
  XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0648[ 11] = { // code 0648, ARABIC LETTER WAW
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0649[ 22] = { // code 0649, ARABIC LETTER ALEF MAKSURA
  ________,_XXX____,
  ________,XXXX____,
  _______X,X__X____,
  _X_____X,________,
  X_____X_,________,
  X_____XX,XXX_____,
  X_____XX,XXX_____,
  X_______,__X_____,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  _XXXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_064A[ 28] = { // code 064A, ARABIC LETTER YEH
  ________,_XXX____,
  ________,XXXX____,
  _______X,X__X____,
  _X_____X,________,
  X_____X_,________,
  X_____XX,XXX_____,
  X_____XX,XXX_____,
  X_______,__X_____,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  _XXXXXX_,________,
  _____XX_,________,
  ___XXXX_,________,
  ___XX___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_064B[  4] = { // code 064B, ARABIC FATHATAN
  __XX____,
  XX______,
  __XX____,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_064C[  5] = { // code 064C, ARABIC DAMMATAN
  ____XX__,
  ___X_X__,
  XX_XXX__,
  _X_X_X__,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_064D[  4] = { // code 064D, ARABIC KASRATAN
  __XX____,
  XX______,
  __XX____,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_064E[  2] = { // code 064E, ARABIC FATHA
  __XX____,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_064F[  5] = { // code 064F, ARABIC DAMMA
  ___XX___,
  __X_X___,
  __XXX___,
  ___XX___,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0650[  2] = { // code 0650, ARABIC KASRA
  __XX____,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0651[  3] = { // code 0651, ARABIC SHADDA
  __X_X___,
  X_XXX___,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0652[  3] = { // code 0652, ARABIC SUKUN
  _XXX____,
  X__X____,
  XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0653[  2] = { // code 0653, ARABIC MADDAH ABOVE
  XX______,
  __XX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0654[  4] = { // code 0654, ARABIC HAMZA ABOVE
  _XX_____,
  X_______,
  _XX_____,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0655[  4] = { // code 0655, ARABIC HAMZA BELOW
  _XX_____,
  X_______,
  _XX_____,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0660[  5] = { // code 0660, ARABIC-INDIC DIGIT ZERO
  ________,
  XXX_____,
  XXX_____,
  XXX_____,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0661[ 12] = { // code 0661, ARABIC-INDIC DIGIT ONE
  X_______,
  XX______,
  XX______,
  _XX_____,
  _XX_____,
  _XX_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0662[ 12] = { // code 0662, ARABIC-INDIC DIGIT TWO
  X____X__,
  XX___X__,
  XXXXXX__,
  _XXXX___,
  __X_____,
  __X_____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0663[ 24] = { // code 0663, ARABIC-INDIC DIGIT THREE
  X___X___,X_______,
  X___X__X,X_______,
  XXXXXXXX,X_______,
  _XXX_XXX,________,
  _X______,________,
  _XX_____,________,
  __X_____,________,
  __X_____,________,
  __X_____,________,
  __X_____,________,
  __X_____,________,
  __X_____,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0664[ 12] = { // code 0664, ARABIC-INDIC DIGIT FOUR
  ____X___,
  ___XX___,
  __X_____,
  _X______,
  XXX_____,
  XXXXX___,
  __XX____,
  __X_____,
  _X______,
  XXX_____,
  XXXXXX__,
  _XXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0665[  8] = { // code 0665, ARABIC-INDIC DIGIT FIVE
  __XXX___,
  _XXXXX__,
  _X__XXX_,
  X____XX_,
  X_____X_,
  X____XX_,
  XXXXXX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0666[ 12] = { // code 0666, ARABIC-INDIC DIGIT SIX
  X_______,
  XXXXX___,
  XXXXX___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____XX__,
  ____XXX_,
  _____XX_,
  ______X_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0667[ 24] = { // code 0667, ARABIC-INDIC DIGIT SEVEN
  X______X,________,
  XX_____X,________,
  XX_____X,________,
  XXX____X,________,
  _XX___XX,________,
  __XX__X_,________,
  __XX_X__,________,
  ___X_X__,________,
  ___XX___,________,
  ____X___,________,
  ____X___,________,
  ____X___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0668[ 24] = { // code 0668, ARABIC-INDIC DIGIT EIGHT
  ____X___,________,
  ____X___,________,
  ____X___,________,
  ___XXX__,________,
  ___X_X__,________,
  __X__XX_,________,
  __X__XX_,________,
  _XX___XX,________,
  XX____XX,X_______,
  XX_____X,X_______,
  X______X,X_______,
  X_______,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0669[ 12] = { // code 0669, ARABIC-INDIC DIGIT NINE
  __XX____,
  _XXXX___,
  X___X___,
  X___X___,
  XXXXX___,
  _XXXX___,
  ____X___,
  ____X___,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_066A[ 28] = { // code 066A, ARABIC PERCENT SIGN
  XX______,X_______,
  XX_____X,________,
  _______X,________,
  ______X_,________,
  _____X__,________,
  _____X__,________,
  ____X___,________,
  ____X___,________,
  ___X____,________,
  ___X____,________,
  __X_____,________,
  _X______,________,
  _X_____X,X_______,
  X______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_066B[  5] = { // code 066B, ARABIC DECIMAL SEPARATOR
  XXX_____,
  XXX_____,
  XXX_____,
  _X______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_066C[  6] = { // code 066C, ARABIC THOUSANDS SEPARATOR
  _X______,
  X_______,
  X_______,
  XX______,
  XXX_____,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_066D[  7] = { // code 066D, ARABIC FIVE POINTED STAR
  ___X____,
  _X_X_X__,
  __XXX___,
  XXX_XXX_,
  __XXX___,
  _X_X_X__,
  ___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_066E[ 14] = { // code 066E, ARABIC LETTER DOTLESS BEH
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_066F[ 24] = { // code 066F, ARABIC LETTER DOTLESS QAF
  _______X,XX______,
  _______X,XX______,
  ______X_,_XX_____,
  _X____X_,_XX_____,
  _X____XX,XXX_____,
  X______X,XXX_____,
  X_______,__X_____,
  X_______,__X_____,
  X_______,_XX_____,
  XX______,XXX_____,
  _XXXXXXX,XX______,
  __XXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0671[ 16] = { // code 0671, ARABIC LETTER ALEF WASLA
  __XX____,
  _X_X____,
  XXXX____,
  X_______,
  __X_____,
  __X_____,
  _XX_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0672[ 16] = { // code 0672, ARABIC LETTER ALEF WITH WAVY HAMZA ABOVE
  __XX____,
  _X______,
  __XX____,
  XX______,
  ________,
  __X_____,
  _XX_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0673[ 17] = { // code 0673, ARABIC LETTER ALEF WITH WAVY HAMZA BELOW
  __X_____,
  __X_____,
  _XX_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  ________,
  __XX____,
  _X______,
  __XX____,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0674[  4] = { // code 0674, ARABIC LETTER HIGH HAMZA
  _XX_____,
  X_______,
  _XX_____,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0675[ 12] = { // code 0675, ARABIC LETTER HIGH HAMZA ALEF
  _X__XX__,
  _X_X____,
  XX__XX__,
  _X_X____,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0676[ 32] = { // code 0676, ARABIC LETTER HIGH HAMZA WAW
  _______X,X_______,
  ______X_,________,
  _______X,X_______,
  ______X_,________,
  ________,________,
  _____XX_,________,
  ____XXXX,________,
  ____X__X,________,
  ____X__X,________,
  ____XXXX,________,
  _____XXX,________,
  _______X,________,
  ______XX,________,
  _____XX_,________,
  X___XX__,________,
  _XXXX___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0677[ 32] = { // code 0677, ARABIC LETTER U WITH HAMZA ABOVE
  ___XX__X,X_______,
  __X_X_X_,________,
  __XXX__X,X_______,
  ___XX_X_,________,
  _XX_____,________,
  _____XX_,________,
  ____XXXX,________,
  ____X__X,________,
  ____X__X,________,
  ____XXXX,________,
  _____XXX,________,
  _______X,________,
  ______XX,________,
  _____XX_,________,
  X___XX__,________,
  _XXXX___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0678[ 32] = { // code 0678, ARABIC LETTER HIGH HAMZA YEH
  ________,___XX___,
  ________,__X_____,
  ________,___XX___,
  ________,__X_____,
  ________,________,
  ________,_XXX____,
  ________,XXXX____,
  _______X,X__X____,
  _X_____X,________,
  X_____X_,________,
  X_____XX,XXX_____,
  X_____XX,XXX_____,
  X_______,__X_____,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  _XXXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0679[ 30] = { // code 0679, ARABIC LETTER TTEH
  _____XX_,________,
  _____X__,________,
  ______X_,________,
  ______X_,________,
  ______X_,XX______,
  ______XX,_X______,
  ____XXXX,XX______,
  ________,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_067A[ 24] = { // code 067A, ARABIC LETTER TTEHEH
  _____XX_,________,
  _____XX_,________,
  ______XX,________,
  ______XX,________,
  ________,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_067B[ 24] = { // code 067B, ARABIC LETTER BEEH
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__,
  ________,________,
  ______XX,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_067C[ 24] = { // code 067C, ARABIC LETTER TEH WITH RING
  _______X,X_______,
  _____XXX,X_______,
  _____XX_,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__,
  _____X__,X_______,
  _____XXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_067D[ 24] = { // code 067D, ARABIC LETTER TEH WITH THREE DOTS ABOVE DOWNWARDS
  ______XX,________,
  ____X_X_,________,
  ____XX_X,________,
  ______XX,________,
  ________,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_067E[ 26] = { // code 067E, ARABIC LETTER PEH
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__,
  ________,________,
  ________,________,
  _______X,X_______,
  _____X_X,________,
  _____XX_,X_______,
  _______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_067F[ 24] = { // code 067F, ARABIC LETTER TEHEH
  _______X,X_______,
  _____XX_,X_______,
  ______XX,________,
  _____X_X,X_______,
  _____XX_,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0680[ 26] = { // code 0680, ARABIC LETTER BEHEH
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__,
  ________,________,
  _______X,X_______,
  _____XX_,X_______,
  ______XX,________,
  _____X_X,X_______,
  _____XX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0681[ 36] = { // code 0681, ARABIC LETTER HAH WITH HAMZA ABOVE
  _____XX_,________,
  ____X___,________,
  _____XX_,________,
  ____X___,________,
  ________,________,
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0682[ 38] = { // code 0682, ARABIC LETTER HAH WITH TWO DOTS VERTICAL ABOVE
  ___XX___,________,
  ___XX___,________,
  ____XX__,________,
  ____XX__,________,
  ________,________,
  ________,________,
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0683[ 26] = { // code 0683, ARABIC LETTER NYEH
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X______,________,
  X_______,________,
  X______X,X_______,
  X____XXX,X_______,
  X____XX_,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0684[ 26] = { // code 0684, ARABIC LETTER DYEH
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X______,________,
  X___XX__,________,
  X___XX__,________,
  X____XX_,________,
  X____XX_,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0685[ 38] = { // code 0685, ARABIC LETTER HAH WITH THREE DOTS ABOVE
  ___XX___,________,
  ___X_XX_,________,
  ____X_X_,________,
  ___XX___,________,
  ________,________,
  ________,________,
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0686[ 26] = { // code 0686, ARABIC LETTER TCHEH
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X____XX,________,
  X___X_X_,________,
  X___XX_X,________,
  X_____XX,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0687[ 26] = { // code 0687, ARABIC LETTER TCHEHEH
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X____XX,________,
  X___XX_X,________,
  X____XX_,________,
  X___X_XX,________,
  X___XX__,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0688[ 16] = { // code 0688, ARABIC LETTER DDAL
  _XX_____,
  _X______,
  __X_____,
  __X_____,
  __X_XX__,
  __XX_X__,
  XXXXXX__,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0689[ 11] = { // code 0689, ARABIC LETTER DAL WITH RING
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__,
  _X__X___,
  _XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_068A[ 12] = { // code 068A, ARABIC LETTER DAL WITH DOT BELOW
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  __XX____,
  __XX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_068B[ 19] = { // code 068B, ARABIC LETTER DAL WITH DOT BELOW AND SMALL TAH
  _XX_____,
  _X______,
  __X_____,
  __X_____,
  __X_XX__,
  __XX_X__,
  XXXXXX__,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  __XX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_068C[ 13] = { // code 068C, ARABIC LETTER DAHAL
  ___XX___,
  _XXXX___,
  _XX_____,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_068D[ 13] = { // code 068D, ARABIC LETTER DDAHAL
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  ___XX___,
  _XXXX___,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_068E[ 14] = { // code 068E, ARABIC LETTER DUL
  _XX_____,
  _X_XX___,
  __X_X___,
  _XX_____,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_068F[ 14] = { // code 068F, ARABIC LETTER DAL WITH THREE DOTS ABOVE DOWNWARDS
  ___XX___,
  _X_X____,
  _XX_X___,
  ___XX___,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0690[ 15] = { // code 0690, ARABIC LETTER DAL WITH FOUR DOTS ABOVE
  ___XX___,
  _XX_X___,
  __XX____,
  _X_XX___,
  _XX_____,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0691[ 40] = { // code 0691, ARABIC LETTER RREH
  ____XX__,________,
  ____X___,________,
  _____X__,________,
  _____X__,________,
  _____X_X,X_______,
  _____XX_,X_______,
  ___XXXXX,X_______,
  ________,________,
  ________,________,
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0692[ 30] = { // code 0692, ARABIC LETTER REH WITH SMALL V
  ____X_X_,________,
  _____X__,________,
  ________,________,
  ________,________,
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0693[ 24] = { // code 0693, ARABIC LETTER REH WITH RING
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XXX,X_______,
  _XXXXX__,X_______,
  _____XXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0694[ 24] = { // code 0694, ARABIC LETTER REH WITH DOT BELOW
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX_X,X_______,
  _______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0695[ 26] = { // code 0695, ARABIC LETTER REH WITH SMALL V BELOW
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________,
  ______X_,X_______,
  _______X,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0696[ 24] = { // code 0696, ARABIC LETTER REH WITH DOT BELOW AND DOT ABOVE
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  __XX____,X_______,
  __XX____,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX_X,X_______,
  _______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0697[ 32] = { // code 0697, ARABIC LETTER REH WITH TWO DOTS ABOVE
  ______XX,________,
  ____XXXX,________,
  ____XX__,________,
  ________,________,
  ________,________,
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0698[ 32] = { // code 0698, ARABIC LETTER JEH
  ____XX__,________,
  ____X_XX,________,
  _____X_X,________,
  ____XX__,________,
  ________,________,
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_0699[ 36] = { // code 0699, ARABIC LETTER REH WITH FOUR DOTS ABOVE
  ______XX,________,
  ____XX_X,________,
  _____XX_,________,
  ____X_XX,________,
  ____XX__,________,
  ________,________,
  ________,________,
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_069A[ 28] = { // code 069A, ARABIC LETTER SEEN WITH DOT BELOW AND DOT ABOVE
  ________,____XX__,
  ________,____XX__,
  ________,________,
  ________,X_____X_,
  ________,XX__X_XX,
  _X______,XX__X__X,
  _X______,_X__X__X,
  X_______,_XXXXXXX,
  X_______,_XXX_XXX,
  X_______,_X______,
  X_______,XX__XX__,
  XX_____X,X___XX__,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_069B[ 22] = { // code 069B, ARABIC LETTER SEEN WITH THREE DOTS BELOW
  ________,X_____X_,
  ________,XX__X_XX,
  _X______,XX__X__X,
  _X______,_X__X__X,
  X_______,_XXXXXXX,
  X_______,_XXX_XXX,
  X_______,_X______,
  X_______,XX____XX,
  XX_____X,X___X_X_,
  XXXXXXXX,X___XX_X,
  __XXXXX_,______XX};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_069C[ 34] = { // code 069C, ARABIC LETTER SEEN WITH THREE DOTS BELOW AND THREE DOTS ABOVE
  ________,___XX___,
  ________,___X_XX_,
  ________,____X_X_,
  ________,___XX___,
  ________,________,
  ________,________,
  ________,X_____X_,
  ________,XX__X_XX,
  _X______,XX__X__X,
  _X______,_X__X__X,
  X_______,_XXXXXXX,
  X_______,_XXX_XXX,
  X_______,_X______,
  X_______,XX____XX,
  XX_____X,X___X_X_,
  XXXXXXXX,X___XX_X,
  __XXXXX_,______XX};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_069D[ 33] = { // code 069D, ARABIC LETTER SAD WITH TWO DOTS BELOW
  ________,X_______,_XXXX___,
  ________,XX______,XXXXXX__,
  _X______,XX____XX,____XX__,
  _X______,_X___X__,____XX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_X______,________,
  X_______,XX______,XX______,
  XX_____X,X_____XX,XX______,
  XXXXXXXX,X_____XX,________,
  __XXXXX_,________,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_069E[ 51] = { // code 069E, ARABIC LETTER SAD WITH THREE DOTS ABOVE
  ________,______XX,________,
  ________,______X_,XX______,
  ________,_______X,_X______,
  ________,______XX,________,
  ________,________,________,
  ________,________,________,
  ________,X_______,_XXXX___,
  ________,XX______,XXXXXX__,
  _X______,XX____XX,____XX__,
  _X______,_X___X__,____XX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_X______,________,
  X_______,XX______,________,
  XX_____X,X_______,________,
  XXXXXXXX,X_______,________,
  __XXXXX_,________,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_069F[ 26] = { // code 069F, ARABIC LETTER TAH WITH THREE DOTS ABOVE
  ___X____,________,
  ___XXX__,XX______,
  ____XX__,X_XX____,
  ____X___,_X_X____,
  ____XX__,XX______,
  _____X__,________,
  _____X__,________,
  _____X__,XXXX____,
  _____X_X,XXXXX___,
  _____XX_,___XX___,
  ____X___,___XX___,
  XXXXXXXX,XXXXX___,
  XXXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06A0[ 44] = { // code 06A0, ARABIC LETTER AIN WITH THREE DOTS ABOVE
  __XX____,________,
  __X_XX__,________,
  ___X_X__,________,
  __XX____,________,
  ________,________,
  __XXX___,________,
  _XXXXXX_,________,
  XXX_____,________,
  X_______,________,
  X_______,X_______,
  XXX__XXX,X_______,
  _XXXXXX_,________,
  __XXX___,________,
  __X_____,________,
  _X______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  XXXX____,________,
  _XXXXXXX,XXX_____,
  ___XXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06A1[ 21] = { // code 06A1, ARABIC LETTER DOTLESS FEH
  _X______,______XX,________,
  X_______,_____XXX,X_______,
  X_______,_____X__,X_______,
  X_______,_____X__,X_______,
  XXX_____,______XX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ___XXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06A2[ 30] = { // code 06A2, ARABIC LETTER FEH WITH DOT MOVED BELOW
  _X______,______XX,________,
  X_______,_____XXX,X_______,
  X_______,_____X__,X_______,
  X_______,_____X__,X_______,
  XXX_____,______XX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ___XXXXX,XXXXXXXX,X_______,
  ________,________,________,
  ________,______XX,________,
  ________,______XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06A3[ 39] = { // code 06A3, ARABIC LETTER FEH WITH DOT BELOW
  ________,______XX,________,
  ________,______XX,________,
  ________,________,________,
  _X______,______XX,________,
  X_______,_____XXX,X_______,
  X_______,_____X__,X_______,
  X_______,_____X__,X_______,
  XXX_____,______XX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ___XXXXX,XXXXXXXX,X_______,
  ________,________,________,
  ________,XX______,________,
  ________,XX______,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06A4[ 39] = { // code 06A4, ARABIC LETTER VEH
  ________,____XX__,________,
  ________,____X_XX,________,
  ________,_____X_X,________,
  ________,____XX__,________,
  ________,________,________,
  ________,________,________,
  _X______,______XX,________,
  X_______,_____XXX,X_______,
  X_______,_____X__,X_______,
  X_______,_____X__,X_______,
  XXX_____,______XX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ___XXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06A5[ 36] = { // code 06A5, ARABIC LETTER FEH WITH THREE DOTS BELOW
  _X______,______XX,________,
  X_______,_____XXX,X_______,
  X_______,_____X__,X_______,
  X_______,_____X__,X_______,
  XXX_____,______XX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ___XXXXX,XXXXXXXX,X_______,
  ________,________,________,
  ________,_______X,X_______,
  ________,_____X_X,________,
  ________,_____XX_,X_______,
  ________,_______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06A6[ 39] = { // code 06A6, ARABIC LETTER PEHEH
  ________,______XX,________,
  ________,____XX_X,________,
  ________,_____XX_,________,
  ________,____X_XX,________,
  ________,____XX__,________,
  ________,________,________,
  _X______,______XX,________,
  X_______,_____XXX,X_______,
  X_______,_____X__,X_______,
  X_______,_____X__,X_______,
  XXX_____,______XX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ___XXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06A7[ 30] = { // code 06A7, ARABIC LETTER QAF WITH DOT ABOVE
  _______X,X_______,
  _______X,X_______,
  ________,________,
  _______X,XX______,
  _______X,XX______,
  ______X_,_XX_____,
  _X____X_,_XX_____,
  _X____XX,XXX_____,
  X______X,XXX_____,
  X_______,__X_____,
  X_______,__X_____,
  X_______,_XX_____,
  XX______,XXX_____,
  _XXXXXXX,XX______,
  __XXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06A8[ 34] = { // code 06A8, ARABIC LETTER QAF WITH THREE DOTS ABOVE
  ______XX,________,
  ______X_,XX______,
  _______X,_X______,
  ______XX,________,
  ________,________,
  _______X,XX______,
  _______X,XX______,
  ______X_,_XX_____,
  _X____X_,_XX_____,
  _X____XX,XXX_____,
  X______X,XXX_____,
  X_______,__X_____,
  X_______,__X_____,
  X_______,_XX_____,
  XX______,XXX_____,
  _XXXXXXX,XX______,
  __XXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06A9[ 36] = { // code 06A9, ARABIC LETTER KEHEH
  ________,_______X,________,
  ________,____XXXX,________,
  ________,___XXX__,________,
  ________,__XX____,________,
  ________,__X_____,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,______XX,________,
  XX______,_______X,X_______,
  XXXXXXXX,XXXXXXXX,X_______,
  _XXXXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06AA[ 33] = { // code 06AA, ARABIC LETTER SWASH KAF
  ________,X_______,________,
  ______XX,X_______,________,
  _____XX_,________,________,
  ____X___,________,________,
  ___X____,________,________,
  ___XXXXX,X_______,________,
  X___XXXX,XXXXXX__,________,
  X_______,_XXXXXXX,________,
  XX______,_______X,X_______,
  XXXXXXXX,XXXXXXXX,X_______,
  _XXXXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06AB[ 36] = { // code 06AB, ARABIC LETTER KAF WITH RING
  ________,_______X,________,
  ________,____XXXX,________,
  ________,___XXXXX,X_______,
  ________,__XX_X__,X_______,
  ________,__X__XXX,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,______XX,________,
  XX______,_______X,X_______,
  XXXXXXXX,XXXXXXXX,X_______,
  _XXXXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06AC[ 26] = { // code 06AC, ARABIC LETTER KAF WITH DOT ABOVE
  ______XX,__XX____,
  ______XX,__XXX___,
  ________,___XX___,
  _______X,___X____,
  _____XX_,___X____,
  _____XXX,X__X____,
  ________,X__X____,
  _X_____X,X___X___,
  X__XXXXX,____X___,
  X_______,____X___,
  XX______,____X___,
  XXXXXXXX,XXXXX___,
  _XXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06AD[ 30] = { // code 06AD, ARABIC LETTER NG
  ____XX__,________,
  ____X_XX,________,
  _____X_X,__XX____,
  ____XX__,__XXX___,
  ________,___XX___,
  _______X,___X____,
  _____XX_,___X____,
  _____XXX,X__X____,
  ________,X__X____,
  _X_____X,X___X___,
  X__XXXXX,____X___,
  X_______,____X___,
  XX______,____X___,
  XXXXXXXX,XXXXX___,
  _XXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06AE[ 38] = { // code 06AE, ARABIC LETTER KAF WITH THREE DOTS BELOW
  ________,__XX____,
  ________,__XXX___,
  ________,___XX___,
  _______X,___X____,
  _____XX_,___X____,
  _____XXX,X__X____,
  ________,X__X____,
  _X_____X,X___X___,
  X__XXXXX,____X___,
  X_______,____X___,
  XX______,____X___,
  XXXXXXXX,XXXXX___,
  _XXXXXXX,XXXXX___,
  ________,________,
  ________,________,
  _______X,X_______,
  _____X_X,________,
  _____XX_,X_______,
  _______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06AF[ 45] = { // code 06AF, ARABIC LETTER GAF
  ________,_______X,________,
  ________,_____XXX,________,
  ________,____XXX_,________,
  ________,___X___X,________,
  ________,__X_XXXX,________,
  ________,___XXX__,________,
  ________,__XX____,________,
  ________,__X_____,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,______XX,________,
  XX______,_______X,X_______,
  XXXXXXXX,XXXXXXXX,X_______,
  _XXXXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06B0[ 45] = { // code 06B0, ARABIC LETTER GAF WITH RING
  ________,_______X,________,
  ________,_____XXX,________,
  ________,____XXX_,________,
  ________,___X___X,________,
  ________,__X_XXXX,________,
  ________,___XXXXX,X_______,
  ________,__XX_X__,X_______,
  ________,__X__XXX,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,______XX,________,
  XX______,_______X,X_______,
  XXXXXXXX,XXXXXXXX,X_______,
  _XXXXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06B1[ 48] = { // code 06B1, ARABIC LETTER NGOEH
  ________,___XX___,________,
  ________,_XXXX__X,________,
  ________,_XX__XXX,________,
  ________,____XXX_,________,
  ________,___X___X,________,
  ________,__X_XXXX,________,
  ________,___XXX__,________,
  ________,__XX____,________,
  ________,__X_____,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,______XX,________,
  XX______,_______X,X_______,
  XXXXXXXX,XXXXXXXX,X_______,
  _XXXXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06B2[ 57] = { // code 06B2, ARABIC LETTER GAF WITH TWO DOTS BELOW
  ________,_______X,________,
  ________,_____XXX,________,
  ________,____XXX_,________,
  ________,___X___X,________,
  ________,__X_XXXX,________,
  ________,___XXX__,________,
  ________,__XX____,________,
  ________,__X_____,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,______XX,________,
  XX______,_______X,X_______,
  XXXXXXXX,XXXXXXXX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ________,________,________,
  ________,_XX_____,________,
  _______X,XXX_____,________,
  _______X,X_______,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06B3[ 60] = { // code 06B3, ARABIC LETTER GUEH
  ________,_______X,________,
  ________,_____XXX,________,
  ________,____XXX_,________,
  ________,___X___X,________,
  ________,__X_XXXX,________,
  ________,___XXX__,________,
  ________,__XX____,________,
  ________,__X_____,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,______XX,________,
  XX______,_______X,X_______,
  XXXXXXXX,XXXXXXXX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ________,________,________,
  _______X,X_______,________,
  _______X,X_______,________,
  ________,XX______,________,
  ________,XX______,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06B4[ 48] = { // code 06B4, ARABIC LETTER GAF WITH THREE DOTS ABOVE
  ________,__XX____,________,
  ________,____XX_X,________,
  ________,__XX__XX,________,
  ________,____XXX_,________,
  ________,___X___X,________,
  ________,__X_XXXX,________,
  ________,___XXX__,________,
  ________,__XX____,________,
  ________,__X_____,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,______XX,________,
  XX______,_______X,X_______,
  XXXXXXXX,XXXXXXXX,X_______,
  _XXXXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06B5[ 36] = { // code 06B5, ARABIC LETTER LAM WITH SMALL V
  _______X,_X______,
  ________,X_______,
  ________,________,
  ________,XX______,
  ________,XX______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  __X_____,_X______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06B6[ 36] = { // code 06B6, ARABIC LETTER LAM WITH DOT ABOVE
  ________,XX______,
  ________,XX______,
  ________,________,
  ________,XX______,
  ________,XX______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  __X_____,_X______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06B7[ 38] = { // code 06B7, ARABIC LETTER LAM WITH THREE DOTS ABOVE
  ______XX,________,
  ________,XX______,
  ______XX,________,
  ________,________,
  ________,XX______,
  ________,XX______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  __X_____,_X______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06B8[ 40] = { // code 06B8, ARABIC LETTER LAM WITH THREE DOTS BELOW
  ________,X_______,
  ________,XX______,
  ________,XX______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  __X_____,_X______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXXX,________,
  _____XX_,________,
  ___X_X__,________,
  ___XX_X_,________,
  _____XX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06B9[ 32] = { // code 06B9, ARABIC LETTER NOON WITH DOT BELOW
  ____XX__,________,
  ____XX__,________,
  ________,________,
  ________,X_______,
  ________,XX______,
  _X______,XX______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,XX______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXX_,________,
  ____XX__,________,
  ____XX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06BA[ 22] = { // code 06BA, ARABIC LETTER NOON GHUNNA
  ________,X_______,
  ________,XX______,
  _X______,XX______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,XX______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06BB[ 38] = { // code 06BB, ARABIC LETTER RNOON
  ___XX___,________,
  ___X____,________,
  ____X___,________,
  ____X___,________,
  ____X_XX,________,
  ____XX_X,________,
  __XXXXXX,________,
  ________,________,
  ________,X_______,
  ________,XX______,
  _X______,XX______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,XX______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06BC[ 32] = { // code 06BC, ARABIC LETTER NOON WITH RING
  ____XX__,________,
  ____XX__,________,
  ________,________,
  ________,X_______,
  ________,XX______,
  _X______,XX______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,XX______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXX_,________,
  ___X__X_,________,
  ___XXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06BD[ 34] = { // code 06BD, ARABIC LETTER NOON WITH THREE DOTS ABOVE
  ___XX___,________,
  ___X_XX_,________,
  ____X_X_,________,
  ___XX___,________,
  ________,________,
  ________,________,
  ________,X_______,
  ________,XX______,
  _X______,XX______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,XX______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06BE[ 18] = { // code 06BE, ARABIC LETTER HEH DOACHASHMEE
  ____X___,________,
  ____XX__,________,
  ____XXX_,________,
  ___XXXX_,________,
  __X__XXX,________,
  __X__X_X,X_______,
  ___XX___,X_______,
  XXXXXXXX,X_______,
  XXX___XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06BF[ 34] = { // code 06BF, ARABIC LETTER TCHEH WITH DOT ABOVE
  ____XX__,________,
  ____XX__,________,
  ________,________,
  ________,________,
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X____XX,________,
  X___X_X_,________,
  X___XX_X,________,
  X_____XX,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06C0[ 12] = { // code 06C0, ARABIC LETTER HEH WITH YEH ABOVE
  __XX____,
  _X______,
  __XX____,
  _X______,
  ________,
  _X______,
  _XXX____,
  _XXXX___,
  X___X___,
  X___X___,
  XXXXX___,
  XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06C1[  6] = { // code 06C1, ARABIC LETTER HEH GOAL
  ___XX___,
  __XXXX__,
  _XX__XXX,
  _X____XX,
  XX______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06C2[ 11] = { // code 06C2, ARABIC LETTER HEH GOAL WITH HAMZA ABOVE
  ___XX___,
  __X_____,
  ___XX___,
  __X_____,
  ________,
  ___XX___,
  __XXXX__,
  _XX__XXX,
  _X____XX,
  XX______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06C3[ 10] = { // code 06C3, ARABIC LETTER TEH MARBUTA GOAL
  ____XX__,
  __XXXX__,
  __XX____,
  ________,
  ___XX___,
  __XXXX__,
  _XX__XXX,
  _X____XX,
  XX______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06C4[ 11] = { // code 06C4, ARABIC LETTER WAW WITH RING
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ___XXXXX,
  __X__XX_,
  X_XXXX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06C5[ 11] = { // code 06C5, ARABIC LETTER KIRGHIZ OE
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  __XX___X,
  ____XXXX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06C6[ 14] = { // code 06C6, ARABIC LETTER OE
  ____X_X_,
  _____X__,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06C7[ 17] = { // code 06C7, ARABIC LETTER U
  ______XX,
  _____X_X,
  _____XXX,
  ______XX,
  ____XX__,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06C8[ 18] = { // code 06C8, ARABIC LETTER YU
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06C9[ 14] = { // code 06C9, ARABIC LETTER KIRGHIZ YU
  _____X__,
  ____X_X_,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06CA[ 15] = { // code 06CA, ARABIC LETTER WAW WITH TWO DOTS ABOVE
  ______XX,
  ____XXXX,
  ____XX__,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06CB[ 16] = { // code 06CB, ARABIC LETTER VE
  ___XX___,
  ___X_XX_,
  ____X_X_,
  ___XX___,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06CC[ 22] = { // code 06CC, ARABIC LETTER FARSI YEH
  ________,_XXX____,
  ________,XXXX____,
  _______X,X__X____,
  _X_____X,________,
  X_____X_,________,
  X_____XX,XXX_____,
  X_____XX,XXX_____,
  X_______,__X_____,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  _XXXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06CD[ 22] = { // code 06CD, ARABIC LETTER YEH WITH TAIL
  ________,__XXX___,
  ________,_XXXX___,
  ________,X___X___,
  __X_____,X_______,
  XXX____X,________,
  _X_____X,XXXX____,
  _X_____X,XXXX____,
  _X______,___X____,
  _XX_____,XXX_____,
  _XXXXXXX,XX______,
  __XXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06CE[ 24] = { // code 06CE, ARABIC LETTER YEH WITH SMALL V
  ___X_X__,________,
  ____X___,_XXX____,
  ________,XXXX____,
  _______X,X__X____,
  _X_____X,________,
  X_____X_,________,
  X_____XX,XXX_____,
  X_____XX,XXX_____,
  X_______,__X_____,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  _XXXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06CF[ 14] = { // code 06CF, ARABIC LETTER WAW WITH DOT ABOVE
  ____XX__,
  ____XX__,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06D0[ 28] = { // code 06D0, ARABIC LETTER E
  ________,_XXX____,
  ________,XXXX____,
  _______X,X__X____,
  _X_____X,________,
  X_____X_,________,
  X_____XX,XXX_____,
  X_____XX,XXX_____,
  X_______,__X_____,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  _XXXXXX_,________,
  ________,________,
  ____X___,________,
  ____X___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06D1[ 28] = { // code 06D1, ARABIC LETTER YEH WITH THREE DOTS BELOW
  ________,_XXX____,
  ________,XXXX____,
  _______X,X__X____,
  _X_____X,________,
  X_____X_,________,
  X_____XX,XXX_____,
  X_____XX,XXX_____,
  X_______,__X_____,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  _XXXXXX_,________,
  ________,________,
  ___X_X__,________,
  ____X___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06D2[ 18] = { // code 06D2, ARABIC LETTER YEH BARREE
  ______XX,________,
  _____XXX,X_______,
  ____XX__,X_______,
  ___XX___,________,
  __XX____,________,
  _XX_____,________,
  X_______,________,
  XXXXXXXX,XXXXXXX_,
  XXXXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06D3[ 24] = { // code 06D3, ARABIC LETTER YEH BARREE WITH HAMZA ABOVE
  ___XX___,________,
  __X_____,________,
  ___XX___,________,
  __X___XX,________,
  _____XXX,X_______,
  ____XX__,X_______,
  ___XX___,________,
  __XX____,________,
  _XX_____,________,
  X_______,________,
  XXXXXXXX,XXXXXXXX,
  XXXXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06D4[  2] = { // code 06D4, ARABIC FULL STOP
  XXX_____,
  XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06D5[  7] = { // code 06D5, ARABIC LETTER AE
  _X______,
  _XXX____,
  _XXXX___,
  X___X___,
  X___X___,
  XXXXX___,
  XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06DD[ 69] = { // code 06DD, ARABIC END OF AYAH
  ________,XXXXXX__,________,
  ____XXXX,______XX,XX______,
  ____X_XX,XXXXXXXX,_X______,
  ___XXX__,________,XXX_____,
  __XX____,________,__XX____,
  __X_____,________,___X____,
  _X______,________,____X___,
  _X______,________,____X___,
  X_______,________,_____X__,
  X_______,________,_____X__,
  X_______,________,_____X__,
  X_______,________,_____X__,
  X_______,________,_____X__,
  X_______,________,_____X__,
  X_______,________,_____X__,
  _X______,________,____X___,
  _X______,________,____X___,
  __X_____,________,___X____,
  __XX____,________,__XX____,
  ___XXX__,________,XXX_____,
  ____X_XX,XXXXXXXX,_X______,
  ____XXXX,______XX,XX______,
  ________,XXXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06DE[ 69] = { // code 06DE, ARABIC START OF RUB EL HIZB
  ________,___X____,________,
  ________,__X_X___,________,
  ________,_X___X__,________,
  ___XXXXX,XXXXXXXX,XXXX____,
  ___X___X,_______X,___X____,
  ___X__X_,________,X__X____,
  ___X_X__,________,_X_X____,
  ___XX___,________,__XX____,
  ___X____,________,___X____,
  __XX____,__XXX___,___XX___,
  _X_X____,_X___X__,___X_X__,
  X__X____,_X___X__,___X__X_,
  _X_X____,_X___X__,___X_X__,
  __XX____,__XXX___,___XX___,
  ___X____,________,___X____,
  ___XX___,________,__XX____,
  ___X_X__,________,_X_X____,
  ___X__X_,________,X__X____,
  ___X___X,_______X,___X____,
  ___XXXXX,XXXXXXXX,XXXX____,
  ________,_X___X__,________,
  ________,__X_X___,________,
  ________,___X____,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06E5[  5] = { // code 06E5, ARABIC SMALL WAW
  __XX____,
  _X_X____,
  _XXX____,
  ___X____,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06E6[  4] = { // code 06E6, ARABIC SMALL YEH
  ___XX___,
  _XX_X___,
  X_______,
  XXXXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06E9[ 36] = { // code 06E9, ARABIC PLACE OF SAJDAH
  _______X,________,
  _____XX_,XX______,
  ____X__X,__X_____,
  ___X_XX_,XX_X____,
  _XX_X__X,__X_XX__,
  X__X_XX_,XX_X__X_,
  _XXXX___,_XXXXX__,
  __X_XXX_,X_X_X___,
  ___XX_X_,X_XX____,
  ___XX_X_,X_XX____,
  ___XX_X_,X_XX____,
  ___XX_X_,X_XX____,
  ___XX_X_,X_XX____,
  ___XX_XX,X_XX____,
  __XXX___,__XXX___,
  __X_XXXX,XXX_X___,
  _X______,_____X__,
  XXXXXXXX,XXXXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06F0[  5] = { // code 06F0, EXTENDED ARABIC-INDIC DIGIT ZERO
  ________,
  XXX_____,
  XXX_____,
  XXX_____,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06F1[ 12] = { // code 06F1, EXTENDED ARABIC-INDIC DIGIT ONE
  X_______,
  XX______,
  XX______,
  _XX_____,
  _XX_____,
  _XX_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06F2[ 12] = { // code 06F2, EXTENDED ARABIC-INDIC DIGIT TWO
  X____X__,
  XX___X__,
  XXXXXX__,
  _XXXX___,
  __X_____,
  __X_____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06F3[ 24] = { // code 06F3, EXTENDED ARABIC-INDIC DIGIT THREE
  X___X___,X_______,
  X___X__X,X_______,
  XXXXXXXX,X_______,
  _XXX_XXX,________,
  _X______,________,
  _XX_____,________,
  __X_____,________,
  __X_____,________,
  __X_____,________,
  __X_____,________,
  __X_____,________,
  __X_____,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06F4[ 12] = { // code 06F4, EXTENDED ARABIC-INDIC DIGIT FOUR
  X___XX__,
  X__XX___,
  XX_X___X,
  _XXX__XX,
  _XXXXXX_,
  _XXXXX__,
  __X_____,
  __XX____,
  __XX____,
  __X_____,
  __X_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06F5[ 12] = { // code 06F5, EXTENDED ARABIC-INDIC DIGIT FIVE
  ___X____,
  ___XX___,
  ___XX___,
  ___XXX__,
  __X_XX__,
  __X__XX_,
  _X___XX_,
  _X____X_,
  XX____X_,
  XX____X_,
  XXXXXX__,
  _XXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06F6[ 12] = { // code 06F6, EXTENDED ARABIC-INDIC DIGIT SIX
  ___XX___,
  __XXXX__,
  _X______,
  X_____X_,
  XXXXXXX_,
  XXXXXX__,
  ___X____,
  __XX____,
  __X_____,
  _XX_____,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06F7[ 24] = { // code 06F7, EXTENDED ARABIC-INDIC DIGIT SEVEN
  X______X,________,
  XX_____X,________,
  XX_____X,________,
  XXX____X,________,
  _XX___XX,________,
  __XX__X_,________,
  __XX_X__,________,
  ___X_X__,________,
  ___XX___,________,
  ____X___,________,
  ____X___,________,
  ____X___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06F8[ 24] = { // code 06F8, EXTENDED ARABIC-INDIC DIGIT EIGHT
  ____X___,________,
  ____X___,________,
  ____X___,________,
  ___XXX__,________,
  ___X_X__,________,
  __X__XX_,________,
  __X__XX_,________,
  _XX___XX,________,
  XX____XX,X_______,
  XX_____X,X_______,
  X______X,X_______,
  X_______,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06F9[ 12] = { // code 06F9, EXTENDED ARABIC-INDIC DIGIT NINE
  __XX____,
  _XXXX___,
  X___X___,
  X___X___,
  XXXXX___,
  _XXXX___,
  ____X___,
  ____X___,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06FA[ 34] = { // code 06FA, ARABIC LETTER SHEEN WITH DOT BELOW
  ________,___XX___,
  ________,___X_XX_,
  ________,____X_X_,
  ________,___XX___,
  ________,________,
  ________,________,
  ________,X_____X_,
  ________,XX__X_XX,
  _X______,XX__X__X,
  _X______,_X__X__X,
  X_______,_XXXXXXX,
  X_______,_XXX_XXX,
  X_______,_X______,
  X_______,XX______,
  XX_____X,X___XX__,
  XXXXXXXX,X___XX__,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06FB[ 42] = { // code 06FB, ARABIC LETTER DAD WITH DOT BELOW
  ________,_____XX_,________,
  ________,_____XX_,________,
  ________,________,________,
  ________,X_______,_XXXX___,
  ________,XX______,XXXXXX__,
  _X______,XX____XX,____XX__,
  _X______,_X___X__,____XX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_X______,________,
  X_______,XX_____X,X_______,
  XX_____X,X______X,X_______,
  XXXXXXXX,X_______,________,
  __XXXXX_,________,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06FC[ 42] = { // code 06FC, ARABIC LETTER GHAIN WITH DOT BELOW
  ___XX___,________,
  ___XX___,________,
  ________,________,
  ________,________,
  __XXX___,________,
  _XXXXXX_,________,
  XXX_____,________,
  X_______,________,
  X_______,X_______,
  XXX__XXX,X_______,
  _XXXXXX_,________,
  __XXX___,________,
  __X_____,________,
  _X______,________,
  X_______,________,
  X____XX_,________,
  X____XX_,________,
  XX______,________,
  XXXX____,________,
  _XXXXXXX,XXX_____,
  ___XXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06FD[ 12] = { // code 06FD, ARABIC SIGN SINDHI AMPERSAND
  __XX____,
  _XXXX___,
  X_______,
  XX__XX__,
  XXXXXX__,
  _XXXX___,
  _XX_____,
  ________,
  __X_X___,
  __X_X___,
  __X_X___,
  __X_X___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_06FE[ 12] = { // code 06FE, ARABIC SIGN SINDHI POSTPOSITION MEN
  __XXX___,
  _XXXXX__,
  ____XXX_,
  __XXXXX_,
  _XXXXXX_,
  XX______,
  X_______,
  X__X_X__,
  XX_X_X__,
  _X_X_X__,
  _X_X_X__,
  _X______};

//
// Start of unicode area <Arabic Presentation Forms-A>
//
GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB50[ 16] = { // code FB50, ARABIC LETTER ALEF WASLA ISOLATED FORM
  __XX____,
  _X_X____,
  XXXX____,
  X_______,
  __X_____,
  __X_____,
  _XX_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB51[ 16] = { // code FB51, ARABIC LETTER ALEF WASLA FINAL FORM
  __XX____,
  _X_X____,
  XXXX____,
  X_______,
  _X______,
  XX______,
  XX______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _XX_____,
  _XXXX___,
  __XXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB52[ 24] = { // code FB52, ARABIC LETTER BEEH ISOLATED FORM
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__,
  ________,________,
  ______XX,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB53[ 24] = { // code FB53, ARABIC LETTER BEEH FINAL FORM
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__,
  ________,________,
  ______XX,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB54[ 12] = { // code FB54, ARABIC LETTER BEEH INITIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  __XX____,
  __XX____,
  ___XX___,
  ___XX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB55[ 12] = { // code FB55, ARABIC LETTER BEEH MEDIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  __XX____,
  __XX____,
  ___XX___,
  ___XX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB56[ 26] = { // code FB56, ARABIC LETTER PEH ISOLATED FORM
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__,
  ________,________,
  ________,________,
  _______X,X_______,
  _____X_X,________,
  _____XX_,X_______,
  _______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB57[ 26] = { // code FB57, ARABIC LETTER PEH FINAL FORM
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__,
  ________,________,
  ________,________,
  _______X,X_______,
  _____X_X,________,
  _____XX_,X_______,
  _______X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB58[ 13] = { // code FB58, ARABIC LETTER PEH INITIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  ________,
  ___XX___,
  _X_X____,
  _XX_X___,
  ___XX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB59[ 13] = { // code FB59, ARABIC LETTER PEH MEDIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  ________,
  ___XX___,
  _X_X____,
  _XX_X___,
  ___XX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB5A[ 26] = { // code FB5A, ARABIC LETTER BEHEH ISOLATED FORM
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__,
  ________,________,
  _______X,X_______,
  _____XX_,X_______,
  ______XX,________,
  _____X_X,X_______,
  _____XX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB5B[ 26] = { // code FB5B, ARABIC LETTER BEHEH FINAL FORM
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__,
  ________,________,
  _______X,X_______,
  _____XX_,X_______,
  ______XX,________,
  _____X_X,X_______,
  _____XX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB5C[ 13] = { // code FB5C, ARABIC LETTER BEHEH INITIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  ___XX___,
  _XX_X___,
  __XX____,
  _X_XX___,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB5D[ 13] = { // code FB5D, ARABIC LETTER BEHEH MEDIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  ___XX___,
  _XX_X___,
  __XX____,
  _X_XX___,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB5E[ 24] = { // code FB5E, ARABIC LETTER TTEHEH ISOLATED FORM
  _____XX_,________,
  _____XX_,________,
  ______XX,________,
  ______XX,________,
  ________,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB5F[ 24] = { // code FB5F, ARABIC LETTER TTEHEH FINAL FORM
  _____XX_,________,
  _____XX_,________,
  ______XX,________,
  ______XX,________,
  ________,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB60[ 12] = { // code FB60, ARABIC LETTER TTEHEH INITIAL FORM
  __XX____,
  __XX____,
  ___XX___,
  ___XX___,
  ________,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB61[ 12] = { // code FB61, ARABIC LETTER TTEHEH MEDIAL FORM
  __XX____,
  __XX____,
  ___XX___,
  ___XX___,
  ________,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB62[ 24] = { // code FB62, ARABIC LETTER TEHEH ISOLATED FORM
  _______X,X_______,
  _____XX_,X_______,
  ______XX,________,
  _____X_X,X_______,
  _____XX_,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB63[ 24] = { // code FB63, ARABIC LETTER TEHEH FINAL FORM
  _______X,X_______,
  _____XX_,X_______,
  ______XX,________,
  _____X_X,X_______,
  _____XX_,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB64[ 12] = { // code FB64, ARABIC LETTER TEHEH INITIAL FORM
  ___XX___,
  _XX_X___,
  __XX____,
  _X_XX___,
  _XX_____,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB65[ 12] = { // code FB65, ARABIC LETTER TEHEH MEDIAL FORM
  ___XX___,
  _XX_X___,
  __XX____,
  _X_XX___,
  _XX_____,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB66[ 30] = { // code FB66, ARABIC LETTER TTEH ISOLATED FORM
  _____XX_,________,
  _____X__,________,
  ______X_,________,
  ______X_,________,
  ______X_,XX______,
  ______XX,_X______,
  ____XXXX,XX______,
  ________,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB67[ 30] = { // code FB67, ARABIC LETTER TTEH FINAL FORM
  _____XX_,________,
  _____X__,________,
  ______X_,________,
  ______X_,________,
  ______X_,XX______,
  ______XX,_X______,
  ____XXXX,XX______,
  ________,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB68[ 15] = { // code FB68, ARABIC LETTER TTEH INITIAL FORM
  __XX____,
  __X_____,
  ___X____,
  ___X____,
  ___X_XX_,
  ___XX_X_,
  _XXXXXX_,
  ________,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB69[ 15] = { // code FB69, ARABIC LETTER TTEH MEDIAL FORM
  __XX____,
  __X_____,
  ___X____,
  ___X____,
  ___X_XX_,
  ___XX_X_,
  _XXXXXX_,
  ________,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB6A[ 39] = { // code FB6A, ARABIC LETTER VEH ISOLATED FORM
  ________,____XX__,________,
  ________,____X_XX,________,
  ________,_____X_X,________,
  ________,____XX__,________,
  ________,________,________,
  ________,________,________,
  _X______,______XX,________,
  X_______,_____XXX,X_______,
  X_______,_____X__,X_______,
  X_______,_____X__,X_______,
  XXX_____,______XX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ___XXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB6B[ 39] = { // code FB6B, ARABIC LETTER VEH FINAL FORM
  ________,____XX__,________,
  ________,____X_XX,________,
  ________,_____X_X,________,
  ________,____XX__,________,
  ________,________,________,
  ________,________,________,
  _X______,______XX,________,
  X_______,_____XXX,X_______,
  X_______,_____X__,X_______,
  X_______,_____X__,X_______,
  XXX_____,______XX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ___XXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB6C[ 14] = { // code FB6C, ARABIC LETTER VEH INITIAL FORM
  __XX____,
  __X_XX__,
  ___X_X__,
  __XX____,
  ________,
  ___XX___,
  __XXXX__,
  __X_XXX_,
  __X__XX_,
  __XXXXX_,
  ___XXXX_,
  ______X_,
  XXXXXXX_,
  XXXXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB6D[ 14] = { // code FB6D, ARABIC LETTER VEH MEDIAL FORM
  __XX____,
  __X_XX__,
  ___X_X__,
  __XX____,
  ________,
  ________,
  ____XX__,
  ___XXXX_,
  ___X_XX_,
  ___X__X_,
  ___XXXX_,
  _____XX_,
  XXXXXXX_,
  XXXXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB6E[ 39] = { // code FB6E, ARABIC LETTER PEHEH ISOLATED FORM
  ________,______XX,________,
  ________,____XX_X,________,
  ________,_____XX_,________,
  ________,____X_XX,________,
  ________,____XX__,________,
  ________,________,________,
  _X______,______XX,________,
  X_______,_____XXX,X_______,
  X_______,_____X__,X_______,
  X_______,_____X__,X_______,
  XXX_____,______XX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ___XXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB6F[ 39] = { // code FB6F, ARABIC LETTER PEHEH FINAL FORM
  ________,______XX,________,
  ________,____XX_X,________,
  ________,_____XX_,________,
  ________,____X_XX,________,
  ________,____XX__,________,
  ________,________,________,
  _X______,______XX,________,
  X_______,_____XXX,X_______,
  X_______,_____X__,X_______,
  X_______,_____X__,X_______,
  XXX_____,______XX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ___XXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB70[ 15] = { // code FB70, ARABIC LETTER PEHEH INITIAL FORM
  ____XX__,
  __XX_X__,
  ___XX___,
  __X_XX__,
  __XX____,
  ________,
  ___XX___,
  __XXXX__,
  __X_XXX_,
  __X__XX_,
  __XXXXX_,
  ___XXXX_,
  ______X_,
  XXXXXXX_,
  XXXXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB71[ 14] = { // code FB71, ARABIC LETTER PEHEH MEDIAL FORM
  ____XX__,
  __XX_X__,
  ___XX___,
  __X_XX__,
  __XX____,
  ________,
  ____XX__,
  ___XXXX_,
  ___X_XX_,
  ___X__X_,
  ___XXXX_,
  _____XX_,
  XXXXXXX_,
  XXXXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB72[ 26] = { // code FB72, ARABIC LETTER DYEH ISOLATED FORM
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X______,________,
  X___XX__,________,
  X___XX__,________,
  X____XX_,________,
  X____XX_,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB73[ 26] = { // code FB73, ARABIC LETTER DYEH FINAL FORM
  _XXXXXXX,X_______,
  XXXXXXXX,X_______,
  ____XXX_,________,
  __XX__X_,________,
  _X____XX,XX______,
  X__XX__X,XX______,
  X__XX___,________,
  X___XX__,________,
  X___XX__,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,X_______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB74[ 22] = { // code FB74, ARABIC LETTER DYEH INITIAL FORM
  ___XXX__,________,
  __XXXXXX,________,
  _____XXX,X_______,
  _______X,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____,
  ________,________,
  _____XX_,________,
  _____XX_,________,
  ______XX,________,
  ______XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB75[ 22] = { // code FB75, ARABIC LETTER DYEH MEDIAL FORM
  ___XXX__,________,
  __XXXXXX,________,
  _____XXX,X_______,
  _______X,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____,
  ________,________,
  _____XX_,________,
  _____XX_,________,
  ______XX,________,
  ______XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB76[ 26] = { // code FB76, ARABIC LETTER NYEH ISOLATED FORM
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X______,________,
  X_______,________,
  X______X,X_______,
  X____XXX,X_______,
  X____XX_,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB77[ 26] = { // code FB77, ARABIC LETTER NYEH FINAL FORM
  _XXXXXXX,X_______,
  XXXXXXXX,X_______,
  ____XXX_,________,
  __XX__X_,________,
  _X____XX,XX______,
  X______X,XX______,
  X___XX__,________,
  X_XXXX__,________,
  X_XX____,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,X_______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB78[ 20] = { // code FB78, ARABIC LETTER NYEH INITIAL FORM
  ___XXX__,________,
  __XXXXXX,________,
  _____XXX,X_______,
  _______X,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____,
  ________,________,
  ______XX,________,
  ____XXXX,________,
  ____XX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB79[ 20] = { // code FB79, ARABIC LETTER NYEH MEDIAL FORM
  ___XXX__,________,
  __XXXXXX,________,
  _____XXX,X_______,
  _______X,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____,
  ________,________,
  ______XX,________,
  ____XXXX,________,
  ____XX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB7A[ 26] = { // code FB7A, ARABIC LETTER TCHEH ISOLATED FORM
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X____XX,________,
  X___X_X_,________,
  X___XX_X,________,
  X_____XX,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB7B[ 26] = { // code FB7B, ARABIC LETTER TCHEH FINAL FORM
  _XXXXXXX,X_______,
  XXXXXXXX,X_______,
  ____XXX_,________,
  __XX__X_,________,
  _X____XX,XX______,
  X______X,XX______,
  X____XX_,________,
  X__X_X__,________,
  X__XX_X_,________,
  XX___XX_,________,
  _XXX____,________,
  _XXXXXXX,X_______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB7C[ 24] = { // code FB7C, ARABIC LETTER TCHEH INITIAL FORM
  ___XXX__,________,
  __XXXXXX,________,
  _____XXX,X_______,
  _______X,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____,
  ________,________,
  ________,________,
  _____XX_,________,
  ___X_X__,________,
  ___XX_X_,________,
  _____XX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB7D[ 24] = { // code FB7D, ARABIC LETTER TCHEH MEDIAL FORM
  ___XXX__,________,
  __XXXXXX,________,
  _____XXX,X_______,
  _______X,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____,
  ________,________,
  ________,________,
  _____XX_,________,
  ___X_X__,________,
  ___XX_X_,________,
  _____XX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB7E[ 26] = { // code FB7E, ARABIC LETTER TCHEHEH ISOLATED FORM
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X____XX,________,
  X___XX_X,________,
  X____XX_,________,
  X___X_XX,________,
  X___XX__,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB7F[ 26] = { // code FB7F, ARABIC LETTER TCHEHEH FINAL FORM
  _XXXXXXX,X_______,
  XXXXXXXX,X_______,
  ____XXX_,________,
  __XX__X_,________,
  _X____XX,XX______,
  X____XXX,XX______,
  X__XX_X_,________,
  X___XX__,________,
  X__X_XX_,________,
  XX_XX___,________,
  _XXX____,________,
  _XXXXXXX,X_______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB80[ 24] = { // code FB80, ARABIC LETTER TCHEHEH INITIAL FORM
  ___XXX__,________,
  __XXXXXX,________,
  _____XXX,X_______,
  _______X,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____,
  ________,________,
  ______XX,________,
  ____XX_X,________,
  _____XX_,________,
  ____X_XX,________,
  ____XX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB81[ 24] = { // code FB81, ARABIC LETTER TCHEHEH MEDIAL FORM
  ___XXX__,________,
  __XXXXXX,________,
  _____XXX,X_______,
  _______X,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____,
  ________,________,
  ______XX,________,
  ____XX_X,________,
  _____XX_,________,
  ____X_XX,________,
  ____XX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB82[ 13] = { // code FB82, ARABIC LETTER DDAHAL ISOLATED FORM
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  ___XX___,
  _XXXX___,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB83[ 13] = { // code FB83, ARABIC LETTER DDAHAL FINAL FORM
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  ___XX___,
  _XXXX___,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB84[ 13] = { // code FB84, ARABIC LETTER DAHAL ISOLATED FORM
  ___XX___,
  _XXXX___,
  _XX_____,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB85[ 13] = { // code FB85, ARABIC LETTER DAHAL FINAL FORM
  ___XX___,
  _XXXX___,
  _XX_____,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB86[ 14] = { // code FB86, ARABIC LETTER DUL ISOLATED FORM
  _XX_____,
  _X_XX___,
  __X_X___,
  _XX_____,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB87[ 14] = { // code FB87, ARABIC LETTER DUL FINAL FORM
  _XX_____,
  _X_XX___,
  __X_X___,
  _XX_____,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB88[ 16] = { // code FB88, ARABIC LETTER DDAL ISOLATED FORM
  _XX_____,
  _X______,
  __X_____,
  __X_____,
  __X_XX__,
  __XX_X__,
  XXXXXX__,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB89[ 16] = { // code FB89, ARABIC LETTER DDAL FINAL FORM
  _XX_____,
  _X______,
  __X_____,
  __X_____,
  __X_XX__,
  __XX_X__,
  XXXXXX__,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB8A[ 32] = { // code FB8A, ARABIC LETTER JEH ISOLATED FORM
  ____XX__,________,
  ____X_XX,________,
  _____X_X,________,
  ____XX__,________,
  ________,________,
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB8B[ 32] = { // code FB8B, ARABIC LETTER JEH FINAL FORM
  ____XX__,________,
  ____X_XX,________,
  _____X_X,________,
  ____XX__,________,
  ________,________,
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB8C[ 40] = { // code FB8C, ARABIC LETTER RREH ISOLATED FORM
  ____XX__,________,
  ____X___,________,
  _____X__,________,
  _____X__,________,
  _____X_X,X_______,
  _____XX_,X_______,
  ___XXXXX,X_______,
  ________,________,
  ________,________,
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB8D[ 40] = { // code FB8D, ARABIC LETTER RREH FINAL FORM
  ____XX__,________,
  ____X___,________,
  _____X__,________,
  _____X__,________,
  _____X_X,X_______,
  _____XX_,X_______,
  ___XXXXX,X_______,
  ________,________,
  ________,________,
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB8E[ 36] = { // code FB8E, ARABIC LETTER KEHEH ISOLATED FORM
  ________,_______X,________,
  ________,____XXXX,________,
  ________,___XXX__,________,
  ________,__XX____,________,
  ________,__X_____,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,______XX,________,
  XX______,_______X,X_______,
  XXXXXXXX,XXXXXXXX,X_______,
  _XXXXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB8F[ 36] = { // code FB8F, ARABIC LETTER KEHEH FINAL FORM
  ________,_______X,________,
  ________,____XXXX,________,
  ________,___XXX__,________,
  ________,__XX____,________,
  ________,__XX____,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,_____XXX,________,
  XX______,____XX_X,X_______,
  XXXXXXXX,XXXXX___,XXXX____,
  _XXXXXXX,XXXX____,_XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB90[ 24] = { // code FB90, ARABIC LETTER KEHEH INITIAL FORM
  _______X,________,
  ____XXXX,________,
  ___XXX__,________,
  __XX____,________,
  __X_____,________,
  __XXX___,________,
  ___XXX__,________,
  _____XX_,________,
  ______XX,________,
  _______X,X_______,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB91[ 24] = { // code FB91, ARABIC LETTER KEHEH MEDIAL FORM
  _______X,________,
  ____XXXX,________,
  ___XXX__,________,
  __XX____,________,
  __XX____,________,
  __XXX___,________,
  ___XXX__,________,
  _____XX_,________,
  _____XXX,________,
  ____XX_X,X_______,
  XXXXX___,XXXX____,
  XXXX____,_XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB92[ 45] = { // code FB92, ARABIC LETTER GAF ISOLATED FORM
  ________,_______X,________,
  ________,_____XXX,________,
  ________,____XXX_,________,
  ________,___X___X,________,
  ________,__X_XXXX,________,
  ________,___XXX__,________,
  ________,__XX____,________,
  ________,__X_____,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,______XX,________,
  XX______,_______X,X_______,
  XXXXXXXX,XXXXXXXX,X_______,
  _XXXXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB93[ 45] = { // code FB93, ARABIC LETTER GAF FINAL FORM
  ________,_______X,________,
  ________,_____XXX,________,
  ________,____XXX_,________,
  ________,___X___X,________,
  ________,__X_XXXX,________,
  ________,___XXX__,________,
  ________,__XX____,________,
  ________,__XX____,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,_____XXX,________,
  XX______,____XX_X,X_______,
  XXXXXXXX,XXXXX___,XXXX____,
  _XXXXXXX,XXXX____,_XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB94[ 30] = { // code FB94, ARABIC LETTER GAF INITIAL FORM
  _______X,________,
  _____XXX,________,
  ____XXX_,________,
  __XX___X,________,
  __X_XXXX,________,
  ___XXX__,________,
  __XX____,________,
  __X_____,________,
  __XXX___,________,
  ___XXX__,________,
  _____XX_,________,
  ______XX,________,
  _______X,X_______,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB95[ 30] = { // code FB95, ARABIC LETTER GAF MEDIAL FORM
  _______X,________,
  _____XXX,________,
  ____XXX_,________,
  __XX___X,________,
  __X_XXXX,________,
  ___XXX__,________,
  __XX____,________,
  __XX____,________,
  __XXX___,________,
  ___XXX__,________,
  _____XX_,________,
  _____XXX,________,
  ____XX_X,X_______,
  XXXXX___,XXXX____,
  XXXX____,_XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB96[ 60] = { // code FB96, ARABIC LETTER GUEH ISOLATED FORM
  ________,_______X,________,
  ________,_____XXX,________,
  ________,____XXX_,________,
  ________,___X___X,________,
  ________,__X_XXXX,________,
  ________,___XXX__,________,
  ________,__XX____,________,
  ________,__X_____,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,______XX,________,
  XX______,_______X,X_______,
  XXXXXXXX,XXXXXXXX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ________,________,________,
  _______X,X_______,________,
  _______X,X_______,________,
  ________,XX______,________,
  ________,XX______,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB97[ 60] = { // code FB97, ARABIC LETTER GUEH FINAL FORM
  ________,_______X,________,
  ________,_____XXX,________,
  ________,____XXX_,________,
  ________,___X___X,________,
  ________,__X_XXXX,________,
  ________,___XXX__,________,
  ________,__XX____,________,
  ________,__XX____,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,_____XXX,________,
  XX______,____XX_X,X_______,
  XXXXXXXX,XXXXX___,XXXX____,
  _XXXXXXX,XXXX____,_XXX____,
  ________,________,________,
  ______XX,________,________,
  ______XX,________,________,
  _______X,X_______,________,
  _______X,X_______,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB98[ 40] = { // code FB98, ARABIC LETTER GUEH INITIAL FORM
  _______X,________,
  _____XXX,________,
  ____XXX_,________,
  __XX___X,________,
  __X_XXXX,________,
  ___XXX__,________,
  __XX____,________,
  __X_____,________,
  __XXX___,________,
  ___XXX__,________,
  _____XX_,________,
  ______XX,________,
  _______X,X_______,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______,
  ________,________,
  ___XX___,________,
  ___XX___,________,
  ____XX__,________,
  ____XX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB99[ 40] = { // code FB99, ARABIC LETTER GUEH MEDIAL FORM
  _______X,________,
  _____XXX,________,
  ____XXX_,________,
  __XX___X,________,
  __X_XXXX,________,
  ___XXX__,________,
  __XX____,________,
  __XX____,________,
  __XXX___,________,
  ___XXX__,________,
  _____XX_,________,
  _____XXX,________,
  ____XX_X,X_______,
  XXXXX___,XXXX____,
  XXXX____,_XXX____,
  ________,________,
  __XX____,________,
  __XX____,________,
  ___XX___,________,
  ___XX___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB9A[ 48] = { // code FB9A, ARABIC LETTER NGOEH ISOLATED FORM
  ________,___XX___,________,
  ________,_XXXX__X,________,
  ________,_XX__XXX,________,
  ________,____XXX_,________,
  ________,___X___X,________,
  ________,__X_XXXX,________,
  ________,___XXX__,________,
  ________,__XX____,________,
  ________,__X_____,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,______XX,________,
  XX______,_______X,X_______,
  XXXXXXXX,XXXXXXXX,X_______,
  _XXXXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB9B[ 48] = { // code FB9B, ARABIC LETTER NGOEH FINAL FORM
  ________,___XX___,________,
  ________,_XXXX__X,________,
  ________,_XX__XXX,________,
  ________,____XXX_,________,
  ________,___X___X,________,
  ________,__X_XXXX,________,
  ________,___XXX__,________,
  ________,__XX____,________,
  ________,__XX____,________,
  ________,__XXX___,________,
  _X______,___XXX__,________,
  X_______,_____XX_,________,
  X_______,_____XXX,________,
  XX______,____XX_X,X_______,
  XXXXXXXX,XXXXX___,XXXX____,
  _XXXXXXX,XXXX____,_XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB9C[ 32] = { // code FB9C, ARABIC LETTER NGOEH INITIAL FORM
  ___XX___,________,
  _XXXX__X,________,
  _XX__XXX,________,
  ____XXX_,________,
  __XX___X,________,
  __X_XXXX,________,
  ___XXX__,________,
  __XX____,________,
  __X_____,________,
  __XXX___,________,
  ___XXX__,________,
  _____XX_,________,
  ______XX,________,
  _______X,X_______,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB9D[ 32] = { // code FB9D, ARABIC LETTER NGOEH MEDIAL FORM
  ___XX___,________,
  _XXXX__X,________,
  _XX__XXX,________,
  ____XXX_,________,
  __XX___X,________,
  __X_XXXX,________,
  ___XXX__,________,
  __XX____,________,
  __XX____,________,
  __XXX___,________,
  ___XXX__,________,
  _____XX_,________,
  _____XXX,________,
  ____XX_X,X_______,
  XXXXX___,XXXX____,
  XXXX____,_XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB9E[ 22] = { // code FB9E, ARABIC LETTER NOON GHUNNA ISOLATED FORM
  ________,X_______,
  ________,XX______,
  _X______,XX______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,XX______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FB9F[ 22] = { // code FB9F, ARABIC LETTER NOON GHUNNA FINAL FORM
  ________,X_______,
  ________,XX______,
  _X______,XX______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,XX______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBA0[ 38] = { // code FBA0, ARABIC LETTER RNOON ISOLATED FORM
  ___XX___,________,
  ___X____,________,
  ____X___,________,
  ____X___,________,
  ____X_XX,________,
  ____XX_X,________,
  __XXXXXX,________,
  ________,________,
  ________,X_______,
  ________,XX______,
  _X______,XX______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,XX______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBA1[ 38] = { // code FBA1, ARABIC LETTER RNOON FINAL FORM
  ___XX___,________,
  ___X____,________,
  ____X___,________,
  ____X___,________,
  ____X_XX,________,
  ____XX_X,________,
  __XXXXXX,________,
  ________,________,
  ________,X_______,
  ________,XX______,
  _X______,XX______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,XX______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBA2[ 15] = { // code FBA2, ARABIC LETTER RNOON INITIAL FORM
  __XX____,
  __X_____,
  ___X____,
  ___X____,
  ___X_XX_,
  ___XX_X_,
  _XXXXXX_,
  ________,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBA3[ 15] = { // code FBA3, ARABIC LETTER RNOON MEDIAL FORM
  __XX____,
  __X_____,
  ___X____,
  ___X____,
  ___X_XX_,
  ___XX_X_,
  _XXXXXX_,
  ________,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBA4[ 12] = { // code FBA4, ARABIC LETTER HEH WITH YEH ABOVE ISOLATED FORM
  __XX____,
  _X______,
  __XX____,
  _X______,
  ________,
  _X______,
  _XXX____,
  _XXXX___,
  X___X___,
  X___X___,
  XXXXX___,
  XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBA5[ 14] = { // code FBA5, ARABIC LETTER HEH WITH YEH ABOVE FINAL FORM
  ___XX___,
  __X_____,
  ___XX___,
  __X_____,
  ____X___,
  ____X___,
  ___XX___,
  __X_X___,
  _X__X___,
  XXXXX___,
  XXXX_X__,
  _____X__,
  _____XXX,
  ______XX};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBA6[  7] = { // code FBA6, ARABIC LETTER HEH GOAL ISOLATED FORM
  _X______,
  _XXX____,
  _XXXX___,
  X___X___,
  X___X___,
  XXXXX___,
  XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBA7[  6] = { // code FBA7, ARABIC LETTER HEH GOAL FINAL FORM
  ___XX___,
  __XXXX__,
  _XX__XXX,
  _X____XX,
  XX______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBA8[ 13] = { // code FBA8, ARABIC LETTER HEH GOAL INITIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  ________,
  ___X____,
  __X_____,
  __XX____,
  __XX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBA9[ 12] = { // code FBA9, ARABIC LETTER HEH GOAL MEDIAL FORM
  ____X___,
  ___X____,
  __XX____,
  XXXX__XX,
  XX_X_XXX,
  ___XXX__,
  ____X___,
  ________,
  ____X___,
  ___X____,
  ___XX___,
  ___XX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBAA[ 18] = { // code FBAA, ARABIC LETTER HEH DOACHASHMEE ISOLATED FORM
  ____X___,________,
  ____XX__,________,
  ____XXX_,________,
  ___XXXX_,________,
  __X__XXX,________,
  __X__X_X,X_______,
  ___XX___,X_______,
  XXXXXXXX,X_______,
  XXX___XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBAB[ 10] = { // code FBAB, ARABIC LETTER HEH DOACHASHMEE FINAL FORM
  ____X___,
  ____X___,
  ___XX___,
  __X_X___,
  _X__X___,
  XXXXX___,
  XXXX_X__,
  _____X__,
  _____XXX,
  ______XX};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBAC[ 18] = { // code FBAC, ARABIC LETTER HEH DOACHASHMEE INITIAL FORM
  ____X___,________,
  ____XX__,________,
  ____XXX_,________,
  ___XXXX_,________,
  __X__XXX,________,
  __X__X_X,X_______,
  ___XX___,X_______,
  XXXXXXXX,X_______,
  XXX___XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBAD[ 24] = { // code FBAD, ARABIC LETTER HEH DOACHASHMEE MEDIAL FORM
  _____XX_,________,
  ____XXX_,________,
  ___XX_X_,________,
  ___X__X_,________,
  __X_XX__,________,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______,
  __X_XX__,________,
  __X___X_,________,
  __XX__X_,________,
  ___XXXX_,________,
  ____XXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBAE[ 18] = { // code FBAE, ARABIC LETTER YEH BARREE ISOLATED FORM
  ______XX,________,
  _____XXX,X_______,
  ____XX__,X_______,
  ___XX___,________,
  __XX____,________,
  _XX_____,________,
  X_______,________,
  XXXXXXXX,XXXXXXX_,
  XXXXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBAF[ 18] = { // code FBAF, ARABIC LETTER YEH BARREE FINAL FORM
  ________,_XXXXXXX,
  ______XX,XXXXXXXX,
  ____XXXX,X_______,
  __XXX___,________,
  _XX_____,________,
  _X______,________,
  X_______,________,
  XXXXXXXX,XXXXXXX_,
  XXXXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBB0[ 24] = { // code FBB0, ARABIC LETTER YEH BARREE WITH HAMZA ABOVE ISOLATED FORM
  ___XX___,________,
  __X_____,________,
  ___XX___,________,
  __X___XX,________,
  _____XXX,X_______,
  ____XX__,X_______,
  ___XX___,________,
  __XX____,________,
  _XX_____,________,
  X_______,________,
  XXXXXXXX,XXXXXXXX,
  XXXXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBB1[ 28] = { // code FBB1, ARABIC LETTER YEH BARREE WITH HAMZA ABOVE FINAL FORM
  ________,__XX____,
  ________,_X______,
  ________,__XX____,
  ________,_X______,
  ________,________,
  ________,_XXXXXXX,
  ______XX,XXXXXXXX,
  ____XXXX,X_______,
  __XXX___,________,
  _XX_____,________,
  _X______,________,
  X_______,________,
  XXXXXXXX,XXXXXXXX,
  XXXXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBD3[ 30] = { // code FBD3, ARABIC LETTER NG ISOLATED FORM
  ____XX__,________,
  ____X_XX,________,
  _____X_X,__XX____,
  ____XX__,__XXX___,
  ________,___XX___,
  _______X,___X____,
  _____XX_,___X____,
  _____XXX,X__X____,
  ________,X__X____,
  _X_____X,X___X___,
  X__XXXXX,____X___,
  X_______,____X___,
  XX______,____X___,
  XXXXXXXX,XXXXX___,
  _XXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBD4[ 30] = { // code FBD4, ARABIC LETTER NG FINAL FORM
  ____XX__,________,
  ____X_XX,________,
  _____X_X,__XX____,
  ____XX__,__XXX___,
  ________,___XX___,
  _______X,___X____,
  _____XX_,___X____,
  _____XXX,X__X____,
  ________,X__X____,
  _X_____X,X___X___,
  X__XXXXX,____X___,
  X_______,____X___,
  XX______,____X___,
  XXXXXXXX,XXXXX___,
  _XXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBD5[ 28] = { // code FBD5, ARABIC LETTER NG INITIAL FORM
  __XX____,________,
  ____XX__,________,
  __XX___X,________,
  ____XXXX,________,
  ___XXX__,________,
  __XX____,________,
  __X_____,________,
  __XXX___,________,
  ___XXX__,________,
  _____XX_,________,
  ______XX,________,
  _______X,X_______,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBD6[ 28] = { // code FBD6, ARABIC LETTER NG MEDIAL FORM
  __XX____,________,
  ____XX__,________,
  __XX___X,________,
  ____XXXX,________,
  ___XXX__,________,
  __XX____,________,
  __X_____,________,
  __XXX___,________,
  ___XXX__,________,
  _____XX_,________,
  ______XX,________,
  _______X,X_______,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBD7[ 17] = { // code FBD7, ARABIC LETTER U ISOLATED FORM
  ______XX,
  _____X_X,
  _____XXX,
  ______XX,
  ____XX__,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBD8[ 17] = { // code FBD8, ARABIC LETTER U FINAL FORM
  ______XX,
  _____X_X,
  _____XXX,
  ______XX,
  ____XX__,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBD9[ 14] = { // code FBD9, ARABIC LETTER OE ISOLATED FORM
  ____X_X_,
  _____X__,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBDA[ 14] = { // code FBDA, ARABIC LETTER OE FINAL FORM
  ____X_X_,
  _____X__,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBDB[ 18] = { // code FBDB, ARABIC LETTER YU ISOLATED FORM
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBDC[ 18] = { // code FBDC, ARABIC LETTER YU FINAL FORM
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBDD[ 32] = { // code FBDD, ARABIC LETTER U WITH HAMZA ABOVE ISOLATED FORM
  ___XX__X,X_______,
  __X_X_X_,________,
  __XXX__X,X_______,
  ___XX_X_,________,
  _XX_____,________,
  _____XX_,________,
  ____XXXX,________,
  ____X__X,________,
  ____X__X,________,
  ____XXXX,________,
  _____XXX,________,
  _______X,________,
  ______XX,________,
  _____XX_,________,
  X___XX__,________,
  _XXXX___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBDE[ 16] = { // code FBDE, ARABIC LETTER VE ISOLATED FORM
  ___XX___,
  ___X_XX_,
  ____X_X_,
  ___XX___,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBDF[ 16] = { // code FBDF, ARABIC LETTER VE FINAL FORM
  ___XX___,
  ___X_XX_,
  ____X_X_,
  ___XX___,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBE0[ 11] = { // code FBE0, ARABIC LETTER KIRGHIZ OE ISOLATED FORM
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  __XX___X,
  ____XXXX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBE1[ 11] = { // code FBE1, ARABIC LETTER KIRGHIZ OE FINAL FORM
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  __XX___X,
  ____XXXX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBE2[ 14] = { // code FBE2, ARABIC LETTER KIRGHIZ YU ISOLATED FORM
  _____X__,
  ____X_X_,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBE3[ 14] = { // code FBE3, ARABIC LETTER KIRGHIZ YU FINAL FORM
  _____X__,
  ____X_X_,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBE4[ 28] = { // code FBE4, ARABIC LETTER E ISOLATED FORM
  ________,_XXX____,
  ________,XXXX____,
  _______X,X__X____,
  _X_____X,________,
  X_____X_,________,
  X_____XX,XXX_____,
  X_____XX,XXX_____,
  X_______,__X_____,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  _XXXXXX_,________,
  ________,________,
  ____X___,________,
  ____X___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBE5[ 20] = { // code FBE5, ARABIC LETTER E FINAL FORM
  _X______,________,
  _X______,XXXX____,
  X______X,XXXX____,
  X_____X_,________,
  X_____XX,XXX_____,
  XXX_____,__X_____,
  _XXXXXXX,XX______,
  __XXXXXX,X_______,
  _____X__,________,
  _____X__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBE6[ 12] = { // code FBE6, ARABIC LETTER E INITIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  __XX____,
  __XX____,
  ___XX___,
  ___XX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBE7[ 12] = { // code FBE7, ARABIC LETTER E MEDIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  __XX____,
  __XX____,
  ___XX___,
  ___XX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBFC[ 22] = { // code FBFC, ARABIC LETTER FARSI YEH ISOLATED FORM
  ________,_XXX____,
  ________,XXXX____,
  _______X,X__X____,
  _X_____X,________,
  X_____X_,________,
  X_____XX,XXX_____,
  X_____XX,XXX_____,
  X_______,__X_____,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  _XXXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBFD[ 16] = { // code FBFD, ARABIC LETTER FARSI YEH FINAL FORM
  _X______,________,
  _X______,XXXX____,
  X______X,XXXX____,
  X_____X_,________,
  X_____XX,XXX_____,
  XXX_____,__X_____,
  _XXXXXXX,XX______,
  __XXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBFE[ 11] = { // code FBFE, ARABIC LETTER FARSI YEH INITIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  ___XX___,
  _XXXX___,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FBFF[ 11] = { // code FBFF, ARABIC LETTER FARSI YEH MEDIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  ___XX___,
  _XXXX___,
  _XX_____};

//
// Start of unicode area <Arabic Presentation Forms-A>
//
GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FC5E[  6] = { // code FC5E, ARABIC LIGATURE SHADDA WITH DAMMATAN ISOLATED FORM
  ____XX__,
  ___X_X__,
  XX_XXX__,
  _X_X_X__,
  _XX_____,
  __X_X___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FC5F[  6] = { // code FC5F, ARABIC LIGATURE SHADDA WITH KASRATAN ISOLATED FORM
  __X_X___,
  X_XXX___,
  XX______,
  ___XX___,
  _XX_____,
  ___XX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FC60[  6] = { // code FC60, ARABIC LIGATURE SHADDA WITH FATHA ISOLATED FORM
  ___XX___,
  _XX_____,
  ________,
  __X_X___,
  X_XXX___,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FC61[  6] = { // code FC61, ARABIC LIGATURE SHADDA WITH DAMMA ISOLATED FORM
  ___XX___,
  __X_X___,
  __XXX___,
  _XX_____,
  ___X_X__,
  _X_XXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FC62[  5] = { // code FC62, ARABIC LIGATURE SHADDA WITH KASRA ISOLATED FORM
  __X_X___,
  X_XXX___,
  XX______,
  ___XX___,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FD3E[ 20] = { // code FD3E, ORNATE LEFT PARENTHESIS
  ___X____,
  __XX____,
  __X_____,
  _XX_____,
  _XX_____,
  _X______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  _X______,
  _XX_____,
  _XX_____,
  __X_____,
  __XX____,
  ___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FD3F[ 20] = { // code FD3F, ORNATE RIGHT PARENTHESIS
  X_______,
  XX______,
  _X______,
  _XX_____,
  _XX_____,
  __X_____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __X_____,
  _XX_____,
  _XX_____,
  _X______,
  XX______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FDF2[ 26] = { // code FDF2, ARABIC LIGATURE ALLAH ISOLATED FORM
  _____X__,________,
  ______X_,________,
  _______X,_X______,
  _____X_X,XX______,
  _____XX_,________,
  ________,X__X____,
  _____X__,X__X____,
  _____X__,X__X____,
  ____XX__,XX_X____,
  __XX_X__,_X__X___,
  _XX__X__,_X__X___,
  XXXXX_XX,XXXXX___,
  XXXX__XX,X__XX___};

//
// Start of unicode area <Arabic Presentation Forms-B>
//
GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE80[  8] = { // code FE80, ARABIC LETTER HAMZA ISOLATED FORM
  __XX____,
  _XXXX___,
  X_______,
  XX__XX__,
  XXXXXX__,
  _XXXX___,
  _XX_____,
  ________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE81[ 14] = { // code FE81, ARABIC LETTER ALEF WITH MADDA ABOVE ISOLATED FORM
  XXXX____,
  ________,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE82[ 14] = { // code FE82, ARABIC LETTER ALEF WITH MADDA ABOVE FINAL FORM
  XXXX____,
  ________,
  __X_____,
  _XX_____,
  _XX_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __XX____,
  __XXXX__,
  ___XXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE83[ 15] = { // code FE83, ARABIC LETTER ALEF WITH HAMZA ABOVE ISOLATED FORM
  _XX_____,
  X_______,
  _XX_____,
  X_______,
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE84[ 15] = { // code FE84, ARABIC LETTER ALEF WITH HAMZA ABOVE FINAL FORM
  _XX_____,
  X_______,
  _XX_____,
  X_______,
  ________,
  _X______,
  XX______,
  XX______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _XXXX___,
  __XXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE85[ 17] = { // code FE85, ARABIC LETTER WAW WITH HAMZA ABOVE ISOLATED FORM
  ___XX___,
  __X_____,
  ___XX___,
  __X_____,
  ________,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE86[ 17] = { // code FE86, ARABIC LETTER WAW WITH HAMZA ABOVE FINAL FORM
  ___XX___,
  __X_____,
  ___XX___,
  __X_____,
  ________,
  ________,
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE87[ 17] = { // code FE87, ARABIC LETTER ALEF WITH HAMZA BELOW ISOLATED FORM
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  ________,
  _XX_____,
  X_______,
  _XX_____,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE88[ 17] = { // code FE88, ARABIC LETTER ALEF WITH HAMZA BELOW FINAL FORM
  _X______,
  XX______,
  XX______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _XX_____,
  _XXXX___,
  __XXX___,
  ________,
  _XX_____,
  X_______,
  _XX_____,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE89[ 26] = { // code FE89, ARABIC LETTER YEH WITH HAMZA ABOVE ISOLATED FORM
  _XX_____,________,
  X_______,________,
  _XX_____,_XXX____,
  X_______,XXXX____,
  _______X,X__X____,
  _X_____X,________,
  X_____X_,________,
  X_____XX,XXX_____,
  X_____XX,XXX_____,
  X_______,__X_____,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  _XXXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE8A[ 28] = { // code FE8A, ARABIC LETTER YEH WITH HAMZA ABOVE FINAL FORM
  _XX_____,________,
  X_______,________,
  _XX_____,________,
  X_______,________,
  ________,________,
  ________,________,
  _X______,________,
  _X______,XXXX____,
  X______X,XXXX____,
  X_____X_,________,
  X_____XX,XXX_____,
  XXX_____,__X_____,
  _XXXXXXX,XX______,
  __XXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE8B[ 12] = { // code FE8B, ARABIC LETTER YEH WITH HAMZA ABOVE INITIAL FORM
  ___XX___,
  __X_____,
  ___XX___,
  __X_____,
  ________,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE8C[ 12] = { // code FE8C, ARABIC LETTER YEH WITH HAMZA ABOVE MEDIAL FORM
  ___XX___,
  __X_____,
  ___XX___,
  __X_____,
  ________,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE8D[ 12] = { // code FE8D, ARABIC LETTER ALEF ISOLATED FORM
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE8E[ 12] = { // code FE8E, ARABIC LETTER ALEF FINAL FORM
  _X______,
  XX______,
  XX______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _XX_____,
  _XXXX___,
  __XXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE8F[ 22] = { // code FE8F, ARABIC LETTER BEH ISOLATED FORM
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__,
  ________,________,
  ________,________,
  ______XX,________,
  ______XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE90[ 22] = { // code FE90, ARABIC LETTER BEH FINAL FORM
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__,
  ________,________,
  ________,________,
  ______XX,________,
  ______XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE91[ 11] = { // code FE91, ARABIC LETTER BEH INITIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  ________,
  __XX____,
  __XX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE92[ 11] = { // code FE92, ARABIC LETTER BEH MEDIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  ________,
  __XX____,
  __XX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE93[ 11] = { // code FE93, ARABIC LETTER TEH MARBUTA ISOLATED FORM
  __XX____,
  XXXX____,
  XX______,
  ________,
  _X______,
  _XXX____,
  _XXXX___,
  X___X___,
  X___X___,
  XXXXX___,
  XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE94[ 14] = { // code FE94, ARABIC LETTER TEH MARBUTA FINAL FORM
  ___XX___,
  _XXXX___,
  _XX_____,
  ________,
  ____X___,
  ____X___,
  ___XX___,
  __X_X___,
  _X__X___,
  XXXXX___,
  XXXX_X__,
  _____X__,
  _____XXX,
  ______XX};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE95[ 20] = { // code FE95, ARABIC LETTER TEH ISOLATED FORM
  _______X,X_______,
  _____XXX,X_______,
  _____XX_,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE96[ 20] = { // code FE96, ARABIC LETTER TEH FINAL FORM
  _______X,X_______,
  _____XXX,X_______,
  _____XX_,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE97[ 11] = { // code FE97, ARABIC LETTER TEH INITIAL FORM
  ___XX___,
  _XXXX___,
  _XX_____,
  ________,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE98[ 11] = { // code FE98, ARABIC LETTER TEH MEDIAL FORM
  ___XX___,
  _XXXX___,
  _XX_____,
  ________,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE99[ 22] = { // code FE99, ARABIC LETTER THEH ISOLATED FORM
  _____XX_,________,
  _____X_X,X_______,
  ______X_,X_______,
  _____XX_,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE9A[ 22] = { // code FE9A, ARABIC LETTER THEH FINAL FORM
  _____XX_,________,
  _____X_X,X_______,
  ______X_,X_______,
  _____XX_,________,
  _X______,____X___,
  X_______,____XX__,
  X_______,____XX__,
  X_______,_____X__,
  XX______,_____X__,
  _XXXXXXX,XXXXXX__,
  __XXXXXX,XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE9B[ 12] = { // code FE9B, ARABIC LETTER THEH INITIAL FORM
  _XX_____,
  _X_XX___,
  __X_X___,
  _XX_____,
  ________,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE9C[ 12] = { // code FE9C, ARABIC LETTER THEH MEDIAL FORM
  _XX_____,
  _X_XX___,
  __X_X___,
  _XX_____,
  ________,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE9D[ 26] = { // code FE9D, ARABIC LETTER JEEM ISOLATED FORM
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X______,________,
  X_____XX,________,
  X_____XX,________,
  X_______,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE9E[ 26] = { // code FE9E, ARABIC LETTER JEEM FINAL FORM
  _XXXXXXX,X_______,
  XXXXXXXX,X_______,
  ____XXX_,________,
  __XX__X_,________,
  _X____XX,XX______,
  X______X,XX______,
  X___XX__,________,
  X___XX__,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,X_______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FE9F[ 18] = { // code FE9F, ARABIC LETTER JEEM INITIAL FORM
  ___XXX__,________,
  __XXXXXX,________,
  _____XXX,X_______,
  _______X,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____,
  ________,________,
  ____XX__,________,
  ____XX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEA0[ 18] = { // code FEA0, ARABIC LETTER JEEM MEDIAL FORM
  ___XXX__,________,
  __XXXXXX,________,
  _____XXX,X_______,
  _______X,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____,
  ________,________,
  ____XX__,________,
  ____XX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEA1[ 26] = { // code FEA1, ARABIC LETTER HAH ISOLATED FORM
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEA2[ 26] = { // code FEA2, ARABIC LETTER HAH FINAL FORM
  _XXXXXXX,X_______,
  XXXXXXXX,X_______,
  ____XXX_,________,
  __XX__X_,________,
  _X____XX,XX______,
  X______X,XX______,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,X_______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEA3[ 12] = { // code FEA3, ARABIC LETTER HAH INITIAL FORM
  ___XXX__,________,
  __XXXXXX,________,
  _____XXX,X_______,
  _______X,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEA4[ 12] = { // code FEA4, ARABIC LETTER HAH MEDIAL FORM
  ___XXX__,________,
  __XXXXXX,________,
  _____XXX,X_______,
  _______X,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEA5[ 34] = { // code FEA5, ARABIC LETTER KHAH ISOLATED FORM
  _____XX_,________,
  _____XX_,________,
  ________,________,
  ________,________,
  _XXXXXXX,XX______,
  XXXXXXXX,XX______,
  ____XXX_,________,
  __XX____,________,
  _X______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEA6[ 34] = { // code FEA6, ARABIC LETTER KHAH FINAL FORM
  ____XX__,________,
  ____XX__,________,
  ________,________,
  ________,________,
  _XXXXXXX,X_______,
  XXXXXXXX,X_______,
  ____XXX_,________,
  __XX__X_,________,
  _X____XX,XX______,
  X______X,XX______,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  _XXX____,________,
  _XXXXXXX,X_______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEA7[ 20] = { // code FEA7, ARABIC LETTER KHAH INITIAL FORM
  ____XX__,________,
  ____XX__,________,
  ________,________,
  ________,________,
  ___XXX__,________,
  __XXXXXX,________,
  _____XXX,X_______,
  _______X,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEA8[ 20] = { // code FEA8, ARABIC LETTER KHAH MEDIAL FORM
  ____XX__,________,
  ____XX__,________,
  ________,________,
  ________,________,
  ___XXX__,________,
  __XXXXXX,________,
  _____XXX,X_______,
  _______X,XX______,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEA9[  9] = { // code FEA9, ARABIC LETTER DAL ISOLATED FORM
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEAA[  9] = { // code FEAA, ARABIC LETTER DAL FINAL FORM
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEAB[ 13] = { // code FEAB, ARABIC LETTER THAL ISOLATED FORM
  _XX_____,
  _XX_____,
  ________,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEAC[ 13] = { // code FEAC, ARABIC LETTER THAL FINAL FORM
  _XX_____,
  _XX_____,
  ________,
  ________,
  ___X____,
  ___XX___,
  ____X___,
  ____XX__,
  _____X__,
  _____X__,
  X____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEAD[ 22] = { // code FEAD, ARABIC LETTER REH ISOLATED FORM
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEAE[ 22] = { // code FEAE, ARABIC LETTER REH FINAL FORM
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEAF[ 30] = { // code FEAF, ARABIC LETTER ZAIN ISOLATED FORM
  _____XX_,________,
  _____XX_,________,
  ________,________,
  ________,________,
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEB0[ 30] = { // code FEB0, ARABIC LETTER ZAIN FINAL FORM
  _____XX_,________,
  _____XX_,________,
  ________,________,
  ________,________,
  ______X_,________,
  ______XX,________,
  _______X,X_______,
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _______X,X_______,
  ______XX,________,
  X____XX_,________,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEB1[ 22] = { // code FEB1, ARABIC LETTER SEEN ISOLATED FORM
  ________,X_____X_,
  ________,XX__X_XX,
  _X______,XX__X__X,
  _X______,_X__X__X,
  X_______,_XXXXXXX,
  X_______,_XXX_XXX,
  X_______,_X______,
  X_______,XX______,
  XX_____X,X_______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEB2[ 22] = { // code FEB2, ARABIC LETTER SEEN FINAL FORM
  ________,X_____X_,
  ________,XX__X_XX,
  _X______,XX__X__X,
  _X______,_X__X__X,
  X_______,_XXXXXXX,
  X_______,_XXX_XXX,
  X_______,_X______,
  X_______,XX______,
  XX_____X,X_______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEB3[ 12] = { // code FEB3, ARABIC LETTER SEEN INITIAL FORM
  ________,__X_____,
  ___X____,X_XX____,
  ___X____,X__X____,
  ___XX___,X__X____,
  XXXXXXXX,XXXX____,
  XXX_XXXX,_XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEB4[ 12] = { // code FEB4, ARABIC LETTER SEEN MEDIAL FORM
  ________,__X_____,
  ___X____,X_XX____,
  ___X____,X__X____,
  ___XX___,X__X____,
  XXXXXXXX,XXXX____,
  XXX_XXXX,_XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEB5[ 32] = { // code FEB5, ARABIC LETTER SHEEN ISOLATED FORM
  ________,___XX___,
  ________,___X_XX_,
  ________,____X_X_,
  ________,___XX___,
  ________,________,
  ________,X_____X_,
  ________,XX__X_XX,
  _X______,XX__X__X,
  _X______,_X__X__X,
  X_______,_XXXXXXX,
  X_______,_XXX_XXX,
  X_______,_X______,
  X_______,XX______,
  XX_____X,X_______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEB6[ 32] = { // code FEB6, ARABIC LETTER SHEEN FINAL FORM
  ________,___XX___,
  ________,___X_XX_,
  ________,____X_X_,
  ________,___XX___,
  ________,________,
  ________,X_____X_,
  ________,XX__X_XX,
  _X______,XX__X__X,
  _X______,_X__X__X,
  X_______,_XXXXXXX,
  X_______,_XXX_XXX,
  X_______,_X______,
  X_______,XX______,
  XX_____X,X_______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEB7[ 22] = { // code FEB7, ARABIC LETTER SHEEN INITIAL FORM
  ______XX,________,
  ______X_,XX______,
  _______X,_X______,
  ______XX,________,
  ________,________,
  ________,__X_____,
  ___X____,X_XX____,
  ___X____,X__X____,
  ___XX___,X__X____,
  XXXXXXXX,XXXX____,
  XXX_XXXX,_XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEB8[ 22] = { // code FEB8, ARABIC LETTER SHEEN MEDIAL FORM
  ______XX,________,
  ______X_,XX______,
  _______X,_X______,
  ______XX,________,
  ________,________,
  ________,__X_____,
  ___X____,X_XX____,
  ___X____,X__X____,
  ___XX___,X__X____,
  XXXXXXXX,XXXX____,
  XXX_XXXX,_XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEB9[ 33] = { // code FEB9, ARABIC LETTER SAD ISOLATED FORM
  ________,X_______,_XXXX___,
  ________,XX______,XXXXXX__,
  _X______,XX____XX,____XX__,
  _X______,_X___X__,____XX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_X______,________,
  X_______,XX______,________,
  XX_____X,X_______,________,
  XXXXXXXX,X_______,________,
  __XXXXX_,________,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEBA[ 33] = { // code FEBA, ARABIC LETTER SAD FINAL FORM
  ________,X_______,_XXXX___,
  ________,XX______,XXXXXX__,
  _X______,XX____XX,____XX__,
  _X______,_X___X__,____XX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_X______,________,
  X_______,XX______,________,
  XX_____X,X_______,________,
  XXXXXXXX,X_______,________,
  __XXXXX_,________,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEBB[ 18] = { // code FEBB, ARABIC LETTER SAD INITIAL FORM
  ________,______XX,XX______,
  ____X___,____XXXX,XXX_____,
  ____X___,___XX___,_XX_____,
  ____XX__,_XX_____,_XX_____,
  XXXXXXXX,XXXXXXXX,XXX_____,
  XXXX_XXX,XXXXXXXX,XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEBC[ 18] = { // code FEBC, ARABIC LETTER SAD MEDIAL FORM
  ________,______XX,XX______,
  ____X___,____XXXX,XXX_____,
  ____X___,___XX___,_XX_____,
  ____XX__,_XX_____,_XX_____,
  XXXXXXXX,XXXXXXXX,XXX_____,
  XXXX_XXX,XXXXXXXX,XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEBD[ 42] = { // code FEBD, ARABIC LETTER DAD ISOLATED FORM
  ________,_____XX_,________,
  ________,_____XX_,________,
  ________,________,________,
  ________,X_______,_XXXX___,
  ________,XX______,XXXXXX__,
  _X______,XX____XX,____XX__,
  _X______,_X___X__,____XX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_X______,________,
  X_______,XX______,________,
  XX_____X,X_______,________,
  XXXXXXXX,X_______,________,
  __XXXXX_,________,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEBE[ 42] = { // code FEBE, ARABIC LETTER DAD FINAL FORM
  ________,_____XX_,________,
  ________,_____XX_,________,
  ________,________,________,
  ________,X_______,_XXXX___,
  ________,XX______,XXXXXX__,
  _X______,XX____XX,____XX__,
  _X______,_X___X__,____XX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_XXXXXXX,XXXXXX__,
  X_______,_X______,________,
  X_______,XX______,________,
  XX_____X,X_______,________,
  XXXXXXXX,X_______,________,
  __XXXXX_,________,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEBF[ 30] = { // code FEBF, ARABIC LETTER DAD INITIAL FORM
  ________,__XX____,________,
  ________,__XX____,________,
  ________,________,________,
  ________,________,________,
  ________,______XX,XX______,
  ____X___,____XXXX,XXX_____,
  ____X___,___XX___,_XX_____,
  ____XX__,_XX_____,_XX_____,
  XXXXXXXX,XXXXXXXX,XXX_____,
  XXXX_XXX,XXXXXXXX,XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEC0[ 30] = { // code FEC0, ARABIC LETTER DAD MEDIAL FORM
  ________,__XX____,________,
  ________,__XX____,________,
  ________,________,________,
  ________,________,________,
  ________,______XX,XX______,
  ____X___,____XXXX,XXX_____,
  ____X___,___XX___,_XX_____,
  ____XX__,_XX_____,_XX_____,
  XXXXXXXX,XXXXXXXX,XXX_____,
  XXXX_XXX,XXXXXXXX,XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEC1[ 26] = { // code FEC1, ARABIC LETTER TAH ISOLATED FORM
  ___X____,________,
  ___XXX__,________,
  ____XX__,________,
  ____X___,________,
  ____XX__,________,
  _____X__,________,
  _____X__,________,
  _____X__,XXXX____,
  _____X_X,XXXXX___,
  _____XX_,___XX___,
  ____X___,___XX___,
  XXXXXXXX,XXXXX___,
  XXXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEC2[ 26] = { // code FEC2, ARABIC LETTER TAH FINAL FORM
  ___X____,________,
  ___XXX__,________,
  ____XX__,________,
  ____X___,________,
  ____XX__,________,
  _____X__,________,
  _____X__,________,
  _____X__,XXXX____,
  _____X_X,XXXXX___,
  _____XX_,___XX___,
  ____X___,___XX___,
  XXXXXXXX,XXXXX___,
  XXXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEC3[ 26] = { // code FEC3, ARABIC LETTER TAH INITIAL FORM
  ___X____,________,
  ___XXX__,________,
  ____XX__,________,
  ____X___,________,
  ____XX__,________,
  _____X__,________,
  _____X__,________,
  _____X__,XXXX____,
  _____X_X,XXXXX___,
  _____XX_,___XX___,
  ____X___,___XX___,
  XXXXXXXX,XXXXX___,
  XXXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEC4[ 26] = { // code FEC4, ARABIC LETTER TAH MEDIAL FORM
  ___X____,________,
  ___XXX__,________,
  ____XX__,________,
  ____X___,________,
  ____XX__,________,
  _____X__,________,
  _____X__,________,
  _____X__,XXXX____,
  _____X_X,XXXXX___,
  _____XX_,___XX___,
  ____X___,___XX___,
  XXXXXXXX,XXXXX___,
  XXXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEC5[ 26] = { // code FEC5, ARABIC LETTER ZAH ISOLATED FORM
  ___X____,________,
  ___XXX__,________,
  ____XX__,XX______,
  ____X___,XX______,
  ____XX__,________,
  _____X__,________,
  _____X__,________,
  _____X__,XXXX____,
  _____X_X,XXXXX___,
  _____XX_,___XX___,
  ____X___,___XX___,
  XXXXXXXX,XXXXX___,
  XXXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEC6[ 26] = { // code FEC6, ARABIC LETTER ZAH FINAL FORM
  ___X____,________,
  ___XXX__,________,
  ____XX__,XX______,
  ____X___,XX______,
  ____XX__,________,
  _____X__,________,
  _____X__,________,
  _____X__,XXXX____,
  _____X_X,XXXXX___,
  _____XX_,___XX___,
  ____X___,___XX___,
  XXXXXXXX,XXXXX___,
  XXXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEC7[ 26] = { // code FEC7, ARABIC LETTER ZAH INITIAL FORM
  ___X____,________,
  ___XXX__,________,
  ____XX__,XX______,
  ____X___,XX______,
  ____XX__,________,
  _____X__,________,
  _____X__,________,
  _____X__,XXXX____,
  _____X_X,XXXXX___,
  _____XX_,___XX___,
  ____X___,___XX___,
  XXXXXXXX,XXXXX___,
  XXXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEC8[ 26] = { // code FEC8, ARABIC LETTER ZAH MEDIAL FORM
  ___X____,________,
  ___XXX__,________,
  ____XX__,XX______,
  ____X___,XX______,
  ____XX__,________,
  _____X__,________,
  _____X__,________,
  _____X__,XXXX____,
  _____X_X,XXXXX___,
  _____XX_,___XX___,
  ____X___,___XX___,
  XXXXXXXX,XXXXX___,
  XXXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEC9[ 34] = { // code FEC9, ARABIC LETTER AIN ISOLATED FORM
  __XXX___,________,
  _XXXXXX_,________,
  XXX_____,________,
  X_______,________,
  X_______,X_______,
  XXX__XXX,X_______,
  _XXXXXX_,________,
  __XXX___,________,
  __X_____,________,
  _X______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  XXXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FECA[ 26] = { // code FECA, ARABIC LETTER AIN FINAL FORM
  ___XXX__,________,
  __XXXXX_,________,
  ____XX__,________,
  ___XXXX_,________,
  __X__XXX,________,
  _X____XX,________,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  XXXX____,________,
  _XXXXXXX,X_______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FECB[ 14] = { // code FECB, ARABIC LETTER AIN INITIAL FORM
  ___XXXXX,________,
  __XXXXXX,X_______,
  __X_____,________,
  __X_____,__X_____,
  __XX___X,XX______,
  XXXXXXXX,X_______,
  XXXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FECC[ 12] = { // code FECC, ARABIC LETTER AIN MEDIAL FORM
  ___XXX__,________,
  __XXXXX_,________,
  __XXXXX_,________,
  ____XX__,________,
  XXXXXXXX,X_______,
  XXX___XX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FECD[ 42] = { // code FECD, ARABIC LETTER GHAIN ISOLATED FORM
  ___XX___,________,
  ___XX___,________,
  ________,________,
  ________,________,
  __XXX___,________,
  _XXXXXX_,________,
  XXX_____,________,
  X_______,________,
  X_______,X_______,
  XXX__XXX,X_______,
  _XXXXXX_,________,
  __XXX___,________,
  __X_____,________,
  _X______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  XXXX____,________,
  _XXXXXXX,XX______,
  ___XXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FECE[ 34] = { // code FECE, ARABIC LETTER GHAIN FINAL FORM
  ____XX__,________,
  ____XX__,________,
  ________,________,
  ________,________,
  ___XXX__,________,
  __XXXXX_,________,
  ____XX__,________,
  ___XXXX_,________,
  __X__XXX,________,
  _X____XX,________,
  X_______,________,
  X_______,________,
  X_______,________,
  XX______,________,
  XXXX____,________,
  _XXXXXXX,X_______,
  ___XXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FECF[ 20] = { // code FECF, ARABIC LETTER GHAIN INITIAL FORM
  ____XX__,________,
  ____XX__,________,
  ________,________,
  ___XXXXX,________,
  __XXXXXX,X_______,
  __X_____,________,
  __X_____,__X_____,
  __XX___X,XX______,
  XXXXXXXX,X_______,
  XXXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FED0[ 20] = { // code FED0, ARABIC LETTER GHAIN MEDIAL FORM
  ___XX___,________,
  ___XX___,________,
  ________,________,
  ________,________,
  ___XXX__,________,
  __XXXXX_,________,
  __XXXXX_,________,
  ____XX__,________,
  XXXXXXXX,X_______,
  XXX___XX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FED1[ 33] = { // code FED1, ARABIC LETTER FEH ISOLATED FORM
  ________,_____XX_,________,
  ________,_____XX_,________,
  ________,________,________,
  ________,________,________,
  _X______,______XX,________,
  X_______,_____XXX,X_______,
  X_______,_____X__,X_______,
  X_______,_____X__,X_______,
  XXX_____,______XX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ___XXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FED2[ 33] = { // code FED2, ARABIC LETTER FEH FINAL FORM
  ________,_____XX_,________,
  ________,_____XX_,________,
  ________,________,________,
  ________,________,________,
  _X______,______XX,________,
  X_______,_____XXX,X_______,
  X_______,_____X__,X_______,
  X_______,_____X__,X_______,
  XXX_____,______XX,X_______,
  _XXXXXXX,XXXXXXXX,X_______,
  ___XXXXX,XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FED3[ 12] = { // code FED3, ARABIC LETTER FEH INITIAL FORM
  ___XX___,
  ___XX___,
  ________,
  ___XX___,
  __XXXX__,
  __X_XXX_,
  __X__XX_,
  __XXXXX_,
  ___XXXX_,
  ______X_,
  XXXXXXX_,
  XXXXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FED4[ 12] = { // code FED4, ARABIC LETTER FEH MEDIAL FORM
  ____XX__,
  ____XX__,
  ________,
  ________,
  ____XX__,
  ___XXXX_,
  ___X_XX_,
  ___X__X_,
  ___XXXX_,
  _____XX_,
  XXXXXXX_,
  XXXXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FED5[ 34] = { // code FED5, ARABIC LETTER QAF ISOLATED FORM
  _______X,X_______,
  _____XXX,X_______,
  _____XX_,________,
  ________,________,
  ________,________,
  _______X,XX______,
  _______X,XX______,
  ______X_,_XX_____,
  _X____X_,_XX_____,
  _X____XX,XXX_____,
  X______X,XXX_____,
  X_______,__X_____,
  X_______,__X_____,
  X_______,_XX_____,
  XX______,XXX_____,
  _XXXXXXX,XX______,
  __XXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FED6[ 34] = { // code FED6, ARABIC LETTER QAF FINAL FORM
  _______X,X_______,
  _____XXX,X_______,
  _____XX_,________,
  ________,________,
  ________,________,
  _______X,XX______,
  _______X,XX______,
  ______X_,_XX_____,
  _X____X_,_XX_____,
  _X____XX,XXX_____,
  X______X,XXX_____,
  X_______,__X_____,
  X_______,__X_____,
  X_______,_XX_____,
  XX______,XXX_____,
  _XXXXXXX,XX______,
  __XXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FED7[ 13] = { // code FED7, ARABIC LETTER QAF INITIAL FORM
  ____XX__,
  __XXXX__,
  __XX____,
  ________,
  ___XX___,
  __XXXX__,
  __X_XXX_,
  __X__XX_,
  __XXXXX_,
  ___XXXX_,
  ______X_,
  XXXXXXX_,
  XXXXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FED8[ 13] = { // code FED8, ARABIC LETTER QAF MEDIAL FORM
  ____XX__,
  __XXXX__,
  __XX____,
  ________,
  ________,
  ____XX__,
  ___XXXX_,
  ___X_XX_,
  ___X__X_,
  ___XXXX_,
  _____XX_,
  XXXXXXX_,
  XXXXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FED9[ 26] = { // code FED9, ARABIC LETTER KAF ISOLATED FORM
  ________,__XX____,
  ________,__XXX___,
  ________,___XX___,
  _______X,___X____,
  _____XX_,___X____,
  _____XXX,X__X____,
  ________,X__X____,
  _X_____X,X___X___,
  X___XXXX,____X___,
  X_______,____X___,
  XX______,____X___,
  XXXXXXXX,XXXXX___,
  _XXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEDA[ 26] = { // code FEDA, ARABIC LETTER KAF FINAL FORM
  ________,__XX____,
  ________,__XXX___,
  ________,___XX___,
  _______X,___X____,
  _____XX_,___X____,
  _____XXX,X__X____,
  ________,X__X____,
  _X_____X,X___X___,
  X___XXXX,____X___,
  X_______,____X___,
  XX______,____X___,
  XXXXXXXX,XXXXX___,
  _XXXXXXX,XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEDB[ 24] = { // code FEDB, ARABIC LETTER KAF INITIAL FORM
  _______X,________,
  ____XXXX,________,
  ___XXX__,________,
  __XX____,________,
  __X_____,________,
  __XXX___,________,
  ___XXX__,________,
  _____XX_,________,
  ______XX,________,
  _______X,X_______,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEDC[ 24] = { // code FEDC, ARABIC LETTER KAF MEDIAL FORM
  _______X,________,
  ____XXXX,________,
  ___XXX__,________,
  __XX____,________,
  __X_____,________,
  __XXX___,________,
  ___XXX__,________,
  _____XX_,________,
  ______XX,________,
  _______X,X_______,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEDD[ 32] = { // code FEDD, ARABIC LETTER LAM ISOLATED FORM
  ________,X_______,
  ________,XX______,
  ________,XX______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  __X_____,_X______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEDE[ 32] = { // code FEDE, ARABIC LETTER LAM FINAL FORM
  ________,X_______,
  ________,XX______,
  ________,XX______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  __X_____,_X______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEDF[ 13] = { // code FEDF, ARABIC LETTER LAM INITIAL FORM
  __XX____,
  __XXX___,
  ___XX___,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  XXXXX___,
  XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEE0[ 13] = { // code FEE0, ARABIC LETTER LAM MEDIAL FORM
  __XX____,
  __XXX___,
  ___XX___,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  XXXXX___,
  XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEE1[ 12] = { // code FEE1, ARABIC LETTER MEEM ISOLATED FORM
  __XXX___,
  _XXXXX__,
  ____XXX_,
  __XXXXX_,
  _XXXXXX_,
  XX______,
  X_______,
  X_______,
  X_______,
  _X______,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEE2[ 12] = { // code FEE2, ARABIC LETTER MEEM FINAL FORM
  __XXX___,
  _XXXXX__,
  ____XXX_,
  __XXXXX_,
  _XXXXXX_,
  XX______,
  X_______,
  X_______,
  X_______,
  _X______,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEE3[ 10] = { // code FEE3, ARABIC LETTER MEEM INITIAL FORM
  ______XX,________,
  _____X_X,________,
  ____XX__,X_______,
  XXXXXXXX,X_______,
  XXXX__XX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEE4[ 10] = { // code FEE4, ARABIC LETTER MEEM MEDIAL FORM
  ______XX,________,
  _____X_X,________,
  ____XX__,X_______,
  XXXXXXXX,X_______,
  XXXX__XX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEE5[ 28] = { // code FEE5, ARABIC LETTER NOON ISOLATED FORM
  ____XX__,________,
  ____XX__,________,
  ________,________,
  ________,X_______,
  ________,XX______,
  _X______,XX______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,XX______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEE6[ 28] = { // code FEE6, ARABIC LETTER NOON FINAL FORM
  ____XX__,________,
  ____XX__,________,
  ________,________,
  ________,X_______,
  ________,XX______,
  _X______,XX______,
  _X______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,XX______,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEE7[ 10] = { // code FEE7, ARABIC LETTER NOON INITIAL FORM
  ___XX___,
  ___XX___,
  ________,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEE8[ 10] = { // code FEE8, ARABIC LETTER NOON MEDIAL FORM
  ___XX___,
  ___XX___,
  ________,
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEE9[  7] = { // code FEE9, ARABIC LETTER HEH ISOLATED FORM
  _X______,
  _XXX____,
  _XXXX___,
  X___X___,
  X___X___,
  XXXXX___,
  XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEEA[ 10] = { // code FEEA, ARABIC LETTER HEH FINAL FORM
  ____X___,
  ____X___,
  ___XX___,
  __X_X___,
  _X__X___,
  XXXXX___,
  XXXX_X__,
  _____X__,
  _____XXX,
  ______XX};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEEB[ 18] = { // code FEEB, ARABIC LETTER HEH INITIAL FORM
  ____X___,________,
  ____XX__,________,
  ____XXX_,________,
  ___XXXX_,________,
  __X__XXX,________,
  __X__X_X,X_______,
  ___XX___,X_______,
  XXXXXXXX,X_______,
  XXX___XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEEC[ 24] = { // code FEEC, ARABIC LETTER HEH MEDIAL FORM
  _____XX_,________,
  ____XXX_,________,
  ___XX_X_,________,
  ___X__X_,________,
  __X_XX__,________,
  XXXXXXXX,X_______,
  XXXXXXXX,X_______,
  __X_XX__,________,
  __X___X_,________,
  __XX__X_,________,
  ___XXXX_,________,
  ____XXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEED[ 11] = { // code FEED, ARABIC LETTER WAW ISOLATED FORM
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEEE[ 11] = { // code FEEE, ARABIC LETTER WAW FINAL FORM
  _____XX_,
  ____XXXX,
  ____X__X,
  ____X__X,
  ____XXXX,
  _____XXX,
  _______X,
  ______XX,
  _____XX_,
  X___XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEEF[ 22] = { // code FEEF, ARABIC LETTER ALEF MAKSURA ISOLATED FORM
  ________,_XXX____,
  ________,XXXX____,
  _______X,X__X____,
  _X_____X,________,
  X_____X_,________,
  X_____XX,XXX_____,
  X_____XX,XXX_____,
  X_______,__X_____,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  _XXXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEF0[ 16] = { // code FEF0, ARABIC LETTER ALEF MAKSURA FINAL FORM
  _X______,________,
  _X______,XXXX____,
  X______X,XXXX____,
  X_____X_,________,
  X_____XX,XXX_____,
  XXX_____,__X_____,
  _XXXXXXX,XX______,
  __XXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEF1[ 28] = { // code FEF1, ARABIC LETTER YEH ISOLATED FORM
  ________,_XXX____,
  ________,XXXX____,
  _______X,X__X____,
  _X_____X,________,
  X_____X_,________,
  X_____XX,XXX_____,
  X_____XX,XXX_____,
  X_______,__X_____,
  XX_____X,XX______,
  XXXXXXXX,X_______,
  _XXXXXX_,________,
  _____XX_,________,
  ___XXXX_,________,
  ___XX___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEF2[ 20] = { // code FEF2, ARABIC LETTER YEH FINAL FORM
  _X______,________,
  _X______,XXXX____,
  X______X,XXXX____,
  X_____X_,________,
  X_____XX,XXX_____,
  XX______,__X_____,
  _XXXXXXX,XX______,
  __XXXXXX,X_______,
  ___X__X_,________,
  ___XXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEF3[ 11] = { // code FEF3, ARABIC LETTER YEH INITIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  ___XX___,
  _XXXX___,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEF4[ 11] = { // code FEF4, ARABIC LETTER YEH MEDIAL FORM
  ____X___,
  ____XX__,
  ____XX__,
  _____X__,
  _____X__,
  XXXXXX__,
  XXXXXX__,
  ________,
  ___XX___,
  _XXXX___,
  _XX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEF5[ 32] = { // code FEF5, ARABIC LIGATURE LAM WITH ALEF WITH MADDA ABOVE ISOLATED FORM
  XXXX____,________,
  ________,________,
  X_____X_,________,
  XX____XX,X_______,
  XXX____X,X_______,
  _XX____X,________,
  _XXX___X,________,
  ___X___X,________,
  ____X__X,________,
  ____X_X_,________,
  ____X_X_,________,
  _____X__,________,
  ____X_X_,________,
  ___X__X_,________,
  ___XXXX_,________,
  ___XXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEF6[ 30] = { // code FEF6, ARABIC LIGATURE LAM WITH ALEF WITH MADDA ABOVE FINAL FORM
  XXXX____,________,
  ________,________,
  XX______,_X______,
  XXXX____,_X______,
  _XXXXX__,_X______,
  _____XX_,_X______,
  ______X_,_X______,
  _______X,_X______,
  ________,_X______,
  ________,XX______,
  ________,XX______,
  _______X,__X_____,
  _____XXX,__XX____,
  __XXXXX_,__XX____,
  XXXXX___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEF7[ 34] = { // code FEF7, ARABIC LIGATURE LAM WITH ALEF WITH HAMZA ABOVE ISOLATED FORM
  _XX_____,________,
  X_______,________,
  _XX_____,________,
  X______X,________,
  _______X,XX______,
  _X______,XX______,
  _XX_____,X_______,
  _XXX____,X_______,
  __XX____,X_______,
  ____X___,X_______,
  _____X_X,________,
  _____X_X,________,
  ______X_,________,
  ______X_,________,
  ____XX_X,________,
  ____XXXX,________,
  ____XXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEF8[ 32] = { // code FEF8, ARABIC LIGATURE LAM WITH ALEF WITH HAMZA ABOVE FINAL FORM
  _XX_____,________,
  X_______,________,
  _XX_____,________,
  X_______,__X_____,
  _XX_____,__X_____,
  _XXXXX__,__X_____,
  __XXXXX_,__X_____,
  _______X,__X_____,
  ________,X_X_____,
  ________,__X_____,
  ________,_XX_____,
  ________,_XX_____,
  ________,X__X____,
  ______XX,X__XX___,
  ___XXXXX,___XX___,
  _XXXXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEF9[ 38] = { // code FEF9, ARABIC LIGATURE LAM WITH ALEF WITH HAMZA BELOW ISOLATED FORM
  X_____X_,________,
  XX____XX,X_______,
  XXX____X,X_______,
  _XX____X,________,
  _XXX___X,________,
  ___X___X,________,
  ____X__X,________,
  ____X_X_,________,
  ____X_X_,________,
  _____X__,________,
  ____X_X_,________,
  ___X__X_,________,
  ___XXXX_,________,
  ___XXX__,________,
  ________,________,
  ___XX___,________,
  __X_____,________,
  ___XX___,________,
  __X_____,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEFA[ 36] = { // code FEFA, ARABIC LIGATURE LAM WITH ALEF WITH HAMZA BELOW FINAL FORM
  XX______,_X______,
  XXXX____,_X______,
  _XXXXX__,_X______,
  _____XX_,_X______,
  ______X_,_X______,
  _______X,_X______,
  ________,_X______,
  ________,XX______,
  ________,XX______,
  _______X,__X_____,
  _____XXX,__XX____,
  __XXXXX_,__XX____,
  XXXXX___,________,
  ________,________,
  __XX____,________,
  _X______,________,
  __XX____,________,
  _X______,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEFB[ 28] = { // code FEFB, ARABIC LIGATURE LAM WITH ALEF ISOLATED FORM
  X_____X_,________,
  XX____XX,X_______,
  XXX____X,X_______,
  _XX____X,________,
  _XXX___X,________,
  ___X___X,________,
  ____X__X,________,
  ____X_X_,________,
  ____X_X_,________,
  _____X__,________,
  ____X_X_,________,
  ___X__X_,________,
  ___XXXX_,________,
  ___XXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FEFC[ 26] = { // code FEFC, ARABIC LIGATURE LAM WITH ALEF FINAL FORM
  XX______,_X______,
  XXXX____,_X______,
  _XXXXX__,_X______,
  _____XX_,_X______,
  ______X_,_X______,
  _______X,_X______,
  ________,_X______,
  ________,XX______,
  ________,XX______,
  _______X,__X_____,
  _____XXX,__XX____,
  __XXXXX_,__XX____,
  XXXXX___,________};

//
// Start of unicode area <Special>
//
GUI_CONST_STORAGE unsigned char acGUI_FontArabic24_FFFF[ 26] = { // code FFFF
  XXXXXXXX,XX______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  X_______,_X______,
  XXXXXXXX,XX______};

GUI_CONST_STORAGE GUI_CHARINFO_EXT GUI_FontArabic24_CharInfo[592] = {
   {   1,   1,   0,  19,   6, acGUI_FontArabic24_0020 } // code 0020, SPACE
  ,{   2,  15,   2,   4,   6, acGUI_FontArabic24_0021 } // code 0021, EXCLAMATION MARK
  ,{   6,   5,   1,   4,   7, acGUI_FontArabic24_0022 } // code 0022, QUOTATION MARK
  ,{  12,  15,   0,   4,  12, acGUI_FontArabic24_0023 } // code 0023, NUMBER SIGN
  ,{   9,  18,   1,   3,  12, acGUI_FontArabic24_0024 } // code 0024, DOLLAR SIGN
  ,{  17,  15,   1,   4,  19, acGUI_FontArabic24_0025 } // code 0025, PERCENT SIGN
  ,{  13,  15,   1,   4,  14, acGUI_FontArabic24_0026 } // code 0026, AMPERSAND
  ,{   2,   5,   1,   4,   4, acGUI_FontArabic24_0027 } // code 0027, APOSTROPHE
  ,{   5,  19,   1,   4,   7, acGUI_FontArabic24_0028 } // code 0028, LEFT PARENTHESIS
  ,{   5,  19,   1,   4,   7, acGUI_FontArabic24_0029 } // code 0029, RIGHT PARENTHESIS
  ,{   8,   6,   0,   4,   8, acGUI_FontArabic24_002A } // code 002A, ASTERISK
  ,{  10,  10,   1,   7,  12, acGUI_FontArabic24_002B } // code 002B, PLUS SIGN
  ,{   2,   5,   2,  17,   6, acGUI_FontArabic24_002C } // code 002C, COMMA
  ,{   6,   2,   0,  12,   7, acGUI_FontArabic24_002D } // code 002D, HYPHEN-MINUS
  ,{   2,   2,   2,  17,   6, acGUI_FontArabic24_002E } // code 002E, FULL STOP
  ,{   6,  15,   0,   4,   6, acGUI_FontArabic24_002F } // code 002F, SOLIDUS
  ,{  10,  15,   1,   4,  12, acGUI_FontArabic24_0030 } // code 0030, DIGIT ZERO
  ,{   6,  15,   2,   4,  12, acGUI_FontArabic24_0031 } // code 0031, DIGIT ONE
  ,{  10,  15,   1,   4,  12, acGUI_FontArabic24_0032 } // code 0032, DIGIT TWO
  ,{  10,  15,   1,   4,  12, acGUI_FontArabic24_0033 } // code 0033, DIGIT THREE
  ,{  10,  15,   1,   4,  12, acGUI_FontArabic24_0034 } // code 0034, DIGIT FOUR
  ,{  10,  15,   1,   4,  12, acGUI_FontArabic24_0035 } // code 0035, DIGIT FIVE
  ,{  10,  15,   1,   4,  12, acGUI_FontArabic24_0036 } // code 0036, DIGIT SIX
  ,{  10,  15,   1,   4,  12, acGUI_FontArabic24_0037 } // code 0037, DIGIT SEVEN
  ,{  10,  15,   1,   4,  12, acGUI_FontArabic24_0038 } // code 0038, DIGIT EIGHT
  ,{  10,  15,   1,   4,  12, acGUI_FontArabic24_0039 } // code 0039, DIGIT NINE
  ,{   2,  11,   2,   8,   6, acGUI_FontArabic24_003A } // code 003A, COLON
  ,{   2,  14,   2,   8,   6, acGUI_FontArabic24_003B } // code 003B, SEMICOLON
  ,{  10,  11,   1,   6,  12, acGUI_FontArabic24_003C } // code 003C, LESS-THAN SIGN
  ,{  10,   7,   1,   8,  12, acGUI_FontArabic24_003D } // code 003D, EQUALS SIGN
  ,{  10,  11,   1,   6,  12, acGUI_FontArabic24_003E } // code 003E, GREATER-THAN SIGN
  ,{  10,  15,   1,   4,  12, acGUI_FontArabic24_003F } // code 003F, QUESTION MARK
  ,{  19,  19,   1,   4,  21, acGUI_FontArabic24_0040 } // code 0040, COMMERCIAL AT
  ,{  13,  15,   0,   4,  13, acGUI_FontArabic24_0041 } // code 0041, LATIN CAPITAL LETTER A
  ,{  11,  15,   2,   4,  14, acGUI_FontArabic24_0042 } // code 0042, LATIN CAPITAL LETTER B
  ,{  13,  15,   1,   4,  15, acGUI_FontArabic24_0043 } // code 0043, LATIN CAPITAL LETTER C
  ,{  12,  15,   2,   4,  15, acGUI_FontArabic24_0044 } // code 0044, LATIN CAPITAL LETTER D
  ,{  11,  15,   2,   4,  14, acGUI_FontArabic24_0045 } // code 0045, LATIN CAPITAL LETTER E
  ,{  10,  15,   2,   4,  13, acGUI_FontArabic24_0046 } // code 0046, LATIN CAPITAL LETTER F
  ,{  14,  15,   1,   4,  16, acGUI_FontArabic24_0047 } // code 0047, LATIN CAPITAL LETTER G
  ,{  12,  15,   1,   4,  14, acGUI_FontArabic24_0048 } // code 0048, LATIN CAPITAL LETTER H
  ,{   2,  15,   2,   4,   6, acGUI_FontArabic24_0049 } // code 0049, LATIN CAPITAL LETTER I
  ,{   8,  15,   1,   4,  11, acGUI_FontArabic24_004A } // code 004A, LATIN CAPITAL LETTER J
  ,{  12,  15,   2,   4,  14, acGUI_FontArabic24_004B } // code 004B, LATIN CAPITAL LETTER K
  ,{   9,  15,   2,   4,  12, acGUI_FontArabic24_004C } // code 004C, LATIN CAPITAL LETTER L
  ,{  15,  15,   1,   4,  17, acGUI_FontArabic24_004D } // code 004D, LATIN CAPITAL LETTER M
  ,{  12,  15,   1,   4,  14, acGUI_FontArabic24_004E } // code 004E, LATIN CAPITAL LETTER N
  ,{  14,  15,   1,   4,  16, acGUI_FontArabic24_004F } // code 004F, LATIN CAPITAL LETTER O
  ,{  11,  15,   2,   4,  14, acGUI_FontArabic24_0050 } // code 0050, LATIN CAPITAL LETTER P
  ,{  14,  16,   1,   4,  16, acGUI_FontArabic24_0051 } // code 0051, LATIN CAPITAL LETTER Q
  ,{  12,  15,   2,   4,  15, acGUI_FontArabic24_0052 } // code 0052, LATIN CAPITAL LETTER R
  ,{  12,  15,   1,   4,  14, acGUI_FontArabic24_0053 } // code 0053, LATIN CAPITAL LETTER S
  ,{  12,  15,   0,   4,  12, acGUI_FontArabic24_0054 } // code 0054, LATIN CAPITAL LETTER T
  ,{  12,  15,   1,   4,  14, acGUI_FontArabic24_0055 } // code 0055, LATIN CAPITAL LETTER U
  ,{  13,  15,   0,   4,  13, acGUI_FontArabic24_0056 } // code 0056, LATIN CAPITAL LETTER V
  ,{  21,  15,   0,   4,  21, acGUI_FontArabic24_0057 } // code 0057, LATIN CAPITAL LETTER W
  ,{  14,  15,   0,   4,  14, acGUI_FontArabic24_0058 } // code 0058, LATIN CAPITAL LETTER X
  ,{  14,  15,   0,   4,  14, acGUI_FontArabic24_0059 } // code 0059, LATIN CAPITAL LETTER Y
  ,{  12,  15,   0,   4,  13, acGUI_FontArabic24_005A } // code 005A, LATIN CAPITAL LETTER Z
  ,{   4,  19,   1,   4,   6, acGUI_FontArabic24_005B } // code 005B, LEFT SQUARE BRACKET
  ,{   6,  15,   0,   4,   6, acGUI_FontArabic24_005C } // code 005C, REVERSE SOLIDUS
  ,{   4,  19,   1,   4,   6, acGUI_FontArabic24_005D } // code 005D, RIGHT SQUARE BRACKET
  ,{   8,   8,   0,   4,   8, acGUI_FontArabic24_005E } // code 005E, CIRCUMFLEX ACCENT
  ,{  12,   2,   0,  21,  12, acGUI_FontArabic24_005F } // code 005F, LOW LINE
  ,{   3,   3,   1,   4,   7, acGUI_FontArabic24_0060 } // code 0060, GRAVE ACCENT
  ,{  10,  11,   1,   8,  12, acGUI_FontArabic24_0061 } // code 0061, LATIN SMALL LETTER A
  ,{   9,  15,   1,   4,  11, acGUI_FontArabic24_0062 } // code 0062, LATIN SMALL LETTER B
  ,{   9,  11,   1,   8,  11, acGUI_FontArabic24_0063 } // code 0063, LATIN SMALL LETTER C
  ,{   9,  15,   1,   4,  11, acGUI_FontArabic24_0064 } // code 0064, LATIN SMALL LETTER D
  ,{  10,  11,   1,   8,  12, acGUI_FontArabic24_0065 } // code 0065, LATIN SMALL LETTER E
  ,{   7,  15,   0,   4,   6, acGUI_FontArabic24_0066 } // code 0066, LATIN SMALL LETTER F
  ,{   9,  15,   1,   8,  11, acGUI_FontArabic24_0067 } // code 0067, LATIN SMALL LETTER G
  ,{   9,  15,   1,   4,  11, acGUI_FontArabic24_0068 } // code 0068, LATIN SMALL LETTER H
  ,{   2,  15,   1,   4,   5, acGUI_FontArabic24_0069 } // code 0069, LATIN SMALL LETTER I
  ,{   4,  19,  -1,   4,   4, acGUI_FontArabic24_006A } // code 006A, LATIN SMALL LETTER J
  ,{   9,  15,   1,   4,  10, acGUI_FontArabic24_006B } // code 006B, LATIN SMALL LETTER K
  ,{   2,  15,   1,   4,   4, acGUI_FontArabic24_006C } // code 006C, LATIN SMALL LETTER L
  ,{  14,  11,   1,   8,  16, acGUI_FontArabic24_006D } // code 006D, LATIN SMALL LETTER M
  ,{   9,  11,   1,   8,  11, acGUI_FontArabic24_006E } // code 006E, LATIN SMALL LETTER N
  ,{  10,  11,   1,   8,  12, acGUI_FontArabic24_006F } // code 006F, LATIN SMALL LETTER O
  ,{   9,  15,   1,   8,  11, acGUI_FontArabic24_0070 } // code 0070, LATIN SMALL LETTER P
  ,{   9,  15,   1,   8,  11, acGUI_FontArabic24_0071 } // code 0071, LATIN SMALL LETTER Q
  ,{   6,  11,   1,   8,   7, acGUI_FontArabic24_0072 } // code 0072, LATIN SMALL LETTER R
  ,{   9,  11,   1,   8,  11, acGUI_FontArabic24_0073 } // code 0073, LATIN SMALL LETTER S
  ,{   5,  15,   0,   4,   6, acGUI_FontArabic24_0074 } // code 0074, LATIN SMALL LETTER T
  ,{   9,  11,   1,   8,  11, acGUI_FontArabic24_0075 } // code 0075, LATIN SMALL LETTER U
  ,{  11,  11,   0,   8,  11, acGUI_FontArabic24_0076 } // code 0076, LATIN SMALL LETTER V
  ,{  17,  11,  -1,   8,  15, acGUI_FontArabic24_0077 } // code 0077, LATIN SMALL LETTER W
  ,{  10,  11,   0,   8,  10, acGUI_FontArabic24_0078 } // code 0078, LATIN SMALL LETTER X
  ,{   9,  15,   1,   8,  11, acGUI_FontArabic24_0079 } // code 0079, LATIN SMALL LETTER Y
  ,{   9,  11,   0,   8,   9, acGUI_FontArabic24_007A } // code 007A, LATIN SMALL LETTER Z
  ,{   6,  19,   0,   4,   7, acGUI_FontArabic24_007B } // code 007B, LEFT CURLY BRACKET
  ,{   2,  20,   2,   4,   6, acGUI_FontArabic24_007C } // code 007C, VERTICAL LINE
  ,{   6,  19,   1,   4,   7, acGUI_FontArabic24_007D } // code 007D, RIGHT CURLY BRACKET
  ,{  10,   4,   1,  10,  12, acGUI_FontArabic24_007E } // code 007E, TILDE
  ,{   1,   3,   3,  20,   7, acGUI_FontArabic24_05B0 } // code 05B0, HEBREW POINT SHEVA
  ,{   5,   3,   1,  20,   7, acGUI_FontArabic24_05B1 } // code 05B1, HEBREW POINT HATAF SEGOL
  ,{   5,   3,   1,  20,   7, acGUI_FontArabic24_05B2 } // code 05B2, HEBREW POINT HATAF PATAH
  ,{   5,   3,   1,  20,   7, acGUI_FontArabic24_05B3 } // code 05B3, HEBREW POINT HATAF QAMATS
  ,{   1,   1,   3,  22,   7, acGUI_FontArabic24_05B4 } // code 05B4, HEBREW POINT HIRIQ
  ,{   3,   1,   2,  22,   7, acGUI_FontArabic24_05B5 } // code 05B5, HEBREW POINT TSERE
  ,{   3,   3,   2,  20,   7, acGUI_FontArabic24_05B6 } // code 05B6, HEBREW POINT SEGOL
  ,{   4,   1,   1,  21,   7, acGUI_FontArabic24_05B7 } // code 05B7, HEBREW POINT PATAH
  ,{   3,   3,   2,  20,   7, acGUI_FontArabic24_05B8 } // code 05B8, HEBREW POINT QAMATS
  ,{   1,   1,   3,   6,   7, acGUI_FontArabic24_05B9 } // code 05B9, HEBREW POINT HOLAM
  ,{   1,   1,   3,   6,   7, acGUI_FontArabic24_05BA } // code 05BA
  ,{   5,   3,   1,  20,   7, acGUI_FontArabic24_05BB } // code 05BB, HEBREW POINT QUBUTS
  ,{   1,   1,   3,  12,   7, acGUI_FontArabic24_05BC } // code 05BC, HEBREW POINT DAGESH OR MAPIQ
  ,{   1,   3,   3,  20,   7, acGUI_FontArabic24_05BD } // code 05BD, HEBREW POINT METEG
  ,{   5,   2,   1,   8,   8, acGUI_FontArabic24_05BE } // code 05BE, HEBREW PUNCTUATION MAQAF
  ,{   4,   1,   1,   5,   7, acGUI_FontArabic24_05BF } // code 05BF, HEBREW POINT RAFE
  ,{   2,  13,   2,   6,   6, acGUI_FontArabic24_05C0 } // code 05C0, HEBREW PUNCTUATION PASEQ
  ,{   1,   1,   8,   5,   7, acGUI_FontArabic24_05C1 } // code 05C1, HEBREW POINT SHIN DOT
  ,{   1,   1,  -2,   5,   7, acGUI_FontArabic24_05C2 } // code 05C2, HEBREW POINT SIN DOT
  ,{   2,  11,   2,   8,   6, acGUI_FontArabic24_05C3 } // code 05C3, HEBREW PUNCTUATION SOF PASUQ
  ,{  11,  11,   1,   8,  12, acGUI_FontArabic24_05D0 } // code 05D0, HEBREW LETTER ALEF
  ,{   9,  11,   1,   8,  11, acGUI_FontArabic24_05D1 } // code 05D1, HEBREW LETTER BET
  ,{   7,  11,   0,   8,   8, acGUI_FontArabic24_05D2 } // code 05D2, HEBREW LETTER GIMEL
  ,{   9,  11,   1,   8,  11, acGUI_FontArabic24_05D3 } // code 05D3, HEBREW LETTER DALET
  ,{   9,  11,   2,   8,  13, acGUI_FontArabic24_05D4 } // code 05D4, HEBREW LETTER HE
  ,{   2,  11,   2,   8,   6, acGUI_FontArabic24_05D5 } // code 05D5, HEBREW LETTER VAV
  ,{   6,  11,   1,   8,   8, acGUI_FontArabic24_05D6 } // code 05D6, HEBREW LETTER ZAYIN
  ,{   9,  11,   2,   8,  13, acGUI_FontArabic24_05D7 } // code 05D7, HEBREW LETTER HET
  ,{   8,  11,   2,   8,  12, acGUI_FontArabic24_05D8 } // code 05D8, HEBREW LETTER TET
  ,{   2,   6,   2,   8,   6, acGUI_FontArabic24_05D9 } // code 05D9, HEBREW LETTER YOD
  ,{   9,  15,   0,   8,  11, acGUI_FontArabic24_05DA } // code 05DA, HEBREW LETTER FINAL KAF
  ,{   8,  11,   1,   8,  10, acGUI_FontArabic24_05DB } // code 05DB, HEBREW LETTER KAF
  ,{   8,  15,   1,   4,  10, acGUI_FontArabic24_05DC } // code 05DC, HEBREW LETTER LAMED
  ,{   9,  11,   2,   8,  13, acGUI_FontArabic24_05DD } // code 05DD, HEBREW LETTER FINAL MEM
  ,{  11,  11,   0,   8,  13, acGUI_FontArabic24_05DE } // code 05DE, HEBREW LETTER MEM
  ,{   2,  15,   2,   8,   6, acGUI_FontArabic24_05DF } // code 05DF, HEBREW LETTER FINAL NUN
  ,{   5,  11,   1,   8,   7, acGUI_FontArabic24_05E0 } // code 05E0, HEBREW LETTER NUN
  ,{  10,  11,   1,   8,  12, acGUI_FontArabic24_05E1 } // code 05E1, HEBREW LETTER SAMEKH
  ,{   9,  12,   0,   8,  11, acGUI_FontArabic24_05E2 } // code 05E2, HEBREW LETTER AYIN
  ,{   9,  15,   1,   8,  12, acGUI_FontArabic24_05E3 } // code 05E3, HEBREW LETTER FINAL PE
  ,{   9,  11,   1,   8,  11, acGUI_FontArabic24_05E4 } // code 05E4, HEBREW LETTER PE
  ,{   9,  15,   0,   8,  10, acGUI_FontArabic24_05E5 } // code 05E5, HEBREW LETTER FINAL TSADI
  ,{   9,  11,   0,   8,  10, acGUI_FontArabic24_05E6 } // code 05E6, HEBREW LETTER TSADI
  ,{   9,  15,   2,   8,  12, acGUI_FontArabic24_05E7 } // code 05E7, HEBREW LETTER QOF
  ,{   9,  11,   0,   8,  11, acGUI_FontArabic24_05E8 } // code 05E8, HEBREW LETTER RESH
  ,{  13,  11,   1,   8,  15, acGUI_FontArabic24_05E9 } // code 05E9, HEBREW LETTER SHIN
  ,{  11,  11,   1,   8,  14, acGUI_FontArabic24_05EA } // code 05EA, HEBREW LETTER TAV
  ,{   7,  11,   2,   8,  11, acGUI_FontArabic24_05F0 } // code 05F0, HEBREW LIGATURE YIDDISH DOUBLE VAV
  ,{   7,  11,   2,   8,  11, acGUI_FontArabic24_05F1 } // code 05F1, HEBREW LIGATURE YIDDISH VAV YOD
  ,{   7,   6,   2,   8,  11, acGUI_FontArabic24_05F2 } // code 05F2, HEBREW LIGATURE YIDDISH DOUBLE YOD
  ,{   3,   4,   1,   8,   5, acGUI_FontArabic24_05F3 } // code 05F3, HEBREW PUNCTUATION GERESH
  ,{   7,   4,   1,   8,   9, acGUI_FontArabic24_05F4 } // code 05F4, HEBREW PUNCTUATION GERSHAYIM
  ,{   3,   6,   2,  10,   7, acGUI_FontArabic24_060C } // code 060C, ARABIC COMMA
  ,{   3,   9,   2,   7,   7, acGUI_FontArabic24_061B } // code 061B, ARABIC SEMICOLON
  ,{   6,  12,   0,   4,   7, acGUI_FontArabic24_061F } // code 061F, ARABIC QUESTION MARK
  ,{   6,   8,   1,  10,   9, acGUI_FontArabic24_0621 } // code 0621, ARABIC LETTER HAMZA
  ,{   4,  14,   0,   2,   4, acGUI_FontArabic24_0622 } // code 0622, ARABIC LETTER ALEF WITH MADDA ABOVE
  ,{   3,  15,   1,   1,   4, acGUI_FontArabic24_0623 } // code 0623, ARABIC LETTER ALEF WITH HAMZA ABOVE
  ,{   8,  17,   1,   4,   9, acGUI_FontArabic24_0624 } // code 0624, ARABIC LETTER WAW WITH HAMZA ABOVE
  ,{   3,  17,   0,   4,   4, acGUI_FontArabic24_0625 } // code 0625, ARABIC LETTER ALEF WITH HAMZA BELOW
  ,{  12,  13,   1,   7,  13, acGUI_FontArabic24_0626 } // code 0626, ARABIC LETTER YEH WITH HAMZA ABOVE
  ,{   2,  12,   1,   4,   4, acGUI_FontArabic24_0627 } // code 0627, ARABIC LETTER ALEF
  ,{  14,  11,   1,   9,  15, acGUI_FontArabic24_0628 } // code 0628, ARABIC LETTER BEH
  ,{   5,  11,   1,   5,   6, acGUI_FontArabic24_0629 } // code 0629, ARABIC LETTER TEH MARBUTA
  ,{  14,  10,   1,   6,  15, acGUI_FontArabic24_062A } // code 062A, ARABIC LETTER TEH
  ,{  14,  11,   1,   5,  15, acGUI_FontArabic24_062B } // code 062B, ARABIC LETTER THEH
  ,{  10,  13,   1,  10,  12, acGUI_FontArabic24_062C } // code 062C, ARABIC LETTER JEEM
  ,{  10,  13,   1,  10,  12, acGUI_FontArabic24_062D } // code 062D, ARABIC LETTER HAH
  ,{  10,  17,   1,   6,  12, acGUI_FontArabic24_062E } // code 062E, ARABIC LETTER KHAH
  ,{   6,   9,   1,   7,   7, acGUI_FontArabic24_062F } // code 062F, ARABIC LETTER DAL
  ,{   6,  13,   1,   3,   7, acGUI_FontArabic24_0630 } // code 0630, ARABIC LETTER THAL
  ,{   9,  11,   1,  10,  10, acGUI_FontArabic24_0631 } // code 0631, ARABIC LETTER REH
  ,{   9,  15,   1,   6,  10, acGUI_FontArabic24_0632 } // code 0632, ARABIC LETTER ZAIN
  ,{  16,  11,   1,  10,  17, acGUI_FontArabic24_0633 } // code 0633, ARABIC LETTER SEEN
  ,{  16,  16,   1,   5,  17, acGUI_FontArabic24_0634 } // code 0634, ARABIC LETTER SHEEN
  ,{  22,  11,   1,  10,  23, acGUI_FontArabic24_0635 } // code 0635, ARABIC LETTER SAD
  ,{  22,  14,   1,   7,  23, acGUI_FontArabic24_0636 } // code 0636, ARABIC LETTER DAD
  ,{  13,  13,  -1,   3,  12, acGUI_FontArabic24_0637 } // code 0637, ARABIC LETTER TAH
  ,{  13,  13,  -1,   3,  12, acGUI_FontArabic24_0638 } // code 0638, ARABIC LETTER ZAH
  ,{  11,  17,   0,   6,  11, acGUI_FontArabic24_0639 } // code 0639, ARABIC LETTER AIN
  ,{  11,  21,   0,   2,  11, acGUI_FontArabic24_063A } // code 063A, ARABIC LETTER GHAIN
  ,{   5,   2,  -1,  14,   4, acGUI_FontArabic24_0640 } // code 0640, ARABIC TATWEEL
  ,{  17,  11,   0,   5,  17, acGUI_FontArabic24_0641 } // code 0641, ARABIC LETTER FEH
  ,{  11,  17,   1,   4,  12, acGUI_FontArabic24_0642 } // code 0642, ARABIC LETTER QAF
  ,{  13,  13,   0,   3,  13, acGUI_FontArabic24_0643 } // code 0643, ARABIC LETTER KAF
  ,{  10,  16,   1,   3,  11, acGUI_FontArabic24_0644 } // code 0644, ARABIC LETTER LAM
  ,{   7,  12,   0,  11,   7, acGUI_FontArabic24_0645 } // code 0645, ARABIC LETTER MEEM
  ,{  10,  14,   1,   7,  11, acGUI_FontArabic24_0646 } // code 0646, ARABIC LETTER NOON
  ,{   5,   7,   1,   9,   6, acGUI_FontArabic24_0647 } // code 0647, ARABIC LETTER HEH
  ,{   8,  11,   1,  10,   9, acGUI_FontArabic24_0648 } // code 0648, ARABIC LETTER WAW
  ,{  12,  11,   1,   9,  13, acGUI_FontArabic24_0649 } // code 0649, ARABIC LETTER ALEF MAKSURA
  ,{  12,  14,   1,   9,  13, acGUI_FontArabic24_064A } // code 064A, ARABIC LETTER YEH
  ,{   4,   4,   1,   2,   4, acGUI_FontArabic24_064B } // code 064B, ARABIC FATHATAN
  ,{   6,   5,   0,   1,   5, acGUI_FontArabic24_064C } // code 064C, ARABIC DAMMATAN
  ,{   4,   4,   1,  18,   4, acGUI_FontArabic24_064D } // code 064D, ARABIC KASRATAN
  ,{   4,   2,   1,   4,   4, acGUI_FontArabic24_064E } // code 064E, ARABIC FATHA
  ,{   5,   5,  -1,   1,   4, acGUI_FontArabic24_064F } // code 064F, ARABIC DAMMA
  ,{   4,   2,   1,  17,   4, acGUI_FontArabic24_0650 } // code 0650, ARABIC KASRA
  ,{   5,   3,   0,   3,   4, acGUI_FontArabic24_0651 } // code 0651, ARABIC SHADDA
  ,{   4,   3,   0,   3,   3, acGUI_FontArabic24_0652 } // code 0652, ARABIC SUKUN
  ,{   4,   2,   0,   2,   4, acGUI_FontArabic24_0653 } // code 0653, ARABIC MADDAH ABOVE
  ,{   3,   4,   1,   1,   4, acGUI_FontArabic24_0654 } // code 0654, ARABIC HAMZA ABOVE
  ,{   3,   4,   1,  18,   4, acGUI_FontArabic24_0655 } // code 0655, ARABIC HAMZA BELOW
  ,{   3,   5,   4,   9,  11, acGUI_FontArabic24_0660 } // code 0660, ARABIC-INDIC DIGIT ZERO
  ,{   3,  12,   4,   4,  11, acGUI_FontArabic24_0661 } // code 0661, ARABIC-INDIC DIGIT ONE
  ,{   6,  12,   3,   4,  11, acGUI_FontArabic24_0662 } // code 0662, ARABIC-INDIC DIGIT TWO
  ,{   9,  12,   2,   4,  11, acGUI_FontArabic24_0663 } // code 0663, ARABIC-INDIC DIGIT THREE
  ,{   6,  12,   3,   4,  11, acGUI_FontArabic24_0664 } // code 0664, ARABIC-INDIC DIGIT FOUR
  ,{   7,   8,   2,   6,  11, acGUI_FontArabic24_0665 } // code 0665, ARABIC-INDIC DIGIT FIVE
  ,{   7,  12,   2,   4,  11, acGUI_FontArabic24_0666 } // code 0666, ARABIC-INDIC DIGIT SIX
  ,{   9,  12,   1,   4,  11, acGUI_FontArabic24_0667 } // code 0667, ARABIC-INDIC DIGIT SEVEN
  ,{   9,  12,   1,   4,  11, acGUI_FontArabic24_0668 } // code 0668, ARABIC-INDIC DIGIT EIGHT
  ,{   6,  12,   3,   4,  11, acGUI_FontArabic24_0669 } // code 0669, ARABIC-INDIC DIGIT NINE
  ,{   9,  14,   1,   3,  11, acGUI_FontArabic24_066A } // code 066A, ARABIC PERCENT SIGN
  ,{   3,   5,   2,  13,   7, acGUI_FontArabic24_066B } // code 066B, ARABIC DECIMAL SEPARATOR
  ,{   3,   6,   2,  10,   7, acGUI_FontArabic24_066C } // code 066C, ARABIC THOUSANDS SEPARATOR
  ,{   7,   7,   2,   4,  11, acGUI_FontArabic24_066D } // code 066D, ARABIC FIVE POINTED STAR
  ,{  14,   7,   1,   9,  15, acGUI_FontArabic24_066E } // code 066E, ARABIC LETTER DOTLESS BEH
  ,{  11,  12,   1,   9,  12, acGUI_FontArabic24_066F } // code 066F, ARABIC LETTER DOTLESS QAF
  ,{   4,  16,   0,   0,   4, acGUI_FontArabic24_0671 } // code 0671, ARABIC LETTER ALEF WASLA
  ,{   4,  16,   0,   0,   4, acGUI_FontArabic24_0672 } // code 0672, ARABIC LETTER ALEF WITH WAVY HAMZA ABOVE
  ,{   4,  17,   0,   4,   4, acGUI_FontArabic24_0673 } // code 0673, ARABIC LETTER ALEF WITH WAVY HAMZA BELOW
  ,{   3,   4,   1,   1,   4, acGUI_FontArabic24_0674 } // code 0674, ARABIC LETTER HIGH HAMZA
  ,{   6,  12,   0,   4,   4, acGUI_FontArabic24_0675 } // code 0675, ARABIC LETTER HIGH HAMZA ALEF
  ,{   9,  16,   1,   5,   9, acGUI_FontArabic24_0676 } // code 0676, ARABIC LETTER HIGH HAMZA WAW
  ,{   9,  16,   1,   5,   9, acGUI_FontArabic24_0677 } // code 0677, ARABIC LETTER U WITH HAMZA ABOVE
  ,{  13,  16,   1,   4,  13, acGUI_FontArabic24_0678 } // code 0678, ARABIC LETTER HIGH HAMZA YEH
  ,{  14,  15,   1,   1,  15, acGUI_FontArabic24_0679 } // code 0679, ARABIC LETTER TTEH
  ,{  14,  12,   1,   4,  15, acGUI_FontArabic24_067A } // code 067A, ARABIC LETTER TTEHEH
  ,{  14,  12,   1,   9,  15, acGUI_FontArabic24_067B } // code 067B, ARABIC LETTER BEEH
  ,{  14,  12,   1,   6,  15, acGUI_FontArabic24_067C } // code 067C, ARABIC LETTER TEH WITH RING
  ,{  14,  12,   1,   4,  15, acGUI_FontArabic24_067D } // code 067D, ARABIC LETTER TEH WITH THREE DOTS ABOVE DOWNWARDS
  ,{  14,  13,   1,   9,  15, acGUI_FontArabic24_067E } // code 067E, ARABIC LETTER PEH
  ,{  14,  12,   1,   4,  15, acGUI_FontArabic24_067F } // code 067F, ARABIC LETTER TEHEH
  ,{  14,  13,   1,   9,  15, acGUI_FontArabic24_0680 } // code 0680, ARABIC LETTER BEHEH
  ,{  10,  18,   1,   5,  12, acGUI_FontArabic24_0681 } // code 0681, ARABIC LETTER HAH WITH HAMZA ABOVE
  ,{  10,  19,   1,   4,  12, acGUI_FontArabic24_0682 } // code 0682, ARABIC LETTER HAH WITH TWO DOTS VERTICAL ABOVE
  ,{  10,  13,   1,  10,  12, acGUI_FontArabic24_0683 } // code 0683, ARABIC LETTER NYEH
  ,{  10,  13,   1,  10,  12, acGUI_FontArabic24_0684 } // code 0684, ARABIC LETTER DYEH
  ,{  10,  19,   1,   4,  12, acGUI_FontArabic24_0685 } // code 0685, ARABIC LETTER HAH WITH THREE DOTS ABOVE
  ,{  10,  13,   1,  10,  12, acGUI_FontArabic24_0686 } // code 0686, ARABIC LETTER TCHEH
  ,{  10,  13,   1,  10,  12, acGUI_FontArabic24_0687 } // code 0687, ARABIC LETTER TCHEHEH
  ,{   6,  16,   1,   0,   7, acGUI_FontArabic24_0688 } // code 0688, ARABIC LETTER DDAL
  ,{   6,  11,   1,   7,   7, acGUI_FontArabic24_0689 } // code 0689, ARABIC LETTER DAL WITH RING
  ,{   6,  12,   1,   7,   7, acGUI_FontArabic24_068A } // code 068A, ARABIC LETTER DAL WITH DOT BELOW
  ,{   6,  19,   1,   0,   7, acGUI_FontArabic24_068B } // code 068B, ARABIC LETTER DAL WITH DOT BELOW AND SMALL TAH
  ,{   6,  13,   1,   3,   7, acGUI_FontArabic24_068C } // code 068C, ARABIC LETTER DAHAL
  ,{   6,  13,   1,   7,   7, acGUI_FontArabic24_068D } // code 068D, ARABIC LETTER DDAHAL
  ,{   6,  14,   1,   2,   7, acGUI_FontArabic24_068E } // code 068E, ARABIC LETTER DUL
  ,{   6,  14,   1,   2,   7, acGUI_FontArabic24_068F } // code 068F, ARABIC LETTER DAL WITH THREE DOTS ABOVE DOWNWARDS
  ,{   6,  15,   1,   1,   7, acGUI_FontArabic24_0690 } // code 0690, ARABIC LETTER DAL WITH FOUR DOTS ABOVE
  ,{   9,  20,   1,   1,  10, acGUI_FontArabic24_0691 } // code 0691, ARABIC LETTER RREH
  ,{   9,  15,   1,   6,  10, acGUI_FontArabic24_0692 } // code 0692, ARABIC LETTER REH WITH SMALL V
  ,{   9,  12,   1,  10,  10, acGUI_FontArabic24_0693 } // code 0693, ARABIC LETTER REH WITH RING
  ,{   9,  12,   1,  10,  10, acGUI_FontArabic24_0694 } // code 0694, ARABIC LETTER REH WITH DOT BELOW
  ,{   9,  13,   1,  10,  10, acGUI_FontArabic24_0695 } // code 0695, ARABIC LETTER REH WITH SMALL V BELOW
  ,{   9,  12,   1,  10,  10, acGUI_FontArabic24_0696 } // code 0696, ARABIC LETTER REH WITH DOT BELOW AND DOT ABOVE
  ,{   9,  16,   1,   5,  10, acGUI_FontArabic24_0697 } // code 0697, ARABIC LETTER REH WITH TWO DOTS ABOVE
  ,{   9,  16,   1,   5,  10, acGUI_FontArabic24_0698 } // code 0698, ARABIC LETTER JEH
  ,{   9,  18,   1,   3,  10, acGUI_FontArabic24_0699 } // code 0699, ARABIC LETTER REH WITH FOUR DOTS ABOVE
  ,{  16,  14,   1,   7,  17, acGUI_FontArabic24_069A } // code 069A, ARABIC LETTER SEEN WITH DOT BELOW AND DOT ABOVE
  ,{  16,  11,   1,  10,  17, acGUI_FontArabic24_069B } // code 069B, ARABIC LETTER SEEN WITH THREE DOTS BELOW
  ,{  16,  17,   1,   4,  17, acGUI_FontArabic24_069C } // code 069C, ARABIC LETTER SEEN WITH THREE DOTS BELOW AND THREE DOTS ABOVE
  ,{  22,  11,   1,  10,  23, acGUI_FontArabic24_069D } // code 069D, ARABIC LETTER SAD WITH TWO DOTS BELOW
  ,{  22,  17,   1,   4,  23, acGUI_FontArabic24_069E } // code 069E, ARABIC LETTER SAD WITH THREE DOTS ABOVE
  ,{  13,  13,  -1,   3,  12, acGUI_FontArabic24_069F } // code 069F, ARABIC LETTER TAH WITH THREE DOTS ABOVE
  ,{  11,  22,   0,   1,  11, acGUI_FontArabic24_06A0 } // code 06A0, ARABIC LETTER AIN WITH THREE DOTS ABOVE
  ,{  17,   7,   0,   9,  17, acGUI_FontArabic24_06A1 } // code 06A1, ARABIC LETTER DOTLESS FEH
  ,{  17,  10,   0,   9,  17, acGUI_FontArabic24_06A2 } // code 06A2, ARABIC LETTER FEH WITH DOT MOVED BELOW
  ,{  17,  13,   0,   6,  17, acGUI_FontArabic24_06A3 } // code 06A3, ARABIC LETTER FEH WITH DOT BELOW
  ,{  17,  13,   0,   3,  17, acGUI_FontArabic24_06A4 } // code 06A4, ARABIC LETTER VEH
  ,{  17,  12,   0,   9,  17, acGUI_FontArabic24_06A5 } // code 06A5, ARABIC LETTER FEH WITH THREE DOTS BELOW
  ,{  17,  13,   0,   3,  17, acGUI_FontArabic24_06A6 } // code 06A6, ARABIC LETTER PEHEH
  ,{  11,  15,   1,   6,  12, acGUI_FontArabic24_06A7 } // code 06A7, ARABIC LETTER QAF WITH DOT ABOVE
  ,{  11,  17,   1,   4,  12, acGUI_FontArabic24_06A8 } // code 06A8, ARABIC LETTER QAF WITH THREE DOTS ABOVE
  ,{  17,  12,   0,   4,  17, acGUI_FontArabic24_06A9 } // code 06A9, ARABIC LETTER KEHEH
  ,{  17,  11,   0,   5,  17, acGUI_FontArabic24_06AA } // code 06AA, ARABIC LETTER SWASH KAF
  ,{  17,  12,   0,   4,  17, acGUI_FontArabic24_06AB } // code 06AB, ARABIC LETTER KAF WITH RING
  ,{  13,  13,   0,   3,  13, acGUI_FontArabic24_06AC } // code 06AC, ARABIC LETTER KAF WITH DOT ABOVE
  ,{  13,  15,   0,   1,  13, acGUI_FontArabic24_06AD } // code 06AD, ARABIC LETTER NG
  ,{  13,  19,   0,   3,  13, acGUI_FontArabic24_06AE } // code 06AE, ARABIC LETTER KAF WITH THREE DOTS BELOW
  ,{  17,  15,   0,   1,  17, acGUI_FontArabic24_06AF } // code 06AF, ARABIC LETTER GAF
  ,{  17,  15,   0,   1,  17, acGUI_FontArabic24_06B0 } // code 06B0, ARABIC LETTER GAF WITH RING
  ,{  17,  16,   0,   0,  17, acGUI_FontArabic24_06B1 } // code 06B1, ARABIC LETTER NGOEH
  ,{  17,  19,   0,   1,  17, acGUI_FontArabic24_06B2 } // code 06B2, ARABIC LETTER GAF WITH TWO DOTS BELOW
  ,{  17,  20,   0,   1,  17, acGUI_FontArabic24_06B3 } // code 06B3, ARABIC LETTER GUEH
  ,{  17,  16,   0,   0,  17, acGUI_FontArabic24_06B4 } // code 06B4, ARABIC LETTER GAF WITH THREE DOTS ABOVE
  ,{  10,  18,   1,   1,  11, acGUI_FontArabic24_06B5 } // code 06B5, ARABIC LETTER LAM WITH SMALL V
  ,{  10,  18,   1,   1,  11, acGUI_FontArabic24_06B6 } // code 06B6, ARABIC LETTER LAM WITH DOT ABOVE
  ,{  10,  19,   1,   0,  11, acGUI_FontArabic24_06B7 } // code 06B7, ARABIC LETTER LAM WITH THREE DOTS ABOVE
  ,{  10,  20,   1,   3,  11, acGUI_FontArabic24_06B8 } // code 06B8, ARABIC LETTER LAM WITH THREE DOTS BELOW
  ,{  10,  16,   1,   7,  11, acGUI_FontArabic24_06B9 } // code 06B9, ARABIC LETTER NOON WITH DOT BELOW
  ,{  10,  11,   1,  10,  11, acGUI_FontArabic24_06BA } // code 06BA, ARABIC LETTER NOON GHUNNA
  ,{  10,  19,   1,   2,  11, acGUI_FontArabic24_06BB } // code 06BB, ARABIC LETTER RNOON
  ,{  10,  16,   1,   7,  11, acGUI_FontArabic24_06BC } // code 06BC, ARABIC LETTER NOON WITH RING
  ,{  10,  17,   1,   4,  11, acGUI_FontArabic24_06BD } // code 06BD, ARABIC LETTER NOON WITH THREE DOTS ABOVE
  ,{   9,   9,  -1,   7,   9, acGUI_FontArabic24_06BE } // code 06BE, ARABIC LETTER HEH DOACHASHMEE
  ,{  10,  17,   1,   6,  12, acGUI_FontArabic24_06BF } // code 06BF, ARABIC LETTER TCHEH WITH DOT ABOVE
  ,{   5,  12,   1,   4,   6, acGUI_FontArabic24_06C0 } // code 06C0, ARABIC LETTER HEH WITH YEH ABOVE
  ,{   8,   6,   0,  12,   8, acGUI_FontArabic24_06C1 } // code 06C1, ARABIC LETTER HEH GOAL
  ,{   8,  11,   0,   7,   8, acGUI_FontArabic24_06C2 } // code 06C2, ARABIC LETTER HEH GOAL WITH HAMZA ABOVE
  ,{   8,  10,   0,   8,   8, acGUI_FontArabic24_06C3 } // code 06C3, ARABIC LETTER TEH MARBUTA GOAL
  ,{   8,  11,   1,  10,   9, acGUI_FontArabic24_06C4 } // code 06C4, ARABIC LETTER WAW WITH RING
  ,{   8,  11,   1,  10,   9, acGUI_FontArabic24_06C5 } // code 06C5, ARABIC LETTER KIRGHIZ OE
  ,{   8,  14,   1,   7,   9, acGUI_FontArabic24_06C6 } // code 06C6, ARABIC LETTER OE
  ,{   8,  17,   1,   4,   9, acGUI_FontArabic24_06C7 } // code 06C7, ARABIC LETTER U
  ,{   8,  18,   1,   3,   9, acGUI_FontArabic24_06C8 } // code 06C8, ARABIC LETTER YU
  ,{   8,  14,   1,   7,   9, acGUI_FontArabic24_06C9 } // code 06C9, ARABIC LETTER KIRGHIZ YU
  ,{   8,  15,   1,   6,   9, acGUI_FontArabic24_06CA } // code 06CA, ARABIC LETTER WAW WITH TWO DOTS ABOVE
  ,{   8,  16,   1,   5,   9, acGUI_FontArabic24_06CB } // code 06CB, ARABIC LETTER VE
  ,{  12,  11,   1,   9,  13, acGUI_FontArabic24_06CC } // code 06CC, ARABIC LETTER FARSI YEH
  ,{  13,  11,   0,   9,  13, acGUI_FontArabic24_06CD } // code 06CD, ARABIC LETTER YEH WITH TAIL
  ,{  12,  12,   1,   8,  13, acGUI_FontArabic24_06CE } // code 06CE, ARABIC LETTER YEH WITH SMALL V
  ,{   8,  14,   1,   7,   9, acGUI_FontArabic24_06CF } // code 06CF, ARABIC LETTER WAW WITH DOT ABOVE
  ,{  12,  14,   1,   9,  13, acGUI_FontArabic24_06D0 } // code 06D0, ARABIC LETTER E
  ,{  12,  14,   1,   9,  13, acGUI_FontArabic24_06D1 } // code 06D1, ARABIC LETTER YEH WITH THREE DOTS BELOW
  ,{  16,   9,   1,  11,  17, acGUI_FontArabic24_06D2 } // code 06D2, ARABIC LETTER YEH BARREE
  ,{  16,  12,   1,   8,  17, acGUI_FontArabic24_06D3 } // code 06D3, ARABIC LETTER YEH BARREE WITH HAMZA ABOVE
  ,{   3,   2,   0,  14,   4, acGUI_FontArabic24_06D4 } // code 06D4, ARABIC FULL STOP
  ,{   5,   7,   1,   9,   6, acGUI_FontArabic24_06D5 } // code 06D5, ARABIC LETTER AE
  ,{  22,  23,   1,   0,  24, acGUI_FontArabic24_06DD } // code 06DD, ARABIC END OF AYAH
  ,{  23,  23,   0,   0,  23, acGUI_FontArabic24_06DE } // code 06DE, ARABIC START OF RUB EL HIZB
  ,{   4,   5,   0,   3,   4, acGUI_FontArabic24_06E5 } // code 06E5, ARABIC SMALL WAW
  ,{   8,   4,   0,   4,   8, acGUI_FontArabic24_06E6 } // code 06E6, ARABIC SMALL YEH
  ,{  15,  18,  -1,   1,  13, acGUI_FontArabic24_06E9 } // code 06E9, ARABIC PLACE OF SAJDAH
  ,{   3,   5,   4,   9,  11, acGUI_FontArabic24_06F0 } // code 06F0, EXTENDED ARABIC-INDIC DIGIT ZERO
  ,{   3,  12,   4,   4,  11, acGUI_FontArabic24_06F1 } // code 06F1, EXTENDED ARABIC-INDIC DIGIT ONE
  ,{   6,  12,   3,   4,  11, acGUI_FontArabic24_06F2 } // code 06F2, EXTENDED ARABIC-INDIC DIGIT TWO
  ,{   9,  12,   2,   4,  11, acGUI_FontArabic24_06F3 } // code 06F3, EXTENDED ARABIC-INDIC DIGIT THREE
  ,{   8,  12,   2,   4,  11, acGUI_FontArabic24_06F4 } // code 06F4, EXTENDED ARABIC-INDIC DIGIT FOUR
  ,{   7,  12,   2,   4,  11, acGUI_FontArabic24_06F5 } // code 06F5, EXTENDED ARABIC-INDIC DIGIT FIVE
  ,{   7,  12,   3,   4,  11, acGUI_FontArabic24_06F6 } // code 06F6, EXTENDED ARABIC-INDIC DIGIT SIX
  ,{   9,  12,   1,   4,  11, acGUI_FontArabic24_06F7 } // code 06F7, EXTENDED ARABIC-INDIC DIGIT SEVEN
  ,{   9,  12,   1,   4,  11, acGUI_FontArabic24_06F8 } // code 06F8, EXTENDED ARABIC-INDIC DIGIT EIGHT
  ,{   6,  12,   3,   4,  11, acGUI_FontArabic24_06F9 } // code 06F9, EXTENDED ARABIC-INDIC DIGIT NINE
  ,{  16,  17,   1,   4,  17, acGUI_FontArabic24_06FA } // code 06FA, ARABIC LETTER SHEEN WITH DOT BELOW
  ,{  22,  14,   1,   7,  23, acGUI_FontArabic24_06FB } // code 06FB, ARABIC LETTER DAD WITH DOT BELOW
  ,{  11,  21,   0,   2,  11, acGUI_FontArabic24_06FC } // code 06FC, ARABIC LETTER GHAIN WITH DOT BELOW
  ,{   6,  12,   1,  10,   9, acGUI_FontArabic24_06FD } // code 06FD, ARABIC SIGN SINDHI AMPERSAND
  ,{   7,  12,   0,  11,   7, acGUI_FontArabic24_06FE } // code 06FE, ARABIC SIGN SINDHI POSTPOSITION MEN
  ,{   4,  16,   0,   0,   4, acGUI_FontArabic24_FB50 } // code FB50, ARABIC LETTER ALEF WASLA ISOLATED FORM
  ,{   5,  16,   0,   0,   5, acGUI_FontArabic24_FB51 } // code FB51, ARABIC LETTER ALEF WASLA FINAL FORM
  ,{  14,  12,   1,   9,  15, acGUI_FontArabic24_FB52 } // code FB52, ARABIC LETTER BEEH ISOLATED FORM
  ,{  14,  12,   1,   9,  15, acGUI_FontArabic24_FB53 } // code FB53, ARABIC LETTER BEEH FINAL FORM
  ,{   6,  12,  -1,   9,   5, acGUI_FontArabic24_FB54 } // code FB54, ARABIC LETTER BEEH INITIAL FORM
  ,{   6,  12,  -1,   9,   5, acGUI_FontArabic24_FB55 } // code FB55, ARABIC LETTER BEEH MEDIAL FORM
  ,{  14,  13,   1,   9,  15, acGUI_FontArabic24_FB56 } // code FB56, ARABIC LETTER PEH ISOLATED FORM
  ,{  14,  13,   1,   9,  15, acGUI_FontArabic24_FB57 } // code FB57, ARABIC LETTER PEH FINAL FORM
  ,{   6,  13,  -1,   9,   5, acGUI_FontArabic24_FB58 } // code FB58, ARABIC LETTER PEH INITIAL FORM
  ,{   6,  13,  -1,   9,   5, acGUI_FontArabic24_FB59 } // code FB59, ARABIC LETTER PEH MEDIAL FORM
  ,{  14,  13,   1,   9,  15, acGUI_FontArabic24_FB5A } // code FB5A, ARABIC LETTER BEHEH ISOLATED FORM
  ,{  14,  13,   1,   9,  15, acGUI_FontArabic24_FB5B } // code FB5B, ARABIC LETTER BEHEH FINAL FORM
  ,{   6,  13,  -1,   9,   5, acGUI_FontArabic24_FB5C } // code FB5C, ARABIC LETTER BEHEH INITIAL FORM
  ,{   6,  13,  -1,   9,   5, acGUI_FontArabic24_FB5D } // code FB5D, ARABIC LETTER BEHEH MEDIAL FORM
  ,{  14,  12,   1,   4,  15, acGUI_FontArabic24_FB5E } // code FB5E, ARABIC LETTER TTEHEH ISOLATED FORM
  ,{  14,  12,   1,   4,  15, acGUI_FontArabic24_FB5F } // code FB5F, ARABIC LETTER TTEHEH FINAL FORM
  ,{   6,  12,  -1,   4,   5, acGUI_FontArabic24_FB60 } // code FB60, ARABIC LETTER TTEHEH INITIAL FORM
  ,{   6,  12,  -1,   4,   5, acGUI_FontArabic24_FB61 } // code FB61, ARABIC LETTER TTEHEH MEDIAL FORM
  ,{  14,  12,   1,   4,  15, acGUI_FontArabic24_FB62 } // code FB62, ARABIC LETTER TEHEH ISOLATED FORM
  ,{  14,  12,   1,   4,  15, acGUI_FontArabic24_FB63 } // code FB63, ARABIC LETTER TEHEH FINAL FORM
  ,{   6,  12,  -1,   4,   5, acGUI_FontArabic24_FB64 } // code FB64, ARABIC LETTER TEHEH INITIAL FORM
  ,{   6,  12,  -1,   4,   5, acGUI_FontArabic24_FB65 } // code FB65, ARABIC LETTER TEHEH MEDIAL FORM
  ,{  14,  15,   1,   1,  15, acGUI_FontArabic24_FB66 } // code FB66, ARABIC LETTER TTEH ISOLATED FORM
  ,{  14,  15,   1,   1,  15, acGUI_FontArabic24_FB67 } // code FB67, ARABIC LETTER TTEH FINAL FORM
  ,{   7,  15,  -1,   1,   5, acGUI_FontArabic24_FB68 } // code FB68, ARABIC LETTER TTEH INITIAL FORM
  ,{   7,  15,  -1,   1,   5, acGUI_FontArabic24_FB69 } // code FB69, ARABIC LETTER TTEH MEDIAL FORM
  ,{  17,  13,   0,   3,  17, acGUI_FontArabic24_FB6A } // code FB6A, ARABIC LETTER VEH ISOLATED FORM
  ,{  17,  13,   0,   3,  17, acGUI_FontArabic24_FB6B } // code FB6B, ARABIC LETTER VEH FINAL FORM
  ,{   7,  14,  -1,   2,   6, acGUI_FontArabic24_FB6C } // code FB6C, ARABIC LETTER VEH INITIAL FORM
  ,{   7,  14,  -1,   2,   6, acGUI_FontArabic24_FB6D } // code FB6D, ARABIC LETTER VEH MEDIAL FORM
  ,{  17,  13,   0,   3,  17, acGUI_FontArabic24_FB6E } // code FB6E, ARABIC LETTER PEHEH ISOLATED FORM
  ,{  17,  13,   0,   3,  17, acGUI_FontArabic24_FB6F } // code FB6F, ARABIC LETTER PEHEH FINAL FORM
  ,{   7,  15,  -1,   1,   6, acGUI_FontArabic24_FB70 } // code FB70, ARABIC LETTER PEHEH INITIAL FORM
  ,{   7,  14,  -1,   2,   6, acGUI_FontArabic24_FB71 } // code FB71, ARABIC LETTER PEHEH MEDIAL FORM
  ,{  10,  13,   1,  10,  12, acGUI_FontArabic24_FB72 } // code FB72, ARABIC LETTER DYEH ISOLATED FORM
  ,{  10,  13,   1,  10,  11, acGUI_FontArabic24_FB73 } // code FB73, ARABIC LETTER DYEH FINAL FORM
  ,{  12,  11,  -1,  10,  11, acGUI_FontArabic24_FB74 } // code FB74, ARABIC LETTER DYEH INITIAL FORM
  ,{  12,  11,  -1,  10,  11, acGUI_FontArabic24_FB75 } // code FB75, ARABIC LETTER DYEH MEDIAL FORM
  ,{  10,  13,   1,  10,  12, acGUI_FontArabic24_FB76 } // code FB76, ARABIC LETTER NYEH ISOLATED FORM
  ,{  10,  13,   1,  10,  11, acGUI_FontArabic24_FB77 } // code FB77, ARABIC LETTER NYEH FINAL FORM
  ,{  12,  10,  -1,  10,  11, acGUI_FontArabic24_FB78 } // code FB78, ARABIC LETTER NYEH INITIAL FORM
  ,{  12,  10,  -1,  10,  11, acGUI_FontArabic24_FB79 } // code FB79, ARABIC LETTER NYEH MEDIAL FORM
  ,{  10,  13,   1,  10,  12, acGUI_FontArabic24_FB7A } // code FB7A, ARABIC LETTER TCHEH ISOLATED FORM
  ,{  10,  13,   1,  10,  11, acGUI_FontArabic24_FB7B } // code FB7B, ARABIC LETTER TCHEH FINAL FORM
  ,{  12,  12,  -1,  10,  11, acGUI_FontArabic24_FB7C } // code FB7C, ARABIC LETTER TCHEH INITIAL FORM
  ,{  12,  12,  -1,  10,  11, acGUI_FontArabic24_FB7D } // code FB7D, ARABIC LETTER TCHEH MEDIAL FORM
  ,{  10,  13,   1,  10,  12, acGUI_FontArabic24_FB7E } // code FB7E, ARABIC LETTER TCHEHEH ISOLATED FORM
  ,{  10,  13,   1,  10,  11, acGUI_FontArabic24_FB7F } // code FB7F, ARABIC LETTER TCHEHEH FINAL FORM
  ,{  12,  12,  -1,  10,  11, acGUI_FontArabic24_FB80 } // code FB80, ARABIC LETTER TCHEHEH INITIAL FORM
  ,{  12,  12,  -1,  10,  11, acGUI_FontArabic24_FB81 } // code FB81, ARABIC LETTER TCHEHEH MEDIAL FORM
  ,{   6,  13,   1,   7,   7, acGUI_FontArabic24_FB82 } // code FB82, ARABIC LETTER DDAHAL ISOLATED FORM
  ,{   6,  13,   1,   7,   7, acGUI_FontArabic24_FB83 } // code FB83, ARABIC LETTER DDAHAL FINAL FORM
  ,{   6,  13,   1,   3,   7, acGUI_FontArabic24_FB84 } // code FB84, ARABIC LETTER DAHAL ISOLATED FORM
  ,{   6,  13,   1,   3,   7, acGUI_FontArabic24_FB85 } // code FB85, ARABIC LETTER DAHAL FINAL FORM
  ,{   6,  14,   1,   2,   7, acGUI_FontArabic24_FB86 } // code FB86, ARABIC LETTER DUL ISOLATED FORM
  ,{   6,  14,   1,   2,   7, acGUI_FontArabic24_FB87 } // code FB87, ARABIC LETTER DUL FINAL FORM
  ,{   6,  16,   1,   0,   7, acGUI_FontArabic24_FB88 } // code FB88, ARABIC LETTER DDAL ISOLATED FORM
  ,{   6,  16,   1,   0,   7, acGUI_FontArabic24_FB89 } // code FB89, ARABIC LETTER DDAL FINAL FORM
  ,{   9,  16,   1,   5,  10, acGUI_FontArabic24_FB8A } // code FB8A, ARABIC LETTER JEH ISOLATED FORM
  ,{   9,  16,   1,   5,  10, acGUI_FontArabic24_FB8B } // code FB8B, ARABIC LETTER JEH FINAL FORM
  ,{   9,  20,   1,   1,  10, acGUI_FontArabic24_FB8C } // code FB8C, ARABIC LETTER RREH ISOLATED FORM
  ,{   9,  20,   1,   1,  10, acGUI_FontArabic24_FB8D } // code FB8D, ARABIC LETTER RREH FINAL FORM
  ,{  17,  12,   0,   4,  17, acGUI_FontArabic24_FB8E } // code FB8E, ARABIC LETTER KEHEH ISOLATED FORM
  ,{  20,  12,   0,   4,  20, acGUI_FontArabic24_FB8F } // code FB8F, ARABIC LETTER KEHEH FINAL FORM
  ,{   9,  12,  -1,   4,   8, acGUI_FontArabic24_FB90 } // code FB90, ARABIC LETTER KEHEH INITIAL FORM
  ,{  12,  12,  -1,   4,  11, acGUI_FontArabic24_FB91 } // code FB91, ARABIC LETTER KEHEH MEDIAL FORM
  ,{  17,  15,   0,   1,  17, acGUI_FontArabic24_FB92 } // code FB92, ARABIC LETTER GAF ISOLATED FORM
  ,{  20,  15,   0,   1,  20, acGUI_FontArabic24_FB93 } // code FB93, ARABIC LETTER GAF FINAL FORM
  ,{   9,  15,  -1,   1,   8, acGUI_FontArabic24_FB94 } // code FB94, ARABIC LETTER GAF INITIAL FORM
  ,{  12,  15,  -1,   1,  11, acGUI_FontArabic24_FB95 } // code FB95, ARABIC LETTER GAF MEDIAL FORM
  ,{  17,  20,   0,   1,  17, acGUI_FontArabic24_FB96 } // code FB96, ARABIC LETTER GUEH ISOLATED FORM
  ,{  20,  20,   0,   1,  20, acGUI_FontArabic24_FB97 } // code FB97, ARABIC LETTER GUEH FINAL FORM
  ,{   9,  20,  -1,   1,   8, acGUI_FontArabic24_FB98 } // code FB98, ARABIC LETTER GUEH INITIAL FORM
  ,{  12,  20,  -1,   1,  11, acGUI_FontArabic24_FB99 } // code FB99, ARABIC LETTER GUEH MEDIAL FORM
  ,{  17,  16,   0,   0,  17, acGUI_FontArabic24_FB9A } // code FB9A, ARABIC LETTER NGOEH ISOLATED FORM
  ,{  20,  16,   0,   0,  20, acGUI_FontArabic24_FB9B } // code FB9B, ARABIC LETTER NGOEH FINAL FORM
  ,{   9,  16,  -1,   0,   8, acGUI_FontArabic24_FB9C } // code FB9C, ARABIC LETTER NGOEH INITIAL FORM
  ,{  12,  16,  -1,   0,  11, acGUI_FontArabic24_FB9D } // code FB9D, ARABIC LETTER NGOEH MEDIAL FORM
  ,{  10,  11,   1,  10,  11, acGUI_FontArabic24_FB9E } // code FB9E, ARABIC LETTER NOON GHUNNA ISOLATED FORM
  ,{  10,  11,   1,  10,  11, acGUI_FontArabic24_FB9F } // code FB9F, ARABIC LETTER NOON GHUNNA FINAL FORM
  ,{  10,  19,   1,   2,  11, acGUI_FontArabic24_FBA0 } // code FBA0, ARABIC LETTER RNOON ISOLATED FORM
  ,{  10,  19,   1,   2,  11, acGUI_FontArabic24_FBA1 } // code FBA1, ARABIC LETTER RNOON FINAL FORM
  ,{   7,  15,  -1,   1,   5, acGUI_FontArabic24_FBA2 } // code FBA2, ARABIC LETTER RNOON INITIAL FORM
  ,{   7,  15,  -1,   1,   5, acGUI_FontArabic24_FBA3 } // code FBA3, ARABIC LETTER RNOON MEDIAL FORM
  ,{   5,  12,   1,   4,   6, acGUI_FontArabic24_FBA4 } // code FBA4, ARABIC LETTER HEH WITH YEH ABOVE ISOLATED FORM
  ,{   8,  14,   0,   2,   8, acGUI_FontArabic24_FBA5 } // code FBA5, ARABIC LETTER HEH WITH YEH ABOVE FINAL FORM
  ,{   5,   7,   1,   9,   6, acGUI_FontArabic24_FBA6 } // code FBA6, ARABIC LETTER HEH GOAL ISOLATED FORM
  ,{   8,   6,   0,  12,   8, acGUI_FontArabic24_FBA7 } // code FBA7, ARABIC LETTER HEH GOAL FINAL FORM
  ,{   6,  13,  -1,   9,   5, acGUI_FontArabic24_FBA8 } // code FBA8, ARABIC LETTER HEH GOAL INITIAL FORM
  ,{   8,  12,  -1,  11,   7, acGUI_FontArabic24_FBA9 } // code FBA9, ARABIC LETTER HEH GOAL MEDIAL FORM
  ,{   9,   9,  -1,   7,   9, acGUI_FontArabic24_FBAA } // code FBAA, ARABIC LETTER HEH DOACHASHMEE ISOLATED FORM
  ,{   8,  10,   0,   6,   8, acGUI_FontArabic24_FBAB } // code FBAB, ARABIC LETTER HEH DOACHASHMEE FINAL FORM
  ,{   9,   9,  -1,   7,   9, acGUI_FontArabic24_FBAC } // code FBAC, ARABIC LETTER HEH DOACHASHMEE INITIAL FORM
  ,{   9,  12,  -1,   9,   8, acGUI_FontArabic24_FBAD } // code FBAD, ARABIC LETTER HEH DOACHASHMEE MEDIAL FORM
  ,{  16,   9,   1,  11,  17, acGUI_FontArabic24_FBAE } // code FBAE, ARABIC LETTER YEH BARREE ISOLATED FORM
  ,{  16,   9,   1,  14,  17, acGUI_FontArabic24_FBAF } // code FBAF, ARABIC LETTER YEH BARREE FINAL FORM
  ,{  16,  12,   1,   8,  17, acGUI_FontArabic24_FBB0 } // code FBB0, ARABIC LETTER YEH BARREE WITH HAMZA ABOVE ISOLATED FORM
  ,{  16,  14,   1,   9,  17, acGUI_FontArabic24_FBB1 } // code FBB1, ARABIC LETTER YEH BARREE WITH HAMZA ABOVE FINAL FORM
  ,{  13,  15,   0,   1,  13, acGUI_FontArabic24_FBD3 } // code FBD3, ARABIC LETTER NG ISOLATED FORM
  ,{  13,  15,   0,   1,  13, acGUI_FontArabic24_FBD4 } // code FBD4, ARABIC LETTER NG FINAL FORM
  ,{   9,  14,  -1,   2,   8, acGUI_FontArabic24_FBD5 } // code FBD5, ARABIC LETTER NG INITIAL FORM
  ,{   9,  14,  -1,   2,   8, acGUI_FontArabic24_FBD6 } // code FBD6, ARABIC LETTER NG MEDIAL FORM
  ,{   8,  17,   1,   4,   9, acGUI_FontArabic24_FBD7 } // code FBD7, ARABIC LETTER U ISOLATED FORM
  ,{   8,  17,   1,   4,   9, acGUI_FontArabic24_FBD8 } // code FBD8, ARABIC LETTER U FINAL FORM
  ,{   8,  14,   1,   7,   9, acGUI_FontArabic24_FBD9 } // code FBD9, ARABIC LETTER OE ISOLATED FORM
  ,{   8,  14,   1,   7,   9, acGUI_FontArabic24_FBDA } // code FBDA, ARABIC LETTER OE FINAL FORM
  ,{   8,  18,   1,   3,   9, acGUI_FontArabic24_FBDB } // code FBDB, ARABIC LETTER YU ISOLATED FORM
  ,{   8,  18,   1,   3,   9, acGUI_FontArabic24_FBDC } // code FBDC, ARABIC LETTER YU FINAL FORM
  ,{   9,  16,   1,   5,   9, acGUI_FontArabic24_FBDD } // code FBDD, ARABIC LETTER U WITH HAMZA ABOVE ISOLATED FORM
  ,{   8,  16,   1,   5,   9, acGUI_FontArabic24_FBDE } // code FBDE, ARABIC LETTER VE ISOLATED FORM
  ,{   8,  16,   1,   5,   9, acGUI_FontArabic24_FBDF } // code FBDF, ARABIC LETTER VE FINAL FORM
  ,{   8,  11,   1,  10,   9, acGUI_FontArabic24_FBE0 } // code FBE0, ARABIC LETTER KIRGHIZ OE ISOLATED FORM
  ,{   8,  11,   1,  10,   9, acGUI_FontArabic24_FBE1 } // code FBE1, ARABIC LETTER KIRGHIZ OE FINAL FORM
  ,{   8,  14,   1,   7,   9, acGUI_FontArabic24_FBE2 } // code FBE2, ARABIC LETTER KIRGHIZ YU ISOLATED FORM
  ,{   8,  14,   1,   7,   9, acGUI_FontArabic24_FBE3 } // code FBE3, ARABIC LETTER KIRGHIZ YU FINAL FORM
  ,{  12,  14,   1,   9,  13, acGUI_FontArabic24_FBE4 } // code FBE4, ARABIC LETTER E ISOLATED FORM
  ,{  12,  10,   0,  13,  12, acGUI_FontArabic24_FBE5 } // code FBE5, ARABIC LETTER E FINAL FORM
  ,{   6,  12,  -1,   9,   5, acGUI_FontArabic24_FBE6 } // code FBE6, ARABIC LETTER E INITIAL FORM
  ,{   6,  12,  -1,   9,   5, acGUI_FontArabic24_FBE7 } // code FBE7, ARABIC LETTER E MEDIAL FORM
  ,{  12,  11,   1,   9,  13, acGUI_FontArabic24_FBFC } // code FBFC, ARABIC LETTER FARSI YEH ISOLATED FORM
  ,{  12,   8,   0,  13,  12, acGUI_FontArabic24_FBFD } // code FBFD, ARABIC LETTER FARSI YEH FINAL FORM
  ,{   6,  11,  -1,   9,   5, acGUI_FontArabic24_FBFE } // code FBFE, ARABIC LETTER FARSI YEH INITIAL FORM
  ,{   6,  11,  -1,   9,   5, acGUI_FontArabic24_FBFF } // code FBFF, ARABIC LETTER FARSI YEH MEDIAL FORM
  ,{   6,   6,   0,   0,   5, acGUI_FontArabic24_FC5E } // code FC5E, ARABIC LIGATURE SHADDA WITH DAMMATAN ISOLATED FORM
  ,{   5,   6,   0,   0,   4, acGUI_FontArabic24_FC5F } // code FC5F, ARABIC LIGATURE SHADDA WITH KASRATAN ISOLATED FORM
  ,{   5,   6,   0,   0,   4, acGUI_FontArabic24_FC60 } // code FC60, ARABIC LIGATURE SHADDA WITH FATHA ISOLATED FORM
  ,{   6,   6,  -1,   0,   4, acGUI_FontArabic24_FC61 } // code FC61, ARABIC LIGATURE SHADDA WITH DAMMA ISOLATED FORM
  ,{   5,   5,   0,   1,   4, acGUI_FontArabic24_FC62 } // code FC62, ARABIC LIGATURE SHADDA WITH KASRA ISOLATED FORM
  ,{   4,  20,   1,   3,   7, acGUI_FontArabic24_FD3E } // code FD3E, ORNATE LEFT PARENTHESIS
  ,{   4,  20,   2,   3,   7, acGUI_FontArabic24_FD3F } // code FD3F, ORNATE RIGHT PARENTHESIS
  ,{  13,  13,   0,   3,  13, acGUI_FontArabic24_FDF2 } // code FDF2, ARABIC LIGATURE ALLAH ISOLATED FORM
  ,{   6,   8,   1,  10,   9, acGUI_FontArabic24_FE80 } // code FE80, ARABIC LETTER HAMZA ISOLATED FORM
  ,{   4,  14,   0,   2,   4, acGUI_FontArabic24_FE81 } // code FE81, ARABIC LETTER ALEF WITH MADDA ABOVE ISOLATED FORM
  ,{   6,  14,  -1,   2,   5, acGUI_FontArabic24_FE82 } // code FE82, ARABIC LETTER ALEF WITH MADDA ABOVE FINAL FORM
  ,{   3,  15,   1,   1,   4, acGUI_FontArabic24_FE83 } // code FE83, ARABIC LETTER ALEF WITH HAMZA ABOVE ISOLATED FORM
  ,{   5,  15,   0,   1,   5, acGUI_FontArabic24_FE84 } // code FE84, ARABIC LETTER ALEF WITH HAMZA ABOVE FINAL FORM
  ,{   8,  17,   1,   4,   9, acGUI_FontArabic24_FE85 } // code FE85, ARABIC LETTER WAW WITH HAMZA ABOVE ISOLATED FORM
  ,{   8,  17,   1,   4,   9, acGUI_FontArabic24_FE86 } // code FE86, ARABIC LETTER WAW WITH HAMZA ABOVE FINAL FORM
  ,{   3,  17,   0,   4,   4, acGUI_FontArabic24_FE87 } // code FE87, ARABIC LETTER ALEF WITH HAMZA BELOW ISOLATED FORM
  ,{   5,  17,   0,   4,   5, acGUI_FontArabic24_FE88 } // code FE88, ARABIC LETTER ALEF WITH HAMZA BELOW FINAL FORM
  ,{  12,  13,   1,   7,  13, acGUI_FontArabic24_FE89 } // code FE89, ARABIC LETTER YEH WITH HAMZA ABOVE ISOLATED FORM
  ,{  12,  14,   0,   7,  12, acGUI_FontArabic24_FE8A } // code FE8A, ARABIC LETTER YEH WITH HAMZA ABOVE FINAL FORM
  ,{   6,  12,  -1,   4,   5, acGUI_FontArabic24_FE8B } // code FE8B, ARABIC LETTER YEH WITH HAMZA ABOVE INITIAL FORM
  ,{   6,  12,  -1,   4,   5, acGUI_FontArabic24_FE8C } // code FE8C, ARABIC LETTER YEH WITH HAMZA ABOVE MEDIAL FORM
  ,{   2,  12,   1,   4,   4, acGUI_FontArabic24_FE8D } // code FE8D, ARABIC LETTER ALEF ISOLATED FORM
  ,{   5,  12,   0,   4,   5, acGUI_FontArabic24_FE8E } // code FE8E, ARABIC LETTER ALEF FINAL FORM
  ,{  14,  11,   1,   9,  15, acGUI_FontArabic24_FE8F } // code FE8F, ARABIC LETTER BEH ISOLATED FORM
  ,{  14,  11,   1,   9,  15, acGUI_FontArabic24_FE90 } // code FE90, ARABIC LETTER BEH FINAL FORM
  ,{   6,  11,  -1,   9,   5, acGUI_FontArabic24_FE91 } // code FE91, ARABIC LETTER BEH INITIAL FORM
  ,{   6,  11,  -1,   9,   5, acGUI_FontArabic24_FE92 } // code FE92, ARABIC LETTER BEH MEDIAL FORM
  ,{   5,  11,   1,   5,   6, acGUI_FontArabic24_FE93 } // code FE93, ARABIC LETTER TEH MARBUTA ISOLATED FORM
  ,{   8,  14,   0,   2,   8, acGUI_FontArabic24_FE94 } // code FE94, ARABIC LETTER TEH MARBUTA FINAL FORM
  ,{  14,  10,   1,   6,  15, acGUI_FontArabic24_FE95 } // code FE95, ARABIC LETTER TEH ISOLATED FORM
  ,{  14,  10,   1,   6,  15, acGUI_FontArabic24_FE96 } // code FE96, ARABIC LETTER TEH FINAL FORM
  ,{   6,  11,  -1,   5,   5, acGUI_FontArabic24_FE97 } // code FE97, ARABIC LETTER TEH INITIAL FORM
  ,{   6,  11,  -1,   5,   5, acGUI_FontArabic24_FE98 } // code FE98, ARABIC LETTER TEH MEDIAL FORM
  ,{  14,  11,   1,   5,  15, acGUI_FontArabic24_FE99 } // code FE99, ARABIC LETTER THEH ISOLATED FORM
  ,{  14,  11,   1,   5,  15, acGUI_FontArabic24_FE9A } // code FE9A, ARABIC LETTER THEH FINAL FORM
  ,{   6,  12,  -1,   4,   5, acGUI_FontArabic24_FE9B } // code FE9B, ARABIC LETTER THEH INITIAL FORM
  ,{   6,  12,  -1,   4,   5, acGUI_FontArabic24_FE9C } // code FE9C, ARABIC LETTER THEH MEDIAL FORM
  ,{  10,  13,   1,  10,  12, acGUI_FontArabic24_FE9D } // code FE9D, ARABIC LETTER JEEM ISOLATED FORM
  ,{  10,  13,   1,  10,  11, acGUI_FontArabic24_FE9E } // code FE9E, ARABIC LETTER JEEM FINAL FORM
  ,{  12,   9,  -1,  10,  11, acGUI_FontArabic24_FE9F } // code FE9F, ARABIC LETTER JEEM INITIAL FORM
  ,{  12,   9,  -1,  10,  11, acGUI_FontArabic24_FEA0 } // code FEA0, ARABIC LETTER JEEM MEDIAL FORM
  ,{  10,  13,   1,  10,  12, acGUI_FontArabic24_FEA1 } // code FEA1, ARABIC LETTER HAH ISOLATED FORM
  ,{  10,  13,   1,  10,  11, acGUI_FontArabic24_FEA2 } // code FEA2, ARABIC LETTER HAH FINAL FORM
  ,{  12,   6,  -1,  10,  11, acGUI_FontArabic24_FEA3 } // code FEA3, ARABIC LETTER HAH INITIAL FORM
  ,{  12,   6,  -1,  10,  11, acGUI_FontArabic24_FEA4 } // code FEA4, ARABIC LETTER HAH MEDIAL FORM
  ,{  10,  17,   1,   6,  12, acGUI_FontArabic24_FEA5 } // code FEA5, ARABIC LETTER KHAH ISOLATED FORM
  ,{  10,  17,   1,   6,  11, acGUI_FontArabic24_FEA6 } // code FEA6, ARABIC LETTER KHAH FINAL FORM
  ,{  12,  10,  -1,   6,  11, acGUI_FontArabic24_FEA7 } // code FEA7, ARABIC LETTER KHAH INITIAL FORM
  ,{  12,  10,  -1,   6,  11, acGUI_FontArabic24_FEA8 } // code FEA8, ARABIC LETTER KHAH MEDIAL FORM
  ,{   6,   9,   1,   7,   7, acGUI_FontArabic24_FEA9 } // code FEA9, ARABIC LETTER DAL ISOLATED FORM
  ,{   6,   9,   1,   7,   7, acGUI_FontArabic24_FEAA } // code FEAA, ARABIC LETTER DAL FINAL FORM
  ,{   6,  13,   1,   3,   7, acGUI_FontArabic24_FEAB } // code FEAB, ARABIC LETTER THAL ISOLATED FORM
  ,{   6,  13,   1,   3,   7, acGUI_FontArabic24_FEAC } // code FEAC, ARABIC LETTER THAL FINAL FORM
  ,{   9,  11,   1,  10,  10, acGUI_FontArabic24_FEAD } // code FEAD, ARABIC LETTER REH ISOLATED FORM
  ,{   9,  11,   1,  10,  10, acGUI_FontArabic24_FEAE } // code FEAE, ARABIC LETTER REH FINAL FORM
  ,{   9,  15,   1,   6,  10, acGUI_FontArabic24_FEAF } // code FEAF, ARABIC LETTER ZAIN ISOLATED FORM
  ,{   9,  15,   1,   6,  10, acGUI_FontArabic24_FEB0 } // code FEB0, ARABIC LETTER ZAIN FINAL FORM
  ,{  16,  11,   1,  10,  17, acGUI_FontArabic24_FEB1 } // code FEB1, ARABIC LETTER SEEN ISOLATED FORM
  ,{  16,  11,   1,  10,  17, acGUI_FontArabic24_FEB2 } // code FEB2, ARABIC LETTER SEEN FINAL FORM
  ,{  12,   6,  -1,  10,  11, acGUI_FontArabic24_FEB3 } // code FEB3, ARABIC LETTER SEEN INITIAL FORM
  ,{  12,   6,  -1,  10,  11, acGUI_FontArabic24_FEB4 } // code FEB4, ARABIC LETTER SEEN MEDIAL FORM
  ,{  16,  16,   1,   5,  17, acGUI_FontArabic24_FEB5 } // code FEB5, ARABIC LETTER SHEEN ISOLATED FORM
  ,{  16,  16,   1,   5,  17, acGUI_FontArabic24_FEB6 } // code FEB6, ARABIC LETTER SHEEN FINAL FORM
  ,{  12,  11,  -1,   5,  11, acGUI_FontArabic24_FEB7 } // code FEB7, ARABIC LETTER SHEEN INITIAL FORM
  ,{  12,  11,  -1,   5,  11, acGUI_FontArabic24_FEB8 } // code FEB8, ARABIC LETTER SHEEN MEDIAL FORM
  ,{  22,  11,   1,  10,  23, acGUI_FontArabic24_FEB9 } // code FEB9, ARABIC LETTER SAD ISOLATED FORM
  ,{  22,  11,   1,  10,  23, acGUI_FontArabic24_FEBA } // code FEBA, ARABIC LETTER SAD FINAL FORM
  ,{  19,   6,  -1,  10,  18, acGUI_FontArabic24_FEBB } // code FEBB, ARABIC LETTER SAD INITIAL FORM
  ,{  19,   6,  -1,  10,  18, acGUI_FontArabic24_FEBC } // code FEBC, ARABIC LETTER SAD MEDIAL FORM
  ,{  22,  14,   1,   7,  23, acGUI_FontArabic24_FEBD } // code FEBD, ARABIC LETTER DAD ISOLATED FORM
  ,{  22,  14,   1,   7,  23, acGUI_FontArabic24_FEBE } // code FEBE, ARABIC LETTER DAD FINAL FORM
  ,{  19,  10,  -1,   6,  18, acGUI_FontArabic24_FEBF } // code FEBF, ARABIC LETTER DAD INITIAL FORM
  ,{  19,  10,  -1,   6,  18, acGUI_FontArabic24_FEC0 } // code FEC0, ARABIC LETTER DAD MEDIAL FORM
  ,{  13,  13,  -1,   3,  12, acGUI_FontArabic24_FEC1 } // code FEC1, ARABIC LETTER TAH ISOLATED FORM
  ,{  13,  13,  -1,   3,  12, acGUI_FontArabic24_FEC2 } // code FEC2, ARABIC LETTER TAH FINAL FORM
  ,{  13,  13,  -1,   3,  12, acGUI_FontArabic24_FEC3 } // code FEC3, ARABIC LETTER TAH INITIAL FORM
  ,{  13,  13,  -1,   3,  12, acGUI_FontArabic24_FEC4 } // code FEC4, ARABIC LETTER TAH MEDIAL FORM
  ,{  13,  13,  -1,   3,  12, acGUI_FontArabic24_FEC5 } // code FEC5, ARABIC LETTER ZAH ISOLATED FORM
  ,{  13,  13,  -1,   3,  12, acGUI_FontArabic24_FEC6 } // code FEC6, ARABIC LETTER ZAH FINAL FORM
  ,{  13,  13,  -1,   3,  12, acGUI_FontArabic24_FEC7 } // code FEC7, ARABIC LETTER ZAH INITIAL FORM
  ,{  13,  13,  -1,   3,  12, acGUI_FontArabic24_FEC8 } // code FEC8, ARABIC LETTER ZAH MEDIAL FORM
  ,{  11,  17,   0,   6,  11, acGUI_FontArabic24_FEC9 } // code FEC9, ARABIC LETTER AIN ISOLATED FORM
  ,{   9,  13,   1,  10,   9, acGUI_FontArabic24_FECA } // code FECA, ARABIC LETTER AIN FINAL FORM
  ,{  11,   7,  -1,   9,  11, acGUI_FontArabic24_FECB } // code FECB, ARABIC LETTER AIN INITIAL FORM
  ,{   9,   6,  -1,  10,   8, acGUI_FontArabic24_FECC } // code FECC, ARABIC LETTER AIN MEDIAL FORM
  ,{  11,  21,   0,   2,  11, acGUI_FontArabic24_FECD } // code FECD, ARABIC LETTER GHAIN ISOLATED FORM
  ,{   9,  17,   1,   6,   9, acGUI_FontArabic24_FECE } // code FECE, ARABIC LETTER GHAIN FINAL FORM
  ,{  11,  10,  -1,   6,  11, acGUI_FontArabic24_FECF } // code FECF, ARABIC LETTER GHAIN INITIAL FORM
  ,{   9,  10,  -1,   6,   8, acGUI_FontArabic24_FED0 } // code FED0, ARABIC LETTER GHAIN MEDIAL FORM
  ,{  17,  11,   0,   5,  17, acGUI_FontArabic24_FED1 } // code FED1, ARABIC LETTER FEH ISOLATED FORM
  ,{  17,  11,   0,   5,  17, acGUI_FontArabic24_FED2 } // code FED2, ARABIC LETTER FEH FINAL FORM
  ,{   7,  12,  -1,   4,   6, acGUI_FontArabic24_FED3 } // code FED3, ARABIC LETTER FEH INITIAL FORM
  ,{   7,  12,  -1,   4,   6, acGUI_FontArabic24_FED4 } // code FED4, ARABIC LETTER FEH MEDIAL FORM
  ,{  11,  17,   1,   4,  12, acGUI_FontArabic24_FED5 } // code FED5, ARABIC LETTER QAF ISOLATED FORM
  ,{  11,  17,   1,   4,  12, acGUI_FontArabic24_FED6 } // code FED6, ARABIC LETTER QAF FINAL FORM
  ,{   7,  13,  -1,   3,   6, acGUI_FontArabic24_FED7 } // code FED7, ARABIC LETTER QAF INITIAL FORM
  ,{   7,  13,  -1,   3,   6, acGUI_FontArabic24_FED8 } // code FED8, ARABIC LETTER QAF MEDIAL FORM
  ,{  13,  13,   0,   3,  13, acGUI_FontArabic24_FED9 } // code FED9, ARABIC LETTER KAF ISOLATED FORM
  ,{  13,  13,   0,   3,  13, acGUI_FontArabic24_FEDA } // code FEDA, ARABIC LETTER KAF FINAL FORM
  ,{   9,  12,  -1,   4,   8, acGUI_FontArabic24_FEDB } // code FEDB, ARABIC LETTER KAF INITIAL FORM
  ,{   9,  12,  -1,   4,   8, acGUI_FontArabic24_FEDC } // code FEDC, ARABIC LETTER KAF MEDIAL FORM
  ,{  10,  16,   1,   3,  11, acGUI_FontArabic24_FEDD } // code FEDD, ARABIC LETTER LAM ISOLATED FORM
  ,{  10,  16,   1,   3,  11, acGUI_FontArabic24_FEDE } // code FEDE, ARABIC LETTER LAM FINAL FORM
  ,{   5,  13,  -1,   3,   4, acGUI_FontArabic24_FEDF } // code FEDF, ARABIC LETTER LAM INITIAL FORM
  ,{   5,  13,  -1,   3,   4, acGUI_FontArabic24_FEE0 } // code FEE0, ARABIC LETTER LAM MEDIAL FORM
  ,{   7,  12,   0,  11,   7, acGUI_FontArabic24_FEE1 } // code FEE1, ARABIC LETTER MEEM ISOLATED FORM
  ,{   7,  12,   0,  11,   7, acGUI_FontArabic24_FEE2 } // code FEE2, ARABIC LETTER MEEM FINAL FORM
  ,{   9,   5,  -1,  11,   8, acGUI_FontArabic24_FEE3 } // code FEE3, ARABIC LETTER MEEM INITIAL FORM
  ,{   9,   5,  -1,  11,   8, acGUI_FontArabic24_FEE4 } // code FEE4, ARABIC LETTER MEEM MEDIAL FORM
  ,{  10,  14,   1,   7,  11, acGUI_FontArabic24_FEE5 } // code FEE5, ARABIC LETTER NOON ISOLATED FORM
  ,{  10,  14,   1,   7,  11, acGUI_FontArabic24_FEE6 } // code FEE6, ARABIC LETTER NOON FINAL FORM
  ,{   6,  10,  -1,   6,   5, acGUI_FontArabic24_FEE7 } // code FEE7, ARABIC LETTER NOON INITIAL FORM
  ,{   6,  10,  -1,   6,   5, acGUI_FontArabic24_FEE8 } // code FEE8, ARABIC LETTER NOON MEDIAL FORM
  ,{   5,   7,   1,   9,   6, acGUI_FontArabic24_FEE9 } // code FEE9, ARABIC LETTER HEH ISOLATED FORM
  ,{   8,  10,   0,   6,   8, acGUI_FontArabic24_FEEA } // code FEEA, ARABIC LETTER HEH FINAL FORM
  ,{   9,   9,  -1,   7,   9, acGUI_FontArabic24_FEEB } // code FEEB, ARABIC LETTER HEH INITIAL FORM
  ,{   9,  12,  -1,   9,   8, acGUI_FontArabic24_FEEC } // code FEEC, ARABIC LETTER HEH MEDIAL FORM
  ,{   8,  11,   1,  10,   9, acGUI_FontArabic24_FEED } // code FEED, ARABIC LETTER WAW ISOLATED FORM
  ,{   8,  11,   1,  10,   9, acGUI_FontArabic24_FEEE } // code FEEE, ARABIC LETTER WAW FINAL FORM
  ,{  12,  11,   1,   9,  13, acGUI_FontArabic24_FEEF } // code FEEF, ARABIC LETTER ALEF MAKSURA ISOLATED FORM
  ,{  12,   8,   0,  13,  12, acGUI_FontArabic24_FEF0 } // code FEF0, ARABIC LETTER ALEF MAKSURA FINAL FORM
  ,{  12,  14,   1,   9,  13, acGUI_FontArabic24_FEF1 } // code FEF1, ARABIC LETTER YEH ISOLATED FORM
  ,{  12,  10,   0,  13,  12, acGUI_FontArabic24_FEF2 } // code FEF2, ARABIC LETTER YEH FINAL FORM
  ,{   6,  11,  -1,   9,   5, acGUI_FontArabic24_FEF3 } // code FEF3, ARABIC LETTER YEH INITIAL FORM
  ,{   6,  11,  -1,   9,   5, acGUI_FontArabic24_FEF4 } // code FEF4, ARABIC LETTER YEH MEDIAL FORM
  ,{   9,  16,   1,   2,  11, acGUI_FontArabic24_FEF5 } // code FEF5, ARABIC LIGATURE LAM WITH ALEF WITH MADDA ABOVE ISOLATED FORM
  ,{  12,  15,   1,   2,  13, acGUI_FontArabic24_FEF6 } // code FEF6, ARABIC LIGATURE LAM WITH ALEF WITH MADDA ABOVE FINAL FORM
  ,{  10,  17,   0,   1,  11, acGUI_FontArabic24_FEF7 } // code FEF7, ARABIC LIGATURE LAM WITH ALEF WITH HAMZA ABOVE ISOLATED FORM
  ,{  13,  16,   0,   1,  13, acGUI_FontArabic24_FEF8 } // code FEF8, ARABIC LIGATURE LAM WITH ALEF WITH HAMZA ABOVE FINAL FORM
  ,{   9,  19,   1,   4,  11, acGUI_FontArabic24_FEF9 } // code FEF9, ARABIC LIGATURE LAM WITH ALEF WITH HAMZA BELOW ISOLATED FORM
  ,{  12,  18,   1,   4,  13, acGUI_FontArabic24_FEFA } // code FEFA, ARABIC LIGATURE LAM WITH ALEF WITH HAMZA BELOW FINAL FORM
  ,{   9,  14,   1,   4,  11, acGUI_FontArabic24_FEFB } // code FEFB, ARABIC LIGATURE LAM WITH ALEF ISOLATED FORM
  ,{  12,  13,   1,   4,  13, acGUI_FontArabic24_FEFC } // code FEFC, ARABIC LIGATURE LAM WITH ALEF FINAL FORM
  ,{  10,  13,   3,   6,  16, acGUI_FontArabic24_FFFF } // code FFFF
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop23 = {
   0xFFFF                                   // First character
  ,0xFFFF                                   // Last character
  ,&GUI_FontArabic24_CharInfo[591]          // Address of first character
  ,(GUI_CONST_STORAGE GUI_FONT_PROP_EXT *)0 // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop22 = {
   0xFE80                          // First character
  ,0xFEFC                          // Last character
  ,&GUI_FontArabic24_CharInfo[466] // Address of first character
  ,&GUI_FontArabic24_Prop23        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop21 = {
   0xFDF2                          // First character
  ,0xFDF2                          // Last character
  ,&GUI_FontArabic24_CharInfo[465] // Address of first character
  ,&GUI_FontArabic24_Prop22        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop20 = {
   0xFD3E                          // First character
  ,0xFD3F                          // Last character
  ,&GUI_FontArabic24_CharInfo[463] // Address of first character
  ,&GUI_FontArabic24_Prop21        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop19 = {
   0xFC5E                          // First character
  ,0xFC62                          // Last character
  ,&GUI_FontArabic24_CharInfo[458] // Address of first character
  ,&GUI_FontArabic24_Prop20        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop18 = {
   0xFBFC                          // First character
  ,0xFBFF                          // Last character
  ,&GUI_FontArabic24_CharInfo[454] // Address of first character
  ,&GUI_FontArabic24_Prop19        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop17 = {
   0xFBD3                          // First character
  ,0xFBE7                          // Last character
  ,&GUI_FontArabic24_CharInfo[433] // Address of first character
  ,&GUI_FontArabic24_Prop18        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop16 = {
   0xFB50                          // First character
  ,0xFBB1                          // Last character
  ,&GUI_FontArabic24_CharInfo[335] // Address of first character
  ,&GUI_FontArabic24_Prop17        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop15 = {
   0x06F0                          // First character
  ,0x06FE                          // Last character
  ,&GUI_FontArabic24_CharInfo[320] // Address of first character
  ,&GUI_FontArabic24_Prop16        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop14 = {
   0x06E9                          // First character
  ,0x06E9                          // Last character
  ,&GUI_FontArabic24_CharInfo[319] // Address of first character
  ,&GUI_FontArabic24_Prop15        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop13 = {
   0x06E5                          // First character
  ,0x06E6                          // Last character
  ,&GUI_FontArabic24_CharInfo[317] // Address of first character
  ,&GUI_FontArabic24_Prop14        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop12 = {
   0x06DD                          // First character
  ,0x06DE                          // Last character
  ,&GUI_FontArabic24_CharInfo[315] // Address of first character
  ,&GUI_FontArabic24_Prop13        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop11 = {
   0x0671                          // First character
  ,0x06D5                          // Last character
  ,&GUI_FontArabic24_CharInfo[214] // Address of first character
  ,&GUI_FontArabic24_Prop12        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop10 = {
   0x0660                          // First character
  ,0x066F                          // Last character
  ,&GUI_FontArabic24_CharInfo[198] // Address of first character
  ,&GUI_FontArabic24_Prop11        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop9 = {
   0x0640                          // First character
  ,0x0655                          // Last character
  ,&GUI_FontArabic24_CharInfo[176] // Address of first character
  ,&GUI_FontArabic24_Prop10        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop8 = {
   0x0621                          // First character
  ,0x063A                          // Last character
  ,&GUI_FontArabic24_CharInfo[150] // Address of first character
  ,&GUI_FontArabic24_Prop9        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop7 = {
   0x061F                          // First character
  ,0x061F                          // Last character
  ,&GUI_FontArabic24_CharInfo[149] // Address of first character
  ,&GUI_FontArabic24_Prop8         // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop6 = {
   0x061B                          // First character
  ,0x061B                          // Last character
  ,&GUI_FontArabic24_CharInfo[148] // Address of first character
  ,&GUI_FontArabic24_Prop7        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop5 = {
   0x060C                          // First character
  ,0x060C                          // Last character
  ,&GUI_FontArabic24_CharInfo[147] // Address of first character
  ,&GUI_FontArabic24_Prop6         // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop4 = {
   0x05F0                          // First character
  ,0x05F4                          // Last character
  ,&GUI_FontArabic24_CharInfo[142] // Address of first character
  ,&GUI_FontArabic24_Prop5         // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop3 = {
   0x05D0                          // First character
  ,0x05EA                          // Last character
  ,&GUI_FontArabic24_CharInfo[115] // Address of first character
  ,&GUI_FontArabic24_Prop4        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop2 = {
   0x05B0                          // First character
  ,0x05C3                          // Last character
  ,&GUI_FontArabic24_CharInfo[ 95] // Address of first character
  ,&GUI_FontArabic24_Prop3         // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontArabic24_Prop1 = {
   0x0020                          // First character
  ,0x007E                          // Last character
  ,&GUI_FontArabic24_CharInfo[  0] // Address of first character
  ,&GUI_FontArabic24_Prop2         // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT GUI_FontArabic24 = {
   GUI_FONTTYPE_PROP_EXT // type of font   
  ,24                    // height of font 
  ,24                    // space of font y
  ,1                     // magnification x
  ,1                     // magnification y
  ,{&GUI_FontArabic24_Prop1}
  ,19                    // Baseline
  ,11                    // Height of lowercase characters
  ,15                    // Height of capital characters
};

/*******************************************************************
*
*       Arabic and bidirectional text samples
*/
static char * _apText[] = {
  "\nBidirectional text\n\n\xd8\xb9\xd9\x84\xd8\xa7 1, 2, 345 \xd8\xba\xd9\x86\xd9\x8a XYZ \xd8\xa3\xd9\x86\xd8\xa7",
  "\nBeautiful\n\n\xd8\xac\xd9\x80\xd9\x85\xd9\x8a\xd9\x84",
  "\nI'm from Lebanon.\n\n\xd8\xa3\xd9\x86\xd8\xa7 \xd9\x85\xd9\x86 \xd9\x84\xd8\xa8\xd9\x86\xd8\xa7\xd9\x86",
  "\nI'm from Canada.\n\n\xd8\xa3\xd9\x86\xd8\xa7 \xd9\x85\xd9\x86 \xd9\x83\xd9\x86\xd8\xaf\xd8\xa7",
  "\nIsn't it like that?\n\n\xd8\xa3\xd9\x84\xd9\x8a\xd8\xb3 \xd9\x83\xd8\xb0\xd8\xa7\xd9\x84\xd9\x83\xd8\x9f",
  "\nDo you work?\n\n\xd9\x87\xd9\x84 \xd8\xaa\xd8\xb9\xd9\x85\xd9\x84\xd8\x9f",
  "\nThe book is heavy.\n\n\xd8\xa7\xd9\x84\xd9\x83\xd8\xaa\xd8\xa7\xd8\xa8 \xd8\xab\xd9\x82\xd9\x8a\xd9\x84",
};

/********************************************************************
*
*       Static code
*
*********************************************************************
*/
/*******************************************************************
*
*       _ShowArabicTextSamples
*/
static void _ShowArabicTextSamples(void) {
  GUI_RECT Rect = {40, 60, 279, 199};

  GUI_SetFont(&GUI_FontArabic24); // Set Arabic font
  while (1) {
    unsigned i;

    GUI_SetColor(GUI_RED);
    GUI_DrawRect(Rect.x0 - 1, Rect.y0 - 1, Rect.x1 + 1, Rect.y1 + 1);
    GUI_SetColor(GUI_WHITE);
    for (i = 0; i < GUI_COUNTOF(_apText); i++) {
      GUI_DispStringInRectWrap(_apText[i], &Rect, GUI_TA_HCENTER, GUI_WRAPMODE_WORD);
      GUI_Delay(2000);
      GUI_ClearRectEx(&Rect);
    }
  }
}

/********************************************************************
*
*       Public code
*
*********************************************************************
*/
/********************************************************************
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
  GUI_UC_SetEncodeUTF8(); // Enable UTF8 decoding
  GUI_UC_EnableBIDI(1);   // Enable bidirectional text
  //
  // Lable the sample
  //
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("Arabic language sample", 160, 5);
  //
  // Call demo loop
  //
  _ShowArabicTextSamples();
}

/*************************** End of file ****************************/
