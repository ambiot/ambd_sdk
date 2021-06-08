
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(SRCDIR)
DIR1 = $(BASEDIR)/component/common/audio/opus-1.3.1

MODULE_IFLAGS = -I$(DIR)./
MODULE_IFLAGS += -I$(DIR1)
MODULE_IFLAGS += -I$(DIR1)/celt
MODULE_IFLAGS += -I$(DIR1)/include
MODULE_IFLAGS += -I$(DIR1)/silk
MODULE_IFLAGS += -I$(DIR1)/silk/fixed
MODULE_IFLAGS += -I$(DIR1)/src
MODULE_IFLAGS += -I$(DIR1)/test

vpath %.c $(DIR)
#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
#CSRC = $(DIR)/main.c
CSRC += $(DIR)/opus_encode_decode.c
CSRC += $(DIR)/Psram_realloc.c
#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all: CLEAN_OBJS CORE_TARGETS COPY_RAM_OBJS
	
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
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)	
