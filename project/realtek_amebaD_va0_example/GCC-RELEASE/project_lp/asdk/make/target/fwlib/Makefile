
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/fwlib/ram_lp
CFGDIR = $(BASEDIR)/component/soc/realtek/amebad/fwlib/usrcfg
DIR_COM = $(BASEDIR)/component/soc/realtek/amebad/fwlib/ram_common
MODULE_IFLAGS = -I$(DIR)/../include/

vpath %.c $(DIR) $(DIR_COM) $(CFGDIR)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC =	$(DIR)/rtl8721dlp_pinmap.c \
	$(DIR)/rtl8721dlp_clk.c \
	$(DIR)/rtl8721dlp_cpft.c \
	$(DIR)/rtl8721dlp_system.c \
	$(DIR)/rtl8721dlp_app_start.c \
	$(DIR)/rtl8721dlp_startup.c \
	$(DIR)/rtl8721dlp_km4.c \
	$(DIR)/rtl8721dlp_simulation.c \
	$(DIR)/rtl8721dlp_flashclk.c \

CSRC +=	$(CFGDIR)/rtl8721dlp_pinmapcfg.c \
	$(CFGDIR)/rtl8721dlp_intfcfg.c \
	$(CFGDIR)/rtl8721dlp_sleepcfg.c \
	$(CFGDIR)/rtl8721dlp_flashcfg.c \
	$(CFGDIR)/rtl8721d_ipccfg.c \
	$(CFGDIR)/rtl8721d_wificfg.c \

CSRC +=	$(DIR_COM)/rtl8721d_uart.c \
	$(DIR_COM)/rtl8721d_efuse.c \
	$(DIR_COM)/rtl8721d_flash_ram.c \
	$(DIR_COM)/rtl8721d_i2c.c \
	$(DIR_COM)/rtl8721d_rtc.c \
	$(DIR_COM)/rtl8721d_wdg.c \
	$(DIR_COM)/rtl8721d_keyscan.c \
	$(DIR_COM)/rtl8721d_sgpio.c \
	$(DIR_COM)/rtl8721d_tim.c \
	$(DIR_COM)/rtl8721d_qdec.c \
	$(DIR_COM)/rtl8721d_captouch.c \
	$(DIR_COM)/rtl8721d_pll.c \
	$(DIR_COM)/rtl8721d_ipc_api.c \
	$(DIR_COM)/rtl8721d_adc.c \
	$(DIR_COM)/rtl8721d_comparator.c \
	$(DIR_COM)/rtl8721d_bor.c \

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
