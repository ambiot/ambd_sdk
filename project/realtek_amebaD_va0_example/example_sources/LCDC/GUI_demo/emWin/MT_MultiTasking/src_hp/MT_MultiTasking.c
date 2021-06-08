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
File        : MT_MultiTasking.c
Purpose     : Example demonstrates MultiTasking capabilities of emWin
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )

              Requires either a MS Windows environment or embOS.
              If not using embOS you have to change the hardware
              dependent macros to work with your OS.
----------------------------------------------------------------------
*/

#ifndef SKIP_TEST
#include <stddef.h>
#include "GUI.h"
#include "FRAMEWIN.h"
#include "ameba_soc.h"
#include "main.h"

#if GUI_OS == 0
  #error Multitasking sample requires task awareness (#define GUI_OS 1)
#endif

#define Delay(t)    vTaskDelay(t)

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 20)




/*******************************************************************
*
*       Static code
*
********************************************************************
*/
/*******************************************************************
*
*       _cbCallbackT0
*/
static int XPos;
static const char aText[] = "Moving text...";

static void _cbCallbackT0(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    //
    // Handle the paint message
    //
    GUI_SetBkColor(GUI_MAKE_COLOR(0x4040FF));
    GUI_SetColor(GUI_BLACK);
    GUI_SetFont(&GUI_FontComic24B_ASCII);
    GUI_Clear();
    GUI_DispStringAt(aText, XPos, 0);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _cbCallbackT1
*/
static void _cbCallbackT1(WM_MESSAGE * pMsg) {
  WM_HWIN hWin = (FRAMEWIN_Handle)(pMsg->hWin);
  switch (pMsg->MsgId) {
  case WM_PAINT:
    //
    // Handle the paint message
    //
    GUI_SetBkColor(GUI_MAKE_COLOR(0xA02020));
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_FontComic24B_ASCII);
    GUI_SetTextAlign(GUI_TA_HCENTER | GUI_TA_VCENTER);
    GUI_Clear();
    GUI_DispStringHCenterAt("Moving window...", 
                            WM_GetWindowSizeX(hWin) / 2, 
                            WM_GetWindowSizeY(hWin) / 2);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _cbBackgroundWin
*/
static void _cbBackgroundWin(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    //
    // Handle only the paint message
    //
    GUI_SetBkColor(GUI_MAKE_COLOR(0x00CC00));
    GUI_Clear();
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_DispStringHCenterAt("emWin - multitasking demo\n", 160, 5);
    GUI_SetFont(&GUI_Font13_1);
    GUI_DispStringAt("Scrolling text and moving windows without flickering", 5, 35);
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _Task_0
*/
static void _Task_0(void) {
  FRAMEWIN_Handle hFrameWin;
  WM_HWIN         hChildWin;
  //
  // Create frame window
  //
  hFrameWin = FRAMEWIN_Create("Task 0",  NULL, WM_CF_SHOW | WM_CF_STAYONTOP,
                              0, 70, 200, 50);
  //
  // Create child window
  //
  hChildWin = WM_CreateWindowAsChild(0, 0, 0, 0, WM_GetClientWindow(hFrameWin),
                                     WM_CF_SHOW | WM_CF_MEMDEV,
                                     _cbCallbackT0, 0);
  FRAMEWIN_SetActive(hFrameWin, 0);
  //
  // Make sure the right window is active...
  //
  WM_SelectWindow(hChildWin);
  //
  // ...and the right font is selected
  //
  GUI_SetFont(&GUI_FontComic24B_ASCII);
  while(1) {
    GUI_RECT Rect;
    int XLen;
    
    XLen = GUI_GetStringDistX(aText);       // Get the length of the string
    WM_GetClientRect(&Rect);                // Get the size of the window
    //
    // Show moving text
    //
    for (XPos = 0; XPos < (Rect.x1 - Rect.x0) - XLen; XPos++) {
      WM_InvalidateWindow(hChildWin);
      Delay(50);
    }
    for (; XPos >= 0; XPos--) {
      WM_InvalidateWindow(hChildWin);
      Delay(100);
    }
  }
}

/*******************************************************************
*
*       _Task_1
*/
static void _Task_1(void) {
  FRAMEWIN_Handle hFrameWin;
  WM_HWIN         hChildWin;

  //
  // Create frame window
  //
  hFrameWin = FRAMEWIN_Create("Task 1", NULL, WM_CF_SHOW | WM_CF_STAYONTOP,
                              20, 170, 200, 50);
  //
  // Create child window
  //
  hChildWin = WM_CreateWindowAsChild(0, 0, 0, 0, WM_GetClientWindow(hFrameWin),
                                     WM_CF_SHOW | WM_CF_MEMDEV,
                                     _cbCallbackT1, 0);
  FRAMEWIN_SetActive(hFrameWin, 0);
  while(1) {
    int i;
    int nx = 80;
    int ny = 90;
    //
    // Move window continously
    //
    for (i = 0; i < ny; i++) {
      WM_MoveWindow(hFrameWin, 0, -2);
      Delay(50);
    }
    for (i = 0; i < nx; i++) {
      WM_MoveWindow(hFrameWin, 2, 0);
      Delay(50);
    }
    for (i = 0; i < ny; i++) {
      WM_MoveWindow(hFrameWin, 0, 2);
      Delay(50);
    }
    for (i = 0; i < nx; i++) {
      WM_MoveWindow(hFrameWin, -2, 0);
      Delay(50);
    }
  }
}

/*******************************************************************
*
*       _GUI_Task
*
* This task does the background processing.
* The MainTask job is to update invalid windows, but other things such as
* evaluating mouse or touch input may also be done.
*/
static void _GUI_Task(void) {
  while(1) {
    GUI_Exec();           // Do the background work ... Update windows etc.)
    GUI_X_ExecIdle();     // Nothing left to do for the moment ... Idle processing
  }
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
  // Init GUI
  //
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  WM_SetCallback(WM_HBKWIN, _cbBackgroundWin);  // Set callback for background window
  //
  // Create tasks
  //

  	if (xTaskCreate((TaskFunction_t )_Task_0,(const char*)"Task_0", 2400, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		DBG_8195A("\n\r%s xTaskCreate(MainTask) failed", __FUNCTION__);

	if (xTaskCreate((TaskFunction_t )_Task_1,(const char*)"Task_1", 2400, NULL, tskIDLE_PRIORITY + 2, NULL) != pdPASS)
		DBG_8195A("\n\r%s xTaskCreate(MainTask) failed", __FUNCTION__);

	if (xTaskCreate((TaskFunction_t )_GUI_Task,(const char*)"GUI_TASK", 2400, NULL, tskIDLE_PRIORITY + 3, NULL) != pdPASS)
		DBG_8195A("\n\r%s xTaskCreate(GUI_TASK) failed\n");

	
	/* Enable Schedule, Start Kernel */
	vTaskStartScheduler();

}

#endif

/*************************** End of file ****************************/
