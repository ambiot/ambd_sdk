include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
GLOBAL_CFLAGS += -DCONFIG_BUILD_ROM

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all:
	make -C vector all
	make -C fwlib all
	make -C monitor all
	make -C xmodem all
	make -C string all
	make -C wifi_fw all

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean:
	make -C vector clean
	make -C fwlib clean
	make -C monitor clean
	make -C xmodem clean
	make -C string clean
	make -C wifi_fw clean

-include $(DEPS)
