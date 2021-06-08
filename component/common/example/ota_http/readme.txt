##################################################################################
#                                                                                #
#                      OTA HTTP UPDATING EXAMPLE                                 #
#                                                                                #
##################################################################################

Date: 2019-10-24

Table of Contents
~~~~~~~~~~~~~~~~~
 - Description
 - Setup Guide
 - Parameter Setting and Configuration
 - Result description
 - Supported List


Description
~~~~~~~~~~~
    This example is designed for firmware update by Over-the-air programming (OTA) via
        Wireless Network Connection. Download OTA_ALL.bin from the http download server
        (in tools\DownloadServer(HTTP)) automatically.


Setup Guide
~~~~~~~~~~~
        1. Add ota_http example to SDK
        
        /component/common/example/ota_http
        .
        |-- example_ota_http.c
        |-- example_ota_http.h
        `-- readme.txt
        
        2. Enable CONFIG_EXAMPLE_OTA_HTTP in [platform_opts.h]
        /* For http ota update example */
        #define CONFIG_EXAMPLE_OTA_HTTP     1

        3. Enable HTTP_OTA_UPDATE 
        [rtl8721d_ota.h]/[rtl8710b_ota.h]/[ota_8195a.h]/[ota_8195b.h]/[ota_8710c.h]
            #define HTTP_OTA_UPDATE
        

Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Modify PORT, HOST and RESOURCE based on your HTTP download server.
        eg: SERVER: http://m-apps.oss-cn-shenzhen.aliyuncs.com/051103061600.bin
        set:    #define PORT    80
                #define HOST    "m-apps.oss-cn-shenzhen.aliyuncs.com"
                #define RESOURCE    "051103061600.bin"
        For local local network download, Set it with IP and OTA_ALL.bin
        e.g.    #define PORT    80
                #define HOST    "192.168.1.100"
                #define RESOURCE    "OTA_ALL.bin"
        Note: Remember to Set the server start.bat with the same PORT and RESOURCE.


Result description
~~~~~~~~~~~~~~~~~~
    Make automatical Wi-Fi connection when booting by using wlan fast connect example.
    A http download example thread will be started automatically when booting.
    Using the example with the tool in tools\DownloadServer(HTTP) with RESOURCE file.


Supported List
~~~~~~~~~~~~~~
[Supported Lis]
        Supported IC:
                Ameba-1, Ameba-pro, Ameba-z2, AmebaD, 
        Source code not in project:
                Ameba-z