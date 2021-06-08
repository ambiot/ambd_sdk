/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */
#include "rtc_api.h"
#include "wait_api.h"

static const u8 dim[12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static bool is_leap_year(unsigned int year)
{
	u32 full_year = year + 1900;
	return (!(full_year % 4) && (full_year % 100)) || !(full_year % 400);
}

static u8 days_in_month (u8 month, u8 year)
{
	u8 ret = dim[month];
	if (ret == 0)
		ret = is_leap_year (year) ? 29 : 28;
	return ret;
}

 int main() 
 {
	time_t seconds;
	u32 delta_days;
	struct tm *timeinfo;
	
		RTC_InitTypeDef RTC_InitStruct;
	RTC_TimeTypeDef RTC_TimeStruct;

	RCC_PeriphClockSource_RTC(0);
	RTC_StructInit(&RTC_InitStruct);
	RTC_InitStruct.RTC_HourFormat = RTC_HourFormat_24;
	RTC_Init(&RTC_InitStruct);
	
	seconds=1256729737;  // Set RTC time to Wed, 28 Oct 2009 11:35:37
	timeinfo = localtime(&seconds);
	
	/*set time in RTC */
	RTC_TimeStruct.RTC_H12_PMAM = RTC_H12_AM;
	RTC_TimeStruct.RTC_Days = timeinfo->tm_yday;
	RTC_TimeStruct.RTC_Hours = timeinfo->tm_hour;
	RTC_TimeStruct.RTC_Minutes = timeinfo->tm_min;
	RTC_TimeStruct.RTC_Seconds = timeinfo->tm_sec;
	RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);

	while(1) {
		/*hour, min, sec get from RTC*/
		RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
		timeinfo->tm_sec = RTC_TimeStruct.RTC_Seconds;
		timeinfo->tm_min = RTC_TimeStruct.RTC_Minutes;
		timeinfo->tm_hour = RTC_TimeStruct.RTC_Hours;

		/* calculate how many days later from last time update rtc_timeinfo */
		delta_days = RTC_TimeStruct.RTC_Days - timeinfo->tm_yday;

		/* calculate  wday, mday, yday, mon, year*/
		timeinfo->tm_wday += delta_days;
		if(timeinfo->tm_wday >= 7){
			timeinfo->tm_wday = timeinfo->tm_wday % 7;
		}
	
		timeinfo->tm_yday += delta_days;
		timeinfo->tm_mday += delta_days;
	
		while(timeinfo->tm_mday > days_in_month(timeinfo->tm_mon, timeinfo->tm_year)){
			timeinfo->tm_mday -= days_in_month(timeinfo->tm_mon, timeinfo->tm_year);
			timeinfo->tm_mon++;

			if(timeinfo->tm_mon >= 12){
				timeinfo->tm_mon -= 12;
				timeinfo->tm_yday -= is_leap_year(timeinfo->tm_year) ? 366 : 365;
				timeinfo->tm_year ++;

				/* over one year, update days in RTC_TR */
				RTC_TimeStruct.RTC_Days = timeinfo->tm_yday;
				RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);
			}
		}

		/* Convert to timestamp(seconds from 1970.1.1 00:00:00)*/
		seconds = mktime(timeinfo);
		
		DBG_8195A("Time as seconds since January 1, 1970 = %d\n", seconds);
		DBG_8195A("Time as a basic string = %s", ctime(&seconds));
		DBG_8195A("Time as a custom formatted string = %d-%d-%d %d:%d:%d\n\n", 
			timeinfo->tm_year, timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour,
			timeinfo->tm_min,timeinfo->tm_sec);

		DelayMs(1001);
	}
}

