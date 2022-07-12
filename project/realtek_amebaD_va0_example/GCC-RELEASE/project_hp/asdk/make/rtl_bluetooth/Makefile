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
ifeq ($(CONFIG_BT_MESH_PROVISIONER),y)
	make -C mesh_provisioner all
ifeq ($(CONFIG_BT_MESH_PROVISIONER_RTK_DEMO),y)
	make -C bt_mesh_provisioner_rtk_demo all
endif
else ifeq ($(CONFIG_BT_MESH_DEVICE),y)
	make -C mesh_device all
ifeq ($(CONFIG_BT_MESH_DEVICE_RTK_DEMO),y)
	make -C bt_mesh_device_rtk_demo all
endif
else ifeq ($(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE),y)
	make -C mesh_provisioner_multiple_profile all
ifeq ($(CONFIG_BT_MESH_PROVISIONER_RTK_DEMO),y)
	make -C bt_mesh_provisioner_rtk_demo all
endif
else ifeq ($(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE),y)	
	make -C mesh_device_multiple_profile all
ifeq ($(CONFIG_BT_MESH_DEVICE_RTK_DEMO),y)
	make -C bt_mesh_device_rtk_demo all
endif
endif
#	make -C bt_beacon all
	make -C bt_config all
#	make -C bt_airsync_config all
#	make -C bt_breeze all
	make -C ble_peripheral all
	make -C ble_central all
	make -C ble_scatternet all
#	make -C bt_tag_scanner all
#	make -C bt_ancs all
#	make -C bt_distance_detector all
endif

#*****************************************************************************#
#              GENERATE OBJECT FILE
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean:
ifeq ($(CONFIG_BT_EN),y)
ifeq ($(CONFIG_BT_MESH_PROVISIONER),y)
	make -C mesh_provisioner clean
ifeq ($(CONFIG_BT_MESH_PROVISIONER_RTK_DEMO),y)
	make -C bt_mesh_provisioner_rtk_demo clean
endif
else ifeq ($(CONFIG_BT_MESH_DEVICE),y)
	make -C mesh_device clean
ifeq ($(CONFIG_BT_MESH_DEVICE_RTK_DEMO),y)
	make -C bt_mesh_device_rtk_demo clean
endif
else ifeq ($(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE),y)
	make -C mesh_provisioner_multiple_profile clean
ifeq ($(CONFIG_BT_MESH_PROVISIONER_RTK_DEMO),y)
	make -C bt_mesh_provisioner_rtk_demo clean
endif
else ifeq ($(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE),y)	
	make -C mesh_device_multiple_profile clean
ifeq ($(CONFIG_BT_MESH_DEVICE_RTK_DEMO),y)
	make -C bt_mesh_device_rtk_demo clean
endif
endif
#	make -C bt_beacon clean
	make -C bt_config clean
#	make -C bt_airsync_config clean
#	make -C bt_breeze clean
	make -C ble_peripheral clean
	make -C ble_central clean
	make -C ble_scatternet clean
#	make -C bt_tag_scanner clean
#	make -C bt_ancs clean
#	make -C bt_distance_detector clean
endif

-include $(DEPS)
