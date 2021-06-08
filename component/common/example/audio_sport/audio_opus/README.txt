This opus example explain how to use the opus lib. In the encoding part, it reads wav files from SDCARD and save the encoded opus file back to the SD card.  In the decoding part, it reads the encoded opus file and play it through the hardware codec.

In order to run the example the following steps must be followed.

	1. Set the parameter CONFIG_EXAMPLE_AUDIO_OPUS to 1 in platform_opts.h file
	
	2. In Cygwin terminal, change to the directory ”project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp”, 
	type ”make menuconfig”, and enable audio related configurations (MENUCONFIG FOR CHIP CONFIG -> Audio Config -> Enable Audio).

	3. Build and flash the binary to test

[Supported List]
	Supported :
	    Ameba-D
	Source code not in project:

[Compilation Tips]
	1. You need to turn WI-FI and Network on to make sure the entry of this example will be called automatically. If not, you need to 
	call it on your own.
	
	2. You may need to change the value of configTOTAL_HEAP_SIZE  defined in project\realtek_amebaD_va0_example\inc\inc_hp\FreeRTOSConfig.h 
	to make sure that ram allocated is enough to run this example.
	
	3. This example needs a big memory space, or hardfault may happen. Psram is used in this example, please enable psram use in rtl8721dhp_intfcfg.c(set psram_dev_enable psram_dev_cal_enable psram_dev_retention to TRUE).
	
	4. Since SD card is needed, in component\soc\realtek\amebad\fwlib\usrcfg\rtl8721dhp_intfcfg.c, set both sdioh_cd_pin and sdioh_wp_pin to _PNC