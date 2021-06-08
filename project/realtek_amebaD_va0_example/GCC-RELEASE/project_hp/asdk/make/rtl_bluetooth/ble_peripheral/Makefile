
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

include ../amebad_bsp/Makefile

# board-specific
MODULE_IFLAGS += \
   -I$(DIR)/sdk/example/ble_peripheral

CSRC += \
    $(DIR)/sdk/src/ble/profile/server/simple_ble_service.c \
    $(DIR)/sdk/src/ble/profile/server/bas.c \
    $(DIR)/sdk/example/ble_peripheral/app_task.c \
    $(DIR)/sdk/example/ble_peripheral/ble_app_main.c \
    $(DIR)/sdk/example/ble_peripheral/peripheral_app.c \
    $(DIR)/sdk/example/ble_peripheral/ble_peripheral_at_cmd.c

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
