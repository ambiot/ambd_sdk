Example Description

This example describes how to use ADC normal channel in software-trigger mode.

We provides a simple mechanism to drive ADC conversion by setting ADC software trigger register. 
Every time software trigger register is set, ADC module do channel switch to the next channel in conversion list. 
System software should check ready/busy register before read conversion data register.




