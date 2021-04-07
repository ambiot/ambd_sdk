#include "example_azure_iot_entry.h"
#ifdef EXAMPLE_AZURE_IOT_HUB_TWIN

// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

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

#include "example_azure_iot_common.h"

#define SAMPLE_TYPE AZIOT_HUB
#define SAMPLE_NAME AZIOT_HUB_TWIN_SAMPLE

#define HUB_HOSTNAME "[IoT Hub Name].azure-devices.net"	
#define HUB_DEVICE_ID "[Device ID]"

#define X509CERTIFICATE \
"-----BEGIN CERTIFICATE-----""\n" \
"MIICXzCCAgWgAwIBAgIJALmwdKzRWp0FMAoGCCqGSM49BAMCMIGLMQswCQYDVQQG""\n" \
"...""\n" \
"AiEAwIgsujX4+jkGvuJTnr74xpSWUxuJCPBUFmG/OHs4wdM=""\n" \
"-----END CERTIFICATE-----""\n"

#define X509PRIVATEKEY \
"-----BEGIN EC PARAMETERS-----""\n" \
"...""\n" \
"-----END EC PARAMETERS-----""\n" \
"-----BEGIN EC PRIVATE KEY-----""\n" \
"MHcCAQEEINO+QhrBdnUP36taC7VO6i0UNoBrbri8i8m3Jx/qIwkroAoGCCqGSM49""\n" \
"...""\n" \
"dpNJXSmXGMOJ5+6tUdkBuJ1gnxqgxj5rnw==""\n" \
"-----END EC PRIVATE KEY-----""\n"

#define MAX_TWIN_MESSAGE_COUNT 5
#define TWIN_RETRY_INTERVAL_SEC 1
#define MQTT_TIMEOUT_RECEIVE_MS (60 * 1000)
#define MQTT_TIMEOUT_DISCONNECT_MS (10 * 1000)

static az_span const twin_document_topic_request_id = AZ_SPAN_LITERAL_FROM_STR("get_twin");
static az_span const twin_patch_topic_request_id = AZ_SPAN_LITERAL_FROM_STR("reported_prop");
static az_span const version_name = AZ_SPAN_LITERAL_FROM_STR("$version");
static az_span const desired_device_count_property_name = AZ_SPAN_LITERAL_FROM_STR("device_count");
static int32_t device_count_value = 0;

static iot_sample_variables az_vars;
static az_iot_hub_client hub_client;
static MQTTClient mqtt_client;
static Network mqtt_network;
static MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
static unsigned char mqtt_sendbuf[1024], mqtt_readbuf[1024];
static int message_count = 0;
static bool message_receive_start = false;


static void create_and_configure_mqtt_client(void)
{
	int rc;

	import_user_configuration(&az_vars, IOT_SAMPLE_HUB_HOSTNAME, HUB_HOSTNAME);
	import_user_configuration(&az_vars, IOT_SAMPLE_HUB_DEVICE_ID, HUB_DEVICE_ID);
	import_user_configuration(&az_vars, IOT_SAMPLE_DEVICE_X509_CERTIFICATE, X509CERTIFICATE);
	import_user_configuration(&az_vars, IOT_SAMPLE_DEVICE_X509_PRIVATE_KEY, X509PRIVATEKEY);
	
	// Check variables set by user for purposes of running sample.
	iot_sample_check_variables(SAMPLE_TYPE, SAMPLE_NAME, &az_vars);

	// Initialize the hub client with the default connection options.
	rc = az_iot_hub_client_init(&hub_client, az_vars.hub_hostname, az_vars.hub_device_id, NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to initialize hub client: az_result return code 0x%08x.", rc);
	}

	NetworkInit(&mqtt_network);
	mqtt_network.clientCA = (char*)az_span_ptr(az_vars.x509_certificate);
	mqtt_network.private_key = (char*)az_span_ptr(az_vars.x509_private_key);
	mqtt_network.use_ssl = 1;

	MQTTClientInit(&mqtt_client, &mqtt_network, 30000, mqtt_sendbuf, sizeof(mqtt_sendbuf), mqtt_readbuf, sizeof(mqtt_readbuf));
  
}

static void connect_mqtt_client_to_iot_hub(void)
{
	int rc;
	char mqtt_client_username_buffer[128];
	char mqtt_client_id_buffer[128];

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

	// Connect to iot hub device
	while (1) {
		do {
			if (mqtt_client.isconnected == 0) {
				  
				if (NetworkConnect(mqtt_client.ipstack, (char*)az_span_ptr(az_vars.hub_hostname), 8883) != 0) {
					break;
				}
				mqtt_printf(MQTT_INFO, "\"%s\" Connected", (char*)az_span_ptr(az_vars.hub_hostname));
  
				if (MQTTConnect(&mqtt_client, &connectData) != 0) {
					break;
				}
				mqtt_printf(MQTT_INFO, "MQTT Connected");
			}
		} while (0);
  
		if (mqtt_client.isconnected) {
			break;
		}
  
    	iot_sample_sleep_for_seconds(TWIN_RETRY_INTERVAL_SEC);
	}

}



static void get_device_twin_document(void)
{
	int rc;

	IOT_SAMPLE_LOG("Client requesting device twin document from service.");

	// Get the Twin Document topic to publish the twin document request.
	char twin_document_topic_buffer[128];
	rc = az_iot_hub_client_twin_document_get_publish_topic(
		&hub_client,
		twin_document_topic_request_id,
		twin_document_topic_buffer,
		sizeof(twin_document_topic_buffer),
		NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to get the Twin Document topic: az_result return code 0x%08x.", rc);
		return;
	}

	MQTTMessage message;
	message.qos = IOT_SAMPLE_MQTT_PUBLISH_QOS;
	message.retained = 0;
	message.payload = NULL;
	message.payloadlen = 0;
	
	if ((rc = MQTTPublish(&mqtt_client, twin_document_topic_buffer, &message)) != 0)
	{
		IOT_SAMPLE_LOG_ERROR("Failed to publish the Twin Document request: MQTTClient return code %d.", rc);
		return;
	}
}

static bool parse_desired_device_count_property(
    az_span message_span,
    int32_t* out_parsed_device_count)
{
	char const* const log = "Failed to parse for desired `%.*s` property";
	az_span property = desired_device_count_property_name;

	bool property_found = false;
	*out_parsed_device_count = 0;

	// Parse message_span.
	az_json_reader jr;
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_init(&jr, message_span, NULL), log, property);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_next_token(&jr), log, property);
	if (jr.token.kind != AZ_JSON_TOKEN_BEGIN_OBJECT)
	{
		IOT_SAMPLE_LOG("`%.*s` property was not found in desired property response.", az_span_size(property), az_span_ptr(property));
		return false;
	}

	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_next_token(&jr), log, property);
	while (!property_found && (jr.token.kind != AZ_JSON_TOKEN_END_OBJECT))
	{
		if (az_json_token_is_text_equal(&jr.token, desired_device_count_property_name))
		{
			// Move to the value token.
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_next_token(&jr), log, property);
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_token_get_int32(&jr.token, out_parsed_device_count), log, property);
			property_found = true;
		}
		else if (az_json_token_is_text_equal(&jr.token, version_name))
		{
			break;
		}
		else
		{
			IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_skip_children(&jr), log, property);
		}
		IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_reader_next_token(&jr), log, property);
	}

	if (property_found)
	{
		IOT_SAMPLE_LOG("Parsed desired `%.*s`: %d", az_span_size(property), az_span_ptr(property), *out_parsed_device_count);
	}
	else
	{
		IOT_SAMPLE_LOG("`%.*s` property was not found in desired property response.", az_span_size(property), az_span_ptr(property));
		return false;
	}

	return true;
}


static void build_reported_property(
    az_span reported_property_payload,
    az_span* out_reported_property_payload)
{
	char const* const log = "Failed to build reported property payload";

	az_json_writer jw;
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_init(&jw, reported_property_payload, NULL), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_begin_object(&jw), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_property_name(&jw, desired_device_count_property_name), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_int32(&jw, device_count_value), log);
	IOT_SAMPLE_EXIT_IF_AZ_FAILED(az_json_writer_append_end_object(&jw), log);

	*out_reported_property_payload = az_json_writer_get_bytes_used_in_destination(&jw);
}

static void send_reported_property(void)
{
	int rc;

	IOT_SAMPLE_LOG("Client sending reported property to service.");

	// Get the Twin Patch topic to publish a reported property update.
	char twin_patch_topic_buffer[128];
	rc = az_iot_hub_client_twin_patch_get_publish_topic(
		&hub_client,
		twin_patch_topic_request_id,
		twin_patch_topic_buffer,
		sizeof(twin_patch_topic_buffer),
		NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to get the Twin Patch topic: az_result return code 0x%08x.", rc);
		return;
	}

	// Build the updated reported property message.
	char reported_property_payload_buffer[128];
	az_span reported_property_payload = AZ_SPAN_FROM_BUFFER(reported_property_payload_buffer);
	build_reported_property(reported_property_payload, &reported_property_payload);

	MQTTMessage message;

	message.qos = IOT_SAMPLE_MQTT_PUBLISH_QOS;
	message.retained = 0;
	message.payload = (void*)az_span_ptr(reported_property_payload);
	message.payloadlen = az_span_size(reported_property_payload);
	
	if ((rc = MQTTPublish(&mqtt_client, twin_patch_topic_buffer, &message)) != 0)
	{
		IOT_SAMPLE_LOG_ERROR("Failed to publish the Twin Patch reported property update: MQTTClient return code %d.",rc);
		return;
	}
	IOT_SAMPLE_LOG_SUCCESS("Client published the Twin Patch reported property message.");
	IOT_SAMPLE_LOG_AZ_SPAN("Payload:", reported_property_payload);
}

static void parse_device_twin_message(
    char* topic,
    int topic_len,
    MQTTMessage const* message,
    az_iot_hub_client_twin_response* out_twin_response)
{
  az_span const topic_span = az_span_create((uint8_t*)topic, topic_len);
  az_span const message_span = az_span_create((uint8_t*)message->payload, message->payloadlen);
  // Parse message and retrieve twin_response info.
  az_result rc = az_iot_hub_client_twin_parse_received_topic(&hub_client, topic_span, out_twin_response);
  if (az_result_failed(rc))
  {
    IOT_SAMPLE_LOG_ERROR("Message from unknown topic: az_result return code 0x%08x.", rc);
    IOT_SAMPLE_LOG_AZ_SPAN("Topic:", topic_span);
	return;
  }
  IOT_SAMPLE_LOG_SUCCESS("Client received a valid topic response.");
  IOT_SAMPLE_LOG_AZ_SPAN("Topic:", topic_span);
  IOT_SAMPLE_LOG_AZ_SPAN("Payload:", message_span);
  IOT_SAMPLE_LOG("Status: %d", out_twin_response->status);
}

static void update_device_count_property(int32_t device_count)
{
	device_count_value = device_count;
	IOT_SAMPLE_LOG_SUCCESS(
		"Client updated `%.*s` locally to %d.",
		az_span_size(desired_device_count_property_name),
		az_span_ptr(desired_device_count_property_name),
		device_count_value);
}

static bool receive_device_twin_message(void)
{
	int rc;
	Timer timer;
	TimerInit(&timer);
	bool message_received = true;

	IOT_SAMPLE_LOG(" "); // Formatting
	IOT_SAMPLE_LOG("Waiting for device twin message.\n");

	TimerCountdownMS(&timer, MQTT_TIMEOUT_RECEIVE_MS);
	
	memset(mqtt_client.readbuf, 0, mqtt_client.readbuf_size);
	rc = cycle(&mqtt_client, &timer);
	if (*mqtt_client.readbuf == 0x0) {
		mqtt_printf(MQTT_INFO, "Receive timeout\n");
		return !message_received;
	}else if(rc < 0){
		mqtt_printf(MQTT_INFO, "Return code from yield is %d\n", rc);
		return !message_received;
	}

	return message_received;
}

static void handle_device_twin_message(
    MQTTMessage const* message,
    az_iot_hub_client_twin_response const* twin_response)
{
	az_span const message_span = az_span_create((uint8_t*)message->payload, message->payloadlen);

	// Invoke appropriate action per response type (3 types only).
	switch (twin_response->response_type)
	{
		case AZ_IOT_HUB_CLIENT_TWIN_RESPONSE_TYPE_GET:
			IOT_SAMPLE_LOG("Message Type: GET");
			break;

		case AZ_IOT_HUB_CLIENT_TWIN_RESPONSE_TYPE_REPORTED_PROPERTIES:
			IOT_SAMPLE_LOG("Message Type: Reported Properties");
			break;

		case AZ_IOT_HUB_CLIENT_TWIN_RESPONSE_TYPE_DESIRED_PROPERTIES:
			IOT_SAMPLE_LOG("Message Type: Desired Properties");

			// Parse for the device count property.
			int32_t desired_device_count;
			if (parse_desired_device_count_property(message_span, &desired_device_count))
			{
				IOT_SAMPLE_LOG(" "); // Formatting

				// Update device count locally and report update to server.
				update_device_count_property(desired_device_count);
				send_reported_property();
				(void)receive_device_twin_message();
			}
			break;
	}
}


static void messageArrived(MessageData* data)
{
	IOT_SAMPLE_LOG_SUCCESS("Client received a device twin message from the service.");
	
	// Parse device twin message.
	az_iot_hub_client_twin_response twin_response;
	parse_device_twin_message(data->topicName->lenstring.data, data->topicName->lenstring.len, data->message, &twin_response);
	IOT_SAMPLE_LOG_SUCCESS("Client parsed device twin message.");
	
	handle_device_twin_message(data->message, &twin_response);

	if(message_receive_start) ++message_count;
}

static void subscribe_mqtt_client_to_iot_hub_topics(void)
{
	int rc;
	
	// Messages received on the Twin Patch topic will be updates to the desired properties.
	mqtt_printf(MQTT_INFO, "Subscribe to Topic: %s", AZ_IOT_HUB_CLIENT_TWIN_PATCH_SUBSCRIBE_TOPIC);
	if ((rc = MQTTSubscribe(&mqtt_client, AZ_IOT_HUB_CLIENT_TWIN_PATCH_SUBSCRIBE_TOPIC, QOS1, messageArrived)) != SUCCESS) {
		IOT_SAMPLE_LOG_ERROR("Failed to subscribe to the Twin Patch topic: MQTTClient return code %d.", rc);
	}
	
	// Messages received on Twin Response topic will be response statuses from the server.
	mqtt_printf(MQTT_INFO, "Subscribe to Topic: %s", AZ_IOT_HUB_CLIENT_TWIN_RESPONSE_SUBSCRIBE_TOPIC);
	if ((rc = MQTTSubscribe(&mqtt_client, AZ_IOT_HUB_CLIENT_TWIN_RESPONSE_SUBSCRIBE_TOPIC, QOS1, messageArrived)) != SUCCESS) {
		IOT_SAMPLE_LOG_ERROR("Failed to subscribe to the Twin Response topic: MQTTClient return code %d.", rc);
	}
}

static void send_and_receive_device_twin_messages(void)
{
	get_device_twin_document();
	(void)receive_device_twin_message();
	IOT_SAMPLE_LOG(" "); // Formatting

	send_reported_property();
	(void)receive_device_twin_message();

	message_receive_start = true;

	// Continue until max # messages received or timeout occurs.
	while(message_count < MAX_TWIN_MESSAGE_COUNT)
	{
		if (!receive_device_twin_message())
		{
			return;
		}
	}

	IOT_SAMPLE_LOG_SUCCESS("Client received messages.");
}


static void disconnect_mqtt_client_from_iot_hub(void)
{
	int rc = MQTTDisconnect(&mqtt_client);
	if (rc != SUCCESS)
	{
		IOT_SAMPLE_LOG_ERROR("Failed to disconnect MQTT client: MQTTClient return code %d.", rc);
	}
	mqtt_network.disconnect(&mqtt_network);
}

/*
 * This sample utilizes the Azure IoT Hub to get the device twin document, send a reported property
 * message, and receive up to 5 desired property messages. If a timeout occurs while waiting for a
 * message from the Azure IoT Hub, the sample will exit. Upon receiving a desired property message,
 * the sample will update the twin property locally and send a reported property message back to the
 * service. X509 self-certification is used.
 *
 * A property named `device_count` is supported for this sample. To send a device twin desired
 * property message, select your device's Device Twin tab in the Azure Portal of your IoT Hub. Add
 * the property `device_count` along with a corresponding value to the `desired` section of the
 * JSON. Select Save to update the twin document and send the twin message to the device.
 *
 * {
 *   "properties": {
 *     "desired": {
 *       "device_count": 42,
 *     }
 *   }
 * }
 *
 * No other property names sent in a desired property message are supported. If any are sent, the
 * IOT_SAMPLE_LOG will report there is nothing to update.
 */
static void example_azure_iot_hub_twin_thread(void* param)
{
	while (wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != SUCCESS) {
		vTaskDelay(1000);
	}
	
	create_and_configure_mqtt_client();
	IOT_SAMPLE_LOG_SUCCESS("Client created and configured.");

	connect_mqtt_client_to_iot_hub();
	IOT_SAMPLE_LOG_SUCCESS("Client connected to IoT Hub.");

	subscribe_mqtt_client_to_iot_hub_topics();
	IOT_SAMPLE_LOG_SUCCESS("Client subscribed to IoT Hub topics.");

	send_and_receive_device_twin_messages();

	disconnect_mqtt_client_from_iot_hub();
	IOT_SAMPLE_LOG_SUCCESS("Client disconnected from IoT Hub.");
  
	vTaskDelete(NULL);
}

void example_azure_iot_hub_twin(void)
{
	if(xTaskCreate(example_azure_iot_hub_twin_thread, ((const char*)"example_azure_iot_hub_twin_thread"), 8000, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_azure_iot_hub_twin_thread) failed", __FUNCTION__);
}

#endif
