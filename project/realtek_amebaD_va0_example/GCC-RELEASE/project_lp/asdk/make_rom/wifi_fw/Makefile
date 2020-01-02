
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/wifi_fw/rom
MODULE_IFLAGS += -Os
GLOBAL_CFLAGS += -DCONFIG_BUILD_ROM

vpath %.c $(DIR)
#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
# effect __FILE__ print
CSRC = $(DIR)/RTL8721D_Ipsec_ROM.c \
       $(DIR)/RTL8721D_GTK_ROM.c \
       $(DIR)/RTL8721D_Packet_ROM.c \
       $(DIR)/RTL8721D_PowerSave_ROM.c \
       $(DIR)/RTL8721D_WoWLAN_ROM.c \
       $(DIR)/RTL8721D_BTConCurr_ROM.c \
       $(DIR)/RTL8721D_cmd_ROM.c \
       $(DIR)/RTL8721D_FWLBK_ROM.c \
       $(DIR)/RTL8721D_INT_ROM.c \
       $(DIR)/RTL8721D_PhyCfg_ROM.c \
       $(DIR)/RTL8721D_RateAdaptive_ROM.c \
       $(DIR)/RTL8721D_TxReport_ROM.c \
       $(DIR)/RTL8721D_DMA_ROM.c \
       $(DIR)/RTL8721D_Init_ROM.c \
       $(DIR)/RTL8721D_Util_ROM.c 

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all: CORE_TARGETS RENAME_ROM_OBJS COPY_ROM_OBJS

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
	$(REMOVE) *.c

-include $(DEPS)
