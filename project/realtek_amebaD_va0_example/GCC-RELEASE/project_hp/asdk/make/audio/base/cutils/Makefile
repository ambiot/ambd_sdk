
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/audio/base/cutils
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/cutils/interfaces
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/cutils/src/include
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/log/interfaces
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/osal/osal_c/interfaces
TARGET_LIB = lib_cutils

vpath %.c $(shell find $(DIR)/src/ -type d)
#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__
CPPFLAGS += -Wno-unused-parameter

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC  = $(DIR)/src/string.c
CSRC += $(DIR)/src/rtlist.c
CSRC += $(DIR)/src/rtvector.c
CSRC += $(DIR)/src/rtrbtree.c
CSRC += $(DIR)/src/rtintmap.c
CSRC += $(DIR)/src/rtrbmap.c
CSRC += $(DIR)/src/rtringbuffer.c
CSRC += $(DIR)/src/rtlooper.c
CSRC += $(DIR)/src/rtmessage.c
CSRC += $(DIR)/src/rtmessage_handler.c
CSRC += $(DIR)/src/rtlooper_manager.c
CSRC += $(DIR)/src/rtstate_machine.c
CSRC += $(DIR)/src/rtdatabuffer.c
CSRC += $(DIR)/src/rtobject_manager.c

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
	$(AR) rvs lib_cutils.a $(OBJS)
	$(MOVE) -f lib_cutils.a $(ROOTDIR)/lib/application

#*****************************************************************************#
#              GENERATE OBJECT FILE
#*****************************************************************************#
CORE_TARGETS: $(OBJS)


#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)
