##################################################################################
#                                                                                #
#                           example_get_beacon_frame                             #
#                                                                                #
##################################################################################

Date: 2018-06-11

Table of Contents
~~~~~~~~~~~~~~~~~
 - Description
 - Setup Guide
 - Result description
 - Supported List

 
Description
~~~~~~~~~~~
        This example shows how to get beacon frame information in station mode.


Setup Guide
~~~~~~~~~~~
        1) Add get_beacon frame example to SDK :
        
        /component/common/example/get_beacon_frame
        .
        |-- example_get_beacon_frame.c
        |-- example_get_beacon_frame.h
        `-- readme.txt
        
        2) Enable CONFIG_EXAMPLE_GET_BEACON_FRAME in [platform_opts.h]
        /* For WIFI GET BEACON FRAME example */
        #define CONFIG_EXAMPLE_GET_BEACON_FRAME  1
        

Result description
~~~~~~~~~~~~~~~~~~
        Call example_get_beacon_frame() to create get beacon frame thread.
        It will collect the beacon of AP in the air.


Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported IC :
                Ameba-pr, Ameba-z2, AmebaD