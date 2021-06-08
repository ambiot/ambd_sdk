
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR_OTG = $(BASEDIR)/component/soc/realtek/amebad/fwlib/usb_otg/device
DIR_CLASS = $(BASEDIR)/component/common/drivers/usb/device
ifeq ($(CONFIG_USBD_AUDIO),y)
DIR = $(DIR_CLASS)/audio/src
endif
ifeq ($(CONFIG_USBD_CDC_ACM),y)
DIR = $(DIR_CLASS)/cdc_acm/src
endif
ifeq ($(CONFIG_USBD_HID),y)
DIR = $(DIR_CLASS)/hid/src
endif
ifeq ($(CONFIG_USBD_MSC),y)
DIR = $(DIR_CLASS)/msc/src
IFLAGS += -I$(BASEDIR)/component/common/drivers/sdio/realtek/sdio_host/inc
endif
ifeq ($(CONFIG_USBD_VENDOR),y)
DIR = $(DIR_CLASS)/vendor/src
endif
IFLAGS += -I$(DIR)/../inc
IFLAGS += -I$(DIR_OTG)/inc

vpath %.c $(DIR)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
ifeq ($(CONFIG_USBD_AUDIO),y)
CSRC = $(DIR)/usb_f_uac1.c
endif
ifeq ($(CONFIG_USBD_CDC_ACM),y)
CSRC = $(DIR)/usbd_cdc_acm.c
endif
ifeq ($(CONFIG_USBD_HID),y)
CSRC = $(DIR)/usbd_hid.c
endif
ifeq ($(CONFIG_USBD_MSC),y)
CSRC = $(DIR)/usbd_msc.c \
       $(DIR)/usbd_scsi.c
endif
ifeq ($(CONFIG_USBD_VENDOR),y)
CSRC = $(DIR)/usbd_vendor.c \
       $(DIR)/usbd_vendor_desc.c
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
