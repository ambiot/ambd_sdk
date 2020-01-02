
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

include ../amebad_bsp/Makefile

# board-specific
MODULE_IFLAGS += \
   -I$(DIR)/sdk/src/app/ble_central_client \
   -I$(DIR)/sdk/board/amebad/src/data_uart \
   -I$(DIR)/sdk/src/mcu/module/data_uart_cmd 

MODULE_IFLAGS += -include app_flags.h


CSRC += \
    $(DIR)/sdk/src/ble/profile/client/gcs_client.c \
    $(DIR)/sdk/src/mcu/module/data_uart_cmd/user_cmd_parse.c \
    $(DIR)/sdk/board/amebad/src/data_uart/data_uart.c \
    $(DIR)/sdk/src/app/ble_central_client/ble_app_main.c \
    $(DIR)/sdk/src/app/ble_central_client/app_task.c \
    $(DIR)/sdk/src/app/ble_central_client/central_client_app.c \
    $(DIR)/sdk/src/app/ble_central_client/link_mgr.c \
    $(DIR)/sdk/src/app/ble_central_client/user_cmd.c 

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
