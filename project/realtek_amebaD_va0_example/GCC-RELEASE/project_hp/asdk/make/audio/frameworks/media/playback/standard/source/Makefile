
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR1 = $(BASEDIR)/component/audio/frameworks/media/playback/stardard/source/src
DIR2 = $(BASEDIR)/component/audio/frameworks/media/playback/stardard/source/adapter/freertos
#MODULE_IFLAGS += -I$(DIR1)/include
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/libs/src/include
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/log/interfaces
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/osal/osal_c/interfaces
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/osal/osal_cxx/interfaces
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/base/utils/interfaces
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/frameworks/media/playback/stardard/utils/include
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/frameworks/media/playback/stardard/common/include
MODULE_IFLAGS += -I$(BASEDIR)/component/audio/frameworks/media/playback/stardard/source/include
vpath %.cpp $(shell find $(DIR1)/ -type d)
vpath %.cpp $(shell find $(DIR2)/ -type d)
#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__ -Wno-multichar -Wno-unused-parameter -DCONFIG_MEDIA_DATASOURCE_BUFFER -DCONFIG_MEDIA_DATASOURCE_HTTP

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC  = $(DIR1)/data_source_base.cpp
CSRC += $(DIR1)/data_source_factory.cpp
CSRC += $(DIR2)/http_source.cpp
#CSRC += $(DIR2)/file_source.cpp
CSRC += $(DIR2)/buffer_source.cpp

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
