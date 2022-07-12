
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/file_system/fatfs
MODULE_IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/host/msc/inc
MODULE_IFLAGS += -I$(BASEDIR)/component/common/drivers/sdio/realtek/sdio_host/inc
#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC += $(DIR)/disk_if/src/sdcard.c \
	$(DIR)/disk_if/src/usbdisk.c \
	$(DIR)/disk_if/src/flash_fatfs.c \
	$(DIR)/r0.10c/src/ff.c \
	$(DIR)/r0.10c/src/diskio.c \
	$(DIR)/r0.10c/src/option/ccsbcs.c \
	$(DIR)/fatfs_ext/src/ff_driver.c

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(CSRC:.c=.o)

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
