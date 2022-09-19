Example Description

	This loopback example describes how to use Ameba SDIO device APIs in spdio_api.c and spdio_api.h. 

How to build:
	1. copy main.c to project\realtek_amebaD_va0_example\src\src_hp
	
Requirement Components:
    PC (running Linux kernel over 3.13) * 1
	AmebaD QA board * 1

Pin assignment for SDIO device on AmebaD QA board:
--------------|----------------|
GPIO Pin name |	SDIO pin name  | 
--------------|----------------|
GPIOB22       |      SD_D0     | 
--------------------------------	
GPIOB23	      |      SD_D1	   | 
--------------------------------
GPIOB18	      |      SD_D2	   |
--------------------------------
GPIOB19	      |      SD_D3	   |
--------------------------------
GPIOB20	      |      SD_CMD	   |
--------------------------------
GPIOB21	      |      SD_CLK	   |
--------------------------------
GND	          |      GND	   |	
--------------------------------	

Set-up:
	1. Connect AmebaD QA board to PC via SDIO slot
	2. build this example and upload firmware to Ameba EVB
	3. build iNIC host SDK and run loopback test (refer to Run Loopback test.docx in iNIC source)

Behaviour:
	PC sends loopback packet to Ameba and Ameba will send back to PC whatever received 
