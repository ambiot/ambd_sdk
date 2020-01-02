
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR_OTG = $(BASEDIR)/component/soc/realtek/amebad/fwlib/usb_otg/device
DIR_CORE = $(DIR_OTG)/core/src
DIR_COMP = $(DIR_OTG)/composite/src
IFLAGS += -I$(DIR_CORE)/../inc
IFLAGS += -I$(DIR_COMP)/../inc

vpath %.c $(DIR_CORE) $(DIR_COMP)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC += $(DIR_CORE)/dwc_common_os.c \
	$(DIR_CORE)/dwc_otg_cil.c \
	$(DIR_CORE)/dwc_otg_cil_intr.c \
	$(DIR_CORE)/dwc_otg_common.c \
	$(DIR_CORE)/dwc_otg_driver.c \
	$(DIR_CORE)/dwc_otg_driver_rom.c \
	$(DIR_CORE)/usb.c \
	$(DIR_CORE)/dwc_otg_pcd.c \
	$(DIR_CORE)/dwc_otg_pcd_intr.c \
	$(DIR_CORE)/dwc_otg_pcd_os.c \
	$(DIR_CORE)/usb_ep_autoconfig.c \
	$(DIR_COMP)/usb_composite_rom.c \
        $(DIR_COMP)/usb_config_rom.c \
        $(DIR_COMP)/usb_multi.c
	
#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))
	
#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS
	$(AR) rvs lib_usbd.a $(OBJS)
	$(MOVE) -f lib_usbd.a $(ROOTDIR)/lib/application
	
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

-include $(DEPS)
