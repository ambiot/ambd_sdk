
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/example/audio_sport/audio_opus_decode
DIR1 = $(BASEDIR)/component/common/audio/libogg-1.3.3
DIR2 = $(BASEDIR)/component/common/audio/opus-1.3.1
DIR3 = $(BASEDIR)/component/common/audio/opusfile-0.11

vpath %.c $(DIR1) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/example_audio_opus_decode.c
CSRC += $(DIR)/Psram_realloc.c

MODULE_IFLAGS += -I$(DIR)
MODULE_IFLAGS += -I$(DIR1)
MODULE_IFLAGS += -I$(DIR1)/include  
MODULE_IFLAGS += -I$(DIR2)
MODULE_IFLAGS += -I$(DIR2)/celt
MODULE_IFLAGS += -I$(DIR2)/include
MODULE_IFLAGS += -I$(DIR2)/silk
MODULE_IFLAGS += -I$(DIR2)/silk/fixed
MODULE_IFLAGS += -I$(DIR2)/src
MODULE_IFLAGS += -I$(DIR2)/test
MODULE_IFLAGS += -I$(DIR3)
MODULE_IFLAGS += -I$(DIR3)/examples
MODULE_IFLAGS += -I$(DIR3)/include
MODULE_IFLAGS += -I$(DIR3)/src

#GLOBAL_CFLAGS += -DHAVE_CONFIG_H
GLOBAL_CFLAGS += -DHAVE_ALLOCA_H
GLOBAL_CFLAGS += -DDISABLE_FLOAT_API
GLOBAL_CFLAGS += -DFIXED_POINT
#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CLEAN_OBJS CORE_TARGETS COPY_RAM_OBJS

#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS:	$(OBJS)


#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d
	$(REMOVE) *.su

-include $(DEPS)