
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES                                     #
#*****************************************************************************#
RENDER_TEST_DIR = $(TARGETDIR)/app/hal/tests/audio_hal_test/render
CAPTURE_TEST_DIR = $(TARGETDIR)/app/hal/tests/audio_hal_test/capture
MODULE_IFLAGS += -I$(TARGETDIR)/app/hal/interfaces

vpath %.c $(shell find $(RENDER_TEST_DIR)/src/ -type d)
vpath %.c $(shell find $(CAPTURE_TEST_DIR)/src/ -type d)

#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__
CPPFLAGS += -Wno-unused-parameter

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(RENDER_TEST_DIR)/render_test.c
CSRC += $(CAPTURE_TEST_DIR)/capture_test.c

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
