
include $(MAKE_INCLUDE_GEN)
IFLAGS       += -I$(BASEDIR)/component/common/network/libcoap/include

.PHONY: lib lib_mp lib_lp lib_lt clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
MODULE_IFLAGS = -I$(DIR)/hal/rtl8721d/little_driver/include/

DIR = $(BASEDIR)/component/common/drivers/wlan/realtek/src
lib_mp:GLOBAL_CFLAGS += -DCONFIG_MP_INCLUDED
lib_lp:GLOBAL_CFLAGS += -DLOW_POWER_WIFI_CONNECT
lib_lt:GLOBAL_CFLAGS += -DLONG_PERIOD_TICKLESS
# OBJS_CONFIG: code run flash or sram based on config
# OBJS: Flash code
# OBJS_SRAM: SRAM code
#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
include ../config/Makefile.config


	

OBJS += $(DIR)/core/rom/rom_aes.o \
	$(DIR)/core/rom/rom_arc4.o \
	$(DIR)/core/rom/rom_md5.o \
	$(DIR)/core/rom/rom_rc4.o \
	$(DIR)/core/rom/rom_sha1.o \
	$(DIR)/core/rom/rom_rtw_ieee80211.o \
	$(DIR)/core/rom/rom_rtw_psk.o \
	$(DIR)/core/rom/rom_rtw_security.o \
	$(DIR)/../ram_patch/ram_patch_8721d.o \
	$(DIR)/../wlan_ram_map/rom/rom_wlan_ram_map.o

OBJS += $(DIR)/../wlan_ram_map/wlan_ram_map.o
ifeq ($(CONFIG_WIFI_TEST),y)
OBJS += $(DIR)/../tests/rtl8195a_wlan_test.o
endif

# Little driver for DLPS
OBJS += $(DIR)/hal/rtl8721d/little_driver/src/hw/rs8721d_phystatus.o \
	$(DIR)/hal/rtl8721d/little_driver/src/hw/rs8721d_ops.o \
	$(DIR)/hal/rtl8721d/little_driver/src/hw/rs8721d_cmd.o \
	$(DIR)/hal/rtl8721d/little_driver/src/hw/rs8721d_halinit.o \
	$(DIR)/hal/rtl8721d/little_driver/src/hw/rs8721d_recv.o \
	$(DIR)/hal/rtl8721d/little_driver/src/hw/rs8721d_suspend.o \
	$(DIR)/hal/rtl8721d/little_driver/src/hw/rs8721d_xmit.o \
	$(DIR)/hal/rtl8721d/little_driver/src/hw/rs8721d_interrupt.o \
	$(DIR)/hal/rtl8721d/little_driver/src/ethernet_rswlan.o \
	$(DIR)/hal/rtl8721d/little_driver/src/rs_intfs.o \
	$(DIR)/hal/rtl8721d/little_driver/src/rs_network.o \

OBJS_SRAM += \
	$(DIR)/core/rtw_xmit.o	\
	$(DIR)/core/rtw_recv.o \
	$(DIR)/osdep/freertos/lxbus_intf.o \
	$(DIR)/osdep/freertos/freertos_skbuff.o \
	$(DIR)/osdep/freertos/freertos_isr.o \
	$(DIR)/osdep/freertos/freertos_recv.o \
	$(DIR)/osdep/freertos/freertos_xmit.o \
	$(DIR)/osdep/freertos/rtk_wlan_if.o \

OBJS_SRAM += $(DIR)/hal/phydm/phydm_cfotracking.o \
	$(DIR)/hal/phydm/phydm_antdiv.o \
	$(DIR)/hal/phydm/phydm_math_lib.o \
	$(DIR)/hal/phydm/phydm_phystatus.o \
	$(DIR)/hal/phydm/phydm_soml.o
	
OBJS_SRAM += $(DIR)/hal/rtl8721d/src/lx_bus/rtl8721d_xmit.o
OBJS_SRAM += $(DIR)/hal/rtl8721d/src/rtl8721d_rf_onoff.o

#ifeq ($(CONFIG_HIGH_TP),y)
#OBJS_SRAM += $(OBJS_CONFIG)
#else
OBJS += $(OBJS_CONFIG)
#endif
#*****************************************************************************#
#                               Dependency	                              #
#*****************************************************************************#
-include $(OBJS:.o=.d)

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
lib: CORE_TARGETS COPY_RAM_OBJS
	$(AR) rvs lib_wlan.a $(OBJS) $(OBJS_SRAM)
	$(FROMELF) --strip-debug lib_wlan.a
	$(MOVE) -f lib_wlan.a $(ROOTDIR)/lib/application
lib_mp: CORE_TARGETS COPY_RAM_OBJS
	$(AR) rvs lib_wlan_mp.a $(OBJS) $(OBJS_SRAM)
	$(FROMELF) --strip-debug lib_wlan_mp.a
	$(MOVE) -f lib_wlan_mp.a $(ROOTDIR)/lib/application
lib_lp: CORE_TARGETS COPY_RAM_OBJS
	$(AR) rvs lib_wlan_lp.a $(OBJS) $(OBJS_SRAM)
	$(FROMELF) --strip-debug lib_wlan_lp.a
	$(MOVE) -f lib_wlan_lp.a $(ROOTDIR)/lib/application
lib_lt: CORE_TARGETS COPY_RAM_OBJS
	$(AR) rvs lib_wlan_lt.a $(OBJS) $(OBJS_SRAM)
	$(FROMELF) --strip-debug lib_wlan_lt.a
	$(MOVE) -f lib_wlan_lt.a $(ROOTDIR)/lib/application
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
