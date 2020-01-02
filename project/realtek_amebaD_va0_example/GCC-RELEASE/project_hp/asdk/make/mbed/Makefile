
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/mbed/targets/hal/rtl8721d

vpath %.c $(DIR)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC += $(DIR)/flash_api.c

ifeq ($(CONFIG_MBED_API_EN),y)
CSRC += $(DIR)/pinmap_common.c
CSRC += $(DIR)/sys_api.c 
CSRC += $(DIR)/us_ticker.c
CSRC += $(DIR)/timer_api.c
CSRC += $(DIR)/dma_api.c
CSRC += $(DIR)/gpio_api.c
CSRC += $(DIR)/gpio_irq_api.c
CSRC += $(DIR)/pinmap.c
CSRC += $(DIR)/port_api.c
CSRC += $(DIR)/spi_api.c
CSRC += $(DIR)/serial_api.c
CSRC += $(DIR)/i2c_api.c
CSRC += $(DIR)/i2s_api.c
CSRC += $(DIR)/pwmout_api.c
CSRC += $(DIR)/analogin_api.c
CSRC += $(DIR)/efuse_api.c
CSRC += $(DIR)/sleep.c
CSRC += $(DIR)/wdt_api.c
CSRC += $(DIR)/spdio_api.c
CSRC += $(DIR)/us_ticker_api.c
CSRC += $(DIR)/wait_api.c
CSRC += $(DIR)/rtc_api.c
CSRC += $(DIR)/captouch_api.c
CSRC += $(DIR)/keyscan_api.c
CSRC += $(DIR)/lcdc_api.c
endif

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS COPY_RAM_OBJS
	
#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS:	$(OBJS)


#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)
