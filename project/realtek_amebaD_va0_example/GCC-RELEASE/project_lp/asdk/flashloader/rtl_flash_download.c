/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *                                        
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#include "rtl8721d.h"
#include "build_info.h"



#define FLASHDATALEN 2048
BOOT_RAM_BSS_SECTION volatile u8  FlashDataBuf[FLASHDATALEN];//#define FLASH_DATA_BUF 	0x00086000 
BOOT_RAM_BSS_SECTION volatile u32 *pFlashDatSrc;
BOOT_RAM_BSS_SECTION volatile u32 FlashBlockWriteSize;    //The maximum size of each block write is FLASHDATALEN,
                            //The actual value MUST be given by GDB.
BOOT_RAM_BSS_SECTION volatile u32 FlashAddrForWrite;      //The flash address to be written.
                            //The actual value MUST be given by GDB.      
BOOT_RAM_BSS_SECTION volatile u8  FlashWriteComplete;                            
BOOT_RAM_BSS_SECTION volatile u32 FlashDatSrc;
BOOT_RAM_BSS_SECTION u32 erase_sector_addr = 0;
	
extern u8 __rom_bss_start__[];
extern u8 __rom_bss_end__[];
extern u8 __ram_start_table_start__[];

//extern u32 ConfigDebugErr;
//extern u32 ConfigDebugInfo;
//extern u32 ConfigDebugWarn;

void BOOT_RAM_TEXT_SECTION
RtlFlashProgram(VOID)
{
	volatile u32 FlashWriteCnt = 0;
	u8 flash_ID[3];
	u32 Temp;
	//2 Need Modify
	InterruptDis(UART_LOG_IRQ);
	DBG_8195A("==========================================================\n");
	DBG_8195A("Flash Downloader Build Time: "UTS_VERSION"\n");  
	DBG_8195A("==========================================================\n");

	FlashDatSrc = (u32)&FlashDataBuf;
	pFlashDatSrc = (u32 *)&FlashDataBuf;
	FlashWriteComplete = 0;
	FlashBlockWriteSize = 0;
	FlashAddrForWrite = 0;
	erase_sector_addr = 0;

	//Cache_Enable(DISABLE);
	//RCC_PeriphClockCmd(APBPeriph_FLASH, APBPeriph_FLASH_CLOCK, DISABLE);
	/*Switch SPIC clock source*/
	Temp = HAL_READ32(SYSTEM_CTRL_BASE_LP, REG_LP_CLK_CTRL0);
	Temp &= ~(BIT_MASK_FLASH_CLK_SEL << BIT_SHIFT_FLASH_CLK_SEL);
	Temp |= BIT_SHIFT_FLASH_CLK_XTAL;
	HAL_WRITE32(SYSTEM_CTRL_BASE_LP, REG_LP_CLK_CTRL0, Temp);

	DBG_8195A("Flash init start\n");
	FLASH_StructInit(&flash_init_para);
	FLASH_Init(SpicOneBitMode);
	DBG_8195A("Flash init done\n");

	FLASH_RxCmd(flash_init_para.FLASH_cmd_rd_id, 3, flash_ID);
	if(flash_ID[0] == 0x20){
		flash_init_para.FLASH_cmd_chip_e = 0xC7;}

	//4 Erase the flash before writing it
	//FLASH_Erase(EraseChip, 0);
	//DBG_8195A("Flash erace done\n");
	DBG_8195A("Flash download start\n");
	//4 Program the flash from memory data
	while(1)
	{
StartOfFlashBlockWrite:
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		
		FlashWriteCnt = 0;
		pFlashDatSrc = (u32 *)&FlashDataBuf[0];
		if (FlashWriteComplete == 1)
			break;

		while (FlashWriteCnt < FlashBlockWriteSize)
		{
			u32 sector_addr1 = FlashAddrForWrite  & 0xFFFFF000; /* sector of first byte */

			if(sector_addr1 >= erase_sector_addr) {
				FLASH_Erase(EraseSector, sector_addr1);
				erase_sector_addr = sector_addr1 + 0x1000; /* next sector we should erase */
			}

			FLASH_TxData12B(FlashAddrForWrite, 4, (u8*)pFlashDatSrc);
			
			FlashAddrForWrite += 4;
			FlashWriteCnt += 4;
			pFlashDatSrc+= 1; 			
		}   

		goto StartOfFlashBlockWrite;
	}

	DBG_8195A("Flash download done\n");
    
	while(1){
		if  (FlashWriteComplete == 1) {           
			FlashWriteComplete = 0;
		}
	}    
}
