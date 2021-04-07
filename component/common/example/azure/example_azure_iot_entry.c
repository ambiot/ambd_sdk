#include <platform_opts.h>
#if defined(CONFIG_EXAMPLE_AZURE) && CONFIG_EXAMPLE_AZURE

#include <stdio.h>
#include "example_azure_iot_entry.h"

void example_azure(void)
{
#if defined EXAMPLE_AZURE_IOT_HUB_C2D
	example_azure_iot_hub_c2d();
#elif defined EXAMPLE_AZURE_IOT_HUB_METHODS
	example_azure_iot_hub_methods();
#elif defined EXAMPLE_AZURE_IOT_HUB_PNP_COMPONENT
	example_azure_iot_hub_pnp_component();
#elif defined EXAMPLE_AZURE_IOT_HUB_PNP
	example_azure_iot_hub_pnp();
#elif defined EXAMPLE_AZURE_IOT_HUB_SAS_TELEMETRY
	example_azure_iot_hub_sas_telemetry();
#elif defined EXAMPLE_AZURE_IOT_HUB_TELEMETRY
	example_azure_iot_hub_telemetry();
#elif defined EXAMPLE_AZURE_IOT_HUB_TWIN
	example_azure_iot_hub_twin();
#elif defined EXAMPLE_AZURE_IOT_PROVISIONING
	example_azure_iot_provisioning();
#elif defined EXAMPLE_AZURE_IOT_PROVISIONING_SAS
	example_azure_iot_provisioning_sas();
#elif defined EXAMPLE_AZURE_IOT_RTK_PNP_SAS
	example_azure_iot_rtk_pnp_sas();
#elif defined EXAMPLE_AZURE_IOT_RTK_PNP_X509
	example_azure_iot_rtk_pnp_x509();
#else
	printf("Please select ONE azure example to run by defining AZIOT_SAMPLE_NAME\r\n");
#endif

}

#endif
