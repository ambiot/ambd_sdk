include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all:
	@make -C test all
	@make -C os all
	@make -C monitor all
	@make -C target all
	@make -C cmsis all
	@make -C project all
ifeq ($(CONFIG_APP_DEMO),y)
	#@make -C example all
endif

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean:
	@make -C test clean
	@make -C os clean
	@make -C monitor clean
	@make -C bootloader clean
	@make -C target clean
	@make -C cmsis clean
	@make -C RT_xmodem clean
	#@make -C example clean
	@make -C project clean

-include $(DEPS)
