This demo is used to display basic rectangle. Follow these steps:

1. Copy src foloder to (project_name)\src folder to replace the original one.
2. Copy config file in Config folder(if it exists) to component\common\ui\emwin\Config\rtl8721d to replace the original one.
3. Enable PSRAM in rtl8721dhp_intfcfg.c if VRAM is allocated in PSRAM.
4. make sure the GUI_NUMBYTES defined in GUIConf.c is larger than RECOMMENDED_MEMORY defined in sample. 
5. make menuconfig -> 'GUI Config' -> 'Enable GUI' -> select 'emWin'
6. Make and download image.

