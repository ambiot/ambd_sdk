include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all:
ifeq ($(CONFIG_BT_EN),y)
	@make -C rtl_bluetooth all
endif
ifeq ($(CONFIG_WIFI_EN),y)
	@make -C network all
	@make -C api all
	@make -C wlan all
endif
	@make -C utilities all
	@make -C test all
	@make -C os all

ifeq ($(CONFIG_MBED_TLS_ENABLED),y)
	@make -C mbedtls all
endif

ifeq ($(CONFIG_GUI_EN),y)
	@make -C ui all
endif

ifeq ($(CONFIG_LINKKIT_AWSS),y)
#	@make -C linkkit all
	@make -C linkkit all
endif
	#@make -C bootloader all
	@make -C app all
	@make -C target all
	@make -C drivers all
	@make -C cmsis all
	@make -C mbed all
	#@make -C audio all
#	@make -C graphic all
	#@make -C media all
	@make -C utilities_example all
	@make -C file_system all
	@make -C project all
	@make -C application all
	#@make -C cmsis-dsp all
#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean:
	@make -C application clean
	@make -C wlan clean
	@make -C wps clean
	@make -C network clean
	@make -C api clean
	@make -C utilities clean
	@make -C test clean
	@make -C os clean
	@make -C ssl clean
	@make -C mbedtls clean
	@make -C mbed clean
	@make -C app clean
	@make -C bootloader clean
	@make -C drivers clean
	@make -C target clean
	@make -C rtl_bluetooth clean
	@make -C cmsis clean
	@make -C cmsis-dsp clean
	@make -C mbed clean
	@make -C audio clean
	@make -C graphic clean
	@make -C utilities_example clean
	@make -C file_system clean	
	@make -C project clean
	@make -C ui clean
	@make -C media clean
	@make -C video clean
-include $(DEPS)
