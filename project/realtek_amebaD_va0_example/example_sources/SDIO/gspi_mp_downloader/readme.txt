Example Description

	This example describes SPI Master how to download  firmware to GSPI slave. 
	copy "src/main.c" to cover the original ones under the default project path.
	Users can use their own image to replace default image,do as follows:
	(1)Prepare ram_1.bin & ram_2.bin:	Slave firmware
	(2)Use bin array tools to change ram_1.bin and ram_2.bin to array ram1 and ram2,
	   and copy array ram1 and ram2 to the Master main.c.

Requirement Components:
    2 AmebaZ_DEV01 are needed in this demo:One(AmebaZ-1) is Assigned as SPI master,the other (AmebaZ-2) is Assigned as GSPI slave
	
	AmebaZ-1:SPI master
	SPI0_SCLK :  PA_18
	GPIO_CS   :  PA_28
	SPI0_MOSI :  PA_23
	SPI0_MISO :  PA_22
    
    AmebaZ-2:GSPI slave (must be configured as boot from SDIO)

	SPI_IN  :  PA_22
	SPI_OUT :  PA_20
	SPI_CLK :  PA_21
	SPI_CS  :  PA_19

Build bin files:
	1. example_sources\gspi_mp_downloader\src\main.c
		(A) boot_all.bin & image2_all_ota1.bin: 	Host firmware downloader		

Demo setup:
	Use ImageTool.exe to load firmware (A)  to host. (Highly Recommended: Erase the whole flash first)

	connect AmebaZ-1 and AmebaZ-2 as given
	
	AmebaZ-1   :   AmebaZ-2

	SPI0_SCLK ----  SPI_CLK
	GPIO_CS   ----  SPI_CS
	SPI0_MOSI ----	SPI_OUT
	SPI0_MISO ----	SPI_IN
	V3.3      ---   V3.3
	GND       ---   GND

Behavior:
	1. Slave end boot from SDIO, waiting master end download firmware
	2. Master end download firmware to slave end, and wait slave firmware ready
	3. Slave boot from SDIO Succeeds.