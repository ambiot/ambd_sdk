#include <autoconf.h>
#include <FreeRTOS.h>
#include "task.h"
#include <platform/platform_stdlib.h>
#include <wifi/wifi_conf.h>
#include <lwip_netconf.h>
#include "netif.h"

#ifndef WLAN0_NAME
#define WLAN0_NAME		"wlan0"
#endif
#ifndef WLAN1_NAME
#define WLAN1_NAME		"wlan1"
#endif

#ifndef ETH_ALEN
#define ETH_ALEN 			6
#endif

#define SCAN_BUFLEN 500 	//each scan list length= 14 + ssid_length(32MAX). so SCAN_BUFLEN should be AP_NUM*(14+32) at least
#define RSSI_THRESHOLD -65
#define MAX_POLLING_COUNT 5
#define MAX_AP_NUM 3

typedef struct wifi_roaming_ap
{
	u8 	ssid[33];
	u8 	bssid[ETH_ALEN];
	u8	channel;
	rtw_security_t		security_type;
	u8 	password[65];
	u8	key_idx;
	s32	rssi;		
#if CONFIG_LWIP_LAYER
	u8	ip[4];
#endif
}wifi_roaming_ap_t;

#if CONFIG_LWIP_LAYER
extern struct netif xnetif[NET_IF_NUM]; 
#endif
static wifi_roaming_ap_t * ap_list[MAX_AP_NUM]={0};
static u32 ap_count = 0;//scanned AP NUM
static u8 pscan_enable = _FALSE; // if set _TRUE, please set pscan_channel_list
static u8 pscan_channel_list[]={1,3,5};// set by customer

u32 wifi_roaming_find_ap_from_scan_buf(char*buf, int buflen, char *target_ssid, void *user_data)
{
	wifi_roaming_ap_t *pwifi = (wifi_roaming_ap_t *)user_data;
	wifi_roaming_ap_t * candicate,*temp;
	u32 i,j,plen = 0;	
	pwifi->rssi = -100;//init

	while(plen < buflen)
	{
		u32 len, ssid_len, security_mode, security_type, channel;
		s32 rssi;
		u8 *mac, *ssid;				
		// len
		len = (int)*(buf + plen);
		// check end
		if(len == 0|| len == strlen(target_ssid)) break;// if len == ssid_len, it means driver dont do scan,maybe it is busy now, buf detail is the same as it initialized
		// mac
		mac =(u8*)(buf + plen + 1);
		// rssi
		rssi = *(s32*)(buf + plen + 1 + 6);
		// security_mode offset = 11
		security_mode = (u8)*(buf + plen + 1 + 6 + 4);
		switch(security_mode){
			case IW_ENCODE_ALG_NONE:
				security_type = RTW_SECURITY_OPEN;
				break;
			case IW_ENCODE_ALG_WEP:
				security_type = RTW_SECURITY_WEP_PSK;
				break;
			case IW_ENCODE_ALG_TKIP:
				security_type = RTW_SECURITY_WPA_TKIP_PSK;
				break;
			case IW_ENCODE_ALG_CCMP:
				security_type = RTW_SECURITY_WPA2_AES_PSK;
				break;
			default:
				break;
		}
		// channel
		channel = *(buf + plen + 1 + 6 + 4 + 1 + 1);
		// ssid
		ssid_len = len - 1 - 6 - 4 - 1 - 1 - 1;
		ssid = (u8*)(buf + plen + 1 + 6 + 4 + 1 + 1 + 1);
		if(pwifi->security_type == security_type ||
		((pwifi->security_type & (WPA2_SECURITY|WPA_SECURITY))&&(security_type & (WPA2_SECURITY|WPA_SECURITY)))){
			if(ap_count < MAX_AP_NUM){
				candicate = (wifi_roaming_ap_t *)malloc(sizeof(wifi_roaming_ap_t));
				if(!candicate)
				{
					printf("\r\n malloc buf for AP info fail!");
					break;
				}
				memset(candicate, 0 , sizeof(wifi_roaming_ap_t));
				memcpy(candicate->ssid, ssid, ssid_len);
				memcpy(candicate->bssid, mac, ETH_ALEN);
				candicate->channel = channel;
				candicate->security_type = security_type;
				memcpy(candicate->password, pwifi->password, strlen((char const*)pwifi->password));
				candicate->key_idx = pwifi->key_idx;
				candicate->rssi = rssi;
				ap_list[ap_count++] = candicate;
			}
		}
		plen += len;			
	}
	
	for(i = 0; i < ap_count; i++)
	{
		for(j = 0; j < ap_count -1 -i ; j++)	
			if(ap_list[j]->rssi < ap_list[j+1]->rssi ){
				temp = ap_list[j];
				ap_list[j] = ap_list[j+1];
				ap_list[j+1]= temp;
			}
	}	
	return 0;
}

void wifi_ip_changed_hdl( u8* buf, u32 buf_len, u32 flags, void* userdata) 
{
	//todo for customer
	printf("\r\n IP has channged!");
}
void wifi_roaming_thread(void *param)
{
	rtw_wifi_setting_t	setting;
	wifi_roaming_ap_t	roaming_ap;
	int	ap_rssi;
	u32	i = 0, polling_count =0;
	u8	*pscan_config = NULL;
	u8	pscan_connect = PSCAN_ENABLE;
	memset(&setting, 0, sizeof(rtw_wifi_setting_t));
	memset(&roaming_ap, 0, sizeof(wifi_roaming_ap_t));
	roaming_ap.rssi = -100;
#if CONFIG_LWIP_LAYER
	uint8_t *IP = LwIP_GetIP(&xnetif[0]);
#endif

	while(1)
	{
		if(wifi_is_up(RTW_STA_INTERFACE)&&(RTW_SUCCESS == wifi_is_ready_to_transceive(RTW_STA_INTERFACE)))
		{
			wifi_get_rssi(&ap_rssi);
			if( (ap_rssi < RSSI_THRESHOLD))
			{
				if( polling_count >= (MAX_POLLING_COUNT-1))
				{
					wifi_get_setting(WLAN0_NAME,&setting);
					strcpy((char*)roaming_ap.ssid, (char const*)setting.ssid);
					roaming_ap.security_type =  setting.security_type;
					strcpy((char*)roaming_ap.password, (char const*)setting.password);
					roaming_ap.key_idx = setting.key_idx;

					if(RTW_ERROR == wifi_get_ap_bssid(roaming_ap.bssid))
						printf("\r\n get AP BSSID FAIL!");
#if CONFIG_LWIP_LAYER
					memcpy(roaming_ap.ip, IP, 4);
#endif		
					if(pscan_enable == _TRUE)
					{
						pscan_config = (u8*)malloc(strlen((char const*)pscan_channel_list));
						if(pscan_config == NULL)
						{
							printf("\r\n malloc pscan_config fail!");
						}else
						{
							memset(pscan_config, PSCAN_ENABLE, sizeof(pscan_channel_list));
							wifi_set_pscan_chan(pscan_channel_list, pscan_config, sizeof(pscan_channel_list));
						}
					}
					wifi_scan_networks_with_ssid((int (*)(char *, int, char *, void *))wifi_roaming_find_ap_from_scan_buf, (void *)&roaming_ap, SCAN_BUFLEN, (char*)roaming_ap.ssid, strlen((char const*)roaming_ap.ssid));
#if CONFIG_AUTO_RECONNECT
					wifi_set_autoreconnect(0);
#endif
					
					i = 0;
connect_ap:
					if(ap_list[i] && memcmp(roaming_ap.bssid, ap_list[i]->bssid, ETH_ALEN))
					{									
						u8 retry_time = 0;
						while(1)
						{
							wifi_set_pscan_chan(&ap_list[i]->channel, &pscan_connect,1);
							if( RTW_SUCCESS == wifi_connect_bssid(ap_list[i]->bssid, (char*)ap_list[i]->ssid,ap_list[i]->security_type,
								(char*)ap_list[i]->password, ETH_ALEN, strlen((char const*)ap_list[i]->ssid), strlen((char const*)ap_list[i]->password), ap_list[i]->key_idx, NULL ))
							{
#if CONFIG_LWIP_LAYER	
								wifi_reg_event_handler(WIFI_EVENT_IP_CHANGED, (rtw_event_handler_t)wifi_ip_changed_hdl, NULL);

								LwIP_DHCP(0, DHCP_START);
								
								if(memcmp(roaming_ap.ip, IP, 4))
								{
									wifi_indication(WIFI_EVENT_IP_CHANGED, NULL,0, 0);
									wifi_unreg_event_handler(WIFI_EVENT_IP_CHANGED,(rtw_event_handler_t) wifi_ip_changed_hdl);
								}
#endif								
								break;
							}
							
							retry_time ++;
							if(retry_time >3){
								i++;
								goto connect_ap;	
							}
						}					
					}
					
					while(ap_count)
					{
						free (ap_list[ap_count-1]);
						ap_count--;
					}	
					memset(ap_list, 0, sizeof(ap_list));
					
					if(pscan_enable == _TRUE && pscan_config != NULL)
						free(pscan_config);

					polling_count = 0;	
#if CONFIG_AUTO_RECONNECT
					wifi_set_autoreconnect(1);
#endif					
				}else				
				polling_count++;
			}else
				polling_count = 0;
		}
		vTaskDelay(2000);// 2s
	}
	//vTaskDelete(NULL);
}

void example_wifi_roaming(void)
{
	if(xTaskCreate(wifi_roaming_thread, ((const char*)"wifi_roaming_thread"), 1024, NULL, tskIDLE_PRIORITY + 1 , NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(wifi_roaming_thread) failed", __FUNCTION__);

	return;
}
