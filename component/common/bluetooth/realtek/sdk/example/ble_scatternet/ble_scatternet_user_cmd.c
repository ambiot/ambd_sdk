/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      user_cmd.c
   * @brief     User defined test commands.
   * @details  User command interfaces.
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
#if defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET
#if	defined (CONFIG_BT_USER_COMMAND) && (CONFIG_BT_USER_COMMAND)
#include <string.h>
#include <trace_app.h>
#include <gap_bond_le.h>
#include <gap_scan.h>
#include <user_cmd.h>
#include <gap.h>
#include <gap_conn_le.h>
#include <gcs_client.h>
#include <stdio.h>
#include <ble_scatternet_app_flags.h>
/** @defgroup  CENTRAL_CLIENT_CMD Central Client User Command
    * @brief This file handles Central Client User Command.
    * @{
    */
/*============================================================================*
 *                              Variables
 *============================================================================*/
/** @brief User command interface data, used to parse the commands from Data UART. */
T_USER_CMD_IF    ble_scatternet_user_cmd_if;

#if F_BT_LE_5_0_SET_PHY_SUPPORT
/**
 * @brief Set the PHY preferences for the connection
 *
 * <b>Command table define</b>
 * \code{.c}
    {
        "setphy",
        "setphy [conn_id] [type]\n\r",
        "Set the PHY preferences for the connection\r\n\
        [type]: 0-(1M), 1-(2M), 2-(CODED-S8), 3-(CODED-S2), 4-(tx 2M, rx 1M) \n\r",
        cmd_setphy
    },
 * \endcode
 */
static T_USER_CMD_PARSE_RESULT cmd_setphy(T_USER_CMD_PARSED_VALUE *p_parse_value)
{
    uint8_t conn_id = p_parse_value->dw_param[0];
    uint8_t all_phys;
    uint8_t tx_phys;
    uint8_t rx_phys;
    T_GAP_PHYS_OPTIONS phy_options = GAP_PHYS_OPTIONS_CODED_PREFER_S8;
    T_GAP_CAUSE cause;

    if (p_parse_value->dw_param[1] == 0)
    {
        all_phys = GAP_PHYS_PREFER_ALL;
        tx_phys = GAP_PHYS_PREFER_1M_BIT;
        rx_phys = GAP_PHYS_PREFER_1M_BIT;
    }
    else if (p_parse_value->dw_param[1] == 1)
    {
        all_phys = GAP_PHYS_PREFER_ALL;
        tx_phys = GAP_PHYS_PREFER_2M_BIT;
        rx_phys = GAP_PHYS_PREFER_2M_BIT;
    }
    else if (p_parse_value->dw_param[1] == 2)
    {
        all_phys = GAP_PHYS_PREFER_ALL;
        tx_phys = GAP_PHYS_PREFER_CODED_BIT;
        rx_phys = GAP_PHYS_PREFER_CODED_BIT;
        phy_options = GAP_PHYS_OPTIONS_CODED_PREFER_S8;
    }
    else if (p_parse_value->dw_param[1] == 3)
    {
        all_phys = GAP_PHYS_PREFER_ALL;
        tx_phys = GAP_PHYS_PREFER_CODED_BIT;
        rx_phys = GAP_PHYS_PREFER_CODED_BIT;
        phy_options = GAP_PHYS_OPTIONS_CODED_PREFER_S2;
    }
    else
    {
        all_phys = GAP_PHYS_NO_PREFER_TX_BIT;
        tx_phys = GAP_PHYS_PREFER_2M_BIT;
        rx_phys = GAP_PHYS_PREFER_1M_BIT;
    }
    cause = le_set_phy(conn_id, all_phys, tx_phys, rx_phys, phy_options);

    return (T_USER_CMD_PARSE_RESULT)cause;
}
#endif

const T_USER_CMD_TABLE_ENTRY ble_scatternet_user_cmd_table[] =
{
#if F_BT_LE_5_0_SET_PHY_SUPPORT
    {
        "setphy",
        "setphy [conn_id] [type]\n\r",
        "Set the PHY preferences for the connection\r\n\
        [type]: 0-(1M), 1-(2M), 2-(CODED-S8), 3-(CODED-S2), 4-(tx 2M, rx 1M) \n\r",
        cmd_setphy
    },
#endif
    /* MUST be at the end: */
    {
        0,
        0,
        0,
        0
    }
};
/** @} */ /* End of group SCATTERNET_CMD */

#endif
#endif
