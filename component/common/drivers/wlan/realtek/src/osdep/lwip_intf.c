/******************************************************************************
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2016, Realtek Semiconductor Corporation. All rights reserved. 
  *
******************************************************************************/

//#define _LWIP_INTF_C_
#include <autoconf.h>
#include <lwip_intf.h>
#if (CONFIG_LWIP_LAYER == 1)
#include <lwip/netif.h>
#endif
#if !defined(CONFIG_MBED_ENABLED)
#include <lwip_netconf.h>
#include <ethernetif.h>
#endif
#include <osdep_service.h>
#include <wifi/wifi_util.h>

#ifdef WIFI_PERFORMANCE_MONITOR
#include <wifi_performance_monitor.h>
#else
#define WIFI_MONITOR_TIMER_START(x) 
#define WIFI_MONITOR_TIMER_END(x, len) 
#endif
//----- ------------------------------------------------------------------
// External Reference
//----- ------------------------------------------------------------------
#if (CONFIG_LWIP_LAYER == 1)
extern struct netif xnetif[];			//LWIP netif
#endif

/**
 *      rltk_wlan_set_netif_info - set netif hw address and register dev pointer to netif device
 *      @idx_wlan: netif index
 *			    0 for STA only or SoftAP only or STA in STA+SoftAP concurrent mode, 
 *			    1 for SoftAP in STA+SoftAP concurrent mode
 *      @dev: register netdev pointer to LWIP. Reserved.
 *      @dev_addr: set netif hw address
 *
 *      Return Value: None
 */     
void rltk_wlan_set_netif_info(int idx_wlan, void * dev, unsigned char * dev_addr)
{
#if (CONFIG_LWIP_LAYER == 1)
#if defined(CONFIG_MBED_ENABLED)
	//rtw_memcpy(xnetif[idx_wlan]->hwaddr, dev_addr, 6);
	//set netif hwaddr later
#else
	rtw_memcpy(xnetif[idx_wlan].hwaddr, dev_addr, 6);
	xnetif[idx_wlan].state = dev;
#endif
#endif
}

/**
 *      rltk_wlan_send - send IP packets to WLAN. Called by low_level_output().
 *      @idx: netif index
 *      @sg_list: data buffer list
 *      @sg_len: size of each data buffer
 *      @total_len: total data len
 *
 *      Return Value: None
 */     
int rltk_wlan_send(int idx, struct eth_drv_sg *sg_list, int sg_len, int total_len)
{
#if (CONFIG_LWIP_LAYER == 1)
	struct eth_drv_sg *last_sg;
	struct sk_buff *skb = NULL;
	int ret = 0;
	
	WIFI_MONITOR_TIMER_START(wifi_time_test.wlan_send_time);
	if(idx == -1){
		DBG_ERR("netif is DOWN");
		return -1;
	}
	DBG_TRACE("%s is called", __FUNCTION__);

	save_and_cli();
	if (rltk_wlan_check_isup(idx)) {
		rltk_wlan_tx_inc(idx);
	} else {
		DBG_ERR("netif is DOWN");
		restore_flags();
		return -1;
	}
	restore_flags();
	
	WIFI_MONITOR_TIMER_START(wifi_time_test.wlan_send_time1);
	skb = rltk_wlan_alloc_skb(total_len);
	WIFI_MONITOR_TIMER_END(wifi_time_test.wlan_send_time1, total_len);
	if (skb == NULL) {
		//DBG_ERR("rltk_wlan_alloc_skb() for data len=%d failed!", total_len);
		ret = -1;
		goto exit;
	}
	WIFI_MONITOR_TIMER_START(wifi_time_test.wlan_send_time2);
	for (last_sg = &sg_list[sg_len]; sg_list < last_sg; ++sg_list) {
		rtw_memcpy(skb->tail, (void *)(sg_list->buf), sg_list->len);
		skb_put(skb,  sg_list->len);
	}
	WIFI_MONITOR_TIMER_END(wifi_time_test.wlan_send_time2, total_len);

	WIFI_MONITOR_TIMER_START(wifi_time_test.wlan_send_skb_time);
	rltk_wlan_send_skb(idx, skb);
	WIFI_MONITOR_TIMER_END(wifi_time_test.wlan_send_skb_time, total_len);
	WIFI_MONITOR_TIMER_END(wifi_time_test.wlan_send_time, total_len);

exit:
	save_and_cli();
	rltk_wlan_tx_dec(idx);
	restore_flags();
	return ret;
#endif
}

/**
 *      rltk_wlan_recv - indicate packets to LWIP. Called by ethernetif_recv().
 *      @idx: netif index
 *      @sg_list: data buffer list
 *      @sg_len: size of each data buffer
 *
 *      Return Value: None
 */     
void rltk_wlan_recv(int idx, struct eth_drv_sg *sg_list, int sg_len)
{
#if (CONFIG_LWIP_LAYER == 1)
	struct eth_drv_sg *last_sg;
	struct sk_buff *skb;
	
	DBG_TRACE("%s is called", __FUNCTION__);
	if(idx == -1){
		DBG_ERR("skb is NULL");
		return;
	}
	skb = rltk_wlan_get_recv_skb(idx);
	DBG_ASSERT(skb, "No pending rx skb");

	for (last_sg = &sg_list[sg_len]; sg_list < last_sg; ++sg_list) {
		if (sg_list->buf != 0) {
			rtw_memcpy((void *)(sg_list->buf), skb->data, sg_list->len);
			skb_pull(skb, sg_list->len);
		}
	}
#endif
}

int netif_is_valid_IP(int idx, unsigned char *ip_dest)
{
#if defined(CONFIG_MBED_ENABLED)
	return 1;
#else
#if CONFIG_LWIP_LAYER == 1
	struct netif * pnetif = &xnetif[idx];

	ip_addr_t addr = { 0 };

#ifdef CONFIG_MEMORY_ACCESS_ALIGNED
	unsigned int temp;
	memcpy(&temp, ip_dest, sizeof(unsigned int));
	u32_t *ip_dest_addr = &temp;
#else
	u32_t *ip_dest_addr  = (u32_t*)ip_dest;
#endif

#if LWIP_VERSION_MAJOR >= 2
	ip_addr_set_ip4_u32(&addr, *ip_dest_addr);
#else
	addr.addr = *ip_dest_addr;
#endif

#if (LWIP_VERSION_MAJOR >= 2)
	if((ip_addr_get_ip4_u32(netif_ip_addr4(pnetif))) == 0)
		return 1;
#else

	if(pnetif->ip_addr.addr == 0)
		return 1;
#endif

	if(ip_addr_ismulticast(&addr) || ip_addr_isbroadcast(&addr,pnetif)){
		return 1;
	}

	//if(ip_addr_netcmp(&(pnetif->ip_addr), &addr, &(pnetif->netmask))) //addr&netmask
	//	return 1;

	if(ip_addr_cmp(&(pnetif->ip_addr),&addr))
		return 1;

	DBG_TRACE("invalid IP: %d.%d.%d.%d ",ip_dest[0],ip_dest[1],ip_dest[2],ip_dest[3]);
#endif	
#ifdef CONFIG_DONT_CARE_TP
	if(pnetif->flags & NETIF_FLAG_IPSWITCH)
		return 1;
	else
#endif
	return 0;
#endif
}

#if !defined(CONFIG_MBED_ENABLED)
int netif_get_idx(struct netif* pnetif)
{
#if (CONFIG_LWIP_LAYER == 1)
	int idx = pnetif - xnetif;

	switch(idx) {
	case 0:
		return 0;
	case 1:
		return 1;
	default:
		return -1;
	}
#else	
	return -1;
#endif
}

unsigned char *netif_get_hwaddr(int idx_wlan)
{
#if (CONFIG_LWIP_LAYER == 1)
	return xnetif[idx_wlan].hwaddr;
#else
	return NULL;
#endif
}
#endif

#if defined(CONFIG_MBED_ENABLED)
emac_callback emac_callback_func = NULL;
void *emac_callback_data = NULL;
void set_callback_func(emac_callback p, void *data)
{
	emac_callback_func = p;
	emac_callback_data = data;
}
#endif

void netif_rx(int idx, unsigned int len)
{
	WIFI_MONITOR_TIMER_START(wifi_time_test.netif_rx_time);
#if (CONFIG_LWIP_LAYER == 1)
#if defined(CONFIG_MBED_ENABLED)
	emac_callback_func(emac_callback_data, NULL, len);
#else
	ethernetif_recv(&xnetif[idx], len);
#endif
#endif
#if (CONFIG_INIC_EN == 1)
        inic_netif_rx(idx, len);
#endif
	WIFI_MONITOR_TIMER_END(wifi_time_test.netif_rx_time, len);
}

void netif_post_sleep_processing(void)
{
#if (CONFIG_LWIP_LAYER == 1)
#if defined(CONFIG_MBED_ENABLED)
#else
	lwip_POST_SLEEP_PROCESSING();	//For FreeRTOS tickless to enable Lwip ARP timer when leaving IPS - Alex Fang
#endif
#endif
}

void netif_pre_sleep_processing(void)
{
#if (CONFIG_LWIP_LAYER == 1)
#if defined(CONFIG_MBED_ENABLED)
#else
	lwip_PRE_SLEEP_PROCESSING();
#endif
#endif
}

#ifdef CONFIG_WOWLAN
int rtw_default_netif_idx = 0;
void rltk_wlan_set_default_idx(int idx){
#if (CONFIG_LWIP_LAYER == 1)
	rtw_default_netif_idx = idx;
#endif
	return;
}

unsigned char *rltk_wlan_get_ip(int idx){
#if (CONFIG_LWIP_LAYER == 1)
	if(rtw_default_netif_idx)
		return LwIP_GetIP(&xnetif[rtw_default_netif_idx]);
	else
		return LwIP_GetIP(&xnetif[idx]);
#else
	return NULL;
#endif

}
unsigned char *rltk_wlan_get_gw(int idx){
#if (CONFIG_LWIP_LAYER == 1)
		if(rtw_default_netif_idx)
			return LwIP_GetGW(&xnetif[rtw_default_netif_idx]);
		else
			return LwIP_GetGW(&xnetif[idx]);
#else
		return NULL;
#endif

}

unsigned char *rltk_wlan_get_gwmask(int idx){
#if (CONFIG_LWIP_LAYER == 1)
		if(rtw_default_netif_idx)
			return LwIP_GetMASK(&xnetif[rtw_default_netif_idx]);
		else
			return LwIP_GetMASK(&xnetif[idx]);
#else
		return NULL;
#endif

}
#endif

