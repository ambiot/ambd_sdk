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
File        : FONT_ShowXBF.c
Purpose     : Shows how to use (E)xternal (B)inary (F)onts
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )

              Can be used in a MS Windows environment only!
----------------------------------------------------------------------
*/

#ifndef SKIP_TEST

#include "GUI.h"
#include "EDIT.h"

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)


#define XBFbaseAddr  0x8106000
void * XBFpVoid;
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetFileName
*
* Function description
*   Returns the file name of the XBF file to be used
*/
static void _GetFileName(char * pPath, unsigned MaxSize) {
  WM_HWIN hWin;
  
  //
  // Set default value on first call
  //
  if (!strlen(pPath)) {
    strcpy(pPath, "Sample\\Tutorial\\FONT_ShowXBF\\ExtBinFont.xbf");
  }
  // Display small hint
  GUI_SetFont(&GUI_Font10_ASCII);
  GUI_DispStringHCenterAt("Please enter the file name of the XBF-file:", 160, 80);
  //
  // Create edit widget
  //
  hWin = EDIT_Create(10, 120, 300, 20, 0, MaxSize, WM_CF_SHOW);
  EDIT_SetText(hWin, pPath);
  WM_SetFocus(hWin);
  //
  // Wait until GUI_KEY_ENTER has been pressed
  //
  while (GUI_GetKey() != GUI_KEY_ENTER) {
    GUI_Delay(100);
  }
  //
  // Get filename from EDIT widget
  //
  EDIT_GetText(hWin, pPath, MaxSize);
  //
  // Create edit widget
  //
  WM_DeleteWindow(hWin);
  //
  // Clear screen
  //
  GUI_ClearRect(0, 40, 319, 239);
}

/*********************************************************************
*
*       _cbGetData
*
* Function description
*   Callback function for getting font data
*
* Parameters:
*   Off      - Position of XBF file to be read
*   NumBytes - Number of requested bytes
*   pVoid    - Application defined pointer
*   pBuffer  - Pointer to buffer to be filled by the function
*
* Return value:
*   0 on success, 1 on error
*/
static int _cbGetData(U32 Off, U16 NumBytes, void * pVoid, void * pBuffer) {
 
	_memcpy( pBuffer, XBFbaseAddr + Off,  NumBytes);

  return 0;   // Ok
}

/*********************************************************************
*
*       _ShowXBF
*
* Function description
*   Small sub routine which creates (and selects) a XBF font,
*   shows 'Hello world!' and waits for a keypress
*/
static void _ShowXBF(void * pVoid) {
  GUI_XBF_DATA XBF_Data;
  GUI_FONT     Font;

  //
  // Create XBF font
  //
  GUI_XBF_CreateFont(&Font,             // Pointer to GUI_FONT structure in RAM
                     &XBF_Data,         // Pointer to GUI_XBF_DATA structure in RAM
                     GUI_XBF_TYPE_PROP, // Font type to be created
                     _cbGetData,        // Pointer to callback function
                     pVoid);            // Pointer to be passed to GetData function
  //
  // Show 'Hello world!'
  //
  GUI_DispStringHCenterAt("Hello world!", 160, 80);
  //
  // Display hint
  //
  GUI_SetFont(&GUI_Font13_ASCII);
  GUI_DispStringHCenterAt("Press any key to continue...", 160, 120);
  //
  // Wait for pressing a key
  //
  while (!GUI_GetKey()) {
    GUI_Delay(100);
  }
  //
  // Delete XBF font and clear display
  //
  GUI_XBF_DeleteFont(&Font);
  GUI_ClearRect(0, 40, 319, 239);
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
  // Initialize emWin
  //
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("External binary font sample", 160, 5);
  while (1) {
  	
      _ShowXBF(XBFpVoid);

     // GUI_MessageBox("File not found!", "Error", GUI_MESSAGEBOX_CF_MODAL);
    //  GUI_ClearRect(0, 40, 319, 239);

  }
}

#endif

/*************************** End of file ****************************/

