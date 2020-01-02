##################################################################################
#                                                                                #
#                             Example mdns                                       #
#                                                                                #
##################################################################################

Date: 2018-05-29

Table of Contents
~~~~~~~~~~~~~~~~~
 - Description
 - Setup Guide
 - Result description
 - Other Reference
 - Supported List

 
Description
~~~~~~~~~~~
        An example to use the mdns APIs in example_mdns.c. 
	
Setup Guide
~~~~~~~~~~~
	To execute this example automatically when booting, the CONFIG_EXAMPLE_MDNS in platform_opts.h
        must be enabled as the follows. LWIP IGMP should also be enabled to support multicast.

        /* lwipopts.h */
        #define LWIP_IGMP 1
        /* platform_opts.h *.
        #define CONFIG_EXAMPLE_MDNS 1

        In example, operations on mDNS responder and service are presented. 
        If device Wi-Fi connection is setup by fast reconnect (Please refer to readme of fast reconnect example), 
        the mDNS responder could be started after IP address is available. An example service is registered,
        updated. Finally, the mDNS responder is stopped.
	
Result description
~~~~~~~~~~~~~~~~~~
        To discover service in network, the ¡§dns-sd¡¨ command provided in Bonjour SDK can be used.
        Bonjour SDK is available on Apple developer support site, and can be downloaded by Apple
        developer. In the following, ¡§dns-sd -B¡¨ command is used to browse for service instance of type
        ¡§_service1¡¨, and service of ¡§ameba._service1._tcp.local.¡¨ is found. ¡§dns-sd -L¡¨ command is used
        to look up this service instance, and the content of service text record is shown. After service
        update operation, the original content of ¡§text1=text1_cotent, text2=text2_content¡¨ is updated
        to ¡§text1=text1_content_new¡¨.

Other Reference
~~~~~~~~~~~~~~~
        For more details, please refer to AN0043 Realtek mDNS User Guide.pdf

Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported :
	    Ameba-1, Ameba-z, Ameba-pro