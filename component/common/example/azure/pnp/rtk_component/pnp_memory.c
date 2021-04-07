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
#include "pnp_memory.h"

// IoT Hub Device Twin Values
static az_span const twin_reported_total_flash_property_name = AZ_SPAN_LITERAL_FROM_STR("total_flash");
static az_span const twin_reported_total_sram_property_name = AZ_SPAN_LITERAL_FROM_STR("total_sram");
static az_span const twin_reported_total_external_ram_property_name = AZ_SPAN_LITERAL_FROM_STR("total_external_ram");
static az_span const twin_desired_telemetry_enable_remain_heap_property_name = AZ_SPAN_LITERAL_FROM_STR("telemetry_enable_remain_heap");
static az_span const twin_desired_telemetry_interval_property_name = AZ_SPAN_LITERAL_FROM_STR("telemetry_interval");
static az_span const twin_response_success = AZ_SPAN_LITERAL_FROM_STR("success");
static az_span const twin_response_failed = AZ_SPAN_LITERAL_FROM_STR("failed");
static az_span const component_specifier_name = AZ_SPAN_LITERAL_FROM_STR("__t");
static az_span const component_specifier_value = AZ_SPAN_LITERAL_FROM_STR("c");
static az_span const command_empty_response_payload = AZ_SPAN_LITERAL_FROM_STR("{}");

static char command_property_scratch_buffer[64];

// IoT Hub Telemetry Values
static az_span const telemetry_remain_heap_name = AZ_SPAN_LITERAL_FROM_STR("remain_heap");

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


az_result pnp_memory_init(
    pnp_memory_component* out_memory_component,
    az_span component_name)
{
	if (out_memory_component == NULL)
	{
		return AZ_ERROR_ARG;
	}
	
	//initialize gpio_component
	memset(out_memory_component, 0, sizeof(pnp_memory_component));
	
	out_memory_component->component_name = component_name;
	out_memory_component->total_flash = 4;
	out_memory_component->total_sram = 512;
	out_memory_component->total_external_ram = 4;
	out_memory_component->telemetry_enable_remain_heap = true;
	out_memory_component->telemetry_counter = 0;
	out_memory_component->telemetry_interval = 1;
	return AZ_OK;
}

void pnp_memory_build_telemetry_message(
    pnp_memory_component* memory_component,
    az_span payload,
    az_span* out_payload)
{
	memory_component->remain_heap = (int32_t)xPortGetFreeHeapSize();
	
	if(memory_component->telemetry_enable_remain_heap){
		pnp_build_telemetry_message(
			payload,
			telemetry_remain_heap_name ,
			append_int32_callback,
			(void*)&memory_component->remain_heap,
			out_payload);
	}
}

void pnp_memory_append_all_reported_property(
    pnp_memory_component* memory_component,
    az_json_writer* jw)
{
	char const* const log = "Failed to build reported property payload for memory";
	
	if (az_span_size(memory_component->component_name) != 0)
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, memory_component->component_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(jw), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, component_specifier_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, component_specifier_value), log);
	}
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_total_flash_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_int32(jw, memory_component->total_flash), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_total_sram_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_int32(jw, memory_component->total_sram), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_total_external_ram_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_int32(jw, memory_component->total_external_ram), log);
	if (az_span_size(memory_component->component_name) != 0)
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(jw), log);
	}
	
}

void pnp_memory_build_reported_property(
    pnp_memory_component* memory_component,
    az_span payload,
    az_span* out_payload,
    az_span property_name)
{
	if(az_span_is_content_equal(property_name, twin_reported_total_flash_property_name))
	{
		pnp_build_reported_property(
			payload,
			memory_component->component_name,
			twin_reported_total_flash_property_name,
			append_int32_callback,
			&memory_component->total_flash,
			out_payload);

	}
	else if(az_span_is_content_equal(property_name, twin_reported_total_sram_property_name))
	{
		pnp_build_reported_property(
			payload,
			memory_component->component_name,
			twin_reported_total_sram_property_name,
			append_int32_callback,
			&memory_component->total_sram,
			out_payload);
	}
	else if(az_span_is_content_equal(property_name, twin_reported_total_external_ram_property_name))
	{
		pnp_build_reported_property(
			payload,
			memory_component->component_name,
			twin_reported_total_external_ram_property_name,
			append_int32_callback,
			&memory_component->total_external_ram,
			out_payload);
	}
	else
	{
		IOT_SAMPLE_LOG_ERROR("Failed to build report property: %s.", az_span_ptr(property_name));
	}

}


void pnp_memory_build_error_reported_property_with_status(
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

bool pnp_memory_process_property_update(
    pnp_memory_component* ref_memory_component,
    az_json_token const* property_name,
    az_json_reader const* property_value,
    int32_t version,
    az_span payload,
    az_span* out_payload)
{

	char const* const log = "Failed to process property update";

	if (az_json_token_is_text_equal(property_name, twin_desired_telemetry_enable_remain_heap_property_name))
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_boolean(&property_value->token, &ref_memory_component->telemetry_enable_remain_heap), log);
		IOT_SAMPLE_LOG_SUCCESS("Client updated desired memory telemetry_enable_remain_heap variables locally.");
    	IOT_SAMPLE_LOG("telemetry_enable_remain_heap: %s", ref_memory_component->telemetry_enable_remain_heap?"true":"false");
		// Build reported property message with status.
		pnp_build_reported_property_with_status(
		   payload,
		   ref_memory_component->component_name,
		   property_name->slice,
		   append_bool_callback,
		   (void*)&ref_memory_component->telemetry_enable_remain_heap,
		   (int32_t)AZ_IOT_STATUS_OK,
		   version,
		   twin_response_success,
		   out_payload);
	
	}
	else if (az_json_token_is_text_equal(property_name, twin_desired_telemetry_interval_property_name))
	{
    	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&property_value->token, &ref_memory_component->telemetry_interval), log);
		ref_memory_component->telemetry_counter = 0;
		IOT_SAMPLE_LOG_SUCCESS("Client updated desired system telemetry_interval variables locally.");
    	IOT_SAMPLE_LOG("telemetry_interval: %d", ref_memory_component->telemetry_interval);
		// Build reported property message with status.
		pnp_build_reported_property_with_status(
		   payload,
		   ref_memory_component->component_name,
		   property_name->slice,
		   append_int32_callback,
		   (void*)&ref_memory_component->telemetry_interval,
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

bool pnp_memory_process_command_request(
    pnp_memory_component* memory_component,
    az_span command_name,
    az_span command_received_payload,
    az_span payload,
    az_span* out_payload,
    az_iot_status* out_status)
{
	// No command yet
	(void) memory_component;
	(void) command_received_payload;
	(void) payload;
	
	IOT_SAMPLE_LOG_AZ_SPAN("Command not supported on led component:", command_name);

	*out_payload = command_empty_response_payload;
	*out_status = AZ_IOT_STATUS_NOT_FOUND;
	
	return false;
}

#endif

