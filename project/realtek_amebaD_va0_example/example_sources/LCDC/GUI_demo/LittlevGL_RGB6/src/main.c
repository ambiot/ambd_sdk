/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"
#include "ameba_soc.h"
#include "bsp_rgb_lcd.h"
#include "lv_rtroller.h"

/**********************
 *  VARIABLES
 **********************/
 xSemaphoreHandle mutex;


/* Flush the content of the internal buffer the specific area on the display
 * You can use DMA or any hardware acceleration to do this operation in the background but
 * 'lv_flush_ready()' has to be called when finished
 * This function is required only when LV_VDB_SIZE != 0 in lv_conf.h*/
static void ex_disp_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/

    int32_t x;
    int32_t y;
    for(y = y1; y <= y2; y++) {
        for(x = x1; x <= x2; x++) {
            /* Put a pixel to the display. */
			RgbLcdDrawPointColor(x, y, color_p->full);
			
            color_p++;
        }
    }

    /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
    lv_flush_ready();
}


/* Write a pixel array (called 'map') to the a specific area on the display
 * This function is required only when LV_VDB_SIZE == 0 in lv_conf.h*/
static void ex_disp_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/

    int32_t x;
    int32_t y;
    for(y = y1; y <= y2; y++) {
        for(x = x1; x <= x2; x++) {
            /* Put a pixel to the display. */
			RgbLcdDrawPointColor(x, y, color_p->full);
			
            color_p++;
        }
    }
}


/* Write a pixel array (called 'map') to the a specific area on the display
 * This function is required only when LV_VDB_SIZE == 0 in lv_conf.h*/
static void ex_disp_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2,  lv_color_t color)
{
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/

    int32_t x;
    int32_t y;
    for(y = y1; y <= y2; y++) {
        for(x = x1; x <= x2; x++) {
            /* Put a pixel to the display. */
			RgbLcdDrawPointColor(x, y, color.full);
        }
    }

    (void)color; /*Just to avid warnings*/
}

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void lv_config(void)
{
    /***********************
     * Initialize LittlevGL
     ***********************/
    lv_init();

    /***********************
     * Display interface
     ***********************/
    RgbLcdInit();									/*Initialize your display*/
	RgbLcdDisplayDir(HORIZONTAL_SCREEN);
	RgbLcdSetBkColor(WHITE);
	RgbLcdClear();

    lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/
    disp_drv.disp_flush = ex_disp_flush;            /*Used in buffered mode (LV_VDB_SIZE != 0  in lv_conf.h)*/
    disp_drv.disp_fill = ex_disp_fill;              /*Used in unbuffered mode (LV_VDB_SIZE == 0  in lv_conf.h)*/
    disp_drv.disp_map = ex_disp_map;                /*Used in unbuffered mode (LV_VDB_SIZE == 0  in lv_conf.h)*/

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);

}

void lv_task_exc(void)
{
    /*************************************
     * Run the task handler of LittlevGL
     *************************************/
    while(1) {
        /* Periodically call this function.
         * The timing is not critical but should be between 1..10 ms */
		xSemaphoreTake(mutex, portMAX_DELAY);
        lv_task_handler();
		xSemaphoreGive(mutex);

		vTaskDelay(5);
    }

	vTaskDelete(NULL);
}
	
void lv_demo_show(void)
{
	xSemaphoreTake(mutex, portMAX_DELAY);
	/****************
	* BACK GROUND
	****************/
	static lv_style_t stylebk;
	lv_style_copy(&stylebk, &lv_style_plain);
	stylebk.body.main_color = LV_COLOR_BLACK;
	stylebk.body.grad_color = LV_COLOR_BLACK;
	stylebk.body.opa = LV_OPA_COVER;
	lv_obj_set_style(lv_scr_act(), &stylebk);

	/****************
	* ADD A RTROLLER
	****************/

	rtroller new_roller;
	new_roller.disp_num=7;
	new_roller.num=7;
	new_roller.label_space=0;
	new_roller.sel_font_hight=40;
	new_roller.letter_space=4;
	new_roller.font_pp=85;
	char* str[7]={"COTTON","QUICK 15","MEMORY","WOOL","DELICATE","SYNTHETIC","COTTON ECO"};
	new_roller.options=str;
	new_roller.sel_index=2;
	new_roller.anim_time=250;
	new_roller.is_loop=1;
	new_roller.sel_style=NULL;
	new_roller.bg_style=NULL;
	new_roller.anim=NULL;
	lv_obj_t * rtroller_obj=lv_rtroller_create(lv_scr_act(), &new_roller);
	lv_rtroller_set_pos(&new_roller, 260, 28);

	/****************
	* ADD A BAR
	****************/
	lv_obj_t * bar1 = lv_bar_create(lv_scr_act(), NULL);
	lv_obj_set_size(bar1, 200, 25);
	lv_obj_set_pos(bar1, 40, 220);
	lv_bar_set_value(bar1, 40);
	lv_obj_t * bar2 = lv_bar_create(lv_scr_act(), NULL);
	lv_obj_set_size(bar2, 200, 25);
	lv_obj_set_pos(bar2, 40, 185);
	lv_bar_set_value(bar2, 30);
	
	static lv_style_t style_bar1, style_indic1;
	static lv_style_t style_bar2, style_indic2;
	lv_style_copy(&style_bar1, &lv_style_pretty);
	style_bar1.body.main_color = LV_COLOR_MAKE(0x43,0xcd,0x80);
	style_bar1.body.grad_color =  LV_COLOR_MAKE(0x43,0xcd,0x80);
	style_bar1.body.radius = LV_RADIUS_CIRCLE;
	style_bar1.body.opa=70;
	style_bar1.body.border.width = 0;
	lv_style_copy(&style_indic1, &lv_style_pretty);
	style_indic1.body.grad_color =  LV_COLOR_MAKE(0x43,0xcd,0x80);
	style_indic1.body.main_color=  LV_COLOR_MAKE(0x43,0xcd,0x80);
	style_indic1.body.padding.hor = 0;          
	style_indic1.body.padding.ver = 0;
	lv_style_copy(&style_bar2, &style_bar1);
	style_bar2.body.main_color = LV_COLOR_MAKE(0xbf,0xef,0xff);
	style_bar2.body.grad_color = LV_COLOR_MAKE(0xbf,0xef,0xff);
	lv_style_copy(&style_indic2, &style_indic1);
	style_indic2.body.grad_color =  LV_COLOR_MAKE(0xbf,0xef,0xff);
	style_indic2.body.main_color=  LV_COLOR_MAKE(0xbf,0xef,0xff);

	lv_bar_set_style(bar1, LV_BAR_STYLE_BG, &style_bar1);
	lv_bar_set_style(bar1, LV_BAR_STYLE_INDIC, &style_indic1);
	lv_bar_set_style(bar2, LV_BAR_STYLE_BG, &style_bar2);
	lv_bar_set_style(bar2, LV_BAR_STYLE_INDIC, &style_indic2);
	
	static lv_style_t charge_style1;
	lv_style_copy(&charge_style1, &lv_style_plain);
	charge_style1.text.color = LV_COLOR_MAKE(0x43,0xcd,0x80);
	static lv_style_t charge_style2;
	lv_style_copy(&charge_style2, &lv_style_plain);
	charge_style2.text.color =LV_COLOR_MAKE(0xbf,0xef,0xff);

	lv_obj_t * charge_txt1 = lv_label_create(lv_scr_act(), NULL);
	lv_obj_set_style(charge_txt1, &charge_style1);
	lv_label_set_align(charge_txt1, LV_LABEL_ALIGN_CENTER);
	lv_label_set_text(charge_txt1, SYMBOL_CHARGE);
	lv_obj_set_pos(charge_txt1, 20, 220);
	lv_obj_align(charge_txt1, bar1, LV_ALIGN_OUT_LEFT_MID, -10, 0);
	lv_obj_t * charge_txt2 = lv_label_create(lv_scr_act(), NULL);
	lv_obj_set_style(charge_txt2, &charge_style2);
	lv_label_set_align(charge_txt2, LV_LABEL_ALIGN_CENTER);
	lv_label_set_text(charge_txt2, SYMBOL_AUDIO);
	lv_obj_set_pos(charge_txt2, 16, 185);
	lv_obj_align(charge_txt1, bar1, LV_ALIGN_OUT_LEFT_MID, -10, 0);

	/****************
	* ADD A LABEL
	****************/	
	static lv_style_t time_style;
	lv_style_copy(&time_style, &lv_style_plain);
	time_style.text.font = &roboto80;
	time_style.text.letter_space = 15;
	time_style.text.opa=255;
	time_style.text.line_space = 1;
	time_style.text.color = LV_COLOR_WHITE;
	
	lv_obj_t * time_txt = lv_label_create(lv_scr_act(), NULL);
	lv_obj_set_style(time_txt, &time_style); 		
	lv_label_set_align(time_txt, LV_LABEL_ALIGN_CENTER); 
	lv_label_set_text(time_txt, "1:20");
	lv_obj_set_pos(time_txt, 60, 30);
	
	static lv_style_t type_style;
	lv_style_copy(&type_style, &lv_style_plain);
	type_style.text.font = &roboto28;
	type_style.text.letter_space = 3;
	type_style.text.line_space = 0;
	type_style.text.opa=160;
	type_style.text.color = LV_COLOR_WHITE;
	
	lv_obj_t * txt = lv_label_create(lv_scr_act(), NULL);
	lv_obj_set_style(txt,&type_style);
	lv_label_set_text(txt, "daily cotton\n  or fibre");
	lv_obj_set_pos(txt, 60, 120);
	
	xSemaphoreGive(mutex);
	vTaskDelay(1000);

	for(int i=0;i<new_roller.num+2;i++){
		xSemaphoreTake(mutex, portMAX_DELAY);
		lv_rtroller_scroll(&new_roller, 0);
		lv_bar_set_value_anim(bar1, lv_bar_get_value(bar1)+4, 250);
		lv_bar_set_value_anim(bar2, lv_bar_get_value(bar2)+5, 250);
		xSemaphoreGive(mutex);
		vTaskDelay(1000);
		
	}
	for(int i=0;i<new_roller.num+2;i++){
		xSemaphoreTake(mutex, portMAX_DELAY);
		lv_rtroller_scroll(&new_roller, 1);
		lv_bar_set_value_anim(bar1, lv_bar_get_value(bar1)-4, 250);
		lv_bar_set_value_anim(bar2, lv_bar_get_value(bar2)-5, 250);
		xSemaphoreGive(mutex);
		vTaskDelay(1000);
		
	}
	
	xSemaphoreGive(mutex);;
	vTaskDelay(1000);

	vTaskDelete(NULL);
}

void main(void)
{
	lv_config();

	/* Note!!! LittlevGL is not thread-safe. 
	* Users should use a mutex to avoid concurrent calling of LittlevGL functions. */
	mutex = xSemaphoreCreateMutex();

	xTaskCreate((TaskFunction_t )lv_task_exc, 
				(const char*)"lv_config", 
				(uint16_t		)2048, 
				(void*			)NULL, 
				(UBaseType_t	)tskIDLE_PRIORITY + 1, 
				(TaskHandle_t*	)NULL);

	xTaskCreate((TaskFunction_t )lv_demo_show,
				(const char*)"lv_show", 
				(uint16_t		)2048, 
				(void*			)NULL, 
				(UBaseType_t	)tskIDLE_PRIORITY + 1, 
				(TaskHandle_t*	)NULL);

	/* Enable Schedule, Start Kernel */
	vTaskStartScheduler();
}

