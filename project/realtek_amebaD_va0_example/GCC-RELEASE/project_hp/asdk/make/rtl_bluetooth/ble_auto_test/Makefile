
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

include ../amebad_bsp/Makefile

# board-specific
MODULE_IFLAGS += \
   -I$(DIR)/sdk/src/app/ble_auto_test \
   -I$(DIR)/sdk/src/app/ble_auto_test/cmd \
   -I$(DIR)/sdk/board/amebad/src/data_uart \
   -I$(DIR)/sdk/src/mcu/module/data_uart_cmd 

MODULE_IFLAGS += -include app_flags.h

CSRC += \
    $(DIR)/sdk/src/ble/profile/client/gaps_client.c \
    $(DIR)/sdk/src/ble/profile/server/hids_kb.c \
    $(DIR)/sdk/src/mcu/module/data_uart_cmd/user_cmd_parse.c \
    $(DIR)/sdk/board/amebad/src/data_uart/data_uart.c \
    $(DIR)/sdk/src/app/ble_auto_test/vendor_tp_service.c \
    $(DIR)/sdk/src/app/ble_auto_test/vendor_pxpext_client.c \
    $(DIR)/sdk/src/app/ble_auto_test/vendor_tp_client.c \
    $(DIR)/sdk/src/app/ble_auto_test/vendor_pxpext_service.c \
    $(DIR)/sdk/src/app/ble_auto_test/ble_app_main.c \
    $(DIR)/sdk/src/app/ble_auto_test/ble_auto_test_application.c \
    $(DIR)/sdk/src/app/ble_auto_test/ble_auto_test_case.c \
    $(DIR)/sdk/src/app/ble_auto_test/cmd/user_cmd.c \
    $(DIR)/sdk/src/app/ble_auto_test/app_task.c \
    $(DIR)/sdk/src/app/ble_auto_test/link_mgr.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_0001.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_100.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_200.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_300.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_400.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_500.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_600.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_700.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_800.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_900.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_1000.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_310.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_1100.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_1200.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_common.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_600_sut.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_300_sut.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_500_sut.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_200_sut.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_400_sut.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_800_sut.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_310_sut.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_1100_sut.c \
    $(DIR)/sdk/src/app/ble_auto_test/tc_1200_sut.c 

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
