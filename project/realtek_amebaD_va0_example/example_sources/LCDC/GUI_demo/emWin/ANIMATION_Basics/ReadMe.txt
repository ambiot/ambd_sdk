This demo is used to display Animation effects. Follow these steps:

1. Copy src foloder to (project_name)\src folder to replace the original one.
2. Copy Config\LCDConf.c to component\common\ui\emwin\Config\rtl8721d to replace the original one.
3. Enable PSRAM in rtl8721dhp_intfcfg.c if VRAM is allocated in PSRAM.
4. make menuconfig -> 'GUI Config' -> 'Enable GUI' -> select 'emWin'
5. Make and download image.

