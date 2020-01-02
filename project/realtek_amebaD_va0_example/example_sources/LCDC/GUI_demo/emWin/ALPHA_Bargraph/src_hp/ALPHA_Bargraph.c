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
File        : ALPHA_Bargraph.c
Purpose     : Shows a bargraph with alpha effect
Requirements: WindowManager - ( )
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include <math.h>
#include <stddef.h>
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
#define RECOMMENDED_MEMORY (1024L * 100)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/*********************************************************************
*
*       Antialiased digit font for labeling
*/
GUI_CONST_STORAGE unsigned char acGUI_FontD9_AA4_0030[ 36] = { // Code 0030, DIGIT ZERO
  0x07, 0xEF, 0x91, 0x00,
  0x4F, 0xCA, 0xF7, 0x00,
  0x8F, 0x20, 0xDC, 0x00,
  0xBF, 0x00, 0xBF, 0x00,
  0xBF, 0x00, 0xBF, 0x00,
  0xBF, 0x00, 0xBF, 0x00,
  0x7F, 0x41, 0xEB, 0x00,
  0x2F, 0xED, 0xF6, 0x00,
  0x04, 0xAB, 0x60, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontD9_AA4_0031[ 27] = { // Code 0031, DIGIT ONE
  0x00, 0xAF, 0x00,
  0x19, 0xFF, 0x00,
  0xEE, 0xDF, 0x00,
  0x82, 0xBF, 0x00,
  0x00, 0xBF, 0x00,
  0x00, 0xBF, 0x00,
  0x00, 0xBF, 0x00,
  0x00, 0xBF, 0x00,
  0x00, 0x8B, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontD9_AA4_0032[ 36] = { // Code 0032, DIGIT TWO
  0x06, 0xEF, 0xC3, 0x00,
  0x3F, 0xC8, 0xFD, 0x00,
  0x5B, 0x30, 0xBF, 0x00,
  0x00, 0x01, 0xEB, 0x00,
  0x00, 0x1C, 0xE3, 0x00,
  0x01, 0xCE, 0x30, 0x00,
  0x0B, 0xE3, 0x00, 0x00,
  0x6F, 0xFF, 0xFF, 0x00,
  0x8B, 0xBB, 0xBB, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontD9_AA4_0033[ 36] = { // Code 0033, DIGIT THREE
  0x3B, 0xFD, 0x30, 0x00,
  0xAF, 0x8E, 0xD0, 0x00,
  0x46, 0x0C, 0xE0, 0x00,
  0x00, 0xBE, 0x50, 0x00,
  0x00, 0x7C, 0xC1, 0x00,
  0x00, 0x05, 0xF7, 0x00,
  0xB9, 0x06, 0xF7, 0x00,
  0xAF, 0xCF, 0xE1, 0x00,
  0x18, 0xB9, 0x20, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontD9_AA4_0034[ 36] = { // Code 0034, DIGIT FOUR
  0x00, 0x0C, 0xF0, 0x00,
  0x00, 0x7F, 0xF0, 0x00,
  0x04, 0xFE, 0xF0, 0x00,
  0x1D, 0x8B, 0xF0, 0x00,
  0x8D, 0x1B, 0xF0, 0x00,
  0xBA, 0x7D, 0xF7, 0x00,
  0xBF, 0xFF, 0xFF, 0x00,
  0x00, 0x0B, 0xF0, 0x00,
  0x00, 0x08, 0xB0, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontD9_AA4_0035[ 36] = { // Code 0035, DIGIT FIVE
  0x05, 0xFF, 0xFB, 0x00,
  0x07, 0xFC, 0xB8, 0x00,
  0x0B, 0xF0, 0x00, 0x00,
  0x0E, 0xFE, 0xD5, 0x00,
  0x2F, 0xD7, 0xEE, 0x10,
  0x02, 0x10, 0x7F, 0x40,
  0x5F, 0x60, 0x9F, 0x30,
  0x2E, 0xFB, 0xFB, 0x00,
  0x03, 0x9B, 0x71, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontD9_AA4_0036[ 36] = { // Code 0036, DIGIT SIX
  0x05, 0xDF, 0xB1, 0x00,
  0x2F, 0xCA, 0xF7, 0x00,
  0x8F, 0x10, 0x74, 0x00,
  0xBE, 0x7B, 0x70, 0x00,
  0xBF, 0xDC, 0xF8, 0x00,
  0xBF, 0x10, 0xCF, 0x00,
  0x7F, 0x20, 0xCF, 0x00,
  0x2E, 0xEC, 0xF8, 0x00,
  0x03, 0xAB, 0x70, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontD9_AA4_0037[ 36] = { // Code 0037, DIGIT SEVEN
  0xBF, 0xFF, 0xFB, 0x00,
  0x8B, 0xBC, 0xF8, 0x00,
  0x00, 0x0C, 0xB0, 0x00,
  0x00, 0x7F, 0x20, 0x00,
  0x00, 0xE9, 0x00, 0x00,
  0x06, 0xF5, 0x00, 0x00,
  0x0A, 0xF1, 0x00, 0x00,
  0x0D, 0xC0, 0x00, 0x00,
  0x0B, 0x80, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontD9_AA4_0038[ 36] = { // Code 0038, DIGIT EIGHT
  0x08, 0xEF, 0xA1, 0x00,
  0x6F, 0x97, 0xF9, 0x00,
  0x7F, 0x40, 0xFB, 0x00,
  0x2D, 0xCA, 0xE5, 0x00,
  0x1B, 0xDC, 0xD3, 0x00,
  0x9F, 0x20, 0xDD, 0x00,
  0xBF, 0x10, 0xCF, 0x00,
  0x5F, 0xB8, 0xF9, 0x00,
  0x05, 0xAB, 0x70, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontD9_AA4_0039[ 36] = { // Code 0039, DIGIT NINE
  0x08, 0xFF, 0x80, 0x00,
  0x7F, 0xA9, 0xF7, 0x00,
  0xBF, 0x00, 0xCC, 0x00,
  0xAF, 0x31, 0xDF, 0x00,
  0x3E, 0xFF, 0xEF, 0x00,
  0x02, 0x76, 0xBF, 0x00,
  0x4B, 0x40, 0xDA, 0x00,
  0x3F, 0xED, 0xF5, 0x00,
  0x05, 0xBA, 0x40, 0x00
};

GUI_CONST_STORAGE GUI_CHARINFO GUI_FontD9_AA4_CharInfo[10] = {
   {   7,   7,  4, acGUI_FontD9_AA4_0030 } // Code 0030
  ,{   5,   5,  3, acGUI_FontD9_AA4_0031 } // Code 0031
  ,{   7,   7,  4, acGUI_FontD9_AA4_0032 } // Code 0032
  ,{   7,   7,  4, acGUI_FontD9_AA4_0033 } // Code 0033
  ,{   7,   7,  4, acGUI_FontD9_AA4_0034 } // Code 0034
  ,{   7,   7,  4, acGUI_FontD9_AA4_0035 } // Code 0035
  ,{   7,   7,  4, acGUI_FontD9_AA4_0036 } // Code 0036
  ,{   7,   7,  4, acGUI_FontD9_AA4_0037 } // Code 0037
  ,{   7,   7,  4, acGUI_FontD9_AA4_0038 } // Code 0038
  ,{   7,   7,  4, acGUI_FontD9_AA4_0039 } // Code 0039
};

GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontD9_AA4_Prop1 = {
   0x0030 // first character
  ,0x0039 // last character 
  ,&GUI_FontD9_AA4_CharInfo[  0] // address of first character
  ,(GUI_CONST_STORAGE GUI_FONT_PROP *)0 // pointer to next GUI_FONT_PROP
};

GUI_CONST_STORAGE GUI_FONT GUI_FontD9_AA4 = {
   GUI_FONTTYPE_PROP_AA4 // type of font   
  ,9 // height of font 
  ,9 // space of font y
  ,1 // magnification x
  ,1 // magnification y
  ,{&GUI_FontD9_AA4_Prop1}
  ,0 // Baseline
  ,0 // Height of lowercase characters
  ,0 // Height of capital characters
};

/*********************************************************************
*
*       Alpha bitmap for the orange dot at the left of the diagramm
*/
static GUI_CONST_STORAGE unsigned long _acCircleOrange_14x14[] = {
#if (GUI_USE_ARGB)
  0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x05F39400, 0x79F39400, 0x86F39400, 0xEBF39400, 0xEBF39400, 0x86F39400, 0x79F39400, 0x05F39400, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
  0x00FFFFFF, 0x00FFFFFF, 0x46F39400, 0xBAF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xBAF39400, 0x46F39400, 0x00FFFFFF, 0x00FFFFFF,
  0x00FFFFFF, 0x03F39400, 0xFAF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFAF39400, 0x03F39400, 0x00FFFFFF,
  0x0EF39400, 0xC1F39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xC1F39400, 0x0EF39400,
  0x78F39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0x78F39400,
  0x89F39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0x89F39400,
  0xEBF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xEBF39400,
  0xEBF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xEBF39400,
  0x89F39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0x89F39400,
  0x78F39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0x78F39400,
  0x0EF39400, 0xC1F39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xC1F39400, 0x0EF39400,
  0x00FFFFFF, 0x03F39400, 0xFAF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFAF39400, 0x03F39400, 0x00FFFFFF,
  0x00FFFFFF, 0x00FFFFFF, 0x46F39400, 0xBAF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xFFF39400, 0xBAF39400, 0x46F39400, 0x00FFFFFF, 0x00FFFFFF,
  0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x05F39400, 0x79F39400, 0x86F39400, 0xEBF39400, 0xEBF39400, 0x86F39400, 0x79F39400, 0x05F39400, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
#else
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFA0094F3, 0x860094F3, 0x790094F3, 0x140094F3, 0x140094F3, 0x790094F3, 0x860094F3, 0xFA0094F3, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xB90094F3, 0x450094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x450094F3, 0xB90094F3, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xC10094F3, 0x050094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x050094F3, 0xC10094F3, 0xFFFFFFFF,
  0xF10094F3, 0x3E0094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x3E0094F3, 0xF10094F3,
  0x870094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x870094F3,
  0x760094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x760094F3,
  0x140094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x140094F3,
  0x140094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x140094F3,
  0x760094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x760094F3,
  0x870094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x870094F3,
  0xF10094F3, 0x3E0094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x3E0094F3, 0xF10094F3,
  0xFFFFFFFF, 0xC10094F3, 0x050094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x050094F3, 0xC10094F3, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xB90094F3, 0x450094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x000094F3, 0x450094F3, 0xB90094F3, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFA0094F3, 0x860094F3, 0x790094F3, 0x140094F3, 0x140094F3, 0x790094F3, 0x860094F3, 0xFA0094F3, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
#endif
};

static GUI_CONST_STORAGE GUI_BITMAP _bmCircleOrange_14x14 = {
  14, // XSize
  14, // YSize
  56, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)_acCircleOrange_14x14,  // Pointer to picture data
  NULL  // Pointer to palette
#if (GUI_USE_ARGB)
 ,GUI_DRAW_BMPM8888I
#else
 ,GUI_DRAW_BMP8888
#endif
};

/*********************************************************************
*
*       Bitmaps for drawing the bars
*/
static GUI_CONST_STORAGE GUI_COLOR ColorsBarOrange_12x1[] = {
#if (GUI_USE_ARGB)
  0xFFE26822,0xFFEC8537,0xFFEF9F50,0xFFF1974B,
  0xFFF3B163,0xFFF3B569,0xFFF5B971,0xFFF7BD7B,
  0xFFF8C486,0xFFFAC88D,0xFFFCDEBA,0xFFFEE9D5,
#else
  0x2268E2,0x3785EC,0x509FEF,0x4B97F1,
  0x63B1F3,0x69B5F3,0x71B9F5,0x7BBDF7,
  0x86C4F8,0x8DC8FA,0xBADEFC,0xD5E9FE,
#endif
};

static GUI_CONST_STORAGE GUI_COLOR ColorsBarBluegreen_12x1[] = {
#if (GUI_USE_ARGB)
  0xFF2D6E74,0xFF3E8F91,0xFF419095,0xFF479197,
  0xFF50969B,0xFF5E9CA1,0xFF6DA5A9,0xFF82B1B2,
  0xFF98BEBF,0xFF9AC2C3,0xFFB3CFCF,0xFFD4E3E1,
#else
  0x746E2D,0x918F3E,0x959041,0x979147,
  0x9B9650,0xA19C5E,0xA9A56D,0xB2B182,
  0xBFBE98,0xC3C29A,0xCFCFB3,0xE1E3D4,
#endif
};

static GUI_CONST_STORAGE GUI_COLOR ColorsBarBlue_12x1[] = {
#if (GUI_USE_ARGB)
  0xFF005182,0xFF2C94C3,0xFF3F95CE,0xFF4A96CD,
  0xFF569BCF,0xFF65A4D4,0xFF76ADDA,0xFF86B9E0,
  0xFF96C4E4,0xFFA7D1EB,0xFFA8D1EA,0xFFBFE1F4,
#else
  0x825100,0xC3942C,0xCE953F,0xCD964A,
  0xCF9B56,0xD4A465,0xDAAD76,0xE0B986,
  0xE4C496,0xEBD1A7,0xEAD1A8,0xF4E1BF,
#endif
};

static GUI_CONST_STORAGE GUI_LOGPALETTE PalBarOrange_12x1 = {
  12, // number of entries
  0,  // No transparency
  &ColorsBarOrange_12x1[0]
};

static GUI_CONST_STORAGE GUI_LOGPALETTE PalBarBluegreen_12x1 = {
  12, // number of entries
  0,  // No transparency
  &ColorsBarBluegreen_12x1[0]
};

static GUI_CONST_STORAGE GUI_LOGPALETTE PalBarBlue_12x1 = {
  12, // number of entries
  0,  // No transparency
  &ColorsBarBlue_12x1[0]
};

static GUI_CONST_STORAGE unsigned char _acBarOrange_12x1[] = {
  0x3B, 0xA9, 0x87, 0x65, 0x42, 0x10
};

static GUI_CONST_STORAGE unsigned char _acBarBluegreen_12x1[] = {
  0x09, 0xBA, 0x87, 0x65, 0x43, 0x21
};

static GUI_CONST_STORAGE unsigned char _acBarBlue_12x1[] = {
  0x01, 0xAB, 0x98, 0x76, 0x54, 0x32
};

static GUI_CONST_STORAGE GUI_BITMAP _bmBarOrange_12x1 = {
  12,                 // XSize
  1,                  // YSize
  6,                  // BytesPerLine
  4,                  // BitsPerPixel
  _acBarOrange_12x1,  // Pointer to picture data (indices)
  &PalBarOrange_12x1  // Pointer to palette
};

static GUI_CONST_STORAGE GUI_BITMAP _bmBarBluegreen_12x1 = {
  12,                    // XSize
  1,                     // YSize
  6,                     // BytesPerLine
  4,                     // BitsPerPixel
  _acBarBluegreen_12x1,  // Pointer to picture data (indices)
  &PalBarBluegreen_12x1  // Pointer to palette
};

static GUI_CONST_STORAGE GUI_BITMAP _bmBarBlue_12x1 = {
  12,               // XSize
  1,                // YSize
  6,                // BytesPerLine
  4,                // BitsPerPixel
  _acBarBlue_12x1,  // Pointer to picture data (indices)
  &PalBarBlue_12x1  // Pointer to palette
};

static GUI_CONST_STORAGE GUI_BITMAP * _apBmBar[] = {
  &_bmBarBlue_12x1,
  &_bmBarBluegreen_12x1,
  &_bmBarOrange_12x1
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawDiagramAt
*/
static void _DrawDiagramAt(int xPos, int yPos, int * py, int xBlend, GUI_MEMDEV_Handle hMemTrans) {
  static GUI_MEMDEV_Handle hMem;
  GUI_RECT Rect;
  int i, ySizeBar, IndexBmBar, FontSizeY, x0, y0;
  //
  // Create memory device
  //
  if (hMem == 0) {
    hMem = GUI_MEMDEV_Create(xPos - 7, yPos, 172 + 7 + 1, 122 + 1);
    if (hMem == 0) {
      return; // Not enough memory available
    }
  }
  GUI_MEMDEV_Select(hMem);
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  //
  // Draw blue background
  //
  GUI_SetColor(GUI_MAKE_COLOR(0x4a2210));
  GUI_FillRoundedRect(xPos, yPos, xPos + 172, yPos + 122, 4);
  //
  // Draw grid lines
  //
  GUI_SetColor(GUI_MAKE_COLOR(0x774830));
  for (i = 0; i < 12; i++) {
    GUI_DrawHLine(yPos + 6 + i * 10, xPos + 2, xPos + 172 - 2);
  }
  //
  // Draw bars
  //
  for (i = 0; i < 10; i++) {
    IndexBmBar = (i < 6) ? i / 2 : 4 - (i / 2);
    ySizeBar = *(py + i);
    GUI_DrawBitmapMag(_apBmBar[IndexBmBar], xPos + 8 + i * 16, yPos + 122 - ySizeBar - 6, 1, ySizeBar);
  }
  //
  // Draw alpha effect
  //
  Rect.x0 = xPos;
  Rect.x1 = xPos + xBlend;
  Rect.y0 = yPos;
  Rect.y1 = yPos + 122;
  GUI_SetClipRect(&Rect);
  GUI_MEMDEV_WriteAt(hMemTrans, xPos, yPos);
  GUI_SetClipRect(NULL);
  //
  // Draw orange frame
  //
  GUI_SetColor(GUI_MAKE_COLOR(0x00f39400));
  GUI_DrawRoundedRect(xPos, yPos, xPos + 172, yPos + 122, 4);
  //
  // Label
  //
  GUI_SetFont(&GUI_FontD9_AA4);
  GUI_SetTextMode(GUI_TM_TRANS);
  FontSizeY = GUI_GetFontSizeY();
  for (i = 0; i < 5; i++) {
    x0 = xPos - 7;
    y0 = yPos + 96 - i * 20 - 7;
    GUI_SetBkColor(GUI_BLACK);
    GUI_ClearRect(x0, y0, x0 + 6, y0 + 13);
    GUI_DrawBitmap(&_bmCircleOrange_14x14, x0, y0);
    GUI_GotoXY(x0 + 7, y0 + 7 - FontSizeY / 2);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_SetColor(GUI_BLACK);
    GUI_DispDecMin((i + 1) * 2);
  }
  GUI_MEMDEV_CopyToLCD(hMem);
}

/*********************************************************************
*
*       _DemoBarGraph
*/
static void _DemoBarGraph(void) {
  int xSize;
  int ySize;
  int xPos;
  int yPosDiagram;
  int yPosText;
  int i;
  int ayOrg[] = { 10, 20, 40, 50, 90, 100, 80, 30, 20, 10 };
  int ayCur[] = { 10, 20, 40, 50, 90, 100, 80, 30, 20, 10 };
  int aAdd[GUI_COUNTOF(ayOrg)];
  int TimeNext;
  int TimeNow;
  int AddBlend;
  int Blend;
  int NumItems;
  GUI_MEMDEV_Handle hMemTrans;
  U32 * pData;

  AddBlend = 1;
  Blend    = 64;
  NumItems = GUI_COUNTOF(ayOrg);
  //
  // Calculate positions
  //
  xSize       = LCD_GetXSize();
  ySize       = LCD_GetYSize();
  xPos        = (xSize - 172) / 2;
  yPosText    = (ySize - 122 - 24) / 3;
  yPosDiagram = yPosText * 2 + 24;
  //
  // Label demo
  //
  GUI_SetFont(&GUI_Font24B_ASCII);
  GUI_DispStringHCenterAt("emWin bargraph demo", xSize / 2, yPosText);
  hMemTrans = GUI_MEMDEV_CreateFixed32(xPos, yPosDiagram, 172, 122);
  pData = GUI_MEMDEV_GetDataPtr(hMemTrans);
  GUI_MEMDEV_Select(hMemTrans);
  GUI_SetBkColor(GUI_TRANSPARENT);
  GUI_Clear();
  GUI_SetColor(GUI_MAKE_COLOR(0xa8d99100));
  GUI_FillRoundedRect(xPos, yPosDiagram, xPos + 172 + 4 , yPosDiagram + 121, 4);
  GUI_MEMDEV_Select(0);
  GUI_MEMDEV_Write(hMemTrans);
  //
  // Initialize values
  //
  for (i = 0; i < NumItems; i++) {
    aAdd[i] = (i & 1) * 2 - 1;
  }
  do {
    TimeNext = GUI_GetTime() + 20;
    //
    // Draw diagram
    //
    _DrawDiagramAt(xPos, yPosDiagram, ayCur, Blend, hMemTrans);
    //
    // Change blending area
    //
    Blend += AddBlend;
    if ((Blend >= 164) || (Blend <= 8)) {
      AddBlend = -AddBlend;
    }
    //
    // Change values
    //
    for (i = 0; i < NumItems; i++) {
      *(ayCur + i) += *(aAdd + i);
      if ((*(ayCur + i) > (*(ayOrg + i) + 10)) || (*(ayCur + i) < (*(ayOrg + i) - 10))) {
        *(aAdd + i) = -*(aAdd + i);
      }
    }
    //
    // Delay if required
    //
    TimeNow = GUI_GetTime();
    if (TimeNext > TimeNow) {
      GUI_Delay(TimeNext - TimeNow);
    }
  } while (1);
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
  _DemoBarGraph();
  while (1) {
    GUI_Delay(100);
  }
}

/*************************** End of file ****************************/
