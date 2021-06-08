##################################################################################
#                                                                                #
#                       EXAMPLE_WIFI_CONNECTION_PRIORITY                         #
#                                                                                #
##################################################################################

Date: 2020-08-28

Table of Contents
~~~~~~~~~~~~~~~~~
 - Description
 - Setup Guide
 - Parameter Setting and Configuration
 - Result description 
 - Supported list


Description
~~~~~~~~~~~
	This file provides user's callback to modify the priority to connect
	the same SSID and security APs. If pr_conn_pri_cond_cb is NULL,
	WiFi will use the default strategy instead for customer's strategy. 


Setup Guide
~~~~~~~~~~~
        Enable CONFIG_EXAMPLE_CONN_PRI_COND in [platform_opts.h]
        /*For wifi connection priority example*/
        #define CONFIG_EXAMPLE_CONN_PRI_COND        1


Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	The below code is a sample for customer to configure the priority to choose
	which AP to be connected.
	Priority to connect AP function

	@param old_ap: A pointer to the old ap
	@param new_ap: A pointer to the new ap

	RETURN:
		_TRUE: need to replace old AP with new AP.
		_FALSE: keep old AP.

	if to meet the condition, the new ap will replace the old_ap co be connected.
	old_ap->Configuration.DSConfig is used to get channel, it's value is the channel
	number.
	old_ap->Rssi is uesed to get the RSSI for this AP.

	static bool wifi_conn_pri_condition(WLAN_BSSID_EX *old_ap, WLAN_BSSID_EX *new_ap)



Result description
~~~~~~~~~~~~~~~~~~
	RETURN:
		_TRUE: need to replace old AP with new AP.
		_FALSE: keep old AP.


Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported IC:
            Ameba-D, 