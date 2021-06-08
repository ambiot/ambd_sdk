Example Description

This example describes how to enter deepsleep mode and configure wakeup source

1.choose wakeup source by static parameter wakeup_source: AON_TIMER_WAKEUP, AON_WAKEPIN_WAKEUP, RTC_WAKEUP, KYESCAN_WAKEUP, CAPTOUCH_WAKEUP

2.configure the wakeup source in array dsleep_aon_wevent_config[] in RTL8721dlp_sleepcfg.c

Note:
1. parameter dslptime should be configured if AON timer is wakeup source, this parameter must be set to a value in the 0-32760000 range(unit ms),
	0 means not wakeup
2. if AON wakepin is wakeup source, array sleep_wakepin_config[] in RTL8721dlp_sleepcfg.c also need be set. 


