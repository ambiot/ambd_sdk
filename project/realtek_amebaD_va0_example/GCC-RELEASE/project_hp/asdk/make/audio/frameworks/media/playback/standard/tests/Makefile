
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/audio/frameworks/media/playback/stardard

MODULE_IFLAGS += \
	-I$(BASEDIR)/component/audio/frameworks/media/playback/interfaces \
	-I$(BASEDIR)/component/file_system/fatfs \
	-I$(BASEDIR)/component/file_system/fatfs/r0.14b/include

MODULE_IFLAGS += \
	-I$(BASEDIR)/component/audio/base/libs/src/include \
	-I$(BASEDIR)/component/audio/base/log/interfaces \
	-I$(BASEDIR)/component/audio/base/osal/osal_c/interfaces \
	-I$(BASEDIR)/component/audio/base/osal/osal_cxx/interfaces \
	-I$(BASEDIR)/component/audio/base/cutils/interfaces \
	-I$(BASEDIR)/component/audio/base/utils/interfaces

ifeq ($(CONFIG_AUDIO_MIXER_SERVICE),y)
MODULE_IFLAGS += \
	-I$(BASEDIR)/component/audio/frameworks/media/audio/interfaces
endif

ifeq ($(CONFIG_AUDIO_MIXER_SERVICE),y)
MODULE_IFLAGS += \
    -I$(BASEDIR)/component/audio/frameworks/media/audio/interfaces
endif

vpath %.c $(shell find $(DIR)/tests -type d)
vpath %.cpp $(shell find $(DIR)/tests -type d)
#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__ -Wno-multichar -Wno-incompatible-pointer-types -Wno-int-conversion -Wno-pointer-sign

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC  = $(DIR)/tests/player_test.c
CPPSRC  = $(DIR)/tests/threads_test.cpp
CSRC += $(DIR)/tests/app_example.c

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))
OBJS += $(notdir $(CPPSRC:.cpp=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
COPY_RAM_OBJS: CORE_TARGETS
all: COPY_RAM_OBJS

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
