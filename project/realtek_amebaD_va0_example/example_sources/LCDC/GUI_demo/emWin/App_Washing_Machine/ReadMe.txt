This demo is a Washing machine interface. Follow these steps:

1. Copy src_hp foloder to (project_name)\src folder to replace the original one.
2. Copy Config\LCDConf_RGB_6bit_eval(if it exists) to component\common\ui\emwin\Sample\rtl8721d\Config to replace the original one.
3. Make sure that GUI_NUMBYTES in GUI_Conf.c is large than RECOMMENDED_MEMORY in the sample.
4. Enable PSRAM in rtl8721dhp_intfcfg.c if VRAM is allocated in PSRAM.
5. make menuconfig -> 'GUI Config' -> 'Enable GUI' -> select 'emWin'
6. Make and download image.

File description:

All functions are implemented by file below:
		Maintask.c
		
All bitmap data is in files below:
		_danhonggan.c
		_dantuoshui.c
		_piaoxituoshui.c 
		_suxi.c 
		_tongzijie.c 
		2t.c 
		6m.c 
		12h.c 
		30m.c 
		30s.c 
		48m.c 
		bm_bkb.c 
		clean.c 
		danhonggan.c 
		dantuoshui.c 
		dry.c 
		fast.c 
		Home.c 
		honggan.c 
		MainTask.c 
		piaoxi.c 
		piaoxituoshui.c 
		setting.c 
		start.c 
		suxi.c 
		suxi_small.c 
		tongzijie.c 
		tongzijie_small.c 
		tuoshui.c 
		wash.c 
		warm.c 
		Wifi_1.c 
		xiatongmoshi.c 
		xidi.c 
		back.c 
		ok.c 
		close.c 
		suzhoushi.c 
		sheshidu.c 
		qingtian.c 
		xiaoyu.c 
		duoyun.c 
		GoodWash.c 
		GoodWarm.c 
		BadWash.c 
		MachineWarm.c 
		bms_rain.c 
		bmsunny.c 
		bmcloudy.c 