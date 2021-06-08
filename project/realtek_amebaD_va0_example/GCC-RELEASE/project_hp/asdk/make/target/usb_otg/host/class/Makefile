
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR_OTG = $(BASEDIR)/component/soc/realtek/amebad/fwlib/usb_otg/host
DIR_CLASS = $(BASEDIR)/component/common/drivers/usb/host
ifeq ($(CONFIG_USBH_MSC),y)
DIR = $(DIR_CLASS)/msc/src
endif
ifeq ($(CONFIG_USBH_UVC),y)
DIR = $(DIR_CLASS)/uvc/src
IFLAGS += -I$(BASEDIR)/component/common/video/v4l2/inc
endif
ifeq ($(CONFIG_USBH_VENDOR),y)
DIR = $(DIR_CLASS)/vendor/src
endif
ifeq ($(CONFIG_USBH_CDC_ACM),y)
DIR = $(DIR_CLASS)/cdc_acm/src
endif
IFLAGS += -I$(DIR)/../inc
IFLAGS += -I$(DIR_OTG)/inc

vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
ifeq ($(CONFIG_USBH_MSC),y)
CSRC = $(DIR)/us.c \
    $(DIR)/us_intf.c \
    $(DIR)/us_scsi.c \
    $(DIR)/us_transport.c \
    $(DIR)/us_protocol.c \
    $(DIR)/us_initializers.c \
    $(DIR)/usual_tables.c \
    $(DIR)/us_debug.c \
    $(DIR)/scsi/scsi_eh.c
endif

ifeq ($(CONFIG_USBH_UVC),y)
CSRC = $(DIR)/uvc_ctrl.c \
    $(DIR)/uvc_driver.c \
    $(DIR)/uvc_intf.c \
    $(DIR)/uvc_queue.c \
    $(DIR)/uvc_status.c \
    $(DIR)/uvc_v4l2.c \
    $(DIR)/uvc_video.c
endif

ifeq ($(CONFIG_USBH_VENDOR),y)
CSRC = $(DIR)/usbh_vendor.c
endif

ifeq ($(CONFIG_USBH_CDC_ACM),y)
CSRC = $(DIR)/usbh_cdc_acm.c
endif

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
	$(REMOVE) *.d
	$(REMOVE) *.i
	$(REMOVE) *.o
	$(REMOVE) *.s
	$(REMOVE) *.su

-include $(DEPS)	
