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

.PHONY: all clean

#*****************************************************************************#
#                                  VARIABLES                                  #
#*****************************************************************************#
AUDIODIR = $(BASEDIR)/component/audio/frameworks/media/audio/lite/audio_stream
DIR = $(AUDIODIR)/tests/audio_track
RECORD_DIR = $(AUDIODIR)/tests/audio_record

IFLAGS               += -I$(AUDIODIR)/services
IFLAGS               += -I$(DIR)/src
IFLAGS               += -I$(AUDIODIR)/frameworks/include
IFLAGS               += -I$(DIR)/audio_utils/include

vpath %.cpp $(shell find $(DIR)/src -type d)
vpath %.c $(shell find $(DIR)/src -type d)
vpath %.c $(shell find $(RECORD_DIR)/src -type d)
#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
 GLOBAL_CFLAGS += -D__RTOS__ -Wno-multichar -Wno-unused-parameter -Wno-narrowing
 CPPFLAGS += -D__RTOS__ -Wno-multichar -Wno-unused-parameter -Wno-narrowing

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CPPSRC += $(DIR)/audio_wav_test.cpp
CSRC += $(DIR)/audio_lite_wav_test.c
CSRC += $(DIR)/audio_lite_record_test.c


#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
CPPOBJS = $(notdir $(CPPSRC:.cpp=.o))
COBJS = $(notdir $(CSRC:.c=.o))

OBJS = $(CPPOBJS)
OBJS += $(COBJS)

#*****************************************************************************#
#                               Dependency	                                  #
#*****************************************************************************#
-include $(OBJS:.o=.d)

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
COPY_RAM_OBJS: CORE_TARGETS

all: COPY_RAM_OBJS

#*****************************************************************************#
#              GENERATE OBJECT FILE
#*****************************************************************************#
CORE_TARGETS:	$(OBJS)

%.o:%.cpp
	$(Q)$(CC) $(CPPFLAGS) $(MODULE_IFLAGS) $<  -o $@
%.o:%.c
	$(Q)$(CC) $(GLOBAL_CFLAGS) $(MODULE_IFLAGS) $<  -o $@

#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.ii
	$(REMOVE) *.s
	$(REMOVE) *.d
