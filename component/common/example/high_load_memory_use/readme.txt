##################################################################################
#                                                                                #
#                      HIGH-LOAD USE CASE MEMORY USAGE EXAMPLE                   #
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
    This example is used to monitor the memory usage at high_load use case.
        The high load example includes 3 TLS sessions and 6 UDP sessions with 
        5 UDP servers on different ports and 1 UDP client.
    To verify the TLS sessions, you can setup an apache server for yourself 
        and make sure the KeepAliveTimeout is larger than 5s.


Setup Guide
~~~~~~~~~~~
        1. Add example_high_load_memory_use example to SDK
        
        /component/common/example/high_load_memory_use
        .
        |-- example_high_load_memory_use.c
        |-- example_high_load_memory_use.h
        `-- readme.txt

        2. Enable CONFIG_EXAMPLE_HIGH_LOAD_MEMORY_USE in [platform_opts.h]
        /* For high load memory use example */
        #define CONFIG_EXAMPLE_HIGH_LOAD_MEMORY_USE  1
        #define CONFIG_EXAMPLE_WLAN_FAST_CONNECT     0

        3. config the parameters for high load usage
        [lwipopts.h]
            #define MEMP_NUM_NETCONN        20
            #define MEMP_NUM_UDP_PCB        MEMP_NUM_NETCONN
        [FreeRTOSConfig.h]
            // Configure this if the heap size is not enough
            #define configTOTAL_HEAP_SIZE   ( ( size_t ) ( 80 * 1024 ) )


Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Modify the AP SSID/PASSWORD/SECURITY_TYPE to connect to the apache server.
    Modify the http server host to connect to the local apache server IP address.
    Modify the IP/Port used in example_high_load_memory_use.c for udp sessions to make it work properly.
    If you want to use ECDHE as TLS cipher suite, you can modify:
    [config_rsa.h] 
        #define POLARSSL_KEY_EXCHANGE_ECDHE_RSA_ENABLED
        #define POLARSSL_ECDH_C
        #define POLARSSL_ECP_C
Note:
Example work flow:
    Start heap monitor thread
    -> Enable Wi-Fi with STA mode
    -> Connect to AP by WPA2-AES
    -> Start 3 TLS sessions
    -> Start 6 UDP sessions


Result description
~~~~~~~~~~~~~~~~~~
    The example thread will be started automatically when booting.
    To verify the TLS sessions, you can setup an apache server for yourself and make sure the KeepAliveTimeout is larger than 5s.
    To verify UDP server session, you can use iperf with following command to send UDP data:
        $ iperf.exe -c 192.168.1.123 -u -p 6001 -t 30 -i 1
    To verify UDP client session, you can use iperf with following command to start UDP server:
        $ iperf.exe -s -p 6001 -u -i 1


Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported :
            Ameba-1, Ameba-z, Ameba-pro, Ameba-z2, AmebaD, 