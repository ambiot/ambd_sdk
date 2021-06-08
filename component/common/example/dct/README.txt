##################################################################################
#                                                                                #
#                              example_dct                                       #
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
        This example shows device configuration table API usage, and user can use DCT api to replace file system.
	
Setup Guide
~~~~~~~~~~~
	In platform_opts.h, please set #define CONFIG_EXAMPLE_DCT  1
	If using Ameba-pro:
		In example_dct.c, please set #define DCT_BEGIN_ADDR	0x200000
	If using Ameba-D:
		In example_dct.c, please set #define DCT_BEGIN_ADDR	0x100000
	
Result description
~~~~~~~~~~~~~~~~~~
        The result will show:
                variable0: value0
                variable1: value1
                Delete variable0 success.
                Remaining amount: 40 (for AmebaD)
	Remaining amount: 61 (for others)
        if DCT is correctly used.

Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported IC :
                Ameba-pro, Ameba-z2, Ameba-D