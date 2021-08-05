
#include "ameba_soc.h"
#include "main.h"
#include "GUI.h"

int main(void)
{
	if (xTaskCreate((TaskFunction_t )MainTask,(const char*)"MainTask", 4096, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		DiagPrintf("\n\r%s xTaskCreate(MainTask) failed", __FUNCTION__);

	//DiagPrintf("M4U:%d \n", RTIM_GetCount(TIMM05));
	/* Enable Schedule, Start Kernel */
	vTaskStartScheduler();
}

