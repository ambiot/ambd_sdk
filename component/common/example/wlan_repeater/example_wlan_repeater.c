#include <platform_opts.h>
#include "FreeRTOS.h"
#include "task.h"
#include <platform/platform_stdlib.h>

#include "wifi_constants.h"
#include "wifi_structures.h"
#include "lwip_netconf.h"
#include "wifi_conf.h"

#if CONFIG_EXAMPLE_WLAN_FAST_CONNECT
typedef int (*init_done_ptr)(void);
extern init_done_ptr p_wlan_init_done_callback;
extern int wlan_init_done_callback();
#endif
#if CONFIG_BRIDGE
extern void bridgeif_set_mac_init(char *bmac);
extern void bridgeif_add_port_ap_netif(void);
extern void bridgeif_add_port_sta_netif(void);
#endif

#if CONFIG_EXAMPLE_WLAN_REPEATER

#if CONFIG_LWIP_LAYER
extern struct netif xnetif[NET_IF_NUM]; 
#endif

/**
 * @brief  Wi-Fi example for mode switch case: Mode switching between concurrent mode and STA and add to bridge.
 * @note  Process Flow:
 *              - Disable Wi-Fi
 *              - Enable Wi-Fi with concurrent (STA + AP) mode
 *              - Start AP
 *              - Check AP running
 *              - Connect to AP using STA mode
 */
static void example_wlan_repeater_thread(void *param)
{
	/* To avoid gcc warnings */
	( void ) param;

	// Wait for other task stable.
	vTaskDelay(4000);

	/*********************************************************************************
	*	1. Enable Wi-Fi with concurrent (STA + AP) mode
	*********************************************************************************/
	printf("\n\r[WLAN_REPEATER_EXAMPLE] Enable Wi-Fi with concurrent (STA + AP) mode\n");

	/*********************************************************************************
	*	1-1. Disable Wi-Fi
	*********************************************************************************/
	printf("\n\r[WLAN_REPEATER_EXAMPLE] Disable Wi-Fi\n");
	wifi_off();
	vTaskDelay(20);

	/*********************************************************************************
	*	1-2. Enable Wi-Fi with STA + AP mode
	*********************************************************************************/
	printf("\n\r[WLAN_REPEATER_EXAMPLE] Enable Wi-Fi with STA + AP mode\n");
	if(wifi_on(RTW_MODE_STA_AP) < 0){
		printf("\n\r[WLAN_REPEATER_EXAMPLE] ERROR: wifi_on failed\n");
		return;
	}

	uint8_t *mac = LwIP_GetMAC(&xnetif[0]);
	bridgeif_set_mac_init(mac);
	bridgeif_add_port_sta_netif();
	bridgeif_add_port_ap_netif();

	/*********************************************************************************
	*	1-3. Start AP
	*********************************************************************************/
	printf("\n\r[WLAN_REPEATER_EXAMPLE] Start AP\n");
	char *ssid = "AmebaRPT";
	char *password = "12345678";	// NULL for RTW_SECURITY_OPEN
	int channel = 6;

	if(wifi_start_ap(ssid, (password)?RTW_SECURITY_WPA2_AES_PSK:RTW_SECURITY_OPEN, password, strlen(ssid), (password)?strlen(password):0, channel) < 0) {
		printf("\n\r[WLAN_REPEATER_EXAMPLE] ERROR: wifi_start_ap failed\n");
		return;
	}

	/*********************************************************************************
	*	1-4. Check AP running
	*********************************************************************************/
	printf("\n\r[WLAN_REPEATER_EXAMPLE] Check AP running\n");
	int timeout = 20;
	while(1) {
		char essid[33];
		if(wext_get_ssid(WLAN1_NAME, (unsigned char *) essid) > 0) {
			if(strcmp((const char *) essid, (const char *)ssid) == 0) {
				printf("\n\r[WLAN_REPEATER_EXAMPLE] %s started\n", ssid);
				break;
			}
		}
		if(timeout == 0) {
			printf("\n\r[WLAN_REPEATER_EXAMPLE] ERROR: Start AP timeout\n");
			return;
		}
		vTaskDelay(1 * configTICK_RATE_HZ);
		timeout --;
	}

	/*********************************************************************************
	*	1-5. Connect to AP using STA mode and start DHCP client
	*********************************************************************************/
	printf("\n\r[WLAN_REPEATER_EXAMPLE] Connect to AP\n");
	if(p_wlan_init_done_callback)
		p_wlan_init_done_callback();

	vTaskDelete(NULL);
}

void example_wlan_repeater(char* id){
	if(xTaskCreate(example_wlan_repeater_thread, ((const char*)"example_wlan_repeater_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate failed\n", __FUNCTION__);
}

#endif /* CONFIG_EXAMPLE_WLAN_REPEATER */
