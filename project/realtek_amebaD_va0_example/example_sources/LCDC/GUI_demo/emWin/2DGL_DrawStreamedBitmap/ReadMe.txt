This demo is used to test screen. Follow these steps:

1. Copy src_hp foloder to (project_name)\src folder to replace the original one.
2. Copy Config\LCDConf_RGB_6bit_eval(if it exists) to component\common\ui\emwin\Sample\rtl8721d\Config to replace the original one.
3. Make sure that GUI_NUMBYTES in GUI_Conf.c is large than RECOMMENDED_MEMORY in the sample.
4. Enable PSRAM in rtl8721dhp_intfcfg.c if VRAM is allocated in PSRAM.
5. make menuconfig -> 'GUI Config' -> 'Enable GUI' -> select 'emWin'
6. Make and download image.
7. Download the Bitmap_50x50.dta to the flash through image tool, and set its address 0x08106000.

