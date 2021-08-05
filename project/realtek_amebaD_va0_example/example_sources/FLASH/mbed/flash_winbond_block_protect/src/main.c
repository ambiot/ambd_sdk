#include "diag.h"
#include "main.h"

#include "objects.h"
#include "flash_api.h"

// Decide starting flash address for storing application data
// User should pick address carefully to avoid corrupting image section
#define FLASH_APP_BASE  0x180000 //the start address of the upper 512KB
#define length 8
void main(void)
{
    flash_t         flash;
    uint32_t        address = FLASH_APP_BASE;

    int result1 = 1, result2 = 1, result3 = 1;
    int i = 0;
    //int length = 8;
    int loop = 0;
    
    char write_data1[length];
    char write_data2[length];
    char buff[length];

    for(i = 0; i<length;i++){
            write_data1[i] = i;
            write_data2[i] = ~i;
    }

    for(loop = 0; loop < 8; loop++) {
        DiagPrintf("Test Address = %x\n", address);
        flash_erase_sector(&flash, address);
        flash_burst_write(&flash, address, length, &write_data1[0]);
        flash_stream_read(&flash, address, length, &buff[0]);

        DiagPrintf("Before Lock\n");

        for(i = 0; i<length;i++) {
           if(write_data1[i] != buff[i]) {
                DiagPrintf("Error : Write Data is = %x, Read Data is %x\n", write_data1[i],buff[i]);
                result1 = 0;
            }
        }
        if(result1 == 1)
            DiagPrintf("Success 1\n");
        
        DiagPrintf("Lock last 8 blocks\n");
        result2 = 1;
        DiagPrintf("Status Register Before Setting= %x\n", flash_get_status(&flash));

        flash_set_status(&flash, 0x10);//Protect upper 512KB, 0x180000h~0x1FFFFFh

        flash_erase_sector(&flash, address);  //This erase should be ignored if the block is protected

        flash_burst_write(&flash, address, length, &write_data2[0]);//This program should be ignored if the block is protected
        flash_stream_read(&flash, address, length, &buff[0]);
            for(i = 0; i < length; i++) {
               if(write_data1[i] != buff[i]){ 
                    DiagPrintf("Error : Write Data1 is = %x, Write Data2 is = %x, Read Data is %x\n", write_data1[i], write_data2[i], buff[i]); 
                    result2 = 0;
                }
            }
        if(result2 == 1)
            DiagPrintf("Success 2\n");  

        DiagPrintf("Unlock\n");
        result3 = 1;
        DiagPrintf("Status Register Before Setting= %x\n", flash_get_status(&flash));

        flash_set_status(&flash, flash_get_status(&flash) & 0x0); //Unlock the protected block   

        flash_erase_sector(&flash, address);//Now the erase operation should be valid

        flash_burst_write(&flash, address, length, &write_data2[0]);

        flash_stream_read(&flash, address, length, &buff[0]);

        for(i = 0; i<length;i++){
           if(write_data2[i] != buff[i]){
                DiagPrintf("Error : Write Data is = %x, Read Data is %x\n",write_data2[i],buff[i]);
                result3 = 0;
            }
        }
        if(result3 == 1)
            DiagPrintf("Success 3\n");

        flash_reset_status(&flash);//make sure the status register is reset if users would like to reload code

        DiagPrintf("Status Register After Reset= %x\n", flash_get_status(&flash));
        DiagPrintf("Result is %s\r\n\n", (result1 && result2 && result3) ? "success" : "fail");
        address += 0x10000;
    }

    DiagPrintf("Test Done\n");
    
    for(;;);
        
}

