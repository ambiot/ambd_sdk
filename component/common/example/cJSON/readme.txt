##################################################################################
#                                                                                #
#                               cJSON EXAMPLE                                    #
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
    This example shows how to use cJSON lib to generate JSON data and how to parse JSON data.


Setup Guide
~~~~~~~~~~~
        1. Add cJSON example to SDK
        
        /component/common/utilities
        .
        |-- cJSON.c
        |-- cJSON.h
        
        /component/common/example/cJSON
        .
        |-- example_cJSON.c
        |-- example_cJSON.h
        `-- readme.txt
        
        2. Enable CONFIG_EXAMPLE_CJSON in [platform_opts.h]
        /* For cJSON example */
        #define CONFIG_EXAMPLE_CJSON     1
        

Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Modify generate_json_data() to specific data structure and parse it in handle_json_data().

Result description
~~~~~~~~~~~~~~~~~~
    The data structure you defined display on the screen after booting.


Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported :
            Ameba-1, Ameba-pro, Ameba-z2, AmebaD, 
        Source code not in project:
            Ameba-z