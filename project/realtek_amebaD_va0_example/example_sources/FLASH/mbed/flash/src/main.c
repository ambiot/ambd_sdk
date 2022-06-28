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
    flash_t         flash;
    uint32_t        address = FLASH_APP_BASE;

#if 1
    uint32_t        val32_to_write = 0x13572468;
    uint32_t        val32_to_read;
    int loop = 0;
    int result = 0;
    
    for(loop = 0; loop < 10; loop++)
    {
		device_mutex_lock(RT_DEV_LOCK_FLASH);
        flash_read_word(&flash, address, &val32_to_read);
        DiagPrintf("Read Data 0x%x\n", val32_to_read);
        flash_erase_sector(&flash, address);
        flash_write_word(&flash, address, val32_to_write);
        flash_read_word(&flash, address, &val32_to_read);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);

        DiagPrintf("Read Data 0x%x\n", val32_to_read);

        // verify result
        result = (val32_to_write == val32_to_read) ? 1 : 0;
        //DiagPrintf("\r\nResult is %s\r\n", (result) ? "success" : "fail");
        DiagPrintf("\r\nResult is %s\r\n", (result) ? "success" : "fail");
        result = 0;
    }

#else
    int VERIFY_SIZE = 256;
    int SECTOR_SIZE = 16;
    
    uint8_t writedata[VERIFY_SIZE];
    uint8_t readdata[VERIFY_SIZE];
    uint8_t verifydata = 0;
    int loop = 0;
    int index = 0;
    int sectorindex = 0;
    int result = 0;
    int resultsector = 0;
    int testloop = 0;
    
    for(testloop = 0; testloop < 1; testloop++){
        address = FLASH_APP_BASE;
        for(sectorindex = 0; sectorindex < 0x300; sectorindex++){
            result = 0;
            //address += SECTOR_SIZE;
			device_mutex_lock(RT_DEV_LOCK_FLASH);
            flash_erase_sector(&flash, address);
			device_mutex_unlock(RT_DEV_LOCK_FLASH);
            //DiagPrintf("Address = %x \n", address);
            for(loop = 0; loop < SECTOR_SIZE; loop++){
                for(index = 0; index < VERIFY_SIZE; index++)
                {
                    writedata[index] = verifydata + index;
                }
				device_mutex_lock(RT_DEV_LOCK_FLASH);
                flash_stream_write(&flash, address, VERIFY_SIZE, &writedata);
                flash_stream_read(&flash, address, VERIFY_SIZE, &readdata);
				device_mutex_unlock(RT_DEV_LOCK_FLASH);
				
                for(index = 0; index < VERIFY_SIZE; index++)
                {
                    //DiagPrintf("Address = %x, Writedata = %x, Readdata = %x \n",address,writedata[index],readdata[index]);
                    if(readdata[index] != writedata[index]){
                        DiagPrintf("Error: Loop = %d, Address = %x, Writedata = %x, Readdata = %x \n",testloop,address,writedata[index],readdata[index]);
                    }
                    else{
                        result++;
                        //DiagPrintf(ANSI_COLOR_BLUE"Correct: Loop = %d, Address = %x, Writedata = %x, Readdata = %x \n"ANSI_COLOR_RESET,testloop,address,writedata[index],readdata[index]);
                    }
                }
                address += VERIFY_SIZE;
            }
            if(result == VERIFY_SIZE * SECTOR_SIZE){
                //DiagPrintf("Sector %d Success \n", sectorindex);
                resultsector++;
            }
        }
        if(resultsector == 0x300){
            DiagPrintf("Test Loop %d Success \n", testloop);    
        }
        resultsector = 0;
        verifydata++;
    }
    //DiagPrintf("%d Sector Success \n", resultsector);

    DiagPrintf("Test Done");

#endif
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
