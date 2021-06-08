##################################################################################
#                                                                                #
#                           example_wlan_fast_connect                            #
#                                                                                #
##################################################################################

Date: 2020-01-15

Table of Contents
~~~~~~~~~~~~~~~~~
 - Description
 - Setup Guide
 - Parameter Setting and Configuration
 - Result description
 - Supported List

 
Description
~~~~~~~~~~~
        This example shows after wifi init done, wlan driver call function to check whether auto-connect is required, and if previous saved wlan profile exists in flash, this example will execute connection.
	
Setup Guide
~~~~~~~~~~~
        In platform_opts.h, please set #define CONFIG_EXAMPLE_WLAN_FAST_CONNECT 1

Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        If you never connect any wifi before enable fast connect, you need connect any wifi first, then reboot to see wifi fast connect.
	
Result description
~~~~~~~~~~~~~~~~~~
		UART Log(Never connect any wifi before reboot): 
			[FAST_CONNECT] Fast connect profile is empty, abort fast connection


		UART Log(Connect any wifi before reboot, and this AP still can be detected after reboot): 
			RTL8721D[Driver]: set ssid [XXX(wlan_name)] 

			RTL8721D[Driver]: rtw_set_wpa_ie[521]: AuthKeyMgmt = 0xX (X=0,2,4,8...) 
		
			RTL8721D[Driver]: start auth to XX:XX:XX:XX:XX:XX(MAC address)
		
			RTL8721D[Driver]: auth success, start assoc
		
			RTL8721D[Driver]: association success(res=3)
			wlan1: 1 DL RSVD page success! DLBcnCount:01, poll:00000001
			
			RTL8721D[Driver]: set pairwise key to hw: alg:X(WEP40-1 WEP104-5 TKIP-2 AES-4) (X=1,2,4,5)
		
			RTL8721D[Driver]: set group key to hw: alg:X(WEP40-1 WEP104-5 TKIP-2 AES-4) keyid:Y (X=1,2,4,5) (Y=0,1)
		
			Interface 0 IP address : XXX.XXX.XXX.XXX

        
		UART Log(Connect any wifi before reboot, but this AP didn't exit yet): 
			RTL8721D[Driver]: set ssid [XXX(wlan_name)] 
			wifi retry
			(repeat five times)

			auto reconnect ...

			RTL8721D[Driver]: set ssid [XXX(wlan_name)]
			(repeat eight times)

Supported List
~~~~~~~~~~~~~~
[Supported List]
	Supported :
	    Ameba-1, Ameba-z, Ameba-pro, Ameba-z2, AmebaD