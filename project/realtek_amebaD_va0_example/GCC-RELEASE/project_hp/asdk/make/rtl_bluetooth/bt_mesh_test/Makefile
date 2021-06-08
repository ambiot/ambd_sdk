include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

include ../amebad_bsp/Makefile

SDK_DIR = $(BASEDIR)/component/bluetooth
MESH_DIR = $(SDK_DIR)/example/bt_mesh
MESH_TEST_DIR = $(SDK_DIR)/example/bt_mesh_test
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
   -I$(MESH_DIR)/lib/model/realtek \
   -I$(MESH_DIR)/lib/gap \
   -I$(MESH_DIR)/lib/common \
   -I$(MESH_DIR)/provisioner \
   -I$(MESH_DIR)/device \
   -I$(MESH_USER_API_DIR)/provisioner \
   -I$(MESH_USER_API_DIR)/device \
   -I$(MESH_USER_API_DIR) \
   -I$(SDK_DIR)/board/amebad/src/vendor_cmd \
   -I$(MESH_TEST_DIR) \

#*****************************************************************************#
#                        DEVICE APP FILES                                     #
#*****************************************************************************#
CSRC += \
	$(MESH_TEST_DIR)/bt_mesh_app_user_cmd_parse.c \
	$(MESH_TEST_DIR)/bt_mesh_datatrans_write_api.c \
	$(MESH_TEST_DIR)/bt_mesh_device_test.c \
	$(MESH_TEST_DIR)/bt_mesh_malloc_free.c \
	$(MESH_TEST_DIR)/bt_mesh_receive_response.c \
	$(MESH_TEST_DIR)/bt_mesh_test_result.c \
	$(MESH_TEST_DIR)/bt_mesh_timer_handler.c \

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
