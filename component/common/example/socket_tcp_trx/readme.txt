##################################################################################
#                                                                                #
#                           example_socket_tcp_trx                               #
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
        Example of TCP bidirectional transmission with use two threads for TCP tx/rx on one socket.
        Example 1 uses non-blocking recv and semaphore for TCP send/recv mutex.
        Example 2 does not use any synchronization mechanism, but can only run correctly on lwip with TCPIP thread msg api patch.
	
Setup Guide
~~~~~~~~~~~
        In platform_opts.h:
        To run example 1 in example_socket_tcp_trx_1.c, please set #define CONFIG_EXAMPLE_SOCKET_TCP_TRX    1
        To run example 2 in example_socket_tcp_trx_2.c, please set #define CONFIG_EXAMPLE_SOCKET_TCP_TRX    2

Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Modify SERVER_PORT in example_socket_tcp_trx.c for listen port.
        Can make automatical Wi-Fi connection when booting by using wlan fast connect example.
	
Result description
~~~~~~~~~~~~~~~~~~
        A socket TCP trx example thread will be started automatically when booting. A TCP server will be started to wait for connection.
        Can use a TCP client connecting to this server to start a TCP bidirectional transmission.

Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported IC :
                Ameba-pro, Ameba-z2