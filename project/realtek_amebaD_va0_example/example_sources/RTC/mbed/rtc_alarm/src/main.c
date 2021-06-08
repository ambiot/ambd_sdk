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
#include "rtc_api.h"

#include <time.h>
#include "timer_api.h"

 alarm_irq_handler rtc_handler(void)
 { 	
 	time_t t;
	struct tm *timeinfo;
	
 	t = rtc_read();
	timeinfo = localtime(&t);

	DBG_8195A("alarm time = %d-%d-%d %d:%d:%d\n", 
            timeinfo->tm_year, timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour,
            timeinfo->tm_min,timeinfo->tm_sec);
 }

void rtc_alarm_en(void)
{
	time_t t = 0;
	struct tm *timeinfo;
	alarm_t alarm;

	rtc_init();
	rtc_write(t);
	timeinfo = localtime(&t);

	DBG_8195A("now time = %d-%d-%d %d:%d:%d\n", 
            timeinfo->tm_year, timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour,
            timeinfo->tm_min,timeinfo->tm_sec);
	
	alarm.hour = 0;
	alarm.yday = 0;
	alarm.min = 0;
	alarm.sec = 10;
	rtc_set_alarm(&alarm, (alarm_irq_handler) rtc_handler);
	
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

