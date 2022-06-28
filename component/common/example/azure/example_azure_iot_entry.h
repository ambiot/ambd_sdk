#ifndef EXAMPLE_AZURE_IOT_ENTRY_H
#define EXAMPLE_AZURE_IOT_ENTRY_H

//select an azure example to run (choose only one)

/* Microsoft provided examples */
//#define EXAMPLE_AZURE_IOT_HUB_C2D
//#define EXAMPLE_AZURE_IOT_HUB_METHODS
//#define EXAMPLE_AZURE_IOT_HUB_PNP_COMPONENT
//#define EXAMPLE_AZURE_IOT_HUB_PNP
#define EXAMPLE_AZURE_IOT_HUB_SAS_TELEMETRY
//#define EXAMPLE_AZURE_IOT_HUB_TELEMETRY
//#define EXAMPLE_AZURE_IOT_HUB_TWIN
//#define EXAMPLE_AZURE_IOT_PROVISIONING
//#define EXAMPLE_AZURE_IOT_PROVISIONING_SAS

/* Realtek IoT Hub pnp examples */
//#define EXAMPLE_AZURE_IOT_RTK_PNP_SAS
//#define EXAMPLE_AZURE_IOT_RTK_PNP_X509

// For Azure IoT Pnp Certification Test
#if defined(EXAMPLE_AZURE_IOT_RTK_PNP_SAS) || defined(EXAMPLE_AZURE_IOT_RTK_PNP_X509)
#define AZURE_PNP_CERTIFICATION_TEST 0
#endif

//use standard c library to support %*.s format
#if defined(CONFIG_PLATFORM_8721D)
#define STD_PRINTF
#include "platform_stdlib.h"
#elif defined(CONFIG_PLATFORM_8710C)
#include "platform_stdlib.h"
#undef printf
#define printf printf
#endif

void example_azure(void);

void example_azure_iot_hub_telemetry(void);

void example_azure_iot_hub_sas_telemetry(void);

void example_azure_iot_hub_c2d(void);

void example_azure_iot_hub_methods(void);

void example_azure_iot_hub_twin(void);

void example_azure_iot_hub_pnp(void);

void example_azure_iot_hub_pnp_component(void);

void example_azure_iot_provisioning(void);

void example_azure_iot_provisioning_sas(void);

void example_azure_iot_rtk_pnp_sas(void);

void example_azure_iot_rtk_pnp_x509(void);

#endif
