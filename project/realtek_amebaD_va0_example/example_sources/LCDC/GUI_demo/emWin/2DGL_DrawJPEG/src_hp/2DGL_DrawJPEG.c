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
File        : 2DGL_DrawJPEG.c
Purpose     : Sample for drawing JPEG files.
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
#define NUM_IMAGES_UNTIL_HINT 5
#define TITLE_HEIGHT          40
#define BORDER_SIZE           5
#define YPOS_IMAGE            73
#define   SIZE           22522
#define   JpegBaseAddr       0x08106000

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 200)

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawJPEGs
*
* Function description
*   Draws the given JPEG image.
*/
static void _DrawJPEGs() {
  static int      i;
  const char      acError[] = "There is possibly not enough memory to display this JPEG image.\n\nPlease assign more memory to emWin in GUIConf.c.";
  GUI_JPEG_INFO   Info;
  GUI_RECT        Rect;

  unsigned int           NumBytesRead;
  char          * pFile;
  int             xSize,  ySize;
  int             xPos,   yPos;
  int             r;

  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();
  //
  // Display file name.
  //
  Rect.x0 = BORDER_SIZE;
  Rect.y0 = TITLE_HEIGHT;
  Rect.x1 = xSize - BORDER_SIZE - 1;
  Rect.y1 = YPOS_IMAGE - 1;
  GUI_ClearRectEx(&Rect);
  GUI_SetTextMode(GUI_TM_NORMAL);
  GUI_SetFont(&GUI_Font8x16);
  GUI_DispStringInRectWrap("QR", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_CHAR);
  //
  // Clear the area in which the JPEG files are displayed.
  //
  Rect.x0 = BORDER_SIZE;
  Rect.y0 = YPOS_IMAGE;
  Rect.x1 = xSize - BORDER_SIZE - 1;
  Rect.y1 = ySize - BORDER_SIZE - 1;
  GUI_ClearRectEx(&Rect);
  //
  // Load image.
  //
  //
  // Check if the current JPEG image fits on the screen.
  //
  GUI_JPEG_GetInfo(JpegBaseAddr, SIZE, &Info);
  xSize -= BORDER_SIZE * 2 + 1;
  ySize -= YPOS_IMAGE + BORDER_SIZE + 1;
  //
  // Display the image centered.
  //
  xPos = BORDER_SIZE + (xSize - Info.XSize) / 2;
  yPos = YPOS_IMAGE  + (ySize - Info.YSize) / 2;
  GUI_SetClipRect(&Rect);
  r = GUI_JPEG_Draw(JpegBaseAddr, SIZE, xPos, yPos);
  GUI_SetClipRect(NULL);
  if (r) {
    //
    // The image could not be displayed successfully. Show an error message.
    //
    GUI_DispStringInRectWrap(acError, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
  } else {
    GUI_Delay(2000);
    if ((Info.XSize > xSize) || (Info.YSize > ySize)) {
      //
      // Inform the user about the possibility of scaling JPEG images.
      //
      if (i == 0) {
        GUI_ClearRectEx(&Rect);
        GUI_DispStringInRectWrap("JPEG images can be scaled as it is shown in 2DGL_JPEG_DrawScaled.c.",  &Rect, GUI_TA_BOTTOM | GUI_TA_HCENTER, GUI_WRAPMODE_WORD);
        GUI_Delay(3000);
      }
      i++;
      if (i == NUM_IMAGES_UNTIL_HINT) {
        i = 0;
      }
    }
  }

}


/*******************************************************************
*
*       _DrawJPEGsFromWindowsDir
*
* Function description
*   Iterates over all JPEG files in a Windows sub folder.
*/
static void _DrawJPEGsFromWindowsDir(void) {
  int             xSize;

  xSize = LCD_GetXSize();
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("Draw JPEG - Sample", xSize / 2, 5);
   _DrawJPEGs();

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
  while (1) {
    _DrawJPEGsFromWindowsDir();
  }
}

#endif

/*************************** End of file ****************************/
