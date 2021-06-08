
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/bootloader
CFGDIR = $(BASEDIR)/component/soc/realtek/amebad/fwlib/usrcfg
RAMDIR = $(BASEDIR)/component/soc/realtek/amebad/fwlib/ram_hp
MODULE_IFLAGS = -I$(RAMDIR)/../include/ \

vpath %.c $(DIR) $(CFGDIR) $(RAMDIR)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = \
	$(CFGDIR)/rtl8721dhp_boot_trustzonecfg.c \
	$(CFGDIR)/rtl8721d_bootcfg.c 

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

-include $(DEPS)
