##################################################################################
#                                                                                #
#                      OTA OVER SD CARD UPDATING EXAMPLE                         #
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
    This example shows how to download ota.bin from SD card if target file presented.
    To perform this example, please make sure the target OTA file is within SD card file system.
    Also, we recommend to rename the OTA file as some vendor specified name, e.g. ota_is_realtek.bin.


Setup Guide
~~~~~~~~~~~
        1. Add ota_sdcard example to SDK
        
        /component/common/example/ota_sdcard
        .
        |-- example_ota_sdcard.c
        |-- example_ota_sdcard.h
        `-- readme.txt
        
        2. Enable CONFIG_EXAMPLE_OTA_SDCARD and FATFS_DISK_SD in [platform_opts.h]
        /* For sd card ota update example */
        #define CONFIG_EXAMPLE_OTA_SDCARD    1
        #define FATFS_DISK_SD   1

        3. Enable SDCARD_OTA_UPDATE 
        [rtl8721d_ota.h]/[ota_8195b.h]
            #define SDCARD_OTA_UPDATE
        

Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Modify FILENAME as the target OTA file in SD card.
        eg: #define FILENAME    "ota_is_realtek.bin"

Result description
~~~~~~~~~~~~~~~~~~
    A OTA over SD card example thread will be started automatically when booting.


Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported :
            Ameba-pro, AmebaD, 
        Source code not in project:
            Ameba-1, Ameba-z



