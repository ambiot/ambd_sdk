/********************************************************************************
 * Copyright (c) 2014, Realtek Semiconductor Corp.
 * All rights reserved.
 *
 * This module is a confidential and proprietary property of RealTek and
 * possession or use of this module requires written permission of RealTek.
 *******************************************************************************
 */
#include "ameba_soc.h"
#include "rtl8721d_floader.h"

#ifdef IMAGE_WRITE_PARSER
BOOT_RAM_TEXT_SECTION
__INLINE u32 Get_FlashWriteMethod(void)
{
	return HAL_READ32(PERI_ON_BASE, REG_LP_SYSTEM_CFG2) & (BIT_SOC_XMODEM_FLASH_EMPTY | BIT_SOC_XMODEM_PAGE_PG);
}
#endif

BOOT_RAM_TEXT_SECTION
__INLINE u32 Get_LogUartPinmux(void)
{
	//TO DO
	//HAL_READ32(SYSTEM_CTRL_BASE, REG_SYS_EFUSE_SYSCFG6) & BIT_SYS_UART2_DEFAULT_GPIO
	return 1;
}

BOOT_RAM_TEXT_SECTION
__INLINE void Reboot_Uart_Download(void)
{
	BKUP_Set(0, BIT_UARTBURN_BOOT);
	NVIC_SystemReset();
}

