
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/bootloader
CFGDIR = $(BASEDIR)/component/soc/realtek/amebad/fwlib/usrcfg
DIR_COM = $(BASEDIR)/component/soc/realtek/amebad/fwlib/ram_common
DIR_RAM_LP = $(BASEDIR)/component/soc/realtek/amebad/fwlib/ram_lp
MODULE_IFLAGS = -I$(DIR)/../include/

vpath %.c $(DIR) $(CFGDIR) $(DIR_RAM_LP) $(DIR_COM)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#

CSRC = $(CFGDIR)/rtl8721d_bootcfg.c

CSRC += $(DIR_COM)/rtl8721d_wdg.c 

CSRC += $(DIR_RAM_LP)/rtl8721dlp_clk.c

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
#all: CORE_TARGETS
all: CORE_TARGETS RENAME_LOADER_OBJS COPY_RAM_OBJS

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
	$(REMOVE) *.su

-include $(DEPS)
