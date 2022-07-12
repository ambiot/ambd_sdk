include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/application/baidu/libduer-device
MODULE_IFLAGS += -I$(DIR)/external/baidu_json \
				-I$(DIR)/external/mbed-client-c/nsdl-c \
				-I$(DIR)/external/mbed-client-c/source/libCoap/src/include \
				-I$(DIR)/external/mbed-client-c/source/libNsdl/src/include \
				-I$(DIR)/external/mbed-client-c-port \
				-I$(DIR)/external/mbed-trace \
				-I$(DIR)/external/speex/include \
				-I$(DIR)/external/speex/libspeex \
				-I$(DIR)/external/Zliblite \
				-I$(DIR)/framework/include \
				-I$(DIR)/framework/core \
				-I$(DIR)/framework/utils \
				-I$(DIR)/modules/coap \
				-I$(DIR)/modules/connagent \
				-I$(DIR)/modules/dcs \
				-I$(DIR)/modules/Device_Info \
				-I$(DIR)/modules/device_status \
				-I$(DIR)/modules/HTTP \
				-I$(DIR)/modules/ntp \
				-I$(DIR)/modules/OTA \
				-I$(DIR)/modules/OTA/Downloader \
				-I$(DIR)/modules/OTA/Notifier \
				-I$(DIR)/modules/OTA/Unpacker \
				-I$(DIR)/modules/OTA/Updater \
				-I$(DIR)/modules/OTA/Zliblite \
				-I$(DIR)/modules/ota/Verifier \
				-I$(DIR)/modules/ota/Decompression \
				-I$(DIR)/modules/ota/Installer \
				-I$(DIR)/modules/System_Info \
				-I$(DIR)/modules/voice_engine \
				-I$(DIR)/platform/source-freertos \
				-I$(DIR)/platform/include \
				-I$(DIR)/../duerapp/include

MODULE_IFLAGS += -DDUER_PLATFORM_RTKAMEBA

vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC +=		$(DIR)/external/baidu_json.c \
			$(DIR)/external/mbed-client-c/source/libCoap/sn_coap_builder.c \
			$(DIR)/external/mbed-client-c/source/libCoap/sn_coap_header_check.c \
			$(DIR)/external/mbed-client-c/source/libCoap/sn_coap_parser.c \
			$(DIR)/external/mbed-client-c/source/libCoap/sn_coap_protocol.c \
			$(DIR)/external/mbed-client-c/source/libCoap/sn_grs.c \
			$(DIR)/external/mbed-client-c/source/libCoap/sn_nsdl.c \
			$(DIR)/external/mbed-trace/source/mbed_trace.c \
			$(DIR)/external/speex/libspeex/bits.c \
			$(DIR)/external/speex/libspeex/cb_search.c \
			$(DIR)/external/speex/libspeex/exc_10_16_table.c \
			$(DIR)/external/speex/libspeex/exc_10_32_table.c \
			$(DIR)/external/speex/libspeex/exc_20_32_table.c \
			$(DIR)/external/speex/libspeex/exc_5_256_table.c \
			$(DIR)/external/speex/libspeex/exc_5_64_table.c \
			$(DIR)/external/speex/libspeex/exc_8_128_table.c \
			$(DIR)/external/speex/libspeex/fftwrap.c \
			$(DIR)/external/speex/libspeex/filterbank.c \
			$(DIR)/external/speex/libspeex/filters.c \
			$(DIR)/external/speex/libspeex/gain_table.c \
			$(DIR)/external/speex/libspeex/gain_table_lbr.c \
			$(DIR)/external/speex/libspeex/hexc_10_32_table.c \
			$(DIR)/external/speex/libspeex/hexc_table.c \
			$(DIR)/external/speex/libspeex/high_lsp_tables.c \
			$(DIR)/external/speex/libspeex/jitter.c \
			$(DIR)/external/speex/libspeex/kiss_fft.c \
			$(DIR)/external/speex/libspeex/kiss_fftr.c \
			$(DIR)/external/speex/libspeex/lbr_48k_tables.c \
			$(DIR)/external/speex/libspeex/lpc.c \
			$(DIR)/external/speex/libspeex/lsp.c \
			$(DIR)/external/speex/libspeex/lsp_tables_nb.c \
			$(DIR)/external/speex/libspeex/ltp.c \
			$(DIR)/external/speex/libspeex/math_approx.c \
			$(DIR)/external/speex/libspeex/mdf.c \
			$(DIR)/external/speex/libspeex/misc.c \
			$(DIR)/external/speex/libspeex/modes.c \
			$(DIR)/external/speex/libspeex/nb_celp.c \
			$(DIR)/external/speex/libspeex/preprocess.c \
			$(DIR)/external/speex/libspeex/quant_lsp.c \
			$(DIR)/external/speex/libspeex/resample.c \
			$(DIR)/external/speex/libspeex/sb_celp.c \
			$(DIR)/external/speex/libspeex/smallft.c \
			$(DIR)/external/speex/libspeex/speex.c \
			$(DIR)/external/speex/libspeex/speex_callbacks.c \
			$(DIR)/external/speex/libspeex/speex_header.c \
			$(DIR)/external/speex/libspeex/stereo.c \
			$(DIR)/external/speex/libspeex/vbr.c \
			$(DIR)/external/speex/libspeex/vorbis_psy.c \
			$(DIR)/external/speex/libspeex/vq.c \
			$(DIR)/external/speex/libspeex/window.c \
			$(DIR)/framework/core/lightduer_debug.c \
			$(DIR)/framework/core/lightduer_memory.c \
			$(DIR)/framework/core/lightduer_mutex.c \
			$(DIR)/framework/core/lightduer_net_trans_encrypted.c \
			$(DIR)/framework/core/lightduer_net_transport.c \
			$(DIR)/framework/core/lightduer_net_transport_wrapper.c \
			$(DIR)/framework/core/lightduer_random.c \
			$(DIR)/framework/core/lightduer_sleep.c \
			$(DIR)/framework/core/lightduer_timestamp.c \
			$(DIR)/framework/utils/lightduer_hashcode.c \
			$(DIR)/framework/utils/lightduer_net_util.c \
			$(DIR)/framework/utils/lightduer_queue_cache.c \
			$(DIR)/framework/utils/lightduer_bitmap.c \
			$(DIR)/framework/utils/lightduer_handler.c \
			$(DIR)/framework/utils/lightduer_snprintf.c \
			$(DIR)/modules/coap/lightduer_coap.c \
			$(DIR)/modules/coap/lightduer_coap_ep.c \
			$(DIR)/modules/coap/lightduer_coap_trace.c \
			$(DIR)/modules/coap/lightduer_nsdl_adapter.c \
			$(DIR)/modules/connagent/lightduer_ca.c \
			$(DIR)/modules/connagent/lightduer_ca_conf.c \
			$(DIR)/modules/connagent/lightduer_connagent.c \
			$(DIR)/modules/connagent/lightduer_data_cache.c \
			$(DIR)/modules/connagent/lightduer_engine.c \
			$(DIR)/modules/connagent/lightduer_event_emitter.c \
			$(DIR)/modules/dcs/lightduer_dcs_alert.c \
			$(DIR)/modules/dcs/lightduer_dcs_audio_player.c \
			$(DIR)/modules/dcs/lightduer_dcs_device_contorl.c \
			$(DIR)/modules/dcs/lightduer_dcs_dummy.c \
			$(DIR)/modules/dcs/lightduer_dcs_local.c \
			$(DIR)/modules/dcs/lightduer_dcs_playback_control.c \
			$(DIR)/modules/dcs/lightduer_dcs_router.c \
			$(DIR)/modules/dcs/lightduer_dcs_screen.c \
			$(DIR)/modules/dcs/lightduer_dcs_speaker_control.c \
			$(DIR)/modules/dcs/lightduer_dcs_system.c \
			$(DIR)/modules/dcs/lightduer_dcs_voice_input.c \
			$(DIR)/modules/dcs/lightduer_dcs_voice_output.c \
			$(DIR)/modules/dcs/lightduer_dcs_miscellaneous.c \
			$(DIR)/modules/Device_Info/lightduer_dev_info.c \
			$(DIR)/modules/device_status/lightduer_ds_log.c \
			$(DIR)/modules/device_status/lightduer_ds_log_ca.c \
			$(DIR)/modules/device_status/lightduer_ds_log_audio.c \
			$(DIR)/modules/device_status/lightduer_ds_log_audio_player.c \
			$(DIR)/modules/device_status/lightduer_ds_log_cache.c \
			$(DIR)/modules/device_status/lightduer_ds_log_dcs.c \
			$(DIR)/modules/device_status/lightduer_ds_log_e2e.c \
			$(DIR)/modules/device_status/lightduer_ds_log_http.c \
			$(DIR)/modules/device_status/lightduer_ds_log_recorder.c \
			$(DIR)/modules/device_status/lightduer_ds_report.c \
			$(DIR)/modules/device_status/lightduer_ds_report_ca.c \
			$(DIR)modules/device_status/lightduer_ds_log_bind.c \
			$(DIR)modules/flash_strings/lightduer_flash_strings.c \
			$(DIR)/modules/interactive_class/lightduer_interactive_class.c \
			$(DIR)/modules/HTTP/lightduer_http_client.c \
			$(DIR)/modules/HTTP/lightduer_http_client_ops.c \
			$(DIR)/modules/HTTP/lightduer_http_dns_client_ops.c \
			$(DIR)/modules/ntp/lightduer_net_ntp.c \
			$(DIR)/modules/OTA/Downloader/lightduer_ota_downloader.c \
			$(DIR)/modules/OTA/Downloader/lightduer_ota_http_downloader.c \
			$(DIR)/modules/OTA/Notifier/lightduer_ota_notifier.c \
			$(DIR)/modules/OTA/Decompression/lightduer_ota_decompression.c \
			$(DIR)/modules/OTA/Decompression/lightduer_ota_zlib.c \
			$(DIR)/modules/OTA/Installer/lightduer_ota_installer.c \
			$(DIR)/modules/OTA/Unpacker/lightduer_ota_unpacker.c \
			$(DIR)/modules/OTA/Updater/lightduer_ota_updater.c \
			$(DIR)/modules/OTA/Verifier/lightduer_ota_verifier.c \
			$(DIR)/modules/SystemInfo/lightduer_system_info.c \
			$(DIR)/modules/bind_device/lightduer_bind_device.c \
			$(DIR)/modules/voice_engine/lightduer_session.c \
			$(DIR)/modules/voice_engine/lightduer_speex.c \
			$(DIR)/modules/voice_engine/lightduer_voice.c \
			$(DIR)/modules/voice_engine/lightduer_store_voice.c \
			$(DIR)/external/Zliblite/adler32.c \
			$(DIR)/external/Zliblite/compress.c \
			$(DIR)/external/Zliblite/crc32.c \
			$(DIR)/external/Zliblite/deflate.c \
			$(DIR)/external/Zliblite/infback.c \
			$(DIR)/external/Zliblite/inffast.c \
			$(DIR)/external/Zliblite/inflate.c \
			$(DIR)/external/Zliblite/inftrees.c \
			$(DIR)/external/Zliblite/trees.c \
			$(DIR)/external/Zliblite/uncompr.c \
			$(DIR)/external/Zliblite/zutil.c \
			$(DIR)/platform/source-freertos/baidu_ca_adapter.c \
			$(DIR)/platform/source-freertos/baidu_ca_debug_adp.c \
			$(DIR)/platform/source-freertos/baidu_ca_memory_adp.c \
			$(DIR)/platform/source-freertos/baidu_ca_mutex_adp.c \
			$(DIR)/platform/source-freertos/baidu_ca_socket_adp.c \
			$(DIR)/platform/source-freertos/lightduer_events.c \
			$(DIR)/platform/source-freertos/lightduer_priority_conf.c \
			$(DIR)/platform/source-freertos/lightduer_statistics.c \
			$(DIR)/platform/source-freertos/lightduer_timers.c \
			$(DIR)/platform/source-freertos/lightduer_adapter_config.c
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
