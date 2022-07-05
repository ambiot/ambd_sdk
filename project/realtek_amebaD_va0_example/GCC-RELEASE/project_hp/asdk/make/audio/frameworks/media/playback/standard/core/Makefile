
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/audio/frameworks/media/playback/stardard

MODULE_IFLAGS += \
    -I$(DIR)/core/include \
    -I$(DIR)/utils/include \
    -I$(DIR)/common/include \
    -I$(DIR)/codec/include \
    -I$(DIR)/source/include \
    -I$(DIR)/demux/include

MODULE_IFLAGS += \
    -I$(BASEDIR)/component/audio/base/libs/src/include \
    -I$(BASEDIR)/component/audio/base/log/interfaces \
    -I$(BASEDIR)/component/audio/base/osal/osal_c/interfaces \
    -I$(BASEDIR)/component/audio/base/osal/osal_cxx/interfaces \
    -I$(BASEDIR)/component/audio/base/cutils/interfaces \
    -I$(BASEDIR)/component/audio/base/utils/interfaces \
    -I$(BASEDIR)/component/audio/base/media/audio/audio_utils/include \
    -I$(BASEDIR)/component/audio/frameworks/media/audio/interfaces \
    -I$(BASEDIR)/component/audio/frameworks/media/playback/interfaces \
    -I$(BASEDIR)/component/audio/frameworks/interfaces \
    -I$(BASEDIR)/component/audio/hal/interfaces \
    -I$(BASEDIR)/component/audio/base/osal/osal_c/interfaces/osal_c \


vpath %.cpp $(shell find $(DIR)/core -type d)
#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__ -Wno-multichar -Wno-unused-parameter #-std=gnu++14

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC  = \
    $(DIR)/core/player_driver.cpp \
    $(DIR)/core/player_core.cpp \
    $(DIR)/core/player_core_decoder_base.cpp \
    $(DIR)/core/player_core_decoder.cpp \
    $(DIR)/core/player_core_renderer.cpp \
    $(DIR)/core/generic_source.cpp \
    $(DIR)/core/audio_output.cpp

#CSRC += $(DIR)/core/rtsp_source.cpp

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.cpp=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
COPY_RAM_OBJS: CORE_TARGETS
all: COPY_RAM_OBJS
	cp *.o  ../../xip

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
	$(REMOVE) *.ii
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)
