
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/media/mmfv2
MODULE_IFLAGS += -I$(DIR)

vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC += $(DIR)/module_audio_8721d.c
CSRC += $(DIR)/mmf2_module.c
CSRC += $(DIR)/mmf2_siso.c
CSRC += $(DIR)/mmf2_miso.c
CSRC += $(DIR)/mmf2_simo.c
CSRC += $(DIR)/mmf2_mimo.c
CSRC += $(DIR)/module_array.c
CSRC += $(DIR)/module_g711.c
CSRC += $(DIR)/module_aac.c
CSRC += $(DIR)/module_aad.c
CSRC += $(DIR)/module_rtsp2.c
CSRC += $(DIR)/module_rtp.c
CSRC += $(DIR)/memory_encoder.c
CSRC += $(DIR)/mmf2_dbg.c
#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                               Include Dependency                            #
#*****************************************************************************#
-include $(OBJS:.o=.d)


#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all: CORE_TARGETS COPY_RAM_OBJS
	
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
	$(REMOVE) *.su
	$(REMOVE) *.d
	$(REMOVE) *.c

-include $(DEPS)	
