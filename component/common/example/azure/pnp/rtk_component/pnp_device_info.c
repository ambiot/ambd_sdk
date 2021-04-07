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
#include "pnp_device_info.h"

// IoT Hub Device Twin Values
static az_span const twin_reported_manufacturer_property_name = AZ_SPAN_LITERAL_FROM_STR("manufacturer");
static az_span const twin_reported_manufacturer_property_value = AZ_SPAN_LITERAL_FROM_STR("Realtek");
static az_span const twin_reported_model_property_name = AZ_SPAN_LITERAL_FROM_STR("model");
#if defined(CONFIG_PLATFORM_8721D)
static az_span const twin_reported_model_property_value = AZ_SPAN_LITERAL_FROM_STR("RTL8721D");
#elif defined(CONFIG_PLATFORM_8710C)
static az_span const twin_reported_model_property_value = AZ_SPAN_LITERAL_FROM_STR("RTL8720C");
#endif
static az_span const twin_reported_fw_version_property_name = AZ_SPAN_LITERAL_FROM_STR("fw_version");
static az_span const twin_reported_fw_version_property_value = AZ_SPAN_LITERAL_FROM_STR("1.1.1");
static az_span const component_specifier_name = AZ_SPAN_LITERAL_FROM_STR("__t");
static az_span const component_specifier_value = AZ_SPAN_LITERAL_FROM_STR("c");

static az_result append_string_callback(az_json_writer* jw, void* value)
{
	return az_json_writer_append_string(jw, *(az_span*)value);
}

void pnp_device_info_append_all_reported_property(
    pnp_device_info_component* device_info_component,
    az_json_writer* jw)
{
	char const* const log = "Failed to build reported property payload for device info";
	
	if (az_span_size(device_info_component->component_name) != 0)
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, device_info_component->component_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(jw), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, component_specifier_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, component_specifier_value), log);
	}
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_manufacturer_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, device_info_component->manufacturer), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_model_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, device_info_component->model), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_fw_version_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, device_info_component->fw_version), log);
	if (az_span_size(device_info_component->component_name) != 0)
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(jw), log);
	}
	
}

void pnp_device_info_build_reported_property(
    pnp_device_info_component* device_info_component,
    az_span payload,
    az_span* out_payload,
    az_span property_name)
{
	if(az_span_is_content_equal(property_name, twin_reported_manufacturer_property_name))
	{
		pnp_build_reported_property(
			payload,
			device_info_component->component_name,
			twin_reported_manufacturer_property_name,
			append_string_callback,
			&device_info_component->manufacturer,
			out_payload);

	}
	else if(az_span_is_content_equal(property_name, twin_reported_model_property_name))
	{
		pnp_build_reported_property(
			payload,
			device_info_component->component_name,
			twin_reported_model_property_name,
			append_string_callback,
			&device_info_component->model,
			out_payload);
	}
	else if(az_span_is_content_equal(property_name, twin_reported_fw_version_property_name))
	{
		pnp_build_reported_property(
			payload,
			device_info_component->component_name,
			twin_reported_fw_version_property_name,
			append_string_callback,
			&device_info_component->fw_version,
			out_payload);
	}
	else
	{
		IOT_SAMPLE_LOG_ERROR("Failed to build report property: %s.", az_span_ptr(property_name));
	}

}

az_result pnp_device_info_init(
    pnp_device_info_component* out_device_info_component,
    az_span component_name)
{
	if (out_device_info_component == NULL)
	{
		return AZ_ERROR_ARG;
	}
	
	//initialize gpio_component
	memset(out_device_info_component, 0, sizeof(pnp_device_info_component));
	
	out_device_info_component->component_name = component_name;
	out_device_info_component->manufacturer = twin_reported_manufacturer_property_value;
	out_device_info_component->model = twin_reported_model_property_value;
	out_device_info_component->fw_version = twin_reported_fw_version_property_value;
	
	return AZ_OK;
}

#endif

