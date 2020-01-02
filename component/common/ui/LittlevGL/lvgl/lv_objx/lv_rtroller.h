/*********************
 *      INCLUDES
 *********************/


/**********************
 *  FONT DECLARATIONS
 **********************/

LV_FONT_DECLARE(roboto12); 
LV_FONT_DECLARE(roboto16); 
LV_FONT_DECLARE(roboto20); 
LV_FONT_DECLARE(roboto24); 
LV_FONT_DECLARE(roboto28); 
LV_FONT_DECLARE(roboto32); 
LV_FONT_DECLARE(roboto36); 
LV_FONT_DECLARE(roboto40);
LV_FONT_DECLARE(roboto44); 
LV_FONT_DECLARE(roboto48); 
LV_FONT_DECLARE(roboto52); 
LV_FONT_DECLARE(roboto56); 
LV_FONT_DECLARE(roboto60); 
LV_FONT_DECLARE(roboto80);


/**********************
 *      TYPEDEFS
 **********************/
 
typedef struct
{	
	lv_coord_t index;
	lv_obj_t * cont;
	lv_obj_t * label;
	lv_style_t style;
}comb;

typedef struct 
{	
	/*user should set*/
	lv_coord_t num;			/*Number of options*/
	lv_coord_t disp_num;			/*Number of options to display, should be odd*/
	char **options;			/*Pointer to options content*/
	lv_coord_t label_space;			/*Space between labels*/
	lv_coord_t sel_index;			/*Current index of selected option*/
	lv_coord_t sel_font_hight;			/*Font height of seleted option*/
	lv_coord_t font_pp;  			/*Porportion of selected and next font height*/
	lv_coord_t letter_space;		/*Space between letters*/
	bool is_loop;			/*Decide if roller loop. 0: not loop; others: loop*/
	lv_coord_t anim_time;			/*Animation time when rtroller scrolls for default animation. unit is ms */
	lv_anim_t *anim;			/*Animation when rtroller scrolls. NULL means rtroller use default animation */
	lv_style_t * sel_style;			/*style of selected option. NULL means rtroller use default sel_style*/
	lv_style_t * bg_style;			/*style of not selected options. NULL means  rtroller use default bg_style*/
	
       /*System use these - user shouldn't set*/
	bool direction;  
	comb* cl;
	lv_obj_t * cont_cover;
	lv_coord_t *pos;
	lv_coord_t *font_height;
	lv_coord_t *opa;
	lv_coord_t style_flag;
}rtroller;



/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_font_t* lv_rtroller_get_font(lv_coord_t font_h);
void lv_rtroller_set_sel_style(rtroller * new_roller, lv_style_t * style );
lv_style_t * lv_rtroller_get_sel_style(rtroller * new_roller );
void lv_rtroller_set_bg_style(rtroller * new_roller, lv_style_t * style );
lv_style_t * lv_rtroller_get_bg_style(rtroller * new_roller );
lv_obj_t * lv_rtroller_create(lv_obj_t * par, rtroller * new_roller);
void lv_rtroller_scroll( rtroller * new_roller, bool direction);
void lv_rtroller_set_pos(rtroller * new_roller, lv_coord_t x, lv_coord_t y);
void lv_rtroller_set_x(rtroller * new_roller, lv_coord_t x);
void lv_rtroller_set_y(rtroller * new_roller, lv_coord_t y);
lv_coord_t lv_rtroller_get_x(rtroller * new_roller);
lv_coord_t lv_rtroller_get_y(rtroller * new_roller);
void lv_rtroller_set_size(rtroller * new_roller,lv_coord_t w,lv_coord_t h);
void lv_rtroller_set_width(rtroller * new_roller,lv_coord_t w);
void lv_rtroller_set_height(rtroller * new_roller, lv_coord_t h);
lv_coord_t lv_rtroller_get_width(rtroller * new_roller);
lv_coord_t lv_rtroller_get_height(rtroller * new_roller);
void lv_rtroller_del(rtroller * new_roller);

