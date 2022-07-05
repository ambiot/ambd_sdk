
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES                                     #
#*****************************************************************************#
DIR = $(BASEDIR)/component/audio/frameworks/media/audio/passthrough/tests/audio_track
RECORD_DIR = $(BASEDIR)/component/audio/frameworks/media/audio/passthrough/tests/audio_record
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/frameworks/media/audio/interfaces
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/log/interfaces
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/osal/osal_c/interfaces
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/libs/src/include
MODULE_IFLAGS += -I$(TARGETDIR)/app/hal/interfaces
MODULE_IFLAGS += -I$(DIR)/src

vpath %.c $(shell find $(DIR)/src/ -type d)
vpath %.c $(shell find $(RECORD_DIR)/src/ -type d)

#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__
CPPFLAGS += -Wno-unused-parameter

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/rtaudio_track_test.c
CSRC += $(RECORD_DIR)/rtaudio_record_test.c
#CSRC += $(RECORD_DIR)/rtaudio_record_for_afe.c

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

