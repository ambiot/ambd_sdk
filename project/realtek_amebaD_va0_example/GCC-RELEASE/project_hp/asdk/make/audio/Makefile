
include $(MAKE_INCLUDE_GEN)

.PHONY: all lib clean


#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = 

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS
ifeq ($(CONFIG_AUDIO_EN),y)
	make -C amr	all
	make -C opus-1.3.1 all
endif
#	haac and faac contain same filenames. cannot build at the same time in amebad.
#	make -C g711 all
#	make -C faac all
#	make -C haac all
#	make -C speex all
ifeq ($(CONFIG_BAIDU_DUER),y)
#	make -C ac3 all
#	make -C haac all
#	make -C hmp3 all
#	make -C m4a_selfparse all
#	make -C m4a all
#	make -C amr	all
endif
#	make -C hls all
#	make -C kws all
#	make -C flac all
	make -C resample all

lib:
ifeq ($(CONFIG_AUDIO_HAL),y)
	make -C hal lib
endif
ifneq ($(findstring $(CONFIG_AUDIO_PASSTHROUGH_INTERFACE)$(CONFIG_AUDIO_MIXER_SERVICE), y y),)
	make -C base lib
	make -C frameworks audiolib
endif
ifeq ($(CONFIG_MEDIA_PLAYER),y)
	make -C base lib
	make -C frameworks playerlib
	make -C 3rdparty lib
	make -C third_party lib
endif

#*****************************************************************************#
#              GENERATE OBJECT FILE                                           #
#*****************************************************************************#
CORE_TARGETS: $(OBJS)




#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: 
#	make -C mp3 clean
#	make -C faac clean
#	make -C g711 clean
#	make -C haac clean
#	make -C speex clean
	make -C amr clean
#	make -C ac3 clean
#	make -C haac clean
#	make -C hmp3 clean
#	make -C m4a_selfparse clean
#	make -C m4a clean
	make -C amr clean
#	make -C hls clean
#	make -C kws clean
#	make -C flac clean
	make -C resample clean
#	make -C gsm610 clean
#	make -C ekho clean
#	make -C libogg-1.3.3 clean
	make -C opus-1.3.1 clean
#	make -C opusfile-0.11 clean
#	make -C example_audio_opus_decode clean
#	make -C libopusenc-0.2.1 clean
#	make -C example_audio_opus_encode clean
	make -C hal clean
	make -C base clean
	make -C frameworks clean
	make -C 3rdparty clean
	make -C third_party clean

-include $(DEPS)
