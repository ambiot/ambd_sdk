#ifndef __EXAMPLE_WIFI_ROAMING_H__
#define __EXAMPLE_WIFI_ROAMING_H__

//fast reconnect callback fun
extern write_reconnect_ptr p_roaming_start_callback;
extern wlan_init_done_ptr p_wlan_init_done_callback;
extern write_reconnect_ptr p_write_reconnect_ptr;

void example_tickless_wifi_roaming_init(void);
void example_tickless_wifi_roaming(void);
#endif