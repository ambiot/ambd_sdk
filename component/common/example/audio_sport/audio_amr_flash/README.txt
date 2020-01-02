This amr example is used to play amr files from the flash. In order to run the example the following steps must be followed.

	1. Set the parameter CONFIG_EXAMPLE_AUDIO_AMR_FLASH to 1 in platform_opts.h file
	   
	2. In Cygwin terminal, change to the directory ”project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp”, 
	type ”make menuconfig”, and enable audio related configurations (MENUCONFIG FOR CHIP CONFIG -> Audio Config -> Enable Audio).
	
	3. In the example file "example_audio_amr_flash.c" set the config parameters in the start of the file

		-->NB_SP_DMA_PAGE_SIZE or WB_SP_DMA_PAGE_SIZE :- Should be set to 320 for amrnb or 640 for amrwb.
		-->NUM_CHANNELS :- Should be set to CH_MONO.
		-->SAMPLING_FREQ:- Check the properties of the amr file to determine the sampling frequency and choose the appropriate macro.

		The default values of the parameters are pre-set to the values of the sample audio file provided in the folder, in case you are using your own audio file please change the above parameters to the parameters for your audio file else the audio will not be played properly.

	4. Build and flash the binary to test

[Supported List]
	Supported :
	    Ameba-D
	Source code not in project:
	    Ameba-1, Ameba-z, Ameba-pro

[Compilation Tips]
	1. WI-FI and Network are needed in order to run this example. If you don't need WI-FI and Network, change "#define CONFIG_EXAMPLE_WLAN_FAST_CONNECT	1"
	to "#define CONFIG_EXAMPLE_WLAN_FAST_CONNECT 0" in platform_opts.h file, then, in project/realtek_amebaD_va0_example/src/src_hp/main.c
	move these 2 function calls -- pre_example_entry() and example_entry()-- out of the "#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)" area.
	
	2. When WI-FI and Network are off, the program may not run in a normal way due to the default small heap size. 
	You can set configTOTAL_HEAP_SIZE to ( ( size_t ) ( 250 * 1024 ) ) to make sure that ram allocated is enough to run this example.
	
	3. In IAR, you need to include lib_amr.a under "km4_application/lib" and .c file in this folder under "km4_application/utilities/example".