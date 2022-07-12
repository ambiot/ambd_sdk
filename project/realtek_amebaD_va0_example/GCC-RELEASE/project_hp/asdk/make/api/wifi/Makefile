
include $(MAKE_INCLUDE_GEN)
IFLAGS               += -I$(BASEDIR)/component/common/network/libcoap/include

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/api/wifi

vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC +=		$(DIR)/wifi_util.c \
		$(DIR)/wifi_conf.c \
		$(DIR)/wifi_promisc.c \
		$(DIR)/wifi_ind.c \
		$(DIR)/wifi_simple_config.c \
		$(DIR)/rtw_wpa_supplicant/wpa_supplicant/wifi_eap_config.c \
		$(DIR)/rtw_wpa_supplicant/wpa_supplicant/wifi_p2p_config.c \
		$(DIR)/rtw_wpa_supplicant/wpa_supplicant/wifi_wps_config.c \
		$(DIR)/rtw_wpa_supplicant/src/crypto/tls_polarssl.c

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
