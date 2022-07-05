
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/audio/frameworks/media/playback/stardard/common
MODULE_IFLAGS += -I$(DIR)/include
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/libs/src/include
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/log/interfaces
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/osal/osal_c/interfaces
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/osal/osal_cxx/interfaces
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/utils/interfaces
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/frameworks/media/playback/stardard/utils/include

vpath %.cpp $(shell find $(DIR)/ -type d)
#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__ -Wno-multichar -Wno-deprecated-copy

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC  = $(DIR)/media_track.cpp
CSRC += $(DIR)/media_buffer_base.cpp
CSRC += $(DIR)/media_buffer.cpp
CSRC += $(DIR)/media_buffer_group.cpp
CSRC += $(DIR)/codec_buffer_info.cpp
CSRC += $(DIR)/media_defs.cpp
CSRC += $(DIR)/meta_data_base.cpp
CSRC += $(DIR)/meta_data.cpp
CSRC += $(DIR)/packet_pool.cpp
CSRC += $(DIR)/esds.cpp
CSRC += $(DIR)/utils.cpp
CSRC += $(DIR)/media_base64.cpp
CSRC += $(DIR)/media_bit_reader.cpp

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
