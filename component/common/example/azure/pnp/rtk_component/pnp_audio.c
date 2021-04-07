#include "../../example_azure_iot_entry.h"
#if defined(EXAMPLE_AZURE_IOT_RTK_PNP_SAS) || defined(EXAMPLE_AZURE_IOT_RTK_PNP_X509)

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>

#include <azure/az_core.h>
#include <azure/az_iot.h>

#include "../../example_azure_iot_common.h"

#include "../pnp_mqtt_message.h"
#include "../pnp_protocol.h"
#include "pnp_audio.h"

// IoT Hub Device Twin Values
static az_span const twin_reported_audio_support_property_name = AZ_SPAN_LITERAL_FROM_STR("audio_support");
static az_span const component_specifier_name = AZ_SPAN_LITERAL_FROM_STR("__t");
static az_span const component_specifier_value = AZ_SPAN_LITERAL_FROM_STR("c");

// IoT Hub Commands Values
static az_span const command_empty_response_payload = AZ_SPAN_LITERAL_FROM_STR("{}");

static az_result append_bool_callback(az_json_writer* jw, void* value)
{
	return az_json_writer_append_bool(jw, *(bool*)value);
}

az_result pnp_audio_init(
    pnp_audio_component* out_audio_component,
    az_span component_name)
{
	if (out_audio_component == NULL)
	{
		return AZ_ERROR_ARG;
	}
	
	//initialize audio_component
	memset(out_audio_component, 0, sizeof(pnp_audio_component));
	
	out_audio_component->audio_support = true;
	out_audio_component->component_name = component_name;
	
	return AZ_OK;
}

void pnp_audio_build_telemetry_message(
    pnp_audio_component* audio_component,
    az_span payload,
    az_span* out_payload)
{
	// No telemetry yet
	(void) audio_component;
	(void) payload;
	(void) out_payload;
}

void pnp_audio_append_all_reported_property(
    pnp_audio_component* audio_component,
    az_json_writer* jw)
{
	char const* const log = "Failed to build reported property payload for audio";
	
	if (az_span_size(audio_component->component_name) != 0)
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, audio_component->component_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(jw), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, component_specifier_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, component_specifier_value), log);
	}
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_audio_support_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_bool(jw, audio_component->audio_support), log);
	if (az_span_size(audio_component->component_name) != 0)
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(jw), log);
	}
	
}

void pnp_audio_build_reported_property(
    pnp_audio_component* audio_component,
    az_span payload,
    az_span* out_payload,
    az_span property_name)
{
	if(az_span_is_content_equal(property_name, twin_reported_audio_support_property_name))
	{
		pnp_build_reported_property(
			payload,
			audio_component->component_name,
			twin_reported_audio_support_property_name,
			append_bool_callback,
			&audio_component->audio_support,
			out_payload);
	}
	else
	{
		IOT_SAMPLE_LOG_ERROR("Failed to build report property: %s.", az_span_ptr(property_name));
	}
}


void pnp_audio_build_error_reported_property_with_status(
    az_span component_name,
    az_span property_name,
    az_json_reader* property_value,
    az_iot_status status,
    int32_t version,
    az_span payload,
    az_span* out_payload)
{
	// No writable property yet
	(void) component_name;
	(void) property_name;
	(void) property_value;
	(void) status;
	(void) version;
	(void) payload;
	(void) out_payload;	
}

bool pnp_audio_process_property_update(
    pnp_audio_component* ref_audio_component,
    az_json_token const* property_name,
    az_json_reader const* property_value,
    int32_t version,
    az_span payload,
    az_span* out_payload)
{
	// No writable property yet
	(void) ref_audio_component;
	(void) property_name;
	(void) property_value;
	(void) version;
	(void) payload;
	(void) out_payload;

	return false;
}

bool pnp_audio_process_command_request(
    pnp_audio_component const* audio_component,
    az_span command_name,
    az_span command_received_payload,
    az_span payload,
    az_span* out_payload,
    az_iot_status* out_status)
{
	// No command yet
	(void) audio_component;
	(void) command_received_payload;
	(void) payload;
	
	IOT_SAMPLE_LOG_AZ_SPAN("Command not supported on audio component:", command_name);

	*out_payload = command_empty_response_payload;
	*out_status = AZ_IOT_STATUS_NOT_FOUND;
	return false;
}
#endif

