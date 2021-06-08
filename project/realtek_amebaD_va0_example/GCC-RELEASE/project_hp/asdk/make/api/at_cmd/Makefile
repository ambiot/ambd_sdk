
include $(MAKE_INCLUDE_GEN)
MESH_MULTIPLE_PROFILE_DIR = $(BASEDIR)/component/common/bluetooth/realtek/sdk/example/bt_mesh_multiple_profile

IFLAGS               += -I$(BASEDIR)/component/common/network/libcoap/include


.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/api/at_cmd

vpath %.c $(DIR)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC +=	$(DIR)/atcmd_sys.c \
		$(DIR)/atcmd_wifi.c \
		$(DIR)/atcmd_lwip.c \
		$(DIR)/log_service.c \
		$(DIR)/atcmd_mp.c \
		$(DIR)/atcmd_mp_ext2.c \

ifeq ($(CONFIG_BT_EN), y)
CSRC += $(DIR)/atcmd_bt.c
endif	

ifeq ($(CONFIG_LINKKIT_AWSS), y)
CSRC += $(DIR)/atcmd_linkkit.c
endif	
#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                               Include Dependency                            #
#*****************************************************************************#
-include $(OBJS:.o=.d)


#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all: CORE_TARGETS COPY_RAM_OBJS
#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean: CLEAN_OBJS 
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)
