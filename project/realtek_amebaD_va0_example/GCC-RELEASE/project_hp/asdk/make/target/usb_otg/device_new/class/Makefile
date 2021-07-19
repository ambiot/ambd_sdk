
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DRV_DIR = $(BASEDIR)/component/common/drivers/usb
COM_DIR = $(DRV_DIR)/common_new
DEV_DIR = $(DRV_DIR)/device_new
IFLAGS += -I$(COM_DIR)
IFLAGS += -I$(DEV_DIR)/core
ifeq ($(CONFIG_USBD_CDC_ACM),y)
DIR = $(DEV_DIR)/cdc_acm
endif
IFLAGS += -I$(DIR)

vpath %.c $(DIR)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
ifeq ($(CONFIG_USBD_CDC_ACM),y)
CSRC = $(DIR)/usbd_cdc_acm.c
endif

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
COPY_RAM_OBJS: CORE_TARGETS
all: COPY_RAM_OBJS

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
	$(REMOVE) *.s*
	$(REMOVE) *.d

-include $(DEPS)
