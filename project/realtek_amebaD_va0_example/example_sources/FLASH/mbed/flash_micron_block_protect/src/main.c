#include "diag.h"
#include "main.h"

#include "objects.h"
#include "flash_api.h"

// Decide starting flash address for storing application data
// User should pick address carefully to avoid corrupting image section
#define FLASH_APP_BASE  0x40000//the start address of the fourth block
#define length 8
void main(void)
{
    flash_t         flash;
    uint32_t        address = FLASH_APP_BASE;

    int result = 1;
    int i = 0;
    //int length = 8;
    int loop = 0;
    
    char data[length];
    char buff[length];

    for(loop = 0; loop<8;loop++){
        DBG_8195A(ANSI_COLOR_MAGENTA"Test Address = %x\n"ANSI_COLOR_RESET, address);
        flash_erase_sector(&flash, address);  

        for(i = 0; i<length;i++){
            data[i] = i; 
        }    

        flash_burst_write(&flash, address, length, &data[0]);
        flash_stream_read(&flash, address, length, &buff[0]);

        DBG_8195A("Before Lock\n");

        for(i = 0; i<length;i++){
           if(data[i] != buff[i]){
                DBG_8195A(ANSI_COLOR_YELLOW"Error : Write Data is = %x, Read Data is %x\n"ANSI_COLOR_RESET, data[i],buff[i]);
                result = 0;
            }
        }
        if(result == 1)
            DBG_8195A("Success 1\n");
        
        DBG_8195A("Lock first 8 blocks\n");
        result = 1;
        DBG_8195A("Status Register Before Setting= %x\n", flash_get_status(&flash));

        flash_set_status(&flash, 0x30);//Protect 0~7 blocks

        flash_erase_sector(&flash, address);  //This erase should be ignored if the block is protected

        for(i = 0; i<length;i++){
            data[i] = ~i; 
        }    

          flash_burst_write(&flash, address, length, &data[0]);
          flash_stream_read(&flash, address, length, &buff[0]);
            for(i = 0; i<length;i++){
               if(data[i] != buff[i]){
                    DBG_8195A(ANSI_COLOR_YELLOW"Error : Write Data is = %x, Read Data is %x\n"ANSI_COLOR_RESET, data[i],buff[i]);
                    result = 0;
                }
            }
        if(result == 1)
            DBG_8195A("Success 2\n");  

        DBG_8195A("Unlock\n");
        result = 1;
        DBG_8195A("Status Register Before Setting= %x\n", flash_get_status(&flash));

        flash_set_status(&flash, flash_get_status(&flash) & (~0x30)); //Unlock the protected block   

        flash_erase_sector(&flash, address);//Now the erase operation should be valid

        flash_burst_write(&flash, address, length, &data[0]);

        flash_stream_read(&flash, address, length, &buff[0]);

        for(i = 0; i<length;i++){
           if(data[i] != buff[i]){
                DBG_8195A(ANSI_COLOR_YELLOW"Error : Write Data is = %x, Read Data is %x\n"ANSI_COLOR_RESET,data[i],buff[i]);
                result = 0;
            }
        }
        if(result == 1)
            DBG_8195A("Success 3\n");

        flash_reset_status(&flash);//make sure the status register is reset if users would like to reload code

        DBG_8195A("Status Register After Reset= %x\n", flash_get_status(&flash));
        address += 0x10000;
    }

    DBG_8195A("Test Done\n");
    
    for(;;);
        
}

