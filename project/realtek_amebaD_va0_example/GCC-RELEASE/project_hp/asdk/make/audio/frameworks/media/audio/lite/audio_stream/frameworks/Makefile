include $(MAKE_INCLUDE_GEN)
IFLAGS               += -I$(BASEDIR)/component/audio/base/log/interfaces
IFLAGS               += -I$(BASEDIR)/component/audio/base/libs/src/include
IFLAGS               += -I$(BASEDIR)/component/audio/base/osal/osal_c/interfaces
IFLAGS               += -I$(BASEDIR)/component/audio/base/osal/osal_cxx/interfaces
IFLAGS               += -I$(BASEDIR)/component/audio/base/cutils/interfaces
IFLAGS               += -I$(BASEDIR)/component/audio/base/utils/interfaces
IFLAGS               += -I$(BASEDIR)/component/audio/base/media/audio/audio_utils/include
IFLAGS               += -I$(BASEDIR)/component/audio/base/media
IFLAGS               += -I$(BASEDIR)/component/audio/frameworks/media/audio/interfaces
IFLAGS               += -I$(BASEDIR)/component/audio/frameworks/media/audio/algorithms/sonic
IFLAGS               += -I$(TARGETDIR)/app/hal/interfaces

.PHONY: lib clean

#*****************************************************************************#
#                                  VARIABLES                                  #
#*****************************************************************************#
DIR = $(BASEDIR)/component/audio/frameworks/media/audio/lite/audio_stream

IFLAGS               += -I$(DIR)/audio_utils/include
IFLAGS               += -I$(DIR)/services
IFLAGS               += -I$(DIR)/frameworks/include

vpath %.cpp $(shell find $(DIR)/frameworks -type d)
#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
CPPFLAGS += -D__RTOS__ -Wno-multichar -Wno-unused-parameter

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC  = $(DIR)/frameworks/audio_system.cpp
CSRC  += $(DIR)/frameworks/track_client.cpp
CSRC  += $(DIR)/frameworks/audio_track.cpp
CSRC  += $(DIR)/frameworks/record_client.cpp
CSRC  += $(DIR)/frameworks/audio_record.cpp
CSRC  += $(DIR)/frameworks/audio_control.cpp

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.cpp=.o))

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
	$(COPY) $(OBJS) ../../../xip/

#*****************************************************************************#
#              GENERATE OBJECT FILE
#*****************************************************************************#
CORE_TARGETS:	$(OBJS)

%.o:%.cpp
	$(Q)$(CC) $(CPPFLAGS) $(MODULE_IFLAGS) $<  -o $@

#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.ii
	$(REMOVE) *.s
	$(REMOVE) *.d
