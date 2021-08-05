include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all:
ifeq ($(CONFIG_BAIDU_DUER),y)
	@make -C baidu all
endif
ifeq ($(CONFIG_MQTT_EN),y)
	@make -C mqtt all
endif
ifeq ($(CONFIG_LINKKIT_AWSS),y)
	@make -C linkkit all
endif
	@make -C xmodem all
	#@make -C azure_emb all
	#@make -C airkiss all
#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean:
	@make -C baidu clean
	@make -C mqtt clean
	@make -C xmodem clean
	#@make -C airkiss clean
	#@make -C linkkit clean
	@make -C dpp clean
	@make -C azure_emb clean
-include $(DEPS)
