
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/verification/secure
MODULE_IFLAGS = -I$(DIR)./
MODULE_IFLAGS += -O0

vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
ifeq ($(CONFIG_SEC_VERIFY),y)
CSRC += $(DIR)/gdma/rtl8721d_gdma_test_secure.c
CSRC += $(DIR)/gdma/rtl8721d_gdma_llp_test_secure.c
CSRC += $(DIR)/efuse/rtl8721d_efuse_test_secure.c
CSRC += $(DIR)/cache/rtl8721d_cache_test_secure.c
CSRC += $(DIR)/crypto/rtl8721d_crc_test_secure.c
CSRC += $(DIR)/crypto/rtl8721d_aes_ecb_test_secure.c
CSRC += $(DIR)/crypto/rtl8721d_aes_ecb_sim.c
CSRC += $(DIR)/crypto/rtl8721d_crypto_test_secure.c
CSRC += $(DIR)/rdp/rdp_test.c
endif

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
