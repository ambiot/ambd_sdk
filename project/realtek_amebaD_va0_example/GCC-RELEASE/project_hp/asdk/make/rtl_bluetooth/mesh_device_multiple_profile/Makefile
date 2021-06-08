include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

include ../amebad_bsp/Makefile

SDK_DIR = $(BASEDIR)/component/common/bluetooth/realtek/sdk
MESH_DIR = $(SDK_DIR)/example/bt_mesh
MESH_MULTIPLE_PROFILE_DIR = $(SDK_DIR)/example/bt_mesh_multiple_profile
MESH_USER_API_DIR = $(MESH_DIR)/api
MESH_TEST_DIR = $(SDK_DIR)/example/bt_mesh_test
MESH_DEV_RTK_DEMO_DIR = $(SDK_DIR)/example/bt_mesh_device_rtk_demo
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
   -I$(MESH_MULTIPLE_PROFILE_DIR)/device_multiple_profile \
   -I$(SDK_DIR)/board/amebad/src/vendor_cmd \
   -I$(MESH_USER_API_DIR)/provisioner \
   -I$(MESH_USER_API_DIR)/device \
   -I$(MESH_USER_API_DIR)\
   -I$(MESH_DEV_RTK_DEMO_DIR) \
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
    $(MESH_DIR)/lib/profile/datatrans_server.c \
    $(MESH_DIR)/lib/profile/datatrans_service.c \
    $(MESH_DIR)/lib/model/generic_on_off_server.c \
    $(MESH_DIR)/lib/model/delay_execution.c \
	$(MESH_DIR)/lib/model/delay_msg_rsp.c \
    $(MESH_DIR)/lib/model/generic_transition_time.c \
    $(MESH_DIR)/lib/model/realtek/datatrans_model.c \
    $(MESH_DIR)/lib/model/realtek/ping_control.c \
    $(MESH_DIR)/lib/model/realtek/tp_control.c \
    $(MESH_DIR)/lib/model/health_server.c \
    $(MESH_DIR)/lib/model/light_lightness_setup_server.c \
    $(MESH_DIR)/lib/model/light_lightness_server.c \
    $(MESH_DIR)/lib/model/light_xyl_setup_server.c \
    $(MESH_DIR)/lib/model/light_xyl_server.c \
    $(MESH_DIR)/lib/model/light_ctl_server.c \
    $(MESH_DIR)/lib/model/light_ctl_setup_server.c \
    $(MESH_DIR)/lib/model/light_ctl_temperature_server.c \
    $(MESH_DIR)/lib/model/light_ctl_temperature_server.c \
    $(MESH_DIR)/lib/model/light_hsl_hue_server.c \
    $(MESH_DIR)/lib/model/light_hsl_saturation_server.c \
    $(MESH_DIR)/lib/model/light_hsl_server.c \
    $(MESH_DIR)/lib/model/light_hsl_setup_server.c \
    $(MESH_DIR)/lib/model/time_server.c \
    $(MESH_DIR)/lib/model/time_setup_server.c \
    $(MESH_DIR)/lib/model/scene_server.c \
    $(MESH_DIR)/lib/model/scene_setup_server.c \
    $(MESH_DIR)/lib/model/scheduler_server.c \
    $(MESH_DIR)/lib/model/scheduler_setup_server.c \
    $(MESH_MULTIPLE_PROFILE_DIR)/device_multiple_profile/bt_mesh_device_multiple_profile_app_task.c \
    $(MESH_MULTIPLE_PROFILE_DIR)/device_multiple_profile/device_multiple_profile_app.c \
    $(MESH_DIR)/lib/common/ping_app.c \
    $(MESH_DIR)/lib/common/datatrans_app.c \
	$(MESH_DIR)/lib/common/customer_dfu_service.c \
	$(MESH_DIR)/lib/common/dfudep_service.c \
	$(MESH_DIR)/lib/common/dfu_updater_app.c \
    $(MESH_DIR)/lib/common/scene_server_app.c \
    $(MESH_DIR)/lib/common/scheduler_server_app.c \
    $(MESH_DIR)/lib/common/time_server_app.c \
    $(MESH_DIR)/lib/common/light_server_app.c \
    $(MESH_DIR)/lib/cmd/mesh_cmd.c \
    $(MESH_DIR)/lib/cmd/test_cmd.c \
    $(MESH_MULTIPLE_PROFILE_DIR)/device_multiple_profile/device_multiple_profile_cmd.c \
    $(MESH_MULTIPLE_PROFILE_DIR)/device_multiple_profile/bt_mesh_device_multiple_profile_app_main.c \
    $(SDK_DIR)/board/amebad/src/vendor_cmd/vendor_cmd.c \
    $(MESH_USER_API_DIR)/device/bt_mesh_device_api.c \
	$(MESH_USER_API_DIR)/device/device_idle_check.c \
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
#LINK_APP_LIB += $(MESH_DIR)/lib/lib/btmesh_dev.a

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
