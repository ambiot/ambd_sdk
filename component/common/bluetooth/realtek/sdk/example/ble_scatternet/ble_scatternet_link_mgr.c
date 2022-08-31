/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      link_mgr.c
   * @brief     Multilink manager functions.
   * @author    jane
   * @date      2017-06-06
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
#if ((defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET) || \
	(defined(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) && CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) || \
	(defined(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE))

#include <ble_scatternet_link_mgr.h>
#include <trace_app.h>
#include <string.h>
#include "ftl_app.h"
/*============================================================================*
 *                              Constants
 *============================================================================*/
#if F_BT_LE_USE_STATIC_RANDOM_ADDR
/** @brief  Define start offset of the flash to save static random address. */
#define BLE_SCATTERNET_APP_STATIC_RANDOM_ADDR_OFFSET 0
#endif

/*============================================================================*
 *                              Variables
 *============================================================================*/
/** @addtogroup  CENTRAL_CLIENT_GAP_MSG
    * @{
    */
T_APP_LINK ble_scatternet_app_link_table[BLE_SCATTERNET_APP_MAX_LINKS];

T_DEV_INFO ble_scatternet_dev_list[BLE_SCATTERNET_APP_MAX_DEVICE_INFO];
uint8_t ble_scatternet_dev_list_count = 0;
/** @} */

/*============================================================================*
 *                              Functions
 *============================================================================*/
/** @addtogroup  CENTRAL_SCAN_MGR
    * @{
    */
/**
 * @brief   Add device information to device list.
 *
 * @param[in] bd_addr Peer device address.
 * @param[in] bd_type Peer device address type.
 * @retval true Success.
 * @retval false Failed, device list is full.
 */
bool ble_scatternet_link_mgr_add_device(uint8_t *bd_addr, uint8_t bd_type)
{
    /* If result count not at max */
    if (ble_scatternet_dev_list_count < BLE_SCATTERNET_APP_MAX_DEVICE_INFO)
    {
        uint8_t i;
        /* Check if device is already in device list*/
        for (i = 0; i < ble_scatternet_dev_list_count; i++)
        {
            if (memcmp(bd_addr, ble_scatternet_dev_list[i].bd_addr, GAP_BD_ADDR_LEN) == 0)
            {
                return true;
            }
        }

        /*Add addr to device list list*/
        memcpy(ble_scatternet_dev_list[ble_scatternet_dev_list_count].bd_addr, bd_addr, GAP_BD_ADDR_LEN);
        ble_scatternet_dev_list[ble_scatternet_dev_list_count].bd_type = bd_type;

        /*Increment device list count*/
        ble_scatternet_dev_list_count++;
    }
    else
    {
        return false;
    }
    return true;
}

/**
 * @brief Clear device list.
 * @retval None.
 */
void ble_scatternet_link_mgr_clear_device_list(void)
{
    ble_scatternet_dev_list_count = 0;
}
/** @} */
/** @addtogroup  SCATTERNET_APP
    * @{
    */
/** @defgroup  SCATTERNET_RANDOM Static Random Address Storage
    * @brief Use @ref F_BT_LE_USE_STATIC_RANDOM_ADDR to open
    * @{
    */
#if F_BT_LE_USE_STATIC_RANDOM_ADDR
/**
 * @brief   Save static random address information into flash.
 * @param[in] p_addr Pointer to the buffer for saving data.
 * @retval 0 Save success.
 * @retval other Failed.
 */
uint32_t ble_scatternet_app_save_static_random_address(T_APP_STATIC_RANDOM_ADDR *p_addr)
{
    APP_PRINT_INFO0("ble_scatternet_app_save_static_random_address");
    return ftl_save(p_addr, BLE_SCATTERNET_APP_STATIC_RANDOM_ADDR_OFFSET, sizeof(T_APP_STATIC_RANDOM_ADDR));
}
/**
  * @brief  Load static random address information from storage.
  * @param[out]  p_addr Pointer to the buffer for loading data.
  * @retval 0 Load success.
  * @retval other Failed.
  */
uint32_t ble_scatternet_app_load_static_random_address(T_APP_STATIC_RANDOM_ADDR *p_addr)
{
    uint32_t result;
    result = ftl_load(p_addr, BLE_SCATTERNET_APP_STATIC_RANDOM_ADDR_OFFSET,
                      sizeof(T_APP_STATIC_RANDOM_ADDR));
    APP_PRINT_INFO1("ble_scatternet_app_load_static_random_address: result 0x%x", result);
    if (result)
    {
        memset(p_addr, 0, sizeof(T_APP_STATIC_RANDOM_ADDR));
    }
    return result;
}
#endif
/** @} */
/** @} */
#endif
