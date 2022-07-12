
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/fwlib/ram_hp
DIR_COM = $(BASEDIR)/component/soc/realtek/amebad/fwlib/ram_common
CFGDIR = $(BASEDIR)/component/soc/realtek/amebad/fwlib/usrcfg
MODULE_IFLAGS = -I$(DIR)/../include/

vpath %.c $(DIR) $(DIR_COM) $(CFGDIR)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC =	\
	$(DIR)/rtl8721dhp_startup.c \
	$(DIR)/rtl8721dhp_app_start.c \
	$(DIR)/rtl8721dhp_clk.c \
	$(DIR)/rtl8721dhp_cpft.c \
	$(DIR)/rtl8721dhp_ota_ram.c \
	$(DIR)/rtl8721dhp_system.c \
	$(DIR)/rtl8721dhp_simulation.c \

CSRC +=	$(DIR)/rtl8721dhp_i2s.c \
	$(DIR)/rtl8721dhp_sdio.c \
	$(DIR)/rtl8721dhp_ssi.c \
	$(DIR)/rtl8721dhp_lcdc.c \
	$(DIR)/rtl8721dhp_usi_uart.c \
	$(DIR)/rtl8721dhp_usi_ssi.c \
	$(DIR)/rtl8721dhp_usi_i2c.c \
	$(DIR)/rtl8721dhp_audio.c \
	$(DIR)/rtl8721dhp_sdio_host.c \
	$(DIR)/rtl8721dhp_sd.c	\

CSRC +=	$(DIR_COM)/rtl8721d_i2c.c \
	$(DIR_COM)/rtl8721d_rtc.c \
	$(DIR_COM)/rtl8721d_uart.c \
	$(DIR_COM)/rtl8721d_tim.c \
	$(DIR_COM)/rtl8721d_adc.c \
	$(DIR_COM)/rtl8721d_comparator.c \
	$(DIR_COM)/rtl8721d_wdg.c \
	$(DIR_COM)/rtl8721d_flash_ram.c \
	$(DIR_COM)/rtl8721d_pll.c \
	$(DIR_COM)/rtl8721d_ir.c \
	$(DIR_COM)/rtl8721d_ipc_api.c \
	$(DIR_COM)/rtl8721d_sgpio.c \
	$(DIR_COM)/rtl8721d_keyscan.c \
	$(DIR_COM)/rtl8721d_captouch.c \
	$(DIR_COM)/rtl8721d_gdma_memcpy.c \
	$(DIR_COM)/rtl8721d_bor.c \
	$(DIR_COM)/rtl8721d_ram_libc.c \

CSRC +=	\
		$(CFGDIR)/rtl8721dlp_intfcfg.c \
		$(CFGDIR)/rtl8721dhp_intfcfg.c \
		$(CFGDIR)/rtl8721d_ipccfg.c \
		$(CFGDIR)/rtl8721d_wificfg.c \

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
#all: CORE_TARGETS
all: CORE_TARGETS COPY_RAM_OBJS

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
	$(REMOVE) *.su

-include $(DEPS)
