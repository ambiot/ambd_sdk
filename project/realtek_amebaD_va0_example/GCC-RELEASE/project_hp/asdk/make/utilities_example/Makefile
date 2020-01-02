
include $(MAKE_INCLUDE_GEN)
IFLAGS               += -I$(BASEDIR)/component/common/network/coap/include
IFLAGS               += -I$(BASEDIR)/component/common/application/mqtt/MQTTClient
IFLAGS				+= -I$(BASEDIR)/component/common/audio/flac
IFLAGS				+= -I$(BASEDIR)/component/common/drivers/usb_class/host/vendor_spec
IFLAGS               += -I$(BASEDIR)/component/common/bluetooth/realtek/sdk
IFLAGS               += -I$(BASEDIR)/component/common/drivers/sdio/realtek/sdio_host/inc

ifeq ($(CONFIG_AUDIO_EN),y)
IFLAGS += -I$(BASEDIR)/component/common/audio/fdk-aac_m4a
IFLAGS += -I$(BASEDIR)/component/common/audio/fdk-aac_m4a/libSYS/include
endif
.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/example
RM_DIRS = 'example/audio_mp3|example/audio_amr|example/audio_helix_aac|example/audio_helix_mp3|example/audio_m4a_selfparse|example/audio_m4a|example/audio_pcm_upload|example/audio_hls'
DIRS = $(shell find $(DIR) -maxdepth 2 -type d|grep -vE $(RM_DIRS))

vpath %.c $(DIRS)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC += $(DIR)/example_entry.c
CSRC += $(DIR)/bcast/example_bcast.c
#CSRC += $(DIR)/eap/example_eap.c
CSRC += $(DIR)/get_beacon_frame/example_get_beacon_frame.c
CSRC += $(DIR)/high_load_memory_use/example_high_load_memory_use.c
CSRC += $(DIR)/http_client/example_http_client.c
CSRC += $(DIR)/http_download/example_http_download.c
CSRC += $(DIR)/mcast/example_mcast.c
CSRC += $(DIR)/mdns/example_mdns.c
CSRC += $(DIR)/nonblock_connect/example_nonblock_connect.c
CSRC += $(DIR)/rarp/example_rarp.c
CSRC += $(DIR)/sntp_showtime/example_sntp_showtime.c
CSRC += $(DIR)/socket_select/example_socket_select.c
CSRC += $(DIR)/ssl_download/example_ssl_download.c
CSRC += $(DIR)/ssl_server/example_ssl_server.c
CSRC += $(DIR)/tcp_keepalive/example_tcp_keepalive.c
CSRC += $(DIR)/uart_atcmd/example_uart_atcmd.c
CSRC += $(DIR)/wifi_mac_monitor/example_wifi_mac_monitor.c
CSRC += $(DIR)/wlan_fast_connect/example_wlan_fast_connect.c
CSRC += $(DIR)/wlan_scenario/example_wlan_scenario.c
CSRC += $(DIR)/websocket_client/example_wsclient.c
CSRC += $(DIR)/xml/example_xml.c
CSRC += $(DIR)/mqtt/example_mqtt.c
CSRC += $(DIR)/coap/example_coap.c
CSRC += $(DIR)/httpd/example_httpd.c
CSRC += $(DIR)/httpd/example_httpc.c
CSRC += $(DIR)/ota_http/example_ota_http.c
CSRC += $(DIR)/ota_sdcard/example_ota_sdcard.c
#CSRC += $(DIR)/wifi_roaming_plus/example_wifi_roaming_plus.c

# MMF AUDIO EXAMPLE
# CSRC += $(DIR)/media_framework/example_media_framework.c
# CSRC += $(DIR)/media_framework/mmf2_example_audioloop_init.c
# CSRC += $(DIR)/media_framework/mmf2_example_pcmu_array_rtsp_init.c
# CSRC += $(DIR)/media_framework/mmf2_example_aac_array_rtsp_init.c
# CSRC += $(DIR)/media_framework/mmf2_example_a_init.c
# CSRC += $(DIR)/media_framework/mmf2_example_rtp_aad_init.c
# CSRC += $(DIR)/media_framework/mmf2_example_2way_audio_init.c
# CSRC += $(DIR)/media_framework/mmf2_example_aacloop_init.c
# CSRC += $(DIR)/media_framework/mmf2_example_g711loop_init.c

#CSRC += $(DIR)/audio_sport/audio_amr/example_audio_amr.c
#CSRC += $(DIR)/audio_sport/audio_mp3/example_audio_mp3.c
#CSRC += $(DIR)/audio_sport/audio_ac3/example_audio_ac3.c
#CSRC += $(DIR)/audio_sport/audio_helix_aac/example_audio_helix_aac.c
#CSRC += $(DIR)/audio_sport/audio_helix_mp3/example_audio_helix_mp3.c
#CSRC += $(DIR)/audio_sport/audio_m4a_selfparse/example_audio_m4a_selfparse.c
#CSRC += $(DIR)/audio_sport/audio_m4a/example_audio_m4a.c
#CSRC += $(DIR)/audio_sport/audio_pcm_upload/example_audio_pcm_upload.c
#CSRC += $(DIR)/audio_sport/audio_hls/example_audio_hls.c
#CSRC += $(DIR)/audio_sport/audio_recorder/example_audio_recorder.c
#CSRC +=	$(DIR)/audio_sport/audio_flac/example_audio_flac.c
#CSRC += $(DIR)/audio_sport/audio_amr_flash/example_audio_amr_flash.c
#CSRC += $(DIR)/audio_sport/audio_amr_flash/audio_play.c
#CSRC += $(DIR)/audio_sport/audio_signal_generate/example_audio_signal_generate.c
#CSRC += $(DIR)/audio_sport/audio_tts/example_audio_tts.c
CSRC += $(DIR)/fatfs/example_fatfs.c
CSRC += $(DIR)/dct/example_dct.c
#CSRC += $(DIR)/competitive_headphones/example_competitive_headphones.c
#CSRC += $(DIR)/competitive_headphones/headphone_rl6548_audio.c
#CSRC += $(DIR)/competitive_headphones/headphone_burst.c
#CSRC += $(DIR)/competitive_headphones/headphone_packet_compensation.c
#CSRC += $(DIR)/competitive_headphones_dongle/example_competitive_headphones_dongle.c

ifeq ($(CONFIG_AUDIO_EN),y)
CSRC += $(DIR)/audio_sport/audio_amr/example_audio_amr.c
#CSRC += $(DIR)/audio_sport/audio_mp3/example_audio_mp3.c
#CSRC += $(DIR)/audio_sport/audio_helix_aac/example_audio_helix_aac.c
#CSRC += $(DIR)/audio_sport/audio_helix_mp3/example_audio_helix_mp3.c
CSRC += $(DIR)/audio_sport/audio_m4a_selfparse/example_audio_m4a_selfparse.c
#CSRC += $(DIR)/audio_sport/audio_m4a/example_audio_m4a.c
#CSRC += $(DIR)/audio_sport/audio_pcm_upload/example_audio_pcm_upload.c
#CSRC += $(DIR)/audio_sport/audio_hls/example_audio_hls.c
#CSRC +=	$(DIR)/audio_sport/audio_flac/example_audio_flac.c
#CSRC += $(DIR)/audio_sport/audio_ac3/example_audio_ac3.c
#CSRC += $(DIR)/audio_sport/audio_recorder/example_audio_recorder.c
CSRC += $(DIR)/audio_sport/audio_amr_flash/example_audio_amr_flash.c
CSRC += $(DIR)/audio_sport/audio_amr_flash/audio_play.c
#CSRC += $(DIR)/audio_sport/example_audio_ekho.c
#CSRC += $(DIR)/audio_sport/audio_signal_generate/example_audio_signal_generate.c
#CSRC += $(DIR)/audio_sport/audio_tts_cybron/example_audio_tts_cyberon.c
endif

#CSRC += $(DIR)/usbd_audio/example_usbd_sp.c
#CSRC += $(DIR)/usbd_audio/example_usbd_audio.c
#CSRC += $(DIR)/usbd_msc/example_usbd_msc.c
#CSRC += $(DIR)/usbd_cdc_vcom/example_usbd_cdc_acm.c

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
