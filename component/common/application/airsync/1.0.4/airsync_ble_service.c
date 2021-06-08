enum { __FILE_NUM__ = 0 };

/**
*********************************************************************************************************
*               Copyright(c) 2014, Realtek Semiconductor Corporation. All rights reserved.
**********************************************************************************************************
* @file     airsync_ble_service.c
* @brief    simple BLE profile source file.
* @details  Demonstration of how to implement a self-definition profile.
* @author
* @date     2015-5-10
* @version  v0.1
*********************************************************************************************************
*/
#include <platform_opts_bt.h>
#if defined(CONFIG_BT_AIRSYNC_CONFIG) && CONFIG_BT_AIRSYNC_CONFIG
#include "trace_app.h"
#include "string.h"
#include "bt_airsync_config_app_task.h"
#include "airsync_ble_service.h"
#include "app_msg.h"
/********************************************************************************************************
* local static variables defined here, only used in this source file.
********************************************************************************************************/
/**<  Value of simple read characteristic. */
static uint8_t airsync_rx_buffer[255];

/**<  Function pointer used to send event to application from simple profile. Initiated in AirSyncBleService_AddService. */
static P_FUN_SERVER_GENERAL_CB pfn_airsync_cb = NULL;


/**< @brief  profile/service definition.  */
const T_ATTRIB_APPL airsync_ble_service_tbl[] =
{
    /* <<Primary Service>>, 0.. */
    {
        (ATTRIB_FLAG_VALUE_INCL | ATTRIB_FLAG_LE),  /* wFlags     */
        {   /* bTypeValue */
            LO_WORD(GATT_UUID_PRIMARY_SERVICE),
            HI_WORD(GATT_UUID_PRIMARY_SERVICE),
            LO_WORD(GATT_UUID_AIRSYNC_SERVICE),      /* service UUID */
            HI_WORD(GATT_UUID_AIRSYNC_SERVICE)
        },
        UUID_16BIT_SIZE,                            /* bValueLen     */
        NULL,                                       /* pValueContext */
        GATT_PERM_READ                              /* wPermissions  */
    },

    /* <<Characteristic>>, 1..*/
    {
        ATTRIB_FLAG_VALUE_INCL,                     /* wFlags */
        {   /* bTypeValue */
            LO_WORD(GATT_UUID_CHARACTERISTIC),
            HI_WORD(GATT_UUID_CHARACTERISTIC),
            GATT_CHAR_PROP_WRITE  /* characteristic properties */
            /* characteristic UUID not needed here, is UUID of next attrib. */
        },
        1,                                          /* bValueLen */
        NULL,
        GATT_PERM_READ                              /* wPermissions */
    },
    {
        ATTRIB_FLAG_VALUE_APPL,                     /* wFlags */
        {   /* bTypeValue */
            LO_WORD(GATT_UUID_AIRSYNC_CHAR_WRITE),
            HI_WORD(GATT_UUID_AIRSYNC_CHAR_WRITE)
        },
        0,                                          /* bValueLen */
        (void *)NULL,
        GATT_PERM_READ | GATT_PERM_WRITE                              /* wPermissions */
    },

    /* <<Characteristic>> 3..*/
    {
        ATTRIB_FLAG_VALUE_INCL,                     /* wFlags */
        {   /* bTypeValue */
            LO_WORD(GATT_UUID_CHARACTERISTIC),
            HI_WORD(GATT_UUID_CHARACTERISTIC),
            GATT_CHAR_PROP_INDICATE                    /* characteristic properties */
            /* characteristic UUID not needed here, is UUID of next attrib. */
        },
        1,                                          /* bValueLen */
        NULL,
        GATT_PERM_READ                              /* wPermissions */
    },
    {
        ATTRIB_FLAG_VALUE_APPL,                     /* wFlags */
        {   /* bTypeValue */
            LO_WORD(GATT_UUID_AIRSYNC_CHAR_INDICATION),
            HI_WORD(GATT_UUID_AIRSYNC_CHAR_INDICATION)
        },
        0,                                          /* bValueLen */
        NULL,
        GATT_PERM_NONE                              /* wPermissions */
    },
    /* client characteristic configuration */
    {
        ATTRIB_FLAG_VALUE_INCL | ATTRIB_FLAG_CCCD_APPL,                 /* wFlags */
        {   /* bTypeValue */
            LO_WORD(GATT_UUID_CHAR_CLIENT_CONFIG),
            HI_WORD(GATT_UUID_CHAR_CLIENT_CONFIG),
            /* NOTE: this value has an instantiation for each client, a write to */
            /* this attribute does not modify this default value:                */
            LO_WORD(GATT_CLIENT_CHAR_CONFIG_DEFAULT), /* client char. config. bit field */
            HI_WORD(GATT_CLIENT_CHAR_CONFIG_DEFAULT)
        },
        2,                                          /* bValueLen */
        NULL,
        (GATT_PERM_READ | GATT_PERM_WRITE)          /* wPermissions */
    },
    /* <<Characteristic>> 6..*/
    {
        ATTRIB_FLAG_VALUE_INCL,                     /* wFlags */
        {   /* bTypeValue */
            LO_WORD(GATT_UUID_CHARACTERISTIC),
            HI_WORD(GATT_UUID_CHARACTERISTIC),
            GATT_CHAR_PROP_READ  /* characteristic properties */
            /* characteristic UUID not needed here, is UUID of next attrib. */
        },
        1,                                          /* bValueLen */
        NULL,
        GATT_PERM_READ                              /* wPermissions */
    },
    {
        ATTRIB_FLAG_VALUE_APPL,                     /* wFlags */
        {   /* bTypeValue */
            LO_WORD(GATT_UUID_AIRSYNC_CHAR_READ),
            HI_WORD(GATT_UUID_AIRSYNC_CHAR_READ)
        },
        0,                                          /* bValueLen */
        NULL,
        GATT_PERM_READ                              /* wPermissions */
    },
};

extern bool bt_airsync_config_app_send_msg_to_apptask(T_IO_MSG *p_msg);

/**
 * @brief read characteristic data from service.
 *
 * @param ServiceId          ServiceID of characteristic data.
 * @param iAttribIndex          Attribute index of getting characteristic data.
 * @param iOffset                Used for Blob Read.
 * @param piLength            length of getting characteristic data.
 * @param ppValue            data got from service.
 * @return Profile procedure result
*/
T_APP_RESULT  airsync_service_attr_read_cb(uint8_t conn_id, T_SERVER_ID service_id,
                                           uint16_t attrib_index,
                                           uint16_t offset, uint16_t *p_length, uint8_t **pp_value)
{
    (void) conn_id;
    (void) service_id;
    (void) offset;
    (void) p_length;
    (void) pp_value;
    T_APP_RESULT  cause  = APP_RESULT_SUCCESS;

    switch (attrib_index)
    {
    default:
        APP_PRINT_ERROR1("<-- airsync_attr_read_cb, Attr not found, index=%d", attrib_index);
        cause  = APP_RESULT_ATTR_NOT_FOUND;
        break;
    case GATT_UUID_AIRSYNC_CHAR_READ_INDEX:
        {
            break;
        }
    }

    return cause;
}



/**
 * @brief write characteristic data from service.
 *
 * @param ServiceID          ServiceID to be written.
 * @param iAttribIndex          Attribute index of characteristic.
 * @param wLength            length of value to be written.
 * @param pValue            value to be written.
 * @return Profile procedure result
*/
T_APP_RESULT airsync_service_attr_write_cb(uint8_t conn_id, T_SERVER_ID service_id,
                                           uint16_t attrib_index, T_WRITE_TYPE write_type, uint16_t length, uint8_t *p_value,
                                           P_FUN_WRITE_IND_POST_PROC *p_write_ind_post_proc)
{
    (void) conn_id;
    (void) service_id;
    (void) write_type;
    (void) p_write_ind_post_proc;

    T_APP_RESULT  cause = APP_RESULT_SUCCESS;
    T_IO_MSG airsync_msg;

    if (p_value == NULL)
    {
        APP_PRINT_ERROR0("airsync_attr_write_cb, p_value is NULL");
        cause  = APP_RESULT_INVALID_VALUE_SIZE;
        return cause;
    }

    switch (attrib_index)
    {
    default:
        APP_PRINT_ERROR2("--> airsync_attr_write_cb Error  attrib_index = 0x%x length=%d",
                         attrib_index, length);
        cause = APP_RESULT_ATTR_NOT_FOUND;
        break;
    case GATT_UUID_AIRSYNC_CHAR_WRITE_INDEX:
        {
            airsync_rx_buffer[0] = length;
            memcpy(airsync_rx_buffer + 1, p_value, length);
            airsync_msg.type = IO_MSG_TYPE_WRISTBNAD;
            airsync_msg.subtype = IO_MSG_WAS_RX_VALUE;
            airsync_msg.u.buf = airsync_rx_buffer;

            bt_airsync_config_app_send_msg_to_apptask(&airsync_msg);
            break;
        }
    }
    return cause;
}


/**
 * @brief update CCCD bits from stack.
 *
 * @param ServiceId          Service ID.
 * @param Index          Attribute index of characteristic data.
 * @param wCCCBits         CCCD bits from stack.
 * @return None
*/
void airsync_service_cccd_update_cb(uint8_t conn_id, T_SERVER_ID service_id, uint16_t index,
                                    uint16_t cccbits)
{
    T_WAS_CALLBACK_DATA callback_data;
    bool is_handled = false;
    callback_data.conn_id = conn_id;
    callback_data.msg_type = SERVICE_CALLBACK_TYPE_INDIFICATION_NOTIFICATION;
    APP_PRINT_INFO2("airsync_service_cccd_update_cb  Index = %d wCCCDBits %x", index, cccbits);

    switch (index)
    {
    case GATT_UUID_AIRSYNC_CHAR_INDICATION_CCCD_INDEX:
        {
            if (cccbits & GATT_CLIENT_CHAR_CONFIG_INDICATE)
            {
                APP_PRINT_INFO0("air sync indication is enabled...");
                callback_data.msg_data.notification_indification_index = GATT_UUID_AIRSYNC_CHAR_INDICATION_ENABLE;
            }
            else
            {
                APP_PRINT_INFO0("air sync indication is disabled...");
                callback_data.msg_data.notification_indification_index = GATT_UUID_AIRSYNC_CHAR_INDICATION_DISABLE;
            }
            is_handled =  true;
            break;
        }

    default:
        break;
    }
    /* Notify Application. */
    if (pfn_airsync_cb && (is_handled == true))
    {
        pfn_airsync_cb(service_id, (void *)&callback_data);
    }
}

/**
 * @brief Simple ble Service Callbacks.
*/
const T_FUN_GATT_SERVICE_CBS airsync_service_cbs =
{
    airsync_service_attr_read_cb,  // Read callback function pointer
    airsync_service_attr_write_cb,  // Write callback function pointer
    airsync_service_cccd_update_cb,  // CCCD update callback function pointer
};

/**
  * @brief add Simple BLE service to application.
  *
  * @param[in] pFunc          pointer of app callback function called by profile.
  * @return service ID auto generated by profile layer.
  * @retval ServiceId
  */
T_SERVER_ID airsync_add_service(void *p_func)
{
    uint8_t airsync_service_id;
    if (false == server_add_service(&airsync_service_id,
                                    (uint8_t *)airsync_ble_service_tbl,
                                    sizeof(airsync_ble_service_tbl),
                                    airsync_service_cbs))
    {
        airsync_service_id = 0xff;
        return airsync_service_id;
    }
    pfn_airsync_cb = (P_FUN_SERVER_GENERAL_CB)p_func;
    return airsync_service_id;
}

#endif
