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
File        : MOVIE_ShowFromFS.c
Purpose     : Shows how to play a movie directly from a file system.
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )

              Requires either a MS Windows environment or emFile.
----------------------------------------------------------------------
*/

#ifndef SKIP_TEST

#include "GUI.h"
#include "diag.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 80)

#define MVBaseAddr  0x8106000 


/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbNotify
*
* Function description
*   Callback function for movie player. Uses multiple buffering if
*   available to avoid tearing effects.
*/
void _cbNotify(GUI_HMEM hMem, int Notification, U32 CurrentFrame) {
  switch (Notification) {
  case GUI_MOVIE_NOTIFICATION_PREDRAW:
    GUI_MULTIBUF_Begin();
    break;
  case GUI_MOVIE_NOTIFICATION_POSTDRAW:
    GUI_MULTIBUF_End();
    break;
  case GUI_MOVIE_NOTIFICATION_STOP:
    break;
  }
}

static int _GetData(void * p, const U8 ** ppData, unsigned NumBytesReq, U32 Off) {
  //
  // Check buffer size
  //
  //
  // Set file pointer to the required position

  //
  // Read data into buffer
  //
  _memcpy(  *ppData, MVBaseAddr + Off, NumBytesReq);
  //
  // Set data pointer to the beginning of the buffer
  //
  //
  // Return number of available bytes
  //
  return NumBytesReq;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawSmilie
*/
static void _DrawSmilie(int xPos, int yPos, int r) {
  int d;

  GUI_SetColor(GUI_YELLOW);
  GUI_FillCircle(xPos, yPos, r);
  GUI_SetColor(GUI_BLACK);
  GUI_SetPenSize(1);
  GUI_DrawCircle(xPos, yPos, r);
  d = (r * 2) / 5;
  GUI_FillCircle(xPos - d, yPos - d, r / 10);
  GUI_FillCircle(xPos + d, yPos - d, r / 10);
  GUI_DrawVLine(xPos, yPos - d / 2, yPos + d / 2);
  GUI_DrawArc(xPos, yPos + r + d, r, r, 70, 110);
}

/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  GUI_MOVIE_INFO   Info;
  GUI_MOVIE_HANDLE hMovie;
  int              xSize, ySize;
  GUI_RECT         Rect;
  int              FontDistY;

  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  //
  // Get display size
  //
  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();
  //
  // Get physical size of movie
  //
  if (GUI_MOVIE_GetInfoEx(_GetData, NULL, &Info) == 0) {
  	DBG_8195A("movie:%d,%d,%d,%d\n", Info.msPerFrame,Info.NumFrames, Info.xSize, Info.ySize);
	//GUI_MOVIE_SetPeriod(hMovie, 83);
    //
    // Check if display size fits
    //
    if ((Info.xSize <= xSize) && (Info.ySize <= ySize)) {
      //
      // Create and play movie
      //
      hMovie = GUI_MOVIE_CreateEx(_GetData, NULL, _cbNotify);
      if (hMovie) {
        GUI_MOVIE_Show(hMovie, (xSize - Info.xSize) / 2, (ySize - Info.ySize) / 2, 1);
      }
    } else {
      //
      // Error message
      //
      GUI_SetFont(GUI_FONT_13_ASCII);
      GUI_DispStringHCenterAt("Video can not be shown.\n\nDisplay size too small.", xSize / 2, (ySize - GUI_GetFontSizeY()) / 2);
    }
  } else {
    GUI_SetBkColor(GUI_RED);
    GUI_Clear();
    GUI_SetFont(GUI_FONT_16_ASCII);
    FontDistY = GUI_GetFontDistY();
    Rect.x0 = 0;
    Rect.y0 = ySize / 2;
    Rect.x1 = xSize - 1;
    Rect.y1 = Rect.y0 + FontDistY * 3 - 1;
    GUI_DispStringInRect("Error opening the movie file.\n"
                         "Please make sure that the given\n"
                         "movie file exists on the specified path:",
                         &Rect, GUI_TA_HCENTER | GUI_TA_TOP);
    Rect.y0 = Rect.y1 + 1;
    Rect.y1 = Rect.y0 + FontDistY;
    GUI_DispStringInRect("MOVIE_ShowFromFS.emf\n", &Rect, GUI_TA_HCENTER | GUI_TA_TOP);
    Rect.y0 = Rect.y1 + 1;
    Rect.y1 = ySize - 1;
    GUI_DispStringInRect("A sample video can be downloaded\non www.segger.com.", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    _DrawSmilie(xSize / 2, ySize / 4, ySize / 8);
  }
  while (1) {
    GUI_Exec();
    GUI_X_Delay(1);
  }
}

#endif

/*************************** End of file ****************************/
