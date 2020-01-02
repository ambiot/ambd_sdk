OTA OVER SD CARD UPDATING EXAMPLE

Description:
Download ota.bin from SD card if target file presented.
To perform this example, please make sure the target OTA file is within SD card file system.
Also, we recommend to rename the OTA file as some vendor specified name, e.g. ota_is_realtek.bin.

Configuration:
[example_ota_http.c]
	Modify FILENAME as the target OTA file in SD card.
	eg: #define FILENAME	"ota_is_realtek.bin"

[platform_opts.h]
	#define CONFIG_EXAMPLE_OTA_SDCARD    1
[ota_8195b.h]
	#define SDCARD_OTA_UPDATE	

Execution:
A OTA over SD card example thread will be started automatically when booting.

[Supported List]
	Supported :
	    Ameba-pro
	Source code not in project:
	    Ameba-1, Ameba-z