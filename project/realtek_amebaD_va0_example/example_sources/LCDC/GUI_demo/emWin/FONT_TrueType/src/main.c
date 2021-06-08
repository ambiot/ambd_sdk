
#include "ameba_soc.h"
#include "main.h"
#include "GUI.h"

int main(void)
{
	if (xTaskCreate((TaskFunction_t )MainTask,(const char*)"MainTask", 4096, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(MainTask) failed", __FUNCTION__);


	//DBG_8195A("M4U:%d \n", RTIM_GetCount(TIMM05));
	/* Enable Schedule, Start Kernel */
	vTaskStartScheduler();
}

