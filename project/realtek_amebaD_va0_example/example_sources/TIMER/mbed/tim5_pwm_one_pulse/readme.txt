Example Description

This example describes how to use Timer5 pwm one pulse mode, default negative edge will trigger one pulse.

Requirement Components:
    A push button

Behaviour:
- PA_12 as GPIO interrupt pin, connect it to PA_13
- PA_13 as one pulse output pin.
- PB_5 as input capture pin with internal pull-high, connect a push button to this pin and ground.

This example will print out interrupt information when push button.
 