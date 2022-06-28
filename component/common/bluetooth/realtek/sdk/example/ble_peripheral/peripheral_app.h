/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      peripheral_app.h
   * @brief     This file handles BLE peripheral application routines.
   * @author    jane
   * @date      2017-06-06
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */

#ifndef _PERIPHERAL_APP__
#define _PERIPHERAL_APP__

#ifdef __cplusplus
extern "C" {
#endif
/*============================================================================*
 *                              Header Files
 *============================================================================*/
#include <app_msg.h>
#include <gap_le.h>
#include <profile_server.h>
#include <app_common_flags.h>

/*============================================================================*
 *                              Variables
 *============================================================================*/
extern T_SERVER_ID simp_srv_id; /**< Simple ble service id*/
extern T_SERVER_ID bas_srv_id;  /**< Battery service id */

/*============================================================================*
 *                              Constants
 *============================================================================*/
/** @addtogroup  PERIPHERAL_APP
    * @{
    */
#if (F_BT_LE_USE_RANDOM_ADDR == 1)
typedef struct
{
	uint8_t 	 is_exist;
	uint8_t 	 reserved;		   /**< remote BD type*/
	uint8_t 	 bd_addr[GAP_BD_ADDR_LEN];	/**< remote BD */
} T_APP_STATIC_RANDOM_ADDR;
#endif

/*============================================================================*
 *                              Functions
 *============================================================================*/

/**
 * @brief    All the application messages are pre-handled in this function
 * @note     All the IO MSGs are sent to this function, then the event handling
 *           function shall be called according to the MSG type.
 * @param[in] io_msg  IO message data
 * @return   void
 */
void app_handle_io_msg(T_IO_MSG io_msg);

/**
 * @brief    All the BT Profile service callback events are handled in this function
 * @note     Then the event handling function shall be called according to the
 *           service_id.
 * @param[in] service_id  Profile service ID
 * @param[in] p_data      Pointer to callback data
 * @return   Indicates the function call is successful or not
 * @retval   result @ref T_APP_RESULT
 */
T_APP_RESULT app_profile_callback(T_SERVER_ID service_id, void *p_data);

/**
  * @brief Callback for gap le to notify app
  * @param[in] cb_type callback msy type @ref GAP_LE_MSG_Types.
  * @param[in] p_cb_data point to callback data @ref T_LE_CB_DATA.
  * @retval result @ref T_APP_RESULT
  */
T_APP_RESULT app_gap_callback(uint8_t cb_type, void *p_cb_data);

void app_vendor_callback(uint8_t cb_type, void *p_cb_data);

#if (F_BT_LE_USE_RANDOM_ADDR == 1)
/**
 * @brief   Save static random address information into flash.
 * @param[in] p_addr Pointer to the buffer for saving data.
 * @retval 0 Save success.
 * @retval other Failed.
 */
uint32_t ble_peripheral_app_save_static_random_address(T_APP_STATIC_RANDOM_ADDR *p_addr);

/**
  * @brief  Load static random address information from storage.
  * @param[out]  p_addr Pointer to the buffer for loading data.
  * @retval 0 Load success.
  * @retval other Failed.
  */
uint32_t ble_peripheral_app_load_static_random_address(T_APP_STATIC_RANDOM_ADDR *p_addr);
#endif

#ifdef __cplusplus
}
#endif

#endif

