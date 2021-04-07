#include "../../example_azure_iot_entry.h"
#if defined(EXAMPLE_AZURE_IOT_RTK_PNP_SAS) || defined(EXAMPLE_AZURE_IOT_RTK_PNP_X509)

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

#include "../../example_azure_iot_common.h"

#include "../pnp_mqtt_message.h"
#include "../pnp_protocol.h"

#include "../rtk_component/pnp_audio.h"
#include "../rtk_component/pnp_bluetooth.h"
#include "../rtk_component/pnp_device_info.h"
#include "../rtk_component/pnp_gpio.h"
#include "../rtk_component/pnp_lcd.h"
#include "../rtk_component/pnp_memory.h"
#include "../rtk_component/pnp_system.h"
#include "../rtk_component/pnp_video.h"
#include "../rtk_component/pnp_wireless.h"

#include "pnp_common_message.h"

extern iot_sample_variables az_vars;
extern az_iot_provisioning_client provisioning_client;
extern az_iot_hub_client hub_client;
extern MQTTClient mqtt_client;

extern char sas_signature_buffer[128];
extern char sas_base64_encoded_signed_signature_buffer[128];
extern char mqtt_password_buffer[256];

extern char provisioned_device_hub_hostname[100];
extern char provisioned_device_id[100];

void generate_dps_sas_key(void)
{
	az_result rc;

	// Create the POSIX expiration time from input minutes.
	uint64_t sas_duration = iot_sample_get_epoch_expiration_time_from_minutes(az_vars.sas_key_duration_minutes);

	// Get the signature which will be signed with the decoded key.
	az_span sas_signature = AZ_SPAN_FROM_BUFFER(sas_signature_buffer);
	rc = az_iot_provisioning_client_sas_get_signature(&provisioning_client, sas_duration, sas_signature, &sas_signature);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Could not get the signature for SAS key: az_result return code 0x%08x.", rc);
    }

	// Generate the encoded, signed signature (b64 encoded, HMAC-SHA256 signing).
  	az_span sas_base64_encoded_signed_signature = AZ_SPAN_FROM_BUFFER(sas_base64_encoded_signed_signature_buffer);
	iot_sample_generate_sas_base64_encoded_signed_signature(
		az_vars.provisioning_sas_key,
		sas_signature,
		sas_base64_encoded_signed_signature,
		&sas_base64_encoded_signed_signature);

	// Get the resulting MQTT password, passing the base64 encoded, HMAC signed bytes.
	size_t mqtt_password_length;
	rc = az_iot_provisioning_client_sas_get_password(
		&provisioning_client,
		sas_base64_encoded_signed_signature,
		sas_duration,
		AZ_SPAN_EMPTY,
		mqtt_password_buffer,
		sizeof(mqtt_password_buffer),
		&mqtt_password_length);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Could not get the password: az_result return code 0x%08x.", rc);
    }
}

void generate_iot_hub_sas_key(void)
{

	az_result rc;
	// Create the POSIX expiration time from input minutes.
	uint64_t sas_duration = iot_sample_get_epoch_expiration_time_from_minutes(az_vars.sas_key_duration_minutes);
  

	// Get the signature that will later be signed with the decoded key.
	az_span sas_signature = AZ_SPAN_FROM_BUFFER(sas_signature_buffer);
	rc = az_iot_hub_client_sas_get_signature(
		&hub_client, sas_duration, sas_signature, &sas_signature);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Could not get the signature for SAS key: az_result return code 0x%08x.", rc);
	}
  

	// Generate the encoded, signed signature (b64 encoded, HMAC-SHA256 signing).
	az_span sas_base64_encoded_signed_signature = AZ_SPAN_FROM_BUFFER(sas_base64_encoded_signed_signature_buffer);
	iot_sample_generate_sas_base64_encoded_signed_signature(
		az_vars.hub_sas_key,
		sas_signature,
		sas_base64_encoded_signed_signature,
		&sas_base64_encoded_signed_signature);
  
	// Get the resulting MQTT password, passing the base64 encoded, HMAC signed bytes.
	size_t mqtt_password_length;
	rc = az_iot_hub_client_sas_get_password(
		&hub_client,
		sas_duration,
		sas_base64_encoded_signed_signature,
		AZ_SPAN_EMPTY,
		mqtt_password_buffer,
		sizeof(mqtt_password_buffer),
		&mqtt_password_length);
	if (az_result_failed(rc))
	{
		IOT_SAMPLE_LOG_ERROR("Could not get the password: az_result return code 0x%08x.", rc);
	}
}


int publish_mqtt_message(const char* topic, az_span payload, int qos)
{

	int rc;
	MQTTMessage message;

	message.qos = (enum QoS)qos;
	message.retained = 0;
	message.payload = (void*)az_span_ptr(payload);
	message.payloadlen = az_span_size(payload);
  
	if ((rc = MQTTPublish(&mqtt_client, topic, &message)) != 0)
	{
		IOT_SAMPLE_LOG_ERROR("Failed to publish message: MQTTClient return code %d", rc);
		return FAILURE;
	}
	return SUCCESS;
}

int receive_mqtt_message(void)
{
	static int8_t timeout_counter;
	int rc;
	Timer timer;
	TimerInit(&timer);

	TimerCountdownMS(&timer, PNP_MQTT_TIMEOUT_RECEIVE_MS);

	memset(mqtt_client.readbuf, 0, mqtt_client.readbuf_size);
	rc = cycle(&mqtt_client, &timer);
	if (*mqtt_client.readbuf == 0x0) {
		if (PNP_MQTT_TIMEOUT_RECEIVE_MAX_MESSAGE_COUNT > 0 && ++timeout_counter >= PNP_MQTT_TIMEOUT_RECEIVE_MAX_MESSAGE_COUNT){
			IOT_SAMPLE_LOG("Receive message timeout expiration count of %d reached.", PNP_MQTT_TIMEOUT_RECEIVE_MAX_MESSAGE_COUNT);
			return FAILURE;
		}
	}else if(rc < 0){
    	IOT_SAMPLE_LOG_ERROR("Failed to receive message: MQTTClient return code %d.", rc);
		return FAILURE;
	}
	return SUCCESS;

}

void parse_device_registration_status_message(
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

void handle_device_registration_status_message(
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
			memcpy(provisioned_device_hub_hostname, az_span_ptr(register_response->registration_state.assigned_hub_hostname), az_span_size(register_response->registration_state.assigned_hub_hostname));
			memcpy(provisioned_device_id, az_span_ptr(register_response->registration_state.device_id), az_span_size(register_response->registration_state.device_id));
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

int connect_to_azure_server_by_mqtt(MQTTClient* mqtt_client, MQTTPacket_connectData* connectData, char* hostname, int retry_interval)
{
	int rc = FAILURE;
	// Connect to server
	while (1) {
		do {
			if (mqtt_client->isconnected == 0) {
				
				//only support secured mqtt port 8883
				if (NetworkConnect(mqtt_client->ipstack, hostname, 8883) != 0) {
					break;
				}
				mqtt_printf(MQTT_INFO, "\"%s\" Connected", hostname);
	  
				if (MQTTConnect(mqtt_client, connectData) != 0) {
					break;
				}
				mqtt_printf(MQTT_INFO, "MQTT Connected");
			}
		} while (0);
	  
		if (mqtt_client->isconnected) {
			rc = SUCCESS;
			break;
		}
	  
		iot_sample_sleep_for_seconds(retry_interval);
	}
	return rc;
}

#endif
