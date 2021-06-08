##################################################################################
#                                                                                #
#                             example_cm_backtrace                               #
#                                                                                #
##################################################################################

Date: 2018-06-01

Table of Contents
~~~~~~~~~~~~~~~~~
 - Description
 - Setup Guide
 - Result description
 - Other Reference
 - Supported List

 
Description
~~~~~~~~~~~
        Cm_Backtrace(Cortex Microcontroller Backtrace) is an open source library for ARM Cortex-M MCUs to trace and locate the error codes, 
        it can also analyze the cause of errors automatically.

        The main features are as follows:
        1. The support errors include: assert failure, hard fault, Memory Management Fault, Bus Fault, Usage Fault, Debug Fault and other failure.
        2. Locate the cause of failure when fault occurs automatically and trace the location of the fault code, don¡¦t need to analyze the complicated fault registers manually.
        3. Output the function call stack in the error field (using addr2line tools for precise location).
        4. Support RT-Thread, UCOS, FreeRTOS operating system.
        5. Support Cortex-M0/M3/M4/M7 MCUs.
        6. Support IAR, Keil, GCC compiler.
	
Setup Guide
~~~~~~~~~~~
		For Ameba1/AmebazZ:
        Step 1 : Open the AmebaZ or Ameba1 IAR project, add a new group called cm_backtrace.
        Step 2 : Add cm_backtrace.c into the new-added group, and the cm_backtrace.c file is located at sdk-ameba-v4.0a\sdk-ameba-v4.0a\component\common\application\cm_backtrace
        Step 3 : Replace the main.c file located under the folder of project\realtek_amebaZ_va0_example\src (or \project\realtek_ameba1_va0_example\src,if 
                 using Ameba1 project) using the main.c located at the folder of project\realtek_amebaZ_va0_example\example_sources\cm_backtrace\src(or 
                 project\realtek_ameba1_va0_example\example_sources\cm_backtrace\src).
        Step 4 : Finally the IAR project is configured completely. Then compile this project.
		
		For AmebaD, set CONFIG_EXAMPLE_CM_BACKTRACE to 1 in project\realtek_amebaD_va0_example\inc\inc_hp\platform_opts.h.
	

Result description
~~~~~~~~~~~~~~~~~~
	This example produce a loag shows the hard fault arises due to thread log_servi, the information about what causing this fault.	

Other Reference
~~~~~~~~~~~~~~~
        For more details, please refer to UM0163 Realtek Ameba Cm_Backtrace user guide.pdf

Supported List
~~~~~~~~~~~~~~
[Supported List]
	Supported :
	    Ameba-1, Ameba-z,Ameba-d.
	Source code not in project:
	    Ameba-pro