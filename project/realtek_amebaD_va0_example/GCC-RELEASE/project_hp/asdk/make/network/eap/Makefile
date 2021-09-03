
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/api/wifi/rtw_wpa_supplicant

vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#

CSRC +=	$(DIR)/src/eap_common/eap_common.c\
		$(DIR)/src/eap_common/eap_peap_common.c\

CSRC +=	$(DIR)/src/eap_peer/eap.c\
		$(DIR)/src/eap_peer/eap_methods.c\
		$(DIR)/src/eap_peer/eap_mschapv2.c\
		$(DIR)/src/eap_peer/eap_peap.c\
		$(DIR)/src/eap_peer/eap_tls.c\
		$(DIR)/src/eap_peer/eap_tls_common.c\
		$(DIR)/src/eap_peer/eap_ttls.c\
		$(DIR)/src/eap_peer/mschapv2.c\

CSRC +=	$(DIR)/src/crypto/des-internal.c\
		$(DIR)/src/crypto/md4-internal.c\
		$(DIR)/src/crypto/ms_funcs.c\
		$(DIR)/src/crypto/rc4.c\
		$(DIR)/src/crypto/sha1-internal.c\

CSRC +=	$(DIR)/src/utils/common.c\

CSRC += $(DIR)/wpa_supplicant/eap_protocol_handler.c\

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
	$(AR) rvs lib_eap.a $(OBJS)
	$(FROMELF) --strip-debug lib_eap.a
	$(MOVE) -f lib_eap.a $(ROOTDIR)/lib/application
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
