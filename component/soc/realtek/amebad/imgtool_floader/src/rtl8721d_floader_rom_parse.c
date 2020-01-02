#include "rtl8721d_floader_rom_parse.h"


#define OLD_ROM_VERSION	0x01
BOOT_RAM_BSS_SECTION u32 RomVer = 0x01;

BOOT_RAM_TEXT_SECTION
u8 BOOT_RAM_GetCutVersion(void)
{
	u32 tmp = HAL_READ32(0, 0x1298);

	if(tmp != 0)
		return 0;
	else
		return 1;
}

BOOT_RAM_TEXT_SECTION
void get_rom_version(void)
{
	u32 Temp = 0;

	RomVer = HAL_READ32(SYSTEM_CTRL_BASE, REG_LP_SYSTEM_CFG2) & BIT_MASK_SYSCFG_ROM_INFO;

	if(BOOT_RAM_GetCutVersion() == 0) {
		/* AmebaD ACut: enable HWPD */
		Temp = HAL_READ32(SYSTEM_CTRL_BASE_LP, REG_AON_PM_OPT);
		Temp |= BIT_AON_PMC_DIRECT_PDN;
		HAL_WRITE32(SYSTEM_CTRL_BASE_LP, REG_AON_PM_OPT, Temp);
	}
	
	RSIP_OTF_Cmd(DISABLE);
}

#if 0 

BOOT_RAM_TEXT_SECTION
VOID *_memset(void *dst0, int Val, SIZE_T length)
{
	if(RomVer == OLD_ROM_VERSION)
		return _memset_v01(dst0, Val, length);
	else
		return _memset_v02(dst0, Val, length);
}

BOOT_RAM_TEXT_SECTION
void *_memcpy( void *s1, const void *s2, SIZE_T n )
{
	if(RomVer == OLD_ROM_VERSION)
		return _memcpy_v01(s1, s2, n);
	else
		return _memcpy_v02(s1, s2, n);
}

BOOT_RAM_TEXT_SECTION
void DelayMs(u32 ms)
{
	if(RomVer == OLD_ROM_VERSION)
		DelayMs_v01(ms);
	else
		DelayMs_v02(ms);
}

BOOT_RAM_TEXT_SECTION
void DelayUs(u32 us)
{
	if(RomVer == OLD_ROM_VERSION)
		DelayUs_v01(us);
	else
		DelayUs_v02(us);

}

BOOT_RAM_TEXT_SECTION
void FLASH_WaitBusy(u32 WaitType)
{
	if(RomVer == OLD_ROM_VERSION)
		FLASH_WaitBusy_v01(WaitType);
	else
		FLASH_WaitBusy_v02(WaitType);

}

BOOT_RAM_TEXT_SECTION
void FLASH_WriteEn(void)
{
	if(RomVer == OLD_ROM_VERSION)
		FLASH_WriteEn_v01();
	else
		FLASH_WriteEn_v02();
}

BOOT_RAM_TEXT_SECTION
void FLASH_Erase(u32 EraseType, u32 Address)
{
	if(RomVer == OLD_ROM_VERSION)
		FLASH_Erase_v01(EraseType, Address);
	else
		FLASH_Erase_v02(EraseType, Address);
}

BOOT_RAM_TEXT_SECTION
void FLASH_RxCmd(u8 cmd, u32 read_len, u8* read_data)
{
	if(RomVer == OLD_ROM_VERSION)
		FLASH_RxCmd_v01(cmd, read_len, read_data);
	else
		FLASH_RxCmd_v02(cmd, read_len, read_data);
}

BOOT_RAM_TEXT_SECTION
void FLASH_SetStatus(u8 Cmd, u32 Len, u8* Status)
{
	if(RomVer == OLD_ROM_VERSION)
		FLASH_SetStatus_v01(Cmd, Len, Status);
	else
		FLASH_SetStatus_v02(Cmd, Len, Status);
}

BOOT_RAM_TEXT_SECTION
void FLASH_TxData12B(u32 StartAddr, u8 DataPhaseLen, u8* pData)
{
	if(RomVer == OLD_ROM_VERSION)
		FLASH_TxData12B_v01(StartAddr, DataPhaseLen, pData);
	else
		FLASH_TxData12B_v02(StartAddr, DataPhaseLen, pData);	
}

BOOT_RAM_TEXT_SECTION
void GPIO_Init(GPIO_InitTypeDef  *GPIO_InitStruct)
{
	if(RomVer == OLD_ROM_VERSION)
		GPIO_Init_v01(GPIO_InitStruct);
	else
		GPIO_Init_v02(GPIO_InitStruct);

}

BOOT_RAM_TEXT_SECTION
void GPIO_WriteBit(u32 GPIO_Pin, u32 Pin_State)
{
	if(RomVer == OLD_ROM_VERSION)
		GPIO_WriteBit_v01(GPIO_Pin, Pin_State);
	else
		GPIO_WriteBit_v02(GPIO_Pin, Pin_State);

}

BOOT_RAM_TEXT_SECTION
void GPIO_Direction(u32 GPIO_Pin, u32 data_direction)
{
	if(RomVer == OLD_ROM_VERSION)
		GPIO_Direction_v01(GPIO_Pin, data_direction);
	else
		GPIO_Direction_v02(GPIO_Pin, data_direction);
}

BOOT_RAM_TEXT_SECTION
char xmodem_uart_readable(void)
{
	if(RomVer == OLD_ROM_VERSION)
		return xmodem_uart_readable_v01();
	else
		return xmodem_uart_readable_v02();

}

BOOT_RAM_TEXT_SECTION
char xmodem_uart_writable(void)
{
	if(RomVer == OLD_ROM_VERSION)
		return xmodem_uart_writable_v01();
	else
		return xmodem_uart_writable_v02();
}

BOOT_RAM_TEXT_SECTION
char xmodem_uart_getc(void)
{
	if(RomVer == OLD_ROM_VERSION)
		return xmodem_uart_getc_v01();
	else
		return xmodem_uart_getc_v02();
}

BOOT_RAM_TEXT_SECTION
void xmodem_uart_putc(char c)
{
	if(RomVer == OLD_ROM_VERSION)
		xmodem_uart_putc_v01(c);
	else
		xmodem_uart_putc_v02(c);

}

BOOT_RAM_TEXT_SECTION
void xmodem_uart_putdata(u8* buf, u32 cnt)
{
	if(RomVer == OLD_ROM_VERSION)
		xmodem_uart_putdata_v01(buf, cnt);
	else
		xmodem_uart_putdata_v02(buf, cnt);

}

BOOT_RAM_TEXT_SECTION
void xmodem_uart_port_init(u8 uart_idx, u8 pin_mux, u32 baud_rate)
{
	if(RomVer == OLD_ROM_VERSION)
		xmodem_uart_port_init_v01(uart_idx, pin_mux, baud_rate);
	else
		xmodem_uart_port_init_v02(uart_idx, pin_mux, baud_rate);

}

BOOT_RAM_TEXT_SECTION
void xmodem_uart_port_deinit(u8 uart_idx)
{
	if(RomVer == OLD_ROM_VERSION)
		xmodem_uart_port_deinit_v01(uart_idx);
	else
		xmodem_uart_port_deinit_v02(uart_idx);

}

BOOT_RAM_TEXT_SECTION
void UART_SetBaud(UART_TypeDef* UARTx, u32 BaudRate)
{
	if(RomVer == OLD_ROM_VERSION)
		UART_SetBaud_v01(UARTx, BaudRate);
	else
		UART_SetBaud_v02(UARTx, BaudRate);
}

BOOT_RAM_TEXT_SECTION
void UART_WaitBusy(UART_TypeDef* UARTx, u32 PollTimes)
{
	if(RomVer == OLD_ROM_VERSION)
		UART_WaitBusy_v01(UARTx, PollTimes);
	else
		UART_WaitBusy_v02(UARTx, PollTimes);
}

BOOT_RAM_TEXT_SECTION
void RCC_PeriphClockCmd(u32 APBPeriph_in, u32 APBPeriph_Clock_in, u8 NewState)
{
	if(RomVer == OLD_ROM_VERSION)
		UART_WaitBusy_v01(APBPeriph_in, APBPeriph_Clock_in, NewState);
	else
		UART_WaitBusy_v02(APBPeriph_in, APBPeriph_Clock_in, NewState);
}

BOOT_RAM_TEXT_SECTION
void Pinmux_Config(u8 PinName, u32 PinFunc)
{
	if(RomVer == OLD_ROM_VERSION)
		Pinmux_Config_v01(PinName, PinFunc);
	else
		Pinmux_Config_v02(PinName, PinFunc);
}


BOOT_RAM_TEXT_SECTION
u32 BKUP_Read(u32 DwordIdx)
{
	if(RomVer == OLD_ROM_VERSION)
		return BKUP_Read_v01(DwordIdx);
	else
		return BKUP_Read_v02(DwordIdx);

}


BOOT_RAM_TEXT_SECTION
void Cache_Flush(void)
{
	if(RomVer == OLD_ROM_VERSION)
		Cache_Flush_v01();
	else
		Cache_Flush_v02();
}


BOOT_RAM_TEXT_SECTION
void io_assert_failed(uint8_t* file, uint32_t line)
{
	if(RomVer == OLD_ROM_VERSION)
		io_assert_failed_v01(file, line);
	else
		io_assert_failed_v02(file, line);

}

BOOT_RAM_TEXT_SECTION
VOID UARTIMG_Download(u8 uart_idx)
{
	if(RomVer == OLD_ROM_VERSION)
		UARTIMG_Download_v01(uart_idx);
	else
		UARTIMG_Download_v02(uart_idx);
}
#endif

