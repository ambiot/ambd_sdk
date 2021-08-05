#include "../../example_azure_iot_entry.h"
#if defined(EXAMPLE_AZURE_IOT_RTK_PNP_SAS) || defined(EXAMPLE_AZURE_IOT_RTK_PNP_X509)

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>

#include <azure/az_core.h>
#include <azure/az_iot.h>
#include <azure/core/internal/az_result_internal.h>

#include "../../example_azure_iot_common.h"

#include "../pnp_mqtt_message.h"
#include "../pnp_protocol.h"
#include "pnp_wireless.h"
#include <lwip_netconf.h>
#include <wifi/wifi_conf.h>
#include <lwip/sockets.h>
#include <lwip/raw.h>
#include <lwip/icmp.h>
#include <lwip/inet_chksum.h>
#include <dhcp/dhcps.h>
#include <sys_api.h>
#include <update.h>

// IoT Hub Device Twin Values
static az_span const twin_reported_wireless_support_property_name = AZ_SPAN_LITERAL_FROM_STR("wireless_support");
static az_span const twin_reported_specification_property_name = AZ_SPAN_LITERAL_FROM_STR("specification");
static az_span const twin_reported_specification_property_value = AZ_SPAN_LITERAL_FROM_STR("Integrated 802.11a/n Wi-Fi SoC");
static az_span const twin_desired_telemetry_enable_wifi_info_property_name = AZ_SPAN_LITERAL_FROM_STR("telemetry_enable_wifi_info");
static az_span const twin_desired_telemetry_interval_property_name = AZ_SPAN_LITERAL_FROM_STR("telemetry_interval");
static az_span const twin_response_success = AZ_SPAN_LITERAL_FROM_STR("success");
static az_span const twin_response_failed = AZ_SPAN_LITERAL_FROM_STR("failed");
static az_span const component_specifier_name = AZ_SPAN_LITERAL_FROM_STR("__t");
static az_span const component_specifier_value = AZ_SPAN_LITERAL_FROM_STR("c");

// IoT Hub Commands Values
static az_span const command_wifi_connect_name = AZ_SPAN_LITERAL_FROM_STR("wifi_connect");
static az_span const command_wifi_connect_ssid_name = AZ_SPAN_LITERAL_FROM_STR("ssid");
static az_span const command_wifi_connect_passphrase_name = AZ_SPAN_LITERAL_FROM_STR("passphrase");

static az_span const command_wifi_scan_name = AZ_SPAN_LITERAL_FROM_STR("wifi_scan");
static az_span const command_wifi_scan_scan_info_idx_name = AZ_SPAN_LITERAL_FROM_STR("idx");
static az_span const command_wifi_scan_scan_info_bss_type_name = AZ_SPAN_LITERAL_FROM_STR("bss_type");
static az_span const command_wifi_scan_scan_info_mac_name = AZ_SPAN_LITERAL_FROM_STR("mac");
static az_span const command_wifi_scan_scan_info_signal_strength_name = AZ_SPAN_LITERAL_FROM_STR("signal_strength");
static az_span const command_wifi_scan_scan_info_channel_name = AZ_SPAN_LITERAL_FROM_STR("channel");
static az_span const command_wifi_scan_scan_info_wps_type_name = AZ_SPAN_LITERAL_FROM_STR("wps_type");
static az_span const command_wifi_scan_scan_info_security_name = AZ_SPAN_LITERAL_FROM_STR("security");
static az_span const command_wifi_scan_scan_info_ssid_name = AZ_SPAN_LITERAL_FROM_STR("ssid");

static az_span const command_ota_name = AZ_SPAN_LITERAL_FROM_STR("ota");
static az_span const command_ota_ip_address_name = AZ_SPAN_LITERAL_FROM_STR("ip_address");
static az_span const command_ota_port_name = AZ_SPAN_LITERAL_FROM_STR("port");

static az_span const command_ping_name = AZ_SPAN_LITERAL_FROM_STR("ping");
static az_span const command_ping_host_address_name = AZ_SPAN_LITERAL_FROM_STR("host_address");
static az_span const command_ping_number_name = AZ_SPAN_LITERAL_FROM_STR("number");
static az_span const command_ping_buffer_size_name = AZ_SPAN_LITERAL_FROM_STR("buffer_size");
static az_span const command_ping_info_name = AZ_SPAN_LITERAL_FROM_STR("info");
static az_span const command_ping_content_name = AZ_SPAN_LITERAL_FROM_STR("content");
static az_span const command_ping_result_name = AZ_SPAN_LITERAL_FROM_STR("result");

static az_span const command_empty_response_payload = AZ_SPAN_LITERAL_FROM_STR("{}");

// IoT Hub Telemetry Values
static az_span const telemetry_wifi_info_name = AZ_SPAN_LITERAL_FROM_STR("wifi_info");
static az_span const telemetry_wifi_info_sta_mode_setting_name = AZ_SPAN_LITERAL_FROM_STR("sta_mode_setting");
static az_span const telemetry_wifi_info_sta_mode_setting_ssid_name = AZ_SPAN_LITERAL_FROM_STR("ssid");
static az_span const telemetry_wifi_info_sta_mode_setting_channel_name = AZ_SPAN_LITERAL_FROM_STR("channel");
static az_span const telemetry_wifi_info_sta_mode_setting_security_name = AZ_SPAN_LITERAL_FROM_STR("security");
static az_span const telemetry_wifi_info_sta_mode_setting_password_name = AZ_SPAN_LITERAL_FROM_STR("password");
static az_span const telemetry_wifi_info_sta_interface_name = AZ_SPAN_LITERAL_FROM_STR("sta_interface");
static az_span const telemetry_wifi_info_sta_interface_mac_name = AZ_SPAN_LITERAL_FROM_STR("mac");
static az_span const telemetry_wifi_info_sta_interface_ip_name = AZ_SPAN_LITERAL_FROM_STR("ip");
static az_span const telemetry_wifi_info_sta_interface_gw_name = AZ_SPAN_LITERAL_FROM_STR("gw");
static az_span const telemetry_wifi_info_sta_interface_msk_name = AZ_SPAN_LITERAL_FROM_STR("msk");

#if CONFIG_LWIP_LAYER
extern struct netif xnetif[NET_IF_NUM]; 
#endif
static char command_property_scratch_buffer[64];
static pnp_scan_info* scan_info_addr;
static bool is_scan_done;

static char wifi_info_ssid[33];
static char wifi_info_security[10];
static char wifi_info_password[65];
static char wifi_info_mac[20];
static char wifi_info_ip[20];
static char wifi_info_gw[20];
static char wifi_info_msk[20];
static char wifi_connect_ssid[33];
static char wifi_connect_passphrase[65];
static char wifi_scan_bss_type[PNP_WIRELESS_MAX_SCAN_AP][5];
static char wifi_scan_mac[PNP_WIRELESS_MAX_SCAN_AP][20];
static char wifi_scan_wps_type[PNP_WIRELESS_MAX_SCAN_AP][20];
static char wifi_scan_security[PNP_WIRELESS_MAX_SCAN_AP][20];
static char wifi_scan_ssid[PNP_WIRELESS_MAX_SCAN_AP][33];
static char ping_host[20];
static int32_t ping_seq;
static char ping_info[50];
static char ping_content[PNP_WIRELESS_MAX_PING_TIME][64];
static char ping_result[75];

static az_result append_bool_callback(az_json_writer* jw, void* value)
{
	return az_json_writer_append_bool(jw, *(bool*)value);
}

static az_result append_string_callback(az_json_writer* jw, void* value)
{
	return az_json_writer_append_string(jw, *(az_span*)value);
}

static az_result append_int32_callback(az_json_writer* jw, void* value)
{
	return az_json_writer_append_int32(jw, *(int32_t*)value);
}

static az_result append_json_token_callback(az_json_writer* jw, void* value)
{
	char const* const log = "Failed to append json token callback";

	az_json_token value_token = *(az_json_token*)value;

	int32_t value_as_int32;
	bool value_as_bool;
	int32_t string_length;

	switch (value_token.kind)
	{
		case AZ_JSON_TOKEN_TRUE:
		case AZ_JSON_TOKEN_FALSE:
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_boolean(&value_token, &value_as_bool), log);
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_bool(jw, value_as_bool), log);
			break;
		case AZ_JSON_TOKEN_NUMBER:
			//Expect int32 here
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&value_token, &value_as_int32), log);
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_int32(jw, value_as_int32), log);
			break;
		case AZ_JSON_TOKEN_STRING:
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(
				az_json_token_get_string(
					&value_token,
					command_property_scratch_buffer,
					sizeof(command_property_scratch_buffer),
					&string_length),
				log);
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(
				az_json_writer_append_string(jw, az_span_create((uint8_t*)command_property_scratch_buffer, string_length)),
				log);
			break;
		default:
			return AZ_ERROR_ITEM_NOT_FOUND;
	}

	return AZ_OK;
}

az_result pnp_wireless_init(
    pnp_wireless_component* out_wireless_component,
    az_span component_name)
{
	if (out_wireless_component == NULL)
	{
		return AZ_ERROR_ARG;
	}
	
	//initialize gpio_component
	memset(out_wireless_component, 0, sizeof(pnp_wireless_component));
	
	out_wireless_component->component_name = component_name;
	out_wireless_component->wireless_support = true;
	out_wireless_component->specification = twin_reported_specification_property_value;
	out_wireless_component->telemetry_enable_wifi_info = true;
	out_wireless_component->telemetry_interval = 1;
	out_wireless_component->telemetry_counter = 0;
	return AZ_OK;
}

// Get STA mode information only
static void get_wifi_information(pnp_wireless_component* wireless_component){
	int32_t i;

	int32_t wifi_info_channel;
	memset(wifi_info_ssid, 0, 33);
	memset(wifi_info_security, 0, 10);
	memset(wifi_info_password, 0, 65);
	memset(wifi_info_mac, 0, 20);
	memset(wifi_info_ip, 0, 20);
	memset(wifi_info_gw, 0, 20);
	memset(wifi_info_msk, 0, 20);

#if CONFIG_LWIP_LAYER
	u8 *mac = LwIP_GetMAC(&xnetif[0]);
	u8 *ip = LwIP_GetIP(&xnetif[0]);
	u8 *gw = LwIP_GetGW(&xnetif[0]);
	u8 *msk = LwIP_GetMASK(&xnetif[0]);
#endif
	u8 *ifname[2] = {(u8*)WLAN0_NAME,(u8*)WLAN1_NAME};
	rtw_wifi_setting_t setting;
		
	for(i=0;i<NET_IF_NUM;i++){
		if(rltk_wlan_running(i)){
#if CONFIG_LWIP_LAYER
			mac = LwIP_GetMAC(&xnetif[i]);
			ip = LwIP_GetIP(&xnetif[i]);
			gw = LwIP_GetGW(&xnetif[i]);
			msk = LwIP_GetMASK(&xnetif[i]);
#endif
			wifi_get_setting((const char*)ifname[i],&setting);
			
			if(setting.mode != RTW_MODE_STA) continue;
			
			strcpy(wifi_info_ssid, (char*)setting.ssid);

			wifi_info_channel = setting.channel;

			switch(setting.security_type) {
				case RTW_SECURITY_OPEN:
					strcpy(wifi_info_security, "OPEN");
					break;
				case RTW_SECURITY_WEP_PSK:
					strcpy(wifi_info_security, "WEP");
					break;
				case RTW_SECURITY_WPA_TKIP_PSK:
					strcpy(wifi_info_security, "TKIP");
					break;
				case RTW_SECURITY_WPA2_AES_PSK:
					strcpy(wifi_info_security, "AES");
					break;
				default:
					strcpy(wifi_info_security, "UNKNOWN");
			}
			
			strcpy(wifi_info_password, (char*)setting.password);
#if CONFIG_LWIP_LAYER
			sprintf(wifi_info_mac, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
			sprintf(wifi_info_ip, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
			sprintf(wifi_info_gw, "%d.%d.%d.%d", gw[0], gw[1], gw[2], gw[3]);
			sprintf(wifi_info_msk, "%d.%d.%d.%d", msk[0], msk[1], msk[2], msk[3]);
#endif
			wireless_component->sta_mode_setting.ssid = az_span_create((uint8_t*)wifi_info_ssid, strlen(wifi_info_ssid));
			wireless_component->sta_mode_setting.channel = wifi_info_channel;
			wireless_component->sta_mode_setting.security = az_span_create((uint8_t*)wifi_info_security, strlen(wifi_info_security));
			wireless_component->sta_mode_setting.password = az_span_create((uint8_t*)wifi_info_password, strlen(wifi_info_password));

			wireless_component->sta_interface.mac = az_span_create((uint8_t*)wifi_info_mac, strlen(wifi_info_mac));
			wireless_component->sta_interface.ip = az_span_create((uint8_t*)wifi_info_ip, strlen(wifi_info_ip));
			wireless_component->sta_interface.gw = az_span_create((uint8_t*)wifi_info_gw, strlen(wifi_info_gw));
			wireless_component->sta_interface.msk = az_span_create((uint8_t*)wifi_info_msk, strlen(wifi_info_msk));
		}
	}
		
}

void pnp_wireless_build_telemetry_message(
    pnp_wireless_component* wireless_component,
    az_span payload,
    az_span* out_payload)
{
	
	char const* const log = "Failed to build telemetry message payload for wireless";
	az_json_writer jw;
	
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_init(&jw, payload, NULL), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(&jw), log);

	if(wireless_component->telemetry_enable_wifi_info){

		get_wifi_information(wireless_component);
		
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, telemetry_wifi_info_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(&jw), log);
					
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, telemetry_wifi_info_sta_mode_setting_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(&jw), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, telemetry_wifi_info_sta_mode_setting_ssid_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->sta_mode_setting.ssid), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, telemetry_wifi_info_sta_mode_setting_channel_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_int32(&jw, wireless_component->sta_mode_setting.channel), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, telemetry_wifi_info_sta_mode_setting_security_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->sta_mode_setting.security), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, telemetry_wifi_info_sta_mode_setting_password_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->sta_mode_setting.password), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(&jw), log);

		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, telemetry_wifi_info_sta_interface_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(&jw), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, telemetry_wifi_info_sta_interface_mac_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->sta_interface.mac), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, telemetry_wifi_info_sta_interface_ip_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->sta_interface.ip), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, telemetry_wifi_info_sta_interface_gw_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->sta_interface.gw), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, telemetry_wifi_info_sta_interface_msk_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->sta_interface.msk), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(&jw), log);

		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(&jw), log);
	}
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(&jw), log);
	
	*out_payload = az_json_writer_get_bytes_used_in_destination(&jw);

}


void pnp_wireless_append_all_reported_property(
    pnp_wireless_component* wireless_component,
    az_json_writer* jw)
{
	char const* const log = "Failed to build reported property payload for wireless";
	
	if (az_span_size(wireless_component->component_name) != 0)
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, wireless_component->component_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(jw), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, component_specifier_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, component_specifier_value), log);
	}
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_wireless_support_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_bool(jw, wireless_component->wireless_support), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_specification_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, wireless_component->specification), log);
	if (az_span_size(wireless_component->component_name) != 0)
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(jw), log);
	}
	
}

void pnp_wireless_build_reported_property(
    pnp_wireless_component* wireless_component,
    az_span payload,
    az_span* out_payload,
    az_span property_name)
{
	if(az_span_is_content_equal(property_name, twin_reported_wireless_support_property_name))
	{
		pnp_build_reported_property(
			payload,
			wireless_component->component_name,
			twin_reported_wireless_support_property_name,
			append_bool_callback,
			&wireless_component->wireless_support,
			out_payload);

	}
	else if(az_span_is_content_equal(property_name, twin_reported_specification_property_name))
	{
		pnp_build_reported_property(
			payload,
			wireless_component->component_name,
			twin_reported_specification_property_name,
			append_string_callback,
			&wireless_component->specification,
			out_payload);

	}
	else
	{
		IOT_SAMPLE_LOG_ERROR("Failed to build report property: %s.", az_span_ptr(property_name));
	}
}

void pnp_wireless_build_error_reported_property_with_status(
    az_span component_name,
    az_span property_name,
    az_json_reader* property_value,
    az_iot_status status,
    int32_t version,
    az_span payload,
    az_span* out_payload)
{
	pnp_build_reported_property_with_status(
		payload,
		component_name,
		property_name,
		append_json_token_callback,
		(void*)property_value,
		(int32_t)status,
		version,
		twin_response_failed,
		out_payload);
}


bool pnp_wireless_process_property_update(
    pnp_wireless_component* ref_wireless_component,
    az_json_token const* property_name,
    az_json_reader const* property_value,
    int32_t version,
    az_span payload,
    az_span* out_payload)
{
	char const* const log = "Failed to process property update";

	if (az_json_token_is_text_equal(property_name, twin_desired_telemetry_enable_wifi_info_property_name))
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_boolean(&property_value->token, &ref_wireless_component->telemetry_enable_wifi_info), log);
		IOT_SAMPLE_LOG_SUCCESS("Client updated desired wireless telemetry_enable_wifi_info variables locally.");
    	IOT_SAMPLE_LOG("telemetry_enable_remain_heap: %s", ref_wireless_component->telemetry_enable_wifi_info?"true":"false");
		// Build reported property message with status.
		pnp_build_reported_property_with_status(
		   payload,
		   ref_wireless_component->component_name,
		   property_name->slice,
		   append_bool_callback,
		   (void*)&ref_wireless_component->telemetry_enable_wifi_info,
		   (int32_t)AZ_IOT_STATUS_OK,
		   version,
		   twin_response_success,
		   out_payload);
	
	}
	else if (az_json_token_is_text_equal(property_name, twin_desired_telemetry_interval_property_name))
	{
    	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&property_value->token, &ref_wireless_component->telemetry_interval), log);
		ref_wireless_component->telemetry_counter = 0;
		IOT_SAMPLE_LOG_SUCCESS("Client updated desired wireless telemetry_interval variables locally.");
    	IOT_SAMPLE_LOG("telemetry_interval: %d", ref_wireless_component->telemetry_interval);
		// Build reported property message with status.
		pnp_build_reported_property_with_status(
		   payload,
		   ref_wireless_component->component_name,
		   property_name->slice,
		   append_int32_callback,
		   (void*)&ref_wireless_component->telemetry_interval,
		   (int32_t)AZ_IOT_STATUS_OK,
		   version,
		   twin_response_success,
		   out_payload);
	}
	else
	{
		return false;
	}
	return true;

}

static void build_wifi_connect_command_response_payload(
    pnp_wireless_component* wireless_component,
    az_span payload,
    az_span* out_payload)
{
	// No response
	(void) wireless_component;
	(void) payload;
	
	*out_payload = command_empty_response_payload;
}

static void build_wifi_scan_command_response_payload(
    pnp_wireless_component* wireless_component,
    az_span payload,
    az_span* out_payload)
{
	int32_t i;
	char const* const log = "Failed to build wifi scan command response payload";

	az_json_writer jw;
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_init(&jw, payload, NULL), log);
	
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_array(&jw), log);
	for(i=0; i<PNP_WIRELESS_MAX_SCAN_AP;i++)
	{
		if(wireless_component->scan_info[i].idx == 0){
			printf("no_other ap\n");
			continue;
		}
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(&jw), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, command_wifi_scan_scan_info_idx_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_int32(&jw, wireless_component->scan_info[i].idx), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, command_wifi_scan_scan_info_bss_type_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->scan_info[i].bss_type), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, command_wifi_scan_scan_info_mac_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->scan_info[i].mac), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, command_wifi_scan_scan_info_signal_strength_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_int32(&jw, wireless_component->scan_info[i].signal_strength), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, command_wifi_scan_scan_info_channel_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_int32(&jw, wireless_component->scan_info[i].channel), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, command_wifi_scan_scan_info_wps_type_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->scan_info[i].wps_type), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, command_wifi_scan_scan_info_security_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->scan_info[i].security), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, command_wifi_scan_scan_info_ssid_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->scan_info[i].ssid), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(&jw), log);
	}
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_array(&jw), log);
	
	*out_payload = az_json_writer_get_bytes_used_in_destination(&jw);

}

static void build_ota_command_response_payload(
    pnp_wireless_component* wireless_component,
    az_span payload,
    az_span* out_payload)
{
	// No response
	(void) wireless_component;
	(void) payload;
	
	*out_payload = command_empty_response_payload;
}

static void build_ping_command_response_payload(
    pnp_wireless_component* wireless_component,
    az_span payload,
    az_span* out_payload)
{

	int32_t i;
	char const* const log = "Failed to build ping command response payload";

	az_json_writer jw;
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_init(&jw, payload, NULL), log);

	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(&jw), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, command_ping_info_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->ping_info.info), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, command_ping_content_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_array(&jw), log);
	for(i=0; i<ping_seq;i++)
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->ping_info.content[i]), log);
	}
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_array(&jw), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, command_ping_result_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, wireless_component->ping_info.result), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(&jw), log);
	
	*out_payload = az_json_writer_get_bytes_used_in_destination(&jw);

}

static void pnp_wireless_wifi_connect_thread(void* param)
{
	unsigned long tick1, tick2, tick3;
	int ret, mode;
	rtw_security_t security_type;

	int32_t ssid_len = strlen(wifi_connect_ssid);
	int32_t passphrase_len = strlen(wifi_connect_passphrase);
	
	IOT_SAMPLE_LOG_SUCCESS("Wifi Connect thread created");

	iot_sample_sleep_for_seconds(5);

	tick1 = xTaskGetTickCount();
	
	if(passphrase_len > 0)
	{
		security_type = RTW_SECURITY_WPA2_AES_PSK;
	}
	else
	{
		security_type = RTW_SECURITY_OPEN;
	}
	
	//Check if in AP mode
	wext_get_mode(WLAN0_NAME, &mode);
	if(mode == IW_MODE_MASTER) {
#if CONFIG_LWIP_LAYER
		dhcps_deinit();
#endif
				
#if (defined(CONFIG_PLATFORM_8710C)||defined(CONFIG_PLATFORM_8721D)) && (defined(CONFIG_BT) && CONFIG_BT)
		if (wifi_set_mode(RTW_MODE_STA) < 0){
			IOT_SAMPLE_LOG_ERROR("Wifi on failed");
			goto wifi_connect_error_exit;
		}
#else	
		wifi_off();
		vTaskDelay(20);
		if (wifi_on(RTW_MODE_STA) < 0){
			IOT_SAMPLE_LOG_ERROR("Wifi on failed");
			goto wifi_connect_error_exit;
		}
#endif
	}
	
	IOT_SAMPLE_LOG("Joining BSS by SSID %s...", (char*)wifi_connect_ssid);
	ret = wifi_connect((char*)wifi_connect_ssid, security_type, (char*)wifi_connect_passphrase, ssid_len, passphrase_len, -1, NULL);
	
	if(ret!= RTW_SUCCESS){
		if(ret == RTW_INVALID_KEY)
		{
			IOT_SAMPLE_LOG_ERROR("Invalid Key");
		}
		IOT_SAMPLE_LOG_ERROR("Can't connect to AP");
		goto wifi_connect_error_exit;
	}
	tick2 = xTaskGetTickCount();
	IOT_SAMPLE_LOG("Connected after %dms.", (tick2-tick1));
#if CONFIG_LWIP_LAYER
	/* Start DHCPClient */
	LwIP_DHCP(0, DHCP_START);
	tick3 = xTaskGetTickCount();
	IOT_SAMPLE_LOG("Got IP after %dms", (tick3-tick1));
#endif

	vTaskDelete(NULL);

	wifi_connect_error_exit:
		
	//if wifi connect error, reboot system to reconnect to azure iot hub with original wifi ssid.
	IOT_SAMPLE_LOG("wifi connect error, reboot system");
	sys_reset();
	
	vTaskDelete(NULL);

}


static bool invoke_wifi_connect(
    pnp_wireless_component* wireless_component,
    az_span payload,
    az_span response,
    az_span* out_response)
{
	int32_t wifi_connect_ssid_len=0;
	int32_t wifi_connect_passphrase_len=0;
	az_json_reader jr;

	memset(wifi_connect_ssid, 0, sizeof(wifi_connect_ssid));
	memset(wifi_connect_passphrase, 0, sizeof(wifi_connect_passphrase));
	
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_init(&jr, payload, NULL), "Failed to init json reader to parse wifi_connect payload");	
	
	while (az_result_succeeded(az_json_reader_next_token(&jr)) 
		&& (jr.token.kind != AZ_JSON_TOKEN_END_OBJECT))
	{
		if (az_json_token_is_text_equal(&jr.token, command_wifi_connect_ssid_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_STRING)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `ssid` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_string(&jr.token, wifi_connect_ssid, sizeof(wifi_connect_ssid), &wifi_connect_ssid_len), "Failed to get for `ssid` field in payload");
		}
		else if (az_json_token_is_text_equal(&jr.token, command_wifi_connect_passphrase_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_STRING)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `passphrase` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_string(&jr.token, wifi_connect_passphrase, sizeof(wifi_connect_passphrase), &wifi_connect_passphrase_len), "Failed to get for `passphrase` field in payload");
		}
		else
		{
			continue;
		}
	}

	if(wifi_connect_ssid_len == 0)
	{	
		IOT_SAMPLE_LOG_ERROR("Invalid SSID");
		return false;
	}

	IOT_SAMPLE_LOG_SUCCESS("Start Connecting to %s", wifi_connect_ssid);

#if defined(AZURE_PNP_CERTIFICATION_TEST) && AZURE_PNP_CERTIFICATION_TEST
		IOT_SAMPLE_LOG("For PnP Certification test, not doing wifi connection");
#else
	if(xTaskCreate(pnp_wireless_wifi_connect_thread, ((const char*)"pnp_wireless_wifi_connect_thread"), 512, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(pnp_wireless_wifi_connect_thread) failed", __FUNCTION__);
#endif


	build_wifi_connect_command_response_payload(wireless_component, response, out_response);
	
	return true;
}

static rtw_result_t app_scan_result_handler( rtw_scan_handler_result_t* malloced_scan_result )
{

	static int ApNum = 0;


	if (malloced_scan_result->scan_complete != RTW_TRUE) 
	{
		if(ApNum < PNP_WIRELESS_MAX_SCAN_AP && !is_scan_done){
			rtw_scan_result_t* record = &malloced_scan_result->ap_details;
			record->SSID.val[record->SSID.len] = 0; /* Ensure the SSID is null terminated */
			
			scan_info_addr->idx = ApNum+1;
			strcpy(wifi_scan_bss_type[ApNum], ( record->bss_type == RTW_BSS_TYPE_ADHOC ) ? "Adhoc" : "Infra"); 
			scan_info_addr->bss_type = az_span_create_from_str(wifi_scan_bss_type[ApNum]);
			sprintf(wifi_scan_mac[ApNum], MAC_FMT, MAC_ARG(record->BSSID.octet));
			scan_info_addr->mac = az_span_create_from_str(wifi_scan_mac[ApNum]);
			scan_info_addr->signal_strength = record->signal_strength;
			scan_info_addr->channel = record->channel;

			strcpy(wifi_scan_wps_type[ApNum], 
				( record->wps_type == RTW_WPS_TYPE_DEFAULT ) ? "DEFAULT" :
				( record->wps_type == RTW_WPS_TYPE_USER_SPECIFIED ) ? "USER_SPECIFIED" :
				( record->wps_type == RTW_WPS_TYPE_MACHINE_SPECIFIED ) ? "MACHINE_SPECIFIED" :
				( record->wps_type == RTW_WPS_TYPE_REKEY ) ? "REKEY" :
				( record->wps_type == RTW_WPS_TYPE_PUSHBUTTON ) ? "PUSHBUTTON" :
				( record->wps_type == RTW_WPS_TYPE_REGISTRAR_SPECIFIED ) ? "REGISTRAR_SPECIFIED" :
				( record->wps_type == RTW_WPS_TYPE_NONE ) ? "NONE" :
				( record->wps_type == RTW_WPS_TYPE_WSC ) ? "WSC" :
				"Unknown");
			scan_info_addr->wps_type = az_span_create_from_str(wifi_scan_wps_type[ApNum]);

			strcpy(wifi_scan_security[ApNum], 
				( record->security == RTW_SECURITY_OPEN ) ? "Open" :
				( record->security == RTW_SECURITY_WEP_PSK ) ? "WEP" :
				( record->security == RTW_SECURITY_WPA_TKIP_PSK ) ? "WPA TKIP" :
				( record->security == RTW_SECURITY_WPA_AES_PSK ) ? "WPA AES" :
				( record->security == RTW_SECURITY_WPA2_AES_PSK ) ? "WPA2 AES" :
				( record->security == RTW_SECURITY_WPA2_TKIP_PSK ) ? "WPA2 TKIP" :
				( record->security == RTW_SECURITY_WPA2_MIXED_PSK ) ? "WPA2 Mixed" :
#if defined(CONFIG_PLATFORM_8721D)
				( record->security == RTW_SECURITY_WPA_WPA2_TKIP_PSK) ? "WPA/WPA2 TKIP" :
				( record->security == RTW_SECURITY_WPA_WPA2_AES_PSK) ? "WPA/WPA2 AES" :
				( record->security == RTW_SECURITY_WPA_WPA2_MIXED_PSK) ? "WPA/WPA2 Mixed" :
#elif defined(CONFIG_PLATFORM_8710C)
				( record->security == RTW_SECURITY_WPA_WPA2_MIXED ) ? "WPA/WPA2 AES" :
#endif
				( record->security == RTW_SECURITY_WPA2_ENTERPRISE ) ? "WPA2 Enterprise" :
				( record->security == RTW_SECURITY_WPA_WPA2_ENTERPRISE ) ? "WPA/WPA2 Enterprise" : 
#ifdef CONFIG_SAE_SUPPORT
				( record->security == RTW_SECURITY_WPA3_AES_PSK) ? "WP3-SAE AES" :
#endif
				"Unknown"); 
			scan_info_addr->security = az_span_create_from_str(wifi_scan_security[ApNum]);
			strcpy(wifi_scan_ssid[ApNum], (char*)record->SSID.val); 
			scan_info_addr->ssid = az_span_create_from_str((char*)wifi_scan_ssid[ApNum]);

			++ApNum;
	 		scan_info_addr += 1;
		}
	}
	else
	{ 
		ApNum = 0;
		is_scan_done = true;
	}
	return RTW_SUCCESS;
}

static bool invoke_wifi_scan(
    pnp_wireless_component* wireless_component,
    az_span payload,
    az_span response,
    az_span* out_response)
{

	int32_t tmp_channel[30];
	u8 *channel_list = NULL;
	u8 *pscan_config = NULL;
	int num_channel = 0;
	int i;
	volatile int ret = RTW_SUCCESS;
	az_json_reader jr;
	int scan_check_interval;
	int scan_check_block_time;
	
	memset(&(wireless_component->scan_info[0]), 0, sizeof(pnp_scan_info) * PNP_WIRELESS_MAX_SCAN_AP);
	memset(wifi_scan_bss_type, 0, PNP_WIRELESS_MAX_SCAN_AP*5);
	memset(wifi_scan_mac, 0, PNP_WIRELESS_MAX_SCAN_AP*20);
	memset(wifi_scan_wps_type, 0, PNP_WIRELESS_MAX_SCAN_AP*20);
	memset(wifi_scan_security, 0, PNP_WIRELESS_MAX_SCAN_AP*20);
	memset(wifi_scan_ssid, 0, PNP_WIRELESS_MAX_SCAN_AP*33);
	scan_info_addr = &(wireless_component->scan_info[0]);
	is_scan_done = false;
	
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_init(&jr, payload, NULL), "Failed to init json reader to parse wifi_scan payload");	
	
	while (az_result_succeeded(az_json_reader_next_token(&jr)) 
		&& (jr.token.kind != AZ_JSON_TOKEN_END_ARRAY))
	{
		if (jr.token.kind == AZ_JSON_TOKEN_NUMBER)
		{
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&jr.token, &tmp_channel[num_channel]), "Failed to get for channel element in payload");
			if(tmp_channel[num_channel] < 0) 
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `channel` field");
				return false;
			}
			num_channel++;
		}
		else
		{
			continue;
		}
	}

	if(num_channel > 0) 
	{
		channel_list = (u8*)malloc(num_channel);
		if(!channel_list)
		{
			IOT_SAMPLE_LOG_ERROR("Can't malloc memory for channel list");
			return false;
		}
		pscan_config = (u8*)malloc(num_channel);
		if(!pscan_config)
		{
			IOT_SAMPLE_LOG_ERROR("Can't malloc memory for pscan_config");
			return false;
		}
		
		//parse command channel list
		for(i = 0; i < num_channel; i++)
		{
			*(channel_list + i) = (u8)tmp_channel[i];
			*(pscan_config + i) = PSCAN_ENABLE;
		}
		
		if((ret = wifi_set_pscan_chan(channel_list, pscan_config, num_channel)) < 0)
		{
			IOT_SAMPLE_LOG_ERROR("Wifi set partial scan channel fail");
			return false;
		}
	}
#if defined(AZURE_PNP_CERTIFICATION_TEST) && AZURE_PNP_CERTIFICATION_TEST
	IOT_SAMPLE_LOG("For PnP Certification test, not doing wifi scan");
#else
	if((ret = wifi_scan_networks(app_scan_result_handler, NULL )) != RTW_SUCCESS)
	{
		IOT_SAMPLE_LOG_ERROR("Wifi scan failed"); 
		return false;
	}
	
	// block to wait for scan result, wait for 3 second and check result for every 200ms
	scan_check_interval = 200;
	scan_check_block_time = 3000;
	while(!is_scan_done || scan_check_block_time>0)
	{
		vTaskDelay(scan_check_interval);
		scan_check_block_time-=scan_check_interval;
	}
	
	if(is_scan_done){
		IOT_SAMPLE_LOG_SUCCESS("Wifi scan Success"); 
	}
	else
	{
		IOT_SAMPLE_LOG_ERROR("Wifi scan out of time");
		return false;
	}
#endif

	if(channel_list)
		free(channel_list);
	if(pscan_config)
		free(pscan_config);

	// Build command response message.
	build_wifi_scan_command_response_payload(wireless_component, response, out_response);
	
	return true;

}

static bool invoke_ota(
    pnp_wireless_component* wireless_component,
    az_span payload,
    az_span response,
    az_span* out_response)
{
	char ip_address[20];
	int32_t port;
	int32_t ip_address_len=0;
	az_json_reader jr;
	
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_init(&jr, payload, NULL), "Failed to init json reader to parse ota payload");	
	
	while (az_result_succeeded(az_json_reader_next_token(&jr)) 
		&& (jr.token.kind != AZ_JSON_TOKEN_END_OBJECT))
	{
		if (az_json_token_is_text_equal(&jr.token, command_ota_ip_address_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_STRING)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `ip_address` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_string(&jr.token, ip_address, sizeof(ip_address), &ip_address_len), "Failed to get for `ip_address` field in payload");
		}
		else if (az_json_token_is_text_equal(&jr.token, command_ota_port_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_NUMBER)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `port` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&jr.token, &port), "Failed to get for `port` field in payload");
		}
		else
		{
			continue;
		}
	}

	if(ip_address_len <= 0 || inet_addr(ip_address) == INADDR_NONE)
	{
		IOT_SAMPLE_LOG_ERROR("Invalid Ip Address");
		return false;
	}
	
	IOT_SAMPLE_LOG_SUCCESS("Starting OTA update");

	
#if defined(AZURE_PNP_CERTIFICATION_TEST) && AZURE_PNP_CERTIFICATION_TEST
	IOT_SAMPLE_LOG("For PnP Certification test, not doing OTA");
#else
	update_ota_local(ip_address, port);
#endif
	
	// Build command response message.
	build_ota_command_response_payload(wireless_component, response, out_response);
	
	return true;

}

static void generate_ping_echo(unsigned char *buf, int size)
{
	int i;
	struct icmp_echo_hdr *pecho;

	for(i = 0; i < size; i ++) {
		buf[sizeof(struct icmp_echo_hdr) + i] = (unsigned char) i;
	}

	pecho = (struct icmp_echo_hdr *) buf;
	ICMPH_TYPE_SET(pecho, ICMP_ECHO);
	ICMPH_CODE_SET(pecho, 0);
	pecho->chksum = 0;
	pecho->id = PNP_WIRELESS_PING_ID;
	pecho->seqno = htons(++ ping_seq);

	//Checksum includes icmp header and data. Need to calculate after fill up icmp header
	pecho->chksum = inet_chksum(pecho, sizeof(struct icmp_echo_hdr) + size);
}


static bool invoke_ping(
    pnp_wireless_component* wireless_component,
    az_span payload,
    az_span response,
    az_span* out_response)
{
	
    int32_t ping_count = PNP_WIRELESS_DEFAULT_PING_TIME;
    int32_t buffer_size = PNP_WIRELESS_DEFAULT_PING_SIZE;
	memset(ping_host, 0, sizeof(ping_host));
	int32_t host_len = 0;
	int i, ping_socket;
	int ping_timeout = PNP_WIRELESS_PING_TO;
	struct sockaddr_in to_addr, from_addr;
	int from_addr_len = sizeof(struct sockaddr_in);
	int ping_size, reply_size;
	unsigned char ping_buf[PNP_WIRELESS_BUF_SIZE], reply_buf[PNP_WIRELESS_BUF_SIZE];
	unsigned int ping_time, reply_time, total_time = 0, received_count = 0;
	struct ip_hdr *iphdr;
	struct icmp_echo_hdr *pecho;
	az_json_reader jr;
	
	
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_init(&jr, payload, NULL), "Failed to init json reader to parse set_gpio payload");	
	while (az_result_succeeded(az_json_reader_next_token(&jr))
		&& jr.token.kind != AZ_JSON_TOKEN_END_OBJECT)
	{
		if (az_json_token_is_text_equal(&jr.token, command_ping_host_address_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_STRING)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `host_address` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_string(&jr.token, ping_host, sizeof(ping_host), &host_len), "Failed to get for `host_address` field in payload");
		}
		else if (az_json_token_is_text_equal(&jr.token, command_ping_number_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_NUMBER)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `number` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&jr.token, &ping_count), "Failed to get for `number` field in payload");
		}
		else if (az_json_token_is_text_equal(&jr.token, command_ping_buffer_size_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_NUMBER)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `buffer_size` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&jr.token, &buffer_size), "Failed to get for `buffer_size` field in payload");
		}
		// else ignore other tokens
	}

	if(host_len == 0 || inet_addr(ping_host) == INADDR_NONE)
	{
		IOT_SAMPLE_LOG_ERROR("Invalid hosthame");
		return false;
	}
	else if(ping_count > PNP_WIRELESS_MAX_PING_TIME)
	{
		// Avoid to exceed response timeout from server
		ping_count = PNP_WIRELESS_MAX_PING_TIME;
	}
	else if(ping_count <= 0)
	{
		ping_count = PNP_WIRELESS_DEFAULT_PING_TIME;
	}
	else if(buffer_size <= 0)
	{
		buffer_size = PNP_WIRELESS_DEFAULT_PING_SIZE;
	}


	//Ping size = icmp header(8 bytes) + data size
	ping_size = sizeof(struct icmp_echo_hdr) + buffer_size;
	
	memset(ping_info, 0, sizeof(ping_info));
	memset(ping_content, 0, PNP_WIRELESS_MAX_PING_TIME*64);
	memset(ping_result, 0, sizeof(ping_result));
	sprintf(ping_info, "PING %s %d(%d) bytes of data", ping_host, buffer_size, sizeof(struct ip_hdr) + sizeof(struct icmp_echo_hdr) + buffer_size);
	wireless_component->ping_info.info = az_span_create_from_str(ping_info);

	for(i = 0; i < ping_count; i++) {
		ping_socket = socket(AF_INET, SOCK_RAW, IP_PROTO_ICMP);
		setsockopt(ping_socket, SOL_SOCKET, SO_RCVTIMEO, &ping_timeout, sizeof(ping_timeout));
	
		to_addr.sin_len = sizeof(to_addr);
		to_addr.sin_family = AF_INET;
		to_addr.sin_addr.s_addr = inet_addr(ping_host);
	
		generate_ping_echo(ping_buf, buffer_size);
		sendto(ping_socket, ping_buf, ping_size, 0, (struct sockaddr *) &to_addr, sizeof(to_addr));
			
		ping_time = xTaskGetTickCount();
		if((reply_size = recvfrom(ping_socket, reply_buf, sizeof(reply_buf), 0, (struct sockaddr *) &from_addr, (socklen_t *) &from_addr_len))
			>= (int)(sizeof(struct ip_hdr) + sizeof(struct icmp_echo_hdr))) 
		{
	
			reply_time = xTaskGetTickCount();
			iphdr = (struct ip_hdr *)reply_buf;
			pecho = (struct icmp_echo_hdr *)(reply_buf + (IPH_HL(iphdr) * 4));
	
			if((pecho->id == PNP_WIRELESS_PING_ID) && (pecho->seqno == htons(ping_seq)))
			{
				sprintf(ping_content[ping_seq-1], "%d bytes from %s: icmp_seq=%d time=%d ms", reply_size - sizeof(struct ip_hdr), inet_ntoa(from_addr.sin_addr), htons(pecho->seqno), (reply_time - ping_time) * portTICK_RATE_MS);
				
				wireless_component->ping_info.content[ping_seq-1] = az_span_create_from_str(ping_content[ping_seq-1]);

				received_count++;
				total_time += (reply_time - ping_time) * portTICK_RATE_MS;
			}
		}
		else
		{
			sprintf(ping_content[ping_seq-1], "Request timeout for icmp_seq %d", ping_seq);
			wireless_component->ping_info.content[ping_seq-1] = az_span_create_from_str(ping_content[ping_seq-1]);
		}
		close(ping_socket);
		vTaskDelay(50); 
	}
	sprintf(ping_result, "%d packets transmitted, %d received, %d%% packet loss, average %d ms", ping_count, received_count, (ping_count-received_count)*100/ping_count, total_time/received_count);
	wireless_component->ping_info.result = az_span_create_from_str(ping_result);

	build_ping_command_response_payload(wireless_component, response, out_response);
	
	ping_seq = 0;
	
	return true;
}


bool pnp_wireless_process_command_request(
    pnp_wireless_component* wireless_component,
    az_span command_name,
    az_span command_received_payload,
    az_span payload,
    az_span* out_payload,
    az_iot_status* out_status)
{
	if (az_span_is_content_equal(command_wifi_connect_name, command_name))
	{
		// Invoke command.
		if (invoke_wifi_connect(wireless_component, command_received_payload, payload, out_payload))
		{
			*out_status = AZ_IOT_STATUS_OK;
		}
		else
		{
			*out_payload = command_empty_response_payload;
			*out_status = AZ_IOT_STATUS_BAD_REQUEST;
			IOT_SAMPLE_LOG_AZ_SPAN("Bad request when invoking command on wireless component:", command_name);
			return false;
		}
	}
	else if(az_span_is_content_equal(command_wifi_scan_name, command_name))
	{
		// Invoke command.
		if (invoke_wifi_scan(wireless_component, command_received_payload, payload, out_payload))
		{
			*out_status = AZ_IOT_STATUS_OK;
		}
		else
		{
			*out_payload = command_empty_response_payload;
			*out_status = AZ_IOT_STATUS_BAD_REQUEST;
			IOT_SAMPLE_LOG_AZ_SPAN("Bad request when invoking command on wireless component:", command_name);
			return false;
		}
	}
	else if(az_span_is_content_equal(command_ota_name, command_name))
	{
		// Invoke command.
		if (invoke_ota(wireless_component, command_received_payload, payload, out_payload))
		{
			*out_status = AZ_IOT_STATUS_OK;
		}
		else
		{
			*out_payload = command_empty_response_payload;
			*out_status = AZ_IOT_STATUS_BAD_REQUEST;
			IOT_SAMPLE_LOG_AZ_SPAN("Bad request when invoking command on wireless component:", command_name);
			return false;
		}
	}
	else if(az_span_is_content_equal(command_ping_name, command_name))
	{
		// Invoke command.
		if (invoke_ping(wireless_component, command_received_payload, payload, out_payload))
		{
			*out_status = AZ_IOT_STATUS_OK;
		}
		else
		{
			*out_payload = command_empty_response_payload;
			*out_status = AZ_IOT_STATUS_BAD_REQUEST;
			IOT_SAMPLE_LOG_AZ_SPAN("Bad request when invoking command on wireless component:", command_name);
			return false;
		}
	}
	else // Unsupported command
	{
		*out_payload = command_empty_response_payload;
		*out_status = AZ_IOT_STATUS_NOT_FOUND;
		IOT_SAMPLE_LOG_AZ_SPAN("Command not supported on wireless component:", command_name);
		return false;
	}

	return true;
}


#endif


