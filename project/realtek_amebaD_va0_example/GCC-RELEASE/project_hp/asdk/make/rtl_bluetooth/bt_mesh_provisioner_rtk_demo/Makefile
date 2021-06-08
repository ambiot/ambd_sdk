include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

include ../amebad_bsp/Makefile

SDK_DIR = $(BASEDIR)/component/common/bluetooth/realtek/sdk
MESH_DIR = $(SDK_DIR)/example/bt_mesh
MESH_PROV_RTK_DEMO_DIR = $(SDK_DIR)/example/bt_mesh_provisioner_rtk_demo
MESH_USER_API_DIR = $(MESH_DIR)/api

#*****************************************************************************#
#                        INCLUDE FILES                                        #
#*****************************************************************************#
MODULE_IFLAGS += \
   -I$(MESH_DIR)/lib/cmd \
   -I$(MESH_DIR)/lib/platform \
   -I$(MESH_DIR)/lib/inc/amebad \
   -I$(MESH_DIR)/lib/inc \
   -I$(MESH_DIR)/lib/model \
   -I$(MESH_DIR)/lib/gap \
   -I$(MESH_DIR)/provisioner \
   -I$(MESH_DIR)/device \
   -I$(MESH_USER_API_DIR)/provisioner \
   -I$(MESH_USER_API_DIR)/device \
   -I$(MESH_USER_API_DIR) \
   -I$(SDK_DIR)/board/amebad/src/vendor_cmd \
   -I$(MESH_PROV_RTK_DEMO_DIR) \
   -I$(MESH_PROV_RTK_DEMO_DIR)/inc \

#*****************************************************************************#
#                        DEVICE APP FILES                                     #
#*****************************************************************************#
CSRC += \
	$(MESH_PROV_RTK_DEMO_DIR)/example_bt_mesh_provisioner_rtk_demo.c \
	$(MESH_PROV_RTK_DEMO_DIR)/src/bt_mesh_app_http_intf.c \
	$(MESH_PROV_RTK_DEMO_DIR)/src/bt_mesh_app_lib_intf.c \
	$(MESH_PROV_RTK_DEMO_DIR)/src/bt_mesh_app_list_intf.c \
	$(MESH_PROV_RTK_DEMO_DIR)/src/bt_mesh_broadcast_demo.c

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
