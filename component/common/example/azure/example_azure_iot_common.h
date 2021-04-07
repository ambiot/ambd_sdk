// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#ifndef EXAMPLE_AZURE_IOT_COMMON_H
#define EXAMPLE_AZURE_IOT_COMMON_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "MQTTClient.h"
#include <sntp/sntp.h>

#include <azure/az_core.h>

#define PROVISIONING_GLOBAL_ENDPOINT "global.azure-devices-provisioning.net"
#define IOT_SAMPLE_SAS_KEY_DURATION_TIME_DIGITS 4
#define IOT_SAMPLE_MQTT_PUBLISH_QOS QOS0

//
// Logging
//
#define IOT_SAMPLE_LOG_ERROR(...)                                               \
    do                                                                          \
    {                                                                           \
        (void)printf("ERROR:\t\t%s:%s():%d: ", __FILE__, __func__, __LINE__);   \
        (void)printf(__VA_ARGS__);                                              \
        (void)printf("\n\r");                                                   \
    } while (0)

#define IOT_SAMPLE_LOG_SUCCESS(...) \
    do                              \
    {                               \
        (void)printf("SUCCESS:\t"); \
        (void)printf(__VA_ARGS__);  \
        (void)printf("\n\r");       \
    } while (0)

#define IOT_SAMPLE_LOG(...)         \
    do                              \
    {                               \
        (void)printf("\t\t");       \
        (void)printf(__VA_ARGS__);  \
        (void)printf("\n\r");       \
    } while (0)

#define IOT_SAMPLE_LOG_AZ_SPAN(span_description, span)                              \
    do                                                                              \
    {                                                                               \
        (void)printf("\t\t%s ", span_description);                                  \
        (void)printf("%.*s", (size_t)az_span_size(span), (char*)az_span_ptr(span)); \
		(void)printf("\n\r");                                                       \
    } while (0)

#define IOT_SAMPLE_PRECONDITION_NOT_NULL(arg)           \
    do                                                  \
    {                                                   \
        if ((arg) == NULL)                              \
        {                                               \
            IOT_SAMPLE_LOG_ERROR("Pointer is NULL.");   \
        }                                               \
    } while (0)

//
// Error handling
//
// Note: Only handles a single variadic parameter of type char const*, or two variadic parameters of
// type char const* and az_span.
void build_error_message(char* out_full_message, char const* const error_message, ...);
bool get_az_span(az_span* out_span, char const* const error_message, ...);
#define IOT_SAMPLE_EXIT_IF_AZ_FAILED(azfn, ...)                                                     \
    do                                                                                              \
        {                                                                                           \
        az_result const result = (azfn);                                                            \
                                                                                                    \
        if (az_result_failed(result))                                                               \
        {                                                                                           \
            char full_message[256];                                                                 \
            build_error_message(full_message, __VA_ARGS__);                                         \
                                                                                                    \
            az_span span;                                                                           \
            bool has_az_span = get_az_span(&span, __VA_ARGS__, AZ_SPAN_EMPTY);                      \
            if (has_az_span)                                                                        \
            {                                                                                       \
                IOT_SAMPLE_LOG_ERROR(full_message, az_span_size(span), az_span_ptr(span), result);  \
            }                                                                                       \
            else                                                                                    \
            {                                                                                       \
                IOT_SAMPLE_LOG_ERROR(full_message, result);                                         \
            }                                                                                       \
        }                                                                                           \
    } while (0)

typedef struct
{
	az_span hub_device_id;
	az_span hub_hostname;
	az_span hub_sas_key;
	az_span provisioning_id_scope;
	az_span provisioning_registration_id;
	az_span provisioning_sas_key;
	az_span x509_certificate;
	az_span x509_private_key;
	uint32_t sas_key_duration_minutes;
} iot_sample_variables;

typedef enum
{
	AZIOT_HUB,
	AZIOT_PROVISIONING
} iot_sample_type;

typedef enum
{
	IOT_SAMPLE_HUB_HOSTNAME,
	IOT_SAMPLE_PROVISIONING_ID_SCOPE,
	IOT_SAMPLE_HUB_DEVICE_ID,
	IOT_SAMPLE_PROVISIONING_REGISTRATION_ID,
	IOT_SAMPLE_HUB_SAS_KEY,
	IOT_SAMPLE_PROVISIONING_SAS_KEY,
	IOT_SAMPLE_SAS_KEY_DURATION_MINUTES,
	IOT_SAMPLE_DEVICE_X509_CERTIFICATE,
	IOT_SAMPLE_DEVICE_X509_PRIVATE_KEY
} iot_sample_variable_name;


typedef enum
{
	AZIOT_HUB_C2D_SAMPLE,
	AZIOT_HUB_METHODS_SAMPLE,
	AZIOT_HUB_PNP_COMPONENT_SAMPLE,
	AZIOT_HUB_PNP_SAMPLE,
	AZIOT_HUB_SAS_TELEMETRY_SAMPLE,
	AZIOT_HUB_TELEMETRY_SAMPLE,
	AZIOT_HUB_TWIN_SAMPLE,
	AZIOT_PROVISIONING_SAMPLE,
	AZIOT_PROVISIONING_SAS_SAMPLE,
	AZIOT_872XD_PNP_SAMPLE,
	AZIOT_872XD_PNP_SAS_SAMPLE
} iot_sample_name;

extern bool is_device_operational;
extern int cycle(MQTTClient* c, Timer* timer);

/*
 * @brief Import user configuration for the sample.
 *
 * @param[in] az_vars A pointer to the struct containing all read-in environment variables.
 * @param[in] name The enumerated name of the user import variable.
 * @param[in] value The value of the user import variable.
 * @param[out] out_env_vars A pointer to the struct containing all read-in environment variables.
 */
bool import_user_configuration(
	iot_sample_variables* az_vars, 
	iot_sample_variable_name name, 
	const char *value);


/*
 * @brief Reads in environment variables set by user for purposes of running sample.
 *
 * @param[in] type The enumerated type of the sample.
 * @param[in] name The enumerated name of the sample.
 * @param[in] out_env_vars A pointer to the struct containing all read-in environment variables.
 */
void iot_sample_check_variables(
	iot_sample_type type,
	iot_sample_name name,
	iot_sample_variables* az_vars);

/*
 * @brief Sleep for given seconds.
 *
 * @param[in] seconds Number of seconds to sleep.
 */
void iot_sample_sleep_for_seconds(uint32_t seconds);

/*
 * @brief Return total seconds passed including supplied minutes.
 *
 * @param[in] minutes Number of minutes to include in total seconds returned.
 *
 * @return Total time in seconds.
 */
int64_t iot_sample_get_epoch_expiration_time_from_minutes(uint32_t minutes);

/*
 * @brief Generate the base64 encoded and signed signature using HMAC-SHA256 signing.
 *
 * @param[in] sas_base64_encoded_key An #az_span containing the SAS key that will be used for
 * signing.
 * @param[in] sas_signature An #az_span containing the signature.
 * @param[in] sas_base64_encoded_signed_signature An #az_span with sufficient capacity to hold the
 * encoded signed signature.
 * @param[out] out_sas_base64_encoded_signed_signature A pointer to the #az_span containing the
 * encoded signed signature.
 */
void iot_sample_generate_sas_base64_encoded_signed_signature(
    az_span sas_base64_encoded_key,
    az_span sas_signature,
    az_span sas_base64_encoded_signed_signature,
    az_span* out_sas_base64_encoded_signed_signature);

#endif // IOT_SAMPLE_COMMON_H
