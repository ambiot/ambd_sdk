
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

include ../amebad_bsp/Makefile

# board-specific
MODULE_IFLAGS += \
   -I$(DIR)/sdk/example/ble_central \
   -I$(DIR)/sdk/example/ble_scatternet \
   -I$(DIR)/sdk/board/amebad/src/data_uart \
   -I$(DIR)/sdk/src/mcu/module/data_uart_cmd

CSRC += \
    $(DIR)/sdk/src/ble/profile/client/gcs_client.c \
    $(DIR)/sdk/src/mcu/module/data_uart_cmd/user_cmd_parse.c \
    $(DIR)/sdk/board/amebad/src/data_uart/data_uart.c \
    $(DIR)/sdk/example/ble_central/ble_central_app_main.c \
    $(DIR)/sdk/example/ble_central/ble_central_app_task.c \
    $(DIR)/sdk/example/ble_central/ble_central_client_app.c \
    $(DIR)/sdk/example/ble_central/ble_central_link_mgr.c \
    $(DIR)/sdk/example/ble_central/user_cmd.c \
    $(DIR)/sdk/example/ble_central/ble_central_at_cmd.c

OBJS = $(CSRC:.c=.o)
TOBJS = $(notdir $(OBJS))
LOBJS = $(addprefix objs/,$(TOBJS))

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
