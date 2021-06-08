This demo is used to display 8bit mode customized MCU LCD which uses ili9488 and has a touch screen. Follow these steps:
	1,Replace the original src folder with this src folder.
	2,make and download image.
	3,you will see that LCD displays points, lines, cycles, blocks, fonts.
	4,finally you can touch the screen and it will display point where you touched.
 
	
Note that if you want to add demo code to main.c in original src folder instead of replace it, you should delete the function app_init_psram() and its call in main.c in this folder, or you will get a error that app_init_psram() is multiple defined. Then you should config PSRAM accroding to AN document.