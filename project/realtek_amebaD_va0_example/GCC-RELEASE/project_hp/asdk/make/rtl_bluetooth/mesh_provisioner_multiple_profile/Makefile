include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

include ../amebad_bsp/Makefile

SDK_DIR = $(BASEDIR)/component/common/bluetooth/realtek/sdk
MESH_DIR = $(SDK_DIR)/example/bt_mesh
MESH_MULTIPLE_PROFILE_DIR = $(SDK_DIR)/example/bt_mesh_multiple_profile
MESH_USER_API_DIR = $(MESH_DIR)/api
MESH_TEST_DIR = $(SDK_DIR)/example/bt_mesh_test
MESH_PROV_RTK_DEMO_DIR = $(SDK_DIR)/example/bt_mesh_provisioner_rtk_demo
CENTRAL_DIR = $(SDK_DIR)/example/ble_central
PERIPHERAL_DIR = $(SDK_DIR)/example/ble_peripheral
SCATTERNET_DIR = $(SDK_DIR)/example/ble_scatternet

#*****************************************************************************#
#                        INCLUDE FILES                                        #
#*****************************************************************************#
MODULE_IFLAGS += \
   -I$(MESH_DIR)/lib/cmd \
   -I$(MESH_DIR)/lib/common \
   -I$(MESH_DIR)/lib/gap \
   -I$(MESH_DIR)/lib/inc \
   -I$(MESH_DIR)/lib/inc/amebad \
   -I$(MESH_DIR)/lib/model \
   -I$(MESH_DIR)/lib/model/realtek \
   -I$(MESH_DIR)/lib/platform \
   -I$(MESH_DIR)/lib/profile \
   -I$(MESH_DIR)/lib/utility \
   -I$(MESH_DIR)/provisioner \
   -I$(MESH_DIR)/device \
   -I$(MESH_MULTIPLE_PROFILE_DIR)/provisioner_multiple_profile \
   -I$(MESH_DIR)/api/provisioner \
   -I$(MESH_DIR)/api/common \
   -I$(SDK_DIR)/board/amebad/src/vendor_cmd \
   -I$(MESH_USER_API_DIR)/provisioner \
   -I$(MESH_USER_API_DIR)/device \
   -I$(MESH_USER_API_DIR) \
   -I$(MESH_PROV_RTK_DEMO_DIR)/inc \
   -I$(MESH_TEST_DIR) \

ifeq ($(CONFIG_BT_MESH_CENTRAL),y)
MODULE_IFLAGS += \
   -I$(CENTRAL_DIR)
else ifeq ($(CONFIG_BT_MESH_PERIPHERAL),y)
MODULE_IFLAGS += \
   -I$(PERIPHERAL_DIR)
else ifeq ($(CONFIG_BT_MESH_SCATTERNET),y)
MODULE_IFLAGS += \
   -I$(SCATTERNET_DIR)
endif

#*****************************************************************************#
#                        DEVICE APP FILES                                     #
#*****************************************************************************#
CSRC += \
    $(MESH_DIR)/lib/cmd/mesh_data_uart.c \
    $(MESH_DIR)/lib/cmd/mesh_user_cmd_parse.c \
    $(MESH_DIR)/lib/profile/datatrans_service.c \
    $(MESH_DIR)/lib/profile/datatrans_client.c \
    $(MESH_DIR)/lib/model/configuration_client.c \
	$(MESH_DIR)/lib/model/blob_transfer_client.c \
	$(MESH_DIR)/lib/model/firmware_distribution_client.c \
	$(MESH_DIR)/lib/model/firmware_update_client.c \
	$(MESH_DIR)/lib/model/private_beacon_client.c \
    $(MESH_DIR)/lib/model/health_client.c \
    $(MESH_DIR)/lib/model/realtek/ping_control.c \
    $(MESH_DIR)/lib/model/realtek/tp_control.c \
    $(MESH_DIR)/lib/model/realtek/light_cwrgb_client.c \
    $(MESH_DIR)/lib/model/realtek/datatrans_model.c \
    $(MESH_DIR)/lib/model/generic_on_off_client.c \
    $(MESH_DIR)/lib/model/generic_default_transition_time_client.c \
    $(MESH_DIR)/lib/model/generic_level_client.c \
    $(MESH_DIR)/lib/model/generic_location_client.c \
    $(MESH_DIR)/lib/model/generic_power_on_off_client.c \
    $(MESH_DIR)/lib/model/generic_property_client.c \
    $(MESH_DIR)/lib/model/light_lightness_client.c \
    $(MESH_DIR)/lib/model/light_xyl_client.c \
    $(MESH_DIR)/lib/model/light_hsl_client.c \
    $(MESH_DIR)/lib/model/generic_power_level_client.c \
    $(MESH_DIR)/lib/model/generic_battery_client.c \
    $(MESH_DIR)/lib/model/light_ctl_client.c \
	$(MESH_DIR)/lib/model/light_lc_client.c \
    $(MESH_DIR)/lib/model/time_client.c \
    $(MESH_DIR)/lib/model/scene_client.c \
    $(MESH_DIR)/lib/model/sensor_client.c \
    $(MESH_DIR)/lib/model/scheduler_client.c \
	$(MESH_DIR)/lib/model/delay_msg_rsp.c \
    $(MESH_MULTIPLE_PROFILE_DIR)/provisioner_multiple_profile/bt_mesh_provisioner_multiple_profile_app_task.c \
    $(MESH_MULTIPLE_PROFILE_DIR)/provisioner_multiple_profile/provisioner_multiple_profile_app.c \
    $(MESH_DIR)/lib/common/ping_app.c \
    $(MESH_DIR)/lib/common/generic_client_app.c \
    $(MESH_DIR)/lib/common/light_client_app.c \
	$(MESH_DIR)/lib/common/rmt_prov_client_app.c \
    $(MESH_DIR)/lib/common/datatrans_app.c \
	$(MESH_DIR)/lib/common/customer_dfu_service.c \
	$(MESH_DIR)/lib/common/dfudep_service.c \
	$(MESH_DIR)/lib/common/dfu_distributor_app.c \
    $(MESH_DIR)/lib/cmd/mesh_cmd.c \
    $(MESH_DIR)/lib/cmd/client_cmd.c \
    $(MESH_DIR)/lib/cmd/test_cmd.c \
    $(MESH_MULTIPLE_PROFILE_DIR)/provisioner_multiple_profile/provisioner_multiple_profile_cmd.c \
    $(MESH_MULTIPLE_PROFILE_DIR)/provisioner_multiple_profile/bt_mesh_provisioner_multiple_profile_app_main.c \
    $(SDK_DIR)/board/amebad/src/vendor_cmd/vendor_cmd.c \
    $(MESH_USER_API_DIR)/provisioner/bt_mesh_provisioner_api.c \
    $(MESH_USER_API_DIR)/bt_mesh_user_api.c 

ifeq ($(CONFIG_BT_MESH_CENTRAL),y)
CSRC += \
    $(CENTRAL_DIR)/ble_central_link_mgr.c \
    $(CENTRAL_DIR)/ble_central_at_cmd.c
else ifeq ($(CONFIG_BT_MESH_PERIPHERAL),y)
CSRC += \
    $(PERIPHERAL_DIR)/ble_peripheral_at_cmd.c
else ifeq ($(CONFIG_BT_MESH_SCATTERNET),y)
CSRC += \
    $(CENTRAL_DIR)/ble_central_at_cmd.c \
    $(PERIPHERAL_DIR)/ble_peripheral_at_cmd.c \
    $(SCATTERNET_DIR)/ble_scatternet_link_mgr.c
endif

OBJS = $(CSRC:.c=.o)
TOBJS = $(notdir $(OBJS))
LOBJS = $(addprefix objs/,$(TOBJS))

#*****************************************************************************#
#                            LINK LIBRARY                                     #
#*****************************************************************************#
#LINK_APP_LIB += $(MESH_DIR)/lib/lib/btmesh_prov.a

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
# LIBBLUETOOTH_OBJS_PATH = $(shell pwd)/objs
# Define the Rules to build the core targets
all: CORE_TARGETS COPY_RAM_OBJS
	# mkdir -p $(LIBBLUETOOTH_OBJS_PATH)
	# for i in $(OBJS); do \
	# 	 $(COPY)  $$i $(LIBBLUETOOTH_OBJS_PATH) -f;\
	# 	done
	# $(REMOVE) *.i
	# $(REMOVE) *.s
	# $(REMOVE) *.d

#*****************************************************************************#
#              GENERATE OBJECT FILE
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)
