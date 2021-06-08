/******************************************************************************
 *
 * Copyright(c) 2007 - 2015 Realtek Corporation. All rights reserved.
 *
 *
 ******************************************************************************/
#include <platform_opts.h>

#if defined(CONFIG_PLATFORM_8710C)
#include <platform_opts_bt.h>
#endif
#if defined(CONFIG_PLATFORM_8721D)
#include <platform_opts_bt.h>
#endif
#include "main.h"

#if ATCMD_VER == ATVER_2
#include "flash_api.h"
#include "device_lock.h"
#endif
   
#if defined(CONFIG_EXAMPLE_MDNS) && CONFIG_EXAMPLE_MDNS
#include <mdns/example_mdns.h>
#endif

#if CONFIG_EXAMPLE_MCAST
#include <mcast/example_mcast.h>
#endif

#if CONFIG_EXAMPLE_XML
#include <xml/example_xml.h>
#endif

#if (defined(CONFIG_EXAMPLE_UART_ATCMD) && CONFIG_EXAMPLE_UART_ATCMD)
#include <uart_atcmd/example_uart_atcmd.h>
#include <freertos_pmu.h>
#endif

#if CONFIG_EXAMPLE_SOCKET_SELECT
#include <socket_select/example_socket_select.h>
#endif

#if CONFIG_EXAMPLE_NONBLOCK_CONNECT
#include <nonblock_connect/example_nonblock_connect.h>
#endif

#if defined(CONFIG_EXAMPLE_SOCKET_TCP_TRX) && CONFIG_EXAMPLE_SOCKET_TCP_TRX
#include <socket_tcp_trx/example_socket_tcp_trx.h>
#endif

#if defined(CONFIG_EXAMPLE_SMTP) && CONFIG_EXAMPLE_SMTP
#include <smtp/example_smtp.h>
#endif

#if CONFIG_EXAMPLE_SSL_DOWNLOAD
#include <ssl_download/example_ssl_download.h>
#endif

#if CONFIG_EXAMPLE_HTTP_CLIENT
#include <http_client/example_http_client.h>
#endif

#if CONFIG_EXAMPLE_HTTP_DOWNLOAD
#include <http_download/example_http_download.h>
#endif

#if defined(CONFIG_EXAMPLE_HTTPC) && CONFIG_EXAMPLE_HTTPC
#include <httpc/example_httpc.h>
#endif

#if defined(CONFIG_EXAMPLE_HTTPD) && CONFIG_EXAMPLE_HTTPD
#include <httpd/example_httpd.h>
#endif

#if defined(CONFIG_EXAMPLE_HTTP2_CLIENT) && CONFIG_EXAMPLE_HTTP2_CLIENT
#include <http2_client/example_http2_client.h>
#endif

#if CONFIG_EXAMPLE_TCP_KEEPALIVE
#include <tcp_keepalive/example_tcp_keepalive.h>
#endif

#if CONFIG_EXAMPLE_SNTP_SHOWTIME
#include <sntp_showtime/example_sntp_showtime.h>
#endif

#if defined(CONFIG_EXAMPLE_PPPOE) && CONFIG_EXAMPLE_PPPOE
#include <pppoe/example_pppoe.h>
#endif

#if defined(CONFIG_EXAMPLE_AZURE_IOT_HUB) && CONFIG_EXAMPLE_AZURE_IOT_HUB
#include <azure_iot_hub/example_azure_iot_hub.h>
#endif

#if defined(CONFIG_EXAMPLE_GOOGLE_NEST) && CONFIG_EXAMPLE_GOOGLE_NEST
#include <googlenest/example_google.h>  
#define FromDevice            1
#define ToDevice     		2 
#define BOTH     		3 
#define TYPE         "ToDevice"
#endif   

#if defined(CONFIG_EXAMPLE_GOOGLE_CLOUD_IOT) && CONFIG_EXAMPLE_GOOGLE_CLOUD_IOT
#include <google_cloud_iot/example_google_cloud_iot.h>  
#endif  

#if defined(CONFIG_EXAMPLE_MJPEG_CAPTURE) && CONFIG_EXAMPLE_MJPEG_CAPTURE
#include <mjpeg_capture/example_mjpeg.h>
#endif

#if defined(CONFIG_EXAMPLE_TRUST_ZONE) && (CONFIG_EXAMPLE_TRUST_ZONE)
#include <trust_zone/example_trust_zone.h>
#endif

#if CONFIG_EXAMPLE_WLAN_FAST_CONNECT
#include <wlan_fast_connect/example_wlan_fast_connect.h>
#endif

#if defined(CONFIG_EXAMPLE_WIGADGET) && CONFIG_EXAMPLE_WIGADGET
#include <wigadget/wigadget.h>
#endif

#if CONFIG_EXAMPLE_MQTT
#include <mqtt/example_mqtt.h>
#endif

#if CONFIG_EXAMPLE_FATFS
#include <fatfs/example_fatfs.h>
#endif
   
#if defined(CONFIG_EXAMPLE_STD_FILE) && (CONFIG_EXAMPLE_STD_FILE)
#include <std_file/example_std_file.h>
#endif

#if defined(CONFIG_EXAMPLE_DCT) && CONFIG_EXAMPLE_DCT
#include <dct/example_dct.h>
#endif

#if defined(CONFIG_EXAMPLE_INIC_GSPI_HOST) && CONFIG_EXAMPLE_INIC_GSPI_HOST
#include <inic_gspi/example_inic_gspi.h>
#endif

#if defined(CONFIG_EXAMPLE_ARDUINO_WIFI) && CONFIG_EXAMPLE_ARDUINO_WIFI
#include <arduino_wifi/ard_spi.h>
#endif

#if defined(CONFIG_EXAMPLE_GET_BEACON_FRAME) && CONFIG_EXAMPLE_GET_BEACON_FRAME
#include <get_beacon_frame/example_get_beacon_frame.h>
#endif

#if defined(CONFIG_EXAMPLE_EAP) && CONFIG_EXAMPLE_EAP
#include <eap/example_eap.h>
#endif

#if defined(CONFIG_EXAMPLE_AJ_BASIC) && CONFIG_EXAMPLE_AJ_BASIC
#include <alljoyn/example_aj_basic.h>
#endif 

#if defined(CONFIG_EXAMPLE_AJ_AMEBA_LED) && CONFIG_EXAMPLE_AJ_AMEBA_LED
#include <alljoyn/example_aj_ameba_led.h>
#endif 

#if defined(CONFIG_EXAMPLE_COAP) && CONFIG_EXAMPLE_COAP
#include <coap/example_coap.h>
#endif

#if defined(CONFIG_EXAMPLE_COAP_CLIENT) && CONFIG_EXAMPLE_COAP_CLIENT
#include <coap_client/example_coap_client.h>
#endif

#if defined(CONFIG_EXAMPLE_COAP_SERVER) && CONFIG_EXAMPLE_COAP_SERVER
#include <coap_server/example_coap_server.h>
#endif

#if defined(CONFIG_EXAMPLE_WEBSOCKET_CLIENT) && CONFIG_EXAMPLE_WEBSOCKET_CLIENT
#include <websocket_client/example_wsclient.h>
#endif

#if defined(CONFIG_EXAMPLE_WEBSOCKET_SERVER) && CONFIG_EXAMPLE_WEBSOCKET_SERVER
#include <websocket_server/example_ws_server.h>
#endif

#if CONFIG_EXAMPLE_WLAN_SCENARIO
#include <wlan_scenario/example_wlan_scenario.h>
#endif

#if defined(CONFIG_EXAMPLE_WLAN_REPEATER) && CONFIG_EXAMPLE_WLAN_REPEATER
#include <wlan_repeater/example_wlan_repeater.h>
#endif

#if defined(CONFIG_EXAMPLE_BCAST) && CONFIG_EXAMPLE_BCAST
#include <bcast/example_bcast.h>
#endif

#if defined(CONFIG_EXAMPLE_AUDIO) && CONFIG_EXAMPLE_AUDIO
#include <audio/example_audio.h>
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_MP3) && CONFIG_EXAMPLE_AUDIO_MP3
#include <audio_mp3/example_audio_mp3.h>
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_M4A) && CONFIG_EXAMPLE_AUDIO_M4A
#include <audio_m4a/example_audio_m4a.h>
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_M4A_SELFPARSE) && CONFIG_EXAMPLE_AUDIO_M4A_SELFPARSE
#include <audio_m4a_selfparse/example_audio_m4a_selfparse.h>
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_M4A_MP3) && CONFIG_EXAMPLE_AUDIO_M4A_MP3
#include <audio_m4a_mp3/example_audio_m4a_mp3.h>
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_AMR) && CONFIG_EXAMPLE_AUDIO_AMR
#include <audio_amr/example_audio_amr.h>
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_HLS) && CONFIG_EXAMPLE_AUDIO_HLS
#include <audio_hls/example_audio_hls.h>
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_HELIX_AAC) && CONFIG_EXAMPLE_AUDIO_HELIX_AAC
#include <audio_helix_aac/example_audio_helix_aac.h>
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_HELIX_MP3) && CONFIG_EXAMPLE_AUDIO_HELIX_MP3
#include <audio_helix_mp3/example_audio_helix_mp3.h>
#endif

#if defined(CONFIG_EXAMPLE_HIGH_LOAD_MEMORY_USE) && CONFIG_EXAMPLE_HIGH_LOAD_MEMORY_USE
#include <high_load_memory_use/example_high_load_memory_use.h>
#endif

#if CONFIG_EXAMPLE_WIFI_MAC_MONITOR
#include <wifi_mac_monitor/example_wifi_mac_monitor.h>
#endif

#if CONFIG_EXAMPLE_WIFI_MANAGER
#include <wifi_manager/example_wifi_manager.h>
#endif

#if defined(CONFIG_EXAMPLE_RARP) && CONFIG_EXAMPLE_RARP
#include <rarp/example_rarp.h>
#endif

#if (defined(CONFIG_EXAMPLE_UART_ATCMD) && CONFIG_EXAMPLE_UART_ATCMD)
#include <uart_atcmd/example_uart_atcmd.h>
#endif

#if CONFIG_EXAMPLE_SSL_SERVER
#include <ssl_server/example_ssl_server.h>
#endif

#if defined(CONFIG_EXAMPLE_OTA_HTTP) && CONFIG_EXAMPLE_OTA_HTTP
#include <ota_http/example_ota_http.h>
#endif

#if defined(CONFIG_EXAMPLE_OTA_HTTPS) && CONFIG_EXAMPLE_OTA_HTTPS
#include <ota_https/example_ota_https.h>
#endif

#if defined(CONFIG_EXAMPLE_OTA_SDCARD) && CONFIG_EXAMPLE_OTA_SDCARD
#include <ota_sdcard/example_ota_sdcard.h>
#endif

#if defined(CONFIG_EXAMPLE_AMAZON_AWS_IOT) && CONFIG_EXAMPLE_AMAZON_AWS_IOT
#include <amazon_awsiot/example_amazon_awsiot.h>
#endif

#if defined(CONFIG_EXAMPLE_ALC_DSP_FW_UPGRADE) && CONFIG_EXAMPLE_ALC_DSP_FW_UPGRADE
#include <alc_dsp_fw_upgrade/example_alc_dsp_fw_upgrade.h>
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_PCM_UPLOAD) && CONFIG_EXAMPLE_AUDIO_PCM_UPLOAD
#include <audio_pcm_upload/example_audio_pcm_upload.h>
#endif

#if defined(CONFIG_EXAMPLE_WIFI_ROAMING) && CONFIG_EXAMPLE_WIFI_ROAMING
#include <wifi_roaming/example_wifi_roaming.h>
#endif

#if defined(CONFIG_EXAMPLE_WIFI_ROAMING_PLUS) && CONFIG_EXAMPLE_WIFI_ROAMING_PLUS
#include <wifi_roaming_plus/example_wifi_roaming_plus.h>
#endif

#if defined(CONFIG_EXAMPLE_TICKLESS_WIFI_ROAMING) && CONFIG_EXAMPLE_TICKLESS_WIFI_ROAMING
#include <tickless_wifi_roaming/example_tickless_wifi_roaming.h>
#endif

#if defined(CONFIG_EXAMPLE_CONN_PRI_COND) && CONFIG_EXAMPLE_CONN_PRI_COND
#include "wifi_connection_priority/example_wifi_conn_pri_cond.h"
#endif

#if defined(CONFIG_EXAMPLE_FLASH_MP3) && CONFIG_EXAMPLE_FLASH_MP3
#include <flash_mp3/example_flash_mp3.h>
#endif

#if defined(CONFIG_EXAMPLE_CJSON) && CONFIG_EXAMPLE_CJSON
#include <cJSON/example_cJSON.h>
#endif
	
#if defined(CONFIG_MEDIA_H264_TO_SDCARD) && CONFIG_MEDIA_H264_TO_SDCARD
#include <media_h264_to_sdcard/example_media_h264_to_sdcard.h>
#endif

#if defined(CONFIG_EXAMPLE_MEDIA_FRAMEWORK) && CONFIG_EXAMPLE_MEDIA_FRAMEWORK
#include <media_framework/example_media_framework.h>
#endif

#if defined(CONFIG_EXAMPLE_MEDIA_FRAMEWORK_SD_DETECT) && CONFIG_EXAMPLE_MEDIA_FRAMEWORK_SD_DETECT
#include <media_framework/example_media_framework_sd_detect.h>
#endif

#if defined(CONFIG_EXAMPLE_MEDIA_UVCD) && CONFIG_EXAMPLE_MEDIA_UVCD
#include <media_uvcd/example_media_uvcd.h>
#endif

#if defined(CONFIG_SDCARD_UPLOAD_HTTPD) && CONFIG_SDCARD_UPLOAD_HTTPD
#include <sdcard_upload_httpd/example_sdcard_upload_httpd.h>
#endif

#if defined(CONFIG_EXAMPLE_QR_CODE_SCANNER) && CONFIG_EXAMPLE_QR_CODE_SCANNER
#include <qr_code_scanner/example_qr_code_scanner.h>
#endif

#if defined(CONFIG_BT) && CONFIG_BT
#include <bt_example_entry.h>
#endif

#if defined(CONFIG_EXAMPLE_COMPETITIVE_HEADPHONES_DONGLE) && CONFIG_EXAMPLE_COMPETITIVE_HEADPHONES_DONGLE
#include <competitive_headphones_dongle/example_competitive_headphones_dongle.h>
#endif

#if defined(CONFIG_EXAMPLE_COMPETITIVE_HEADPHONES) && CONFIG_EXAMPLE_COMPETITIVE_HEADPHONES
#include <competitive_headphones/example_competitive_headphones.h>
#endif

#if defined(CONFIG_EXAMPLE_SECURE_BOOT) && CONFIG_EXAMPLE_SECURE_BOOT
#include <secure_boot/example_secure_boot.h>
#endif

#if defined(CONFIG_EXAMPLE_BT_MESH_DEMO) && CONFIG_EXAMPLE_BT_MESH_DEMO
#include <bt_mesh_demo/example_bt_mesh_demo.h>
#endif

#if defined (CONFIG_EXAMPLE_IPV6) && (CONFIG_EXAMPLE_IPV6)
#include <ipv6/example_ipv6.h>
#endif

#if defined(CONFIG_EXAMPLE_USB_MASS_STORAGE) && CONFIG_EXAMPLE_USB_MASS_STORAGE
#include <usb_mass_storage/example_usb_msc.h>
#endif

#if defined(CONFIG_EXAMPLE_USBD_AUDIO) && CONFIG_EXAMPLE_USBD_AUDIO
#include <usbd_audio/example_usbd_audio.h>
#endif

#if defined(CONFIG_EXAMPLE_USBD_MSC) && CONFIG_EXAMPLE_USBD_MSC
#include <usbd_msc/example_usbd_msc.h>
#endif

#if defined(CONFIG_EXAMPLE_USBD_CDC_ACM) && CONFIG_EXAMPLE_USBD_CDC_ACM
#include <usbd_cdc_acm/example_usbd_cdc_acm.h>
#endif

#if defined(CONFIG_EXAMPLE_USBD_VENDOR) && CONFIG_EXAMPLE_USBD_VENDOR
#include <usbd_vendor/example_usbd_vendor.h>
#endif

#if defined(CONFIG_EXAMPLE_USBD_HID) && CONFIG_EXAMPLE_USBD_HID
#include <usbd_hid_mouse/example_usbd_hid_mouse.h>
#endif

#if defined(CONFIG_EXAMPLE_USBH_MSC) && CONFIG_EXAMPLE_USBH_MSC
#include <usbh_msc/example_usbh_msc.h>
#endif

#if defined(CONFIG_EXAMPLE_USBH_UVC) && CONFIG_EXAMPLE_USBH_UVC
#include <usbh_uvc/example_usbh_uvc.h>
#endif

#if defined(CONFIG_EXAMPLE_USBH_VENDOR) && CONFIG_EXAMPLE_USBH_VENDOR
#include <usbh_vendor/example_usbh_vendor.h>
#endif

#if defined(CONFIG_EXAMPLE_USBH_CDC_ACM) && CONFIG_EXAMPLE_USBH_CDC_ACM
#include <usbh_cdc_acm/example_usbh_cdc_acm.h>
#endif

#if (CONFIG_EXAMPLE_AMAZON_FREERTOS)
#include <amazon_freertos/example_amazon_freertos.h>
#endif

/*
	Preprocessor of example
*/
void pre_example_entry(void)
{

#if defined(CONFIG_EXAMPLE_CM_BACKTRACE) && CONFIG_EXAMPLE_CM_BACKTRACE
	cm_backtrace_init("target_img2", "HW v1.0", "SW v1.0");
#endif

#if ATCMD_VER == ATVER_2
	flash_t flash;
	struct wlan_fast_reconnect read_data = {0};
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_stream_read(&flash, FAST_RECONNECT_DATA, sizeof(struct wlan_fast_reconnect), (u8 *) &read_data);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
#endif

#if CONFIG_EXAMPLE_WLAN_FAST_CONNECT
#if ATCMD_VER == ATVER_2
	if(read_data.enable == 1)
#endif
	{
		example_wlan_fast_connect();
	}
#endif
#if defined(CONFIG_JD_SMART) && CONFIG_JD_SMART
	example_jdsmart_init();
#endif
#if defined(CONFIG_EXAMPLE_UART_ADAPTER) && CONFIG_EXAMPLE_UART_ADAPTER
	example_uart_adapter_init();
#endif
#if defined(CONFIG_EXAMPLE_ARDUINO_WIFI) && CONFIG_EXAMPLE_ARDUINO_WIFI
    /*To ensure the application has enough heap size, please goto FreeRTOSConfig.h to change configTOTAL_HEAP_SIZE at least to 80*1024 */
    example_arduino_wifi_init();
#endif
#if defined(CONFIG_EXAMPLE_WIFI_ROAMING_PLUS) && CONFIG_EXAMPLE_WIFI_ROAMING_PLUS
	example_wifi_roaming_plus_init();
#endif
#if defined(CONFIG_EXAMPLE_TICKLESS_WIFI_ROAMING) && CONFIG_EXAMPLE_TICKLESS_WIFI_ROAMING
	example_tickless_wifi_roaming_init();
#endif

#if defined(FREERTOS_PMU_TICKLESS_PLL_RESERVED) && (FREERTOS_PMU_TICKLESS_PLL_RESERVED==1)
    pmu_set_pll_reserved(1);
#endif

#if (configGENERATE_RUN_TIME_STATS == 1)
    //pmu_enable_wakelock_stats(1);
#endif

#if defined(CONFIG_BAIDU_DUER) && CONFIG_BAIDU_DUER
    initialize_peripheral();
#endif

#if defined(CONFIG_PLATFORM_8710C) && defined(CONFIG_FTL_ENABLED)
	app_ftl_init();
#endif

}

#if ((defined CONFIG_BT_MESH_PROVISIONER_RTK_DEMO && CONFIG_BT_MESH_PROVISIONER_RTK_DEMO) || (defined CONFIG_BT_MESH_DEVICE_RTK_DEMO && CONFIG_BT_MESH_DEVICE_RTK_DEMO))
extern void example_bt_mesh(void);
#endif

/*
  	All of the examples are disabled by default for code size consideration
   	The configuration is enabled in platform_opts.h
*/
void example_entry(void)
{	
#if defined(CONFIG_LINKKIT_AWSS) && CONFIG_LINKKIT_AWSS
	example_ali_awss();
#endif

#if (CONFIG_EXAMPLE_MDNS && !CONFIG_EXAMPLE_UART_ADAPTER) 
	example_mdns();
#endif

#if CONFIG_EXAMPLE_MCAST
	example_mcast();
#endif
#if CONFIG_EXAMPLE_XML
	example_xml();
#endif

#if CONFIG_EXAMPLE_SOCKET_SELECT
	example_socket_select();
#endif

#if CONFIG_EXAMPLE_NONBLOCK_CONNECT
	example_nonblock_connect();
#endif

#if defined(CONFIG_EXAMPLE_SOCKET_TCP_TRX) && (CONFIG_EXAMPLE_SOCKET_TCP_TRX == 1)
	example_socket_tcp_trx_1();
#elif defined(CONFIG_EXAMPLE_SOCKET_TCP_TRX) && (CONFIG_EXAMPLE_SOCKET_TCP_TRX == 2)
	example_socket_tcp_trx_2();
#endif

#if defined(CONFIG_EXAMPLE_SMTP) && CONFIG_EXAMPLE_SMTP
	example_smtp();
#endif
        
#if CONFIG_EXAMPLE_SSL_DOWNLOAD
	example_ssl_download();
#endif

#if CONFIG_EXAMPLE_HTTP_DOWNLOAD
	example_http_download();
#endif

#if defined(CONFIG_EXAMPLE_HTTPC) && CONFIG_EXAMPLE_HTTPC
	example_httpc();
#endif

#if defined(CONFIG_EXAMPLE_HTTPD) && CONFIG_EXAMPLE_HTTPD
	example_httpd();
#endif

#if defined(CONFIG_EXAMPLE_HTTP2_CLIENT) && CONFIG_EXAMPLE_HTTP2_CLIENT
    example_http2_client();
#endif

#if CONFIG_EXAMPLE_TCP_KEEPALIVE
	example_tcp_keepalive();
#endif

#if CONFIG_EXAMPLE_SNTP_SHOWTIME
	example_sntp_showtime();
#endif

#if defined(CONFIG_EXAMPLE_PPPOE) && CONFIG_EXAMPLE_PPPOE
	example_pppoe();
#endif

#if defined(CONFIG_EXAMPLE_GOOGLE_NEST) && CONFIG_EXAMPLE_GOOGLE_NEST
	example_google(TYPE);
#endif

#if defined(CONFIG_EXAMPLE_GOOGLE_CLOUD_IOT) && CONFIG_EXAMPLE_GOOGLE_CLOUD_IOT
	example_google_cloud_iot();
#endif

#if defined(CONFIG_UART_UPDATE) && CONFIG_UART_UPDATE
	example_uart_update();
#endif  

#if defined(CONFIG_EXAMPLE_WIGADGET) && CONFIG_EXAMPLE_WIGADGET
    /*To ensure the application has enough heap size, please goto FreeRTOSConfig.h to change configTOTAL_HEAP_SIZE at least to 115*1024 */
    example_wigadget();         
#endif

#if CONFIG_EXAMPLE_MQTT
	example_mqtt();
#endif

#if CONFIG_QQ_LINK
	example_qq_link();
#endif

#if CONFIG_JOYLINK
	example_joylink();
#endif

#if defined(CONFIG_AIRKISS_CLOUD) && CONFIG_AIRKISS_CLOUD
	example_airkiss_cloud();
#endif

#if CONFIG_EXAMPLE_WIFI_MAC_MONITOR
	example_wifi_mac_monitor();
#endif

#if CONFIG_EXAMPLE_WIFI_MANAGER
	example_wifi_manager();
#endif

#if CONFIG_EXAMPLE_HTTP_CLIENT        
        example_http_client();
#endif
        
#if defined(CONFIG_JOINLINK) && CONFIG_JOINLINK
	example_joinlink();
#endif

#if defined(CONFIG_EXAMPLE_GET_BEACON_FRAME) && CONFIG_EXAMPLE_GET_BEACON_FRAME
	example_get_beacon_frame();
#endif

#if CONFIG_EXAMPLE_FATFS
	example_fatfs();
#endif
        
#if defined (CONFIG_EXAMPLE_STD_FILE) && (CONFIG_EXAMPLE_STD_FILE)
        example_std_file();
#endif        


#if defined(CONFIG_EXAMPLE_DCT) && CONFIG_EXAMPLE_DCT
	example_dct();
#endif

#if CONFIG_GAGENT
	example_gagent();
#endif

#if defined(CONFIG_EXAMPLE_INIC_GSPI_HOST) && CONFIG_EXAMPLE_INIC_GSPI_HOST
	example_inic_gspi();
#endif       
        
#if (defined(CONFIG_EXAMPLE_UART_ATCMD) && CONFIG_EXAMPLE_UART_ATCMD)
	example_uart_atcmd();
#endif

#if defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD
    example_spi_atcmd();
#endif

#if defined(CONFIG_EXAMPLE_MJPEG_CAPTURE) && CONFIG_EXAMPLE_MJPEG_CAPTURE
	example_mjpeg();
#endif

// supported eap methods: tls, peap, ttls
// make sure the corresponding config has been turned on before you use it
// e.g. set CONFIG_ENABLE_TLS to 1 if you want to use TLS eap method
#if defined(CONFIG_EXAMPLE_EAP) && CONFIG_EXAMPLE_EAP
	example_eap("tls");
	//example_eap("peap");
	//example_eap("ttls");
#endif

#if defined(CONFIG_EXAMPLE_AJ_BASIC) && CONFIG_EXAMPLE_AJ_BASIC
    example_aj_basic();
#endif
           
#if defined(CONFIG_EXAMPLE_AJ_AMEBA_LED) && CONFIG_EXAMPLE_AJ_AMEBA_LED
    example_aj_ameba_led();
#endif
        
#if defined(CONFIG_EXAMPLE_COAP) && CONFIG_EXAMPLE_COAP
    example_coap();
#endif

#if defined(CONFIG_EXAMPLE_COAP_CLIENT) && CONFIG_EXAMPLE_COAP_CLIENT
    example_coap_client();
#endif

#if defined(CONFIG_EXAMPLE_COAP_SERVER) && CONFIG_EXAMPLE_COAP_SERVER
    example_coap_server();
#endif

#if defined(CONFIG_EXAMPLE_WEBSOCKET_CLIENT) && CONFIG_EXAMPLE_WEBSOCKET_CLIENT
    example_wsclient();
#endif
    
#if defined(CONFIG_EXAMPLE_WEBSOCKET_SERVER) && CONFIG_EXAMPLE_WEBSOCKET_SERVER
    example_wsserver();
#endif

#if CONFIG_EXAMPLE_WLAN_SCENARIO
	// For Network Scan, Authentication, Mode Switch, Sequence Senario cases
	// Para: S/ A/ M1/ M2/ M3/ M4/ M5/ M6/ M7/ S1/ S2/ S3/ S4/ S5/ S6
	example_wlan_scenario("S");
#endif
	
#if defined(CONFIG_EXAMPLE_WLAN_REPEATER) && CONFIG_EXAMPLE_WLAN_REPEATER
	example_wlan_repeater();
#endif

#if defined(CONFIG_EXAMPLE_BCAST) && CONFIG_EXAMPLE_BCAST
	example_bcast();
#endif

#if defined(CONFIG_EXAMPLE_AUDIO) && CONFIG_EXAMPLE_AUDIO
	example_audio();
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_MP3) && CONFIG_EXAMPLE_AUDIO_MP3
/*To ensure the application has enough heap size, please goto FreeRTOSConfig.h to change configTOTAL_HEAP_SIZE at least to 60*1024 */
	example_audio_mp3();
#endif     

#if defined(CONFIG_EXAMPLE_AUDIO_AC3) && CONFIG_EXAMPLE_AUDIO_AC3
	example_audio_ac3();
#endif     

#if defined(CONFIG_EXAMPLE_AUDIO_M4A) && CONFIG_EXAMPLE_AUDIO_M4A
/*To ensure the application has enough heap size, please goto FreeRTOSConfig.h to change configTOTAL_HEAP_SIZE at least to 270*1024 and ENABLE WIFI*/
	example_audio_m4a();
#endif  
        
#if defined(CONFIG_EXAMPLE_AUDIO_M4A_SELFPARSE) && CONFIG_EXAMPLE_AUDIO_M4A_SELFPARSE
/*To ensure the application has enough heap size, please goto FreeRTOSConfig.h to change configTOTAL_HEAP_SIZE at least to 270*1024 and ENABLE WIFI*/
	example_audio_m4a_selfparse();
#endif 

#if defined(CONFIG_EXAMPLE_AUDIO_OPUS) && CONFIG_EXAMPLE_AUDIO_OPUS
	example_audio_opus();
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_M4A_MP3) && CONFIG_EXAMPLE_AUDIO_M4A_MP3
	example_audio_m4a_mp3();
#endif  

#if defined(CONFIG_EXAMPLE_AUDIO_AMR) && CONFIG_EXAMPLE_AUDIO_AMR
	example_audio_amr();
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_AMR_FLASH) && CONFIG_EXAMPLE_AUDIO_AMR_FLASH
	example_audio_amr_flash();
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_HLS) && CONFIG_EXAMPLE_AUDIO_HLS
	example_audio_hls();
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_RECORDER) && CONFIG_EXAMPLE_AUDIO_RECORDER
	example_audio_recorder();
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_HELIX_AAC) && CONFIG_EXAMPLE_AUDIO_HELIX_AAC
    example_audio_helix_aac();
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_HELIX_MP3) && CONFIG_EXAMPLE_AUDIO_HELIX_MP3
    example_audio_helix_mp3();
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_FLAC) && CONFIG_EXAMPLE_AUDIO_FLAC
	example_audio_flac();
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_TTS) && CONFIG_EXAMPLE_AUDIO_TTS 
	example_audio_tts();
#endif

#if defined(CONFIG_EXAMPLE_EKHO) && CONFIG_EXAMPLE_EKHO 
	example_audio_ekho();
#endif

#if defined(CONFIG_EXAMPLE_TTS_CYBERON) && CONFIG_EXAMPLE_TTS_CYBERON
	example_audio_tts_with_cyberon();
#endif


#if defined(CONFIG_EXAMPLE_AUDIO_OPUS_DECODE) && CONFIG_EXAMPLE_AUDIO_OPUS_DECODE
	example_audio_opus_decode();
#endif

#if defined(CONFIG_EXAMPLE_AUDIO_OPUS_ENCODE) && CONFIG_EXAMPLE_AUDIO_OPUS_ENCODE
	example_audio_opus_encode();
#endif

#if defined(CONFIG_EXAMPLE_HIGH_LOAD_MEMORY_USE) && CONFIG_EXAMPLE_HIGH_LOAD_MEMORY_USE
	example_high_load_memory_use();
#endif

#if defined(CONFIG_EXAMPLE_RARP) && CONFIG_EXAMPLE_RARP
	example_rarp();
#endif 

#if CONFIG_EXAMPLE_SSL_SERVER
	example_ssl_server();
#endif  
        
#if defined(CONFIG_EXAMPLE_TIMELAPSE) && CONFIG_EXAMPLE_TIMELAPSE
        example_media_tl();
#endif

#if defined(CONFIG_EXAMPLE_OTA_HTTP) && CONFIG_EXAMPLE_OTA_HTTP
	example_ota_http();
#endif 

#if defined(CONFIG_EXAMPLE_OTA_HTTPS) && CONFIG_EXAMPLE_OTA_HTTPS
	example_ota_https();
#endif

#if defined(CONFIG_EXAMPLE_OTA_SDCARD) && CONFIG_EXAMPLE_OTA_SDCARD
	example_ota_sdcard();
#endif
	
#if defined(CONFIG_EXAMPLE_AMAZON_AWS_IOT) && CONFIG_EXAMPLE_AMAZON_AWS_IOT
    example_amazon_awsiot();
#endif

#if defined(CONFIG_EXAMPLE_AZURE_IOT_HUB) && CONFIG_EXAMPLE_AZURE_IOT_HUB
    example_iot_hub();
#endif
    
#if CONFIG_ALINK
	example_alink();
#endif

#if defined(CONFIG_HILINK) && CONFIG_HILINK
example_hilink();
#endif

#if defined(CONFIG_EXAMPLE_ALC_DSP_FW_UPGRADE) && CONFIG_EXAMPLE_ALC_DSP_FW_UPGRADE
        example_alc_dsp_fw_upgrade();
#endif
        
#if defined(CONFIG_EXAMPLE_AUDIO_PCM_UPLOAD) && CONFIG_EXAMPLE_AUDIO_PCM_UPLOAD
        example_audio_pcm_upload();
#endif 

#if defined(CONFIG_EXAMPLE_WIFI_ROAMING) && CONFIG_EXAMPLE_WIFI_ROAMING
	example_wifi_roaming();
#endif

#if defined(CONFIG_EXAMPLE_WIFI_ROAMING_PLUS) && CONFIG_EXAMPLE_WIFI_ROAMING_PLUS
	example_wifi_roaming_plus();
#endif

#if defined(CONFIG_EXAMPLE_TICKLESS_WIFI_ROAMING) && CONFIG_EXAMPLE_TICKLESS_WIFI_ROAMING
	example_tickless_wifi_roaming();
#endif

#if defined(CONFIG_EXAMPLE_CONN_PRI_COND) && CONFIG_EXAMPLE_CONN_PRI_COND
	example_init_conn_pri_cond();
#endif

#if defined(CONFIG_EXAMPLE_FLASH_MP3) && CONFIG_EXAMPLE_FLASH_MP3
	example_flash_mp3();
#endif

#if defined(CONFIG_EXAMPLE_CJSON) && CONFIG_EXAMPLE_CJSON
	example_cJSON();
#endif

#if defined(CONFIG_MEDIA_AMEBACAM_APP_BROADCAST) && CONFIG_MEDIA_AMEBACAM_APP_BROADCAST
	media_amebacam_broadcast();
#endif
	
#if defined(CONFIG_MEDIA_H264_TO_SDCARD) && CONFIG_MEDIA_H264_TO_SDCARD
	example_media_h264_to_sdcard();
#endif

#if defined(CONFIG_EXAMPLE_MEDIA_FRAMEWORK) && CONFIG_EXAMPLE_MEDIA_FRAMEWORK
	example_media_framework();
#endif

#if defined(CONFIG_EXAMPLE_MEDIA_FRAMEWORK_SD_DETECT) && CONFIG_EXAMPLE_MEDIA_FRAMEWORK_SD_DETECT
	example_media_framework_sd_detect();
#endif

#if defined(CONFIG_EXAMPLE_MEDIA_UVCD) && CONFIG_EXAMPLE_MEDIA_UVCD
	example_media_uvcd();
#endif

#if defined(CONFIG_SDCARD_UPLOAD_HTTPD) && CONFIG_SDCARD_UPLOAD_HTTPD
	example_sdcard_upload_httpd();
#endif

#if defined(CONFIG_EXAMPLE_QR_CODE_SCANNER) && CONFIG_EXAMPLE_QR_CODE_SCANNER
	example_qr_code_scanner();
#endif

#if defined(CONFIG_BAIDU_DUER) && CONFIG_BAIDU_DUER
        example_duer();
#endif

#if defined(CONFIG_BT) && CONFIG_BT
	// do not start example if defined BT MP or WIFI MP
	#if !(defined(CONFIG_MP_INCLUDED))
	bt_example_init();
	#endif
#endif

#if defined(CONFIG_EXAMPLE_USB_MASS_STORAGE) && CONFIG_EXAMPLE_USB_MASS_STORAGE
	example_mass_storage();
#endif

#if defined(CONFIG_EXAMPLE_USB_ISOC_DEVICE) && CONFIG_EXAMPLE_USB_ISOC_DEVICE        
    example_isoc_device();
#endif

#if defined(CONFIG_EXAMPLE_USB_VENDOR_SPECIFIC) && CONFIG_EXAMPLE_USB_VENDOR_SPECIFIC
	example_vendor_specific();
#endif 

#if defined(CONFIG_EXAMPLE_USBD_AUDIO) && CONFIG_EXAMPLE_USBD_AUDIO	        
	example_usbd_audio();
#endif

#if defined(CONFIG_EXAMPLE_USBD_MSC) && CONFIG_EXAMPLE_USBD_MSC	        
	example_usbd_msc();
#endif

#if defined(CONFIG_EXAMPLE_USBD_CDC_ACM) && CONFIG_EXAMPLE_USBD_CDC_ACM
	example_usbd_cdc_acm();
#endif

#if defined(CONFIG_EXAMPLE_USBD_HID) && CONFIG_EXAMPLE_USBD_HID
	example_usbd_hid_mouse();
#endif

#if defined(CONFIG_EXAMPLE_USBD_VENDOR) && CONFIG_EXAMPLE_USBD_VENDOR
	example_usbd_vendor();
#endif

#if defined(CONFIG_EXAMPLE_USBH_MSC) && CONFIG_EXAMPLE_USBH_MSC	        
	example_usbh_msc();
#endif

#if defined(CONFIG_EXAMPLE_USBH_UVC) && CONFIG_EXAMPLE_USBH_UVC	        
	example_usbh_uvc();
#endif

#if defined(CONFIG_EXAMPLE_USBH_VENDOR) && CONFIG_EXAMPLE_USBH_VENDOR	        
	example_usbh_vendor();
#endif

#if defined(CONFIG_EXAMPLE_USBH_CDC_ACM) && CONFIG_EXAMPLE_USBH_CDC_ACM
	example_usbh_cdc_acm();
#endif

#if defined(CONFIG_EXAMPLE_COMPETITIVE_HEADPHONES) && CONFIG_EXAMPLE_COMPETITIVE_HEADPHONES
//	example_competitive_headphones();
#endif
#if defined(CONFIG_EXAMPLE_COMPETITIVE_HEADPHONES_DONGLE) && CONFIG_EXAMPLE_COMPETITIVE_HEADPHONES_DONGLE
//	example_competitive_headphones_dongle();
#endif

#if defined(CONFIG_EXAMPLE_SECURE_BOOT) && (CONFIG_EXAMPLE_SECURE_BOOT == 1)
	example_secure_boot();
#endif

#if defined(CONFIG_EXAMPLE_TRUST_ZONE) && (CONFIG_EXAMPLE_TRUST_ZONE == 1)
	example_trust_zone();
#endif

#if defined(CONFIG_EXAMPLE_BT_MESH_DEMO) && CONFIG_EXAMPLE_BT_MESH_DEMO
	example_bt_mesh_demo();
#endif

#if ((defined CONFIG_BT_MESH_PROVISIONER_RTK_DEMO && CONFIG_BT_MESH_PROVISIONER_RTK_DEMO) || (defined CONFIG_BT_MESH_DEVICE_RTK_DEMO && CONFIG_BT_MESH_DEVICE_RTK_DEMO))
	example_bt_mesh();
#endif

#if defined(CONFIG_EXAMPLE_IPV6) && CONFIG_EXAMPLE_IPV6
	example_ipv6();
#endif

#if (CONFIG_EXAMPLE_AMAZON_FREERTOS)
	example_amazon_freertos();
#endif

#if defined(CONFIG_EXAMPLE_SW_PTA) && CONFIG_EXAMPLE_SW_PTA
	example_sw_pta();
#endif

}
