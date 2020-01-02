##################################################################################
#                                                                                #
#                             example_httpc                                      #
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
        Based on HTTPC API, an HTTP/HTTPS client example to access httpbin.org for test are provided
	
Setup Guide
~~~~~~~~~~~
        In platform_opts.h, please set #define CONFIG_EXAMPLE_HTTPC 1

Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Can make automatical Wi-Fi connection when booting by using wlan fast connect example.
	
Result description
~~~~~~~~~~~~~~~~~~
        A httpc example thread is started automatically when booting.
        GET to http://httpbin.org/get and POST to http://httpbin.org/post will be verified.
        Both HTTP and HTTPS are supported by this exmaple, and can be changed by modifying USE_HTTPS.
        Should link PolarSSL bignum.c to SRAM to speed up SSL handshake for HTTPS client.
	
Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported IC :
                Ameba-pro, Ameba-z2
 
Trouble Shooting
~~~~~~~~~~~~~~
         ERROR: ssl_handshake return -0x7200
         Solution: In config_rsa.h or config_all.h, increase the value of MBEDTLS_SSL_MAX_CONTENT_LEN, the maximum value is 16384.