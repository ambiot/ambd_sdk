DIR = $(BASEDIR)/component/common/bluetooth/realtek

# board-specific
MODULE_IFLAGS += \
   -I$(DIR)/sdk \
   -I$(DIR)/sdk/inc \
   -I$(DIR)/sdk/inc/app \
   -I$(DIR)/sdk/inc/bluetooth/gap \
   -I$(DIR)/sdk/inc/bluetooth/gap/gap_lib \
   -I$(DIR)/sdk/inc/os \
   -I$(DIR)/sdk/inc/platform \
   -I$(DIR)/sdk/inc/bluetooth/profile \
   -I$(DIR)/sdk/inc/bluetooth/profile/client \
   -I$(DIR)/sdk/inc/bluetooth/profile/server \
   -I$(DIR)/sdk/inc/stack \
   -I$(DIR)/sdk/board/amebad/src \
   -I$(DIR)/sdk/board/amebad/src/hci \
   -I$(DIR)/sdk/board/amebad/src/vendor_cmd \
   -I$(DIR)/sdk/board/amebad/lib \
   -I$(DIR)/sdk/board/common/inc 


MODULE_IFLAGS += -DUPPER_STACK_USE_NORMAL_HCI
MODULE_IFLAGS += -DAMEBAD_BOARD

MODULE_IFLAGS += -include bt_flags.h

CSRC += \
    $(DIR)/sdk/board/common/os/freertos/osif_freertos.c \
    $(DIR)/sdk/board/amebad/src/platform_utils.c \
    $(DIR)/sdk/board/common/src/cycle_queue.c \
    $(DIR)/sdk/board/common/src/trace_task.c \
    $(DIR)/sdk/board/common/src/hci_process.c \
    $(DIR)/sdk/board/common/src/hci_adapter.c \
    $(DIR)/sdk/board/common/src/bt_uart_bridge.c \
    $(DIR)/sdk/board/amebad/src/trace_uart.c \
	$(DIR)/sdk/board/amebad/src/rtk_coex.c \
	$(DIR)/sdk/board/amebad/src/vendor_cmd/vendor_cmd.c \
	$(DIR)/sdk/board/amebad/src/hci/hci_uart.c \
    $(DIR)/sdk/board/amebad/src/hci/hci_board.c \
    $(DIR)/sdk/board/amebad/src/hci/bt_fwconfig.c \
    $(DIR)/sdk/board/amebad/src/hci/bt_normal_patch.c \
	$(DIR)/sdk/board/amebad/src/hci/bt_mp_patch.c \
	$(DIR)/sdk/bt_example_entry.c
	
MODULE_IFLAGS += -include stdint.h
