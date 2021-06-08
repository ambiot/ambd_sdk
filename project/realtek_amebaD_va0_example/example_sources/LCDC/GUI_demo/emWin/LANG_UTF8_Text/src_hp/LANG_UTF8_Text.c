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
File        : LANG_UTF8_Text.c
Purpose     : Sample application which shows how text resource files
              can be used to display different languages using UTF-8.
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include "GUI.h"

#define SPACE_TO_TOP  40
#define CRLF          "\r\n"      // Carriage Return = '\r' - Line Feed = '\n'

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
*       _GUI_FontJapanese_headline16
*
**********************************************************************
*/
static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_headline16_4EBA[ 28] = { // Code 4EBA
  _______X,XX______,
  _______X,X_______,
  _______X,X_______,
  _______X,X_______,
  ______XX,XX______,
  ______XX,XX______,
  ______XX,XX______,
  _____XX_,_XX_____,
  _____XX_,_XX_____,
  ____XX__,__XX____,
  ____XX__,__XX____,
  ___XX___,___XX___,
  __XX____,____XX__,
  XXX_____,_____XXX};

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

static GUI_CONST_STORAGE GUI_CHARINFO_EXT _GUI_FontJapanese_headline16_CharInfo[3] = {
   {  16,  14,   0,   1,  17, _acGUI_FontJapanese_headline16_4EBA } // Code 4EBA
  ,{  11,  14,   3,   1,  17, _acGUI_FontJapanese_headline16_65E5 } // Code 65E5
  ,{  16,  15,   0,   0,  17, _acGUI_FontJapanese_headline16_672C } // Code 672C
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_headline16_Prop3 = {
   0x672C                                      // First character
  ,0x672C                                      // Last character 
  ,&_GUI_FontJapanese_headline16_CharInfo[  2] // Address of first character
  ,(GUI_CONST_STORAGE GUI_FONT_PROP_EXT *)0    // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_headline16_Prop2 = {
   0x65E5                                      // First character
  ,0x65E5                                      // Last character 
  ,&_GUI_FontJapanese_headline16_CharInfo[  1] // Address of first character
  ,&_GUI_FontJapanese_headline16_Prop3         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_headline16_Prop1 = {
   0x4EBA                                      // First character
  ,0x4EBA                                      // Last character 
  ,&_GUI_FontJapanese_headline16_CharInfo[  0] // Address of first character
  ,&_GUI_FontJapanese_headline16_Prop2         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT _GUI_FontJapanese_headline16 = {
   GUI_FONTTYPE_PROP_EXT // Type of font   
  ,16                    // Height of font 
  ,16                    // Space of font y
  ,1                     // Magnification x
  ,1                     // Magnification y
  ,{&_GUI_FontJapanese_headline16_Prop1}
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
// Start of unicode area <Hiragana>
//
static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_3055[ 28] = { // Code 3055, HIRAGANA LETTER SA
  _____XX_,________,
  ______X_,________,
  ______X_,________,
  X______X,_XX_____,
  _XXXXXXX,X_______,
  _______X,________,
  ________,X_______,
  __XXXXX_,X_______,
  _X_____X,XX______,
  X_______,_X______,
  X_______,________,
  X_______,________,
  _XX_____,________,
  ___XXXXX,________};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_3056[ 28] = { // Code 3056, HIRAGANA LETTER ZA
  _____XX_,___X____,
  ______X_,_X__X___,
  ______X_,__X_____,
  X______X,_X______,
  _XXXXXXX,X_______,
  _______X,________,
  ________,X_______,
  __XXXXX_,X_______,
  _X_____X,XX______,
  X_______,_X______,
  X_______,________,
  X_______,________,
  _XX_____,________,
  ___XXXXX,________};

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
// Start of unicode area <Katakana>
//
static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_30B5[ 26] = { // Code 30B5, KATAKANA LETTER SA
  ________,XX______,
  ___XX___,_X______,
  ____X___,_X__X___,
  X___XXXX,XXXXXX__,
  _XXXX___,_X______,
  ____X___,_X______,
  ____X___,_X______,
  ____X___,_X______,
  ________,_X______,
  ________,X_______,
  ________,X_______,
  _______X,________,
  _____XX_,________};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_30C8[ 13] = { // Code 30C8, KATAKANA LETTER TO
  XX______,
  _XX_____,
  _X______,
  _X______,
  _X______,
  _XXX____,
  _X__XX__,
  _X___XX_,
  _X____X_,
  _X______,
  _X______,
  _X______,
  _X______};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_30DD[ 28] = { // Code 30DD, KATAKANA LETTER PO
  ________,___XX___,
  _____XX_,__X__X__,
  ______XX,__X__X__,
  ______X_,___XX___,
  XXXXXXXX,XXXX____,
  _X____X_,________,
  ______X_,________,
  __X___X_,_X______,
  __X___X_,__X_____,
  _X____X_,___X____,
  XX_X__X_,___XX___,
  X___X_X_,____X___,
  _____XX_,________,
  _____X__,________};

static GUI_CONST_STORAGE unsigned char _acGUI_FontJapanese_text16_30FC[  6] = { // Code 30FC, KATAKANA-HIRAGANA PROLONGED SOUND MARK
  ________,___X____,
  XX____XX,XXXXX___,
  _XXXXX__,________};

//
// Start of unicode area <CJK Unified Ideographs>
//
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

static GUI_CONST_STORAGE GUI_CHARINFO_EXT _GUI_FontJapanese_text16_CharInfo[15] = {
   {   7,  13,   0,   1,   8, _acGUI_FontJapanese_text16_0057 } // Code 0057, LATIN CAPITAL LETTER W
  ,{   6,   8,   1,   6,   8, _acGUI_FontJapanese_text16_0065 } // Code 0065, LATIN SMALL LETTER E
  ,{   3,  12,   2,   2,   8, _acGUI_FontJapanese_text16_0069 } // Code 0069, LATIN SMALL LETTER I
  ,{   7,   8,   0,   6,   8, _acGUI_FontJapanese_text16_006D } // Code 006D, LATIN SMALL LETTER M
  ,{   7,   8,   0,   6,   8, _acGUI_FontJapanese_text16_006E } // Code 006E, LATIN SMALL LETTER N
  ,{  11,  14,   2,   0,  16, _acGUI_FontJapanese_text16_3055 } // Code 3055, HIRAGANA LETTER SA
  ,{  13,  14,   2,   0,  16, _acGUI_FontJapanese_text16_3056 } // Code 3056, HIRAGANA LETTER ZA
  ,{  13,  14,   1,   0,  16, _acGUI_FontJapanese_text16_306A } // Code 306A, HIRAGANA LETTER NA
  ,{  12,  14,   1,   1,  16, _acGUI_FontJapanese_text16_307E } // Code 307E, HIRAGANA LETTER MA
  ,{  14,  13,   0,   1,  16, _acGUI_FontJapanese_text16_30B5 } // Code 30B5, KATAKANA LETTER SA
  ,{   7,  13,   5,   1,  16, _acGUI_FontJapanese_text16_30C8 } // Code 30C8, KATAKANA LETTER TO
  ,{  14,  14,   1,   0,  16, _acGUI_FontJapanese_text16_30DD } // Code 30DD, KATAKANA LETTER PO
  ,{  13,   3,   1,   6,  16, _acGUI_FontJapanese_text16_30FC } // Code 30FC, KATAKANA-HIRAGANA PROLONGED SOUND MARK
  ,{  13,  15,   1,   0,  16, _acGUI_FontJapanese_text16_8A00 } // Code 8A00
  ,{  15,  15,   0,   0,  16, _acGUI_FontJapanese_text16_8A9E } // Code 8A9E
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop13 = {
   0x8A9E                                   // First character
  ,0x8A9E                                   // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[ 14]  // Address of first character
  ,(GUI_CONST_STORAGE GUI_FONT_PROP_EXT *)0 // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop12 = {
   0x8A00                                  // First character
  ,0x8A00                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[ 13] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop13        // Pointer to next GUI_FONT_PROP_EXT
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop11 = {
   0x30FC                                  // First character
  ,0x30FC                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[ 12] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop12        // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop10 = {
   0x30DD                                  // First character
  ,0x30DD                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[ 11] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop11        // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop9 = {
   0x30C8                                  // First character
  ,0x30C8                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[ 10] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop10        // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop8 = {
   0x30B5                                  // First character
  ,0x30B5                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[  9] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop9         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop7 = {
   0x307E                                  // First character
  ,0x307E                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[  8] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop8         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop6 = {
   0x306A                                  // First character
  ,0x306A                                  // Last character 
  ,&_GUI_FontJapanese_text16_CharInfo[  7] // Address of first character
  ,&_GUI_FontJapanese_text16_Prop7         // Pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT _GUI_FontJapanese_text16_Prop5 = {
   0x3055                                  // First character
  ,0x3056                                  // Last character 
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
   GUI_FONTTYPE_PROP_EXT // Type of font   
  ,16                    // Height of font 
  ,16                    // Space of font y
  ,1                     // Magnification x
  ,1                     // Magnification y
  ,{&_GUI_FontJapanese_text16_Prop1}
  ,14                    // Baseline
  ,8                     // Height of lowercase characters
  ,13                    // Height of capital characters
};

/*********************************************************************
*
*       Language texts
*
**********************************************************************
*/
static U8 _acLangGer[] = {
  "Deutsch"CRLF
  "emWin"CRLF
  "unterst\xc3\xbctzt"CRLF
  "verschiedene"CRLF
  "Sprachen"
};

static U8 _acLangEng[] = {
  "English"CRLF
  "emWin"CRLF
  "supports"CRLF
  "different"CRLF
  "languages"CRLF
};

static U8 _acLangJap[] = {
  "\xe6\x97\xa5\xe6\x9c\xac\xe4\xba\xba"CRLF
  "emWin"CRLF
  "\xe3\x82\xb5\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x88"CRLF
  "\xe3\x81\x95\xe3\x81\xbe\xe3\x81\x96\xe3\x81\xbe\xe3\x81\xaa"CRLF
  "\xe8\xa8\x80\xe8\xaa\x9e"CRLF
};

/*********************************************************************
*
*       Language context
*
**********************************************************************
*/
typedef struct {
  U8             * pLanguage;
  U32              NumChars;
  const GUI_FONT * pFontHeadline;
  const GUI_FONT * pFontBody;
} LANGUAGE_CONTEXT;

static LANGUAGE_CONTEXT _Languages[] = {
  { _acLangGer, sizeof(_acLangGer), &GUI_Font16B_1,                &GUI_Font16_1  },
  { _acLangEng, sizeof(_acLangEng), &GUI_Font16B_1,                &GUI_Font16_1  },
  { _acLangJap, sizeof(_acLangJap), &_GUI_FontJapanese_headline16, &_GUI_FontJapanese_text16 }
};

static U8 _NumLanguages = GUI_COUNTOF(_Languages);

/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  const char * pText;
  GUI_RECT     Rect;
  int          xItemSize;
  int          yItemSize;
  int          NumItems;
  int          LangCnt;
  int          ItemCnt;
  int          xSize;
  int          ySize;

  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  xSize   = LCD_GetXSize();
  ySize   = LCD_GetYSize();
  Rect.x0 = 0;
  Rect.y0 = 0;
  Rect.x1 = xSize        - 1;
  Rect.y1 = SPACE_TO_TOP - 1;
  GUI_SetFont(&GUI_Font20B_1);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetBkColor(GUI_DARKBLUE);
  GUI_ClearRectEx(&Rect);
  GUI_DispStringInRect("emWin - Language Resources", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
  GUI_DrawGradientV(0, SPACE_TO_TOP, xSize - 1, ySize - 1, GUI_DARKBLUE, GUI_DARKGRAY);
  GUI_UC_SetEncodeUTF8();
  GUI_LANG_SetMaxNumLang(_NumLanguages);
  for (LangCnt = 0; LangCnt < _NumLanguages; LangCnt++) {
    GUI_LANG_LoadText(_Languages[LangCnt].pLanguage, _Languages[LangCnt].NumChars, LangCnt);
    xItemSize = xSize / _NumLanguages;
    Rect.x0   = LangCnt * xItemSize;
    Rect.x1   = Rect.x0 + xItemSize;
    NumItems  = GUI_LANG_GetNumItems(LangCnt);
    yItemSize = (ySize - SPACE_TO_TOP) / NumItems;
    for (ItemCnt = 0; ItemCnt < NumItems; ItemCnt++) {
      pText   = GUI_LANG_GetTextEx(ItemCnt, LangCnt);
      Rect.y0 = SPACE_TO_TOP + (ItemCnt * yItemSize);
      Rect.y1 = Rect.y0 + yItemSize;
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

/*************************** End of file ****************************/
