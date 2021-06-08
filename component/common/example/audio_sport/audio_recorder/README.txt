This example is used to record audio data to the SDCARD. In order to run the example the following steps must be followed.

	1. Set the parameter CONFIG_EXAMPLE_AUDIO_RECORDER to 1 in platform_opts.h file

	2. In Cygwin terminal, change to the directory ”project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp”, 
	type ”make menuconfig”, and enable audio related configurations (MENUCONFIG FOR CHIP CONFIG -> Audio Config -> Enable Audio).

	3. Build and flash the binary to test
	
	4. _PA_22 is used to control the flow of recording. When _PA_22 is set to GPIO_PIN_LOW, recording process starts, else, 
	recording process ends.
	
[Supported List]
	Supported :
	    Ameba-D
	Source code not in project:

[Compilation Tips]
	1. You need to turn WI-FI and Network on to make sure the entry of this example will be called automatically. If not, you need to 
	call it on your own.
	
	2. You may need to change the value of configTOTAL_HEAP_SIZE  defined in project\realtek_amebaD_va0_example\inc\inc_hp\FreeRTOSConfig.h 
	to make sure that ram allocated is enough to run this example.
	
	3. In IAR, you need to include example_audio_recorder_iar.c file under "km4_application/utilities/example".