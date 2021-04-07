#include "example_azure_iot_entry.h"
#ifdef EXAMPLE_AZURE_IOT_PROVISIONING

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

#define SAMPLE_TYPE AZIOT_PROVISIONING
#define SAMPLE_NAME AZIOT_PROVISIONING_SAMPLE

#define ID_SCOPE "[ID Scope]"	
#define REGISTRATION_ID "[Registration ID]"

#define X509CERTIFICATE \
"-----BEGIN CERTIFICATE-----""\n" \
"MIIBEzCBugIJAMamL5pVB3RHMAoGCCqGSM49BAMCMBIxEDAOBgNVBAMMB3JheW1v""\n" \
"...""\n" \
"PwH30gIhAJIGT8Y5AI5BygtYm7sgQY/yRccQfCxgI07TxBfnH10o""\n" \
"-----END CERTIFICATE-----""\n"

#define X509PRIVATEKEY \
"-----BEGIN EC PARAMETERS-----""\n" \
"...""\n" \
"-----END EC PARAMETERS-----""\n" \
"-----BEGIN EC PRIVATE KEY-----""\n" \
"MHcCAQEEIO7ekzAc/Mnyd/+zDDVPP5DNs2w8czHj0wbTtvVfa2wMoAoGCCqGSM49""\n" \
"...""\n" \
"V7WhqI6bNNkkzR2JfeM5nfT+QhyuUgXNew==""\n" \
"-----END EC PRIVATE KEY-----""\n"

#define MQTT_TIMEOUT_RECEIVE_MS (60 * 1000)
#define MQTT_TIMEOUT_DISCONNECT_MS (10 * 1000)
#define PROVISIONING_RETRY_INTERVAL_SEC 1

static iot_sample_variables az_vars;
static az_iot_provisioning_client provisioning_client;
static MQTTClient mqtt_client;
static Network mqtt_network;
static MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
static unsigned char mqtt_sendbuf[1024], mqtt_readbuf[1024];
bool is_operation_complete = false;

static void create_and_configure_mqtt_client(void)
{
	int rc;

	import_user_configuration(&az_vars, IOT_SAMPLE_PROVISIONING_ID_SCOPE, ID_SCOPE);
	import_user_configuration(&az_vars, IOT_SAMPLE_PROVISIONING_REGISTRATION_ID, REGISTRATION_ID);
	import_user_configuration(&az_vars, IOT_SAMPLE_DEVICE_X509_CERTIFICATE, X509CERTIFICATE);
	import_user_configuration(&az_vars, IOT_SAMPLE_DEVICE_X509_PRIVATE_KEY, X509PRIVATEKEY);
	
	// Check variables set by user for purposes of running sample.
	iot_sample_check_variables(SAMPLE_TYPE, SAMPLE_NAME, &az_vars);

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
		IOT_SAMPLE_LOG_ERROR(
			"Failed to initialize provisioning client: az_result return code 0x%08x.", rc);
	  }

	NetworkInit(&mqtt_network);
	mqtt_network.clientCA = (char*)az_span_ptr(az_vars.x509_certificate);
	mqtt_network.private_key = (char*)az_span_ptr(az_vars.x509_private_key);
	mqtt_network.use_ssl = 1;

	MQTTClientInit(&mqtt_client, &mqtt_network, 30000, mqtt_sendbuf, sizeof(mqtt_sendbuf), mqtt_readbuf, sizeof(mqtt_readbuf));
  
}

static void connect_mqtt_client_to_provisioning_service(void)
{
	char mqtt_client_username_buffer[128];
	
	// Get the MQTT client username.
	int rc = az_iot_provisioning_client_get_user_name(&provisioning_client, mqtt_client_username_buffer, sizeof(mqtt_client_username_buffer), NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to get MQTT client username: az_result return code 0x%08x.", rc);
	}

	// Get the MQTT client id used for the MQTT connection.
	char mqtt_client_id_buffer[128];
	rc = az_iot_provisioning_client_get_client_id(&provisioning_client, mqtt_client_id_buffer, sizeof(mqtt_client_id_buffer), NULL);
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
					
				if (NetworkConnect(mqtt_client.ipstack, PROVISIONING_GLOBAL_ENDPOINT, 8883) != 0) {
					break;
				}
				mqtt_printf(MQTT_INFO, "\"%s\" Connected", PROVISIONING_GLOBAL_ENDPOINT);
	
				if (MQTTConnect(&mqtt_client, &connectData) != 0) {
					break;
				}
				mqtt_printf(MQTT_INFO, "MQTT Connected");
			}
		} while (0);
	
		if (mqtt_client.isconnected) {
			break;
		}
	
		iot_sample_sleep_for_seconds(PROVISIONING_RETRY_INTERVAL_SEC);
	}
}

static void parse_device_registration_status_message(
    char* topic,
    int topic_len,
    MQTTMessage const* message,
    az_iot_provisioning_client_register_response* out_register_response)
{
	az_result rc;
	az_span const topic_span = az_span_create((uint8_t*)topic, topic_len);
	az_span const message_span = az_span_create((uint8_t*)message->payload, message->payloadlen);

	// Parse message and retrieve register_response info.
	rc = az_iot_provisioning_client_parse_received_topic_and_payload(&provisioning_client, topic_span, message_span, out_register_response);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Message from unknown topic: az_result return code 0x%08x.", rc);
		IOT_SAMPLE_LOG_AZ_SPAN("Topic:", topic_span);
	}
	IOT_SAMPLE_LOG_SUCCESS("Client received a valid topic response:");
	IOT_SAMPLE_LOG_AZ_SPAN("Topic:", topic_span);
	IOT_SAMPLE_LOG_AZ_SPAN("Payload:", message_span);
	IOT_SAMPLE_LOG("Status: %d", out_register_response->status);
}

static void send_operation_query_message(
    az_iot_provisioning_client_register_response const* register_response)
{
	int rc;

	// Get the Query Status topic to publish the query status request.
	char query_topic_buffer[256];
	rc = az_iot_provisioning_client_query_status_get_publish_topic(
		&provisioning_client,
		register_response->operation_id,
		query_topic_buffer,
		sizeof(query_topic_buffer),
		NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Unable to get query status publish topic: az_result return code 0x%08x.", rc);
	}

	// IMPORTANT: Wait the recommended retry-after number of seconds before query.
	IOT_SAMPLE_LOG("Querying after %d seconds...", register_response->retry_after_seconds);
	iot_sample_sleep_for_seconds(register_response->retry_after_seconds);
  
	// Set MQTT message options.
	MQTTMessage message;
	message.qos = IOT_SAMPLE_MQTT_PUBLISH_QOS;
	message.retained = 0;
	message.payload = NULL;
	message.payloadlen = 0;
  
	// Publish the register request.
	if ((rc = MQTTPublish(&mqtt_client, query_topic_buffer, &message)) != 0)
	{
		IOT_SAMPLE_LOG_ERROR("Failed to publish query status request: MQTTClient return code %d.", rc);
	}
}

static void handle_device_registration_status_message(
    az_iot_provisioning_client_register_response const* register_response,
    bool* ref_is_operation_complete)
{
	*ref_is_operation_complete = az_iot_provisioning_client_operation_complete(register_response->operation_status);

	// If operation is not complete, send query. On return, will loop to receive new operation
	// message.
	if (!*ref_is_operation_complete)
	{
		IOT_SAMPLE_LOG("Operation is still pending.");

		send_operation_query_message(register_response);
		IOT_SAMPLE_LOG_SUCCESS("Client sent operation query message.");
	}
	else // Operation is complete.
	{
		if (register_response->operation_status == AZ_IOT_PROVISIONING_STATUS_ASSIGNED) // Successful assignment
		{
			IOT_SAMPLE_LOG_SUCCESS("Device provisioned:");
			IOT_SAMPLE_LOG_AZ_SPAN("Hub Hostname:", register_response->registration_state.assigned_hub_hostname);
			IOT_SAMPLE_LOG_AZ_SPAN("Device Id:", register_response->registration_state.device_id);
			IOT_SAMPLE_LOG(" "); // Formatting
		}
		else // Unsuccessful assignment (unassigned, failed or disabled states)
		{
			IOT_SAMPLE_LOG_ERROR("Device provisioning failed:");
			IOT_SAMPLE_LOG("Registration state: %d", register_response->operation_status);
			IOT_SAMPLE_LOG("Last operation status: %d", register_response->status);
			IOT_SAMPLE_LOG_AZ_SPAN("Operation ID:", register_response->operation_id);
			IOT_SAMPLE_LOG("Error code: %u", register_response->registration_state.extended_error_code);
			IOT_SAMPLE_LOG_AZ_SPAN("Error message:", register_response->registration_state.error_message);
			IOT_SAMPLE_LOG_AZ_SPAN("Error timestamp:", register_response->registration_state.error_timestamp);
			IOT_SAMPLE_LOG_AZ_SPAN("Error tracking ID:", register_response->registration_state.error_tracking_id);
		}
	}
}

static void messageArrived(MessageData* data)
{
	IOT_SAMPLE_LOG_SUCCESS("Client received a message from the provisioning service.");
	
	// Parse registration status message.
	az_iot_provisioning_client_register_response register_response;
	parse_device_registration_status_message(data->topicName->lenstring.data, data->topicName->lenstring.len, data->message, &register_response);
	IOT_SAMPLE_LOG_SUCCESS("Client parsed registration status message.");
	
	handle_device_registration_status_message(&register_response, &is_operation_complete);

}


static void subscribe_mqtt_client_to_provisioning_service_topics(void)
{
	int rc;
	
	// Messages received on the Register topic will be registration responses from the server.

	mqtt_printf(MQTT_INFO, "Subscribe to Topic: %s", AZ_IOT_PROVISIONING_CLIENT_REGISTER_SUBSCRIBE_TOPIC);
	if ((rc = MQTTSubscribe(&mqtt_client, AZ_IOT_PROVISIONING_CLIENT_REGISTER_SUBSCRIBE_TOPIC, QOS1, messageArrived)) != SUCCESS)
	{
		IOT_SAMPLE_LOG_ERROR("Failed to subscribe to the Register topic: MQTTClient return code %d.", rc);
	}
}

static void register_device_with_provisioning_service(void)
{
	int rc;

	// Get the Register topic to publish the register request.
	char register_topic_buffer[128];
	rc = az_iot_provisioning_client_register_get_publish_topic(&provisioning_client, register_topic_buffer, sizeof(register_topic_buffer), NULL);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Failed to get the Register topic: az_result return code 0x%08x.", rc);
	}
	
	// Set MQTT message options.
	MQTTMessage message;
	message.qos = IOT_SAMPLE_MQTT_PUBLISH_QOS;
	message.retained = 0;
	message.payload = NULL;
	message.payloadlen = 0;

	// Publish the register request.
	if ((rc = MQTTPublish(&mqtt_client, register_topic_buffer, &message)) != 0)
	{
		IOT_SAMPLE_LOG_ERROR("Failed to publish Register request: MQTTClient return code %d.", rc);
	}
}



static void receive_device_registration_status_message(void)
{
	int rc;
	Timer timer;
	TimerInit(&timer);

	// Continue to parse incoming responses from the provisioning service until the device has been
	// successfully provisioned or an error occurs.
	do
	{
		IOT_SAMPLE_LOG(" "); // Formatting
		IOT_SAMPLE_LOG("Waiting for registration status message.\n");
	
		TimerCountdownMS(&timer, MQTT_TIMEOUT_RECEIVE_MS);

		memset(mqtt_client.readbuf, 0, mqtt_client.readbuf_size);
		rc = cycle(&mqtt_client, &timer);
		if (*mqtt_client.readbuf == 0x0) {
			mqtt_printf(MQTT_INFO, "Receive timeout\n");
		}else if(rc < 0){
			mqtt_printf(MQTT_INFO, "Return code from yield is %d\n", rc);
			break;
		}
	
		IOT_SAMPLE_LOG_SUCCESS("Client received a message from the provisioning service.");

	} while (!is_operation_complete); // Will loop to receive new operation message.
}


static void disconnect_mqtt_client_from_provisioning_service(void)
{
	int rc = MQTTDisconnect(&mqtt_client);
	if (rc != SUCCESS)
	{
		IOT_SAMPLE_LOG_ERROR("Failed to disconnect MQTT client: MQTTClient return code %d.", rc);
	}
	mqtt_network.disconnect(&mqtt_network);
}


/*
 * This sample registers a device with the Azure IoT Device Provisioning Service. It will wait to
 * receive the registration status before disconnecting. X509 self-certification is used.
 */
static void example_azure_iot_provisioning_thread(void* param)
{
	while (wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != SUCCESS) {
		vTaskDelay(1000);
	}

	create_and_configure_mqtt_client();
	IOT_SAMPLE_LOG_SUCCESS("Client created and configured.");

	connect_mqtt_client_to_provisioning_service();
	IOT_SAMPLE_LOG_SUCCESS("Client connected to provisioning service.");

	subscribe_mqtt_client_to_provisioning_service_topics();
	IOT_SAMPLE_LOG_SUCCESS("Client subscribed to provisioning service topics.");

	register_device_with_provisioning_service();
	IOT_SAMPLE_LOG_SUCCESS("Client registering with provisioning service.");

	receive_device_registration_status_message();
	IOT_SAMPLE_LOG_SUCCESS("Client received registration status message.");

	disconnect_mqtt_client_from_provisioning_service();
	IOT_SAMPLE_LOG_SUCCESS("Client disconnected from provisioning service.");

	vTaskDelete(NULL);
}


void example_azure_iot_provisioning(void)
{
	if(xTaskCreate(example_azure_iot_provisioning_thread, ((const char*)"example_azure_iot_provisioning_thread"), 8000, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_azure_iot_provisioning_thread) failed", __FUNCTION__);
}

#endif
