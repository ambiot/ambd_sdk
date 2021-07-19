
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/verification
MODULE_IFLAGS = -I$(DIR)./
MODULE_IFLAGS += -I$(BASEDIR)/component/common/drivers/ir/protocol
vpath %.c $(DIR) $(shell find $(DIR) -type d)

ifeq ($(findstring y, $(CONFIG_USBD_VERIFY) $(CONFIG_USBD_CLASS_VERIFY)), y)
IFLAGS += -I$(TARGETDIR)/fwlib/usb_otg/device/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/device/audio/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/device/cdc_acm/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/device/msc/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/device/vendor/inc
endif

ifeq ($(CONFIG_USB_DEVICE_NEW_EN),y)
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/common_new
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/device_new/cdc_acm
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/device_new/core
endif

ifeq ($(findstring y, $(CONFIG_USBH_VERIFY) $(CONFIG_USBH_CLASS_VERIFY)), y)
IFLAGS += -I$(TARGETDIR)/fwlib/usb_otg/host/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/host/msc/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/host/uvc/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/host/vendor/inc
IFLAGS += -I$(BASEDIR)/component/common/drivers/usb/host/cdc_acm/inc
ifeq ($(CONFIG_USBH_UVC),y)
IFLAGS += -I$(BASEDIR)/component/common/video/v4l2/inc
IFLAGS += -I$(BASEDIR)/component/common/media/rtp_codec
IFLAGS += -I$(BASEDIR)/component/common/media/mmfv2
endif
endif

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
ifeq ($(CONFIG_ADC_VERIFY),y)
CSRC = $(DIR)/adc/rtl8195a_adc_test.c
endif

ifeq ($(CONFIG_FT),y)
MODULE_IFLAGS += -I$(DIR)/ft_test/adc/
CSRC += $(DIR)/ft_test/adc/rtl8195a_ft_adc_dac.c
CSRC += $(DIR)/ft_test/adc/rtl8195a_dac_sin_23p84.c
CSRC += $(DIR)/ft_test/adc/rtl8195a_i2c_spi_dac.c
CSRC += $(DIR)/ft_test/adc/rtl8195a_spidac_sin_5p722k.c
CSRC += $(DIR)/ft_test/adc/rtl8710b_ft_test.c
endif

ifeq ($(CONFIG_EQC),y)
MODULE_IFLAGS += -I$(DIR)/eqc/
CSRC += $(DIR)/eqc/rtl8721d_eqc.c
endif

ifeq ($(CONFIG_CRYPTO_VERIFY),y)
CSRC += $(DIR)/crypto/rtl8721d_crypto_test.c
CSRC += $(DIR)/crypto/cryptoSim.c
CSRC += $(DIR)/crypto/rtl8721d_aes_ecb_test.c
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

ifeq ($(CONFIG_USI_I2C_VERIFY),y)
CSRC += $(DIR)/usi_i2c/rtl8721d_usi_i2c_test.c
CSRC += $(DIR)/usi_i2c/hal_usi_i2c_test.c
endif

ifeq ($(CONFIG_KEYSCAN_VERIFY),y)
CSRC += $(DIR)/keyscan/rtl8721d_keyscan_test.c
endif

ifeq ($(CONFIG_SGPIO_VERIFY),y)
CSRC += $(DIR)/sgpio/rtl8721d_sgpio_test.c
endif

ifeq ($(CONFIG_PSRAM_VERIFY),y)
CSRC += $(DIR)/psram/rtl8721d_psram_test.c
endif

ifeq ($(CONFIG_I2S_VERIFY),y)
CSRC += $(DIR)/i2s/rtl8195a_i2s_test.c
endif

ifeq ($(CONFIG_AUDIO_VERIFY),y)
CSRC += $(DIR)/audio/rtl8721d_audio_test.c
#CSRC += $(DIR)/audio/rtl8721d_audio_llp_test.c
CSRC += $(DIR)/audio/rtl8721d_audio_cyclic_dma_test.c
#CSRC += $(DIR)/audio/rtl8721d_audio_opus_test.c
endif

ifeq ($(CONFIG_SDIO_DEVICE_VERIFY),y)
CSRC += $(DIR)/sdio_device/rtl8195a_sdio_device_test.c
endif

ifeq ($(CONFIG_SPI_COM_VERIFY),y)
CSRC += $(DIR)/spi_communication/rtl8721d_ssi_test.c
CSRC += $(DIR)/spi_communication/hal_ssi_test.c
endif

ifeq ($(CONFIG_USI_SPI_VERIFY),y)
CSRC += $(DIR)/usi_ssi/rtl8721d_usi_ssi_test.c
CSRC += $(DIR)/usi_ssi/hal_usi_ssi_test.c
endif

ifeq ($(CONFIG_SPIC_VERIFY),y)
#CSRC += $(DIR)/spi_flash/rtl8721d_spi_flash_test.c
CSRC += $(DIR)/spi_flash/rtl8721d_spi_flash_qc_test.c  
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

ifeq ($(CONFIG_USI_UART_VERIFY),y)
CSRC += $(DIR)/usi_uart/rtl8721d_usi_uart_test.c
CSRC += $(DIR)/usi_uart/hal_usi_uart_test.c
endif

ifeq ($(CONFIG_LCDC_VERIFY),y)
MODULE_IFLAGS += -I$(DIR)/lcdc/
MODULE_IFLAGS += -I$(DIR)/lcdc/demo_code
MODULE_IFLAGS += -I$(BASEDIR)/component/common/ui/ucgui/Config/
MODULE_IFLAGS += -I$(BASEDIR)/component/common/ui/ucgui/GUI/Core/
MODULE_IFLAGS += -I$(BASEDIR)/component/common/ui/ucgui/GUI/JPEG/
MODULE_IFLAGS += -I$(BASEDIR)/component/common/ui/ucgui/GUI/MultiLayer/
MODULE_IFLAGS += -I$(BASEDIR)/component/common/ui/ucgui/GUI/Widget/
MODULE_IFLAGS += -I$(BASEDIR)/component/common/ui/ucgui/GUI/WM/
MODULE_IFLAGS += -I$(BASEDIR)/component/common/graphic/codec/jpeg
CSRC += $(DIR)/lcdc/rtl8721d_lcdc_test.c
CSRC += $(DIR)/lcdc/bsp_mcu_lcd.c
CSRC += $(DIR)/lcdc/bsp_rgb_lcd.c
CSRC += $(DIR)/lcdc/bsp_led_board.c
CSRC += $(DIR)/lcdc/bsp_lcdc_font.c
CSRC += $(DIR)/lcdc/gt9147.c
CSRC += $(DIR)/lcdc/ctiic.c
CSRC += $(DIR)/lcdc/touch.c

CSRC += $(DIR)/lcdc/demo_code/clock_menu.c
CSRC += $(DIR)/lcdc/demo_code/grad_menu.c
CSRC += $(DIR)/lcdc/demo_code/gui_cus_parts.c
CSRC += $(DIR)/lcdc/demo_code/light_menu.c
CSRC += $(DIR)/lcdc/demo_code/main_menu.c
CSRC += $(DIR)/lcdc/demo_code/realtek_demo.c
CSRC += $(DIR)/lcdc/demo_code/start_menu.c
CSRC += $(DIR)/lcdc/demo_code/tempre_menu.c
CSRC += $(DIR)/lcdc/demo_code/wave_menu.c
CSRC += $(DIR)/lcdc/demo_code/clock_pic.c
CSRC += $(DIR)/lcdc/demo_code/gradienter_pic.c
CSRC += $(DIR)/lcdc/demo_code/light_off_pic.c
CSRC += $(DIR)/lcdc/demo_code/light_on_pic.c
CSRC += $(DIR)/lcdc/demo_code/light_pic.c
CSRC += $(DIR)/lcdc/demo_code/realtek_logo.c
CSRC += $(DIR)/lcdc/demo_code/return_btn_pic.c
CSRC += $(DIR)/lcdc/demo_code/tempre_pic.c
CSRC += $(DIR)/lcdc/demo_code/wave_pic.c
endif

ifeq ($(CONFIG_USBD_VERIFY),y)
CSRC += $(DIR)/usb_otg/rtl8721d_usbd_test.c
endif

ifeq ($(CONFIG_USBH_VERIFY),y)
CSRC += $(DIR)/usb_otg/rtl8721d_usbh_test.c
endif

ifeq ($(CONFIG_USBD_CDC_ACM_TP),y)
CSRC += $(DIR)/usb_otg/usbd_cdc_acm/example_usbd_cdc_acm_tx_tp.c
endif

ifeq ($(CONFIG_USBD_CDC_ACM_RP),y)
CSRC += $(DIR)/usb_otg/usbd_cdc_acm/example_usbd_cdc_acm_rx_tp.c
endif

ifeq ($(CONFIG_USBD_CDC_ACM_TP_NEW),y)
CSRC += $(DIR)/usb_otg/usbd_cdc_acm_new/example_usbd_cdc_acm_tx_tp_new.c
endif

ifeq ($(CONFIG_USBD_CDC_ACM_RP_NEW),y)
CSRC += $(DIR)/usb_otg/usbd_cdc_acm_new/example_usbd_cdc_acm_rx_tp_new.c
endif

ifeq ($(CONFIG_USBH_CDC_ACM_VERIFY),y)
CSRC += $(DIR)/usb_otg/usbh_cdc_acm/usbh_cdc_acm_tp_test.c
endif

ifeq ($(CONFIG_WDG_VERIFY),y)
CSRC += $(DIR)/wdg/rtl8195a_wdg_test.c
endif

ifeq ($(CONFIG_IPC_VERIFY),y)
CSRC += $(DIR)/ipc/ipc_test.c
endif

ifeq ($(CONFIG_MPU_VERIFY),y)
CSRC += $(DIR)/mpu/mpu_test.c
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

ifeq ($(CONFIG_CACHE_VERIFY),y)
CSRC += $(DIR)/cache/rtl8721d_cache_test.c
endif

ifeq ($(CONFIG_SEC_VERIFY),y)
CSRC += $(DIR)/secure/secure_test_ns.c
CSRC += $(DIR)/secure/cryptoSimsecure.c
endif

ifeq ($(CONFIG_WFE_VERIFY),y)
CSRC += $(DIR)/wfe/wfe_test.c
endif

ifeq ($(CONFIG_IR_VERIFY),y)
CSRC += $(DIR)/IR/rtl8721d_ir_learn.c
CSRC += $(DIR)/IR/rtl8721d_ir_test.c
#CSRC += $(DIR)/IR/protocol/ir_nec_protocol.c
endif

ifeq ($(CONFIG_PMC_VERIFY),y)
CSRC += $(DIR)/pmc/pmc_test_hp.c
endif

ifeq ($(CONFIG_FTL_VERIFY),y)
CSRC += $(DIR)/ftl/rtl8721d_ftl_test.c
endif

ifeq ($(CONFIG_SDIOH_VERIFY),y)
CSRC += $(DIR)/sdio_host/rtl8721d_sdio_host_test.c
endif

CSRC += $(DIR)/rtl8721d_debugport.c
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
