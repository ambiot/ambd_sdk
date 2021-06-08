
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

include ../amebad_bsp/Makefile

# board-specific
MODULE_IFLAGS += \
   -I$(DIR)/sdk/example/bt_breeze \
   -I$(DIR)/sdk/../../../application/breeze/api \
   -I$(DIR)/sdk/../../../application/breeze/include \
   -I$(DIR)/sdk/../../../application/breeze/core/include \
   -I$(DIR)/sdk/../../../application/breeze/ref-impl \
   -I$(DIR)/sdk/../../../network/ssl/mbedtls-2.4.0/include/mbedtls

CSRC += \
    $(DIR)/sdk/../../../application/breeze/api/breeze_awss_export.c \
    $(DIR)/sdk/../../../application/breeze/api/breeze_export.c \
    $(DIR)/sdk/../../../application/breeze/core/src/auth.c \
    $(DIR)/sdk/../../../application/breeze/core/src/ble_service.c \
    $(DIR)/sdk/../../../application/breeze/core/src/core.c \
    $(DIR)/sdk/../../../application/breeze/core/src/extcmd.c \
    $(DIR)/sdk/../../../application/breeze/core/src/transport.c \
    $(DIR)/sdk/../../../application/breeze/core/src/utils.c \
    $(DIR)/sdk/../../../application/breeze/ref-impl/aes.c \
    $(DIR)/sdk/../../../application/breeze/ref-impl/sha256.c \
    $(DIR)/sdk/example/bt_breeze/breeze.c \
    $(DIR)/sdk/example/bt_breeze/hal/breeze_hal_ble.c \
    $(DIR)/sdk/example/bt_breeze/hal/breeze_hal_sec.c \
    $(DIR)/sdk/example/bt_breeze/hal/breeze_hal_os.c \
    $(DIR)/sdk/example/bt_breeze/bt_breeze_app_main.c \
    $(DIR)/sdk/example/bt_breeze/bt_breeze_app_task.c \
    $(DIR)/sdk/example/bt_breeze/bt_breeze_peripheral_app.c

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
