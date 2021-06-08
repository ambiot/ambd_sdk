Example Description

This example describes how to use USI UART to communicate with PC.

Required Components:
    USBtoTTL adapter

Connect to PC
 - Connect Ground: connect to GND pin via USBtoTTL adapter
 - Use USI UART
	GPIOB_21 as USI_UART_RX connect to TX of USBtoTTL adapter
	GPIOB_20 as USI_UART_TX connect to RX of USBtoTTL adapter

Open Super terminal or teraterm and 
set baud rate to 38400, 1 stopbit, no parity, no flow contorl.

This example shows:
1. The RX data ready interrupt service routine is used to receive characters from the PC, and then loopback them to the PC.
2. The TX done interrupt service routine will send a prompt string "8195a$" to the PC.