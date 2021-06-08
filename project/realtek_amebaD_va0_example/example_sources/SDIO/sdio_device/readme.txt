Example Description

	This loopback example describes how to use Ameba SDIO device APIs in spdio_api.c and spdio_api.h. 

How to build:
	1. copy src\main.c to project\realtek_ameba1_va0_example\src
	2. include lib\lib_sdiod.a for build, then re-build the project 
	
Requirement Components:
    PC (running Linux kernel over 3.13) * 1
	Ameba EVB * 1

Pin assignment for SDIO device on Ameba EVB:
--------------|----------------|-----------------------
GPIO Pin name |	SDIO pin name  | Pin name on Ameba EVB 3V0
--------------|----------------|-----------------------
GPIOA4        |      SD_D0     |          D5
-------------------------------------------------------	
GPIOA5	      |      SD_D1	   |          D2	
-------------------------------------------------------
GPIOA0	      |      SD_D2	   |	      D17
-------------------------------------------------------
GPIOA1	      |      SD_D3	   |          D16	
-------------------------------------------------------
GPIOA2	      |      SD_CMD	   |          D7
-------------------------------------------------------
GPIOA3	      |      SD_CLK	   |          D6	
-------------------------------------------------------
GND	          |      GND	   |          GND	
-------------------------------------------------------		

Set-up:
	1. Connect Ameba to PC via SDIO slot
	2. build this example and upload firmware to Ameba EVB
	3. build iNIC host SDK and run loopback test (refer to Run Loopback test.docx in iNIC source)

Behaviour:
	PC sends loopback packet to Ameba and Ameba will send back to PC whatever received 
