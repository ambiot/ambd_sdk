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
	#@make -C azure_emb all
	#@make -C airkiss all
#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean:
	@make -C baidu clean
	@make -C mqtt clean
	#@make -C airkiss clean
	@make -C azure_emb clean
-include $(DEPS)
