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
File        : 2DGL_DrawBMP.c
Purpose     : Example for drawing bitmap files
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )

              Can be used in a MS Windows environment only!
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

#define BMPBaseAddr  0x8086000 

void *pVoid;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static char _acBuffer[0x800];

/*******************************************************************
*
*       Static functions
*
********************************************************************
*/
/*********************************************************************
*
*       _GetData
*
* Function description
*   This routine is called by the functions GUI_BMP_GetXSizeEx(),
*   GUI_BMP_GetYSizeEx() and GUI_BMP_DrawEx(). The routine is responsible
*   for setting the data pointer to a valid data location with at least
*   one valid byte.
*
* Parameters
*   p           - Pointer to application defined data.
*   NumBytesReq - Number of bytes requested.
*   ppData      - Pointer to data pointer. This pointer should be set to
*                 a valid location.
*   StartOfFile - If this flag is 1, the data pointer should be set to the
*                 beginning of the data stream.
*
* Return value
*   Number of data bytes available.
*/
static int _GetData(void * p, const U8 ** ppData, unsigned NumBytesReq, U32 Off) {

  //
  // Check buffer size
  //
  if (NumBytesReq > sizeof(_acBuffer)) {
    NumBytesReq = sizeof(_acBuffer);
  }
  //
  // Set file pointer to the required position

  //
  // Read data into buffer
  //
 
  _memcpy(_acBuffer, BMPBaseAddr+Off, NumBytesReq);
  //
  // Set data pointer to the beginning of the buffer
  //
  *ppData = _acBuffer;
  //
  // Return number of available bytes
  //
  return NumBytesReq;
}

/*******************************************************************
*
*       _ShowBMP
*
* Function description
*   Shows the contents of a bitmap file
*/
static void _ShowBMP() {
  int    XSize;
  int    YSize;
  int    XPos;
  int    YPos;


  GUI_ClearRect(0, 60, 319, 239);

  if (!GUI_BMP_DrawEx(_GetData, pVoid, 150, 120)) {
    GUI_Delay(2000);
  }

}


/*******************************************************************
*
*       _DrawWindowsDirectoryBitmaps
*
* Function description
*   Iterates over all *.bmp-files of the windows directory
*/
static void _DrawWindowsDirectoryBitmaps(void) {

  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("DrawBMP - Sample", 160, 5);
  GUI_SetFont(&GUI_Font8x16);


    do {
      _ShowBMP();
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
  while(1) {
    _DrawWindowsDirectoryBitmaps();
  }
}

#endif

/*************************** End of file ****************************/
