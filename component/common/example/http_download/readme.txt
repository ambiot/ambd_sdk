d##################################################################################
#                                                                                #
#                           example_http_download                                #
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
        This example downloads file from Web server via http.
	
Setup Guide
~~~~~~~~~~~
        In platform_opts.h, please set #define CONFIG_EXAMPLE_HTTP_DOWNLOAD    1

Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Modify SERVER_HOST, SERVER_PORT and RESOURCE in example_http_download.c based on your HTTP server
        Can make automatical Wi-Fi connection when booting by using wlan fast connect example..
	
Result description
~~~~~~~~~~~~~~~~~~
        A http download example thread will be started automatically when booting.
	
Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported IC :
                Ameba-pro, Ameba-z2, AmebaD