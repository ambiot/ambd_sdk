LWIP PPPOE EXAMPLE

Description:
Example for lwip pppoe connection.

Configuration:
[lwipopts.h]
For LwIP 1.4.1
    #define PPP_SUPPORT                     1
    #define PPPOE_SUPPORT                   1
    #define PPPOS_SUPPORT                   0
    #define PAP_SUPPORT                     1
    #define CHAP_SUPPORT                    1
    #define MD5_SUPPORT                     1
For LwIP 2.0.2 (since SDK v4.1)
    #define PPP_SUPPORT                     1
    #define PPPOE_SUPPORT                   1
    #define PAP_SUPPORT                     1
    #define CHAP_SUPPORT                    1
    #define EAP_SUPPORT                     1
[platform_opts.h]
    #define CONFIG_EXAMPLE_PPPOE            1

Execution:
Can make automatical Wi-Fi connection when booting by using wlan fast connect example.
A PPPOE example thread will be started automatically when booting.

Setup PPPOE_USER and PPPOE_PASSWD in example_pppoe.c for authentication. PPP addresses will be shown after PPP is connected

[Supported List]
	Supported :
	    Ameba-1, Ameba-pro
	Source code not in project:
	    Ameba-z