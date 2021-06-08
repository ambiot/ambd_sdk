/**
 * @file lv_rtroller.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"
#include "lv_rtroller.h"
#include "ameba_soc.h"

#define    MIN_OPA                     60			/*min opa value in animation*/
#define    MIN_FONT_HEIGHT	10			/*min font height in animation*/

/**********************
 * GLOBAL VARARIABLES
 **********************/
 
lv_font_t* font_set[13]={&roboto12, &roboto16, &roboto20, &roboto24, &roboto28, &roboto32, &roboto36, &roboto40,
		 			&roboto44, &roboto48, &roboto52, &roboto56, &roboto60};

/**********************
 *   STATIC FUNCTIONS
 **********************/
static lv_coord_t  index_correction(lv_coord_t index, lv_coord_t num)
{
	lv_coord_t  ret;
	if(index<0) 
		ret = index + num;
	else if(index >= num)
		ret = index - num;
	else 
		ret = index;

	return ret;
}


static void init_pos_height_opa(rtroller * new_roller)
{
	lv_coord_t num, i;
	num = new_roller->disp_num;
	for( i = 0; i < num; i ++){
		new_roller->pos[i] = lv_obj_get_y(new_roller->cl[i].cont);
		new_roller->font_height[i] = new_roller->cl[i].label->style_p->text.font->h_px;
		new_roller->opa[i] = new_roller->cl[i].label->style_p->text.opa;
	}
}

 static void rtroller_anim_cb(rtroller * new_roller)
{
	int i;
	if(0 == new_roller->direction){
			for( i = 0; i < new_roller->disp_num; i ++) 
				new_roller->cl[i].index -= 1;
			new_roller->sel_index += 1;
	}else{
			for( i = 0; i < new_roller->disp_num; i ++) 
				new_roller->cl[i].index += 1;
			new_roller->sel_index -= 1;
	}
	for( i = 0; i < new_roller->disp_num; i ++) 
		new_roller->cl[i].index = index_correction(new_roller->cl[i].index, new_roller->disp_num);
	new_roller->sel_index = index_correction(new_roller->sel_index, new_roller->num);
	new_roller->style_flag = 0;
}

static void rtroller_set_y_font(rtroller * new_roller, lv_coord_t y)
{
	lv_coord_t i, flag, move, inc, id, x, ix, a, num, index;
	num = new_roller->disp_num;
	index = new_roller->cl[0].index;

	/*y coordinate of child conts except the edge one*/
	for( i = 0;i < num - 1; i ++){
		move = (new_roller->pos[i + 1]-new_roller->pos[i]) * y /1024;
		if(0 == new_roller->direction){
			lv_obj_set_y(new_roller->cl[index_correction(1 + i + num - index,num)].cont, new_roller->pos[i + 1] - move);
		}else{
			lv_obj_set_y(new_roller->cl[index_correction(num - index + i,num)].cont, new_roller->pos[i] + move);
		}
	}
	
	/*y coordinate of the edge one child cont*/
	if(0 == new_roller->direction){
		ix = index_correction(num - index, num);
		a = 0;
		flag = -1;
	}else{
		ix = index_correction(num - 1 - index, num);
		a = num - 1;
		flag = 1;
	}
	move = (new_roller->font_height[0]) * y /1024;
	id = new_roller->sel_index - flag*(num /2 + 1);
	if(y < 512){
		lv_obj_set_y(new_roller->cl[ix].cont, new_roller->pos[a] + flag * move);
	}else{
		if(0 == new_roller->is_loop){
			if(id >= 0&&id < new_roller->num){
				lv_label_set_text(new_roller->cl[ix].label, new_roller->options[id]);
			}else{
				lv_label_set_text(new_roller->cl[ix].label, "");
			}
		}else{
			id = index_correction(id, new_roller->num);
			lv_label_set_text(new_roller->cl[ix].label, new_roller->options[id]);
		}
		lv_obj_set_y(new_roller->cl[ix].cont, new_roller->pos[num-1-a] - flag * (new_roller->font_height[0] - move));
	}

	/*exchange style between current label and next label*/
	if(0 == new_roller->style_flag && y > 512){
		lv_style_t style;
		lv_coord_t opa, iflag;
		new_roller->style_flag = 1;
		ix = index_correction(num - index + num /2,num);
		iflag = index_correction(ix - flag, num);
		style = new_roller->cl[ix].style;
		new_roller->cl[ix].style = new_roller->cl[iflag].style;
		new_roller->cl[ix].style.text.opa = style.text.opa;
		lv_label_set_style(new_roller->cl[ix].label,&new_roller->cl[ix].style);
		opa = new_roller->cl[iflag].style.text.opa;
		new_roller->cl[iflag].style = style;
		new_roller->cl[iflag].style.text.opa=opa;
		lv_label_set_style(new_roller->cl[iflag].label,&new_roller->cl[iflag].style);
	}

	/*set font height and opa gradient*/
	if(y< 512 ){
		for( i = 0; i< num; i ++){
			inc = new_roller->font_height[i] - (new_roller->font_height[i]-MIN_FONT_HEIGHT) * y /512;
			x = index_correction(num-index + i,num);
			new_roller->cl[x].style.text.font = lv_rtroller_get_font(inc);
			lv_obj_set_style(new_roller->cl[x].label, &new_roller->cl[x].style);
			lv_obj_align(new_roller->cl[x].label, new_roller->cl[x].cont, LV_ALIGN_CENTER, 0, 0);
		}	
	}else{
		for( i = 0; i < num; i ++){
			inc = MIN_FONT_HEIGHT + (new_roller->font_height[index_correction(i + flag,num)] - MIN_FONT_HEIGHT) * (y - 512) /512;
			x = index_correction(num - index + i, num);
			new_roller->cl[x].style.text.font = lv_rtroller_get_font(inc);
			new_roller->cl[x].style.text.opa = new_roller->opa[index_correction(i + flag,num)];
			lv_obj_set_style(new_roller->cl[x].label, &new_roller->cl[x].style);
			lv_obj_align(new_roller->cl[x].label, new_roller->cl[x].cont, LV_ALIGN_CENTER, 0, 0);
		}
	}
}

static void rtroller_pos_calc(rtroller *new_roller)
{
	lv_obj_t * par = lv_obj_get_parent(new_roller->cl[0].cont);
	lv_coord_t num, h, w, i, h_cur, h_next;
	h = lv_obj_get_height(par);
	w = lv_obj_get_width(par);
	num = new_roller->disp_num;
	lv_obj_set_size(new_roller->cl[num /2].cont, w, 1);
	lv_obj_set_pos(new_roller->cl[num /2].cont, 0, h /2 );
	
	for(  i = (num) /2-1;i >= 0;i --){
		h_cur = new_roller->cl[i].label->style_p->text.font->h_px;
		h_next = new_roller->cl[i + 1].label->style_p->text.font->h_px;
		lv_obj_set_size(new_roller->cl[i].cont, w, 1);
		lv_obj_set_pos(new_roller->cl[i].cont, 0, lv_obj_get_y(new_roller->cl[i + 1].cont) - (h_cur + h_next) /2-new_roller->label_space);
		lv_obj_set_size(new_roller->cl[num - 1 - i].cont, w, 1);
		lv_obj_set_pos(new_roller->cl[num -1- i].cont, 0, lv_obj_get_y(new_roller->cl[num - 2 - i].cont) + (h_cur + h_next)/2 + new_roller->label_space);
	}
	for(  i = 0; i < num; i++){
		lv_obj_align(new_roller->cl[i].label, new_roller->cl[i].cont, LV_ALIGN_CENTER, 0, 0);
	}
}


static lv_coord_t cur_sel_calc(rtroller * new_roller)
{
	lv_coord_t cur_sel;
	cur_sel = new_roller->disp_num/2 - new_roller->cl[0].index + new_roller->disp_num;
	cur_sel = index_correction(cur_sel, new_roller->disp_num);

	return cur_sel;
}


/**********************
 *   GLOBAL FUNCTIONS
 **********************/


/**
 * Get a font pointer of according font height
 * @param font_h: font height
 * @return: pointer to a font
 */
lv_font_t* lv_rtroller_get_font(lv_coord_t font_h)
{
	int i = 0;
	lv_font_t* res = NULL;

	for(i = 0; i < sizeof(font_set)/sizeof(lv_font_t*); i++) {
		if(font_h <= lv_font_get_height(font_set[i])) {
			res = font_set[i];
			break;
		}
	}
	
	return res;
}

/**
 * Set the style of selected label
 * @param new_roller: pointer to struct of rtroller 
 * @param style: pointer to a style
 */
void lv_rtroller_set_sel_style(rtroller * new_roller, lv_style_t * style )
{
	lv_coord_t cur_sel=cur_sel_calc(new_roller);
	new_roller->cl[cur_sel].style = *style;
	lv_obj_set_style(new_roller->cl[cur_sel].label, &new_roller->cl[cur_sel].style);
}

/**
 * Get the style of selected label
 * @param new_roller: pointer to struct of rtroller
 * @return: pointer to a style
 */
lv_style_t * lv_rtroller_get_sel_style(rtroller * new_roller )
{
	lv_coord_t cur_sel=cur_sel_calc(new_roller);
	
	return &new_roller->cl[cur_sel].style;
}

/**
 * Set the style of all non-selected labels
 * @param new_roller: pointer to struct of rtroller 
 * @param style: pointer to a style
 */
void lv_rtroller_set_bg_style(rtroller * new_roller, lv_style_t * style )
{
	lv_coord_t cur_sel, font_opa;
	lv_font_t * font;
	cur_sel=cur_sel_calc(new_roller);
	for(int i = 0; i<new_roller->disp_num; i ++){
		if(i != cur_sel){
			font_opa = new_roller->cl[i].style.text.opa;
			font = new_roller->cl[i].style.text.font;
			new_roller->cl[i].style = *style;
			new_roller->cl[i].style.text.opa = font_opa;
			new_roller->cl[i].style.text.font = font;
			lv_obj_set_style (new_roller->cl[i].label, &new_roller->cl[i].style);
		}
	}
}

/**
 * Get the style of a non-selected label
 * @param new_roller: pointer to struct of rtroller
 * @return: pointer to a style
 */
lv_style_t * lv_rtroller_get_bg_style(rtroller * new_roller )
{
	lv_coord_t cur_sel=cur_sel_calc(new_roller);
	cur_sel = index_correction(cur_sel + 1, new_roller->disp_num);
	
	return &new_roller->cl[cur_sel].style;
}

/**
 * Create a rtroller object
 * @param par: parent of rtroller obj  
 * @param new_roller: pointer to struct of rtroller 
 * @return: pointer to rtroller obj
 */
lv_obj_t * lv_rtroller_create(lv_obj_t * par, rtroller * new_roller)
{
	lv_coord_t i, num, tmp_index,cont_height, width, len;
	num = new_roller->disp_num;
	lv_coord_t font_h[num];
	lv_coord_t font_opa[num];
	new_roller->style_flag = 0;

	/*create cont_cover and styles*/
	lv_obj_t * cont_cover = lv_cont_create(par, NULL);
	static lv_style_t cont_style_cover;
	lv_style_copy(&cont_style_cover, &lv_style_plain);
	cont_style_cover.body.opa = LV_OPA_0;
	lv_obj_set_style(cont_cover, &cont_style_cover); 
	static lv_style_t cont_style,label_style;
	lv_style_copy(&cont_style, &lv_style_plain);
	cont_style.body.opa = LV_OPA_0;
	
	/*create child conts and set styles*/
	new_roller->cl = (comb *) lv_mem_alloc(num * sizeof(comb));
	for( i = 0;i<num;i++){
		new_roller->cl[i].index = i;
		new_roller->cl[i].cont = lv_cont_create(cont_cover, NULL);
		lv_obj_set_style(new_roller->cl[i].cont, &cont_style);
	}
	
	/*calculate font height and opa of child labels*/
	font_h[num/2] = new_roller->sel_font_hight;
	font_opa[num/2] = 255;
	lv_coord_t inc = (255-MIN_OPA) /(num /2);
	for( i = num /2-1;i >=  0; i --){
		font_h[i] = font_h[i + 1]*new_roller->font_pp/100;
		font_h[num - 1 - i ] = font_h[i];
		font_opa[i] = font_opa[i + 1] - inc;
		font_opa[num - 1 - i] = font_opa[i];
	}

	/*set text and style of child labels*/
	if(new_roller->bg_style == NULL){
		lv_style_copy(&label_style, &lv_style_plain);
		label_style.text.letter_space  =  new_roller->letter_space;
		label_style.text.color =  LV_COLOR_WHITE;
		for( i = 0; i< num; i ++){
			lv_style_copy(&new_roller->cl[i].style, &label_style);
		}
	}else{
		for( i = 0; i < num; i ++){
			lv_style_copy(&new_roller->cl[i].style, new_roller->bg_style);
		}
	}
	if(new_roller->sel_style != NULL){
		lv_style_copy(&new_roller->cl[num/2].style, new_roller->sel_style);
	}
	for( i = 0; i< num; i ++){
		new_roller->cl[i].style.text.font = lv_rtroller_get_font(font_h[i]);
		new_roller->cl[i].style.text.opa = font_opa[i];
	}
	for( i = 0; i < num; i ++){
		new_roller->cl[i].label =  lv_label_create(cont_cover, NULL);
		lv_label_set_style(new_roller->cl[i].label, &new_roller->cl[i].style);
		lv_label_set_align(new_roller->cl[i].label, LV_LABEL_ALIGN_CENTER);
		if(0 == new_roller->is_loop){
			tmp_index = i + new_roller->sel_index - num /2;
			if(tmp_index >= 0&&tmp_index < new_roller->num){
				lv_label_set_text(new_roller->cl[i].label, new_roller->options[tmp_index]);
			}else{
				lv_label_set_text(new_roller->cl[i].label, "");
			}
		}else{
			tmp_index = index_correction( i + new_roller->sel_index - num /2, new_roller->num);
			lv_label_set_text(new_roller->cl[i].label, new_roller->options[tmp_index]);
		}
	}

	/*calculate cont_cover height*/
	cont_height = new_roller->sel_font_hight;
	if(num>1){
		int j = new_roller->sel_font_hight;
		for(int i = 0;i < (num - 1) /2; i ++){
			j = j * new_roller->font_pp /100;
			cont_height += (j + new_roller->label_space) * 2;
		}
	}
	
	/*calculate longest width of all labels*/
	lv_obj_t * long_label = lv_label_create(par, NULL);
	lv_obj_set_style(long_label, &new_roller->cl[num /2].style);
	lv_label_set_text(long_label, new_roller->options[0]);
	width = lv_obj_get_width(long_label) ;
	for(i = 0; i < new_roller->num-1; i++){
			lv_label_set_text(long_label, new_roller->options[i + 1]);
			len = lv_obj_get_width(long_label) ;
			if(width < len){
				width = len;
			}
		}
	lv_obj_del(long_label);
	width+=2;
	lv_obj_set_size(cont_cover, width, cont_height);
	lv_obj_set_pos(cont_cover, 0, 0);
	rtroller_pos_calc(new_roller);

	/*save postion, height and opa information to rtroller struct*/
	new_roller->pos = (lv_coord_t *)lv_mem_alloc(num * sizeof(lv_coord_t));
	new_roller->font_height = (lv_coord_t*)lv_mem_alloc(num * sizeof(lv_coord_t));
	new_roller->opa = (lv_coord_t* )lv_mem_alloc(num * sizeof(lv_coord_t));
	init_pos_height_opa(new_roller);
	new_roller->cont_cover=cont_cover;
	
	return cont_cover;
}

/**
 * Scroll the rtroller
 * @param new_roller: pointer to struct of rtroller
 * @param direction: direction of rtroller
 *			0: scroll up
 *			others: scroll down
 */
void lv_rtroller_scroll( rtroller * new_roller, bool direction)
{
	new_roller->direction = direction;
	if(0 == new_roller->is_loop){
		if(0 == new_roller->direction){
			if(new_roller->sel_index == (new_roller->num - 1)) 
				return;
		}else{
			if(new_roller->sel_index == 0)
				return;
		}
	}
	if(new_roller->anim!=NULL){
		lv_anim_create(new_roller->anim);
		return;
	}
	lv_anim_t anim;
	anim.var = new_roller;
	anim.start = 0;
	anim.end = 1024;
	anim.fp = (lv_anim_fp_t)rtroller_set_y_font;
	anim.path = lv_anim_path_linear;
	anim.end_cb = rtroller_anim_cb;
	anim.act_time = 0;                         
	anim.time = new_roller->anim_time;                              
	anim.repeat = 0;                              
	anim.playback=0;                          
	anim.playback_pause = 0 ;                                                        
	anim.repeat_pause = 0 ;
	lv_anim_create( &anim);
}

/**
 * Set position of rtroller
 * @param new_roller: pointer to struct of rtroller 
 * @param x: x coordinate 
 * @param y: y coordinate
 */
void lv_rtroller_set_pos(rtroller * new_roller, lv_coord_t x, lv_coord_t y)
{
	lv_obj_set_pos(new_roller->cont_cover, x, y);
}

/**
 * Get position of rtroller
 * @param new_roller: pointer to struct of rtroller
 * @param x: pointer to x coordinate
 * @param y: pointer to y coordinate
 */
void lv_rtroller_get_pos(rtroller * new_roller, lv_coord_t * x, lv_coord_t * y)
{
	*x = lv_obj_get_x(new_roller->cont_cover);
	*y = lv_obj_get_y(new_roller->cont_cover);
}

/**
 * Set size of rtroller
 * @param new_roller: pointer to struct of rtroller 
 * @param w: width of rtroller
 * @param h: height of rtroller
 */
void lv_rtroller_set_size(rtroller * new_roller, lv_coord_t w, lv_coord_t h)
{
	lv_obj_set_size(new_roller->cont_cover, w, h);
	rtroller_pos_calc(new_roller);
	init_pos_height_opa(new_roller);
}

/**
 * Get size of rtroller
 * @param new_roller: pointer to struct of rtroller 
 * @param w: pointer to width 
 * @param h: pointer to height
 */
void lv_rtroller_get_size(rtroller * new_roller,lv_coord_t * w, lv_coord_t * h)
{
	*w = lv_obj_get_width(new_roller->cont_cover);
	*h = lv_obj_get_height(new_roller->cont_cover);
	
}


/**
 * Delete rtroller obj and all of its children, free memory
 * @param obj pointer to an object to delete
 * @param new_roller: pointer to struct of rtroller 
 */
void lv_rtroller_del(rtroller * new_roller)
{	
	int i;
	lv_obj_del(new_roller->cont_cover);
	for( i = 0;i < new_roller->disp_num; i ++){
		lv_obj_del(new_roller->cl[i].cont);
		lv_obj_del(new_roller->cl[i].label);
	}
	lv_mem_free(new_roller->cl);
	lv_mem_free(new_roller->pos);
	lv_mem_free(new_roller->opa);
	lv_mem_free(new_roller->font_height);
}
	
