Example Description

This example describes how to use GPIO Port read/write by raw api.

Requirement Components:
    9 LEDs  
	dupont line

Pin name A12 map to GPIOA_12:	
   -For 32pin test, the available Gpio port are A12, A13, A14, A15, A16, A17, A18, A19, A25.
   -GPIO ports as output pins connect to the LED long leg, and the LED short leg connect to GND.
   
In this example:
When test Gpio port output, the LEDs is on when corresponding Gpio pins output 1, the LEDs is off when corresponding Gpio pins output 0; 
When test Gpio port input, current selected Gpio pins input value is different with original value, trace tool print current Gpio pins value.


