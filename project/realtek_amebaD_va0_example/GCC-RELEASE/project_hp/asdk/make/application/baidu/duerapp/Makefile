
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DUERAPPDIR = $(BASEDIR)/component/common/application/baidu/duerapp/src
MODULE_IFLAGS += -I$(DUERAPPDIR)/../include \
				-I$(DUERAPPDIR)/../include/amebad \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/connagent \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/voice_engine \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/ntp \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/dcs \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/system_info \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/device_status \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/device_info \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/ota/Updater \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/ota/Unpacker \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/ota/Downloader \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/ota/Notifier \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/ota/Verifier \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/ota/Decompression \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/ota/Installer \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/modules/http \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/framework/include \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/framework/core \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/platform/include \
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/external/baidu_json	\
				-I$(BASEDIR)/component/common/application/baidu/libduer-device/sdk_headers	\
				-I$(BASEDIR)/component/common/audio/mp3	\
				-I$(BASEDIR)/component/common/file_system/fatfs/r0.10c/include \
				-I$(BASEDIR)/component/common/file_system/fatfs	\
				-I$(BASEDIR)/component/common/drivers/sdio/realtek/sdio_host/inc

RM_DIR = 'src/public/ameba1'				
vpath %.c $(DUERAPPDIR) $(shell find $(DUERAPPDIR) -type d|grep -vE $(RM_DIR))

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC +=		$(DUERAPPDIR)/public/duerapp.c \
			$(DUERAPPDIR)/public/duerapp_alert.c \
			$(DUERAPPDIR)/public/duerapp_audio.c \
			$(DUERAPPDIR)/public/duerapp_dcs_handler.c \
			$(DUERAPPDIR)/public/duerapp_event.c \
			$(DUERAPPDIR)/public/duerapp_media.c \
			$(DUERAPPDIR)/public/duerapp_ota.c \
			$(DUERAPPDIR)/public/amebad/duerapp_ota_flash.c \
			$(DUERAPPDIR)/public/duerapp_tone_config.c \
			$(DUERAPPDIR)/public/duerapp_user_defined.c \
			$(DUERAPPDIR)/public/duerapp_wifi_config.c \
			$(DUERAPPDIR)/private/duerapp_media_parser.c \
			$(DUERAPPDIR)/private/duerapp_media_player.c \
			$(DUERAPPDIR)/private/duerapp_play_event.c \
			$(DUERAPPDIR)/private/duerapp_play_tone.c \
			$(DUERAPPDIR)/private/duerapp_profile_config.c \
			$(DUERAPPDIR)/private/duerapp_recorder.c \
			$(DUERAPPDIR)/private/duerapp_sdcard_config.c \
			$(DUERAPPDIR)/private/duerapp_sdcard_record.c \
			$(DUERAPPDIR)/public/amebad/duerapp_rl6548_play.c \
			$(DUERAPPDIR)/public/amebad/duerapp_rl6548_record.c \
			$(DUERAPPDIR)/public/amebad/duerapp_rl6548_play.c \
			$(DUERAPPDIR)/public/amebad/duerapp_rl6548_audio.c \
			$(DUERAPPDIR)/public/amebad/duerapp_amebad_peripheral.c

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS COPY_RAM_OBJS
	
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

-include $(DEPS)	
