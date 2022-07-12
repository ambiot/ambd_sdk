#ifndef PNP_DEVICE_INFO_COMPONENT_H
#define PNP_DEVICE_INFO_COMPONENT_H

#include <stdbool.h>
#include <stdint.h>

#include <azure/az_core.h>
#include <azure/az_iot.h>

//#include "pnp_mqtt_message.h"

typedef struct
{
  az_span component_name;
  az_span manufacturer;
  az_span model;
  az_span fw_version;
} pnp_device_info_component;


/**
 * @brief Initialize a #pnp_thermostat_component which holds device thermostat info.
 *
 * @param[out] out_thermostat_component A pointer to a #out_thermostat_component instance to
 * initialize.
 * @param[in] component_name The name of the component.
 * @param[in] initial_temperature The initial temperature to set all temperature member variables.
 *
 * @return An #az_result value indicating the result of the operation.
 * @retval #AZ_OK #pnp_thermostat_component is initialied successfully.
 * @retval #AZ_ERROR_ARG The pointer to the #pnp_thermostat_component instance is NULL.
 */
az_result pnp_device_info_init(
    pnp_device_info_component* out_device_info_component,
    az_span component_name);

/**
 * @brief Build the thermostat's maximum temperature reported property message.
 *
 * @param[in] thermostat_component A pointer to the themostat component to get data.
 * @param[in] payload An #az_span with sufficient capacity to hold the json payload.
 * @param[out] out_payload A pointer to the #az_span containing the output json payload.
 * @param[out] out_property_name The name of the reported property to be sent.
 */
void pnp_device_info_append_all_reported_property(
	pnp_device_info_component* device_info_component,
	az_json_writer* jw);

void pnp_device_info_build_reported_property(
    pnp_device_info_component* device_info_component,
    az_span payload,
    az_span* out_payload,
    az_span property_name);


#endif // PNP_DEVICE_INFO_COMPONENT_H

