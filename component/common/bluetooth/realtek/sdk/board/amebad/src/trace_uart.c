/**
 * Copyright (c) 2015, Realsil Semiconductor Corporation. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include "trace_uart.h"
#include "bt_board.h"
#include "osif.h"

typedef struct _TraceUartBuffer
{
    uint8_t *tx_buffer;
    uint16_t tx_len;
    bool     tx_switch;
    void    *tx_done_sem;
} TRACE_UART_INFO;

TRACE_UART_INFO g_uart_obj;

#ifdef TRACE_UART_TX_IRQ
static inline void traceuart_stop_tx(TRACE_UART_INFO *trace_pointer)
{
    UART_INTConfig(TRACE_UART_DEV, RUART_IER_ETBEI, DISABLE);
}

static inline void transmit_log(TRACE_UART_INFO *trace_pointer)
{
    int count;
    if (trace_pointer->tx_len == 0)
    {
        traceuart_stop_tx(trace_pointer);
        if (trace_pointer->tx_done_sem)
            osif_sem_give(trace_pointer->tx_done_sem);
        return;
    }

    count = TRACE_COUNT;
    do
    {
        UART_CharPut(TRACE_UART_DEV, *trace_pointer->tx_buffer);
        trace_pointer->tx_buffer++;
        trace_pointer->tx_len--;
    } while (--count > 0 && trace_pointer->tx_len > 0);
}

uint32_t traceuart_irq(void *data)
{
    volatile uint8_t reg_iir;
    uint8_t int_id;
    uint32_t reg_val;
    TRACE_UART_INFO *trace_pointer = (TRACE_UART_INFO *) data;

    reg_iir = UART_IntStatus(TRACE_UART_DEV);
    if ((reg_iir & RUART_IIR_INT_PEND) != 0)
    {
        /* No pending IRQ */
        return 0;
    }

    int_id = (reg_iir & RUART_IIR_INT_ID) >> 1;

    switch (int_id)
    {
        case RUART_TX_FIFO_EMPTY:
            transmit_log(trace_pointer);
            break;
        case RUART_RECEIVE_LINE_STATUS:
            reg_val = (UART_LineStatusGet(TRACE_UART_DEV));
            printf("traceuart_irq: LSR interrupt, reg_val=%x\r\n", reg_val);
            break;
        default:
            printf("traceuart_irq: Unknown interrupt type %x\r\n", int_id);
            break;
    }

    return 0;
}
#endif

bool trace_uart_init(void)
{
    memset(&g_uart_obj, 0, sizeof(g_uart_obj));

    if (!CHECK_SW(EFUSE_SW_TRACE_SWITCH))
    {
        printf("trace_uart_init: TRACE OPEN\r\n");
        g_uart_obj.tx_switch = true;

        Pinmux_Config(TRACE_UART_TX, PINMUX_FUNCTION_UART);
        PAD_PullCtrl(TRACE_UART_TX, GPIO_PuPd_UP);

        UART_InitTypeDef UARTStruct;
        UART_InitTypeDef *pUARTStruct = &UARTStruct;

        UART_StructInit(pUARTStruct);
        pUARTStruct->WordLen = RUART_WLS_8BITS;
        pUARTStruct->StopBit = RUART_STOP_BIT_1;
        pUARTStruct->Parity = RUART_PARITY_DISABLE;
        pUARTStruct->ParityType = RUART_EVEN_PARITY;
        pUARTStruct->StickParity = RUART_STICK_PARITY_DISABLE;

        UART_Init(TRACE_UART_DEV, pUARTStruct);
        UART_SetBaud(TRACE_UART_DEV, TRACE_UART_BAUDRATE);
        UART_RxCmd(TRACE_UART_DEV, DISABLE);

#ifdef TRACE_UART_TX_IRQ
        if (osif_sem_create(&g_uart_obj.tx_done_sem, 0, 1) == false)
        {
            printf("tx_done_sem create fail!\r\n");
            return false;
        }

        InterruptDis(TRACE_UART_IRQ);
        InterruptUnRegister(TRACE_UART_IRQ);
        InterruptRegister((IRQ_FUN)traceuart_irq, TRACE_UART_IRQ, (uint32_t)&g_uart_obj, TRACEUART_IRQ_PRIO);
        InterruptEn(TRACE_UART_IRQ, TRACEUART_IRQ_PRIO);
#endif
    }
    else
    {
        g_uart_obj.tx_switch = false;
    }

    return true;
}

bool trace_uart_deinit(void)
{
    if (!CHECK_SW(EFUSE_SW_TRACE_SWITCH))
    {
        if (g_uart_obj.tx_switch == true)
        {
            UART_DeInit(TRACE_UART_DEV);
#ifdef TRACE_UART_TX_IRQ
            InterruptDis(TRACE_UART_IRQ);
            InterruptUnRegister(TRACE_UART_IRQ);

            if (g_uart_obj.tx_done_sem) {
                osif_sem_delete(g_uart_obj.tx_done_sem);
                g_uart_obj.tx_done_sem = NULL;
            }
#endif
            g_uart_obj.tx_switch = false;
            return true;
        }
        else
        {
            printf("trace_uart_deinit: no need\r\n");
            return false;
        }
    }
    return true;
}

bool trace_uart_tx(uint8_t *pstr, uint16_t len, UART_TX_CB tx_cb)
{
    if (g_uart_obj.tx_switch == false)
    {
        if (tx_cb)
            tx_cb();
        return true;
    }

#ifdef TRACE_UART_TX_IRQ
    g_uart_obj.tx_buffer = pstr;
    g_uart_obj.tx_len = len;

    UART_INTConfig(TRACE_UART_DEV, RUART_IER_ETBEI, ENABLE);

    if (g_uart_obj.tx_done_sem) {
        if (osif_sem_take(g_uart_obj.tx_done_sem, 0xFFFFFFFF) == false) {
            printf("tx_done_sem take fail!\r\n");
            return false;
        }
    }
#else
    UART_SendData(TRACE_UART_DEV, pstr, len);
#endif

    if (tx_cb)
        tx_cb();

    return true;
}

