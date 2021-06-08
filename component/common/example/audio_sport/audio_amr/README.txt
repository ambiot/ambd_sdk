This amr example is used to play amr files from the SDCARD. In order to run the example the following steps must be followed.

	1. Set the parameter CONFIG_EXAMPLE_AUDIO_AMR to 1 in platform_opts.h file
	
	2. In Cygwin terminal, change to the directory ”project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp”, 
	type ”make menuconfig”, and enable audio related configurations (MENUCONFIG FOR CHIP CONFIG -> Audio Config -> Enable Audio).

	3. In the example file "example_audio_amr.c" set the config parameters in the start of the file

		-->NUM_CHANNELS :- set as CH_MONO in this example. You should change this according to your own application.
		-->NB_SAMPLING_FREQ :- sample rate of amr-nb format is 8KHz
		-->WB_SAMPLING_FREQ :- sample rate of amr-nb format is 16KHz
		-->AMRNB_FILE_NAME :- Specify the NB file name you wish to play that is present in the SDCARD. "sound.amr" is used as an example here.
		-->AMRWB_FILE_NAME :- Specify the WB file name you wish to play that is present in the SDCARD. "sound-wb.amr" is used as an example here.
		
		The default values of the parameters are pre-set to the values of the sample audio file provided in the folder, in case you are using your own audio file please change the above parameters to the parameters for your audio file else the audio will not be played properly.

	4. Build and flash the binary to test

[Supported List]
	Supported :
	    Ameba-D(Only audio decoding is available now. So you can't define WRITE_RAW_DATA_SD and AMR_ENC_EN to 1).
	Source code not in project:
	    Ameba-1, Ameba-z, Ameba-pro

[Compilation Tips]
	1. You need to turn WI-FI and Network on to make sure the entry of this example will be called automatically. If not, you need to 
	call it on your own.
	
	2. You may need to change the value of configTOTAL_HEAP_SIZE defined in project\realtek_amebaD_va0_example\inc\inc_hp\FreeRTOSConfig.h 
	to make sure that ram allocated is enough to run this example.
	
	3. In IAR, you need to include lib_amr.a under "km4_application/lib" and example_audio_amr.c file in this folder under "km4_application/utilities/example"
	
	4. Since SD card is needed, in component\soc\realtek\amebad\fwlib\usrcfg\rtl8721dhp_intfcfg.c, set both sdioh_cd_pin and sdioh_wp_pin to _PNC