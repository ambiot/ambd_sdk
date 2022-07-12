802.1X EAP METHOD SUPPLICANT EXAMPLE

Description:
Use 802.1X EAP methods to connect to AP and authenticate with backend radius server.
Current supported methods are EAP-TLS, PEAPv0/EAP-MSCHAPv2, and EAP-TTLS/MSCHAPv2.

Configuration:
Modify the argument of example_eap() in example_entry.c to set which EAP methods you want to use.
[example_entry.c]
#if defined(CONFIG_EXAMPLE_EAP) && CONFIG_EXAMPLE_EAP
	example_eap("tls");
	//example_eap("peap");
	//example_eap("ttls");
	// example_eap("fast");
#endif

Modify the connection config (ssid, identity, password, cert) in example_eap_config() of example_eap.c based on your server's setting.
[FreeRTOSConfig.h]
	#define configTOTAL_HEAP_SIZE          ( ( size_t ) ( 70 * 1024 ) )
[platform_opts.h]
	# define CONFIG_EXAMPLE_EAP	1

	// Turn on/off the specified method
	# define CONFIG_ENABLE_PEAP	1
	# define CONFIG_ENABLE_TLS	1
	# define CONFIG_ENABLE_TTLS	1
	# define CONFIG_ENABLE_FAST	1

	// If you want to verify the certificate of radius server, turn this on
	# define ENABLE_EAP_SSL_VERIFY_SERVER	1

Add lib_eap.a to project and modify makefile/IAR project setting to link it
	(a) For IAR project
			lib_eap.a is located at component/soc/realtek/amebad/misc/bsp/lib/common/IAR, add it to group <lib> and rebuild the project
	(b) For GCC project
			For AmebaD, lib_eap.a is located at project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp/asdk/lib/application, modify makefile to link it, such as LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_eap.a

Execution:
An EAP connection thread will be started automatically when booting.

Note:
Please make sure the lib_wps, polarssl/mbedtls, ssl_ram_map are also builded.

Eap support DER format certificate as well.
User can set DER format certificate/private key/ca cert to eap_client_cert/eap_client_key/eap_ca_cert as below, and use sizeof() to get the length instead of strlen().
unsigned char ca_der_cert[] = {
    0x30,0x82,0x04,0xE4,0x30,0x82,0x03,0xCC,0xA0,0x03,0x02,0x01,0x02,0x02,0x09,0x00,
    0xD6,0xD2,0xF1,0x05,0x3E,0xF9,0xC8,0xC1,0x30,0x0D,0x06,0x09,0x2A,0x86,0x48,0x86,
 	...
    0x9D,0x9A,0x9C,0x44,0x38,0xF0,0x0B,0x07,0x68,0x48,0xCF,0x8C,0x25,0x8F,0x02,0x7D,
    0x87,0xC0,0xA3,0x55,0x16,0xFF,0x1A,0x3F,0xF1,0x01,0x3A,0x65,0x8E,0x96,0x74,0x1F,
    0xB4,0x44,0x64,0xF0,0x3F,0xA4,0xC6,0xF7
};
eap_ca_cert_len = sizeof(ca_der_cert);

If the connection failed, you can try the following directions to make it work:
1. Make sure the config_rsa.h of PolarSSL/MbedTLS include the SSL/TLS cipher suite supported by radius server.
2. Make sure the config_rsa.h of PolarSSL/MbedTLS include the certificate format which you use.
3. For EAP-TLS authentication, may need to enable POLARSSL_DES_C or MBEDTLS_DES_C in config_rsa.h to support for encrypted private key which you set in void example_eap_config(void).
4. Set a larger value to SSL_MAX_CONTENT_LEN in config_rsa.h
5. Increase the FreeRTOS heap in FreeRTOSConfig.h, for example you can increase the heap to 80kbytes:
	#define configTOTAL_HEAP_SIZE	( ( size_t ) ( 80 * 1024 ) )
6. Try to change using SW crypto instead of HW crypto.


[Supported List]
	Supported :
	    Ameba-1, Ameba-z, Ameba-pro, Ameba-D
