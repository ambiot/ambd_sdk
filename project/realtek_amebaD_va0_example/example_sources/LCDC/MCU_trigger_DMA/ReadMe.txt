This demo is used to display 8bit mode MCU LCD. Follow these steps:
	1,Replace the original src folder with this src folder.
	2,make and download image.
	3,you will see that LCD displays RED,GREEN,BLUE cyclically.
 
	
Note that if you want to add demo code to main.c in original src folder instead of replace it, you should delete the function app_init_psram() and its call in main.c in this folder, or you will get a error that app_init_psram() is multiple defined. Then you should config PSRAM accroding to AN document.