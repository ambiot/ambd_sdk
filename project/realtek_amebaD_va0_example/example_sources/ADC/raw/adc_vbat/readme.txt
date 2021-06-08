Example Description

This example describes how to use adc vabt channel to measure 5V vlotage.
This example also use ADC in timer-trigger mode. 

ADC could cooperate with timer modules which drive ADC module to do conversions according to a pre-configured timer event period. 
Every time a timer event is sent to ADC module, one conversion would be executed. System software should set timer trigger control 
register to enable this mode and set an appropriate timer module number to trigger timer selection register based on system design.
Timer-trigger mode can also be used by other normal channels.

Requirement Components:
    none

 