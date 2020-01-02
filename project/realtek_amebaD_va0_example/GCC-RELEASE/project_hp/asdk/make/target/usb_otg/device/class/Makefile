
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR_OTG = $(BASEDIR)/component/soc/realtek/amebad/fwlib/usb_otg/device
ifeq ($(CONFIG_USBD_AUDIO),y)
DIR = $(DIR_OTG)/class/audio/src
endif
ifeq ($(CONFIG_USBD_CDC_ACM),y)
DIR = $(DIR_OTG)/class/cdc_acm/src
endif
ifeq ($(CONFIG_USBD_MSC),y)
DIR = $(DIR_OTG)/class/msc/src
IFLAGS += -I$(BASEDIR)/component/common/drivers/sdio/realtek/sdio_host/inc
endif
IFLAGS += -I$(DIR_OTG)/class
IFLAGS += -I$(DIR_OTG)/core/inc
IFLAGS += -I$(DIR_OTG)/composite/inc

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
ifeq ($(CONFIG_USBD_MSC),y)
CSRC = $(DIR)/usbd_msc.c \
       $(DIR)/usbd_scsi.c
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
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)	
