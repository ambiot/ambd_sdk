
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

MODULE_IFLAGS += -I$(BASEDIR)/component/file_system/fatfs/r0.14

MODULE_IFLAGS += \
    -I$(BASEDIR)/component/audio/base/libs/src/include \
    -I$(BASEDIR)/component/audio/base/log/interfaces \
    -I$(BASEDIR)/component/audio/base/osal/osal_c/interfaces \
    -I$(BASEDIR)/component/audio/base/osal/osal_cxx/interfaces \
    -I$(BASEDIR)/component/audio/base/cutils/interfaces \
    -I$(BASEDIR)/component/audio/base/utils/interfaces \
    -I$(BASEDIR)/component/audio/base/media/audio/audio_utils/include \
    -I$(BASEDIR)/component/audio/frameworks/media/audio/interfaces \
    -I$(BASEDIR)/component/audio/frameworks/media/playback/interfaces

vpath %.cpp $(shell find $(DIR)/libmedia -type d)
#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__ -Wno-multichar -Wno-unused-parameter

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC  = \
    $(DIR)/libmedia/rtplayer.cpp
#    $(DIR)/libmedia/rtdemux.cpp \
#    $(DIR)/libmedia/rtdecoder.cpp \
#    $(DIR)/libmedia/rtmedia_format.cpp

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
