
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/wifi_fw/ram
DIR_TEST = $(BASEDIR)/component/soc/realtek/amebad/wifi_fw/test

GLOBAL_CFLAGS += -DCONFIG_LONGPERIOD_TICKLESS=0
GLOBAL_CFLAGS += -DCONFIG_1FIRELINE_PowerProtect=0

vpath %.c $(DIR)
vpath %.c $(DIR_TEST)

#*****************************************************************************#
#                                Source FILE LIST                             #
#*****************************************************************************#
CSRC =$(DIR)/RTL8721D_BTConCurr_RAM.c \
       $(DIR)/RTL8721D_Cmd_RAM.c \
       $(DIR)/RTL8721D_Coex_RAM.c \
       $(DIR)/RTL8721D_debug_RAM.c \
       $(DIR)/RTL8721D_FastChannelSwitch_RAM.c \
       $(DIR)/RTL8721D_GPIO_RAM.c    \
       $(DIR)/RTL8721D_Init_RAM.c \
       $(DIR)/RTL8721D_IQK_RAM.c   \
       $(DIR)/RTL8721D_LTECOEX_RAM.c \
       $(DIR)/RTL8721D_Packet_RAM.c \
       $(DIR)/RTL8721D_PhyCfg_RAM.c \
       $(DIR)/RTL8721D_PowerCtrl_RAM.c \
       $(DIR)/RTL8721D_RateAdaptive_RAM.c  \
       $(DIR)/RTL8721D_SWTimer_RAM.c \
       $(DIR)/RTL8721D_TxBF_RAM.c    \
       $(DIR)/RTL8721D_TxReport_RAM.c    \
       $(DIR)/RTL8721D_Util_RAM.c  \
       $(DIR)/RTL8721D_Efuse_RAM.c \
       $(DIR)/RTL8721D_INT_RAM.c \
       $(DIR)/RTL8721D_LockChip_RAM.c \
       $(DIR)/RTL8721D_NAN_RAM.c \
       $(DIR)/RTL8721D_PSD_RAM.c \
       $(DIR)/RTL8721D_AP_Offload_RAM.c \
       $(DIR)/RTL8721D_APPSOffload_RAM.c \
       $(DIR)/RTL8721D_D0_Scan_Offlad_RAM.c \
       $(DIR)/RTL8721D_MLME_RAM.c \
       $(DIR)/RTL8721D_P2POffload_RAM.c \
       $(DIR)/RTL8721D_RLPS_RAM.c \
       $(DIR)/RTL8721D_Teredo_RAM.c \
       $(DIR)/RTL8721D_P2PPS_RAM.c \
       $(DIR)/RTL8721D_PowerSave_RAM.c \
       $(DIR)/RTL8721D_RealWoW_V2_RAM.c \
       $(DIR)/RTL8721D_GTK_RAM.c	\
       $(DIR)/RTL8721D_NLO_RAM.c	\
	   $(DIR)/RTL8721D_Normal_Dbg.c	\
	   $(DIR)/RTL8721D_CP_FT_TEST_RAM.c	\
       $(DIR)/RTL8721D_WoWLAN_RAM.c     \
       $(DIR)/RTL8721D_Phydm_Offload_RAM.c     \
       $(DIR)/RTL8721D_RegConfig_RAM.c
#ifeq ($(CONFIG_WIFI_FW_VERIFY),y)
CSRC +=	$(DIR_TEST)/RTL8721D_Serial_IO_Test.c \
       $(DIR_TEST)/RTL8721D_BUF_Test.c \
       $(DIR_TEST)/RTL8721D_DDMA_Test.c \
       $(DIR_TEST)/RTL8721D_Efuse_Test.c \
       $(DIR_TEST)/RTL8721D_INT_Test.c \
       $(DIR_TEST)/RTL8721D_IOPATH_Test.c \
       $(DIR_TEST)/RTL8721D_REG_Test.c    \
       $(DIR_TEST)/RTL8721D_ROM_Test.c \
       $(DIR_TEST)/RTL8721D_SecEng_Test.c \
       $(DIR_TEST)/RTL8721D_FWLBK_Test.c \
       $(DIR_TEST)/RTL8721D_test.c
#endif

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                               Dependency	                              #
#*****************************************************************************#
-include $(OBJS:.o=.d)

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS COPY_RAM_OBJS
	$(AR) rvs lib_wifi_fw.a $(OBJS)
	$(FROMELF) --strip-debug lib_wifi_fw.a
	$(MOVE) -f lib_wifi_fw.a $(ROOTDIR)/lib/application

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
