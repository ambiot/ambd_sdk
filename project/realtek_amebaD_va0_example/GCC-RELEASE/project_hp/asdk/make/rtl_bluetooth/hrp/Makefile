
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

include ../amebad_bsp/Makefile

# board-specific
MODULE_IFLAGS += \
   -I$(DIR)/sdk/board/amebad/src/data_uart \
   -I$(DIR)/sdk/src/app/hrp/application \
   -I$(DIR)/sdk/src/app/hrp/btif \
   -I$(DIR)/sdk/src/app/hrp \
   -I$(DIR)/sdk/src/app/hrp/lps \
   -I$(DIR)/sdk/src/app/hrp/service \
   -I$(DIR)/sdk/src/app/hrp/uart \
   -I$(DIR)/sdk/src/app/hrp/gap \
   -I$(DIR)/sdk/src/app/hrp/gap_ble \
   -I$(DIR)/sdk/src/app/hrp/platform \
   -I$(DIR)/sdk/src/app/hrp/storage
   
MODULE_IFLAGS += -include hrp_app_flags.h


CSRC += \
    $(DIR)/sdk/src/app/hrp/service/gattsvc_bas.c \
    $(DIR)/sdk/src/app/hrp/service/gattsvc_cts.c \
    $(DIR)/sdk/src/app/hrp/service/gattsvc_dis.c \
    $(DIR)/sdk/src/app/hrp/service/gattsvc_gls.c \
    $(DIR)/sdk/src/app/hrp/service/gattsvc_ndcs.c \
    $(DIR)/sdk/src/app/hrp/service/gattsvc_rtus.c \
    $(DIR)/sdk/src/app/hrp/service/hrp_service.c \
	$(DIR)/sdk/src/ble/profile/client/gaps_client.c \
    $(DIR)/sdk/src/app/hrp/application/hrp_application.c \
    $(DIR)/sdk/src/app/hrp/application/hrp_utils.c \
    $(DIR)/sdk/src/app/hrp/application/ble_app_main.c \
    $(DIR)/sdk/src/app/hrp/btif/hrp_btif_common_api.c \
    $(DIR)/sdk/src/app/hrp/btif/hrp_btif_entry.c \
    $(DIR)/sdk/src/app/hrp/btif/hrp_btif_le_api.c \
    $(DIR)/sdk/src/app/hrp/btif/hrp_btif_system_api.c \
    $(DIR)/sdk/src/app/hrp/lps/hrp_dlps.c \
    $(DIR)/sdk/src/app/hrp/uart/btltp_uart_bb3.c \
    $(DIR)/sdk/src/app/hrp/gap_ble/hrp_gap_ble_api.c \
    $(DIR)/sdk/src/app/hrp/gap_ble/hrp_gap_ble_cmd_table.c \
    $(DIR)/sdk/src/app/hrp/gap_ble/hrp_gap_ble_msg.c \
    $(DIR)/sdk/src/app/hrp/gap_ble/hrp_gap_ble_utils.c \
    $(DIR)/sdk/src/app/hrp/gap/complete_ble_client.c \
    $(DIR)/sdk/src/app/hrp/gap/complete_ble_service.c \
	$(DIR)/sdk/src/app/hrp/gap/hrp_gap_le.c \
    $(DIR)/sdk/src/app/hrp/gap/hrp_profile_entry.c \
    $(DIR)/sdk/src/app/hrp/gap/hrp_profile_le_simple_ble.c \
    $(DIR)/sdk/src/app/hrp/gap/hrp_profile_system_api.c \
    $(DIR)/sdk/src/app/hrp/platform/wdt_reset.c 

OBJS = $(CSRC:.c=.o)
TOBJS = $(notdir $(OBJS))
LOBJS = $(addprefix objs/,$(TOBJS))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

LIBBLUETOOTH_OBJS_PATH = $(shell pwd)/objs
# Define the Rules to build the core targets
all: CLEAN_OBJS CORE_TARGETS COPY_RAM_OBJS
	mkdir -p $(LIBBLUETOOTH_OBJS_PATH)
	for i in $(OBJS); do \
		 $(COPY)  $$i $(LIBBLUETOOTH_OBJS_PATH) -f;\
		done
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

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
