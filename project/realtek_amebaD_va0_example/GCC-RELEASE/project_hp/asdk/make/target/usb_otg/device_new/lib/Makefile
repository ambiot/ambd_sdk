
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
HAL_DIR = $(TARGETDIR)/fwlib/ram_hp
DRV_DIR = $(BASEDIR)/component/common/drivers/usb
COM_DIR = $(DRV_DIR)/common_new
LIB_DIR = $(DRV_DIR)/device_new/core
IFLAGS += -I$(COM_DIR)
IFLAGS += -I$(LIB_DIR)
GLOBAL_CFLAGS += -DCONFIG_USB_NEW_STACK_EN
TARGET_LIB = lib_usbd_new

vpath %.c $(HAL_DIR) $(COM_DIR) $(LIB_DIR)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC += $(HAL_DIR)/rtl8721dhp_usb.c \
	$(COM_DIR)/usb_hal.c \
	$(COM_DIR)/usb_os.c \
	$(LIB_DIR)/usbd.c \
	$(LIB_DIR)/usbd_core.c \
	$(LIB_DIR)/usbd_hal.c \
	$(LIB_DIR)/usbd_pcd.c

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS
	$(AR) rvs $(TARGET_LIB).a $(OBJS)
	$(FROMELF) --strip-debug $(TARGET_LIB).a
	$(MOVE) -f $(TARGET_LIB).a $(ROOTDIR)/lib/application

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
