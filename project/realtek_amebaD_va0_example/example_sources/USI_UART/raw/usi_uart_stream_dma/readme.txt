Example Description

This example describes how to use USI UART to communicate with PC.

Required Components:
    USBtoTTL adapter

Connect to PC
 - Connect Ground: connect to GND pin via USBtoTTL adapter
 - Use UART0
	GPIOB_21 as UART0_RX connect to TX of USBtoTTL adapter
	GPIOB_20 as UART0_TX connect to RX of USBtoTTL adapter

Open Super terminal or teraterm and 
set baud rate to 38400, 1 stopbit, no parity, no flow contorl.

This example shows:
1. The USI UART Rev DMA mode is used to receive characters from the PC, and then loopback them to the PC.

Note that buffer length should be integral multiple of 32 bytes, and buffer address should be 32 bytes aligned when using DMA. 

