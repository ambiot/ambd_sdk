
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/media/mmfv2
MODULE_IFLAGS += -I$(DIR)
MODULE_IFLAGS += -I$(TARGETDIR)/fwlib/usb_otg/host/inc
MODULE_IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/host/uvc/inc
MODULE_IFLAGS += -I$(BASEDIR)/component/common/video/v4l2/inc
MODULE_IFLAGS += -I$(BASEDIR)/component/common/network
MODULE_IFLAGS += -I$(BASEDIR)/component/common/media/rtp_codec
MODULE_IFLAGS += -DREFER_USBH_UVC

vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC += $(DIR)/mmf2_module.c
CSRC += $(DIR)/mmf2_siso.c
CSRC += $(DIR)/mmf2_miso.c
CSRC += $(DIR)/mmf2_simo.c
CSRC += $(DIR)/mmf2_mimo.c
CSRC += $(DIR)/module_audio_8721d.c
CSRC += $(DIR)/module_rtsp2.c
CSRC += $(DIR)/module_uvch.c
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
	$(AR) rvs lib_mmfv2.a $(OBJS)
	$(FROMELF) --strip-debug lib_mmfv2.a
	$(MOVE) -f lib_mmfv2.a $(ROOTDIR)/lib/application
	
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

-include $(DEPS)
