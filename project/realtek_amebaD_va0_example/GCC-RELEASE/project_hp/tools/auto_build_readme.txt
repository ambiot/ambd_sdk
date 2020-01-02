1.	Build设置
	a)	打开mbed api
		i.	asdk\make\Makefile: 确认打开了@make -C mbed all（default已打开）
		ii.	asdk\make\mbed\Makefile: 打开*_api.c
	b)	关闭captouch&keyscan以免影响GPIO test: rtl8721dlp_app_start.c , main中
		i.	//app_captouch_init(); /* 1uA */
		ii.	//app_keyscan_init(); /* 5uA */
	c)	To make I2C/mbed/i2c_epl2197_heartrate: add following to asdk\Makefile
		LINK_APP_LIB += $(ROOTDIR)/../example_sources/I2C/mbed/i2c_epl2197_heartrate/src/hr_library.a
2.	Build 
	a)	Cygwin 中输入cd tools
	b)	输入./auto_build.sh
	c)	bin文档和build log在文件夹peripheral_xxxxxxxx_xxxxxx
3.	auto_build.sh
	b)	build_default: build km0 & km4 default image
	c)	build_example interface.txt: build examples in interface.txt
	d)	build_example application.txt: build examples in application.txt
	e)	If building all examples, add following to auto_build.sh
		get_list
		build_example example_list.txt

