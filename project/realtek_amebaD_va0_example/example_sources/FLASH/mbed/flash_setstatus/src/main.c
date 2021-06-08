#include "diag.h"
#include "main.h"

#include "objects.h"
#include "flash_api.h"

// Decide starting flash address for storing application data
// User should pick address carefully to avoid corrupting image section
#define FLASH_APP_BASE  0x1F0000//the start address of the last block((for MX25L1606E, please refer to datasheets for different flash))
#define length 256
void main(void)
{
    flash_t         flash;
    uint32_t        address = FLASH_APP_BASE;

    int result = 1;
    int i = 0;
    //int length = 256;
    
    char data[length];
    char buff[length];

    
    flash_erase_sector(&flash, address);  

    for(i = 0; i<length;i++){
        data[i] = i; 
    }    

    flash_burst_write(&flash, address, length, &data[0]);
    flash_stream_read(&flash, address, length, &buff[0]);


    for(i = 0; i<length;i++){
       if(data[i] != buff[i]){
            DBG_8195A("Error Addr %x, Write Data is = %x, Read Data is %x\n", address, data[i],buff[i]);
            result = 0;
        }
    }
    if(result == 1)
        DBG_8195A("Success 1\n");

    result = 1;
    DBG_8195A("Status Register Before Setting= %x\n", flash_get_status(&flash));

    flash_set_status(&flash, 0x4);//Protect hte last block (for MX25L1606E, please refer to datasheets for different flash)

    flash_erase_sector(&flash, address);  //This erase should be ignored due to block protect

    for(i = 0; i<length;i++){
        data[i] = ~i; 
    }    

      flash_burst_write(&flash, address, length, &data[0]);
      flash_stream_read(&flash, address, length, &buff[0]);
        for(i = 0; i<length;i++){
           if(data[i] != buff[i]){
                DBG_8195A("Error Addr %x, Write Data is = %x, Read Data is %x\n", address, data[i],buff[i]);
                result = 0;
            }
        }
    if(result == 1)
        DBG_8195A("Success 2\n");   

    result = 1;
    DBG_8195A("Status Register Before Setting= %x\n", flash_get_status(&flash));

    flash_set_status(&flash, flash_get_status(&flash) & (~0x4)); //Unlock the protected block   

    flash_erase_sector(&flash, address);//Now the erase operation should be valid

    flash_burst_write(&flash, address, length, &data[0]);

    flash_stream_read(&flash, address, length, &buff[0]);

    for(i = 0; i<length;i++){
       if(data[i] != buff[i]){
            DBG_8195A("Error Addr %x, Write Data is = %x, Read Data is %x\n", address, data[i],buff[i]);
            result = 0;
        }
    }
    if(result == 1)
        DBG_8195A("Success 3\n");

    flash_reset_status(&flash);//make sure the status register is reset if users would like to reload code

    DBG_8195A("Status Register After Reset= %x\n", flash_get_status(&flash));

    DBG_8195A("Test Done\n");
    
    for(;;);
        
}

