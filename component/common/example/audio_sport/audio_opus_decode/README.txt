This mp3 example is used to play mp3 files from the SDCARD. In order to run the example the following steps must be followed.

	1. Set the parameter CONFIG_EXAMPLE_AUDIO_OPUS_DECODE to 1 in platform_opts.h file
	
    2. In Cygwin terminal, change to the directory "/project/realtek_amebaD_cm4_gcc_verification", 
	type "make menuconfig", and enable audio related configurations (MENUCONFIG FOR CHIP CONFIG -> Audio Config -> Enable Audio).
	
    3. Build and flash the binary to test

[Supported List]
	Supported :
	    Ameba-D
	Source code not in project:

[Compilation Tips]
	1. WI-FI and Network are needed in order to run this example. If you don't need WI-FI and Network, change "#define CONFIG_EXAMPLE_WLAN_FAST_CONNECT	1"
	to "#define CONFIG_EXAMPLE_WLAN_FAST_CONNECT 0" in platform_opts.h file, then, in project/realtek_amebaD_va0_example/src/src_hp/main.c
	move these 2 function calls -- pre_example_entry() and example_entry()-- out of the "#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)" area.
	
	2. When WI-FI and Network are off, the program may not run in a normal way due to the default small heap size. 
	You can set configTOTAL_HEAP_SIZE to ( ( size_t ) ( 250 * 1024 ) ) to make sure that ram allocated is enough to run this example.
	
	3. This example needs a big memory space, or hardfault may happen. You can choose to use RAM only or RAM with PSRAM to run this example.
	In "/component/common/audio/libogg-1.3.3/include/ogg/os_types.h", you can choose either mode by changing macro values on line 20, 21.
	If you "#define RAM  1", set configTOTAL_HEAP_SIZE to ( ( size_t ) ( 400 * 1024 ) ) is enough to run this example.
	If you "#define PSRAM 1", set configTOTAL_HEAP_SIZE to ( ( size_t ) ( 250 * 1024 ) ) is enough to run this example. In this case, remember to enable psram
	use in rtl8721dhp_intfcfg.c.
	
	4. In IAR, you need to include lib_opus.a lib_libogg.a lib_opusfile.a under "km4_application/lib" and .c files in this folder under "km4_application/utilities/example".