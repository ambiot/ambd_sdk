/******************************************************************************
 * Copyright (c) 2020-2021 Realtek Semiconductor Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
  ******************************************************************************
  * @file    example_wifi_conn_pri_cond.h
  * @author  Andrew Su
  * @version V1.0.0
  * @brief   This file provides user's callback to modify the priority to connect
  *          the same SSID and security APs. If pr_conn_pri_cond_cb is NULL,
  *          WiFi will use the default strategy instead for customer's strategy.
  ******************************************************************************
  */
#ifndef __EXAMPLE_WIFI_CONN_PRI_COND_H__
#define __EXAMPLE_WIFI_CONN_PRI_COND_H__

/* -------------------------------- Includes -------------------------------- */
/* external head files */
#include "freertos_service.h"
#include "wlan_bssdef.h"
#include "platform_opts.h"
//#include <drv_types.h>

/* internal head files */

/* -------------------------------- Defines --------------------------------- */

/* -------------------------------- Macros ---------------------------------- */

/* ------------------------------- Data Types ------------------------------- */

/* ---------------------------- Global Variables ---------------------------- */
typedef bool (*rtw_conn_pri_cond_cb_t)(WLAN_BSSID_EX *old_ap, WLAN_BSSID_EX *new_ap);
extern rtw_conn_pri_cond_cb_t pr_conn_pri_cond_cb;

/* -------------------------- Function declaration -------------------------- */
void example_init_conn_pri_cond(void);

#endif /* __EXAMPLE_WIFI_CONN_PRI_COND_H__ */
