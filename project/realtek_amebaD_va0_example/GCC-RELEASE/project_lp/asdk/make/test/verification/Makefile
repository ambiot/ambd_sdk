
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/verification
MODULE_IFLAGS = -I$(DIR)./

vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
ifeq ($(CONFIG_ADC_VERIFY),y)
CSRC = $(DIR)/adc/rtl8195a_adc_test.c
endif

ifeq ($(CONFIG_EFUSE_VERIFY),y)
CSRC += $(DIR)/efuse/rtl8195a_efuse_test.c
endif

ifeq ($(CONFIG_GDMA_VERIFY),y)
CSRC += $(DIR)/gdma/rtl8195a_gdma_test.c
CSRC += $(DIR)/gdma/rtl8195a_gdma_llp_test.c
endif

ifeq ($(CONFIG_GPIO_VERIFY),y)
CSRC += $(DIR)/gpio/rtl8195a_gpio_test.c
endif

ifeq ($(CONFIG_I2C_VERIFY),y)
CSRC += $(DIR)/i2c/rtl8195a_i2c_test_sal.c
CSRC += $(DIR)/i2c/hal_i2c_test.c
endif

ifeq ($(CONFIG_PMC_VERIFY),y)
CSRC += $(DIR)/pmc/pmc_test.c
endif

ifeq ($(CONFIG_SPI_COM_VERIFY),y)
CSRC += $(DIR)/spi_communication/rtl8721d_ssi_test.c
CSRC += $(DIR)/spi_communication/hal_ssi_test.c
endif

ifeq ($(CONFIG_SPIC_VERIFY),y)
CSRC += $(DIR)/spi_flash/rtl8721d_spi_flash_test.c
CSRC += $(DIR)/spi_flash/flash_runcode_test.c
CSRC += $(DIR)/spi_flash/rtl8721d_flash_N25Q00AA_patch.c
endif

ifeq ($(CONFIG_TIMER_VERIFY),y)
CSRC += $(DIR)/timer/rtl8195a_timer_test.c
CSRC += $(DIR)/timer/rtl8710b_rtc_test.c
CSRC += $(DIR)/timer/rtl8710b_pwm_test.c 
CSRC += $(DIR)/timer/rtl8710b_timer_capture_test.c
CSRC += $(DIR)/timer/rtl8710b_osc_test.c
endif

ifeq ($(CONFIG_UART_VERIFY),y)
CSRC += $(DIR)/uart/rtl8721d_uart_test.c
CSRC += $(DIR)/uart/hal_uart_test.c
CSRC += $(DIR)/uart/rtl8721d_uart_cyclic_dma_test.c
endif

ifeq ($(CONFIG_WDG_VERIFY),y)
CSRC += $(DIR)/wdg/rtl8195a_wdg_test.c
endif

ifeq ($(CONFIG_KEYSCAN_VERIFY),y)
CSRC += $(DIR)/keyscan/rtl8721d_keyscan_test.c
endif

ifeq ($(CONFIG_CAPTOUCH_VERIFY),y)
CSRC += $(DIR)/captouch/rtl8721d_captouch_test.c
endif

ifeq ($(CONFIG_SGPIO_VERIFY),y)
CSRC += $(DIR)/sgpio/rtl8721d_sgpio_test.c
endif

ifeq ($(CONFIG_QDEC_VERIFY),y)
CSRC += $(DIR)/qdecoder/rtl8721d_qdec_test.c
endif

ifeq ($(CONFIG_IPC_VERIFY),y)
CSRC += $(DIR)/ipc/ipc_test.c
endif

ifeq ($(CONFIG_MPU_VERIFY),y)
CSRC += $(DIR)/mpu/mpu_test.c
endif

ifeq ($(CONFIG_CACHE_VERIFY),y)
CSRC += $(DIR)/cache/rtl8721d_cache_test.c
endif

ifeq ($(CONFIG_RSIP_VERIFY),y)
CSRC += $(DIR)/rsip/rsip_test.c
endif

ifeq ($(CONFIG_DHRYSTONE_TEST),y)
CSRC += $(DIR)/dhrystone/dhrystone_test.c
endif

ifeq ($(CONFIG_SBOOT_VERIFY),y)
CSRC += $(DIR)/sboot/sboot_test.c
endif

ifeq ($(CONFIG_WFE_VERIFY),y)
CSRC += $(DIR)/wfe/wfe_test.c
endif

CSRC += $(DIR)/rtl_simulation/rtl_simulation.c
#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CLEAN_OBJS CORE_TARGETS COPY_RAM_OBJS

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
