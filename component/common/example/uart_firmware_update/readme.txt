##################################################################################
#                                                                                #
#                          Example uart_firmware_update                          #
#                                                                                #
##################################################################################

Date: 2018-05-29

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
        Here gives an example how to use UART update function in AMEBA-1( RTL8711AM/
        RTL8195AM / RTL8711AF) and AMEBA-Z( RTL8710B). The UART update helps to flash the OTA
        image onto the AMEBA board using the UART protocol. Once the OTA image is flashed onto the
        AMEBA board the AMEBA will boot from the new updated OTA image.

        For AMEBA-1, it is to be noted here that the original default image is not erased when the OTA
        image is being flashed.
        For AMEBA-Z, the example supports swap update between OTA1 and OTA2.
        

Setup Guide
~~~~~~~~~~~
        Configuration for baud rate:
            In file: component\common\example\uart_firmware_update\example_uart_update.c¡¨
            Chang the baud rate in Ameba SDK to 115200: #define XMODEM_UART_BAUDRATE 115200

            Note: If you are using Ameba EVB board, please set the baud rate not higher than
            115200. However, if your board supports a higher baud rate, you could set it to 1000000
            even 3000000 to get a higher transfer rate.

        Enable the UART firmware update feature:
	    #define CONFIG_UART_UPDATE 1
        Build the project after setting the above two parameters correctly and flash the AMEBA board.
	
Result description
~~~~~~~~~~~~~~~~~~
        After building the software and making the necessary hardware and pins setup 1.3, 
        we should now reboot the AMEBA board. Then you will see the xmodem uart update feature is enabled.

Parameter Setting and Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Configure the GPIO of Ameba board:

            Use PA_6 and PA_7 as UART TTL RX and TX pins in RTL8711AM/RTL8195AM. Use PC_0
            and PC_3 as UART RX and TX in RTL8711AF, and change default XMODEM_UART_MUX
            in example_uart_update.c from 2 to 0. Use PA_18 and PA_23 as UART RX and TX in
            RTL8710B.

            Pull low PC_2 (D11/MOSI/PWN2) by connecting it to one of the GND pins in
            RTL8711AM/RTL8195AM/RTL8711AF, refer to ¡§UM0048 Realtek Ameba1 DEV 1v0 User
            Manual_1v8_20160328¡¨ document for the AMEBA-1 pinout. Pull low PA_5 (PWN4) in
            RTL8710B; refer to ¡§UM0113 Realtek Ameba-Z DEV 1v0 User Manual¡¨ document for the
            AMEBA-Z pinout.

            For connecting the tx and rx pins to the PC we can use a UART TTL-USB adapter as
            shown below. The Vcc and GND pins can be powered using the AMEBA board¡¦s pinout
            or can also be powered separately. The setup with the UART TTL-USB adapter has not
            been shown here as an alternative test setup was used in the lab setup which is shown
            in the next point after this.
            An alternative to connect the UART to pc is to use a combination of a UART TTL-RS232
            Adapter and an RS323-USB serial adapter as shown below in the image.

Other Reference
~~~~~~~~~~~~~~~
        For more details, please refer to AN0096 Realtek Ameba-all Series xmodem UART Update firmware.pdf

Supported List
~~~~~~~~~~~~~~
[Supported List]
        Supported :
           Ameba-1, Ameba-z, Ameba-pro