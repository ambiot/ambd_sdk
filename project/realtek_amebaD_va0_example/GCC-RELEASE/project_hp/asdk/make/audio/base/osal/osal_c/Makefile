include $(MAKE_INCLUDE_GEN)
IFLAGS               += -I$(BASEDIR)/component/audio/base/log/interfaces
IFLAGS               += -I$(BASEDIR)/component/audio/base/osal/osal_c/interfaces
IFLAGS               += -I$(BASEDIR)/component/audio/base/libs/src/include

.PHONY: lib clean

#*****************************************************************************#
#                                  VARIABLES                                  #
#*****************************************************************************#
DIR = $(BASEDIR)/component/audio/base/osal/osal_c

vpath %.c $(shell find $(DIR)/adapter/freertos -type d)
#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__ -DRSICV_CORE_KR4

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC  = $(DIR)/adapter/freertos/osal_mem.c
CSRC += $(DIR)/adapter/freertos/osal_mutex.c
CSRC += $(DIR)/adapter/freertos/osal_sem.c
CSRC += $(DIR)/adapter/freertos/osal_condition.c
CSRC += $(DIR)/adapter/freertos/osal_thread.c
CSRC += $(DIR)/adapter/freertos/osal_time.c

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                               Dependency	                                  #
#*****************************************************************************#
-include $(OBJS:.o=.d)

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
COPY_RAM_OBJS: CORE_TARGETS

lib: COPY_RAM_OBJS
	$(COPY) $(OBJS) ../../xip/

#*****************************************************************************#
#              GENERATE OBJECT FILE
#*****************************************************************************#
CORE_TARGETS:	$(OBJS)

%.o:%.c
	$(Q)$(CC) $(GLOBAL_CFLAGS) $(MODULE_IFLAGS) $<  -o $@

#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d
