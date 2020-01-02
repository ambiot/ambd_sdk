include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
OBJS =

#*****************************************************************************#
#                               Include Dependency                            #
#*****************************************************************************#
-include $(OBJS:.o=.d)


#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all: CORE_TARGETS
ifeq ($(CONFIG_BT_EN),y)
	make -C bt_beacon all
	make -C bt_config all
	make -C bt_airsync_config all
	make -C ble_peripheral all
	make -C ble_central all
	make -C ble_scatternet all
endif

#*****************************************************************************#
#              GENERATE OBJECT FILE
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean:
	make -C bt_beacon clean
	make -C bt_config clean
	make -C bt_airsync_config clean
	make -C ble_peripheral clean
	make -C ble_central clean
	make -C ble_scatternet clean

-include $(DEPS)
