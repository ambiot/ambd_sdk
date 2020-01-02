
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/wifi_fw/wifi_rcu_ram
#DIR_TEST = $(BASEDIR)/component/soc/realtek/amebad/wifi_fw/test

vpath %.c $(DIR)
#vpath %.c $(DIR_TEST)

#*****************************************************************************#
#                                Source FILE LIST                             #
#*****************************************************************************#
CSRC =$(DIR)/RTL8721D_RCU_Init_RAM.c \
      $(DIR)/RTL8721D_RCU_INT_RAM.c \
	  $(DIR)/RTL8721D_RCU_OS_SIG_RAM.c \
	  $(DIR)/RTL8721D_RCU_PowerCtrl_RAM.c \
	  $(DIR)/RTL8721D_RCU_Normal_Dbg.c \
	  $(DIR)/RTL8721D_RCU_PhyCfg_RAM.c \
	  $(DIR)/RTL8721D_RCU_WoWLAN_RAM.c \
	  $(DIR)/RTL8721D_RCU_Util_RAM.c \
       $(DIR)/RTL8721D_RCU_Task_RAM.c

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
	$(AR) rvs lib_wifi_ucps_fw.a $(OBJS)
	$(MOVE) -f lib_wifi_ucps_fw.a $(ROOTDIR)/lib/application

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
