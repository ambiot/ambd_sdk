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
File        : BASIC_DriverPerformance.c
Purpose     : Display driver performance test
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>
#include "GUI.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define XSIZE_XBPP             64
#define YSIZE_XBPP             8
#define LCDTEST_MEASURE_PERIOD 1000

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  GUI_BITMAP  Bm;
  U32         aPixels[XSIZE_XBPP * YSIZE_XBPP];
} PARAM_XBPP;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static PARAM_XBPP _Param;

static const GUI_COLOR _Colors_1bpp[] = {
#if (GUI_USE_ARGB == 1)
  0xFF000000, 0xFFFFFFFF
#else
  0x000000, 0xFFFFFF
#endif
};
static const GUI_COLOR _Colors_2bpp[] = {
#if (GUI_USE_ARGB == 1)
  0xFF000000, 0xFF808080, 0xFFC0C0C0, 0xFFFFFFFF
#else
  0x000000, 0x808080, 0xC0C0C0, 0xFFFFFF
#endif
};
static const GUI_COLOR _Colors_4bpp[] = {
#if (GUI_USE_ARGB == 1)
  0xFF000000, 0xFF800000, 0xFF008000, 0xFF808000,
  0xFF000080, 0xFF800080, 0xFF008080, 0xFF808080,
  0xFFC0C0C0, 0xFFFF0000, 0xFF00FF00, 0xFFFFFF00,
  0xFF0000FF, 0xFFFF00FF, 0xFF00FFFF, 0xFFFFFFFF
#else
  0x000000, 0x000080, 0x008000, 0x008080,
  0x800000, 0x800080, 0x808000, 0x808080,
  0xC0C0C0, 0x0000FF, 0x00FF00, 0x00FFFF,
  0xFF0000, 0xFF00FF, 0xFFFF00, 0xFFFFFF
#endif
};
static const GUI_COLOR _Colors_8bpp[] = {
#if (GUI_USE_ARGB == 1)
  0xFF000000, 0xFF800000, 0xFF008000, 0xFF808000, 0xFF000080, 0xFF800080, 0xFF008080, 0xFFC0C0C0, 0xFFC0DCC0, 0xFFA6CAF0, 0xFF402000, 0xFF602000, 0xFF802000, 0xFFA02000, 0xFFC02000, 0xFFE02000,
  0xFF004000, 0xFF204000, 0xFF404000, 0xFF604000, 0xFF804000, 0xFFA04000, 0xFFC04000, 0xFFE04000, 0xFF006000, 0xFF206000, 0xFF406000, 0xFF606000, 0xFF806000, 0xFFA06000, 0xFFC06000, 0xFFE06000,
  0xFF008000, 0xFF208000, 0xFF408000, 0xFF608000, 0xFF808000, 0xFFA08000, 0xFFC08000, 0xFFE08000, 0xFF00A000, 0xFF20A000, 0xFF40A000, 0xFF60A000, 0xFF80A000, 0xFFA0A000, 0xFFC0A000, 0xFFE0A000,
  0xFF00C000, 0xFF20C000, 0xFF40C000, 0xFF60C000, 0xFF80C000, 0xFFA0C000, 0xFFC0C000, 0xFFE0C000, 0xFF00E000, 0xFF20E000, 0xFF40E000, 0xFF60E000, 0xFF80E000, 0xFFA0E000, 0xFFC0E000, 0xFFE0E000,
  0xFF000040, 0xFF200040, 0xFF400040, 0xFF600040, 0xFF800040, 0xFFA00040, 0xFFC00040, 0xFFE00040, 0xFF002040, 0xFF202040, 0xFF402040, 0xFF602040, 0xFF802040, 0xFFA02040, 0xFFC02040, 0xFFE02040,
  0xFF004040, 0xFF204040, 0xFF404040, 0xFF604040, 0xFF804040, 0xFFA04040, 0xFFC04040, 0xFFE04040, 0xFF006040, 0xFF206040, 0xFF406040, 0xFF606040, 0xFF806040, 0xFFA06040, 0xFFC06040, 0xFFE06040,
  0xFF008040, 0xFF208040, 0xFF408040, 0xFF608040, 0xFF808040, 0xFFA08040, 0xFFC08040, 0xFFE08040, 0xFF00A040, 0xFF20A040, 0xFF40A040, 0xFF60A040, 0xFF80A040, 0xFFA0A040, 0xFFC0A040, 0xFFE0A040,
  0xFF00C040, 0xFF20C040, 0xFF40C040, 0xFF60C040, 0xFF80C040, 0xFFA0C040, 0xFFC0C040, 0xFFE0C040, 0xFF00E040, 0xFF20E040, 0xFF40E040, 0xFF60E040, 0xFF80E040, 0xFFA0E040, 0xFFC0E040, 0xFFE0E040,
  0xFF000080, 0xFF200080, 0xFF400080, 0xFF600080, 0xFF800080, 0xFFA00080, 0xFFC00080, 0xFFE00080, 0xFF002080, 0xFF202080, 0xFF402080, 0xFF602080, 0xFF802080, 0xFFA02080, 0xFFC02080, 0xFFE02080,
  0xFF004080, 0xFF204080, 0xFF404080, 0xFF604080, 0xFF804080, 0xFFA04080, 0xFFC04080, 0xFFE04080, 0xFF006080, 0xFF206080, 0xFF406080, 0xFF606080, 0xFF806080, 0xFFA06080, 0xFFC06080, 0xFFE06080,
  0xFF008080, 0xFF208080, 0xFF408080, 0xFF608080, 0xFF808080, 0xFFA08080, 0xFFC08080, 0xFFE08080, 0xFF00A080, 0xFF20A080, 0xFF40A080, 0xFF60A080, 0xFF80A080, 0xFFA0A080, 0xFFC0A080, 0xFFE0A080,
  0xFF00C080, 0xFF20C080, 0xFF40C080, 0xFF60C080, 0xFF80C080, 0xFFA0C080, 0xFFC0C080, 0xFFE0C080, 0xFF00E080, 0xFF20E080, 0xFF40E080, 0xFF60E080, 0xFF80E080, 0xFFA0E080, 0xFFC0E080, 0xFFE0E080,
  0xFF0000C0, 0xFF2000C0, 0xFF4000C0, 0xFF6000C0, 0xFF8000C0, 0xFFA000C0, 0xFFC000C0, 0xFFE000C0, 0xFF0020C0, 0xFF2020C0, 0xFF4020C0, 0xFF6020C0, 0xFF8020C0, 0xFFA020C0, 0xFFC020C0, 0xFFE020C0,
  0xFF0040C0, 0xFF2040C0, 0xFF4040C0, 0xFF6040C0, 0xFF8040C0, 0xFFA040C0, 0xFFC040C0, 0xFFE040C0, 0xFF0060C0, 0xFF2060C0, 0xFF4060C0, 0xFF6060C0, 0xFF8060C0, 0xFFA060C0, 0xFFC060C0, 0xFFE060C0,
  0xFF0080C0, 0xFF2080C0, 0xFF4080C0, 0xFF6080C0, 0xFF8080C0, 0xFFA080C0, 0xFFC080C0, 0xFFE080C0, 0xFF00A0C0, 0xFF20A0C0, 0xFF40A0C0, 0xFF60A0C0, 0xFF80A0C0, 0xFFA0A0C0, 0xFFC0A0C0, 0xFFE0A0C0,
  0xFF00C0C0, 0xFF20C0C0, 0xFF40C0C0, 0xFF60C0C0, 0xFF80C0C0, 0xFFA0C0C0, 0xFFFFFBF0, 0xFFA0A0A4, 0xFF808080, 0xFFFF0000, 0xFF00FF00, 0xFFFFFF00, 0xFF0000FF, 0xFFFF00FF, 0xFF00FFFF, 0xFFFFFFFF
#else
  0x000000, 0x000080, 0x008000, 0x008080, 0x800000, 0x800080, 0x808000, 0xC0C0C0, 0xC0DCC0, 0xF0CAA6, 0x002040, 0x002060, 0x002080, 0x0020A0, 0x0020C0, 0x0020E0,
  0x004000, 0x004020, 0x004040, 0x004060, 0x004080, 0x0040A0, 0x0040C0, 0x0040E0, 0x006000, 0x006020, 0x006040, 0x006060, 0x006080, 0x0060A0, 0x0060C0, 0x0060E0,
  0x008000, 0x008020, 0x008040, 0x008060, 0x008080, 0x0080A0, 0x0080C0, 0x0080E0, 0x00A000, 0x00A020, 0x00A040, 0x00A060, 0x00A080, 0x00A0A0, 0x00A0C0, 0x00A0E0,
  0x00C000, 0x00C020, 0x00C040, 0x00C060, 0x00C080, 0x00C0A0, 0x00C0C0, 0x00C0E0, 0x00E000, 0x00E020, 0x00E040, 0x00E060, 0x00E080, 0x00E0A0, 0x00E0C0, 0x00E0E0,
  0x400000, 0x400020, 0x400040, 0x400060, 0x400080, 0x4000A0, 0x4000C0, 0x4000E0, 0x402000, 0x402020, 0x402040, 0x402060, 0x402080, 0x4020A0, 0x4020C0, 0x4020E0,
  0x404000, 0x404020, 0x404040, 0x404060, 0x404080, 0x4040A0, 0x4040C0, 0x4040E0, 0x406000, 0x406020, 0x406040, 0x406060, 0x406080, 0x4060A0, 0x4060C0, 0x4060E0,
  0x408000, 0x408020, 0x408040, 0x408060, 0x408080, 0x4080A0, 0x4080C0, 0x4080E0, 0x40A000, 0x40A020, 0x40A040, 0x40A060, 0x40A080, 0x40A0A0, 0x40A0C0, 0x40A0E0,
  0x40C000, 0x40C020, 0x40C040, 0x40C060, 0x40C080, 0x40C0A0, 0x40C0C0, 0x40C0E0, 0x40E000, 0x40E020, 0x40E040, 0x40E060, 0x40E080, 0x40E0A0, 0x40E0C0, 0x40E0E0,
  0x800000, 0x800020, 0x800040, 0x800060, 0x800080, 0x8000A0, 0x8000C0, 0x8000E0, 0x802000, 0x802020, 0x802040, 0x802060, 0x802080, 0x8020A0, 0x8020C0, 0x8020E0,
  0x804000, 0x804020, 0x804040, 0x804060, 0x804080, 0x8040A0, 0x8040C0, 0x8040E0, 0x806000, 0x806020, 0x806040, 0x806060, 0x806080, 0x8060A0, 0x8060C0, 0x8060E0,
  0x808000, 0x808020, 0x808040, 0x808060, 0x808080, 0x8080A0, 0x8080C0, 0x8080E0, 0x80A000, 0x80A020, 0x80A040, 0x80A060, 0x80A080, 0x80A0A0, 0x80A0C0, 0x80A0E0,
  0x80C000, 0x80C020, 0x80C040, 0x80C060, 0x80C080, 0x80C0A0, 0x80C0C0, 0x80C0E0, 0x80E000, 0x80E020, 0x80E040, 0x80E060, 0x80E080, 0x80E0A0, 0x80E0C0, 0x80E0E0,
  0xC00000, 0xC00020, 0xC00040, 0xC00060, 0xC00080, 0xC000A0, 0xC000C0, 0xC000E0, 0xC02000, 0xC02020, 0xC02040, 0xC02060, 0xC02080, 0xC020A0, 0xC020C0, 0xC020E0,
  0xC04000, 0xC04020, 0xC04040, 0xC04060, 0xC04080, 0xC040A0, 0xC040C0, 0xC040E0, 0xC06000, 0xC06020, 0xC06040, 0xC06060, 0xC06080, 0xC060A0, 0xC060C0, 0xC060E0,
  0xC08000, 0xC08020, 0xC08040, 0xC08060, 0xC08080, 0xC080A0, 0xC080C0, 0xC080E0, 0xC0A000, 0xC0A020, 0xC0A040, 0xC0A060, 0xC0A080, 0xC0A0A0, 0xC0A0C0, 0xC0A0E0,
  0xC0C000, 0xC0C020, 0xC0C040, 0xC0C060, 0xC0C080, 0xC0C0A0, 0xF0FBFF, 0xA4A0A0, 0x808080, 0x0000FF, 0x00FF00, 0x00FFFF, 0xFF0000, 0xFF00FF, 0xFFFF00, 0xFFFFFF
#endif
};

/*********************************************************************
*
*       Palettes
*/
static const GUI_LOGPALETTE _Pal_1bpp    = {   2,  0,  &_Colors_1bpp[0] };
static const GUI_LOGPALETTE _Pal_2bpp    = {   4,  0,  &_Colors_2bpp[0] };
static const GUI_LOGPALETTE _Pal_4bpp    = {  16,  0,  &_Colors_4bpp[0] };
static const GUI_LOGPALETTE _Pal_8bpp    = { 256,  0,  &_Colors_8bpp[0] };

/*********************************************************************
*
*       Pixels
*/
//
// 1bpp
//
static const unsigned char _ac_1bpp_58x8[] = {
  __X__XX_, __XX__X_, ___XXXX_, _XX__XXX, X__XX___, XX___XX_, __XX__XX, X_______,
  _XX_X__X, _X__X_X_, ___X____, X__X____, X_X__X_X, __X_X__X, _X__X_X_, _X______,
  X_X____X, ____X_X_, X__X____, X______X, __X__X_X, __X_X__X, _X__X_X_, _X______,
  __X___X_, __XX__XX, XX_XXX__, XXX____X, ___XX___, XXX_X__X, _XXXX_XX, X_______,
  __X__X__, ____X___, X_____X_, X__X__X_, __X__X__, __X_X__X, _X__X_X_, _X______,
  __X_X___, ____X___, X_____X_, X__X__X_, __X__X__, __X_X__X, _X__X_X_, _X______,
  __X_X___, _X__X___, X__X__X_, X__X_X__, __X__X_X, __X_X__X, _X__X_X_, _X______,
  __X_XXXX, __XX____, X___XX__, _XX__X__, ___XX___, XX___XX_, _X__X_XX, X_______,
};

//
// 2bpp
//
static const unsigned char _ac_2bpp_32x11[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff,
  0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff,
  0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff,
  0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff,
  0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff,
  0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff,
  0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff,
  0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

//
// 4bpp
//
static const unsigned char _ac_4bpp_32x11[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
  0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
  0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
  0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
  0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
  0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
  0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
  0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

//
// 8bpp
//
static const unsigned char _ac_8bpp_32x11[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0, 0x01, 0x11, 0x21, 0x31, 0x41, 0x51, 0x61, 0x71, 0x81, 0x91, 0xa1, 0xb1, 0xc1, 0xd1, 0xe1, 0xf1,
  0x02, 0x12, 0x22, 0x32, 0x42, 0x52, 0x62, 0x72, 0x82, 0x92, 0xa2, 0xb2, 0xc2, 0xd2, 0xe2, 0xf2, 0x03, 0x13, 0x23, 0x33, 0x43, 0x53, 0x63, 0x73, 0x83, 0x93, 0xa3, 0xb3, 0xc3, 0xd3, 0xe3, 0xf3,
  0x04, 0x14, 0x24, 0x34, 0x44, 0x54, 0x64, 0x74, 0x84, 0x94, 0xa4, 0xb4, 0xc4, 0xd4, 0xe4, 0xf4, 0x05, 0x15, 0x25, 0x35, 0x45, 0x55, 0x65, 0x75, 0x85, 0x95, 0xa5, 0xb5, 0xc5, 0xd5, 0xe5, 0xf5,
  0x06, 0x16, 0x26, 0x36, 0x46, 0x56, 0x66, 0x76, 0x86, 0x96, 0xa6, 0xb6, 0xc6, 0xd6, 0xe6, 0xf6, 0x07, 0x17, 0x27, 0x37, 0x47, 0x57, 0x67, 0x77, 0x87, 0x97, 0xa7, 0xb7, 0xc7, 0xd7, 0xe7, 0xf7,
  0x08, 0x18, 0x28, 0x38, 0x48, 0x58, 0x68, 0x78, 0x88, 0x98, 0xa8, 0xb8, 0xc8, 0xd8, 0xe8, 0xf8, 0x09, 0x19, 0x29, 0x39, 0x49, 0x59, 0x69, 0x79, 0x89, 0x99, 0xa9, 0xb9, 0xc9, 0xd9, 0xe9, 0xf9,
  0x0a, 0x1a, 0x2a, 0x3a, 0x4a, 0x5a, 0x6a, 0x7a, 0x8a, 0x9a, 0xaa, 0xba, 0xca, 0xda, 0xea, 0xfa, 0x0b, 0x1b, 0x2b, 0x3b, 0x4b, 0x5b, 0x6b, 0x7b, 0x8b, 0x9b, 0xab, 0xbb, 0xcb, 0xdb, 0xeb, 0xfb,
  0x0c, 0x1c, 0x2c, 0x3c, 0x4c, 0x5c, 0x6c, 0x7c, 0x8c, 0x9c, 0xac, 0xbc, 0xcc, 0xdc, 0xec, 0xfc, 0x0d, 0x1d, 0x2d, 0x3d, 0x4d, 0x5d, 0x6d, 0x7d, 0x8d, 0x9d, 0xad, 0xbd, 0xcd, 0xdd, 0xed, 0xfd,
  0x0e, 0x1e, 0x2e, 0x3e, 0x4e, 0x5e, 0x6e, 0x7e, 0x8e, 0x9e, 0xae, 0xbe, 0xce, 0xde, 0xee, 0xfe, 0x0f, 0x1f, 0x2f, 0x3f, 0x4f, 0x5f, 0x6f, 0x7f, 0x8f, 0x9f, 0xaf, 0xbf, 0xcf, 0xdf, 0xef, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

/*********************************************************************
*
*       Bitmaps
*/
static const GUI_BITMAP _bm_1bpp_58x8     = {  58,   8,   8,   1,  _ac_1bpp_58x8 ,  &_Pal_1bpp};
static const GUI_BITMAP _bm_2bpp_32x11    = {  32,  11,   8,   2,  _ac_2bpp_32x11,  &_Pal_2bpp};
static const GUI_BITMAP _bm_4bpp_32x11    = {  32,  11,  16,   4,  _ac_4bpp_32x11,  &_Pal_4bpp};
static const GUI_BITMAP _bm_8bpp_32x11    = {  32,  11,  32,   8,  _ac_8bpp_32x11,  &_Pal_8bpp};

/*********************************************************************
*
*       Strings
*/
static char _acSmall[] = "0123456789\n";
static char _acBig[]   = "01234\n";

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _ExecFill
*/
static void _ExecFill(void * p) {
  GUI_POINT * pPoint;

  pPoint = (GUI_POINT *)p;
  GUI_SetBkColor(GUI_WHITE);
  GUI_ClearRect(1, 1, pPoint->x - 3, pPoint->y - 3);
  GUI_SetBkColor(GUI_BLACK);
  GUI_ClearRect(3, 3, pPoint->x - 1, pPoint->y - 1);
}

/*********************************************************************
*
*       _ExecSmallFont
*/
static void _ExecSmallFont(void * p) {
  char * s;
  int    i;

  s = (char *)p;
  GUI_SetLBorder(0);
  GUI_DispStringAt(s, 0, 0);
  for (i = 0; i < 7; i++) {
    GUI_DispString(s);
  }
  GUI_SetLBorder(1);
  GUI_DispStringAt(s, 1, 0);
  for (i = 0; i < 7; i++) {
    GUI_DispString(s);
  }
  GUI_SetLBorder(0);
}

/*********************************************************************
*
*       _ExecBigFont
*/
static void _ExecBigFont(void * p) {
  char * s;
  int    i;

  s = (char *)p;
  GUI_SetLBorder(0);
  GUI_DispStringAt(s, 0, 0);
  for (i = 0; i < 1; i++) {
    GUI_DispString(s);
  }
  GUI_SetLBorder(1);
  GUI_DispStringAt(s, 1, 0);
  for (i = 0; i < 1; i++) {
    GUI_DispString(s);
  }
  GUI_SetLBorder(0);
}

/*********************************************************************
*
*       _Exec1bpp
*/
static void _Exec1bpp(void * p) {
  (void)p;
  GUI_DrawBitmap(&_bm_1bpp_58x8, 0, 0);
  GUI_DrawBitmap(&_bm_1bpp_58x8, 1, 1);
}

/*********************************************************************
*
*       _Exec2bpp
*/
static void _Exec2bpp(void * p) {
  (void)p;
  GUI_DrawBitmap(&_bm_2bpp_32x11, 0, 0);
  GUI_DrawBitmap(&_bm_2bpp_32x11, 1, 1);
}

/*********************************************************************
*
*       _Exec4bpp
*/
static void _Exec4bpp(void * p) {
  (void)p;
  GUI_DrawBitmap(&_bm_4bpp_32x11, 0, 0);
  GUI_DrawBitmap(&_bm_4bpp_32x11, 1, 1);
}

/*********************************************************************
*
*       _Exec8bpp
*/
static void _Exec8bpp(void * p) {
  (void)p;
  GUI_DrawBitmap(&_bm_8bpp_32x11, 0, 0);
  GUI_DrawBitmap(&_bm_8bpp_32x11, 1, 1);
}

/*********************************************************************
*
*       _InitXbppDDP
*/
static void _InitXbppDDP(void) {
  GUI_COLOR Color;
  int       BytesPerPixel;
  int       BitsPerPixel;
  int       x;
  int       y;
  U32       MaxColor;

  BitsPerPixel = LCD_GetBitsPerPixel();
  if (BitsPerPixel <= 8) {
    BytesPerPixel = 1;
  } else if (BitsPerPixel <= 16) {
    BytesPerPixel = 2;
  } else {
    BytesPerPixel = 4;
  }
  MaxColor               = 1L << BitsPerPixel;
  _Param.Bm.XSize        = XSIZE_XBPP;
  _Param.Bm.YSize        = YSIZE_XBPP;
  _Param.Bm.BytesPerLine = (BitsPerPixel <= 8) ? XSIZE_XBPP : XSIZE_XBPP * (BitsPerPixel >> 3);
  _Param.Bm.BitsPerPixel = BytesPerPixel << 3;
  _Param.Bm.pData        = (U8 *)_Param.aPixels;
  _Param.Bm.pPal         = NULL;
  _Param.Bm.pMethods     = NULL;
  Color = 0;
  switch (BytesPerPixel) {
  case 1: {
      U8 * pData;
      pData = (U8 *)_Param.aPixels;
      for (y = 0; y < YSIZE_XBPP; y++) {
        for (x = 0; x < XSIZE_XBPP; x++) {
          *(pData++) = Color++;
          if (Color >= MaxColor) {
            Color = 0;
          }
        }
      }
    }
    break;
  case 2: {
      U16 * pData;
      pData = (U16 *)_Param.aPixels;
      for (y = 0; y < YSIZE_XBPP; y++) {
        for (x = 0; x < XSIZE_XBPP; x++) {
          *(pData++) = Color++;
          if (Color >= MaxColor) {
            Color = 0;
          }
        }
      }
    }
    break;
  case 4: {
      U32 * pData;
      pData = (U32 *)_Param.aPixels;
      for (y = 0; y < YSIZE_XBPP; y++) {
        for (x = 0; x < XSIZE_XBPP; x++) {
#if (GUI_USE_ARGB == 1)
          *(pData++) = (Color * 0x10101) | 0xFF000000;
#else
          *(pData++) = (Color * 0x10101);
#endif
          ++Color;
          if (MaxColor) {
            if (Color >= MaxColor) {
              Color = 0;
            }
          } else {
            if (Color >= 0xFF) {
              Color = 0;
            }
          }
        }
      }
    }
    break;
  }
}

/*********************************************************************
*
*       _ExecXbppDDP
*/
static void _ExecXbppDDP(void * p) {
  (void)p;
  GUI_DrawBitmap(&_Param.Bm, 0, 0);
  GUI_DrawBitmap(&_Param.Bm, 1, 1);
}

/*********************************************************************
*
*       _Measure
*/
static float _Measure(void (* pfOutput)(void * p), void * p) {
  int Period;
  int Cnt;
  int t0;
  int t;

  Period = LCDTEST_MEASURE_PERIOD;
  Cnt    = 0;
  pfOutput(p);  // Eliminate one time effects like color conversion
  t0 = GUI_GetTime();
  while ((t=GUI_GetTime()-t0) < Period) {
    pfOutput(p);
    Cnt++;
  }
  GUI_Clear();
  return 1000 * (float)Cnt / (float)t;
}

/*********************************************************************
*
*       _DispFillrate
*/
static void _DispFillrate(char * sPre, float FillratePPS, char * sPost) {
  unsigned int   i;
  char         * apLabel[] = {" KPixel/s", " MPixel/s"};

  GUI_DispString(sPre);
  for (i = 0; i < GUI_COUNTOF(apLabel); i++) {
    FillratePPS /= 1000;
    if (FillratePPS < 1000) {
      GUI_DispFloatFix((float)FillratePPS, 7, 3);
      GUI_DispString(apLabel[i]);
      break;
    }
  }
  GUI_DispString(sPost);
}

/*********************************************************************
*
*       _LCDBench
*/
static void _LCDBench(void) {
  GUI_POINT   Point;
  float       aPixelrateBitmap[5] = {0, 0, 0, 0, 0};
  float       PixelrateBigFont;
  float       PixelrateF6x8;
  float       FillratePPS;
  char      * s;
  char        ac[80];
  int         BitsPerPixel;
  int         xSizeString;
  int         ySizeFont;
  int         NumColors;
  int         MirrorX;
  int         MirrorY;
  int         SwapXY;
  int         xSize;
  int         ySize;

  BitsPerPixel = LCD_GetBitsPerPixelEx(0);
  xSize        = LCD_GetXSizeEx(0);
  ySize        = LCD_GetYSizeEx(0);
  MirrorX      = LCD_GetMirrorXEx(0);
  MirrorY      = LCD_GetMirrorYEx(0);
  SwapXY       = LCD_GetSwapXYEx(0);
  NumColors    = (1 << BitsPerPixel);
  _InitXbppDDP();
  //
  // Say hi !
  //
  GUI_X_Log("\nLCD driver benchmark. All values are  \xb5""s/pixel");
  GUI_X_Log("\nLower values are better.");
  GUI_SetBkColor(GUI_RED);
  GUI_SetColor(GUI_WHITE);
  GUI_Clear();
  GUI_SetFont(&GUI_FontComic18B_1);
  GUI_DispStringHCenterAt("LCD driver", xSize / 2, ySize / 3 - 10);
  GUI_DispStringHCenterAt("Benchmark" , xSize / 2, ySize / 3 + 20);
  GUI_Delay(1000);
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  GUI_SetLBorder(1);
  //
  // Log color depth, controller, orientation and cache
  //
  sDiagPrintf(ac, "\nColor depth: %d", BitsPerPixel);
  GUI_X_Log(ac);
  sDiagPrintf(ac, "\nOrientation: LCD_MIRROR_X = %d, LCD_MIRROR_Y = %d, LCD_SWAP_XY = %d", MirrorX, MirrorY, SwapXY);
  GUI_X_Log(ac);
  //
  // Measure filling
  //
  Point.x             = xSize;
  Point.y             = ySize;
  FillratePPS         = _Measure(&_ExecFill, &Point)  * (float)(2 * ((U32)xSize - 4) * ((U32)ySize - 4));
  sDiagPrintf(ac, "\nFill: %f", (float)1E6 / FillratePPS);
  GUI_X_Log(ac);
  //
  // Measure small font
  //
  GUI_SetFont(&GUI_Font6x8);
  s                   = _acSmall;
  xSizeString         = GUI_GetStringDistX(s);
  ySizeFont           = GUI_GetFontSizeY();
  PixelrateF6x8       = _Measure(&_ExecSmallFont, s)  * (float)2 * xSizeString * ySizeFont * 8;
  sDiagPrintf(ac, "\nF6x8: %f", (float)1E6 / PixelrateF6x8);
  GUI_X_Log(ac);
  //
  // Measure big font
  //
  GUI_SetFont(&GUI_FontComic18B_ASCII);
  s                   = _acBig;
  xSizeString         = GUI_GetStringDistX(s);
  ySizeFont           = GUI_GetFontSizeY();
  PixelrateBigFont    = _Measure(&_ExecBigFont, s)    * (float)2 * xSizeString * ySizeFont * 2;
  sDiagPrintf(ac, "\nFBig: %f", (float)1E6 / PixelrateBigFont);
  GUI_X_Log(ac);
  //
  // Measure 1bpp bitmap
  //
  aPixelrateBitmap[0] = _Measure(&_Exec1bpp, NULL)    * (float)2 * _bm_1bpp_58x8.XSize * 8;
  sDiagPrintf(ac, "\n1bpp: %f", (float)1E6 / aPixelrateBitmap[0]);
  GUI_X_Log(ac);
  //
  // Measure 2bpp bitmap
  //
  aPixelrateBitmap[1] = _Measure(&_Exec2bpp, NULL)    * (float)2 * _bm_2bpp_32x11.XSize * 11;
  sDiagPrintf(ac, "\n2bpp: %f", (float)1E6 / aPixelrateBitmap[1]);
  GUI_X_Log(ac);
  //
  // Measure 4bpp bitmap
  //
  aPixelrateBitmap[2] = _Measure(&_Exec4bpp, NULL)    * (float)2 * _bm_4bpp_32x11.XSize * 11;
  sDiagPrintf(ac, "\n4bpp: %f", (float)1E6 / aPixelrateBitmap[2]);
  GUI_X_Log(ac);
  //
  // Measure 8bpp bitmap
  //
  aPixelrateBitmap[3] = _Measure(&_Exec8bpp, NULL)    * (float)2 * _bm_8bpp_32x11.XSize * 11;
  sDiagPrintf(ac, "\n8bpp: %f", (float)1E6 / aPixelrateBitmap[3]);
  GUI_X_Log(ac);
  //
  // Measure device dependent bitmap
  //
  aPixelrateBitmap[4] = _Measure(&_ExecXbppDDP, NULL) * (float)2 * XSIZE_XBPP * YSIZE_XBPP;
  sDiagPrintf(ac, "\nXDDP: %f", (float)1E6 / aPixelrateBitmap[4]);
  GUI_X_Log(ac);
  //
  // Show results on display
  //
  GUI_Clear();
  if (xSize < 320) {
    GUI_SetFont(&GUI_Font6x8);
  } else {
    GUI_SetFont(&GUI_Font8x16);
  }
  GUI_GotoXY(0, 0);
  GUI_DispDecMin(BitsPerPixel);
  GUI_DispString(" bpp, ");
  GUI_DispDecMin(NumColors);
  GUI_DispString(" colors\n\nMIRROR_X ");
  GUI_DispDecMin(MirrorX);
  GUI_DispString(", MIRROR_Y ");
  GUI_DispDecMin(MirrorY);
  GUI_DispString(", SWAPXY ");
  GUI_DispDecMin(SwapXY);
  GUI_SetLBorder(1);
  GUI_SetFont(&GUI_Font6x8);
  GUI_DispChar('\n');
  _DispFillrate("\nFill: ", FillratePPS,         " Fill");
  _DispFillrate("\nF6x8: ", PixelrateF6x8,       " F6x8");
  _DispFillrate("\nFBig: ", PixelrateBigFont,    " FComic18");
  _DispFillrate("\n1bpp: ", aPixelrateBitmap[0], " Bitmap 1bpp");
  _DispFillrate("\n2bpp: ", aPixelrateBitmap[1], " Bitmap 2bpp");
  _DispFillrate("\n4bpp: ", aPixelrateBitmap[2], " Bitmap 4bpp");
  _DispFillrate("\n8bpp: ", aPixelrateBitmap[3], " Bitmap 8bpp");
  _DispFillrate("\nXDDP: ", aPixelrateBitmap[4], " 8/16bppDDP");
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
void MainTask(void);
void MainTask(void) {
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available.");
    return;
  }
  while (1) {
    _LCDBench();
    GUI_Delay(10000);
  }
}

/*************************** End of file ****************************/
