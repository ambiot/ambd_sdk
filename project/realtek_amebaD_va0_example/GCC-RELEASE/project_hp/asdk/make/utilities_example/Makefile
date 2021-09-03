
include $(MAKE_INCLUDE_GEN)
#IFLAGS               += -I$(BASEDIR)/component/common/network/coap/include
IFLAGS               += -I$(BASEDIR)/component/common/application/mqtt/MQTTClient
IFLAGS				+= -I$(BASEDIR)/component/common/audio/flac
IFLAGS               += -I$(BASEDIR)/component/common/bluetooth/realtek/sdk
IFLAGS               += -I$(BASEDIR)/component/common/drivers/sdio/realtek/sdio_host/inc
IFLAGS               += -I$(BASEDIR)/component/common/network/libcoap/include

ifeq ($(CONFIG_LINKKIT_AWSS), y)
#aliyun
IFLAGS				 += -I$(BASEDIR)/component/common/application/linkkit/v1.3.0/include
IFLAGS				 += -I$(BASEDIR)/component/common/application/linkkit/v1.3.0/include/imports
IFLAGS				 += -I$(BASEDIR)/component/common/application/linkkit/v1.3.0/include/exports
IFLAGS				 += -I$(BASEDIR)/component/common/application/linkkit/v1.3.0/include/platform
endif

ifeq ($(CONFIG_USB_DEVICE_EN),y)
IFLAGS += -I$(TARGETDIR)/fwlib/usb_otg/device/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/device/audio/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/device/cdc_acm/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/device/msc/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/device/vendor/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/device/hid/inc
endif
ifeq ($(CONFIG_USB_HOST_EN),y)
IFLAGS += -I$(TARGETDIR)/fwlib/usb_otg/host/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/host/msc/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/host/uvc/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/host/vendor/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/host/cdc_acm/inc
ifeq ($(CONFIG_USBH_UVC),y)
IFLAGS += -I$(BASEDIR)/component/common/video/v4l2/inc
IFLAGS += -I$(BASEDIR)/component/common/media/rtp_codec
IFLAGS += -I$(BASEDIR)/component/common/media/mmfv2
endif
endif

ifeq ($(CONFIG_USB_DEVICE_NEW_EN),y)
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/common_new
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/device_new/core
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/device_new/cdc_acm
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/device_new/hid
endif

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/example
RM_DIRS = 'example/audio_mp3|example/audio_amr|example/audio_helix_aac|example/audio_helix_mp3|example/audio_m4a_selfparse|example/audio_m4a|example/audio_pcm_upload|example/audio_hls'
DIRS = $(shell find $(DIR) -maxdepth 3 -type d|grep -vE $(RM_DIRS))

vpath %.c $(DIRS)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC += $(DIR)/example_entry.c
CSRC += $(DIR)/cm_backtrace/example_cm_backtrace.c
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
CSRC += $(DIR)/wlan_repeater/example_wlan_repeater.c
CSRC += $(DIR)/wlan_scenario/example_wlan_scenario.c
CSRC += $(DIR)/websocket_client/example_wsclient.c
CSRC += $(DIR)/websocket_server/example_ws_server.c
CSRC += $(DIR)/xml/example_xml.c
CSRC += $(DIR)/mqtt/example_mqtt.c
#CSRC += $(DIR)/coap/example_coap.c
#CSRC += $(DIR)/coap_client/example_coap_client.c
#CSRC += $(DIR)/coap_server/example_coap_server.c
CSRC += $(DIR)/httpd/example_httpd.c
CSRC += $(DIR)/httpd/example_httpc.c
CSRC += $(DIR)/ota_http/example_ota_http.c
#CSRC += $(DIR)/ota_https/example_ota_https.c
CSRC += $(DIR)/ota_sdcard/example_ota_sdcard.c
CSRC += $(DIR)/dct/example_dct.c
#CSRC += $(DIR)/wifi_manager/example_wifi_manager.c
CSRC += $(DIR)/wifi_roaming/example_wifi_roaming.c
#CSRC += $(DIR)/wifi_roaming_plus/example_wifi_roaming_plus.c
CSRC += $(DIR)/wifi_connection_priority/example_wifi_conn_pri_cond.c
CSRC += $(DIR)/uart_firmware_update/example_uart_update.c
#CSRC += $(DIR)/ipv6/example_ipv6.c
CSRC += $(DIR)/cJSON/example_cJSON.c
#CSRC += $(DIR)/sdcard_upload_httpd/example_sdcard_upload_httpd.c
CSRC += $(DIR)/socket_tcp_trx/example_socket_tcp_trx_1.c
CSRC += $(DIR)/socket_tcp_trx/example_socket_tcp_trx_2.c
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
IFLAGS += -I$(BASEDIR)/component/common/audio/libav
IFLAGS += -I$(BASEDIR)/component/common/audio/a52dec/src
IFLAGS += -I$(BASEDIR)/component/common/audio/a52dec/include
IFLAGS += -I$(BASEDIR)/component/common/audio/a52dec/libao
IFLAGS += -I$(BASEDIR)/component/common/audio/opus-1.3.1/include
IFLAGS += -I$(BASEDIR)/component/common/audio/opus-1.3.1/src
IFLAGS += -I$(BASEDIR)/component/common/audio/opus-1.3.1/celt
CSRC += $(DIR)/audio_sport/audio_amr/example_audio_amr.c
#CSRC += $(DIR)/audio_sport/audio_mp3/example_audio_mp3.c
#CSRC += $(DIR)/audio_sport/audio_helix_aac/example_audio_helix_aac.c
#CSRC += $(DIR)/audio_sport/audio_helix_mp3/example_audio_helix_mp3.c
#CSRC += $(DIR)/audio_sport/audio_m4a_selfparse/example_audio_m4a_selfparse.c
#CSRC += $(DIR)/audio_sport/audio_m4a/example_audio_m4a.c
#CSRC += $(DIR)/audio_sport/audio_pcm_upload/example_audio_pcm_upload.c
#CSRC += $(DIR)/audio_sport/audio_hls/example_audio_hls.c
#CSRC += $(DIR)/audio_sport/audio_flac/example_audio_flac.c
#CSRC += $(DIR)/audio_sport/audio_ac3/example_audio_ac3.c
#CSRC += $(DIR)/audio_sport/audio_ac3/a52dec.c
CSRC += $(DIR)/audio_sport/audio_recorder/example_audio_recorder.c
CSRC += $(DIR)/audio_sport/audio_amr_flash/example_audio_amr_flash.c
CSRC += $(DIR)/audio_sport/audio_amr_flash/audio_play.c
#CSRC += $(DIR)/audio_sport/example_audio_ekho.c
CSRC += $(DIR)/audio_sport/audio_signal_generate/example_audio_signal_generate.c
#CSRC += $(DIR)/audio_sport/audio_tts_cybron/example_audio_tts_cyberon.c
CSRC += $(DIR)/opus_encode_decode.c
CSRC += $(DIR)/Psram_realloc.c
endif

ifeq ($(CONFIG_USB_OTG_EN),y)
ifeq ($(CONFIG_USB_DEVICE_EN),y)
#CSRC += $(DIR)/usbd_audio/example_usbd_audio_sp.c
#CSRC += $(DIR)/usbd_audio/example_usbd_audio.c
#CSRC += $(DIR)/usbd_msc/example_usbd_msc.c
#CSRC += $(DIR)/usbd_cdc_acm/example_usbd_cdc_acm.c
#CSRC += $(DIR)/usbd_vendor/example_usbd_vendor.c
#CSRC += $(DIR)/usbd_hid_mouse/example_usbd_hid_mouse.c
endif
ifeq ($(CONFIG_USB_HOST_EN),y)
#CSRC += $(DIR)/usbh_msc/example_usbh_msc.c
#CSRC += $(DIR)/usbh_uvc/example_usbh_uvc.c
#CSRC += $(DIR)/usbh_vendor/example_usbh_vendor.c
#CSRC += $(DIR)/usbh_cdc_acm/example_usbh_cdc_acm.c
endif
ifeq ($(CONFIG_USB_DEVICE_NEW_EN),y)
#CSRC += $(DIR)/usbd_cdc_acm_new/example_usbd_cdc_acm_new.c
#CSRC += $(DIR)/usbd_hid_mouse_new/example_usbd_hid_mouse_new.c
endif
endif

ifeq ($(CONFIG_LINKKIT_AWSS), y)
#linkkit
#CSRC += $(DIR)/linkkit/linkkit_awss_example.c
endif

#azure examples
# CSRC += $(DIR)/azure_iothub_telemetry/example_azure_iothub_telemetry.c
# CSRC += $(DIR)/azure_iothub_x509/example_azure_iothub_x509.c

#azure embedded examples
# CSRC += $(DIR)/azure/example_azure_iot_common.c
# CSRC += $(DIR)/azure/example_azure_iot_entry.c
# CSRC += $(DIR)/azure/example_azure_iot_hub_c2d.c
# CSRC += $(DIR)/azure/example_azure_iot_hub_methods.c
# CSRC += $(DIR)/azure/example_azure_iot_hub_pnp.c
# CSRC += $(DIR)/azure/example_azure_iot_hub_pnp_component.c
# CSRC += $(DIR)/azure/example_azure_iot_hub_sas_telemetry.c
# CSRC += $(DIR)/azure/example_azure_iot_hub_telemetry.c
# CSRC += $(DIR)/azure/example_azure_iot_hub_twin.c
# CSRC += $(DIR)/azure/example_azure_iot_rtk_pnp_sas.c
# CSRC += $(DIR)/azure/example_azure_iot_rtk_pnp_x509.c
# CSRC += $(DIR)/azure/example_azure_iot_provisioning.c
# CSRC += $(DIR)/azure/example_azure_iot_provisioning_sas.c
# CSRC += $(DIR)/azure/pnp/pnp_mqtt_message.c
# CSRC += $(DIR)/azure/pnp/pnp_protocol.c
# CSRC += $(DIR)/azure/pnp/sample_component/pnp_device_info_component.c
# CSRC += $(DIR)/azure/pnp/sample_component/pnp_thermostat_component.c
# CSRC += $(DIR)/azure/pnp/rtk_message/pnp_common_message.c
# CSRC += $(DIR)/azure/pnp/rtk_component/pnp_audio.c
# CSRC += $(DIR)/azure/pnp/rtk_component/pnp_bluetooth.c
# CSRC += $(DIR)/azure/pnp/rtk_component/pnp_device_info.c
# CSRC += $(DIR)/azure/pnp/rtk_component/pnp_gpio.c
# CSRC += $(DIR)/azure/pnp/rtk_component/pnp_lcd.c
# CSRC += $(DIR)/azure/pnp/rtk_component/pnp_memory.c
# CSRC += $(DIR)/azure/pnp/rtk_component/pnp_system.c
# CSRC += $(DIR)/azure/pnp/rtk_component/pnp_video.c
# CSRC += $(DIR)/azure/pnp/rtk_component/pnp_wireless.c
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
