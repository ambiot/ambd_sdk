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
File        : FONT_ThaiText.c
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
*       Thai font
*/
//
// Start of unicode area <Basic Latin>
//
GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0020[  1] = { // Code 0020, SPACE
  ________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0021[ 11] = { // Code 0021, EXCLAMATION MARK
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  ________,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0022[  4] = { // Code 0022, QUOTATION MARK
  X_X_____,
  X_X_____,
  X_X_____,
  X_X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0023[ 11] = { // Code 0023, NUMBER SIGN
  ___X__X_,
  ___X__X_,
  ___X__X_,
  XXXXXXXX,
  __X__X__,
  __X__X__,
  __X__X__,
  XXXXXXXX,
  _X__X___,
  _X__X___,
  _X__X___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0024[ 13] = { // Code 0024, DOLLAR SIGN
  ___X____,
  _XXXX___,
  X__X_X__,
  X__X_X__,
  X__X____,
  _X_X____,
  __XXX___,
  ___X_X__,
  ___X_X__,
  X__X_X__,
  X__X_X__,
  _XXXX___,
  ___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0025[ 22] = { // Code 0025, PERCENT SIGN
  _XX____X,________,
  X__X__X_,________,
  X__X__X_,________,
  X__X_X__,________,
  X__X_X__,________,
  _XX_X__X,X_______,
  ____X_X_,_X______,
  ____X_X_,_X______,
  ___X__X_,_X______,
  ___X__X_,_X______,
  __X____X,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0026[ 22] = { // Code 0026, AMPERSAND
  __XXX___,________,
  _X___X__,________,
  _X___X__,________,
  _X___X__,________,
  __X_X___,________,
  _XXX____,________,
  X___X__X,________,
  X____XX_,________,
  X_____X_,________,
  _X___X_X,________,
  __XXX___,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0027[  4] = { // Code 0027, APOSTROPHE
  X_______,
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0028[ 14] = { // Code 0028, LEFT PARENTHESIS
  __X_____,
  _X______,
  _X______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  _X______,
  _X______,
  __X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0029[ 14] = { // Code 0029, RIGHT PARENTHESIS
  X_______,
  _X______,
  _X______,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  _X______,
  _X______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_002A[  4] = { // Code 002A, ASTERISK
  __X_____,
  XXXXX___,
  __X_____,
  _X_X____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_002B[ 18] = { // Code 002B, PLUS SIGN
  ____X___,________,
  ____X___,________,
  ____X___,________,
  ____X___,________,
  XXXXXXXX,X_______,
  ____X___,________,
  ____X___,________,
  ____X___,________,
  ____X___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_002C[  3] = { // Code 002C, COMMA
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_002D[  1] = { // Code 002D, HYPHEN-MINUS
  XXXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_002E[  1] = { // Code 002E, FULL STOP
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_002F[ 11] = { // Code 002F, SOLIDUS
  ___X____,
  ___X____,
  __X_____,
  __X_____,
  __X_____,
  _X______,
  _X______,
  _X______,
  _X______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0030[ 11] = { // Code 0030, DIGIT ZERO
  __XX____,
  _X__X___,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  _X__X___,
  __XX____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0031[ 11] = { // Code 0031, DIGIT ONE
  ___X____,
  __XX____,
  _X_X____,
  X__X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0032[ 11] = { // Code 0032, DIGIT TWO
  _XXXX___,
  X____X__,
  X____X__,
  _____X__,
  _____X__,
  ____X___,
  ___X____,
  __X_____,
  _X______,
  X_______,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0033[ 11] = { // Code 0033, DIGIT THREE
  _XXXX___,
  X____X__,
  _____X__,
  _____X__,
  _____X__,
  __XXX___,
  _____X__,
  _____X__,
  _____X__,
  X____X__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0034[ 11] = { // Code 0034, DIGIT FOUR
  ____X___,
  ___XX___,
  __X_X___,
  __X_X___,
  _X__X___,
  _X__X___,
  X___X___,
  XXXXXX__,
  ____X___,
  ____X___,
  ____X___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0035[ 11] = { // Code 0035, DIGIT FIVE
  _XXXXX__,
  _X______,
  _X______,
  X_______,
  X_XXX___,
  XX___X__,
  _____X__,
  _____X__,
  X____X__,
  X___X___,
  _XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0036[ 11] = { // Code 0036, DIGIT SIX
  __XXX___,
  _X___X__,
  X_______,
  X_______,
  X_XXX___,
  XX___X__,
  X____X__,
  X____X__,
  X____X__,
  _X___X__,
  __XXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0037[ 11] = { // Code 0037, DIGIT SEVEN
  XXXXXX__,
  ____X___,
  ____X___,
  ___X____,
  ___X____,
  __X_____,
  __X_____,
  __X_____,
  _X______,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0038[ 11] = { // Code 0038, DIGIT EIGHT
  _XXXX___,
  X____X__,
  X____X__,
  X____X__,
  _X__X___,
  __XX____,
  _X__X___,
  X____X__,
  X____X__,
  X____X__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0039[ 11] = { // Code 0039, DIGIT NINE
  _XXX____,
  X___X___,
  X____X__,
  X____X__,
  X____X__,
  X___XX__,
  _XXX_X__,
  _____X__,
  _____X__,
  X___X___,
  _XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_003A[  8] = { // Code 003A, COLON
  X_______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_003B[ 10] = { // Code 003B, SEMICOLON
  X_______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_003C[  7] = { // Code 003C, LESS-THAN SIGN
  ______X_,
  ___XXX__,
  _XX_____,
  X_______,
  _XX_____,
  ___XXX__,
  ______X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_003D[  5] = { // Code 003D, EQUALS SIGN
  XXXXXXX_,
  ________,
  ________,
  ________,
  XXXXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_003E[  7] = { // Code 003E, GREATER-THAN SIGN
  X_______,
  _XXX____,
  ____XX__,
  ______X_,
  ____XX__,
  _XXX____,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_003F[ 11] = { // Code 003F, QUESTION MARK
  __XXXX__,
  _X____X_,
  X_____X_,
  ______X_,
  _____X__,
  _____X__,
  ____X___,
  ___X____,
  ___X____,
  ________,
  ___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0040[ 26] = { // Code 0040, COMMERCIAL AT
  ____XXXX,X_______,
  __XX____,_XX_____,
  _X______,__X_____,
  _X___XX_,X__X____,
  X___X__X,X__X____,
  X__X____,X__X____,
  X__X___X,___X____,
  X__X___X,___X____,
  X__X__XX,__X_____,
  _X__XX_X,XX______,
  _X______,___X____,
  __XX____,_XX_____,
  ____XXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0041[ 22] = { // Code 0041, LATIN CAPITAL LETTER A
  ____X___,________,
  ___X_X__,________,
  ___X_X__,________,
  ___X_X__,________,
  __X___X_,________,
  __X___X_,________,
  _XXXXXXX,________,
  _X_____X,________,
  _X_____X,________,
  X_______,X_______,
  X_______,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0042[ 11] = { // Code 0042, LATIN CAPITAL LETTER B
  XXXXXX__,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  XXXXXX__,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0043[ 22] = { // Code 0043, LATIN CAPITAL LETTER C
  ___XXXX_,________,
  _XX____X,________,
  _X______,X_______,
  X_______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  X_______,________,
  _X______,X_______,
  _XX____X,________,
  ___XXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0044[ 11] = { // Code 0044, LATIN CAPITAL LETTER D
  XXXXX___,
  X____XX_,
  X_____X_,
  X______X,
  X______X,
  X______X,
  X______X,
  X______X,
  X_____X_,
  X____XX_,
  XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0045[ 11] = { // Code 0045, LATIN CAPITAL LETTER E
  XXXXXXX_,
  X_______,
  X_______,
  X_______,
  X_______,
  XXXXXX__,
  X_______,
  X_______,
  X_______,
  X_______,
  XXXXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0046[ 11] = { // Code 0046, LATIN CAPITAL LETTER F
  XXXXXX__,
  X_______,
  X_______,
  X_______,
  X_______,
  XXXXX___,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0047[ 22] = { // Code 0047, LATIN CAPITAL LETTER G
  ___XXXX_,________,
  _XX____X,________,
  _X______,X_______,
  X_______,________,
  X_______,________,
  X____XXX,X_______,
  X_______,X_______,
  X_______,X_______,
  _X______,X_______,
  _XX____X,X_______,
  ___XXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0048[ 11] = { // Code 0048, LATIN CAPITAL LETTER H
  X______X,
  X______X,
  X______X,
  X______X,
  X______X,
  XXXXXXXX,
  X______X,
  X______X,
  X______X,
  X______X,
  X______X};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0049[ 11] = { // Code 0049, LATIN CAPITAL LETTER I
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_004A[ 11] = { // Code 004A, LATIN CAPITAL LETTER J
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  X____X__,
  X____X__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_004B[ 11] = { // Code 004B, LATIN CAPITAL LETTER K
  X_____X_,
  X____X__,
  X___X___,
  X__X____,
  X_X_____,
  XX_X____,
  X___X___,
  X___X___,
  X____X__,
  X_____X_,
  X______X};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_004C[ 11] = { // Code 004C, LATIN CAPITAL LETTER L
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_004D[ 22] = { // Code 004D, LATIN CAPITAL LETTER M
  XX_____X,X_______,
  XX_____X,X_______,
  XX_____X,X_______,
  X_X___X_,X_______,
  X_X___X_,X_______,
  X_X___X_,X_______,
  X__X_X__,X_______,
  X__X_X__,X_______,
  X__X_X__,X_______,
  X__X_X__,X_______,
  X___X___,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_004E[ 11] = { // Code 004E, LATIN CAPITAL LETTER N
  X______X,
  XX_____X,
  X_X____X,
  X_X____X,
  X__X___X,
  X__X___X,
  X___X__X,
  X____X_X,
  X____X_X,
  X_____XX,
  X______X};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_004F[ 22] = { // Code 004F, LATIN CAPITAL LETTER O
  ___XXX__,________,
  _XX___XX,________,
  _X_____X,________,
  X_______,X_______,
  X_______,X_______,
  X_______,X_______,
  X_______,X_______,
  X_______,X_______,
  _X_____X,________,
  _XX___XX,________,
  ___XXX__,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0050[ 11] = { // Code 0050, LATIN CAPITAL LETTER P
  XXXXXX__,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  XXXXXX__,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0051[ 24] = { // Code 0051, LATIN CAPITAL LETTER Q
  ___XXX__,________,
  _XX___XX,________,
  _X_____X,________,
  X_______,X_______,
  X_______,X_______,
  X_______,X_______,
  X_______,X_______,
  X_______,X_______,
  _X___X_X,________,
  _XX___XX,________,
  ___XXX_X,________,
  ________,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0052[ 11] = { // Code 0052, LATIN CAPITAL LETTER R
  XXXXXX__,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  XXXXXX__,
  X___X___,
  X____X__,
  X_____X_,
  X_____X_,
  X______X};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0053[ 11] = { // Code 0053, LATIN CAPITAL LETTER S
  _XXXX___,
  X____X__,
  X____X__,
  X_______,
  _XX_____,
  ___XX___,
  _____X__,
  _____X__,
  X____X__,
  X____X__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0054[ 11] = { // Code 0054, LATIN CAPITAL LETTER T
  XXXXXXX_,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0055[ 11] = { // Code 0055, LATIN CAPITAL LETTER U
  X______X,
  X______X,
  X______X,
  X______X,
  X______X,
  X______X,
  X______X,
  X______X,
  X______X,
  _X____X_,
  __XXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0056[ 22] = { // Code 0056, LATIN CAPITAL LETTER V
  X_______,X_______,
  X_______,X_______,
  _X_____X,________,
  _X_____X,________,
  _X_____X,________,
  __X___X_,________,
  __X___X_,________,
  ___X_X__,________,
  ___X_X__,________,
  ___X_X__,________,
  ____X___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0057[ 22] = { // Code 0057, LATIN CAPITAL LETTER W
  X____X__,__X_____,
  X___X_X_,__X_____,
  X___X_X_,__X_____,
  X___X_X_,__X_____,
  _X__X_X_,_X______,
  _X_X___X,_X______,
  _X_X___X,_X______,
  _X_X___X,_X______,
  _X_X___X,_X______,
  __X_____,X_______,
  __X_____,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0058[ 11] = { // Code 0058, LATIN CAPITAL LETTER X
  _X_____X,
  __X___X_,
  __X__X__,
  ___X_X__,
  ____X___,
  ____X___,
  ___X_X__,
  __X__X__,
  __X___X_,
  _X____X_,
  X______X};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0059[ 22] = { // Code 0059, LATIN CAPITAL LETTER Y
  X_______,X_______,
  _X_____X,________,
  __X___X_,________,
  __X___X_,________,
  ___X_X__,________,
  ____X___,________,
  ____X___,________,
  ____X___,________,
  ____X___,________,
  ____X___,________,
  ____X___,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_005A[ 11] = { // Code 005A, LATIN CAPITAL LETTER Z
  _XXXXXXX,
  _______X,
  ______X_,
  _____X__,
  ____X___,
  ___X____,
  ___X____,
  __X_____,
  _X______,
  X_______,
  XXXXXXXX};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_005B[ 14] = { // Code 005B, LEFT SQUARE BRACKET
  XXX_____,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_005C[ 11] = { // Code 005C, REVERSE SOLIDUS
  X_______,
  X_______,
  _X______,
  _X______,
  _X______,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  ___X____,
  ___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_005D[ 14] = { // Code 005D, RIGHT SQUARE BRACKET
  XXX_____,
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
  XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_005E[  4] = { // Code 005E, CIRCUMFLEX ACCENT
  ___X____,
  __X_X___,
  _X___X__,
  X_____X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_005F[  1] = { // Code 005F, LOW LINE
  XXXXXXXX};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0060[  2] = { // Code 0060, GRAVE ACCENT
  X_______,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0061[  8] = { // Code 0061, LATIN SMALL LETTER A
  _XXXX___,
  X____X__,
  _____X__,
  ___XXX__,
  _XX__X__,
  X____X__,
  X___XX__,
  _XXX_X__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0062[ 11] = { // Code 0062, LATIN SMALL LETTER B
  X_______,
  X_______,
  X_______,
  X_XXX___,
  XX___X__,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  XX___X__,
  X_XXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0063[  8] = { // Code 0063, LATIN SMALL LETTER C
  _XXXX___,
  X____X__,
  X_______,
  X_______,
  X_______,
  X_______,
  X____X__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0064[ 11] = { // Code 0064, LATIN SMALL LETTER D
  ______X_,
  ______X_,
  ______X_,
  __XXX_X_,
  _X___XX_,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  _X___XX_,
  __XXX_X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0065[  8] = { // Code 0065, LATIN SMALL LETTER E
  _XXXX___,
  X____X__,
  X____X__,
  XXXXXX__,
  X_______,
  X_______,
  X____X__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0066[ 11] = { // Code 0066, LATIN SMALL LETTER F
  __XX____,
  _X______,
  _X______,
  XXXX____,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0067[ 11] = { // Code 0067, LATIN SMALL LETTER G
  __XXX_X_,
  _X___XX_,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  _X___XX_,
  __XXX_X_,
  ______X_,
  X____X__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0068[ 11] = { // Code 0068, LATIN SMALL LETTER H
  X_______,
  X_______,
  X_______,
  X_XXX___,
  XX___X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0069[ 11] = { // Code 0069, LATIN SMALL LETTER I
  X_______,
  ________,
  ________,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_006A[ 14] = { // Code 006A, LATIN SMALL LETTER J
  __X_____,
  ________,
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
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_006B[ 11] = { // Code 006B, LATIN SMALL LETTER K
  X_______,
  X_______,
  X_______,
  X____X__,
  X___X___,
  X__X____,
  XXX_____,
  X__X____,
  X___X___,
  X____X__,
  X_____X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_006C[ 11] = { // Code 006C, LATIN SMALL LETTER L
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_006D[ 16] = { // Code 006D, LATIN SMALL LETTER M
  X_XXX__X,XX______,
  XX___XX_,__X_____,
  X____X__,__X_____,
  X____X__,__X_____,
  X____X__,__X_____,
  X____X__,__X_____,
  X____X__,__X_____,
  X____X__,__X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_006E[  8] = { // Code 006E, LATIN SMALL LETTER N
  X_XXX___,
  XX___X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_006F[  8] = { // Code 006F, LATIN SMALL LETTER O
  _XXXX___,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0070[ 11] = { // Code 0070, LATIN SMALL LETTER P
  X_XXX___,
  XX___X__,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  XX___X__,
  X_XXX___,
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0071[ 11] = { // Code 0071, LATIN SMALL LETTER Q
  __XXX_X_,
  _X___XX_,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  _X___XX_,
  __XXX_X_,
  ______X_,
  ______X_,
  ______X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0072[  8] = { // Code 0072, LATIN SMALL LETTER R
  X_XX____,
  XX______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0073[  8] = { // Code 0073, LATIN SMALL LETTER S
  _XXXX___,
  X____X__,
  X_______,
  _XX_____,
  ___XX___,
  _____X__,
  X____X__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0074[ 11] = { // Code 0074, LATIN SMALL LETTER T
  _X______,
  _X______,
  _X______,
  XXXX____,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  __XX____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0075[  8] = { // Code 0075, LATIN SMALL LETTER U
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X___XX__,
  _XXX_X__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0076[  8] = { // Code 0076, LATIN SMALL LETTER V
  X_____X_,
  X_____X_,
  _X___X__,
  _X___X__,
  __X_X___,
  __X_X___,
  __X_X___,
  ___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0077[ 16] = { // Code 0077, LATIN SMALL LETTER W
  X____X__,__X_____,
  X___X_X_,__X_____,
  X___X_X_,__X_____,
  _X__X_X_,_X______,
  _X_X___X,_X______,
  _X_X___X,_X______,
  _X_X___X,_X______,
  __X_____,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0078[  8] = { // Code 0078, LATIN SMALL LETTER X
  X____X__,
  _X__X___,
  _X__X___,
  __XX____,
  __XX____,
  _X__X___,
  _X__X___,
  X____X__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0079[ 11] = { // Code 0079, LATIN SMALL LETTER Y
  X_____X_,
  X_____X_,
  _X___X__,
  _X___X__,
  __X_X___,
  __X_X___,
  __X_X___,
  ___X____,
  ___X____,
  __X_____,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_007A[  8] = { // Code 007A, LATIN SMALL LETTER Z
  XXXXXX__,
  _____X__,
  ____X___,
  ___X____,
  __X_____,
  _X______,
  X_______,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_007B[ 14] = { // Code 007B, LEFT CURLY BRACKET
  __X_____,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  X_______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  __X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_007C[ 14] = { // Code 007C, VERTICAL LINE
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_007D[ 14] = { // Code 007D, RIGHT CURLY BRACKET
  X_______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  __X_____,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_007E[  2] = { // Code 007E, TILDE
  _XX___X_,
  X__XXX__};

//
// Start of unicode area <Thai>
//
GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E00[  1] = { // Code 0E00
  ________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E01[  9] = { // Code 0E01, THAI CHARACTER KO KAI
  _XXXX___,
  X____X__,
  _XX___X_,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E02[  9] = { // Code 0E02, THAI CHARACTER KHO KHAI
  _XXX__X_,
  XX__X_X_,
  X_X_X_X_,
  _X_X__X_,
  ___X__X_,
  ___X__X_,
  ___X__X_,
  ___X__X_,
  __XXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E03[  9] = { // Code 0E03, THAI CHARACTER KHO KHUAT
  _XX_X__X,
  X__X_X_X,
  XX__X__X,
  X_X_X__X,
  _X__X__X,
  ____X__X,
  ____X__X,
  ____X__X,
  ___XXXXX};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E04[  9] = { // Code 0E04, THAI CHARACTER KHO KHWAI
  __XXXX__,
  _X____X_,
  X______X,
  X__X___X,
  X_X_X__X,
  X_XX___X,
  XX_____X,
  XX_____X,
  X______X};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E05[  9] = { // Code 0E05, THAI CHARACTER KHO KHON
  _XX__XX_,
  X__XX__X,
  X______X,
  X__X___X,
  X_X_X__X,
  X_XX___X,
  XX_____X,
  XX_____X,
  X______X};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E06[ 18] = { // Code 0E06, THAI CHARACTER KHO RAKHANG
  _XX_X___,_X______,
  X__X_X__,_X______,
  XX__X___,_X______,
  X_X_X___,_X______,
  _X__X___,_X______,
  ____X___,_X______,
  __XXXXX_,_X______,
  _X__X__X,XX______,
  __XXX___,_X______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E07[  9] = { // Code 0E07, THAI CHARACTER NGO NGU
  ____X___,
  ___X_X__,
  ____XX__,
  _____X__,
  X____X__,
  _X___X__,
  __X__X__,
  ___X_X__,
  ____XX__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E08[  9] = { // Code 0E08, THAI CHARACTER CHO CHAN
  __XXX___,
  _X___X__,
  X_____X_,
  X__X__X_,
  X_X_X_X_,
  ___XX_X_,
  _____XX_,
  _____XX_,
  ______X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E09[  9] = { // Code 0E09, THAI CHARACTER CHO CHING
  _XXXX___,
  X____X__,
  X_____X_,
  __X___X_,
  _X_X__X_,
  __X___X_,
  __X__XX_,
  __X_XX_X,
  __XX__X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E0A[ 10] = { // Code 0E0A, THAI CHARACTER CHO CHANG
  _______X,
  _XXXX_X_,
  XX___XX_,
  X_X_X__X,
  _X__X__X,
  ____X__X,
  ____X__X,
  ____X__X,
  ____X__X,
  ___XXXXX};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E0B[ 10] = { // Code 0E0B, THAI CHARACTER SO SO
  _______X,
  _XX_X_X_,
  X__X_XX_,
  XX__X__X,
  X_X_X__X,
  _X__X__X,
  ____X__X,
  ____X__X,
  ____X__X,
  ___XXXXX};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E0C[ 18] = { // Code 0E0C, THAI CHARACTER CHO CHOE
  _XXXX___,___X____,
  X____X__,___X____,
  _XX___X_,___X____,
  X_____X_,___X____,
  X_____X_,___X____,
  X____XXX,___X____,
  XX__X_X_,XX_X____,
  X_X_X_X_,__XX____,
  _X___XX_,___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E0D[ 26] = { // Code 0E0D, THAI CHARACTER YO YING
  _XXXX___,___X____,
  X____X__,___X____,
  _XX___X_,___X____,
  X_____X_,___X____,
  X_____X_,___X____,
  X_____X_,___X____,
  XX____X_,___X____,
  X_X___X_,___X____,
  _X____XX,XXXX____,
  ________,________,
  _______X,___X____,
  ______X_,X_X_____,
  _______X,XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E0E[ 30] = { // Code 0E0E, THAI CHARACTER DO CHADA
  ___XXXX_,________,
  __X____X,________,
  ___XX___,X_______,
  __X_____,X_______,
  __X_____,X_______,
  __X_____,X_______,
  _XX_____,X_______,
  X_X_____,X_______,
  _X______,X_______,
  ________,X_______,
  ________,X_______,
  ___X____,X_______,
  __XX____,X_______,
  _X_XXX_X,________,
  __X___X_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E0F[ 30] = { // Code 0E0F, THAI CHARACTER TO PATAK
  ___XXXX_,________,
  __X____X,________,
  ___XX___,X_______,
  __X_____,X_______,
  __X_____,X_______,
  __X_____,X_______,
  _XX_____,X_______,
  X_X_____,X_______,
  _X______,X_______,
  ________,X_______,
  ________,X_______,
  ___X____,X_______,
  __XX____,X_______,
  _X_XX_X_,X_______,
  __X__X_X,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E10[ 32] = { // Code 0E10, THAI CHARACTER THO THAN
  ________,X_______,
  ___XXXX_,X_______,
  __X____X,X_______,
  _XXXXXX_,________,
  _______X,________,
  ___X___X,________,
  __X_X__X,________,
  ___X_XX_,________,
  _____XX_,________,
  ______X_,________,
  ________,________,
  __X___X_,________,
  __X__X_X,________,
  _XX___XX,________,
  X_XX_X_X,________,
  _X__X_X_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E11[ 18] = { // Code 0E11, THAI CHARACTER THO NANGMONTHO
  _XX_X___,XX______,
  X__X_X_X,__X_____,
  XX__X__X,__X_____,
  X_X_X_X_,__X_____,
  _X__X_X_,__X_____,
  ____XX__,__X_____,
  ____XX__,__X_____,
  ____XX__,__X_____,
  ____X___,__X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E12[ 18] = { // Code 0E12, THAI CHARACTER THO PHUTHAO
  _XX__XX_,___X____,
  X__XX__X,___X____,
  X______X,___X____,
  X___X__X,___X____,
  X__X_X_X,___X____,
  X___X__X,___X____,
  X__X__XX,X__X____,
  X_X__X_X,_XXX____,
  XX____XX,___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E13[ 18] = { // Code 0E13, THAI CHARACTER NO NEN
  _XXXX___,___X____,
  X____X__,___X____,
  _XX___X_,___X____,
  X_____X_,___X____,
  X_____X_,___X____,
  X_____X_,___X____,
  XX____X_,_XXX____,
  X_X___X_,X_X_X___,
  _X____XX,___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E14[  9] = { // Code 0E14, THAI CHARACTER DO DEK
  __XXXX__,
  _X____X_,
  X______X,
  X___X__X,
  X__X_X_X,
  X___X__X,
  X__X___X,
  X_X____X,
  XX_____X};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E15[  9] = { // Code 0E15, THAI CHARACTER TO TAO
  _XX__XX_,
  X__XX__X,
  X______X,
  X___X__X,
  X__X_X_X,
  X___X__X,
  X__X___X,
  X_X____X,
  XX_____X};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E16[  9] = { // Code 0E16, THAI CHARACTER THO THUNG
  _XXXX___,
  X____X__,
  _XX___X_,
  X_____X_,
  X_____X_,
  X_____X_,
  XX____X_,
  X_X___X_,
  _X____X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E17[  9] = { // Code 0E17, THAI CHARACTER THO THAHAN
  _X___XX_,
  X_X__X_X,
  _XX_X__X,
  __X_X__X,
  __XX___X,
  __XX___X,
  __XX___X,
  __X____X,
  __X____X};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E18[  9] = { // Code 0E18, THAI CHARACTER THO THONG
  __XXX___,
  _X___X__,
  X_______,
  XXXXX___,
  _X__X___,
  _X__X___,
  _X__X___,
  _X__X___,
  XXXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E19[ 18] = { // Code 0E19, THAI CHARACTER NO NU
  _X_____X,________,
  X_X____X,________,
  _XX____X,________,
  __X____X,________,
  __X____X,________,
  __X____X,________,
  __X__XXX,________,
  __X_X_X_,X_______,
  __XX___X,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E1A[  9] = { // Code 0E1A, THAI CHARACTER BO BAIMAI
  _X_____X,
  X_X____X,
  _XX____X,
  __X____X,
  __X____X,
  __X____X,
  __X____X,
  __X____X,
  _XXXXXXX};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E1B[ 14] = { // Code 0E1B, THAI CHARACTER PO PLA
  _______X,
  _______X,
  _______X,
  _______X,
  _______X,
  _X_____X,
  X_X____X,
  _XX____X,
  __X____X,
  __X____X,
  __X____X,
  __X____X,
  __X____X,
  _XXXXXXX};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E1C[  9] = { // Code 0E1C, THAI CHARACTER PHO PHUNG
  _X____X_,
  X_X___X_,
  XX____X_,
  X_____X_,
  X_____X_,
  X__X__X_,
  X_X_X_X_,
  XX___XX_,
  X_____X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E1D[ 14] = { // Code 0E1D, THAI CHARACTER FO FA
  ______X_,
  ______X_,
  ______X_,
  ______X_,
  ______X_,
  _X____X_,
  X_X___X_,
  XX____X_,
  X_____X_,
  X_____X_,
  X__X__X_,
  X_X_X_X_,
  XX___XX_,
  X_____X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E1E[ 18] = { // Code 0E1E, THAI CHARACTER PHO PHAN
  _X___X__,X_______,
  X_X_X_X_,X_______,
  _XX_X_X_,X_______,
  __X_X_X_,X_______,
  __XX___X,X_______,
  __XX___X,X_______,
  __XX___X,X_______,
  __X_____,X_______,
  __X_____,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E1F[ 28] = { // Code 0E1F, THAI CHARACTER FO FAN
  ________,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  _X___X__,X_______,
  X_X_X_X_,X_______,
  _XX_X_X_,X_______,
  __X_X_X_,X_______,
  __XX___X,X_______,
  __XX___X,X_______,
  __XX___X,X_______,
  __X_____,X_______,
  __X_____,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E20[ 18] = { // Code 0E20, THAI CHARACTER PHO SAMPHAO
  ___XXXX_,________,
  __X____X,________,
  ___XX___,X_______,
  __X_____,X_______,
  __X_____,X_______,
  __X_____,X_______,
  _XX_____,X_______,
  X_X_____,X_______,
  _X______,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E21[  9] = { // Code 0E21, THAI CHARACTER MO MA
  _X_____X,
  X_X____X,
  _XX____X,
  __X____X,
  __X____X,
  __X____X,
  _XXXX__X,
  X_X__X_X,
  _XX___XX};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E22[  9] = { // Code 0E22, THAI CHARACTER YO YAK
  _XX___X_,
  XX_X__X_,
  X_X___X_,
  X_____X_,
  _XXX__X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _XXXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E23[  9] = { // Code 0E23, THAI CHARACTER RO RUA
  _XXXX___,
  X____X__,
  XXXX_X__,
  ___X____,
  ___X____,
  ___X____,
  __XX____,
  _X_X____,
  __X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E24[ 15] = { // Code 0E24, THAI CHARACTER RU
  _XXXX___,
  X____X__,
  _XX___X_,
  X_____X_,
  X_____X_,
  X_____X_,
  XX____X_,
  X_X___X_,
  _X____X_,
  ______X_,
  ______X_,
  ______X_,
  ______X_,
  ______X_,
  ______X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E25[  9] = { // Code 0E25, THAI CHARACTER LO LING
  __XXX___,
  _X___X__,
  X__X__X_,
  X_X_X_X_,
  __X_X_X_,
  _X___XX_,
  _XX__XX_,
  _X_X__X_,
  __X___X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E26[ 30] = { // Code 0E26, THAI CHARACTER LU
  ___XXXX_,________,
  __X____X,________,
  ___XX___,X_______,
  __X_____,X_______,
  __X_____,X_______,
  __X_____,X_______,
  _XX_____,X_______,
  X_X_____,X_______,
  _X______,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______,
  ________,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E27[  9] = { // Code 0E27, THAI CHARACTER WO WAEN
  _XXXX___,
  X____X__,
  X____X__,
  X____X__,
  _____X__,
  _____X__,
  ____XX__,
  ___X_X__,
  ____X___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E28[ 10] = { // Code 0E28, THAI CHARACTER SO SALA
  _______X,
  __XXXXX_,
  _X____X_,
  X____X_X,
  X__XX__X,
  X_X_X__X,
  X_XX___X,
  XX_____X,
  XX_____X,
  X______X};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E29[ 18] = { // Code 0E29, THAI CHARACTER SO RUSI
  _X_____X,________,
  X_X____X,________,
  _XX__X_X,_X______,
  __X_X_XX,X_______,
  __X__XXX,________,
  __X____X,________,
  __X____X,________,
  __X____X,________,
  _XXXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E2A[ 10] = { // Code 0E2A, THAI CHARACTER SO SUA
  _____X__,
  __XXX___,
  _X__XX__,
  X__X__X_,
  X__X__X_,
  __X_X_X_,
  _X___XX_,
  _XX__XX_,
  _X_X__X_,
  __X___X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E2B[  9] = { // Code 0E2B, THAI CHARACTER HO HIP
  _X____X_,
  X_X__X_X,
  _XX__X_X,
  __X___XX,
  __X__X_X,
  __X__X_X,
  __X_X__X,
  __XX___X,
  __X____X};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E2C[ 24] = { // Code 0E2C, THAI CHARACTER LO CHULA
  _______X,XX______,
  ______X_,X_______,
  _______X,X_______,
  _X___X__,X_______,
  X_X_X_X_,X_______,
  _XX_X_X_,X_______,
  __X_X_X_,X_______,
  __XX___X,X_______,
  __XX___X,X_______,
  __XX___X,X_______,
  __X_____,X_______,
  __X_____,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E2D[  9] = { // Code 0E2D, THAI CHARACTER O ANG
  __XXX___,
  _X___X__,
  X__X__X_,
  X_X_X_X_,
  __XX__X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __XXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E2E[ 10] = { // Code 0E2E, THAI CHARACTER HO NOKHUK
  ________,
  _XXXXXX_,
  X____X__,
  _XXXX_X_,
  ______X_,
  _X____X_,
  X_X___X_,
  XX____X_,
  X_____X_,
  XXXXXXX_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E2F[  9] = { // Code 0E2F, THAI CHARACTER PAIYANNOI
  _X___X__,
  X_X__X__,
  XX__XX__,
  _XXX_X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E30[  9] = { // Code 0E30, THAI CHARACTER SARA A
  _X___X__,
  X_X_X___,
  _XXX____,
  ________,
  ________,
  ________,
  _X___X__,
  X_X_X___,
  _XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E31[  3] = { // Code 0E31, THAI CHARACTER MAI HAN-AKAT
  _X____X_,
  X_X_XX__,
  _XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E32[  9] = { // Code 0E32, THAI CHARACTER SARA AA
  _XXXX___,
  X____X__,
  X____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E33[ 28] = { // Code 0E33, THAI CHARACTER SARA AM
  _X______,________,
  X_X_____,________,
  _X______,________,
  ________,________,
  ________,________,
  _____XXX,X_______,
  ____X___,_X______,
  ____X___,_X______,
  ________,_X______,
  ________,_X______,
  ________,_X______,
  ________,_X______,
  ________,_X______,
  ________,_X______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E34[  4] = { // Code 0E34, THAI CHARACTER SARA I
  _XXXX___,
  X____X__,
  XXXXX_X_,
  _____XX_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E35[  5] = { // Code 0E35, THAI CHARACTER SARA II
  ______X_,
  _XXXX_X_,
  X____XX_,
  XXXXX_X_,
  _____XX_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E36[  6] = { // Code 0E36, THAI CHARACTER SARA UE
  _____X__,
  ____X_X_,
  _XXXXX__,
  X____X__,
  XXXXX_X_,
  _____XX_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E37[  5] = { // Code 0E37, THAI CHARACTER SARA UEE
  ____X_X_,
  _XXXX_X_,
  X____XX_,
  XXXXX_X_,
  _____XX_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E38[  4] = { // Code 0E38, THAI CHARACTER SARA U
  _X______,
  X_X_____,
  _XX_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E39[  4] = { // Code 0E39, THAI CHARACTER SARA UU
  _X__X___,
  X_X_X___,
  _XX_X___,
  __XXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E3A[  2] = { // Code 0E3A, THAI CHARACTER PHINTHU
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E3F[ 14] = { // Code 0E3F, THAI CURRENCY SYMBOL BAHT
  ___X____,
  XXXXXX__,
  X__X__X_,
  X__X__X_,
  X__X__X_,
  X__X__X_,
  XXXXXX__,
  X__X__X_,
  X__X__X_,
  X__X__X_,
  X__X__X_,
  XXXXXX__,
  ___X____,
  ___X____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E40[  9] = { // Code 0E40, THAI CHARACTER SARA E
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  XX______,
  X_X_____,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E41[  9] = { // Code 0E41, THAI CHARACTER SARA AE
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  XX__XX__,
  X_X_X_X_,
  _X___X__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E42[ 15] = { // Code 0E42, THAI CHARACTER SARA O
  _XXXX___,
  X____X__,
  X____X__,
  _XX_____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___XX___,
  ___X_X__,
  ____X___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E43[ 15] = { // Code 0E43, THAI CHARACTER SARA AI MAIMUAN
  _XXX____,
  X___X___,
  XX__X___,
  X_X_X___,
  _X__X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____XX__,
  ____X_X_,
  _____X__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E44[ 16] = { // Code 0E44, THAI CHARACTER SARA AI MAIMALAI
  X_______,
  _X__X___,
  _X_XX___,
  _XX_X___,
  _X__X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____XX__,
  ____X_X_,
  _____X__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E45[ 15] = { // Code 0E45, THAI CHARACTER LAKKHANGYAO
  _XXXX___,
  X____X__,
  X____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E46[ 15] = { // Code 0E46, THAI CHARACTER MAIYAMOK
  _XXX_XX_,
  X_X_X_X_,
  _X____X_,
  ______X_,
  ______X_,
  ______X_,
  ______X_,
  ______X_,
  ______X_,
  ______X_,
  ______X_,
  ______X_,
  ______X_,
  ______X_,
  ______X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E47[  5] = { // Code 0E47, THAI CHARACTER MAITAIKHU
  _____X__,
  _XXXX___,
  X_______,
  X__XX___,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E48[  3] = { // Code 0E48, THAI CHARACTER MAI EK
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E49[  5] = { // Code 0E49, THAI CHARACTER MAI THO
  _X______,
  X_X_X___,
  _XX_X___,
  _X_X____,
  XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E4A[  4] = { // Code 0E4A, THAI CHARACTER MAI TRI
  _X_X__X_,
  X_X_X_X_,
  XX__X_X_,
  XX_XXX__};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E4B[  4] = { // Code 0E4B, THAI CHARACTER MAI CHATTAWA
  __X_____,
  __X_____,
  XXXXX___,
  __X_____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E4C[  5] = { // Code 0E4C, THAI CHARACTER THANTHAKHAT
  _____X__,
  _XXXX___,
  XX______,
  X_X_____,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E4D[  3] = { // Code 0E4D, THAI CHARACTER NIKHAHIT
  _X______,
  X_X_____,
  _X______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E4E[  5] = { // Code 0E4E, THAI CHARACTER YAMAKKAN
  __XXX___,
  _X______,
  _XXX____,
  X_______,
  XXX_____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E4F[  5] = { // Code 0E4F, THAI CHARACTER FONGMAN
  _XXX____,
  X___X___,
  X_X_X___,
  X___X___,
  _XXX____};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E50[ 12] = { // Code 0E50, THAI DIGIT ZERO
  __XXXXX_,________,
  _X_____X,________,
  X_______,X_______,
  X_______,X_______,
  _X_____X,________,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E51[  8] = { // Code 0E51, THAI DIGIT ONE
  __XXX___,
  _X___X__,
  X__X__X_,
  X_X_X_X_,
  X__XX_X_,
  _XXX__X_,
  _____X__,
  ____X___};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E52[ 18] = { // Code 0E52, THAI DIGIT TWO
  X_______,________,
  _X______,________,
  _X______,________,
  _X__XX_X,X_______,
  _X_X__X_,X_______,
  _X_XX___,X_______,
  _X_X_X__,X_______,
  _X__X___,X_______,
  _XXXXXXX,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E53[ 12] = { // Code 0E53, THAI DIGIT THREE
  _XXX__XX,________,
  X___XX__,X_______,
  X____X__,X_______,
  X_X__X__,X_______,
  XX_X_X__,X_______,
  _XX__X__,X_______};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E54[ 16] = { // Code 0E54, THAI DIGIT FOUR
  ________,_X______,
  ________,X_______,
  _XXXXXXX,________,
  X_______,________,
  X___X___,________,
  X__X_X__,________,
  X___X___,________,
  _XXXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E55[ 18] = { // Code 0E55, THAI DIGIT FIVE
  ___XX___,________,
  __X__X__,_X______,
  __X__X__,X_______,
  __XXXXXX,________,
  _X______,________,
  X___X___,________,
  X__X_X__,________,
  X___X___,________,
  _XXXXXXX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E56[ 18] = { // Code 0E56, THAI DIGIT SIX
  X_______,________,
  _X______,________,
  _X______,________,
  _XXXXXXX,________,
  _X______,X_______,
  ________,X_______,
  __X_____,X_______,
  _X_X___X,________,
  __XXXXX_,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E57[ 18] = { // Code 0E57, THAI DIGIT SEVEN
  ________,_X______,
  ________,X_______,
  ________,X_______,
  _XX_XX__,X_______,
  X__X__X_,X_______,
  X_____X_,X_______,
  X_X___X_,X_______,
  XX_X__X_,X_______,
  _XX___XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E58[ 16] = { // Code 0E58, THAI DIGIT EIGHT
  ________,_X______,
  ________,X_______,
  _XXXXXXX,________,
  X_______,________,
  X_______,________,
  X_XX___X,________,
  XX__XXX_,X_______,
  _X____XX,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E59[ 18] = { // Code 0E59, THAI DIGIT NINE
  ________,_X______,
  ________,_X______,
  ________,_X______,
  _XXX__XX,_X______,
  X___XX__,XX______,
  X____X__,________,
  X__X__X_,________,
  _XX_X_X_,________,
  __XX___X,________};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E5A[  9] = { // Code 0E5A, THAI CHARACTER ANGKHANKHU
  _X__X_X_,
  X_X_X_X_,
  XX_XX_X_,
  _XX_X_X_,
  ____X_X_,
  ____X_X_,
  ____X_X_,
  ____X_X_,
  ____X_X_};

GUI_CONST_STORAGE unsigned char acGUI_FontCordiaNew32_0E5B[ 24] = { // Code 0E5B, THAI CHARACTER KHOMUT
  __XXX___,________,________,
  _X___X__,________,________,
  X_______,________,________,
  X_______,X_X_X___,X_______,
  X_______,XX_X_X__,X_______,
  X______X,_X_X__XX,________,
  _X____X_,________,________,
  __XXXX__,________,________};

GUI_CONST_STORAGE GUI_CHARINFO_EXT GUI_FontCordiaNew32_CharInfo[183] = {
   {   1,   1,   0,  21,   4, acGUI_FontCordiaNew32_0020 } // Code 0020, SPACE
  ,{   1,  11,   2,  10,   5, acGUI_FontCordiaNew32_0021 } // Code 0021, EXCLAMATION MARK
  ,{   3,   4,   0,  10,   4, acGUI_FontCordiaNew32_0022 } // Code 0022, QUOTATION MARK
  ,{   8,  11,   0,  10,   8, acGUI_FontCordiaNew32_0023 } // Code 0023, NUMBER SIGN
  ,{   6,  13,   1,   9,   8, acGUI_FontCordiaNew32_0024 } // Code 0024, DOLLAR SIGN
  ,{  10,  11,   1,  10,  13, acGUI_FontCordiaNew32_0025 } // Code 0025, PERCENT SIGN
  ,{   9,  11,   1,  10,  10, acGUI_FontCordiaNew32_0026 } // Code 0026, AMPERSAND
  ,{   1,   4,   1,  10,   3, acGUI_FontCordiaNew32_0027 } // Code 0027, APOSTROPHE
  ,{   3,  14,   1,  10,   5, acGUI_FontCordiaNew32_0028 } // Code 0028, LEFT PARENTHESIS
  ,{   3,  14,   1,  10,   5, acGUI_FontCordiaNew32_0029 } // Code 0029, RIGHT PARENTHESIS
  ,{   5,   4,   0,  10,   6, acGUI_FontCordiaNew32_002A } // Code 002A, ASTERISK
  ,{   9,   9,   0,  11,  10, acGUI_FontCordiaNew32_002B } // Code 002B, PLUS SIGN
  ,{   1,   3,   1,  20,   4, acGUI_FontCordiaNew32_002C } // Code 002C, COMMA
  ,{   4,   1,   0,  16,   5, acGUI_FontCordiaNew32_002D } // Code 002D, HYPHEN-MINUS
  ,{   1,   1,   1,  20,   4, acGUI_FontCordiaNew32_002E } // Code 002E, FULL STOP
  ,{   4,  11,   0,  10,   4, acGUI_FontCordiaNew32_002F } // Code 002F, SOLIDUS
  ,{   6,  11,   1,  10,   8, acGUI_FontCordiaNew32_0030 } // Code 0030, DIGIT ZERO
  ,{   4,  11,   1,  10,   8, acGUI_FontCordiaNew32_0031 } // Code 0031, DIGIT ONE
  ,{   6,  11,   1,  10,   8, acGUI_FontCordiaNew32_0032 } // Code 0032, DIGIT TWO
  ,{   6,  11,   1,  10,   8, acGUI_FontCordiaNew32_0033 } // Code 0033, DIGIT THREE
  ,{   6,  11,   1,  10,   8, acGUI_FontCordiaNew32_0034 } // Code 0034, DIGIT FOUR
  ,{   6,  11,   1,  10,   8, acGUI_FontCordiaNew32_0035 } // Code 0035, DIGIT FIVE
  ,{   6,  11,   1,  10,   8, acGUI_FontCordiaNew32_0036 } // Code 0036, DIGIT SIX
  ,{   6,  11,   1,  10,   8, acGUI_FontCordiaNew32_0037 } // Code 0037, DIGIT SEVEN
  ,{   6,  11,   1,  10,   8, acGUI_FontCordiaNew32_0038 } // Code 0038, DIGIT EIGHT
  ,{   6,  11,   1,  10,   8, acGUI_FontCordiaNew32_0039 } // Code 0039, DIGIT NINE
  ,{   1,   8,   1,  13,   4, acGUI_FontCordiaNew32_003A } // Code 003A, COLON
  ,{   1,  10,   1,  13,   4, acGUI_FontCordiaNew32_003B } // Code 003B, SEMICOLON
  ,{   7,   7,   1,  12,  10, acGUI_FontCordiaNew32_003C } // Code 003C, LESS-THAN SIGN
  ,{   7,   5,   1,  13,  10, acGUI_FontCordiaNew32_003D } // Code 003D, EQUALS SIGN
  ,{   7,   7,   1,  12,  10, acGUI_FontCordiaNew32_003E } // Code 003E, GREATER-THAN SIGN
  ,{   7,  11,   0,  10,   8, acGUI_FontCordiaNew32_003F } // Code 003F, QUESTION MARK
  ,{  12,  13,   0,  11,  12, acGUI_FontCordiaNew32_0040 } // Code 0040, COMMERCIAL AT
  ,{   9,  11,   0,  10,  10, acGUI_FontCordiaNew32_0041 } // Code 0041, LATIN CAPITAL LETTER A
  ,{   7,  11,   1,  10,  10, acGUI_FontCordiaNew32_0042 } // Code 0042, LATIN CAPITAL LETTER B
  ,{   9,  11,   1,  10,  11, acGUI_FontCordiaNew32_0043 } // Code 0043, LATIN CAPITAL LETTER C
  ,{   8,  11,   1,  10,  11, acGUI_FontCordiaNew32_0044 } // Code 0044, LATIN CAPITAL LETTER D
  ,{   7,  11,   1,  10,   9, acGUI_FontCordiaNew32_0045 } // Code 0045, LATIN CAPITAL LETTER E
  ,{   6,  11,   1,  10,   8, acGUI_FontCordiaNew32_0046 } // Code 0046, LATIN CAPITAL LETTER F
  ,{   9,  11,   1,  10,  12, acGUI_FontCordiaNew32_0047 } // Code 0047, LATIN CAPITAL LETTER G
  ,{   8,  11,   1,  10,  11, acGUI_FontCordiaNew32_0048 } // Code 0048, LATIN CAPITAL LETTER H
  ,{   1,  11,   1,  10,   4, acGUI_FontCordiaNew32_0049 } // Code 0049, LATIN CAPITAL LETTER I
  ,{   6,  11,   0,  10,   8, acGUI_FontCordiaNew32_004A } // Code 004A, LATIN CAPITAL LETTER J
  ,{   8,  11,   1,  10,  10, acGUI_FontCordiaNew32_004B } // Code 004B, LATIN CAPITAL LETTER K
  ,{   6,  11,   1,  10,   8, acGUI_FontCordiaNew32_004C } // Code 004C, LATIN CAPITAL LETTER L
  ,{   9,  11,   1,  10,  12, acGUI_FontCordiaNew32_004D } // Code 004D, LATIN CAPITAL LETTER M
  ,{   8,  11,   1,  10,  11, acGUI_FontCordiaNew32_004E } // Code 004E, LATIN CAPITAL LETTER N
  ,{   9,  11,   1,  10,  12, acGUI_FontCordiaNew32_004F } // Code 004F, LATIN CAPITAL LETTER O
  ,{   7,  11,   1,  10,   9, acGUI_FontCordiaNew32_0050 } // Code 0050, LATIN CAPITAL LETTER P
  ,{   9,  12,   1,  10,  12, acGUI_FontCordiaNew32_0051 } // Code 0051, LATIN CAPITAL LETTER Q
  ,{   8,  11,   1,  10,  10, acGUI_FontCordiaNew32_0052 } // Code 0052, LATIN CAPITAL LETTER R
  ,{   6,  11,   1,  10,   9, acGUI_FontCordiaNew32_0053 } // Code 0053, LATIN CAPITAL LETTER S
  ,{   7,  11,   0,  10,   8, acGUI_FontCordiaNew32_0054 } // Code 0054, LATIN CAPITAL LETTER T
  ,{   8,  11,   1,  10,  11, acGUI_FontCordiaNew32_0055 } // Code 0055, LATIN CAPITAL LETTER U
  ,{   9,  11,  -1,  10,   8, acGUI_FontCordiaNew32_0056 } // Code 0056, LATIN CAPITAL LETTER V
  ,{  11,  11,   0,  10,  12, acGUI_FontCordiaNew32_0057 } // Code 0057, LATIN CAPITAL LETTER W
  ,{   8,  11,   0,  10,   9, acGUI_FontCordiaNew32_0058 } // Code 0058, LATIN CAPITAL LETTER X
  ,{   9,  11,   0,  10,   9, acGUI_FontCordiaNew32_0059 } // Code 0059, LATIN CAPITAL LETTER Y
  ,{   8,  11,   0,  10,   9, acGUI_FontCordiaNew32_005A } // Code 005A, LATIN CAPITAL LETTER Z
  ,{   3,  14,   1,  10,   5, acGUI_FontCordiaNew32_005B } // Code 005B, LEFT SQUARE BRACKET
  ,{   4,  11,   0,  10,   4, acGUI_FontCordiaNew32_005C } // Code 005C, REVERSE SOLIDUS
  ,{   3,  14,   1,  10,   5, acGUI_FontCordiaNew32_005D } // Code 005D, RIGHT SQUARE BRACKET
  ,{   7,   4,   1,  10,  10, acGUI_FontCordiaNew32_005E } // Code 005E, CIRCUMFLEX ACCENT
  ,{   8,   1,   0,  22,   8, acGUI_FontCordiaNew32_005F } // Code 005F, LOW LINE
  ,{   2,   2,   1,  10,   5, acGUI_FontCordiaNew32_0060 } // Code 0060, GRAVE ACCENT
  ,{   6,   8,   1,  13,   8, acGUI_FontCordiaNew32_0061 } // Code 0061, LATIN SMALL LETTER A
  ,{   7,  11,   1,  10,   9, acGUI_FontCordiaNew32_0062 } // Code 0062, LATIN SMALL LETTER B
  ,{   6,   8,   1,  13,   8, acGUI_FontCordiaNew32_0063 } // Code 0063, LATIN SMALL LETTER C
  ,{   7,  11,   1,  10,   9, acGUI_FontCordiaNew32_0064 } // Code 0064, LATIN SMALL LETTER D
  ,{   6,   8,   1,  13,   8, acGUI_FontCordiaNew32_0065 } // Code 0065, LATIN SMALL LETTER E
  ,{   4,  11,   0,  10,   4, acGUI_FontCordiaNew32_0066 } // Code 0066, LATIN SMALL LETTER F
  ,{   7,  11,   1,  13,   9, acGUI_FontCordiaNew32_0067 } // Code 0067, LATIN SMALL LETTER G
  ,{   6,  11,   1,  10,   8, acGUI_FontCordiaNew32_0068 } // Code 0068, LATIN SMALL LETTER H
  ,{   1,  11,   1,  10,   3, acGUI_FontCordiaNew32_0069 } // Code 0069, LATIN SMALL LETTER I
  ,{   3,  14,  -1,  10,   3, acGUI_FontCordiaNew32_006A } // Code 006A, LATIN SMALL LETTER J
  ,{   7,  11,   1,  10,   8, acGUI_FontCordiaNew32_006B } // Code 006B, LATIN SMALL LETTER K
  ,{   1,  11,   1,  10,   3, acGUI_FontCordiaNew32_006C } // Code 006C, LATIN SMALL LETTER L
  ,{  11,   8,   1,  13,  13, acGUI_FontCordiaNew32_006D } // Code 006D, LATIN SMALL LETTER M
  ,{   6,   8,   1,  13,   8, acGUI_FontCordiaNew32_006E } // Code 006E, LATIN SMALL LETTER N
  ,{   6,   8,   1,  13,   8, acGUI_FontCordiaNew32_006F } // Code 006F, LATIN SMALL LETTER O
  ,{   7,  11,   1,  13,   9, acGUI_FontCordiaNew32_0070 } // Code 0070, LATIN SMALL LETTER P
  ,{   7,  11,   1,  13,   9, acGUI_FontCordiaNew32_0071 } // Code 0071, LATIN SMALL LETTER Q
  ,{   4,   8,   1,  13,   5, acGUI_FontCordiaNew32_0072 } // Code 0072, LATIN SMALL LETTER R
  ,{   6,   8,   1,  13,   8, acGUI_FontCordiaNew32_0073 } // Code 0073, LATIN SMALL LETTER S
  ,{   4,  11,   0,  10,   4, acGUI_FontCordiaNew32_0074 } // Code 0074, LATIN SMALL LETTER T
  ,{   6,   8,   1,  13,   8, acGUI_FontCordiaNew32_0075 } // Code 0075, LATIN SMALL LETTER U
  ,{   7,   8,   0,  13,   7, acGUI_FontCordiaNew32_0076 } // Code 0076, LATIN SMALL LETTER V
  ,{  11,   8,   0,  13,  11, acGUI_FontCordiaNew32_0077 } // Code 0077, LATIN SMALL LETTER W
  ,{   6,   8,   1,  13,   8, acGUI_FontCordiaNew32_0078 } // Code 0078, LATIN SMALL LETTER X
  ,{   7,  11,   0,  13,   7, acGUI_FontCordiaNew32_0079 } // Code 0079, LATIN SMALL LETTER Y
  ,{   6,   8,   1,  13,   8, acGUI_FontCordiaNew32_007A } // Code 007A, LATIN SMALL LETTER Z
  ,{   3,  14,   1,  10,   5, acGUI_FontCordiaNew32_007B } // Code 007B, LEFT CURLY BRACKET
  ,{   1,  14,   1,  10,   3, acGUI_FontCordiaNew32_007C } // Code 007C, VERTICAL LINE
  ,{   3,  14,   1,  10,   5, acGUI_FontCordiaNew32_007D } // Code 007D, RIGHT CURLY BRACKET
  ,{   7,   2,   1,  15,  10, acGUI_FontCordiaNew32_007E } // Code 007E, TILDE
  ,{   1,   1,   0,  21,   2, acGUI_FontCordiaNew32_0E00 } // Code 0E00
  ,{   7,   9,   1,  12,   9, acGUI_FontCordiaNew32_0E01 } // Code 0E01, THAI CHARACTER KO KAI
  ,{   7,   9,   1,  12,   9, acGUI_FontCordiaNew32_0E02 } // Code 0E02, THAI CHARACTER KHO KHAI
  ,{   8,   9,   0,  12,   9, acGUI_FontCordiaNew32_0E03 } // Code 0E03, THAI CHARACTER KHO KHUAT
  ,{   8,   9,   1,  12,  10, acGUI_FontCordiaNew32_0E04 } // Code 0E04, THAI CHARACTER KHO KHWAI
  ,{   8,   9,   1,  12,  10, acGUI_FontCordiaNew32_0E05 } // Code 0E05, THAI CHARACTER KHO KHON
  ,{  10,   9,   0,  12,  11, acGUI_FontCordiaNew32_0E06 } // Code 0E06, THAI CHARACTER KHO RAKHANG
  ,{   6,   9,   0,  12,   7, acGUI_FontCordiaNew32_0E07 } // Code 0E07, THAI CHARACTER NGO NGU
  ,{   7,   9,   1,  12,   9, acGUI_FontCordiaNew32_0E08 } // Code 0E08, THAI CHARACTER CHO CHAN
  ,{   8,   9,   1,  12,   9, acGUI_FontCordiaNew32_0E09 } // Code 0E09, THAI CHARACTER CHO CHING
  ,{   8,  10,   0,  11,   9, acGUI_FontCordiaNew32_0E0A } // Code 0E0A, THAI CHARACTER CHO CHANG
  ,{   8,  10,   0,  11,   9, acGUI_FontCordiaNew32_0E0B } // Code 0E0B, THAI CHARACTER SO SO
  ,{  12,   9,   1,  12,  14, acGUI_FontCordiaNew32_0E0C } // Code 0E0C, THAI CHARACTER CHO CHOE
  ,{  12,  13,   1,  12,  14, acGUI_FontCordiaNew32_0E0D } // Code 0E0D, THAI CHARACTER YO YING
  ,{   9,  15,   0,  12,  10, acGUI_FontCordiaNew32_0E0E } // Code 0E0E, THAI CHARACTER DO CHADA
  ,{   9,  15,   0,  12,  10, acGUI_FontCordiaNew32_0E0F } // Code 0E0F, THAI CHARACTER TO PATAK
  ,{   9,  16,   0,  11,   9, acGUI_FontCordiaNew32_0E10 } // Code 0E10, THAI CHARACTER THO THAN
  ,{  11,   9,   0,  12,  12, acGUI_FontCordiaNew32_0E11 } // Code 0E11, THAI CHARACTER THO NANGMONTHO
  ,{  12,   9,   1,  12,  14, acGUI_FontCordiaNew32_0E12 } // Code 0E12, THAI CHARACTER THO PHUTHAO
  ,{  13,   9,   1,  12,  14, acGUI_FontCordiaNew32_0E13 } // Code 0E13, THAI CHARACTER NO NEN
  ,{   8,   9,   1,  12,  10, acGUI_FontCordiaNew32_0E14 } // Code 0E14, THAI CHARACTER DO DEK
  ,{   8,   9,   1,  12,  10, acGUI_FontCordiaNew32_0E15 } // Code 0E15, THAI CHARACTER TO TAO
  ,{   7,   9,   1,  12,   9, acGUI_FontCordiaNew32_0E16 } // Code 0E16, THAI CHARACTER THO THUNG
  ,{   8,   9,   1,  12,  10, acGUI_FontCordiaNew32_0E17 } // Code 0E17, THAI CHARACTER THO THAHAN
  ,{   6,   9,   1,  12,   8, acGUI_FontCordiaNew32_0E18 } // Code 0E18, THAI CHARACTER THO THONG
  ,{   9,   9,   1,  12,  10, acGUI_FontCordiaNew32_0E19 } // Code 0E19, THAI CHARACTER NO NU
  ,{   8,   9,   1,  12,  10, acGUI_FontCordiaNew32_0E1A } // Code 0E1A, THAI CHARACTER BO BAIMAI
  ,{   8,  14,   1,   7,  10, acGUI_FontCordiaNew32_0E1B } // Code 0E1B, THAI CHARACTER PO PLA
  ,{   7,   9,   1,  12,   9, acGUI_FontCordiaNew32_0E1C } // Code 0E1C, THAI CHARACTER PHO PHUNG
  ,{   7,  14,   1,   7,   9, acGUI_FontCordiaNew32_0E1D } // Code 0E1D, THAI CHARACTER FO FA
  ,{   9,   9,   1,  12,  11, acGUI_FontCordiaNew32_0E1E } // Code 0E1E, THAI CHARACTER PHO PHAN
  ,{   9,  14,   1,   7,  11, acGUI_FontCordiaNew32_0E1F } // Code 0E1F, THAI CHARACTER FO FAN
  ,{   9,   9,   0,  12,  10, acGUI_FontCordiaNew32_0E20 } // Code 0E20, THAI CHARACTER PHO SAMPHAO
  ,{   8,   9,   1,  12,  10, acGUI_FontCordiaNew32_0E21 } // Code 0E21, THAI CHARACTER MO MA
  ,{   7,   9,   1,  12,   9, acGUI_FontCordiaNew32_0E22 } // Code 0E22, THAI CHARACTER YO YAK
  ,{   6,   9,   1,  12,   7, acGUI_FontCordiaNew32_0E23 } // Code 0E23, THAI CHARACTER RO RUA
  ,{   7,  15,   1,  12,   9, acGUI_FontCordiaNew32_0E24 } // Code 0E24, THAI CHARACTER RU
  ,{   7,   9,   1,  12,   9, acGUI_FontCordiaNew32_0E25 } // Code 0E25, THAI CHARACTER LO LING
  ,{   9,  15,   0,  12,  10, acGUI_FontCordiaNew32_0E26 } // Code 0E26, THAI CHARACTER LU
  ,{   6,   9,   1,  12,   8, acGUI_FontCordiaNew32_0E27 } // Code 0E27, THAI CHARACTER WO WAEN
  ,{   8,  10,   1,  11,  10, acGUI_FontCordiaNew32_0E28 } // Code 0E28, THAI CHARACTER SO SALA
  ,{  10,   9,   1,  12,  11, acGUI_FontCordiaNew32_0E29 } // Code 0E29, THAI CHARACTER SO RUSI
  ,{   7,  10,   1,  11,   9, acGUI_FontCordiaNew32_0E2A } // Code 0E2A, THAI CHARACTER SO SUA
  ,{   8,   9,   1,  12,  10, acGUI_FontCordiaNew32_0E2B } // Code 0E2B, THAI CHARACTER HO HIP
  ,{  10,  12,   1,   9,  11, acGUI_FontCordiaNew32_0E2C } // Code 0E2C, THAI CHARACTER LO CHULA
  ,{   7,   9,   1,  12,   9, acGUI_FontCordiaNew32_0E2D } // Code 0E2D, THAI CHARACTER O ANG
  ,{   8,  10,   1,  11,   9, acGUI_FontCordiaNew32_0E2E } // Code 0E2E, THAI CHARACTER HO NOKHUK
  ,{   6,   9,   1,  12,   8, acGUI_FontCordiaNew32_0E2F } // Code 0E2F, THAI CHARACTER PAIYANNOI
  ,{   6,   9,   1,  12,   8, acGUI_FontCordiaNew32_0E30 } // Code 0E30, THAI CHARACTER SARA A
  ,{   7,   3,  -5,   7,   0, acGUI_FontCordiaNew32_0E31 } // Code 0E31, THAI CHARACTER MAI HAN-AKAT
  ,{   6,   9,   1,  12,   8, acGUI_FontCordiaNew32_0E32 } // Code 0E32, THAI CHARACTER SARA AA
  ,{  10,  14,  -3,   7,   8, acGUI_FontCordiaNew32_0E33 } // Code 0E33, THAI CHARACTER SARA AM
  ,{   7,   4,  -8,   6,   0, acGUI_FontCordiaNew32_0E34 } // Code 0E34, THAI CHARACTER SARA I
  ,{   7,   5,  -8,   5,   0, acGUI_FontCordiaNew32_0E35 } // Code 0E35, THAI CHARACTER SARA II
  ,{   7,   6,  -8,   4,   0, acGUI_FontCordiaNew32_0E36 } // Code 0E36, THAI CHARACTER SARA UE
  ,{   7,   5,  -8,   5,   0, acGUI_FontCordiaNew32_0E37 } // Code 0E37, THAI CHARACTER SARA UEE
  ,{   3,   4,  -4,  22,   0, acGUI_FontCordiaNew32_0E38 } // Code 0E38, THAI CHARACTER SARA U
  ,{   5,   4,  -6,  22,   0, acGUI_FontCordiaNew32_0E39 } // Code 0E39, THAI CHARACTER SARA UU
  ,{   2,   2,  -3,  22,   0, acGUI_FontCordiaNew32_0E3A } // Code 0E3A, THAI CHARACTER PHINTHU
  ,{   7,  14,   1,   9,  10, acGUI_FontCordiaNew32_0E3F } // Code 0E3F, THAI CURRENCY SYMBOL BAHT
  ,{   3,   9,   2,  12,   5, acGUI_FontCordiaNew32_0E40 } // Code 0E40, THAI CHARACTER SARA E
  ,{   7,   9,   2,  12,   9, acGUI_FontCordiaNew32_0E41 } // Code 0E41, THAI CHARACTER SARA AE
  ,{   6,  15,   0,   6,   6, acGUI_FontCordiaNew32_0E42 } // Code 0E42, THAI CHARACTER SARA O
  ,{   7,  15,  -1,   6,   6, acGUI_FontCordiaNew32_0E43 } // Code 0E43, THAI CHARACTER SARA AI MAIMUAN
  ,{   7,  16,  -1,   5,   6, acGUI_FontCordiaNew32_0E44 } // Code 0E44, THAI CHARACTER SARA AI MAIMALAI
  ,{   6,  15,   1,  12,   8, acGUI_FontCordiaNew32_0E45 } // Code 0E45, THAI CHARACTER LAKKHANGYAO
  ,{   7,  15,   1,  12,   9, acGUI_FontCordiaNew32_0E46 } // Code 0E46, THAI CHARACTER MAIYAMOK
  ,{   6,   5,  -6,   5,   0, acGUI_FontCordiaNew32_0E47 } // Code 0E47, THAI CHARACTER MAITAIKHU
  ,{   1,   3,  -2,   1,   0, acGUI_FontCordiaNew32_0E48 } // Code 0E48, THAI CHARACTER MAI EK
  ,{   5,   5,  -5,   0,   0, acGUI_FontCordiaNew32_0E49 } // Code 0E49, THAI CHARACTER MAI THO
  ,{   7,   4,  -7,   0,   0, acGUI_FontCordiaNew32_0E4A } // Code 0E4A, THAI CHARACTER MAI TRI
  ,{   5,   4,  -4,   0,   0, acGUI_FontCordiaNew32_0E4B } // Code 0E4B, THAI CHARACTER MAI CHATTAWA
  ,{   6,   5,  -4,   0,   0, acGUI_FontCordiaNew32_0E4C } // Code 0E4C, THAI CHARACTER THANTHAKHAT
  ,{   3,   3,  -4,   7,   0, acGUI_FontCordiaNew32_0E4D } // Code 0E4D, THAI CHARACTER NIKHAHIT
  ,{   5,   5,  -4,   5,   0, acGUI_FontCordiaNew32_0E4E } // Code 0E4E, THAI CHARACTER YAMAKKAN
  ,{   5,   5,   1,  15,   7, acGUI_FontCordiaNew32_0E4F } // Code 0E4F, THAI CHARACTER FONGMAN
  ,{   9,   6,   1,  15,  11, acGUI_FontCordiaNew32_0E50 } // Code 0E50, THAI DIGIT ZERO
  ,{   7,   8,   2,  15,  11, acGUI_FontCordiaNew32_0E51 } // Code 0E51, THAI DIGIT ONE
  ,{   9,   9,   1,  12,  11, acGUI_FontCordiaNew32_0E52 } // Code 0E52, THAI DIGIT TWO
  ,{   9,   6,   1,  15,  11, acGUI_FontCordiaNew32_0E53 } // Code 0E53, THAI DIGIT THREE
  ,{  10,   8,   1,  13,  11, acGUI_FontCordiaNew32_0E54 } // Code 0E54, THAI DIGIT FOUR
  ,{  10,   9,   1,  12,  11, acGUI_FontCordiaNew32_0E55 } // Code 0E55, THAI DIGIT FIVE
  ,{   9,   9,   1,  12,  11, acGUI_FontCordiaNew32_0E56 } // Code 0E56, THAI DIGIT SIX
  ,{  10,   9,   1,  12,  11, acGUI_FontCordiaNew32_0E57 } // Code 0E57, THAI DIGIT SEVEN
  ,{  10,   8,   1,  13,  11, acGUI_FontCordiaNew32_0E58 } // Code 0E58, THAI DIGIT EIGHT
  ,{  10,   9,   1,  12,  11, acGUI_FontCordiaNew32_0E59 } // Code 0E59, THAI DIGIT NINE
  ,{   7,   9,   1,  12,   9, acGUI_FontCordiaNew32_0E5A } // Code 0E5A, THAI CHARACTER ANGKHANKHU
  ,{  17,   8,   1,  13,  18, acGUI_FontCordiaNew32_0E5B } // Code 0E5B, THAI CHARACTER KHOMUT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontCordiaNew32_Prop3 = {
   0x0E3F                                   // First character
  ,0x0E5B                                   // Last character 
  ,&GUI_FontCordiaNew32_CharInfo[154]       // Address of first character
  ,(GUI_CONST_STORAGE GUI_FONT_PROP_EXT *)0 // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontCordiaNew32_Prop2 = {
   0x0E00                             // First character
  ,0x0E3A                             // Last character 
  ,&GUI_FontCordiaNew32_CharInfo[ 95] // Address of first character
  ,&GUI_FontCordiaNew32_Prop3         // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontCordiaNew32_Prop1 = {
   0x0020                             // First character
  ,0x007E                             // Last character 
  ,&GUI_FontCordiaNew32_CharInfo[  0] // Address of first character
  ,&GUI_FontCordiaNew32_Prop2         // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT GUI_FontCordiaNew32 = {
   GUI_FONTTYPE_PROP_EXT // Type of font   
  ,32                    // Height of font 
  ,32                    // Space of font y
  ,1                     // Magnification x
  ,1                     // Magnification y
  ,{&GUI_FontCordiaNew32_Prop1}
  ,21                    // Baseline
  ,8                     // Height of lowercase characters
  ,11                    // Height of capital characters
};

/*******************************************************************
*
*       Thai text samples
*/
static char * _apText[] = {
  "How are you?\n\xe0\xb8\xaa\xe0\xb8\x9a\xe0\xb8\xb2\xe0\xb8\xa2\xe0\xb8\x94\xe0\xb8\xb5\xe0\xb8\xab\xe0\xb8\xa3\xe0\xb8\xb7\xe0\xb8\xad",
  "Fine, and you?\n\xe0\xb8\xaa\xe0\xb8\x9a\xe0\xb8\xb2\xe0\xb8\xa2\xe0\xb8\x94\xe0\xb8\xb5 \xe0\xb9\x81\xe0\xb8\xa5\xe0\xb9\x89\xe0\xb8\xa7\xe0\xb8\x84\xe0\xb8\xb8\xe0\xb8\x93\xe0\xb8\xab\xe0\xb8\xa5\xe0\xb9\x88\xe0\xb8\xb0\xe0\xb8\x84\xe0\xb8\xa3\xe0\xb8\xb1\xe0\xb8\x9a",
  "Nice to meet you.\n\xe0\xb8\xa2\xe0\xb8\xb4\xe0\xb8\x99\xe0\xb8\x94\xe0\xb8\xb5\xe0\xb8\x97\xe0\xb8\xb5\xe0\xb9\x88\xe0\xb9\x84\xe0\xb8\x94\xe0\xb9\x89\xe0\xb8\xa3\xe0\xb8\xb9\xe0\xb9\x89\xe0\xb8\x88\xe0\xb8\xa3\xe0\xb8\xb1\xe0\xb8\x81",
  "You're welcome.\n\xe0\xb9\x84\xe0\xb8\xa1\xe0\xb9\x88\xe0\xb9\x80\xe0\xb8\x9b\xe0\xb9\x87\xe0\xb8\x99\xe0\xb9\x84\xe0\xb8\xa3",
  "I can't speak Thai\n\xe0\xb8\x9e\xe0\xb8\xb9\xe0\xb8\x94\xe0\xb8\xa0\xe0\xb8\xb2\xe0\xb8\xa9\xe0\xb8\xb2\xe0\xb9\x84\xe0\xb8\x97\xe0\xb8\xa2\xe0\xb9\x84\xe0\xb8\xa1\xe0\xb9\x84\xe0\xb8\x94",
  "Do you speak English?\n\xe0\xb8\x9e\xe0\xb8\xb9\xe0\xb8\x94\xe0\xb8\xa0\xe0\xb8\xb2\xe0\xb8\xa9\xe0\xb8\xb2\xe0\xb8\xad\xe0\xb8\xb1\xe0\xb8\x87\xe0\xb8\x81\xe0\xb8\xa4\xe0\xb8\xa9\xe0\xb9\x84\xe0\xb8\x94\xe0\xb9\x89\xe0\xb9\x84\xe0\xb8\xab\xe0\xb8\xa1",
  "Thank you very much.\n\xe0\xb8\x82\xe0\xb8\xad\xe0\xb8\x9a\xe0\xb8\x84\xe0\xb8\xb8\xe0\xb8\x93\xe0\xb8\xa1\xe0\xb8\xb2\xe0\xb8\x81",
  "How do you say this in Thai?\n\xe0\xb8\x9e\xe0\xb8\xb9\xe0\xb8\x94\xe0\xb9\x80\xe0\xb8\x9b\xe0\xb9\x87\xe0\xb8\x99\xe0\xb8\xa0\xe0\xb8\xb2\xe0\xb8\xa9\xe0\xb8\xb2\xe0\xb9\x84\xe0\xb8\x97\xe0\xb8\xa2\xe0\xb8\xad\xe0\xb8\xa2\xe0\xb9\x88\xe0\xb8\xb2\xe0\xb8\x87\xe0\xb9\x84\xe0\xb8\xa3",
};

/********************************************************************
*
*       Static code
*
*********************************************************************
*/
/*******************************************************************
*
*       _ShowThaiTextSamples
*/
static void _ShowThaiTextSamples(void) {
  GUI_RECT Rect = {100, 60, 219, 199};
  GUI_SetFont(&GUI_FontCordiaNew32); // Set thai font
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
  //
  // Lable the sample
  //
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("Thai language sample", 160, 5);
  //
  // Call demo loop
  //
  _ShowThaiTextSamples();
}

/*************************** End of file ****************************/

