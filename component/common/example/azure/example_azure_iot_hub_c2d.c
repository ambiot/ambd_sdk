#include "example_azure_iot_entry.h"
#ifdef EXAMPLE_AZURE_IOT_HUB_C2D

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
#define SAMPLE_NAME AZIOT_HUB_C2D_SAMPLE

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

#define MAX_C2D_MESSAGE_COUNT 5
#define C2D_RETRY_INTERVAL_SEC 1
#define MQTT_TIMEOUT_RECEIVE_MS (60 * 1000)
#define MQTT_TIMEOUT_DISCONNECT_MS (10 * 1000)

static iot_sample_variables az_vars;
static az_iot_hub_client hub_client;
static MQTTClient mqtt_client;
static Network mqtt_network;
static MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
static unsigned char mqtt_sendbuf[1024], mqtt_readbuf[1024];
static int message_count = 0;

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
  
    	iot_sample_sleep_for_seconds(C2D_RETRY_INTERVAL_SEC);
	}

}

static void parse_c2d_message(
	char* topic,
	int topic_len,
	MQTTMessage const* message,
	az_iot_hub_client_c2d_request* out_c2d_request)
{
	az_span const topic_span = az_span_create((uint8_t*)topic, topic_len);
	az_span const message_span = az_span_create((uint8_t*)message->payload, message->payloadlen);

	// Parse message and retrieve c2d_request info.
	az_result rc = az_iot_hub_client_c2d_parse_received_topic(&hub_client, topic_span, out_c2d_request);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Message from unknown topic: az_result return code 0x%08x.", rc);
		IOT_SAMPLE_LOG_AZ_SPAN("Topic:", topic_span);
		return;
	}
	IOT_SAMPLE_LOG_SUCCESS("Client received a valid topic response.");
	IOT_SAMPLE_LOG_AZ_SPAN("Topic:", topic_span);
	IOT_SAMPLE_LOG_AZ_SPAN("Payload:", message_span);
}


static void messageArrived(MessageData* data)
{
	IOT_SAMPLE_LOG_SUCCESS("Message #%d: Client received a C2D message from the service.", message_count + 1);
	
	// Parse C2D message
	az_iot_hub_client_c2d_request c2d_request;
	parse_c2d_message(data->topicName->lenstring.data, data->topicName->lenstring.len, data->message, &c2d_request);
	IOT_SAMPLE_LOG_SUCCESS("Client parsed C2D message.");
	
	++message_count;
}

static void subscribe_mqtt_client_to_iot_hub_topics(void)
{
	int rc;
	
	// Messages received on the C2D topic will be cloud-to-device messages.
	mqtt_printf(MQTT_INFO, "Subscribe to Topic: %s", AZ_IOT_HUB_CLIENT_C2D_SUBSCRIBE_TOPIC);
	if ((rc = MQTTSubscribe(&mqtt_client, AZ_IOT_HUB_CLIENT_C2D_SUBSCRIBE_TOPIC, QOS1, messageArrived)) != SUCCESS) 
	{
		IOT_SAMPLE_LOG_ERROR("Failed to subscribe to the C2D topic: MQTTClient return code %d.", rc);
	}
}

static void receive_c2d_messages(void)
{
	int rc;
	Timer timer;
	TimerInit(&timer);

	// Continue until max # messages received or timeout expires.
	while(message_count < MAX_C2D_MESSAGE_COUNT)
	{
		IOT_SAMPLE_LOG(" "); // Formatting
    	IOT_SAMPLE_LOG("Waiting for C2D message.\n");

		TimerCountdownMS(&timer, MQTT_TIMEOUT_RECEIVE_MS);
		
		memset(mqtt_client.readbuf, 0, mqtt_client.readbuf_size);
		rc = cycle(&mqtt_client, &timer);
		if (*mqtt_client.readbuf == 0x0) {
			mqtt_printf(MQTT_INFO, "Receive timeout\n");
		}else if(rc < 0){
			mqtt_printf(MQTT_INFO, "Return code from yield is %d\n", rc);
			break;
		}
	}

	IOT_SAMPLE_LOG(" "); // Formatting
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
 * This sample receives incoming cloud-to-device (C2D) messages sent from the Azure IoT Hub to the
 * device. It will successfully receive up to MAX_C2D_MESSAGE_COUNT messages sent from the service.
 * If a timeout occurs of TIMEOUT_MQTT_RECEIVE_MS while waiting for a message, the sample will exit.
 * X509 self-certification is used.
 *
 * To send a C2D message, select your device's Message to Device tab in the Azure Portal for your
 * IoT Hub. Enter a message in the Message Body and select Send Message.
 */
static void example_azure_iot_hub_c2d_thread(void* param)
{
	while (wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != SUCCESS) {
		vTaskDelay(1000);
	}

	create_and_configure_mqtt_client();
	IOT_SAMPLE_LOG_SUCCESS("Client created and configured.");

	connect_mqtt_client_to_iot_hub();
	IOT_SAMPLE_LOG_SUCCESS("Client connected to IoT Hub.");

	subscribe_mqtt_client_to_iot_hub_topics();
	IOT_SAMPLE_LOG_SUCCESS("Client subscribed to IoT Hub topics and is ready to receive C2D messages.");

	receive_c2d_messages();

	disconnect_mqtt_client_from_iot_hub();
	IOT_SAMPLE_LOG_SUCCESS("Client disconnected from IoT Hub.");

	vTaskDelete(NULL);
}

void example_azure_iot_hub_c2d(void)
{
	if(xTaskCreate(example_azure_iot_hub_c2d_thread, ((const char*)"example_azure_iot_hub_c2d_thread"), 8000, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_azure_iot_hub_c2d_thread) failed", __FUNCTION__);
}

#endif
