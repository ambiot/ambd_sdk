Example Description

	This example describes how to communicate with AmebaZ gspi interface. 

How to build:
	1. copy src\main.c to project\realtek_amebaz_va0_example\src

	This example source code(mian.c) contain both GSPI slave code and SPI master code, you can use "CONFIG_GPSI_SLAVE" to choose which dirver to run.

	"#define CONFIG_GPSI_SLAVE 1"  for GSPI Slave
	"#define CONFIG_GPSI_SLAVE 0"  for SPI master

Requirement Components:
    2 AmebaZ Board

    AmebaZ (A): Assign as SPI master
	
	SPI0_MOSI : PA_23
	SPI0_MISO : PA_22  
	SPI0_SCLK : PA_18
	GPIO_CS : PA_28
	GPIO_INT : PA_27

    AmebaZ (B): Assign as GSPI slave

	GSPI_MOSI :	PA_20
	GSPI_MISO : PA_22
	GSPI_CLK : PA_21
	GSPI_CS : PA_19
	GSPI_INT : PA_23

Setup:connect A and B as given
	
	A:	            B:
	SPI0_SCLK  ---  GSPI_CLK
	GPIO_CS    ---  GSPI_CS
	SPI0_MOSI  ---	GSPI_MOSI
	SPI0_MISO  ---	GSPI_MISO
	GPIO_INT   ---	GSPI_INT
	V3.3       ---  V3.3
	GND        ---  GND

Behavior:
	A send 2048 bytes to B about every 500ms and B will send whatever received back to A.
	Every time if A Checks Rx Datas are the same as Tx Datas,then it logs "Succeed" ,else it logs "Failed" and finished.
