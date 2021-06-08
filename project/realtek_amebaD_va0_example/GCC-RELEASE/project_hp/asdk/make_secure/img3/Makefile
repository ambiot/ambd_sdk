
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/img3
FWDIR = $(BASEDIR)/component/soc/realtek/amebad/fwlib

MODULE_IFLAGS = -I$(DIR)./
MODULE_IFLAGS += -O0

vpath %.c $(DIR) $(FWDIR)/usrcfg $(FWDIR)/ram_common

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC += $(DIR)/boot_img3.c \
	$(DIR)/rtl8721dhp_crc.c \
	$(DIR)/secure_src.c \
	$(DIR)/secure_efuse.c

CSRC += $(FWDIR)/usrcfg/rtl8721dhp_intfcfg.c \
	$(FWDIR)/ram_common/rtl8721d_adc.c \
	$(FWDIR)/ram_common/rtl8721d_ram_libc.c

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS COPY_RAM_OBJS

#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS:	$(OBJS)


#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d
