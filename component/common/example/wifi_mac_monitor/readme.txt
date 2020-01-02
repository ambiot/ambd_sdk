##################################################################################
#                                                                                #
#                           example_wifi_mac_monitor                             #
#                                                                                #
##################################################################################

Date: 2018-06-11

Table of Contents
~~~~~~~~~~~~~~~~~
 - Description
 - Setup Guide
 - Parameter Setting and Configuration
 - Result description
 - Supported List

 
Description
~~~~~~~~~~~
        This example shows how to get station mac information in AP mode.
	
Setup Guide
~~~~~~~~~~~
        In platform_opts.h, please set 	#define CONFIG_EXAMPLE_WIFI_MAC_MONITOR 1
	
Result description
~~~~~~~~~~~~~~~~~~
        When define CONFIG_EXAMPLE_WIFI_MAC_MONITOR, the callback function is automatically registered as get_station_mac().

Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        This example will collect the station mac address and rssi.

Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported IC :
                Ameba-pro, Ameba-z2