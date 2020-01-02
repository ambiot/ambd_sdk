##################################################################################
#                                                                                #
#                             Example_coap                                       #
#                                                                                #
##################################################################################

Date: 2018-06-01

Table of Contents
~~~~~~~~~~~~~~~~~
 - Description
 - Setup Guide
 - Result description
 - Parameter Setting and Configuration
 - Other Reference
 - Supported List

 
Description
~~~~~~~~~~~
        This example demonstrates how to use mbed-CoAP C library to build and parse a CoAP message.
	
Setup Guide
~~~~~~~~~~~
        1) Add CoAP library and example to SDK : 
      
        /component/common/network/coap
        .
        |-- include
        | |-- ns_list.h
        | |-- ns_types.h
        | |-- sn_coap_ameba_port.h
        | |-- sn_coap_header.h
        | |-- sn_coap_header_internal.h
        | |-- sn_coap_protocol.h
        | |-- sn_coap_protocol_internal.h
        | `-- sn_config.h
        |-- sn_coap_ameba_port.c
        |-- sn_coap_builder.c
        |-- sn_coap_header_check.c
        |-- sn_coap_parser.c
        `-- sn_coap_protocol.c

        /component/common/example/coap
        .
        |-- example_coap.c
        |-- example_coap.h
        `-- readme.txt
        
        2) Add/Enable CONFIG_EXAMPLE_COAP in platform_opts.h
	/* for CoAP example*/
        #define CONFIG_EXAMPLE_COAP 1

        3) Add example_coap() to example_entry.c
        #if CONFIG_EXAMPLE_COAP
            #include <coap/example_coap.h>
        #endif
        void example_entry(void)
        {
        #if CONFIG_EXAMPLE_COAP
            example_coap();
        #endif
        }
        4) Add CoAP related files to IAR project
        5) Add include directories to project
        $PROJ_DIR$\..\..\..\component\common\network\coap\include

Result description
~~~~~~~~~~~~~~~~~~
	In the example, a confirmable GET request is send to test server "coap.me" to retrieve the resource under path "/hello". The expected return is an ACK message with payload "world".

        Note: Company Firewall may block CoAP message. You can use copper (https://addons.mozilla.org/en-US/firefox/addon/copper-270430/) to test the server's reachability.

Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Make sure SERVER_PORT has been set.
	

Other Reference
~~~~~~~~~~~~~~~
        For more details, please refer to UM0150 Realtek Ameba CoAP User Guide.pdf


Supported List
~~~~~~~~~~~~~~
[Supported List]
	Supported IC :
		Ameba-1, 
		Ameba-pro, 
		Ameba-z2
	Not Supported IC: 
		Ameba-z
  

	 