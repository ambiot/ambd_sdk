
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                                  #
#*****************************************************************************#
DIR = $(BASEDIR)/component/audio/frameworks/media/playback/stardard

MODULE_IFLAGS += \
    -I$(DIR)/utils/include \
    -I$(DIR)/common/include \
    -I$(DIR)/codec/include \
    -I$(DIR)/codec/include/media/codec/omxil

MODULE_IFLAGS += -I$(BASEDIR)/project/realtek_amebaLite_va0_example/GCC-RELEASE/project_kr4/toolchain/linux/vsdk-10.2.0/linux/newlib/riscv32-none-elf/include/c++/10.2.0/bits

MODULE_IFLAGS += \
    -I$(BASEDIR)/component/audio/base/libs/src/include \
    -I$(BASEDIR)/component/audio/base/log/interfaces \
    -I$(BASEDIR)/component/audio/base/osal/osal_c/interfaces \
    -I$(BASEDIR)/component/audio/base/osal/osal_cxx/interfaces \
    -I$(BASEDIR)/component/audio/base/cutils/interfaces \
    -I$(BASEDIR)/component/audio/base/utils/interfaces \
    -I$(BASEDIR)/component/audio/base/media/audio/audio_utils/include 

vpath %.cpp $(shell find $(DIR)/codec -type d)
#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__ -Wno-multichar -Wno-unused-parameter

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
#CONFIG_MEDIA_PLAYER
#CONFIG_MEDIA_CODEC_SW_RAW:=y
#CONFIG_MEDIA_CODEC_SW_MP3:=y
#CONFIG_MEDIA_CODEC_SW_AAC:=y
#CONFIG_MEDIA_CODEC_SW_HELIX_AAC:=y

CSRC  = \
    $(DIR)/codec/media_codec.cpp \
    $(DIR)/codec/codec.cpp \
    $(DIR)/codec/codec_buffer_tunnel.cpp \
    $(DIR)/codec/data_converter.cpp \
    $(DIR)/codec/omx/omx_buffer.cpp \
    $(DIR)/codec/omx/omx_utils.cpp \
    $(DIR)/codec/omx/omx_node.cpp \
    $(DIR)/codec/omx/omx.cpp \
    $(DIR)/codec/omx/omx_core.cpp \
    $(DIR)/codec/omx/sw_omx_component.cpp

# rawpcm codec
ifeq ($(CONFIG_MEDIA_CODEC_SW_RAW),y)
LIBRAW_SRC_FILES := $(DIR)/codec/codecs/rawdec/sw_raw_dec.cpp
CSRC += $(LIBRAW_SRC_FILES)
GLOBAL_CFLAGS += -DMEDIA_CODEC_SW_RAW
endif

# aac codec
ifeq ($(CONFIG_MEDIA_CODEC_SW_AAC),y)
LIBAAC_SRC_FILES := \
    $(DIR)/codec/codecs/aacdec/drc_pres_mode_wrap.cpp \
    $(DIR)/codec/codecs/aacdec/sw_aac2_dec.cpp

LIBAAC_C_INCLUDES := \
    -I$(BASEDIR)/component/audio/third_party/aac/libAACdec/include \
    -I$(BASEDIR)/component/audio/third_party/aac/libPCMutils/include \
    -I$(BASEDIR)/component/audio/third_party/aac/libFDK/include \
    -I$(BASEDIR)/component/audio/third_party/aac/libSYS/include \
    -I$(BASEDIR)/component/audio/third_party/aac/libMpegTPDec/include \
    -I$(BASEDIR)/component/audio/third_party/aac/libSBRdec/include \
    -I$(BASEDIR)/component/audio/third_party/aac/libArithCoding/include \
    -I$(BASEDIR)/component/audio/third_party/aac/libDRCdec/include \
    -I$(BASEDIR)/component/audio/third_party/aac/libSACdec/include

CSRC += $(LIBAAC_SRC_FILES)
MODULE_IFLAGS += $(LIBAAC_C_INCLUDES)
GLOBAL_CFLAGS += -DMEDIA_CODEC_SW_AAC
endif

# haac codec
ifeq ($(CONFIG_MEDIA_CODEC_SW_HELIX_AAC),y)
LIBAAC_SRC_FILES := \
    $(DIR)/codec/codecs/helixaacdec/sw_helix_aac_dec.cpp

LIBAAC_C_INCLUDES := \
    -I$(BASEDIR)/component/audio/3rdparty/haac

CSRC += $(LIBAAC_SRC_FILES)
MODULE_IFLAGS += $(LIBAAC_C_INCLUDES)
GLOBAL_CFLAGS += -DMEDIA_CODEC_SW_HELIX_AAC
endif

# mp3 codec
ifeq ($(CONFIG_MEDIA_CODEC_SW_MP3),y)
LIBMP3_SRC_FILES := \
	$(DIR)/codec/codecs/mp3dec/sw_mp3_dec.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_normalize.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_alias_reduction.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_crc.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_decode_header.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_decode_huff_cw.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_getbits.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_dequantize_sample.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_framedecoder.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_get_main_data_size.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_get_side_info.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_get_scale_factors.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_mpeg2_get_scale_data.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_mpeg2_get_scale_factors.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_mpeg2_stereo_proc.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_huffman_decoding.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_huffman_parsing.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_tables.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_imdct_synth.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_mdct_6.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_dct_6.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_poly_phase_synthesis.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_equalizer.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_seek_synch.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_stereo_proc.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_reorder.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_polyphase_filter_window.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_mdct_18.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_dct_9.cpp \
	$(DIR)/codec/codecs/mp3dec/src/pvmp3_dct_16.cpp

LIBMP3_C_INCLUDES := \
	-I$(DIR)/codec/codecs/mp3dec/include \
	-I$(DIR)/codec/codecs/mp3dec/src

CSRC += $(LIBMP3_SRC_FILES)
MODULE_IFLAGS += $(LIBMP3_C_INCLUDES)
GLOBAL_CFLAGS += -DMEDIA_CODEC_SW_MP3
endif

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
