Example Description

This example describes how to use adc one shot mode wakeup.

Requirement Components:
The following modules in rtl8710b_sleepcfg.c need to be set to ON before compile:
(1) BIT_SYSON_PMOPT_SNZ_XTAL_EN and BIT_SYSON_PMOPT_SNZ_SYSPLL_EN of sleep_pwrmgt_config(global variable)
(2) BIT_SYSON_WEVT_ADC_MSK of sleep_wevent_config(global variable)

Operating process: 
 - Boot up device, and wait around 1 second, device will enter sleep mode, and the registered suspend function will called automatically.
 - ADC scan each channel every 200ms.When adc fifo data size is more than 8, adc wakes up CPU and the registered resume function will be called automatically.
 - Then system will enter sleep again until next one shot mode interrupt occurs.
