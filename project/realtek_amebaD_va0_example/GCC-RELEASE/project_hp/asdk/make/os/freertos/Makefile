
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/os/freertos
DIR_OSDEP = $(BASEDIR)/component/os/os_dep

vpath %.c $(DIR) $(DIR_OSDEP)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/freertos_backtrace_ext.c\
       $(DIR)/freertos_service.c \
       $(DIR)/freertos_heap5_config.c \
       $(DIR_OSDEP)/device_lock.c \
       $(DIR_OSDEP)/osdep_service.c \
       $(DIR_OSDEP)/psram_reserve.c \

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS NETWORK_RENAME_CODE2SRAM COPY_RAM_OBJS

#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

%.o:%.c
	$(CC) $(GLOBAL_CFLAGS) $(MODULE_IFLAGS) $<  -o $@

#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS 
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d
	
-include $(DEPS)



