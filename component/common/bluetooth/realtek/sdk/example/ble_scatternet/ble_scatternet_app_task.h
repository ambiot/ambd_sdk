/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      app_task.h
   * @brief     Routines to create App task and handle events & messages
   * @author    jane
   * @date      2017-06-02
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */
#ifndef _APP_TASK_H_
#define _APP_TASK_H_

/**
 * @brief  Initialize App task
 * @return void
 */
void ble_scatternet_send_msg(uint16_t sub_type);
void ble_scatternet_app_task_init(void);
void ble_peripheral_ble_central_concurrent_app_task_init(void);
void ble_scatternet_app_task_deinit(void);

#endif

