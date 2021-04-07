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
#include "pnp_gpio.h"

// IoT Hub Device Twin Values
static az_span const twin_reported_gpio_support_property_name = AZ_SPAN_LITERAL_FROM_STR("gpio_support");
static az_span const component_specifier_name = AZ_SPAN_LITERAL_FROM_STR("__t");
static az_span const component_specifier_value = AZ_SPAN_LITERAL_FROM_STR("c");

// IoT Hub Commands Values
static az_span const command_gpio_set_name = AZ_SPAN_LITERAL_FROM_STR("gpio_set");
static az_span const command_gpio_read_name = AZ_SPAN_LITERAL_FROM_STR("gpio_read");
static az_span const command_gpio_write_name = AZ_SPAN_LITERAL_FROM_STR("gpio_write");

static az_span const command_port_number_name = AZ_SPAN_LITERAL_FROM_STR("port_num");
static az_span const command_pin_number_name = AZ_SPAN_LITERAL_FROM_STR("pin_num");
static az_span const command_gpio_set_pin_mode_name = AZ_SPAN_LITERAL_FROM_STR("pin_mode");
static az_span const command_gpio_set_pin_direction_name = AZ_SPAN_LITERAL_FROM_STR("pin_direction");
static az_span const command_gpio_write_value_name = AZ_SPAN_LITERAL_FROM_STR("value");
static az_span const command_empty_response_payload = AZ_SPAN_LITERAL_FROM_STR("{}");

#if defined(CONFIG_PLATFORM_8721D)
#define PNP_GPIO_LED_PIN PB_5
#define PNP_GPIO_PUSHBT_PIN PA_12
#elif defined(CONFIG_PLATFORM_8710C)
#define PNP_GPIO_LED_PIN PA_20
#define PNP_GPIO_PUSHBT_PIN PA_19
#endif

static az_result append_bool_callback(az_json_writer* jw, void* value)
{
	return az_json_writer_append_bool(jw, *(bool*)value);
}

az_result pnp_gpio_init(
    pnp_gpio_component* out_gpio_component,
    az_span component_name)
{
	int32_t pin_num, port_num;
	if (out_gpio_component == NULL)
	{
		return AZ_ERROR_ARG;
	}
	
	//initialize gpio_component
	memset(out_gpio_component, 0, sizeof(pnp_gpio_component));
	
	out_gpio_component->component_name = component_name;
	out_gpio_component->gpio_support = true;
	
	//Init GPIO we need, for example LED_PIN and PUSHBT_PIN
	//LED PIN
	pin_num = PIN_NUM(PNP_GPIO_LED_PIN);
	port_num = PORT_NUM(PNP_GPIO_LED_PIN);
	if(port_num == PORT_A)
	{
		gpio_init((gpio_t*)&out_gpio_component->GPIO_PA_set[pin_num], PNP_GPIO_LED_PIN);
		gpio_dir((gpio_t*)&out_gpio_component->GPIO_PA_set[pin_num], PIN_OUTPUT);
		gpio_mode((gpio_t*)&out_gpio_component->GPIO_PA_set[pin_num], PullNone);
		out_gpio_component->GPIO_PA_is_used[pin_num] = true;
	}
	else
	{
		gpio_init((gpio_t*)&out_gpio_component->GPIO_PB_set[pin_num], PNP_GPIO_LED_PIN);
		gpio_dir((gpio_t*)&out_gpio_component->GPIO_PB_set[pin_num], PIN_OUTPUT);
		gpio_mode((gpio_t*)&out_gpio_component->GPIO_PB_set[pin_num], PullNone);
		out_gpio_component->GPIO_PB_is_used[pin_num] = true;
	}

	//PUSH BUTTON PIN
	pin_num = PIN_NUM(PNP_GPIO_PUSHBT_PIN);
	port_num = PORT_NUM(PNP_GPIO_PUSHBT_PIN);
	if(port_num == PORT_A)
	{
		gpio_init((gpio_t*)&out_gpio_component->GPIO_PA_set[pin_num], PNP_GPIO_PUSHBT_PIN);
		gpio_dir((gpio_t*)&out_gpio_component->GPIO_PA_set[pin_num], PIN_INPUT);
		gpio_mode((gpio_t*)&out_gpio_component->GPIO_PA_set[pin_num], PullUp);
		out_gpio_component->GPIO_PA_is_used[pin_num] = true;
	}
	else
	{
		gpio_init((gpio_t*)&out_gpio_component->GPIO_PB_set[pin_num], PNP_GPIO_PUSHBT_PIN);
		gpio_dir((gpio_t*)&out_gpio_component->GPIO_PB_set[pin_num], PIN_INPUT);
		gpio_mode((gpio_t*)&out_gpio_component->GPIO_PB_set[pin_num], PullUp);
		out_gpio_component->GPIO_PB_is_used[pin_num] = true;
	}
	return AZ_OK;
}

void pnp_gpio_build_telemetry_message(
    pnp_gpio_component* gpio_component,
    az_span payload,
    az_span* out_payload)
{
	// No telemetry yet
	(void) gpio_component;
	(void) payload;
	(void) out_payload;
}

void pnp_gpio_append_all_reported_property(
    pnp_gpio_component* gpio_component,
    az_json_writer* jw)
{
	char const* const log = "Failed to build reported property payload for device info";
	
	if (az_span_size(gpio_component->component_name) != 0)
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, gpio_component->component_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(jw), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, component_specifier_name), log);
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_string(jw, component_specifier_value), log);
	}
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(jw, twin_reported_gpio_support_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_bool(jw, gpio_component->gpio_support), log);
	if (az_span_size(gpio_component->component_name) != 0)
	{
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(jw), log);
	}
	
}

void pnp_gpio_build_reported_property(
    pnp_gpio_component* gpio_component,
    az_span payload,
    az_span* out_payload,
    az_span property_name)
{
	if(az_span_is_content_equal(property_name, twin_reported_gpio_support_property_name))
	{
		pnp_build_reported_property(
			payload,
			gpio_component->component_name,
			twin_reported_gpio_support_property_name,
			append_bool_callback,
			&gpio_component->gpio_support,
			out_payload);
	}
	else
	{
		IOT_SAMPLE_LOG_ERROR("Failed to build report property: %s.", az_span_ptr(property_name));
	}
}

void pnp_gpio_build_error_reported_property_with_status(
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

bool pnp_gpio_process_property_update(
    pnp_gpio_component* ref_gpio_component,
    az_json_token const* property_name,
    az_json_reader const* property_value,
    int32_t version,
    az_span payload,
    az_span* out_payload)
{
	// No writable property yet
	(void) ref_gpio_component;
	(void) property_name;
	(void) property_value;
	(void) version;
	(void) payload;
	(void) out_payload;

	return false;
}

static void build_gpio_set_command_response_payload(
    pnp_gpio_component* gpio_component,
    az_span payload,
    az_span* out_payload)
{
	// No response
	(void) gpio_component;
	(void) payload;
	
	*out_payload = command_empty_response_payload;
}

static void build_gpio_read_command_response_payload(
    pnp_gpio_component* gpio_component,
    int32_t pin_state,
    az_span payload,
    az_span* out_payload)
{
	char const* const log = "Failed to build command response payload";

	az_json_writer jw;
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_init(&jw, payload, NULL), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_int32(&jw, pin_state), log);

	*out_payload = az_json_writer_get_bytes_used_in_destination(&jw);
}

static void build_gpio_write_command_response_payload(
    pnp_gpio_component* gpio_component,
    az_span payload,
    az_span* out_payload)
{
	// No response
	(void) gpio_component;
	(void) payload;
	
	*out_payload = command_empty_response_payload;
}


static bool invoke_gpio_set(
    pnp_gpio_component* gpio_component,
    az_span payload,
    az_span response,
    az_span* out_response)
{
	az_json_reader jr;
	int32_t port_num = -1;
	int32_t pin_num = -1;
	int32_t pin_mode = -1;
	int32_t pin_direction = -1;
	int param_found = 0;
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_init(&jr, payload, NULL), "Failed to init json reader to parse set_gpio payload");	
	
	while (az_result_succeeded(az_json_reader_next_token(&jr))
		&& (jr.token.kind != AZ_JSON_TOKEN_END_OBJECT || param_found < 4)) //Search all fields
	{
		if (az_json_token_is_text_equal(&jr.token, command_port_number_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_NUMBER)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `port_num` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&jr.token, &port_num), "Failed to get for `port_num` field in payload");
			++param_found;
		}
		else if (az_json_token_is_text_equal(&jr.token, command_pin_number_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_NUMBER)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `pin_num` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&jr.token, &pin_num), "Failed to get for `pin_num` field in payload");
			++param_found;
		}
		else if (az_json_token_is_text_equal(&jr.token, command_gpio_set_pin_mode_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_NUMBER)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `pin_mode` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&jr.token, &pin_mode), "Failed to get for `pin_mode` field in payload");
			++param_found;
		}
		else if (az_json_token_is_text_equal(&jr.token, command_gpio_set_pin_direction_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_NUMBER)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `pin_direction` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&jr.token, &pin_direction), "Failed to get for `pin_direction` field in payload");
			++param_found;
		}
		// else ignore other tokens
	}

	// Set the response payload to error if the `port_number` or `pin_number` field was empty.
	if (port_num < 0 || port_num > 1
		|| (port_num == PORT_A && (pin_num < 0 || pin_num >= PNP_GPIO_PA_NUM))
		|| (port_num == PORT_B && (pin_num < 0 || pin_num >= PNP_GPIO_PB_NUM))
		|| pin_mode < 0 || pin_direction < 0) 
	{
		IOT_SAMPLE_LOG_ERROR("Invalid parameter");
		return false;
	}

	//if pin is used, just set the parameter
	if(port_num == PORT_A)
	{
		if(gpio_component->GPIO_PA_is_used[pin_num] == true)
		{
			gpio_dir((gpio_t*)&gpio_component->GPIO_PA_set[pin_num], (PinDirection)pin_direction);
			gpio_mode((gpio_t*)&gpio_component->GPIO_PA_set[pin_num], (PinMode)pin_mode);
		}
		else //PA is not used
		{
			gpio_init((gpio_t*)&gpio_component->GPIO_PA_set[pin_num], (PinName)(PORT_A<<5|pin_num));
			gpio_dir((gpio_t*)&gpio_component->GPIO_PA_set[pin_num], (PinDirection)pin_direction);
			gpio_mode((gpio_t*)&gpio_component->GPIO_PA_set[pin_num], (PinMode)pin_mode);
			gpio_component->GPIO_PA_is_used[pin_num] = true;
		}
	}
	else //PORTB
	{
		if(gpio_component->GPIO_PB_is_used[pin_num] == true)
		{
			gpio_dir((gpio_t*)&gpio_component->GPIO_PB_set[pin_num], (PinDirection)pin_direction);
			gpio_mode((gpio_t*)&gpio_component->GPIO_PB_set[pin_num], (PinMode)pin_mode);
		}
		else //PORT_B
		{
			gpio_init((gpio_t*)&gpio_component->GPIO_PB_set[pin_num], (PinName)(PORT_B<<5|pin_num));
			gpio_dir((gpio_t*)&gpio_component->GPIO_PB_set[pin_num], (PinDirection)pin_direction);
			gpio_mode((gpio_t*)&gpio_component->GPIO_PB_set[pin_num], (PinMode)pin_mode);
			gpio_component->GPIO_PB_is_used[pin_num] = true;
		}
	}
	
	IOT_SAMPLE_LOG("Pinmux %s_%d set success", (port_num == PORT_A)?"PA":"PB", pin_num);
	
	build_gpio_set_command_response_payload(gpio_component, response, out_response);
	
	return true;
}

static bool invoke_gpio_read(
    pnp_gpio_component* gpio_component,
    az_span payload,
    az_span response,
    az_span* out_response)
{
	int32_t port_num = -1;
	int32_t pin_num = -1;
	int param_found = 0;
	az_json_reader jr;
	
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_init(&jr, payload, NULL), "Failed to init json reader to parse set_gpio payload");	
	
	while (az_result_succeeded(az_json_reader_next_token(&jr)) 
		&& (jr.token.kind != AZ_JSON_TOKEN_END_OBJECT || param_found < 2)) //Search all fields
	{
		if (az_json_token_is_text_equal(&jr.token, command_port_number_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_NUMBER)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `port_num` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&jr.token, &port_num), "Failed to get for `port_num` field in payload");
			++param_found;
		}
		else if (az_json_token_is_text_equal(&jr.token, command_pin_number_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_NUMBER)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `pin_num` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&jr.token, &pin_num), "Failed to get for `pin_num` field in payload");
			++param_found;
		}
		// else ignore other tokens
	}


	// Set the response payload to error if the `port_number` or `pin_number` field was empty.
	if (port_num < 0 || port_num > 1
		|| (port_num == PORT_A && (pin_num < 0 || pin_num >= PNP_GPIO_PA_NUM))
		|| (port_num == PORT_B && (pin_num < 0 || pin_num >= PNP_GPIO_PB_NUM))) 
	{
		IOT_SAMPLE_LOG_ERROR("Invalid parameter");
		return false;
	}

	//get GPIO status
	int32_t pin_state = -1;

	if(port_num == PORT_A && gpio_component->GPIO_PA_is_used[pin_num] == true)
	{
		pin_state = gpio_read((gpio_t*)&gpio_component->GPIO_PA_set[pin_num]);
	}
	else if(port_num == PORT_B && gpio_component->GPIO_PB_is_used[pin_num] == true) 
	{
		pin_state = gpio_read((gpio_t*)&gpio_component->GPIO_PB_set[pin_num]);
	}
	else
	{
		IOT_SAMPLE_LOG_ERROR("Pinmux is not initialize");
		return false;
	}

	IOT_SAMPLE_LOG("Pinmux %s_%d read success", (port_num == PORT_A)?"PA":"PB", pin_num);

	build_gpio_read_command_response_payload(gpio_component, pin_state, response, out_response);

	return true;
}

static bool invoke_gpio_write(
    pnp_gpio_component* gpio_component,
    az_span payload,
    az_span response,
    az_span* out_response)
{
	int32_t port_num = -1;
	int32_t pin_num = -1;
	int32_t value = -1;
	int param_found = 0;
	az_json_reader jr;
	
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_init(&jr, payload, NULL), "Failed to init json reader to parse set_gpio payload");	
	
	while (az_result_succeeded(az_json_reader_next_token(&jr)) 
		&& (jr.token.kind != AZ_JSON_TOKEN_END_OBJECT || param_found < 3)) //Search all fields
	{
		if (az_json_token_is_text_equal(&jr.token, command_port_number_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_NUMBER)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `port_num` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&jr.token, &port_num), "Failed to get for `port_num` field in payload");
			++param_found;
		}
		else if (az_json_token_is_text_equal(&jr.token, command_pin_number_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_NUMBER)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `pin_num` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&jr.token, &pin_num), "Failed to get for `pin_num` field in payload");
			++param_found;
		}
		else if (az_json_token_is_text_equal(&jr.token, command_gpio_write_value_name))
		{
			_az_RETURN_IF_FAILED(az_json_reader_next_token(&jr));
			if (jr.token.kind != AZ_JSON_TOKEN_NUMBER)
			{
				IOT_SAMPLE_LOG_ERROR("Invalid format of `value` field");
				return false;
			}
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&jr.token, &value), "Failed to get for `value` field in payload");
			++param_found;
		}
		// else ignore other tokens
	}

	// Set the response payload to error if the `port_number` or `pin_number` field was empty.
	if (port_num < 0 || port_num > 1
		|| (port_num == PORT_A && (port_num < 0 || pin_num >= PNP_GPIO_PA_NUM))
		|| (port_num == PORT_B && (pin_num < 0 || pin_num >= PNP_GPIO_PB_NUM))
		|| value < 0 || value > 1) 
	{
		IOT_SAMPLE_LOG_ERROR("Invalid parameter");
		return false;
	}
	//set gpio value
	if(port_num == PORT_A && gpio_component->GPIO_PA_is_used[pin_num] == true)
	{
		gpio_write((gpio_t*)&gpio_component->GPIO_PA_set[pin_num], value);
	}
	else if(port_num == PORT_B && gpio_component->GPIO_PB_is_used[pin_num] == true) 
	{
		gpio_write((gpio_t*)&gpio_component->GPIO_PB_set[pin_num], value);
	}
	else
	{
		IOT_SAMPLE_LOG_ERROR("Pinmux is not initialize");
		return false;
	}

	IOT_SAMPLE_LOG("Pinmux %s_%d write success", (port_num == PORT_A)?"PA":"PB", pin_num);

	build_gpio_write_command_response_payload(gpio_component, response, out_response);

	return true;
}

bool pnp_gpio_process_command_request(
    pnp_gpio_component* gpio_component,
    az_span command_name,
    az_span command_received_payload,
    az_span payload,
    az_span* out_payload,
    az_iot_status* out_status)
{
	if (az_span_is_content_equal(command_gpio_set_name, command_name))
	{
		// Invoke command.
		if (invoke_gpio_set(gpio_component, command_received_payload, payload, out_payload))
		{
			*out_status = AZ_IOT_STATUS_OK;
		}
		else
		{
			*out_payload = command_empty_response_payload;
			*out_status = AZ_IOT_STATUS_BAD_REQUEST;
			IOT_SAMPLE_LOG_AZ_SPAN("Bad request when invoking command on GPIO component:", command_name);
			return false;
		}
	}
	else if(az_span_is_content_equal(command_gpio_read_name, command_name))
	{
		// Invoke command.
		if (invoke_gpio_read(gpio_component, command_received_payload, payload, out_payload))
		{
			*out_status = AZ_IOT_STATUS_OK;
		}
		else
		{
			*out_payload = command_empty_response_payload;
			*out_status = AZ_IOT_STATUS_BAD_REQUEST;
			IOT_SAMPLE_LOG_AZ_SPAN("Bad request when invoking command on GPIO component:", command_name);
			return false;
		}
	}
	else if(az_span_is_content_equal(command_gpio_write_name, command_name))
	{
		// Invoke command.
		if (invoke_gpio_write(gpio_component, command_received_payload, payload, out_payload))
		{
			*out_status = AZ_IOT_STATUS_OK;
		}
		else
		{
			*out_payload = command_empty_response_payload;
			*out_status = AZ_IOT_STATUS_BAD_REQUEST;
			IOT_SAMPLE_LOG_AZ_SPAN("Bad request when invoking command on GPIO component:", command_name);
			return false;
		}
	}
	else // Unsupported command
	{
		*out_payload = command_empty_response_payload;
		*out_status = AZ_IOT_STATUS_NOT_FOUND;
		IOT_SAMPLE_LOG_AZ_SPAN("Command not supported on GPIO component:", command_name);
		return false;
	}

	return true;
}


#endif

