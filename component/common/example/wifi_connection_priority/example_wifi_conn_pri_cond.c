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
  * @file    example_wifi_conn_pri_cond.c
  * @author  Andrew Su
  * @version V1.0.0
  * @brief   This file provides user's callback to modify the priority to connect
  *          the same SSID and security APs. If pr_conn_pri_cond_cb is NULL,
  *          WiFi will use the default strategy instead for customer's strategy.
  ******************************************************************************
  */
#ifndef __EXAMPLE_WIFI_CONN_PRI_COND_C__
#define __EXAMPLE_WIFI_CONN_PRI_COND_C__
/* -------------------------------- Includes -------------------------------- */
/* external head files */

/* internal head files */
#include "example_wifi_conn_pri_cond.h"

/* -------------------------------- Defines --------------------------------- */

/* -------------------------------- Macros ---------------------------------- */

/* ------------------------------- Data Types ------------------------------- */

/* -------------------------- Function declaration -------------------------- */

/* ---------------------------- Global Variables ---------------------------- */

/* ---------------------------- Private Functions --------------------------- */

#if defined(CONFIG_EXAMPLE_CONN_PRI_COND) && CONFIG_EXAMPLE_CONN_PRI_COND
/* The below code is a sample for customer to configure the priority to choose
 * which AP to be connected. */
/** Priority to connect AP function
 *
 * @param old_ap: A pointer to the old ap
 * @param new_ap: A pointer to the new ap
 *
 * RETURN:
 *		_TRUE: need to replace old AP with new AP.
 *		_FALSE: keep old AP.
 *
 * if to meet the condition, the new ap will replace the old_ap co be connected.
 * old_ap->Configuration.DSConfig is used to get channel, it's value is the channel
 *	number.
 * old_ap->Rssi is uesed to get the RSSI for this AP.
 */
static bool wifi_conn_pri_condition(WLAN_BSSID_EX *old_ap, WLAN_BSSID_EX *new_ap)
{
	bool ret = _FALSE;
	/* The delta RSSI, It can be defined by customer. */
	int delta_rssi = 15;

	/* Below is the strategy to choose whtether to replace old AP with new AP. */
	if ((old_ap->Configuration.DSConfig > 14) && (new_ap->Configuration.DSConfig <= 14)) {
		/* old AP is 5G and new AP is 2.4G */
		if (old_ap->Configuration.DSConfig - new_ap->Configuration.DSConfig > delta_rssi) {
			/* The RSSI of 5G is better than 2.4G, and the value is more
			 * than threshold. So to connect the 5G. */
			printf("%s, New AP is 2.4G, but don't reach the RSSI threshold. Keep it!\n\r", __func__);
			ret = _FALSE;
		} else {
			printf("%s, New AP is 2.4G, switch to connect to new AP.\n\r", __func__);
			ret = _TRUE;
		}
	} else if ((old_ap->Configuration.DSConfig <= 14) && (new_ap->Configuration.DSConfig > 14)) {
		/* old AP is 2.4G and new AP is 5G */
		if (new_ap->Configuration.DSConfig - old_ap->Configuration.DSConfig > delta_rssi) {
			/* The RSSI of 5G is better than 2.4G, and the value is more
			 * than threshold. So to connect the 5G. */
			printf("%s, New AP is 5G, but reach the RSSI threshold. Replace it!\n\r", __func__);
			ret = _TRUE;
		} else {
			printf("%s, New AP is 5G, Keep old AP.\n\r", __func__);
			ret = _FALSE;
		}
	} else if (old_ap->Rssi < new_ap->Rssi) {
		/* same band, but new AP's RSSI is better than old RSSI. */
		ret = _TRUE;
	} else {
		/* same band, but new AP's RSSI is worse than old RSSI. */
		ret = _FALSE;
	}

	return ret;
}

/* ---------------------------- Public Functions ---------------------------- */

/* Assigne the wifi_conn_pri_condition to pr_conn_pri_cond_cb. */
void example_init_conn_pri_cond(void) {
	pr_conn_pri_cond_cb = wifi_conn_pri_condition;
}

#else

/* ---------------------------- Public Functions ---------------------------- */

void example_init_conn_pri_cond(void) {
	pr_conn_pri_cond_cb = NULL;
}
#endif /* Customer to do */

#endif /* __EXAMPLE_WIFI_CONN_PRI_COND_C__ */
