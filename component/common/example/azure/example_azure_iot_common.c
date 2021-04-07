#include <platform_opts.h>
#if defined(CONFIG_EXAMPLE_AZURE) && CONFIG_EXAMPLE_AZURE

// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <basic_types.h>

#include <azure/az_core.h>

#include "example_azure_iot_common.h"

extern int mbedtls_base64_decode( unsigned char *dst, size_t dlen, size_t *olen, const unsigned char *src, size_t slen);
extern int rom_hmac_sha256(const u8 *key, size_t key_len, const u8 *data, size_t data_len, u8 *mac);
extern int mbedtls_base64_encode( unsigned char *dst, size_t dlen, size_t *olen, const unsigned char *src, size_t slen);

bool import_user_configuration(
	iot_sample_variables* az_vars, 
	iot_sample_variable_name name, 
	const char *value)
{
	static bool is_init = false;
	if(!is_init){
		memset(az_vars, 0, sizeof(iot_sample_variables));
		is_init = true;
	}
	IOT_SAMPLE_PRECONDITION_NOT_NULL(az_vars);
	switch (name)
	{
		case IOT_SAMPLE_HUB_HOSTNAME:
			az_vars->hub_hostname = az_span_create_from_str((char*)value);
	        break;
		case IOT_SAMPLE_PROVISIONING_ID_SCOPE:
			az_vars->provisioning_id_scope = az_span_create_from_str((char*)value);
	        break;
		case IOT_SAMPLE_HUB_DEVICE_ID:
			az_vars->hub_device_id = az_span_create_from_str((char*)value);
	        break;
		case IOT_SAMPLE_PROVISIONING_REGISTRATION_ID:
			az_vars->provisioning_registration_id = az_span_create_from_str((char*)value);
	        break;
		case IOT_SAMPLE_HUB_SAS_KEY:
			az_vars->hub_sas_key = az_span_create_from_str((char*)value);
	        break;
		case IOT_SAMPLE_PROVISIONING_SAS_KEY:
			az_vars->provisioning_sas_key = az_span_create_from_str((char*)value);
	        break;
		case IOT_SAMPLE_DEVICE_X509_CERTIFICATE:
			az_vars->x509_certificate = az_span_create_from_str((char*)value);
	        break;
		case IOT_SAMPLE_DEVICE_X509_PRIVATE_KEY:
			az_vars->x509_private_key = az_span_create_from_str((char*)value);
	        break;
		default:
			IOT_SAMPLE_LOG_ERROR("Failed to import user configuration");
			return false;
	}
	return true;
}

void iot_sample_check_variables(
    iot_sample_type type,
    iot_sample_name name,
    iot_sample_variables* az_vars)
{
	IOT_SAMPLE_PRECONDITION_NOT_NULL(az_vars);

 	az_span duration;
 	az_result rc = 0;
	char * value;

	IOT_SAMPLE_LOG(" "); // Formatting

	if (type == AZIOT_HUB)
	{
		value = (char*)az_span_ptr(az_vars->hub_hostname);
		if(value) IOT_SAMPLE_LOG("IOT_SAMPLE_HUB_HOSTNAME: %s", value);
		else
		{
			IOT_SAMPLE_LOG_ERROR("IOT_SAMPLE_HUB_HOSTNAME is not set");
			return;
		}

	    switch (name)
	    {
			case AZIOT_HUB_C2D_SAMPLE:
			case AZIOT_HUB_METHODS_SAMPLE:
			case AZIOT_HUB_PNP_COMPONENT_SAMPLE:
			case AZIOT_HUB_PNP_SAMPLE:
			case AZIOT_HUB_TELEMETRY_SAMPLE:
			case AZIOT_HUB_TWIN_SAMPLE:
			case AZIOT_872XD_PNP_SAMPLE:
			
				//check hub device_id
				value = (char*)az_span_ptr(az_vars->hub_device_id);
				if(value) IOT_SAMPLE_LOG("IOT_SAMPLE_HUB_DEVICE_ID: %s", value);
				else
				{
					IOT_SAMPLE_LOG_ERROR("IOT_SAMPLE_HUB_DEVICE_ID is not set");
					return;
				}
				
				//check x509 certificate
				value = (char*)az_span_ptr(az_vars->x509_certificate);
				if(value) IOT_SAMPLE_LOG("IOT_SAMPLE_DEVICE_X509_CERTIFICATE: \n%s", value);
				else
				{
					IOT_SAMPLE_LOG_ERROR("IOT_SAMPLE_DEVICE_X509_CERTIFICATE is not set");
					return;
				}

				//check x509 private key
				value = (char*)az_span_ptr(az_vars->x509_private_key);
				if(value) IOT_SAMPLE_LOG("IOT_SAMPLE_DEVICE_X509_PRIVATE_KEY: \n%s", value);
				else
				{
					IOT_SAMPLE_LOG_ERROR("IOT_SAMPLE_DEVICE_X509_PRIVATE_KEY is not set");
					return;
				}
		        break;

			case AZIOT_HUB_SAS_TELEMETRY_SAMPLE:
			case AZIOT_872XD_PNP_SAS_SAMPLE:

				//check hub device_id
				value = (char*)az_span_ptr(az_vars->hub_device_id);
				if(value) IOT_SAMPLE_LOG("IOT_SAMPLE_HUB_DEVICE_ID: %s", value);
				else
				{
					IOT_SAMPLE_LOG_ERROR("IOT_SAMPLE_HUB_DEVICE_ID is not set");
					return;
				}

				//check sas key
				value = (char*)az_span_ptr(az_vars->hub_sas_key);
				if(value) IOT_SAMPLE_LOG("IOT_SAMPLE_HUB_SAS_KEY: %s", value);
				else
				{
					IOT_SAMPLE_LOG_ERROR("IOT_SAMPLE_HUB_SAS_KEY is not set");
					return;
				}

				//check sas key duration
				duration = az_span_create_from_str((char*)"120");
				rc = az_span_atou32(duration, &(az_vars->sas_key_duration_minutes));
				if(az_result_succeeded(rc)) IOT_SAMPLE_LOG("IOT_SAMPLE_SAS_KEY_DURATION_MINUTES: %d", az_vars->sas_key_duration_minutes);
				else
				{
					IOT_SAMPLE_LOG_ERROR("IOT_SAMPLE_SAS_KEY_DURATION_MINUTES is not set");
					return;
				}
				break;

	      default:
			IOT_SAMPLE_LOG_ERROR("Hub sample name undefined.");
			return;
		}
	}
	else if (type == AZIOT_PROVISIONING)
	{
		
		//check provisioning id_scope
		value = (char*)az_span_ptr(az_vars->provisioning_id_scope);
		if(value) IOT_SAMPLE_LOG("IOT_SAMPLE_PROVISIONING_ID_SCOPE: %s", value);
		else
		{
			IOT_SAMPLE_LOG_ERROR("IOT_SAMPLE_PROVISIONING_ID_SCOPE is not set");
			return;
		}

		switch (name)
		{
			case AZIOT_PROVISIONING_SAMPLE:
			case AZIOT_872XD_PNP_SAMPLE:
				//check provisioning id_scope
				value = (char*)az_span_ptr(az_vars->provisioning_registration_id);
				if(value) IOT_SAMPLE_LOG("IOT_SAMPLE_PROVISIONING_REGISTRATION_ID: %s", value);
				else
				{
					IOT_SAMPLE_LOG_ERROR("IOT_SAMPLE_PROVISIONING_REGISTRATION_ID is not set");
					return;
				}

				//check x509 certificate
				value = (char*)az_span_ptr(az_vars->x509_certificate);
				if(value) IOT_SAMPLE_LOG("IOT_SAMPLE_DEVICE_X509_CERTIFICATE: \n%s", value);
				else
				{
					IOT_SAMPLE_LOG_ERROR("IOT_SAMPLE_DEVICE_X509_CERTIFICATE is not set");
					return;
				}

				//check x509 private key
				value = (char*)az_span_ptr(az_vars->x509_private_key);
				if(value) IOT_SAMPLE_LOG("IOT_SAMPLE_DEVICE_X509_PRIVATE_KEY: \n%s", value);
				else
				{
					IOT_SAMPLE_LOG_ERROR("IOT_SAMPLE_DEVICE_X509_PRIVATE_KEY is not set");
					return;
				}
				break;

			case AZIOT_PROVISIONING_SAS_SAMPLE:
			case AZIOT_872XD_PNP_SAS_SAMPLE:

				//check provisioning id_scope
				value = (char*)az_span_ptr(az_vars->provisioning_registration_id);
				if(value) IOT_SAMPLE_LOG("IOT_SAMPLE_PROVISIONING_REGISTRATION_ID: %s", value);
				else
				{
					IOT_SAMPLE_LOG_ERROR("IOT_SAMPLE_PROVISIONING_REGISTRATION_ID is not set");
					return;
				}

				//check provisioning id_scope
				value = (char*)az_span_ptr(az_vars->provisioning_sas_key);
				if(value) IOT_SAMPLE_LOG("IOT_SAMPLE_PROVISIONING_SAS_KEY: %s", value);
				else
				{
					IOT_SAMPLE_LOG_ERROR("IOT_SAMPLE_PROVISIONING_SAS_KEY is not set");
					return;
				}

				//check sas key duration
				duration = az_span_create_from_str((char*)"120");
				rc = az_span_atou32(duration, &(az_vars->sas_key_duration_minutes));
				if(az_result_succeeded(rc)) IOT_SAMPLE_LOG("IOT_SAMPLE_SAS_KEY_DURATION_MINUTES: %d", az_vars->sas_key_duration_minutes);
				else
				{
					IOT_SAMPLE_LOG_ERROR("IOT_SAMPLE_SAS_KEY_DURATION_MINUTES is not set");
					return;
				}
				break;

	      default:
	        IOT_SAMPLE_LOG_ERROR("Failed to read environment variables: Provisioning sample name undefined.");
	        return;
	    }
	}
	else
	{
		IOT_SAMPLE_LOG_ERROR("Failed to read environment variables: Sample type undefined.");
		return;
	}
	IOT_SAMPLE_LOG(" "); // Formatting
}

void build_error_message(char* out_full_message, char const* const error_message, ...)
{
	char const* const append_message = ": az_result return code 0x%08x.";

	strcpy(out_full_message, error_message);
	strcat(out_full_message, append_message);
}

bool get_az_span(az_span* out_span, char const* const error_message, ...)
{
	va_list args;
	va_start(args, error_message);

	*out_span = va_arg(args, az_span);
	va_end(args);

	if (az_span_size(*out_span) == 0) // There was no span
	{
		return false;
	}

	return true;
}

void iot_sample_sleep_for_seconds(uint32_t seconds)
{
	(void)az_platform_sleep_msec(seconds*1000);
}

int64_t iot_sample_get_epoch_expiration_time_from_minutes(uint32_t minutes)
{

	int64_t expiration_time = 0;
	long ts = 0;
	long tus = 0;
	unsigned int ttk = 0;

	//it should be ok to do init more than one times. It'll handle inside sntp_init().
	sntp_init();

	sntp_get_lasttime(&ts,&tus,&ttk);
	
	while(ts == 0){
		vTaskDelay(1000 / portTICK_RATE_MS);
		sntp_get_lasttime(&ts,&tus,&ttk);
	}	

	expiration_time = (int64_t)ts + minutes * 60;
	
	return expiration_time;
}


static void decode_base64_bytes(
    az_span base64_encoded_bytes,
    az_span decoded_bytes,
    az_span* out_decoded_bytes)
{
	
	memset(az_span_ptr(decoded_bytes), 0, (size_t)az_span_size(decoded_bytes));

	size_t len;
	if( mbedtls_base64_decode( az_span_ptr(decoded_bytes), (size_t)az_span_size(decoded_bytes), 
	  	&len, az_span_ptr(base64_encoded_bytes), (size_t)az_span_size(base64_encoded_bytes)) != 0)
	{
		IOT_SAMPLE_LOG_ERROR("mbedtls_base64_decode fail\n");
	}
	
	*out_decoded_bytes = az_span_create(az_span_ptr(decoded_bytes), (int32_t)len);
}

static void hmac_sha256_sign_signature(
    az_span decoded_key,
    az_span signature,
    az_span signed_signature,
    az_span* out_signed_signature)
{ 
	if(rom_hmac_sha256(
		az_span_ptr(decoded_key), 
		(size_t)az_span_size(decoded_key),
		az_span_ptr(signature),
		(size_t)az_span_size(signature),
		az_span_ptr(signed_signature)) != 0)

	{
		IOT_SAMPLE_LOG_ERROR("rom_hmac_sha256 failed\n");
	};

	*out_signed_signature = az_span_create(az_span_ptr(signed_signature), 32);
}

static void base64_encode_bytes(
    az_span decoded_bytes,
    az_span base64_encoded_bytes,
    az_span* out_base64_encoded_bytes)
{
	size_t len;
	if( mbedtls_base64_encode( az_span_ptr(base64_encoded_bytes), (size_t)az_span_size(base64_encoded_bytes), 
		&len, az_span_ptr(decoded_bytes), (size_t)az_span_size(decoded_bytes)) != 0)
	{
		IOT_SAMPLE_LOG_ERROR("mbedtls_base64_encode fail\n");
	}
  
	*out_base64_encoded_bytes = az_span_create(az_span_ptr(base64_encoded_bytes), (int32_t)len);
}

void iot_sample_generate_sas_base64_encoded_signed_signature(
    az_span sas_base64_encoded_key,
    az_span sas_signature,
    az_span sas_base64_encoded_signed_signature,
    az_span* out_sas_base64_encoded_signed_signature)
{
	IOT_SAMPLE_PRECONDITION_NOT_NULL(out_sas_base64_encoded_signed_signature);

	// Decode the sas base64 encoded key to use for HMAC signing.
	char sas_decoded_key_buffer[64];
	az_span sas_decoded_key = AZ_SPAN_FROM_BUFFER(sas_decoded_key_buffer);
	decode_base64_bytes(sas_base64_encoded_key, sas_decoded_key, &sas_decoded_key);

	// HMAC-SHA256 sign the signature with the decoded key.
	char sas_hmac256_signed_signature_buffer[64];
	az_span sas_hmac256_signed_signature = AZ_SPAN_FROM_BUFFER(sas_hmac256_signed_signature_buffer);
	hmac_sha256_sign_signature(sas_decoded_key, sas_signature, sas_hmac256_signed_signature, &sas_hmac256_signed_signature);

	// Base64 encode the result of the HMAC signing.
	base64_encode_bytes(
		sas_hmac256_signed_signature,
		sas_base64_encoded_signed_signature,
		out_sas_base64_encoded_signed_signature);
}

#endif
