
include $(MAKE_INCLUDE_GEN)


.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/ui/LittlevGL/lvgl

MODULE_IFLAGS += -I$(DIR)/ \
		 -I$(DIR)/lv_core \
 		 -I$(DIR)/lv_draw \
		 -I$(DIR)/lv_fonts \
		 -I$(DIR)/lv_hal \
		 -I$(DIR)/lv_misc \
		 -I$(DIR)/lv_objx \
		 -I$(DIR)/lv_themes \

vpath %.c $(DIR) $(shell find $(DIR) -type d) 

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC += $(DIR)/lv_core/lv_group.c \
	$(DIR)/lv_core/lv_indev.c \
	$(DIR)/lv_core/lv_obj.c \
	$(DIR)/lv_core/lv_style.c \
	$(DIR)/lv_core/lv_refr.c \
	$(DIR)/lv_core/lv_vdb.c

CSRC += $(DIR)/lv_draw/lv_draw.c \
	$(DIR)/lv_draw/lv_draw_arc.c \
	$(DIR)/lv_draw/lv_draw_img.c \
	$(DIR)/lv_draw/lv_draw_label.c \
	$(DIR)/lv_draw/lv_draw_line.c \
	$(DIR)/lv_draw/lv_draw_rbasic.c \
	$(DIR)/lv_draw/lv_draw_rect.c \
	$(DIR)/lv_draw/lv_draw_triangle.c \
	$(DIR)/lv_draw/lv_draw_vbasic.c

CSRC += $(DIR)/lv_fonts/lv_font_builtin.c \
	$(DIR)/lv_fonts/lv_font_dejavu_10.c \
	$(DIR)/lv_fonts/lv_font_dejavu_10_cyrillic.c \
	$(DIR)/lv_fonts/lv_font_dejavu_10_latin_sup.c \
	$(DIR)/lv_fonts/lv_font_dejavu_20.c \
	$(DIR)/lv_fonts/lv_font_dejavu_20_cyrillic.c \
	$(DIR)/lv_fonts/lv_font_dejavu_20_latin_sup.c \
	$(DIR)/lv_fonts/lv_font_dejavu_30.c \
	$(DIR)/lv_fonts/lv_font_dejavu_30_cyrillic.c \
	$(DIR)/lv_fonts/lv_font_dejavu_30_latin_sup.c \
	$(DIR)/lv_fonts/lv_font_dejavu_40.c \
	$(DIR)/lv_fonts/lv_font_dejavu_40_cyrillic.c \
	$(DIR)/lv_fonts/lv_font_dejavu_40_latin_sup.c \
	$(DIR)/lv_fonts/lv_font_monospace_8.c \
	$(DIR)/lv_fonts/lv_font_symbol_10.c \
	$(DIR)/lv_fonts/lv_font_symbol_20.c \
	$(DIR)/lv_fonts/lv_font_symbol_30.c \
	$(DIR)/lv_fonts/lv_font_symbol_40.c \
	$(DIR)/lv_fonts/roboto12.c \
	$(DIR)/lv_fonts/roboto16.c \
	$(DIR)/lv_fonts/roboto20.c \
	$(DIR)/lv_fonts/roboto24.c \
	$(DIR)/lv_fonts/roboto28.c \
	$(DIR)/lv_fonts/roboto32.c \
	$(DIR)/lv_fonts/roboto36.c \
	$(DIR)/lv_fonts/roboto40.c \
	$(DIR)/lv_fonts/roboto44.c \
	$(DIR)/lv_fonts/roboto48.c \
	$(DIR)/lv_fonts/roboto52.c \
	$(DIR)/lv_fonts/roboto56.c \
	$(DIR)/lv_fonts/roboto60.c \
	$(DIR)/lv_fonts/roboto_thin80.c
	
CSRC += $(DIR)/lv_hal/lv_hal_disp.c \
	$(DIR)/lv_hal/lv_hal_indev.c \
	$(DIR)/lv_hal/lv_hal_tick.c

CSRC += $(DIR)/lv_misc/lv_anim.c \
	$(DIR)/lv_misc/lv_mem.c \
	$(DIR)/lv_misc/lv_area.c \
	$(DIR)/lv_misc/lv_circ.c \
	$(DIR)/lv_misc/lv_color.c \
	$(DIR)/lv_misc/lv_font.c \
	$(DIR)/lv_misc/lv_fs.c \
	$(DIR)/lv_misc/lv_ll.c \
	$(DIR)/lv_misc/lv_log.c \
	$(DIR)/lv_misc/lv_math.c \
	$(DIR)/lv_misc/lv_task.c \
	$(DIR)/lv_misc/lv_templ.c \
	$(DIR)/lv_misc/lv_txt.c \
	$(DIR)/lv_misc/lv_ufs.c

CSRC += $(DIR)/lv_objx/lv_calendar.c \
	$(DIR)/lv_objx/lv_chart.c \
	$(DIR)/lv_objx/lv_ddlist.c \
	$(DIR)/lv_objx/lv_list.c \
	$(DIR)/lv_objx/lv_page.c \
	$(DIR)/lv_objx/lv_roller.c \
	$(DIR)/lv_objx/lv_ta.c \
	$(DIR)/lv_objx/lv_tabview.c \
	$(DIR)/lv_objx/lv_arc.c \
	$(DIR)/lv_objx/lv_bar.c \
	$(DIR)/lv_objx/lv_btn.c \
	$(DIR)/lv_objx/lv_btnm.c \
	$(DIR)/lv_objx/lv_cb.c \
	$(DIR)/lv_objx/lv_cont.c \
	$(DIR)/lv_objx/lv_gauge.c \
	$(DIR)/lv_objx/lv_img.c \
	$(DIR)/lv_objx/lv_imgbtn.c \
	$(DIR)/lv_objx/lv_kb.c \
	$(DIR)/lv_objx/lv_label.c \
	$(DIR)/lv_objx/lv_led.c \
	$(DIR)/lv_objx/lv_line.c \
	$(DIR)/lv_objx/lv_lmeter.c \
	$(DIR)/lv_objx/lv_mbox.c \
	$(DIR)/lv_objx/lv_objx_templ.c \
	$(DIR)/lv_objx/lv_preload.c \
	$(DIR)/lv_objx/lv_slider.c \
	$(DIR)/lv_objx/lv_sw.c \
	$(DIR)/lv_objx/lv_win.c \
	$(DIR)/lv_objx/lv_rtroller.c


CSRC +=	$(DIR)/lv_themes/lv_theme_material.c \
	$(DIR)/lv_themes/lv_theme.c \
	$(DIR)/lv_themes/lv_theme_alien.c \
	$(DIR)/lv_themes/lv_theme_default.c \
	$(DIR)/lv_themes/lv_theme_mono.c \
	$(DIR)/lv_themes/lv_theme_nemo.c \
	$(DIR)/lv_themes/lv_theme_night.c \
	$(DIR)/lv_themes/lv_theme_templ.c \
	$(DIR)/lv_themes/lv_theme_zen.c 

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                               Include Dependency                            #
#*****************************************************************************#
-include $(OBJS:.o=.d)

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all: CORE_TARGETS COPY_RAM_OBJS
#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean: CLEAN_OBJS 
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)
