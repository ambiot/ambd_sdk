/**
 * Copyright (c) 2015, Realsil Semiconductor Corporation. All rights reserved.
 *
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "ameba_soc.h"

#define hci_board_debug    printf

#define TRACE_UART_TX_IRQ

#define TRACE_UART_BAUDRATE    1500000

#define TRACE_UART_DEV    UART3_DEV
#define TRACE_UART_IRQ    UARTLP_IRQ
#define TRACE_UART_TX     _PA_26

#ifdef TRACE_UART_TX_IRQ
#define TRACE_COUNT           16    //ONE IRQ send DATA LEN
#define TRACEUART_IRQ_PRIO    12
#endif

#define TRACE_TASK_PRIO    3
#define TRACE_TASK_STACK_SIZE    0x200

#define BT_DEFAUT_LMP_SUBVER    0x8721

#define HCI_START_IQK
#define HCI_WRITE_IQK

#define MERGE_PATCH_ADDRESS_OTA1  0x080F8000
#define MERGE_PATCH_ADDRESS_OTA2  0x081F8000
#define MERGE_PATCH_SWITCH_ADDR   0x08003028
#define MERGE_PATCH_SWITCH_SINGLE 0xAAAAAAAA

#define CALI_IQK_RF_STEP0    0x4000
#define CALI_IQK_RF_STEP1    0x0180
#define CALI_IQK_RF_STEP2    0x3800
#define CALI_IQK_RF_STEP3F   0x0400

#define LEFUSE(x)    (x-0x190)

#define EFUSE_SW_USE_FLASH_PATCH     BIT0
#define EFUSE_SW_BT_FW_LOG           BIT1
#define EFUSE_SW_RSVD                BIT2
#define EFUSE_SW_HCI_OUT             BIT3
#define EFUSE_SW_UPPERSTACK_SWITCH   BIT4
#define EFUSE_SW_TRACE_SWITCH        BIT5
#define EFUSE_SW_DRIVER_DEBUG_LOG    BIT6
#define EFUSE_SW_RSVD2               BIT7

#define CHECK_SW(x)                  (HAL_READ32(SPI_FLASH_BASE, FLASH_SYSTEM_DATA_ADDR + 0x28) & x)

extern uint8_t rltk_wlan_is_mp(void);

#ifdef __cplusplus
}
#endif

#endif

