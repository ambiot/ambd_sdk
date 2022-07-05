include $(MAKE_INCLUDE_GEN)
IFLAGS               += -I$(TARGETDIR)/app/hal/src/audio/include
IFLAGS               += -I$(TARGETDIR)/app/hal/interfaces
IFLAGS               += -I$(BASEDIR)/component/audio/frameworks/media/audio/preprocess/afe/include

.PHONY: lib  clean

#*****************************************************************************#
#                                  VARIABLES                                  #
#*****************************************************************************#
DIR = $(TARGETDIR)/app/hal/src/audio

vpath %.c $(shell find $(DIR)/ -type d)

#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__
GLOBAL_CFLAGS += -DNDEBUG -UDEBUG

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/circular_buffer.c
CSRC += $(DIR)/params_handle.c
CSRC += $(DIR)/ameba_audio_driver.c
CSRC += $(DIR)/primary_audio_hw_render.c
CSRC += $(DIR)/primary_audio_hw_adapter.c
CSRC += $(DIR)/primary_audio_hw_capture.c
CSRC += $(DIR)/audio_hw_manager.c

ifeq ($(CONFIG_AUDIO_HAL_AFE),y)
GLOBAL_CFLAGS += -DAUDIO_HAL_AFE
endif

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

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
	$(AR) rvs lib_audio_hal.a $(OBJS)
	$(MOVE) -f lib_audio_hal.a $(ROOTDIR)/lib/application/

#*****************************************************************************#
#              GENERATE OBJECT FILE
#*****************************************************************************#
CORE_TARGETS:	$(OBJS)

%.o:%.c
	$(Q)$(CC) $(GLOBAL_CFLAGS) $(MODULE_IFLAGS) $<  -o $@

#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d
