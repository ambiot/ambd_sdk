##################################################################################
#                                                                                #
#                                 RARP EXAMPLE                                   #
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
    In this example, it will send rarp request for 3 times. And the rarp reply callback 
        will print the received reply IP address.


Setup Guide
~~~~~~~~~~~
        1. Add rarp example to SDK
        
        /component/common/example/rarp
        .
        |-- example_rarp.c
        |-- example_rarp.h
        `-- readme.txt

        2. Enable CONFIG_EXAMPLE_RARP in [platform_opts.h]
        /* For rarp example */
        #define CONFIG_EXAMPLE_RARP     1


Result description
~~~~~~~~~~~~~~~~~~
    You need to connect to WiFi manually by AT command. 
    After connected the rarp request will be sent.

RARP server:
    For Ubuntu, you can try to setup the RARP server as doing this:
        apt-get install rarpd
        touch /etc/ethers
        Add Ameba's MAC address such as "00:e0:4c:87:00:09  client"     in /etc/ethers
        Add Ameba's IP  address such as "192.168.0.100  client"     in /etc/hosts


Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported :
            Ameba-1, Ameba-z, Ameba-pro, Ameba-z2, AmebaD, 