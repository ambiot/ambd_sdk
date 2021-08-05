#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "objects.h"
#include "flash_api.h"
#include "osdep_service.h"
#include "device_lock.h"
#include "main.h"

// Decide starting flash address for storing application data
// User should pick address carefully to avoid corrupting image section

#define FLASH_APP_BASE  0xFF000
static void flash_test_task(void *param)
{
	uint32_t        address = FLASH_APP_BASE;

	uint32_t        val32_to_write = 0x13572468;
	uint32_t        val32_to_read;
	int loop = 0;
	int result = 0;

	for(loop = 0; loop < 10; loop++)
	{
		device_mutex_lock(RT_DEV_LOCK_FLASH);
		val32_to_read = HAL_READ32(SPI_FLASH_BASE, address);
		DiagPrintf("Read Data 0x%x\n", val32_to_read);

		FLASH_Write_Lock();
		FLASH_Erase(EraseSector, address);
		FLASH_TxData12B(address, 4, (u8*)&val32_to_write);
		FLASH_Write_Unlock();

		DCache_Invalidate(address, 4);
		val32_to_read = HAL_READ32(SPI_FLASH_BASE, address);

		device_mutex_unlock(RT_DEV_LOCK_FLASH);

		DiagPrintf("Read Data 0x%x\n", val32_to_read);

		// verify result
		result = (val32_to_write == val32_to_read) ? 1 : 0;
		//DiagPrintf("\r\nResult is %s\r\n", (result) ? "success" : "fail");
		DiagPrintf("\r\nResult is %s\r\n", (result) ? "success" : "fail");
		result = 0;
	}

	vTaskDelete(NULL);
}

void main(void)
{
	if(xTaskCreate(flash_test_task, ((const char*)"flash_test_task"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		DiagPrintf("\n\r%s xTaskCreate(flash_test_task) failed", __FUNCTION__);

	vTaskStartScheduler();
	while(1){
		vTaskDelay( 1000 / portTICK_RATE_MS );
	}
	
}
