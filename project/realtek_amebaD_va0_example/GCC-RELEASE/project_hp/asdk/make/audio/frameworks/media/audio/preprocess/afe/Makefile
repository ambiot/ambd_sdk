
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES                                     #
#*****************************************************************************#
DIR = $(BASEDIR)/component/audio/frameworks/media/audio/preprocess/afe
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/frameworks/media/audio/preprocess/afe/include
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/osal/osal_c/interfaces
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/log/interfaces

vpath %.c $(shell find $(DIR)/src/ -type d)

#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__
GLOBAL_CFLAGS += -DNDEBUG -UDEBUG -DAUDIO_AFE
CPPFLAGS += -Wno-unused-parameter

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/afe_adapter.c

ifeq ($(CONFIG_AUDIO_RPC_AFE),y)
GLOBAL_CFLAGS += -DAUDIO_RPC_AFE
else ifeq($(CONFIG_AUDIO_LOCAL_AFE),y)
GLOBAL_CLFAGS += -DAUDIO_LOCAL_AFE
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

lib: COPY_RAM_OBJS
	$(AR) rvs lib_audio_afe.a $(OBJS)
	$(MOVE) -f lib_audio_afe.a $(ROOTDIR)/lib/application/

##*****************************************************************************#
# GENERATE OBJECT FILE
##*****************************************************************************#

CORE_TARGETS:   $(OBJS)


#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	        $(REMOVE) *.o
		$(REMOVE) *.i
		$(REMOVE) *.s
		$(REMOVE) *.d

-include $(DEPS)

