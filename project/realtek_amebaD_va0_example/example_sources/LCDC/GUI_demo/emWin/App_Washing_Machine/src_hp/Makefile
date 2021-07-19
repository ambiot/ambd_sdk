
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(SRCDIR)

MODULE_IFLAGS = -I$(DIR)./

vpath %.c $(DIR)
#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/main.c \
	$(DIR)/_danhonggan.c \
	$(DIR)/_dantuoshui.c \
	$(DIR)/_piaoxituoshui.c \
       $(DIR)/_suxi.c \
       $(DIR)/_tongzijie.c \
       $(DIR)/2t.c \
       $(DIR)/6m.c \
       $(DIR)/12h.c \
       $(DIR)/30m.c \
       $(DIR)/30s.c \
       $(DIR)/48m.c \
       $(DIR)/bm_bkb.c \
       $(DIR)/clean.c \
       $(DIR)/danhonggan.c \
       $(DIR)/dantuoshui.c \
       $(DIR)/dry.c \
       $(DIR)/fast.c \
       $(DIR)/Home.c \
       $(DIR)/honggan.c \
       $(DIR)/MainTask.c \
       $(DIR)/piaoxi.c \
       $(DIR)/piaoxituoshui.c \
       $(DIR)/setting.c \
       $(DIR)/start.c \
       $(DIR)/suxi.c \
       $(DIR)/suxi_small.c \
       $(DIR)/tongzijie.c \
       $(DIR)/tongzijie_small.c \
       $(DIR)/tuoshui.c \
       $(DIR)/wash.c \
       $(DIR)/warm.c \
       $(DIR)/Wifi_1.c \
       $(DIR)/xiatongmoshi.c \
       $(DIR)/xidi.c \
       $(DIR)/back.c \
       $(DIR)/ok.c \
       $(DIR)/close.c \
       $(DIR)/suzhoushi.c \
       $(DIR)/sheshidu.c \
       $(DIR)/qingtian.c \
       $(DIR)/xiaoyu.c \
       $(DIR)/duoyun.c \
       $(DIR)/GoodWash.c \
       $(DIR)/GoodWarm.c \
       $(DIR)/BadWash.c \
       $(DIR)/MachineWarm.c \
       $(DIR)/bms_rain.c \
       $(DIR)/bmsunny.c \
       $(DIR)/bmcloudy.c \
       

       
       
      
	   
	      
	  

	  

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all: CLEAN_OBJS CORE_TARGETS COPY_RAM_OBJS
	
#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)	
