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
#include "pnp_system.h"

#include "FreeRTOS.h"
#include "task.h"

#include <sys_api.h>

#include <build_info.h>
#include <sntp/sntp.h>

// IoT Hub Device Twin Values
static az_span const twin_desired_telemetry_enable_device_runtime_property_name = AZ_SPAN_LITERAL_FROM_STR("telemetry_enable_device_runtime");
static az_span const twin_desired_telemetry_enable_cpu_usage_property_name = AZ_SPAN_LITERAL_FROM_STR("telemetry_enable_cpu_usage");
static az_span const twin_desired_telemetry_interval_property_name = AZ_SPAN_LITERAL_FROM_STR("telemetry_interval");
static az_span const twin_reported_build_info_property_name = AZ_SPAN_LITERAL_FROM_STR("build_info");
static az_span const twin_reported_build_info_fw_compile_time_property_name = AZ_SPAN_LITERAL_FROM_STR("fw_compile_time");
static az_span const twin_reported_build_info_fw_compile_by_property_name = AZ_SPAN_LITERAL_FROM_STR("fw_compile_by");
static az_span const twin_reported_build_info_fw_compile_host_property_name = AZ_SPAN_LITERAL_FROM_STR("fw_compile_host");
static az_span const twin_reported_build_info_fw_compiler_property_name = AZ_SPAN_LITERAL_FROM_STR("fw_compiler");
#if defined(CONFIG_PLATFORM_8721D)
static az_span const twin_reported_build_info_fw_compile_time_property_value = AZ_SPAN_LITERAL_FROM_STR(RTL_FW_COMPILE_TIME);
static az_span const twin_reported_build_info_fw_compile_by_property_value = AZ_SPAN_LITERAL_FROM_STR(RTL_FW_COMPILE_BY);
static az_span const twin_reported_build_info_fw_compile_host_property_value = AZ_SPAN_LITERAL_FROM_STR(RTL_FW_COMPILE_HOST);
static az_span const twin_reported_build_info_fw_compiler_property_value = AZ_SPAN_LITERAL_FROM_STR(RTL_FW_COMPILER);
#elif defined(CONFIG_PLATFORM_8710C)
static az_span const twin_reported_build_info_fw_compile_time_property_value = AZ_SPAN_LITERAL_FROM_STR(RTL_FW_COMPILE_TIME);
static az_span const twin_reported_build_info_fw_compile_by_property_value = AZ_SPAN_LITERAL_FROM_STR(RTL8710CFW_COMPILE_BY);
static az_span const twin_reported_build_info_fw_compile_host_property_value = AZ_SPAN_LITERAL_FROM_STR(RTL8710CFW_COMPILE_HOST);
static az_span const twin_reported_build_info_fw_compiler_property_value = AZ_SPAN_LITERAL_FROM_STR(RTL8710CFW_COMPILER);
#endif
static az_span const twin_reported_os_info_property_name = AZ_SPAN_LITERAL_FROM_STR("os_info");
static az_span const twin_reported_os_info_property_value = AZ_SPAN_LITERAL_FROM_STR("Freertos_v10.2.0");
static az_span const twin_reported_processor_architecture_property_name = AZ_SPAN_LITERAL_FROM_STR("processor_architecture");
static az_span const twin_reported_processor_architecture_property_value = AZ_SPAN_LITERAL_FROM_STR("32-bit 200MHz ArmRCortexR-M4 & 32-bit 20MHz ArmRCortexR-M0");
static az_span const twin_reported_trustzone_support_property_name = AZ_SPAN_LITERAL_FROM_STR("trustzone_support");
static az_span const twin_response_success = AZ_SPAN_LITERAL_FROM_STR("success");
static az_span const twin_response_failed = AZ_SPAN_LITERAL_FROM_STR("failed");
static az_span const component_specifier_name = AZ_SPAN_LITERAL_FROM_STR("__t");
static az_span const component_specifier_value = AZ_SPAN_LITERAL_FROM_STR("c");

// IoT Hub Commands Values
static az_span const command_reboot_name = AZ_SPAN_LITERAL_FROM_STR("reboot");
static az_span const command_switch_to_upgraded_image_name = AZ_SPAN_LITERAL_FROM_STR("switch_to_upgraded_image");
static az_span const command_switch_to_default_image_name = AZ_SPAN_LITERAL_FROM_STR("switch_to_default_image");
static az_span const command_empty_response_payload = AZ_SPAN_LITERAL_FROM_STR("{}");

// IoT Hub Telemetry Values
static az_span const telemetry_device_runtime_name = AZ_SPAN_LITERAL_FROM_STR("device_runtime");
static az_span const telemetry_cpu_usage_name = AZ_SPAN_LITERAL_FROM_STR("cpu_usage");

static char command_property_scratch_buffer[64];
static char const iso_spec_time_format[] = "%Y-%m-%dT%H:%M:%S%z"; // ISO8601 Time Format

static struct tm tm_start;

static az_result append_string_callback(az_json_writer* jw, void* value)
{
	return az_json_writer_append_string(jw, *(az_span*)value);
}

static az_result append_bool_callback(az_json_writer* jw, void* value)
{
	return az_json_writer_append_bool(jw, *(bool*)value);
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

az_result pnp_system_init(
    pnp_system_component* out_system_component,
    az_span component_name)
{
	if (out_system_component == NULL)
	{
		return AZ_ERROR_ARG;
	}
	
	//initialize gpio_component
	memset(out_system_component, 0, sizeof(pnp_system_component));
	
	out_system_component->component_name = component_name;
	out_system_component->build_info.build_info_fw_compile_time = twin_reported_build_info_fw_compile_time_property_value;
	out_system_component->build_info.build_info_fw_compile_by = twin_reported_build_info_fw_compile_by_property_value;
	out_system_component->build_info.build_info_fw_compile_host = twin_reported_build_info_fw_compile_host_property_value;
	out_system_component->build_info.build_info_fw_compiler = twin_reported_build_info_fw_compiler_property_value;
	out_system_component->os_info = twin_reported_os_info_property_value;
	out_system_component->processor_architecture = twin_reported_processor_architecture_property_value;
	out_system_component->trustzone_support = true;
	int timezone = 8;   // use UTC+8 timezone for example
	tm_start = sntp_gen_system_time(timezone);
	tm_start.tm_year -= 1900;
	tm_start.tm_mon -= 1;
	out_system_component->telemetry_enable_device_runtime = true;
	out_system_component->telemetry_enable_cpu_usage = true;
	out_system_component->telemetry_counter = 0;
	out_system_component->telemetry_interval = 1;
	out_system_component->reboot_delay = 0;
	
	return AZ_OK;
}

void pnp_system_build_telemetry_message(
    pnp_system_component* system_component,
    az_span payload,
    az_span* out_payload)
{
	
	char const* const log = "Failed to build telemetry message payload for system";
	az_json_writer jw;
	struct tm tm_cur;

	
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_init(&jw, payload, NULL), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(&jw), log);

	if(system_component->telemetry_enable_device_runtime){

		int timezone = 8;   // use UTC+8 timezone for example
		tm_cur = sntp_gen_system_time(timezone);
		tm_cur.tm_year -= 1900;
		tm_cur.tm_mon -= 1;
		
		time_t total_elapse_sec = mktime(&tm_cur) -  mktime(&tm_start);

		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, telemetry_device_runtime_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_int32(&jw, total_elapse_sec), log);
	}
	
	if(system_component->telemetry_enable_cpu_usage){
		
#if (configGENERATE_RUN_TIME_STATS == 1)

		vTaskGetRunTimeStats((char *)system_component->cpu_usage);
		az_span runTimeStats = az_span_create_from_str(system_component->cpu_usage);

		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, telemetry_cpu_usage_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, runTimeStats), log);
		
#else
		IOT_SAMPLE_LOG("please enable configGENERATE_RUN_TIME_STATS to get cpu status");
#endif

	}
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(&jw), log);
	
	*out_payload = az_json_writer_get_bytes_used_in_destination(&jw);

}

void pnp_system_append_all_reported_property(
    pnp_system_component* system_component,
    az_json_writer* jw)
{
	char const* const log = "Failed to build reported property payload for system";
	if (az_span_size(system_component->component_name) != 0)
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, system_component->component_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(jw), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, component_specifier_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, component_specifier_value), log);
	}
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_build_info_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(jw), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_build_info_fw_compile_time_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, system_component->build_info.build_info_fw_compile_time), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_build_info_fw_compile_by_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, system_component->build_info.build_info_fw_compile_by), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_build_info_fw_compile_host_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, system_component->build_info.build_info_fw_compile_host), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_build_info_fw_compiler_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, system_component->build_info.build_info_fw_compiler), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(jw), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_os_info_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, system_component->os_info), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_processor_architecture_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, system_component->processor_architecture), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_trustzone_support_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_bool(jw, system_component->trustzone_support), log);
	if (az_span_size(system_component->component_name) != 0)
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(jw), log);
	}
	
}

void pnp_system_build_reported_property(
    pnp_system_component* system_component,
    az_span payload,
    az_span* out_payload,
    az_span property_name)
{
	if(az_span_is_content_equal(property_name, twin_reported_build_info_property_name))
	{
		pnp_build_reported_property(
			payload,
			system_component->component_name,
			twin_reported_build_info_property_name,
			append_string_callback,
			&system_component->build_info,
			out_payload);

	}
	else if(az_span_is_content_equal(property_name, twin_reported_os_info_property_name))
	{
		pnp_build_reported_property(
			payload,
			system_component->component_name,
			twin_reported_os_info_property_name,
			append_string_callback,
			&system_component->os_info,
			out_payload);
	}
	else if(az_span_is_content_equal(property_name, twin_reported_processor_architecture_property_name))
	{
		pnp_build_reported_property(
			payload,
			system_component->component_name,
			twin_reported_processor_architecture_property_name,
			append_string_callback,
			&system_component->processor_architecture,
			out_payload);
	}
	else if(az_span_is_content_equal(property_name, twin_reported_trustzone_support_property_name))
	{
		pnp_build_reported_property(
			payload,
			system_component->component_name,
			twin_reported_trustzone_support_property_name,
			append_bool_callback,
			&system_component->trustzone_support,
			out_payload);
	}
	else
	{
		IOT_SAMPLE_LOG_ERROR("Failed to build report property: %s.", az_span_ptr(property_name));
	}

}

void pnp_system_build_error_reported_property_with_status(
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

bool pnp_system_process_property_update(
    pnp_system_component* ref_system_component,
    az_json_token const* property_name,
    az_json_reader const* property_value,
    int32_t version,
    az_span payload,
    az_span* out_payload)
{

	char const* const log = "Failed to process property update";

	if (az_json_token_is_text_equal(property_name, twin_desired_telemetry_enable_device_runtime_property_name))
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_boolean(&property_value->token, &ref_system_component->telemetry_enable_device_runtime), log);
		IOT_SAMPLE_LOG_SUCCESS("Client updated desired system telemetry_enable_device_runtime variables locally.");
    	IOT_SAMPLE_LOG("telemetry_enable_device_runtime: %s", ref_system_component->telemetry_enable_device_runtime?"true":"false");
		// Build reported property message with status.
		pnp_build_reported_property_with_status(
		   payload,
		   ref_system_component->component_name,
		   property_name->slice,
		   append_bool_callback,
		   (void*)&ref_system_component->telemetry_enable_device_runtime,
		   (int32_t)AZ_IOT_STATUS_OK,
		   version,
		   twin_response_success,
		   out_payload);
	
	}
	else if (az_json_token_is_text_equal(property_name, twin_desired_telemetry_enable_cpu_usage_property_name))
	{
    	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_boolean(&property_value->token, &ref_system_component->telemetry_enable_cpu_usage), log);
		IOT_SAMPLE_LOG_SUCCESS("Client updated desired system telemetry_enable_cpu_usage variables locally.");
    	IOT_SAMPLE_LOG("telemetry_enable_cpu_usage: %s", ref_system_component->telemetry_enable_cpu_usage?"true":"false");
		// Build reported property message with status.
		pnp_build_reported_property_with_status(
		   payload,
		   ref_system_component->component_name,
		   property_name->slice,
		   append_bool_callback,
		   (void*)&ref_system_component->telemetry_enable_cpu_usage,
		   (int32_t)AZ_IOT_STATUS_OK,
		   version,
		   twin_response_success,
		   out_payload);
	}
	else if (az_json_token_is_text_equal(property_name, twin_desired_telemetry_interval_property_name))
	{
    	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&property_value->token, &ref_system_component->telemetry_interval), log);
		ref_system_component->telemetry_counter = 0;
		IOT_SAMPLE_LOG_SUCCESS("Client updated desired system telemetry_interval variables locally.");
    	IOT_SAMPLE_LOG("telemetry_interval: %d", ref_system_component->telemetry_interval);
		// Build reported property message with status.
		pnp_build_reported_property_with_status(
		   payload,
		   ref_system_component->component_name,
		   property_name->slice,
		   append_int32_callback,
		   (void*)&ref_system_component->telemetry_interval,
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


static void pnp_system_reboot_thread(void* param)
{
	pnp_system_component* system_component = (pnp_system_component*) param;
	
	IOT_SAMPLE_LOG_SUCCESS("Reboot thread created");

	iot_sample_sleep_for_seconds(system_component->reboot_delay);
	
	sys_reset();
	
	vTaskDelete(NULL);
}

static void build_switch_image_command_response_payload(
    pnp_system_component* system_component,
    az_span payload,
    az_span* out_payload)
{
	// No response
	(void) system_component;
	(void) payload;
	
	*out_payload = command_empty_response_payload;
}


static void build_reboot_command_response_payload(
    pnp_system_component* system_component,
    az_span scheduleTime,
    az_span payload,
    az_span* out_payload)
{
	char const* const log = "Failed to build reboot command response payload";

	az_json_writer jw;
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_init(&jw, payload, NULL), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(&jw, scheduleTime), log);

	*out_payload = az_json_writer_get_bytes_used_in_destination(&jw);
}

static bool invoke_switch_to_upgraded_image(
    pnp_system_component* system_component,
    az_span payload,
    az_span response,
    az_span* out_response)
{
#if defined(AZURE_PNP_CERTIFICATION_TEST) && AZURE_PNP_CERTIFICATION_TEST

	IOT_SAMPLE_LOG("For PnP Certification test, not switching firmware");

	// Build command response message.
	build_switch_image_command_response_payload(system_component, response, out_response);
	return true;
	
#else

#if	CONFIG_OTA_UPDATE
	sys_recover_ota_signature();

	IOT_SAMPLE_LOG("switched to upgraded image");

	//reboot after 5 seconds
	system_component->reboot_delay = 5;
		
	if(xTaskCreate(pnp_system_reboot_thread, ((const char*)"pnp_system_reboot_thread"), 256, system_component, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(pnp_system_reboot_thread) failed", __FUNCTION__);

#else
	IOT_SAMPLE_LOG_ERROR("please enable CONFIG_OTA_UPDATE to enbable firmware switch.");
	return false;
#endif

	// Build command response message.
	build_switch_image_command_response_payload(system_component, response, out_response);
	return true;
	
#endif
}

static bool invoke_switch_to_default_image(
    pnp_system_component* system_component,
    az_span payload,
    az_span response,
    az_span* out_response)
{

#if defined(AZURE_PNP_CERTIFICATION_TEST) && AZURE_PNP_CERTIFICATION_TEST

	IOT_SAMPLE_LOG("For PnP Certification test, not switching firmware");

	// Build command response message.
	build_switch_image_command_response_payload(system_component, response, out_response);
	return true;

#else

#if	CONFIG_OTA_UPDATE
	sys_clear_ota_signature();
	
	IOT_SAMPLE_LOG("switched to default image");

	//reboot after 5 seconds
	system_component->reboot_delay = 5;
	
	if(xTaskCreate(pnp_system_reboot_thread, ((const char*)"pnp_system_reboot_thread"), 256, system_component, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(pnp_system_reboot_thread) failed", __FUNCTION__);
	
#else
	IOT_SAMPLE_LOG_ERROR("please enable CONFIG_OTA_UPDATE to enbable firmware switch.");
	return false;
#endif

	// Build command response message.
	build_switch_image_command_response_payload(system_component, response, out_response);
	return true;
	
#endif
}


static bool invoke_reboot(
    pnp_system_component* system_component,
    az_span payload,
    az_span response,
    az_span* out_response)
{
	char time_buf[64];
	int32_t time_buflen;
	int32_t i, str_counter;
	char slice_buf[5];
	az_span rebootTime_span;
	struct tm rebootTime;
	az_json_reader jr;
	
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_init(&jr, payload, NULL), "Failed to init json reader to parse set_gpio payload");	
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_next_token(&jr), "Failed to parse for command rebootTime field");
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(
			az_json_token_get_string(
				&jr.token,
				time_buf,
				sizeof(time_buf),
				&time_buflen),
			"Failed to get for `rebootTime` field in payload");


	// we dont have strptime(), so parse manually.  Support only ISO8601 Time Format. "%Y-%m-%dT%H:%M:%S%z"
	for(i=0, str_counter=0; i<4; i++, str_counter++) slice_buf[i] = time_buf[str_counter];
	slice_buf[i] = '\0';
	rebootTime.tm_year = atoi(slice_buf) - 1900;
	str_counter++; // skip "-"

	for(i=0; i<2; i++, str_counter++) slice_buf[i] = time_buf[str_counter];
	slice_buf[i] = '\0';
	rebootTime.tm_mon = atoi(slice_buf) - 1;
	str_counter++; // skip "-"

	for(i=0; i<2; i++, str_counter++) slice_buf[i] = time_buf[str_counter];
	slice_buf[i] = '\0';
	rebootTime.tm_mday = atoi(slice_buf);
	str_counter++; // skip "T"

	for(i=0; i<2; i++, str_counter++) slice_buf[i] = time_buf[str_counter];
	slice_buf[i] = '\0';
	rebootTime.tm_hour = atoi(slice_buf);
	str_counter++; // skip ":"

	for(i=0; i<2; i++, str_counter++) slice_buf[i] = time_buf[str_counter];
	slice_buf[i] = '\0';
	rebootTime.tm_min = atoi(slice_buf);
	str_counter++; // skip ":"

	for(i=0; i<2; i++, str_counter++) slice_buf[i] = time_buf[str_counter];
	slice_buf[i] = '\0';
	rebootTime.tm_sec = atoi(slice_buf);
	rebootTime.tm_isdst = -1; //fix mktime parse wrong time

	// Get the current time as a string.
	int timezone = 8;	// use UTC+8 timezone for example
	struct tm tm_now = sntp_gen_system_time(timezone);
	tm_now.tm_year -= 1900;
	tm_now.tm_mon -= 1;
	tm_now.tm_isdst = -1; //fix mktime parse wrong time
	
	// Since received time doesn't have timezone swift (UTC), increment the timezone here.
    rebootTime.tm_hour += timezone;
    mktime(&rebootTime); //this function normalize the time overflow
    
	char tm_cur_buf[32], tm_reboot_buf[32];
	int32_t tm_cur_buflen, tm_reboot_buflen;

	tm_cur_buflen = strftime(tm_cur_buf, sizeof(tm_cur_buf), iso_spec_time_format, &tm_now);
	tm_reboot_buflen = strftime(tm_reboot_buf, sizeof(tm_reboot_buf), iso_spec_time_format, &rebootTime);

	// Reboot delay (sec)
	system_component->reboot_delay = mktime(&rebootTime) - mktime(&tm_now);

	IOT_SAMPLE_LOG("Current time: %.*s", tm_cur_buflen, tm_cur_buf);
	

	if(system_component->reboot_delay < 5) // reboot immidiately
	{
		// Leave some time to send the command response
		system_component->reboot_delay = 5;
		rebootTime_span = az_span_create((uint8_t*)tm_cur_buf, tm_cur_buflen);
		IOT_SAMPLE_LOG("Reboot immidiately");
	}
	else
	{
		rebootTime_span = az_span_create((uint8_t*)tm_reboot_buf, tm_reboot_buflen);
		IOT_SAMPLE_LOG("Reboot time: %.*s.", tm_reboot_buflen, tm_reboot_buf);
	}

#if defined(AZURE_PNP_CERTIFICATION_TEST) && AZURE_PNP_CERTIFICATION_TEST
	IOT_SAMPLE_LOG("For PnP Certification test, reboot after 5 mins");
	system_component->reboot_delay = 300000;
#endif

	if(xTaskCreate(pnp_system_reboot_thread, ((const char*)"pnp_system_reboot_thread"), 256, system_component, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(pnp_system_reboot_thread) failed", __FUNCTION__);


	// Build command response message. It should be success if reach here.
	build_reboot_command_response_payload(system_component, rebootTime_span, response, out_response);

	return true;
}


bool pnp_system_process_command_request(
    pnp_system_component* system_component,
    az_span command_name,
    az_span command_received_payload,
    az_span payload,
    az_span* out_payload,
    az_iot_status* out_status)
{
	if (az_span_is_content_equal(command_reboot_name, command_name))
	{
		// Invoke command.
		if (invoke_reboot(system_component, command_received_payload, payload, out_payload))
		{
			*out_status = AZ_IOT_STATUS_OK;
		}
		else
		{
			*out_payload = command_empty_response_payload;
			*out_status = AZ_IOT_STATUS_BAD_REQUEST;
			IOT_SAMPLE_LOG_AZ_SPAN("Bad request when invoking command on system component:", command_name);
			return false;
		}
	}
	else if (az_span_is_content_equal(command_switch_to_upgraded_image_name, command_name))
	{
		// Invoke command.
		if (invoke_switch_to_upgraded_image(system_component, command_received_payload, payload, out_payload))
		{
			*out_status = AZ_IOT_STATUS_OK;
		}
		else
		{
			*out_payload = command_empty_response_payload;
			*out_status = AZ_IOT_STATUS_BAD_REQUEST;
			IOT_SAMPLE_LOG_AZ_SPAN("Bad request when invoking command on system component:", command_name);
			return false;
		}
	}
	else if (az_span_is_content_equal(command_switch_to_default_image_name, command_name))
	{
		// Invoke command.
		if (invoke_switch_to_default_image(system_component, command_received_payload, payload, out_payload))
		{
			*out_status = AZ_IOT_STATUS_OK;
		}
		else
		{
			*out_payload = command_empty_response_payload;
			*out_status = AZ_IOT_STATUS_BAD_REQUEST;
			IOT_SAMPLE_LOG_AZ_SPAN("Bad request when invoking command on system component:", command_name);
			return false;
		}
	}
	else // Unsupported command
	{
		*out_payload = command_empty_response_payload;
		*out_status = AZ_IOT_STATUS_NOT_FOUND;
		IOT_SAMPLE_LOG_AZ_SPAN("Command not supported on system component:", command_name);
		return false;
	}

	return true;
}


#endif

