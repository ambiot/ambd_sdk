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
File        : 2DGL_BMPExport.c
Purpose     : Demonstrates the use of GUI_BMP_Serialize
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )

              Can be used in a MS Windows environment only!
---------------------------END-OF-HEADER------------------------------
*/

#ifndef SKIP_TEST

#include "DIALOG.h"
#include "diag.h"

/*********************************************************************
*
*       Externals
*
**********************************************************************
*/

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
*       Types
*
**********************************************************************
*/
typedef struct {
  char  *  acBuffer;
  U32	BufferSize;
  U32       BytesWritten;
} WRITE_BUFFER;

WRITE_BUFFER WriteBuffer = { 0 };
 

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static const GUI_POINT _aPointStar[] = {
  {   0, -36 },
  {   8,  -8 },
  {  36,   0 },
  {   8,   8 },
  {   0,  36 },
  {  -8,   8 },
  { -36,   0 },
  {  -8,  -8 }
};

static const GUI_POINT _aPointHexagon[] = {
  {   0, -30 },
  {  26, -15 },
  {  26,  15 },
  {   0,  30 },
  { -26,  15 },
  { -26, -15 },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawSomething
*
* Function description
*   Draws something to LCD
*/
static void _DrawSomething(void) {
  int xSize;
  int ySize;

  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_DispStringHCenterAt("Demo of GUI_BMP_Serialize", xSize / 2, (ySize - GUI_GetFontSizeY()) / 2);
  GUI_SetColor(GUI_GREEN);
  GUI_FillPolygon (&_aPointHexagon[0], GUI_COUNTOF(_aPointHexagon), xSize / 2, ySize / 5);
  GUI_SetColor(GUI_RED);
  GUI_FillPolygon (&_aPointStar[0],    GUI_COUNTOF(_aPointStar),    xSize / 2, ySize / 5 * 4);
}

/*********************************************************************
*
*       _WriteByte2File
*
* Function description
*   This function will be called by GUI_BMP_Serialize to write the
*   bytes to the file
*/
static void _WriteByte2File(U8 Data, void * p) {
  WRITE_BUFFER *pWriteBuffer;
  pWriteBuffer = (WRITE_BUFFER *)p;
  
  pWriteBuffer->acBuffer[pWriteBuffer->BytesWritten++] = Data;

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
  int xSize;
  int ySize;

  char acVolumeName[10];
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }

  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();
  _DrawSomething();

  WriteBuffer.BufferSize = xSize*ySize;
  /*you may need to merge the psram heap start address in rtl8721dhp_intfcfg.c*/
  WriteBuffer.acBuffer = Psram_reserve_malloc(WriteBuffer.BufferSize);
  
  GUI_BMP_Serialize(_WriteByte2File, (void *)&WriteBuffer);

  GUI_Delay(500);
  GUI_Clear();
 
  GUI_SetColor(GUI_MAKE_COLOR(0xF06060));
  GUI_DispStringHCenterAt("The image was stored in PSRAM\n " , xSize >> 1, ySize >> 1);
  GUI_Delay(3000);
  GUI_SetBkColor(GUI_BLACK);
  GUI_ClearRect(0, 0, 479, 271);
  GUI_SetColor(GUI_RED);
  GUI_DispStringHCenterAt("Now Display the stored image\n " , xSize >> 1, ySize >> 1);
  GUI_Delay(3000);
  GUI_BMP_Draw(WriteBuffer.acBuffer, 0, 0);
 
  while (1) {
    GUI_Delay(200);
  }
}

#endif

/*************************** End of file ****************************/
