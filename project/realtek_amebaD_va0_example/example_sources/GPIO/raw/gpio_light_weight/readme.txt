Example Description

This example describes how to use GPIO read/write in a light weight way.

Requirement Components:
    a LED
    a push button

Pin name PA_12 and PB_5 map to GPIOA_12 and GPIOB_5:
 - PA_12 as input with internal pull-high, connect a push button to this pin and ground.
 - PB_5 as output, connect a LED to this pin and ground.

In this example, the LED is on when the push button is pressed.
