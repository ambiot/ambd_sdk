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
        In platform_opts.h, please set #define CONFIG_EXAMPLE_GET_BEACON_FRAME 1
	
Result description
~~~~~~~~~~~~~~~~~~
        Call example_get_beacon_frame() to create get beacon frame thread.
        It will collect the beacon of AP in the air.

Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported IC :
                Ameba-pr, Ameba-z2