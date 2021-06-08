Example Description

This example describes how to disable the row where the stuck key is located and how to resume.

Requirement Components:
	USBtoTTL adapter

Connect to PC
 - Connect Ground: connect to GND pin via USBtoTTL adapter
 - Use KM0 LOGUART
	_PA_8 as LOGUART_RX connect to TX of USBtoTTL adapter
	_PA_7 as LOGUART_TX connect to RX of USBtoTTL adapter

Procedure
(1) Freertos will enter/leave tickless automatically.
(2) User can wakeup chip by key press or captouch.
(3) If a key is pressed for more than 10000ms(set by MACRO KEYSCAN_TIMEOUT_DELAY), the row where the stuck key is located will be disabled and chip will enter low power mode.
(4) After captouch or keys that located on other rows, chip wakeup, and resume all row scan function.


