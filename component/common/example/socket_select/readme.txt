##################################################################################
#                                                                                #
#                          example_socket_select                                 #
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
	This example shows how to use socket select() to handle socket read from clients or remote server.
	
Setup Guide
~~~~~~~~~~~
	1. In [platform_opts.h], please setting #define CONFIG_EXAMPLE_SOCKET_SELECT 1
        2. Can make automatical Wi-Fi connection when booting by using wlan fast connect example.
	
Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        1. Modify SERVER_PORT definition for listen port of created TCP server.
        2. Can enable CONNECT_REMOTE to include TCP connection to remote server in example. 
        3. Modify REMOTE_HOST and REMOTE_PORT for remote server.

Result description
~~~~~~~~~~~~~~~~~~
       The socket select example thread will be started automatically when booting.
       A local TCP server will be started to wait for connection. Can use a TCP client connecting to this server to send data.
       If CONNECT_REMOTE is enabed in example. A remote TCP server is required and can send data to the created remote connection.

Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported IC :
                Ameba-pro, Ameba-z2
		