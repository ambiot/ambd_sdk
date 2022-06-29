
#include "ameba_soc.h"
#include "main.h"
#include "GUI.h"
#include "WM.h"
#include "WIDGET.h"
#include "gpio_api.h"
#include "gpio_irq_api.h"

#define INT_PIN    _PA_17

void gpio_touch_irq_handler (uint32_t id, gpio_irq_event event)
{
	GUI_TOUCH_Exec();
	GUI_TOUCH_Exec();
}


int main(void)
{
#if GUI_SUPPORT_MEMDEV
    WM_SetCreateFlags(WM_CF_MEMDEV);
#endif
	GUI_Init();
	/*touch interrupt pin*/
	gpio_irq_t gpio_btn;

	gpio_irq_init(&gpio_btn, INT_PIN, gpio_touch_irq_handler, (uint32_t)(&gpio_btn));
	gpio_irq_set(&gpio_btn, IRQ_FALL, 1);   
	gpio_irq_enable(&gpio_btn);

	/*debounce need to be disable, because touch pulse width may be less than 2 debounce clk*/
	GPIO_INTMode(INT_PIN, ENABLE, GPIO_INT_Trigger_EDGE, GPIO_INT_POLARITY_ACTIVE_LOW, GPIO_INT_DEBOUNCE_DISABLE);
  
	if (xTaskCreate((TaskFunction_t )MainTask,(const char*)"MainTask", 4096, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		DiagPrintf("\n\r%s xTaskCreate(MainTask) failed", __FUNCTION__);
	
	//DiagPrintf("M4U:%d \n", RTIM_GetCount(TIMM05));
	/* Enable Schedule, Start Kernel */
	vTaskStartScheduler();
}

