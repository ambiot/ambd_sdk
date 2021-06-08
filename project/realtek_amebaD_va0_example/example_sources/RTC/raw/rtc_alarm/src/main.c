/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */
#include "ameba_soc.h"
#include "main.h"

 VOID RTC_Handler(u32 Data)
 {
	 RTC_TimeTypeDef RTC_TimeStruct;
	 
	 /*clear alarm flag*/
	 RTC_AlarmClear();
	 
	 RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
	 DBG_8195A("RTC_ISR time: %d:%d:%d:%d (%d) \n", RTC_TimeStruct.RTC_Days,
			 RTC_TimeStruct.RTC_Hours,
			 RTC_TimeStruct.RTC_Minutes,
			 RTC_TimeStruct.RTC_Seconds,
			 RTC_TimeStruct.RTC_H12_PMAM);
 }

void rtc_alarm_en(void)
{
	RTC_InitTypeDef RTC_InitStruct_temp;
	RTC_AlarmTypeDef RTC_AlarmStruct_temp;
	RTC_TimeTypeDef RTC_TimeStruct;

	/*enable RTC*/
	RTC_StructInit(&RTC_InitStruct_temp);
	RTC_Init(&RTC_InitStruct_temp);

	RTC_TimeStructInit(&RTC_TimeStruct);
	RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);
		
	/* set alarm */
	RTC_AlarmStructInit(&RTC_AlarmStruct_temp);
	RTC_AlarmStruct_temp.RTC_AlarmTime.RTC_Days = 1;
	RTC_AlarmStruct_temp.RTC_AlarmTime.RTC_Hours = 1;
	RTC_AlarmStruct_temp.RTC_AlarmTime.RTC_Minutes = 1;
	RTC_AlarmStruct_temp.RTC_AlarmTime.RTC_Seconds = 0;
	RTC_AlarmStruct_temp.RTC_AlarmMask = RTC_AlarmMask_Hours | RTC_AlarmMask_Minutes;
	RTC_AlarmStruct_temp.RTC_Alarm2Mask = RTC_Alarm2Mask_Days;
	
	RTC_SetAlarm(RTC_Format_BIN, &RTC_AlarmStruct_temp);
	RTC_AlarmCmd(ENABLE);
	
	InterruptRegister((IRQ_FUN)RTC_Handler, RTC_IRQ, NULL, 5);
	InterruptEn(RTC_IRQ, 5);

	vTaskDelete(NULL);
}

 int main() 
 {
	if(xTaskCreate( (TaskFunction_t)rtc_alarm_en, "RTC ALARM DEMO", (2048/4), NULL, (tskIDLE_PRIORITY + 1), NULL)!= pdPASS) {
			DBG_8195A("Cannot create rtc alarm demo task\n\r");
	}

	vTaskStartScheduler();

	while(1);
 }

