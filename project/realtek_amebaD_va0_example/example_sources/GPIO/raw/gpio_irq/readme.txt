Example Description

This example describes how to use GPIO_irq to read/write by raw api.

Requirement Components:
    a LED
    a push button

Pin name PA_12 and PA_5 map to GPIOA_12 and GPIOB_5:
 - PA_12 as input with internal pull-high, connect a push button to this pin and ground.
 - PB_5 as output, connect a LED to this pin and ground.

In this example, push the button to trigger interrupt to turn on/off the LED.
