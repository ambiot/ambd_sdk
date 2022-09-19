
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/fwlib/usb_otg/host/src
IFLAGS += -I$(DIR)/../inc

vpath %.c $(DIR)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC += $(DIR)/dwc_common_os.c \
	$(DIR)/dwc_os.c \
	$(DIR)/dwc_otg_cil.c \
	$(DIR)/dwc_otg_cil_intr.c \
	$(DIR)/dwc_otg_common.c \
	$(DIR)/dwc_otg_common_rom.c \
	$(DIR)/dwc_otg_dbg.c \
	$(DIR)/dwc_otg_driver.c \
	$(DIR)/dwc_otg_driver_rom.c \
	$(DIR)/dwc_otg_hcd.c \
	$(DIR)/dwc_otg_hcd_intr.c \
	$(DIR)/dwc_otg_hcd_os.c \
	$(DIR)/dwc_otg_hcd_queue.c \
	$(DIR)/usb.c
	
#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))
	
#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS COPY_RAM_OBJS
	$(AR) rvs lib_usbh.a $(OBJS)
	$(FROMELF) --strip-debug lib_usbh.a
	$(MOVE) -f lib_usbh.a $(ROOTDIR)/lib/application
	
#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS:	$(OBJS)


#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.d
	$(REMOVE) *.i
	$(REMOVE) *.o
	$(REMOVE) *.s
	$(REMOVE) *.su

-include $(DEPS)
