/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

 #include "ameba_soc.h"
 #include "ir_nec_protocol.h"

xSemaphoreHandle IR_Recv_end_sema = NULL;

IR_InitTypeDef IR_InitStruct;

/* Buffer which store encoded data */
IR_DataTypeDef IR_DataStruct;


/*the maximum number of carrier
if the counter is larger than MAX_CARRIER, we consider it is a non-carrier*/
#define MAX_CARRIER     2000

/**
  * @brief  receive and store data to IR_DataStruct
  * @param   No parameter.
  * @return  void
  */
void IR_RX_recv(void)
{
	uint16_t len = 0;
	static u8 continue_filter = 0;
	u32 data;
	u32 duration;

	len = IR_GetRxDataLen(IR_DEV);
	while (len) {
		len--;
		data = IR_ReceiveData(IR_DEV);
		duration = data & 0x7fffffff;

		if (IR_DataStruct.bufLen >= 67) {
			DBG_8195A("the waveform is inverse, you should set: \n");
			DBG_8195A("IR_InitStruct.IR_RxCntThrType = IR_RX_COUNT_HIGH_LEVEL \n");
			DBG_8195A("#define INVERSE_DATA in Ir_nec_protocol.h \n");
			break;
		}

		if((IR_DataStruct.bufLen == 0) && (IR_DataStruct.irBuf[0] == 0)) {
			IR_DataStruct.irBuf[0] = data;
		} else {
			if(duration > MAX_CARRIER)
				IR_DataStruct.irBuf[++IR_DataStruct.bufLen] = data;
			else if(continue_filter == 0)
				IR_DataStruct.irBuf[++IR_DataStruct.bufLen] = data;
			else
				IR_DataStruct.irBuf[IR_DataStruct.bufLen] += duration;
		}
		if (duration > MAX_CARRIER)
			continue_filter = 0;
		else 
			continue_filter = 1;
			
		len = IR_GetRxDataLen(IR_DEV);
	}
	
}

/**
  * @brief  interrupt handler function
  * @param   No parameter.
  * @return  void
  */
void IR_irq_handler(void)
{
	u32 IntStatus,IntMask;
	portBASE_TYPE taskWoken = pdFALSE;

	IntStatus = IR_GetINTStatus(IR_DEV);
	IntMask = IR_GetIMR(IR_DEV);

	if(IR_InitStruct.IR_Mode == IR_MODE_RX){
		IR_MaskINTConfig(IR_DEV, IR_RX_INT_ALL_MASK, DISABLE);

		if(IntStatus & IR_RX_FIFO_FULL_INT_STATUS){					
			IR_ClearINTPendingBit(IR_DEV, IR_RX_FIFO_FULL_INT_CLR);
		}

		if(IntStatus & IR_RX_FIFO_LEVEL_INT_STATUS){
			IR_ClearINTPendingBit(IR_DEV, IR_RX_FIFO_LEVEL_INT_CLR);
			IR_RX_recv();
		}

		if(IntStatus & IR_RX_CNT_OF_INT_STATUS){					
			IR_ClearINTPendingBit(IR_DEV, IR_RX_CNT_OF_INT_CLR);
		}

		if(IntStatus & IR_RX_FIFO_OF_INT_STATUS){			
			IR_ClearINTPendingBit(IR_DEV, IR_RX_FIFO_OF_INT_CLR);
		}

		if(IntStatus & IR_RX_CNT_THR_INT_STATUS){
			taskWoken = pdFALSE;		
			IR_ClearINTPendingBit(IR_DEV, IR_RX_CNT_THR_INT_CLR);
			xSemaphoreGiveFromISR(IR_Recv_end_sema, &taskWoken);		
		}

		if(IntStatus & IR_RX_FIFO_ERROR_INT_STATUS){					
			IR_ClearINTPendingBit(IR_DEV, IR_RX_FIFO_ERROR_INT_CLR);
		}
		
	}

	IR_MaskINTConfig(IR_DEV, IntMask, ENABLE);
}


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
	IR_InitStruct.IR_Mode = IR_MODE_RX;
	IR_InitStruct.IR_Freq = 10000000;            //sample frrequency   Hz
	IR_InitStruct.IR_RxFIFOThrLevel     = 5;

	IR_InitStruct.IR_RxCntThrType      = IR_RX_COUNT_LOW_LEVEL;      //the idle level of receiving waveform is low
	//IR_InitStruct.IR_RxCntThrType       = IR_RX_COUNT_HIGH_LEVEL;     //the idle level of receiving waveform is high  
	
	IR_InitStruct.IR_RxCntThr              = 0xa1644;
	IR_Init(IR_DEV, &IR_InitStruct);

	/* Configure interrrupt if need */
	IR_INTConfig(IR_DEV, IR_RX_INT_ALL_EN, ENABLE);
	//register interrupt callback function
	InterruptRegister((IRQ_FUN) IR_irq_handler, IR_IRQ, (u32)NULL, 10);
	InterruptEn(IR_IRQ, 10);
	
}


/**
  * @brief  RX with NEC protocol
  * @param   No parameter.
  * @return  void
  */
 void IR_RX_thread(void)
 {
	IR_Cmd(IR_DEV, IR_InitStruct.IR_Mode, DISABLE);
	Driver_IR_Init();
	IR_Cmd(IR_DEV, IR_MODE_RX, ENABLE);
	uint8_t ir_code[2] = {0, 0};
	uint8_t data[4] = {0, 0, 0, 0};

	do {
		IR_DataStruct.bufLen = 0;
		IR_DataStruct.codeLen = 0;
		IR_DataStruct.irBuf[0] = 0;
		IR_ClearRxFIFO(IR_DEV);
		if (xSemaphoreTake(IR_Recv_end_sema, 10 * configTICK_RATE_HZ)) {
			//rx end
			u32 result;
			result = IR_NECDecode(IR_InitStruct.IR_Freq, &data, &IR_DataStruct);
			ir_code[0] = data[0];
			ir_code[1] = data[2];
			DBG_8195A("result %d RX %2x%2x\n",result, ir_code[1],ir_code[0]);
		}
		else {
			DBG_8195A("rx timeout\n");
		}
	} while (1);

	vTaskDelete(NULL);

 }


 void main(void)
 {
 	Board_IR_Init();
	
	if(IR_Recv_end_sema == NULL) {
		vSemaphoreCreateBinary(IR_Recv_end_sema);
		xSemaphoreTake(IR_Recv_end_sema, 1/portTICK_RATE_MS);
	}

	if (pdTRUE != xTaskCreate( IR_RX_thread, (const char * const)"IR_RX_THREAD", 256, NULL, tskIDLE_PRIORITY + 5 , NULL))
		DBG_8195A("create IR RX thread error\n");

	vTaskStartScheduler();
 }
