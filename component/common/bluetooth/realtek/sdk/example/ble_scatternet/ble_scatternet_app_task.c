/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      app_task.c
   * @brief     Routines to create App task and handle events & messages
   * @author    jane
   * @date      2017-06-02
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */

/*============================================================================*
 *                              Header Files
 *============================================================================*/
#include <platform_opts_bt.h>
#if defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET
#include <os_msg.h>
#include <os_task.h>
#include <gap.h>
#include <gap_le.h>
#include <trace_app.h>
#include <ble_scatternet_app_task.h>
#include <app_msg.h>
#include <ble_scatternet_app.h>
#include <data_uart.h>
#include <user_cmd_parse.h>
#include "ble_scatternet_user_cmd.h"
#include <basic_types.h>
#include <gap_msg.h>

/** @defgroup  CENTRAL_CLIENT_APP_TASK Central Client App Task
    * @brief This file handles the implementation of application task related functions.
    *
    * Create App task and handle events & messages
    * @{
    */
/*============================================================================*
 *                              Macros
 *============================================================================*/
#define BLE_SCATTERNET_APP_TASK_PRIORITY             1         //!< Task priorities
#define BLE_SCATTERNET_APP_TASK_STACK_SIZE           256 * 6   //!<  Task stack size
#define BLE_SCATTERNET_MAX_NUMBER_OF_GAP_MESSAGE     0x20      //!<  GAP message queue size
#define BLE_SCATTERNET_MAX_NUMBER_OF_IO_MESSAGE      0x20      //!<  IO message queue size
#define BLE_SCATTERNET_MAX_NUMBER_OF_EVENT_MESSAGE   (BLE_SCATTERNET_MAX_NUMBER_OF_GAP_MESSAGE + BLE_SCATTERNET_MAX_NUMBER_OF_IO_MESSAGE)    //!< Event message queue size

/*============================================================================*
 *                              Variables
 *============================================================================*/
void *ble_scatternet_app_task_handle;   //!< APP Task handle
void *ble_scatternet_evt_queue_handle;  //!< Event queue handle
void *ble_scatternet_io_queue_handle;   //!< IO queue handle

extern T_GAP_DEV_STATE ble_scatternet_gap_dev_state;
extern int ble_scatternet_central_app_max_links;
extern int ble_scatternet_peripheral_app_max_links;


/*============================================================================*
 *                              Functions
 *============================================================================*/
void ble_scatternet_send_msg(uint16_t sub_type)
{
    uint8_t event = EVENT_IO_TO_APP;

    T_IO_MSG io_msg;

    io_msg.type = IO_MSG_TYPE_QDECODE;
    io_msg.subtype = sub_type;

    if (ble_scatternet_evt_queue_handle != NULL && ble_scatternet_io_queue_handle != NULL) {
        if (os_msg_send(ble_scatternet_io_queue_handle, &io_msg, 0) == false) {
            data_uart_print("ble scatternet send msg fail: subtype 0x%x", io_msg.subtype);
        } else if (os_msg_send(ble_scatternet_evt_queue_handle, &event, 0) == false) {
            data_uart_print("ble scatternet send event fail: subtype 0x%x", io_msg.subtype);
        }
    }
}

void ble_scatternet_app_main_task(void *p_param);

/**
 * @brief  Initialize App task
 * @return void
 */
void ble_scatternet_app_task_init(void)
{
    os_task_create(&ble_scatternet_app_task_handle, "ble_scatternet_app", ble_scatternet_app_main_task, 0, BLE_SCATTERNET_APP_TASK_STACK_SIZE,
                   BLE_SCATTERNET_APP_TASK_PRIORITY);
}

/**
 * @brief        App task to handle events & messages
 * @param[in]    p_param    Parameters sending to the task
 * @return       void
 */
void ble_scatternet_app_main_task(void *p_param)
{
    (void) p_param;
    uint8_t event;

    os_msg_queue_create(&ble_scatternet_io_queue_handle, BLE_SCATTERNET_MAX_NUMBER_OF_IO_MESSAGE, sizeof(T_IO_MSG));
    os_msg_queue_create(&ble_scatternet_evt_queue_handle, BLE_SCATTERNET_MAX_NUMBER_OF_EVENT_MESSAGE, sizeof(uint8_t));

    gap_start_bt_stack(ble_scatternet_evt_queue_handle, ble_scatternet_io_queue_handle, BLE_SCATTERNET_MAX_NUMBER_OF_GAP_MESSAGE);

    data_uart_init(ble_scatternet_evt_queue_handle, ble_scatternet_io_queue_handle);
#if	defined (CONFIG_BT_USER_COMMAND) && (CONFIG_BT_USER_COMMAND)
    user_cmd_init(&ble_scatternet_user_cmd_if, "ble_scatternet");
#endif

    while (true)
    {
        if (os_msg_recv(ble_scatternet_evt_queue_handle, &event, 0xFFFFFFFF) == true)
        {
            if (event == EVENT_IO_TO_APP)
            {
                T_IO_MSG io_msg;
                if (os_msg_recv(ble_scatternet_io_queue_handle, &io_msg, 0) == true)
                {
                    ble_scatternet_app_handle_io_msg(io_msg);
                }
            }
            else
            {
                gap_handle_msg(event);
            }
        }
    }
}

void ble_scatternet_app_task_deinit(void)
{
	if (ble_scatternet_app_task_handle) {
		os_task_delete(ble_scatternet_app_task_handle);
	}
	if (ble_scatternet_io_queue_handle) {
		os_msg_queue_delete(ble_scatternet_io_queue_handle);
	}
	if (ble_scatternet_evt_queue_handle) {
		os_msg_queue_delete(ble_scatternet_evt_queue_handle);
	}
	ble_scatternet_io_queue_handle = NULL;
	ble_scatternet_evt_queue_handle = NULL;
	ble_scatternet_app_task_handle = NULL;

	ble_scatternet_gap_dev_state.gap_init_state = 0;
	ble_scatternet_gap_dev_state.gap_adv_sub_state = 0;
	ble_scatternet_gap_dev_state.gap_adv_state = 0;
	ble_scatternet_gap_dev_state.gap_scan_state = 0;
	ble_scatternet_gap_dev_state.gap_conn_state = 0;

	ble_scatternet_central_app_max_links = 0;
	ble_scatternet_peripheral_app_max_links = 0;

}


/** @} */ /* End of group CENTRAL_CLIENT_APP_TASK */
#endif

