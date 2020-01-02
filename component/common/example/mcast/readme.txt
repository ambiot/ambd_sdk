##################################################################################
#                                                                                #
#                             example_mcast                                      #
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
        This example will join multicast group of 224.0.0.251 and listen on port 5353 
        Send packet with the content of received packet to multicast group of 224.0.0.251
	
Setup Guide
~~~~~~~~~~~
	In lwipopts.h, please set #define LWIP_UDP  and #define LWIP_IGMP    1
        In platform_opts.h  #define CONFIG_EXAMPLE_MCAST    1

Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Can make automatical Wi-Fi connection when booting by using wlan fast connect example.
		
Result description
~~~~~~~~~~~~~~~~~~
        A multicast example thread will be started automatically when booting.

Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported IC :
                Ameba-pro, Ameba-z2