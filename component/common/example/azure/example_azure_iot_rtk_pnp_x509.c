#include "example_azure_iot_entry.h"
#ifdef EXAMPLE_AZURE_IOT_RTK_PNP_X509
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <azure/az_core.h>
#include <azure/az_iot.h>

#include "FreeRTOS.h"
#include "task.h"

#include "MQTTClient.h"
#include "wifi_conf.h"
#include <sntp/sntp.h>

#include "example_azure_iot_common.h"

#include "pnp/pnp_mqtt_message.h"
#include "pnp/pnp_protocol.h"
#include "pnp/rtk_message/pnp_common_message.h"

#include "pnp/rtk_component/pnp_audio.h"
#include "pnp/rtk_component/pnp_bluetooth.h"
#include "pnp/rtk_component/pnp_device_info.h"
#include "pnp/rtk_component/pnp_gpio.h"
#include "pnp/rtk_component/pnp_lcd.h"
#include "pnp/rtk_component/pnp_memory.h"
#include "pnp/rtk_component/pnp_system.h"
#include "pnp/rtk_component/pnp_video.h"
#include "pnp/rtk_component/pnp_wireless.h"

#define ID_SCOPE "[ID Scope]"	
#define REGISTRATION_ID "[Registration ID]"

#define X509CERTIFICATE \
"-----BEGIN CERTIFICATE-----""\n" \
"MIICKTCCAc+gAwIBAgIJANf4macI+5CjMAoGCCqGSM49BAMCMIGLMQswCQYDVQQG""\n" \
"...""\n" \
"BAMCA0gAMEUCIASvNlsu1B5YYukbi81uTCRpqsAVXl7k4qoOYOrsrU35AiEAyo76""\n" \
"Iqj1a5zwz6lTC3Gl8Ge9lsuhFWf+epVLppJNDMI=""\n" \
"-----END CERTIFICATE-----""\n"

#define X509PRIVATEKEY \
"-----BEGIN EC PARAMETERS-----""\n" \
"...""\n" \
"-----END EC PARAMETERS-----""\n" \
"-----BEGIN EC PRIVATE KEY-----""\n" \
"MHcCAQEEIBUCAxvvqARY6IfihGk5V5pwv8DYVSlIJGyCWODpbU5GoAoGCCqGSM49""\n" \
"...""\n" \
"1ZghkDRQGUDzDkUgy0ffsL3lv864Zzk0ng==""\n" \
"-----END EC PRIVATE KEY-----""\n"

#define MQTT_TIMEOUT_RECEIVE_MS (60 * 1000)
#define MQTT_TIMEOUT_DISCONNECT_MS (10 * 1000)
#define PNP_RETRY_INTERVAL_SEC 1
#define PUBLISH_SEMA_POOL 1

// * PnP Values *
// The model id is the JSON document (also called the Digital Twins Model Identifier or DTMI) which
// defines the capability of your device. The functionality of the device should match what is
// described in the corresponding DTMI. Should you choose to program your own PnP capable device,
// the functionality would need to match the DTMI and you would need to update the below 'model_id'.
// Please see the sample README for more information on this DTMI.
static az_span const model_id = AZ_SPAN_LITERAL_FROM_STR("dtmi:realtek:rtk_ameba_series;1");
static az_span const command_empty_response_payload = AZ_SPAN_LITERAL_FROM_STR("{}");
static char dps_payload_with_model_id[100];
char provisioned_device_hub_hostname[100];
char provisioned_device_id[100];

// Components
static pnp_audio_component pnp_audio;
static pnp_bluetooth_component pnp_bluetooth;
static pnp_device_info_component pnp_device_info;
static pnp_gpio_component pnp_gpio;
static pnp_lcd_component pnp_lcd;
static pnp_memory_component pnp_memory;
static pnp_system_component pnp_system;
static pnp_video_component pnp_video;
static pnp_wireless_component pnp_wireless;
static az_span const audio_name = AZ_SPAN_LITERAL_FROM_STR("audio");
static az_span const bluetooth_name = AZ_SPAN_LITERAL_FROM_STR("bluetooth");
static az_span const device_info_name = AZ_SPAN_LITERAL_FROM_STR("device_information");
static az_span const gpio_name = AZ_SPAN_LITERAL_FROM_STR("gpio");
static az_span const lcd_name = AZ_SPAN_LITERAL_FROM_STR("lcd");
static az_span const memory_name = AZ_SPAN_LITERAL_FROM_STR("memory");
static az_span const system_name = AZ_SPAN_LITERAL_FROM_STR("system");
static az_span const video_name = AZ_SPAN_LITERAL_FROM_STR("video");
static az_span const wireless_name = AZ_SPAN_LITERAL_FROM_STR("wireless");
static az_span const* pnp_components[] = {&audio_name, &bluetooth_name, &device_info_name, &gpio_name, &lcd_name,
                                          &memory_name, &system_name, &video_name, &wireless_name};
static int32_t const pnp_components_num = sizeof(pnp_components) / sizeof(pnp_components[0]);

// Connection Variables
iot_sample_variables az_vars;
az_iot_provisioning_client provisioning_client;
az_iot_hub_client hub_client;
MQTTClient mqtt_client;
static Network mqtt_network;
static MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
static unsigned char mqtt_sendbuf[2048], mqtt_readbuf[2048];
static bool dps_is_connect = false;
static bool iot_hub_is_connect = false;
static bool is_operation_complete = false;
static bool is_message_error = false;
static az_iot_hub_client_options options;
static pnp_mqtt_message publish_message;
static char mqtt_client_username_buffer[256];
static char mqtt_client_id_buffer[128];
static xSemaphoreHandle publish_sema = NULL;

static void property_callback(
    az_span component_name,
    az_json_token const* property_name,
    az_json_reader property_value,
    int32_t version,
    void* user_context_callback)
{
	az_result rc;

	(void)user_context_callback;
	
	xSemaphoreTake(publish_sema, portMAX_DELAY);

	// Get the Twin Patch topic to send a property update.
	rc = az_iot_hub_client_twin_patch_get_publish_topic(&hub_client, pnp_mqtt_get_request_id(), publish_message.topic, publish_message.topic_length, NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to get the Twin Patch topic: az_result return code 0x%08x.", rc);
	}

	// Attempt to process property update per component until find success or exit on error.
	if (az_span_is_content_equal(pnp_memory.component_name, component_name))
	{
		if (!pnp_memory_process_property_update(&pnp_memory, property_name, &property_value, version, publish_message.payload, &publish_message.out_payload))
		{
			IOT_SAMPLE_LOG_ERROR("Memory component does not support writeable property `%.*s`.", az_span_size(property_name->slice), az_span_ptr(property_name->slice));

			// Build the component error message.
			pnp_memory_build_error_reported_property_with_status(component_name, property_name->slice, &property_value, AZ_IOT_STATUS_NOT_FOUND, 
				version, publish_message.payload, &publish_message.out_payload);
		}
	}
	else if (az_span_is_content_equal(pnp_system.component_name, component_name))
	{
		if (!pnp_system_process_property_update(&pnp_system, property_name, &property_value, version, publish_message.payload, &publish_message.out_payload))
		{
			IOT_SAMPLE_LOG_ERROR("System component does not support writeable property `%.*s`.", az_span_size(property_name->slice), az_span_ptr(property_name->slice));

			// Build the component error message.
			pnp_system_build_error_reported_property_with_status(component_name, property_name->slice, &property_value, AZ_IOT_STATUS_NOT_FOUND, 
				version, publish_message.payload, &publish_message.out_payload);
		}
	}
	else if (az_span_is_content_equal(pnp_wireless.component_name, component_name))
	{
		if (!pnp_wireless_process_property_update(&pnp_wireless, property_name, &property_value, version, publish_message.payload, &publish_message.out_payload))
		{
			IOT_SAMPLE_LOG_ERROR("Wireless component does not support writeable property `%.*s`.", az_span_size(property_name->slice), az_span_ptr(property_name->slice));

			// Build the component error message.
			pnp_wireless_build_error_reported_property_with_status(component_name, property_name->slice, &property_value, AZ_IOT_STATUS_NOT_FOUND, 
				version, publish_message.payload, &publish_message.out_payload);
		}
	}
	else
	{
		IOT_SAMPLE_LOG("No components recognized to update a property.");
		xSemaphoreGive(publish_sema);
		return;
	}

	// Send response. On a successfull property update above, out_payload will already be set.
	publish_mqtt_message(publish_message.topic, publish_message.out_payload, IOT_SAMPLE_MQTT_PUBLISH_QOS);
	IOT_SAMPLE_LOG_SUCCESS("Client sent reported property with status message.");
	IOT_SAMPLE_LOG_AZ_SPAN("Payload:", publish_message.out_payload);
	IOT_SAMPLE_LOG(" "); // Formatting.
	xSemaphoreGive(publish_sema);
	
	// Receive the response from the server.
	receive_mqtt_message();
}


static void handle_device_twin_message(
    MQTTMessage const* receive_message,
    az_iot_hub_client_twin_response const* twin_response)
{
	uint8_t* message_buf = NULL;
	az_span message_span;

	//If there are more then one component properties in the recieved payload, the payload buffer may be overwrited.
	//Since each property update need to publish a response to IoT Hub and need to recieve ack. 
	//Recieve ack may overwrite the payload buffer so that the rest of property update will not be completed.
	message_buf = (uint8_t*)malloc(receive_message->payloadlen * sizeof(uint8_t)+1);
	memcpy(message_buf, receive_message->payload, receive_message->payloadlen);
	message_span = az_span_create(message_buf, receive_message->payloadlen);

	// Invoke appropriate action per response type (3 types only).
	switch (twin_response->response_type)
	{
		// A response from a twin GET publish message with the twin document as a payload.
		case AZ_IOT_HUB_CLIENT_TWIN_RESPONSE_TYPE_GET:
			IOT_SAMPLE_LOG("Message Type: GET");
			pnp_process_device_twin_message(message_span, false, pnp_components, pnp_components_num, property_callback, NULL);
			break;

		// An update to the desired properties with the properties as a payload.
		case AZ_IOT_HUB_CLIENT_TWIN_RESPONSE_TYPE_DESIRED_PROPERTIES:
			IOT_SAMPLE_LOG("Message Type: Desired Properties");
			pnp_process_device_twin_message(message_span, true, pnp_components, pnp_components_num, property_callback, NULL);
			break;

		// A response from a twin reported properties publish message.
		case AZ_IOT_HUB_CLIENT_TWIN_RESPONSE_TYPE_REPORTED_PROPERTIES:
			IOT_SAMPLE_LOG("Message Type: Reported Properties");
			break;
	}

	if(message_buf)
	{
		free(message_buf);
	}
}

static void handle_command_request(
    MQTTMessage const* receive_message,
    az_iot_hub_client_method_request const* command_request)
{
	az_span component_name;
	az_span command_name;
	pnp_parse_command_name(command_request->name, &component_name, &command_name);

	az_span const message_span = az_span_create((uint8_t*)receive_message->payload, receive_message->payloadlen);
	az_iot_status status = AZ_IOT_STATUS_UNKNOWN;
	
	xSemaphoreTake(publish_sema, portMAX_DELAY);
	
	// Invoke command and retrieve status and response payload to send to server.
	if (az_span_is_content_equal(pnp_gpio.component_name, component_name))
	{
 		if (pnp_gpio_process_command_request(&pnp_gpio, command_name, message_span, publish_message.payload, &publish_message.out_payload, &status))
		{
			IOT_SAMPLE_LOG_AZ_SPAN("Client invoked command on gpio component:", command_name);
		}
	}
	else if (az_span_is_content_equal(pnp_system.component_name, component_name))
	{
 		if (pnp_system_process_command_request(&pnp_system, command_name, message_span, publish_message.payload, &publish_message.out_payload, &status))
		{
			IOT_SAMPLE_LOG_AZ_SPAN("Client invoked command on system component:", command_name);
		}
	}
	else if (az_span_is_content_equal(pnp_wireless.component_name, component_name))
	{
 		if (pnp_wireless_process_command_request(&pnp_wireless, command_name, message_span, publish_message.payload, &publish_message.out_payload, &status))
		{
			IOT_SAMPLE_LOG_AZ_SPAN("Client invoked command on wireless component:", command_name);
		}
	}
	else
	{
		IOT_SAMPLE_LOG_AZ_SPAN("Command not supported:", command_request->name);
		publish_message.out_payload = command_empty_response_payload;
		status = AZ_IOT_STATUS_NOT_FOUND;
	}

	// Get the Methods response topic to publish the command response.
	az_result rc = az_iot_hub_client_methods_response_get_publish_topic(
		&hub_client,
		command_request->request_id,
		(uint16_t)status,
		publish_message.topic,
		publish_message.topic_length,
		NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to get the Methods response topic: az_result return code 0x%08x.", rc);
	}

	// Publish the command response.
	publish_mqtt_message(publish_message.topic, publish_message.out_payload, IOT_SAMPLE_MQTT_PUBLISH_QOS);
	IOT_SAMPLE_LOG_SUCCESS("Client published command response.");
	IOT_SAMPLE_LOG("Status: %d", status);
	IOT_SAMPLE_LOG_AZ_SPAN("Payload:", publish_message.out_payload);
	xSemaphoreGive(publish_sema);
}

static void send_telemetry_messages(void)
{
	int ret = SUCCESS;
	if(pnp_memory.telemetry_enable_remain_heap &&
		++pnp_memory.telemetry_counter == pnp_memory.telemetry_interval)
	{
		xSemaphoreTake(publish_sema, portMAX_DELAY);
		// Get the Telemetry topic to publish the telemetry message.
		pnp_telemetry_get_publish_topic(
			&hub_client,
			NULL,
			pnp_memory.component_name,
			publish_message.topic,
			publish_message.topic_length,
			NULL);

		// Build the Telemetry message.
		pnp_memory_build_telemetry_message(&pnp_memory, publish_message.payload, &publish_message.out_payload);

		// Publish the telemetry message.
		ret = publish_mqtt_message(publish_message.topic, publish_message.out_payload, IOT_SAMPLE_MQTT_PUBLISH_QOS);
		pnp_memory.telemetry_counter = 0;
		if(ret == FAILURE)
		{
			IOT_SAMPLE_LOG_ERROR("Client failed to publish the Telemetry message for Memory Component.");
			is_message_error = true;
			xSemaphoreGive(publish_sema);
			return;
		}
		IOT_SAMPLE_LOG_SUCCESS("Client published the Telemetry message for Memory Component.");
		IOT_SAMPLE_LOG_AZ_SPAN("Payload:", publish_message.out_payload);
		xSemaphoreGive(publish_sema);
	}
	
	if((pnp_system.telemetry_enable_cpu_usage || pnp_system.telemetry_enable_device_runtime) &&
		++pnp_system.telemetry_counter == pnp_system.telemetry_interval)
	{
		xSemaphoreTake(publish_sema, portMAX_DELAY);
		// Get the Telemetry topic to publish the telemetry message.
		pnp_telemetry_get_publish_topic(
			&hub_client,
			NULL,
			pnp_system.component_name,
			publish_message.topic,
			publish_message.topic_length,
			NULL);

		// Build the Telemetry message.
		pnp_system_build_telemetry_message(&pnp_system, publish_message.payload, &publish_message.out_payload);

		// Publish the telemetry message.
		ret = publish_mqtt_message(publish_message.topic, publish_message.out_payload, IOT_SAMPLE_MQTT_PUBLISH_QOS);
		pnp_system.telemetry_counter = 0;
		if(ret == FAILURE)
		{
			IOT_SAMPLE_LOG_ERROR("Client failed to publish the Telemetry message for System Component.");
			is_message_error = true;
			xSemaphoreGive(publish_sema);
			return;
		}
		IOT_SAMPLE_LOG_SUCCESS("Client published the Telemetry message for System Component.");
		IOT_SAMPLE_LOG_AZ_SPAN("Payload:", publish_message.out_payload);
		xSemaphoreGive(publish_sema);
	}
	
	if(pnp_wireless.telemetry_enable_wifi_info &&
			++pnp_wireless.telemetry_counter == pnp_wireless.telemetry_interval)
	{
		xSemaphoreTake(publish_sema, portMAX_DELAY);
		// Get the Telemetry topic to publish the telemetry message.
		pnp_telemetry_get_publish_topic(
			&hub_client,
			NULL,
			pnp_wireless.component_name,
			publish_message.topic,
			publish_message.topic_length,
			NULL);

		// Build the Telemetry message.
		pnp_wireless_build_telemetry_message(&pnp_wireless, publish_message.payload, &publish_message.out_payload);

		// Publish the telemetry message.
		ret = publish_mqtt_message(publish_message.topic, publish_message.out_payload, IOT_SAMPLE_MQTT_PUBLISH_QOS);
		pnp_wireless.telemetry_counter = 0;
		if(ret == FAILURE)
		{
			IOT_SAMPLE_LOG_ERROR("Client failed to publish the Telemetry message for Wireless Component.");
			is_message_error = true;
			xSemaphoreGive(publish_sema);
			return;
		}
		IOT_SAMPLE_LOG_SUCCESS("Client published the Telemetry message for Wireless Component.");
		IOT_SAMPLE_LOG_AZ_SPAN("Payload:", publish_message.out_payload);
		xSemaphoreGive(publish_sema);
	}

}


static void initialize_components(void)
{
	az_result rc;

	//audio component init
	rc = pnp_audio_init(&pnp_audio, audio_name);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to initialize audio component: az_result return code 0x%08x.", rc);
	}
	//bluetooth component init
	rc = pnp_bluetooth_init(&pnp_bluetooth, bluetooth_name);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to initialize bluetooth component: az_result return code 0x%08x.", rc);
	}	
	//device_info component init
	rc = pnp_device_info_init(&pnp_device_info, device_info_name);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to initialize device_info component: az_result return code 0x%08x.", rc);
	}	
	//gpio component init
	rc = pnp_gpio_init(&pnp_gpio, gpio_name);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to initialize gpio component: az_result return code 0x%08x.", rc);
	}	
	//lcd component init
	rc = pnp_lcd_init(&pnp_lcd, lcd_name);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to initialize lcd component: az_result return code 0x%08x.", rc);
	}	
	//memory component init
	rc = pnp_memory_init(&pnp_memory, memory_name);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to initialize memory component: az_result return code 0x%08x.", rc);
	}
	//system component init
	rc = pnp_system_init(&pnp_system, system_name);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to initialize system component: az_result return code 0x%08x.", rc);
	}
	//video component init
	rc = pnp_video_init(&pnp_video, video_name);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to initialize video component: az_result return code 0x%08x.", rc);
	}
	//wireless component init
	rc = pnp_wireless_init(&pnp_wireless, wireless_name);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to initialize wireless component: az_result return code 0x%08x.", rc);
	}

}

void send_device_twins_reported_property(void)
{
	int rc;
	az_json_writer jw;

	char const* const log = "Failed to build reported property payload for device info";

	rc = az_iot_hub_client_twin_patch_get_publish_topic(
		&hub_client,
		pnp_mqtt_get_request_id(),
		publish_message.topic,
		publish_message.topic_length,
		NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to get the Twin Patch topic: az_result return code 0x%08x.", rc);
    }

	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_init(&jw, publish_message.payload, NULL), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(&jw), log);

	// Append the device info reported property message.
	pnp_device_info_append_all_reported_property(&pnp_device_info, &jw);
	
	// Append the device info reported property message.
	pnp_system_append_all_reported_property(&pnp_system, &jw);
	
	// Append the device info reported property message.
	pnp_memory_append_all_reported_property(&pnp_memory, &jw);
	
	// Append the device info reported property message.
	pnp_wireless_append_all_reported_property(&pnp_wireless, &jw);
	
	// Append the device info reported property message.
	pnp_bluetooth_append_all_reported_property(&pnp_bluetooth, &jw);
	
	// Append the device info reported property message.
	pnp_audio_append_all_reported_property(&pnp_audio, &jw);
	
	// Append the device info reported property message.
	pnp_video_append_all_reported_property(&pnp_video, &jw);
	
	// Append the device info reported property message.
	pnp_lcd_append_all_reported_property(&pnp_lcd, &jw);
	
	// Append the device info reported property message.
	pnp_gpio_append_all_reported_property(&pnp_gpio, &jw);

	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(&jw), log);

	publish_message.out_payload = az_json_writer_get_bytes_used_in_destination(&jw);

	// Publish the device info reported property update.
	publish_mqtt_message(publish_message.topic, publish_message.out_payload, IOT_SAMPLE_MQTT_PUBLISH_QOS);
	IOT_SAMPLE_LOG_SUCCESS("Client sent reported property message for all components.");
	IOT_SAMPLE_LOG_AZ_SPAN("Payload:", publish_message.out_payload);
	IOT_SAMPLE_LOG(" "); // Formatting

	// Receive the response from the server.
	receive_mqtt_message();
}

static void messageArrivedFromDPS(MessageData* data)
{
	IOT_SAMPLE_LOG_SUCCESS("Client received a message from the provisioning service.");
	
	// Parse registration status message.
	az_iot_provisioning_client_register_response register_response;
	parse_device_registration_status_message(data->topicName->lenstring.data, data->topicName->lenstring.len, data->message, &register_response);
	IOT_SAMPLE_LOG_SUCCESS("Client parsed registration status message.");
	
	handle_device_registration_status_message(&register_response, &is_operation_complete);
}

static void messageArrivedFromIothub(MessageData* data)
{
	az_result rc;

	IOT_SAMPLE_LOG_SUCCESS("Client received a message from the service.");

	az_span const topic_span = az_span_create((uint8_t*)data->topicName->lenstring.data, data->topicName->lenstring.len);
	az_span const message_span = az_span_create((uint8_t*)data->message->payload, data->message->payloadlen);

	az_iot_hub_client_twin_response twin_response;
	az_iot_hub_client_method_request command_request;

	// Parse the incoming message topic and handle appropriately.
	rc = az_iot_hub_client_twin_parse_received_topic(&hub_client, topic_span, &twin_response);
	if (az_result_succeeded(rc))
	{
		IOT_SAMPLE_LOG_SUCCESS("Client received a valid topic response.");
		IOT_SAMPLE_LOG_AZ_SPAN("Topic:", topic_span);
		IOT_SAMPLE_LOG_AZ_SPAN("Payload:", message_span);
		IOT_SAMPLE_LOG("Status: %d", twin_response.status);

		handle_device_twin_message(data->message, &twin_response);
	}
	else
	{
		rc = az_iot_hub_client_methods_parse_received_topic(&hub_client, topic_span, &command_request);
		if (az_result_succeeded(rc))
		{
			IOT_SAMPLE_LOG_SUCCESS("Client received a valid topic response.");
			IOT_SAMPLE_LOG_AZ_SPAN("Topic:", topic_span);
			IOT_SAMPLE_LOG_AZ_SPAN("Payload:", message_span);

			handle_command_request(data->message, &command_request);
		}
		else
		{
			IOT_SAMPLE_LOG_ERROR("Message from unknown topic: az_result return code 0x%08x.", rc);
			IOT_SAMPLE_LOG_AZ_SPAN("Topic:", topic_span);
		}
	}
	
	IOT_SAMPLE_LOG(" "); // Formatting
}


static void pnp_telemetry_thread(void* param)
{
	
	iot_sample_sleep_for_seconds(1);
	IOT_SAMPLE_LOG_SUCCESS("Telemetry thread created");
	
	while(iot_hub_is_connect && !is_message_error){
		// Send telemetry messages
		send_telemetry_messages();
		
		iot_sample_sleep_for_seconds(1); // 1 sec counter for all component telemetry
	}
	vTaskDelete(NULL);
}


/*
 * This sample registers a device with the Azure IoT Hub Device Provisioning Service. It will wait
 * to receive the registration status before disconnecting. SAS certification is used.
 */
static void example_azure_iot_rtk_pnp_x509_thread(void* param)
{
	int rc;

	while (wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != SUCCESS)
	{
		vTaskDelay(1000);
	}
	
	// for directed method query for ISO8061 time
	sntp_init();

	/******************************* IoT Device Provisioning *******************************/

	import_user_configuration(&az_vars, IOT_SAMPLE_PROVISIONING_ID_SCOPE, ID_SCOPE);
	import_user_configuration(&az_vars, IOT_SAMPLE_PROVISIONING_REGISTRATION_ID, REGISTRATION_ID);
	import_user_configuration(&az_vars, IOT_SAMPLE_DEVICE_X509_CERTIFICATE, X509CERTIFICATE);
	import_user_configuration(&az_vars, IOT_SAMPLE_DEVICE_X509_PRIVATE_KEY, X509PRIVATEKEY);
	
	// Check variables set by user for purposes of running sample.
	iot_sample_check_variables(AZIOT_PROVISIONING, AZIOT_872XD_PNP_SAMPLE, &az_vars);
	
	// Initialize the provisioning client with the provisioning global endpoint and the default
	// connection options.
	rc = az_iot_provisioning_client_init(
		&provisioning_client,
		az_span_create_from_str(PROVISIONING_GLOBAL_ENDPOINT),
		az_vars.provisioning_id_scope,
		az_vars.provisioning_registration_id,
		NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to initialize provisioning client: az_result return code 0x%08x.", rc);
		goto aziot_exit;
	}

	//Init network option for mqtt client
	NetworkInit(&mqtt_network);
	mqtt_network.clientCA = (char*)az_span_ptr(az_vars.x509_certificate);
	mqtt_network.private_key = (char*)az_span_ptr(az_vars.x509_private_key);
	mqtt_network.use_ssl = 1;

	//MQTT client init
	MQTTClientInit(&mqtt_client, &mqtt_network, 30000, mqtt_sendbuf, sizeof(mqtt_sendbuf), mqtt_readbuf, sizeof(mqtt_readbuf));
	IOT_SAMPLE_LOG_SUCCESS("Client created and configured.");
	
	// Get the MQTT client username.
	rc = az_iot_provisioning_client_get_user_name(&provisioning_client, mqtt_client_username_buffer, sizeof(mqtt_client_username_buffer), NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to get MQTT client username: az_result return code 0x%08x.", rc);
		goto aziot_exit;
	}
	
	// Get the MQTT client id used for the MQTT connection.
	rc = az_iot_provisioning_client_get_client_id(&provisioning_client, mqtt_client_id_buffer, sizeof(mqtt_client_id_buffer), NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to get MQTT client id: az_result return code 0x%08x.", rc);
		goto aziot_exit;
	}
	
	// Set MQTT connection options.
	connectData.clientID.cstring = mqtt_client_id_buffer;
	connectData.username.cstring = mqtt_client_username_buffer;
	connectData.cleansession = false;
	connectData.keepAliveInterval = AZ_IOT_DEFAULT_MQTT_CONNECT_KEEPALIVE_SECONDS;

	if((rc = connect_to_azure_server_by_mqtt(&mqtt_client, &connectData, PROVISIONING_GLOBAL_ENDPOINT, PNP_RETRY_INTERVAL_SEC)) != SUCCESS)
	{
		goto aziot_exit;
	}
	dps_is_connect = true;
	IOT_SAMPLE_LOG_SUCCESS("Client connected to provisioning service.");
	
	// Subscribe mqtt client to provisioning service topics
	if ((rc = MQTTSubscribe(&mqtt_client, AZ_IOT_PROVISIONING_CLIENT_REGISTER_SUBSCRIBE_TOPIC, QOS1, messageArrivedFromDPS)) != SUCCESS)
	{
		IOT_SAMPLE_LOG_ERROR("Failed to subscribe to the Register topic: MQTTClient return code %d.", rc);
		goto aziot_exit;
	}
	IOT_SAMPLE_LOG_SUCCESS("Client subscribed to provisioning service topics.");

	// Register device with provisioning service
	// Get the Register topic to publish the register request.
	char register_topic_buffer[128];
	rc = az_iot_provisioning_client_register_get_publish_topic(&provisioning_client, register_topic_buffer, sizeof(register_topic_buffer), NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to get the Register topic: az_result return code 0x%08x.", rc);
		goto aziot_exit;
	}
	
	// Set MQTT message options.
	MQTTMessage message;
	message.qos = IOT_SAMPLE_MQTT_PUBLISH_QOS;
	message.retained = 0;
	
	memset(dps_payload_with_model_id, 0, sizeof(dps_payload_with_model_id));
	sprintf(dps_payload_with_model_id, "{\"payload\":{\"modelId\":\"%.*s\"}}", az_span_size(model_id), az_span_ptr(model_id));

	message.payload = dps_payload_with_model_id;
	message.payloadlen = strlen(dps_payload_with_model_id);
	
	// Publish the register request.
	if ((rc = MQTTPublish(&mqtt_client, register_topic_buffer, &message)) != 0)
	{
		IOT_SAMPLE_LOG_ERROR("Failed to publish Register request: MQTTClient return code %d.", rc);
		goto aziot_exit;
	}
	IOT_SAMPLE_LOG_SUCCESS("Client registering with provisioning service.");

	//clean buffer for provisioned device
	memset(provisioned_device_hub_hostname, 0, sizeof(provisioned_device_hub_hostname));
	memset(provisioned_device_id, 0, sizeof(provisioned_device_id));

	// Continue to parse incoming responses from the provisioning service until the device has been
	// successfully provisioned or an error occurs.
	while (!is_operation_complete)
	{
		IOT_SAMPLE_LOG(" "); // Formatting
		IOT_SAMPLE_LOG("Waiting for registration status message.");
		// Wait for any server messages.
		if((rc = receive_mqtt_message()) == FAILURE)
		{
			goto aziot_exit;
		}
		IOT_SAMPLE_LOG_SUCCESS("Client received a message from the provisioning service.");
	}
	IOT_SAMPLE_LOG_SUCCESS("Device is registered to iot hub.");

	// Disconnect from DPS and close socket
	rc = MQTTDisconnect(&mqtt_client);
	if (rc != SUCCESS)
	{
		IOT_SAMPLE_LOG_ERROR("Failed to disconnect MQTT client: MQTTClient return code %d.", rc);
	}
	mqtt_network.disconnect(&mqtt_network);
	dps_is_connect = false;


	/******************************* IoT Hub Plug and Play *******************************/

	if(strlen(provisioned_device_hub_hostname) == 0 || strlen(provisioned_device_id) == 0)
	{
		IOT_SAMPLE_LOG_ERROR("Empty information for provisioned device");
		goto aziot_exit;
	}

	import_user_configuration(&az_vars, IOT_SAMPLE_HUB_HOSTNAME, (const char *)provisioned_device_hub_hostname);
	import_user_configuration(&az_vars, IOT_SAMPLE_HUB_DEVICE_ID, (const char *)provisioned_device_id);
	import_user_configuration(&az_vars, IOT_SAMPLE_DEVICE_X509_CERTIFICATE, X509CERTIFICATE);
	import_user_configuration(&az_vars, IOT_SAMPLE_DEVICE_X509_PRIVATE_KEY, X509PRIVATEKEY);

	// Check variables set by user for purposes of running sample.
	iot_sample_check_variables(AZIOT_HUB, AZIOT_872XD_PNP_SAMPLE, &az_vars);
  
	// Initialize the hub client with the connection options.
	options = az_iot_hub_client_options_default();
	options.model_id = model_id;
	
	// Initialize the hub client with the default connection options.
	rc = az_iot_hub_client_init(&hub_client, az_vars.hub_hostname, az_vars.hub_device_id, &options);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to initialize hub client: az_result return code 0x%08x.", rc);
	}
  
	NetworkInit(&mqtt_network);
	mqtt_network.clientCA = (char*)az_span_ptr(az_vars.x509_certificate);
	mqtt_network.private_key = (char*)az_span_ptr(az_vars.x509_private_key);
	mqtt_network.use_ssl = 1;
  
	MQTTClientInit(&mqtt_client, &mqtt_network, 30000, mqtt_sendbuf, sizeof(mqtt_sendbuf), mqtt_readbuf, sizeof(mqtt_readbuf));

	memset(mqtt_client_username_buffer, 0, sizeof(mqtt_client_username_buffer));
	memset(mqtt_client_id_buffer, 0, sizeof(mqtt_client_id_buffer));
	
	// Get the MQTT client username.
	rc = az_iot_hub_client_get_user_name(&hub_client, mqtt_client_username_buffer, sizeof(mqtt_client_username_buffer), NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to get MQTT client username: az_result return code 0x%08x.", rc);
	}
	// Get the MQTT client id used for the MQTT connection.
	rc = az_iot_hub_client_get_client_id(&hub_client, mqtt_client_id_buffer, sizeof(mqtt_client_id_buffer), NULL);
	if (az_result_failed(rc))
	{
	  IOT_SAMPLE_LOG_ERROR("Failed to get MQTT client id: az_result return code 0x%08x.", rc);
	}
	// Set MQTT connection options.
	connectData.clientID.cstring = mqtt_client_id_buffer;
	connectData.username.cstring = mqtt_client_username_buffer;
	connectData.cleansession = false;
	connectData.keepAliveInterval = AZ_IOT_DEFAULT_MQTT_CONNECT_KEEPALIVE_SECONDS;

	if((rc = connect_to_azure_server_by_mqtt(&mqtt_client, &connectData, (char*)az_span_ptr(az_vars.hub_hostname), PNP_RETRY_INTERVAL_SEC)) != SUCCESS)
	{
		goto aziot_exit;
	}
	iot_hub_is_connect = true;
	IOT_SAMPLE_LOG_SUCCESS("Client connected to provisioning service.");

	// Messages received on the Methods topic will be commands to be invoked.
	if ((rc = MQTTSubscribe(&mqtt_client, AZ_IOT_HUB_CLIENT_METHODS_SUBSCRIBE_TOPIC, QOS1, messageArrivedFromIothub)) != SUCCESS) {
		IOT_SAMPLE_LOG_ERROR("Failed to subscribe to the Methods topic: MQTTClient return code %d.", rc);
	}
  

	// Messages received on the Twin Patch topic will be updates to the desired properties.
	if ((rc = MQTTSubscribe(&mqtt_client, AZ_IOT_HUB_CLIENT_TWIN_PATCH_SUBSCRIBE_TOPIC, QOS1, messageArrivedFromIothub)) != SUCCESS) {
		IOT_SAMPLE_LOG_ERROR("Failed to subscribe to the Twin Patch topic: MQTTClient return code %d.", rc);
	}
  

	// Messages received on Twin Response topic will be response statuses from the server.
	if ((rc = MQTTSubscribe(&mqtt_client, AZ_IOT_HUB_CLIENT_TWIN_RESPONSE_SUBSCRIBE_TOPIC, QOS1, messageArrivedFromIothub)) != SUCCESS) {
		IOT_SAMPLE_LOG_ERROR("Failed to subscribe to the Twin Response topic: MQTTClient return code %d.", rc);
	}

	IOT_SAMPLE_LOG_SUCCESS("Client subscribed to IoT Hub topics.");

	// Initializations
	rc = pnp_mqtt_message_init(&publish_message);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to initialize pnp_mqtt_message: az_result return code 0x%08x.", rc);
	}

	// We created a thread for telemetry so there will be two threads publishing data.
	// Therefore semaphore is needed to protect data.
	if(publish_sema == NULL){
		if ( ( publish_sema = xSemaphoreCreateCounting( PUBLISH_SEMA_POOL, 1 ) ) == NULL )
		{
			IOT_SAMPLE_LOG_ERROR("Failed to init semaphore for mqtt publish");
			goto aziot_exit;
		}
		IOT_SAMPLE_LOG_SUCCESS("Initialize semaphore for mqtt publish");
	}

	initialize_components();
	IOT_SAMPLE_LOG_SUCCESS("Client initialized all components.");

	send_device_twins_reported_property();
	
	//request_device_twin_document();
	IOT_SAMPLE_LOG("Client requesting device twin document from service.");

	// Get the Twin Document topic to publish the twin document request.
	rc = az_iot_hub_client_twin_document_get_publish_topic(
		&hub_client,
		pnp_mqtt_get_request_id(),
		publish_message.topic,
		publish_message.topic_length,
		NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to get the Twin Document topic: az_result return code 0x%08x.", rc);
	}

	// Publish the twin document request.
	publish_mqtt_message(publish_message.topic, AZ_SPAN_EMPTY, IOT_SAMPLE_MQTT_PUBLISH_QOS);
	IOT_SAMPLE_LOG(" "); // Formatting

	// Receive the response from the server.
	receive_mqtt_message();

	if(xTaskCreate(pnp_telemetry_thread, ((const char*)"pnp_telemetry_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(pnp_telemetry_thread) failed", __FUNCTION__);

	// Continue to receive commands or device twin messages while device is operational.
	while (iot_hub_is_connect && !is_message_error)
	{
		// Wait for any server messages.
		IOT_SAMPLE_LOG(" "); // Formatting
		IOT_SAMPLE_LOG("Waiting for command request or device twin message.\n");
		if((rc = receive_mqtt_message()) == FAILURE)
		{
			is_message_error = true;
		}
	}

aziot_exit:
	if(dps_is_connect || iot_hub_is_connect)
	{
	  	rc = MQTTDisconnect(&mqtt_client);
		if (rc != SUCCESS)
		{
			IOT_SAMPLE_LOG_ERROR("Failed to disconnect MQTT client: MQTTClient return code %d.", rc);
		}
		mqtt_network.disconnect(&mqtt_network);
		iot_hub_is_connect = false;
		dps_is_connect = false;
	}
	if(publish_sema != NULL)
	{
		vSemaphoreDelete(publish_sema);
	}
	vTaskDelete(NULL);
}


void example_azure_iot_rtk_pnp_x509(void)
{
	if(xTaskCreate(example_azure_iot_rtk_pnp_x509_thread, ((const char*)"example_azure_iot_rtk_pnp_x509_thread"), 8000, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_azure_iot_rtk_pnp_x509_thread) failed", __FUNCTION__);
}

#endif
