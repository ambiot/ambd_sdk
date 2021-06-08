WIFI REPEATER EXAMPLE

Description:
	Provide scenario of using bridge interface and wlan concurrent mode to support Wi-Fi repeater.

Supported List:
	Ameba D

Configuration:
	// platform_opts.h
	#define CONFIG_EXAMPLE_WLAN_REPEATER	1
	#define CONFIG_BRIDGE	1

Execution:
	The Wi-Fi repeater example thread will be started automatically when booting.

Note:
	Use component/common/drivers/wlan/realtek/src/core/option/rtw_opt_skbuf.c and increase skb number if skb is not enough.

