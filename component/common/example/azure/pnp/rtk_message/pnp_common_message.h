// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#ifndef PNP_COMMON_MESSAGE_H
#define PNP_COMMON_MESSAGE_H

void generate_dps_sas_key(void);

void generate_iot_hub_sas_key(void);

int publish_mqtt_message(const char* topic, az_span payload, int qos);

int receive_mqtt_message(void);


void parse_device_registration_status_message(
    char* topic,
    int topic_len,
    MQTTMessage const* message,
    az_iot_provisioning_client_register_response* out_register_response);


void handle_device_registration_status_message(
    az_iot_provisioning_client_register_response const* register_response,
    bool* ref_is_operation_complete);


int connect_to_azure_server_by_mqtt(MQTTClient* mqtt_client, MQTTPacket_connectData* connectData, char* hostname, int retry_interval);


#endif // PNP_COMMMON_MESSAGE_H
