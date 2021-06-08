##################################################################################
#                                                                                #
#                             example_httpd                                      #
#                                                                                #
##################################################################################

Date: 2018-09-10

Table of Contents
~~~~~~~~~~~~~~~~~
 - Description
 - Setup Guide
 - Parameter Setting and Configuration
 - Result description
 - Supported List

 
Description
~~~~~~~~~~~
        This example is based on HTTPD API, an HTTP/HTTPS server example with a simple homepage and GET/POST method test pages are provided.
	
Setup Guide
~~~~~~~~~~~
        In platform_opts.h, please set #define CONFIG_EXAMPLE_HTTPD  1
        In lwipopts.h, please set #define SO_REUSE  1
		For HTTPS, please set #define USE_HTTPS    1 in example_httpd.c
		For HTTPS, MBEDTLS_SSL_MAX_CONTENT_LEN in config_rsa.h may need to be increased.

Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
About SSL configuration:
Ameba-1 and Ameba-Z support both POLARSSL and MBEDTLS library.
AmebaPro and AmebaZ2 only support MBEDTLS.

[platform_opts.h]:
	#define CONFIG_USE_POLARSSL 0 	
	#define CONFIG_USE_MBEDTLS 1	
[config_rsa.h]:
        SSL Configuration for HTTPS:
			For Ameba-1,and Ameba-Z:
                        	#define POLARSSL_CERTS_C  		#define MBEDTLS_CERTS_C
								or
                        	#define POLARSSL_SSL_SRV_C		#define MBEDTLS_SSL_SRV_C
			For AmebaPro, Ameba-Z2 and AmebaD:
				#define MBEDTLS_CERTS_C
				#define MBEDTLS_SSL_SRV_C

        Can make automatical Wi-Fi connection when booting by using wlan fast connect example.
		
Result description
~~~~~~~~~~~~~~~~~~
        This example is a httpd example thread is started automatically when booting.
        Both HTTP and HTTPS are supported by this exmaple, and can be changed by modifying USE_HTTPS.
        Can test with a Web browser connecting to the homepage of httpd server.
        Should link PolarSSL bignum.c to SRAM to speed up SSL handshake if starting HTTPS server.

Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported IC :
                Ameba-pro, Ameba-Z, Ameba-1, Ameba-Z2, AmebaD
Trouble Shooting
~~~~~~~~~~~~~~
         'ERROR: mbedtls_ssl_handshake -29312' & 'ERROR: httpd_tls_new_handshake'
         Solution: In config_rsa.h or config_all.h, increase the value of MBEDTLS_SSL_MAX_CONTENT_LEN, the maximum value is 16384.
