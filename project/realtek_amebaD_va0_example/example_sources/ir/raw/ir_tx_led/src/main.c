/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "ameba_soc.h"
#include "ir_led.h"

IR_InitTypeDef IR_InitStruct;
/**
  * @brief  initialization of pinmux settings and pad settings.
  * @param   No parameter.
  * @return  void
  */
void Board_IR_Init(void)
{
	/*there are three groups of pinmux and pad settings*/
	
	//Pinmux_Config(_PA_25, PINMUX_FUNCTION_IR);    //TX
	//Pinmux_Config(_PA_26, PINMUX_FUNCTION_IR);    //RX

	Pinmux_Config(_PB_23, PINMUX_FUNCTION_IR);   //TX
	Pinmux_Config(_PB_22, PINMUX_FUNCTION_IR);   //RX
	
	//Pinmux_Config(_PB_29, PINMUX_FUNCTION_IR);   //TX
	//Pinmux_Config(_PB_31, PINMUX_FUNCTION_IR);   //RX
}

/**
  * @brief  Initialize IR peripheral.
  * @param   No parameter.
  * @return  void
  */
void Driver_IR_Init(void)
{
	/* Enable IR clock */
	// already init when sysboot

	/* Initialize IR */
	IR_StructInit(&IR_InitStruct);
	IR_InitStruct.IR_Mode = IR_MODE_TX;
	IR_InitStruct.IR_Freq = 10000000;            //Hz   10MHz
	IR_InitStruct.IR_DutyCycle = 1;
	IR_Init(IR_DEV, &IR_InitStruct);

	/* Configure interrrupt if need */

}

/**
  * @brief  TX with NEC protocol
  * @param   No parameter.
  * @return  void
  */
void IR_TX_thread(void* param)
{
	
	u32 tx_count;
	u8 tx_thres = 15;	
	u8 N = 4;
	
	/* struct which stores encoded data */
	IR_DataTypeDef IR_DataStruct;
	/*Buffer which stores command*/
	uint8_t GRB[3] = {0x00, 0xff, 0x00};
	
	IR_Cmd(IR_DEV, IR_InitStruct.IR_Mode, DISABLE);
	Driver_IR_Init();

	do {
		tx_count = 0;
		if (GRB[0] < 0xff)
			GRB[0] ++;
		else if (GRB[0] == 0xff) {
			if (GRB[1] < 0xff) {
				GRB[1] ++;
				GRB[0] = 0x00;
			}
			else if (GRB[1] == 0xff) {
				if (GRB[2] < 0xff) {
					GRB[2] ++;
					GRB[1] = 0x00;
				}
				else if (GRB[2] == 0xff) {
					for (int i = 0; i < 3; ++i) {
						GRB[i] = 0x00;
					}
				}
			}
		}
			
		DiagPrintf("TX %2x%2x%2x\n",GRB[2], GRB[1], GRB[0]);

		/* Encode by LED protocol */
		IR_LEDEncode(IR_InitStruct.IR_Freq, (uint8_t *)&GRB, &IR_DataStruct, 0);
			
		IR_SendBuf(IR_DEV, IR_DataStruct.irBuf, IR_TX_FIFO_SIZE, FALSE);		
		IR_Cmd(IR_DEV, IR_InitStruct.IR_Mode, ENABLE);
		
		tx_count += IR_TX_FIFO_SIZE;
		
		while(IR_DataStruct.bufLen - tx_count > 0) {
			while(IR_GetTxFIFOFreeLen(IR_DEV) < tx_thres){
				taskYIELD();
			}
				
			if(IR_DataStruct.bufLen - tx_count > tx_thres) {
				IR_SendBuf(IR_DEV, IR_DataStruct.irBuf + tx_count, tx_thres, FALSE);
				tx_count += tx_thres;
			} else {
				IR_SendBuf(IR_DEV, IR_DataStruct.irBuf + tx_count, IR_DataStruct.bufLen - tx_count, TRUE);
				tx_count = IR_DataStruct.bufLen;
			}
		}
		/*
		// When IR FSM status is idle, which means that the current data packets have finished sending,
		// the next data packets are going to be sent.
		while (1){
			if (IR_FSMRunning(IR_DEV) == FALSE) {
				IR_Cmd(IR_DEV, IR_InitStruct.IR_Mode, DISABLE);
				break;
			}
		}
		*/	 	
		vTaskDelay(1000/portTICK_RATE_MS);      //delay 1s
		IR_Cmd(IR_DEV, IR_InitStruct.IR_Mode, DISABLE);
	}while (1);
	
	vTaskDelete(NULL);
	
}


int main (void)
{

	Board_IR_Init();
	DiagPrintf("ir tx led \n");
	if (pdTRUE != xTaskCreate( IR_TX_thread, (const char * const)"IR_TX_THREAD", 256, NULL, tskIDLE_PRIORITY + 5 , NULL))
		DiagPrintf("creat IR TX thread error\n");

	vTaskStartScheduler();
}
