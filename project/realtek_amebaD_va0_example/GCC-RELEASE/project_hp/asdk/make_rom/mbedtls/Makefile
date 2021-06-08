
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/network/ssl/mbedtls-2.4.0/library/rom
DIR_MAP = $(BASEDIR)/component/common/network/ssl/ssl_ram_map/rom
MODULE_IFLAGS += -I../../include -fno-tree-switch-conversion -Os

GLOBAL_CFLAGS += -DCONFIG_SSL_ROM
GLOBAL_CFLAGS += -DCONFIG_BUILD_ROM

vpath %.c $(DIR) $(DIR_MAP)
#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC =	   $(DIR)/mbedtls_rom_aes.c	\
	   $(DIR)/mbedtls_rom_arc4.c	\
	   $(DIR)/mbedtls_rom_asn1parse.c	\
	   $(DIR)/mbedtls_rom_asn1write.c 	\
	   $(DIR)/mbedtls_rom_base64.c	\
	   $(DIR)/mbedtls_rom_bignum.c	\
	   $(DIR)/mbedtls_rom_ctr_drbg.c	\
	   $(DIR)/mbedtls_rom_des.c	\
	   $(DIR)/mbedtls_rom_dhm.c	\
	   $(DIR)/mbedtls_rom_ecdh.c	\
	   $(DIR)/mbedtls_rom_ecdsa.c	\
	   $(DIR)/mbedtls_rom_ecp.c	\
	   $(DIR)/mbedtls_rom_ecp_curves.c	\
	   $(DIR)/mbedtls_rom_ecjpake.c	\
	   $(DIR)/mbedtls_rom_hmac_drbg.c	\
	   $(DIR)/mbedtls_rom_md.c		\
	   $(DIR)/mbedtls_rom_md_wrap.c	\
	   $(DIR)/mbedtls_rom_md5.c	\
	   $(DIR)/mbedtls_rom_oid.c	\
	   $(DIR)/mbedtls_rom_pem.c	\
	   $(DIR)/mbedtls_rom_pk.c		\
	   $(DIR)/mbedtls_rom_pk_wrap.c	\
	   $(DIR)/mbedtls_rom_pkwrite.c	\
	   $(DIR)/mbedtls_rom_rsa.c	\
	   $(DIR)/mbedtls_rom_sha1.c	\
	   $(DIR)/mbedtls_rom_sha256.c	\
	   $(DIR)/mbedtls_rom_sha512.c     \
	   $(DIR_MAP)/rom_ssl_ram_map.c

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                           ROM Object FILE LIST                              #
#*****************************************************************************#
MBEDTLS_ROM_OBJS =	mbedtls_rom_aes.o		\
		mbedtls_rom_arc4.o		\
		mbedtls_rom_asn1parse.o		\
		mbedtls_rom_asn1write.o		\
		mbedtls_rom_base64.o		\
		mbedtls_rom_bignum.o		\
		mbedtls_rom_ctr_drbg.o		\
		mbedtls_rom_des.o		\
		mbedtls_rom_dhm.o		\
		mbedtls_rom_ecdh.o		\
		mbedtls_rom_ecdsa.o		\
		mbedtls_rom_ecp.o		\
		mbedtls_rom_ecp_curves.o	\
		mbedtls_rom_hmac_drbg.o		\
		mbedtls_rom_md.o		\
		mbedtls_rom_md_wrap.o		\
		mbedtls_rom_md5.o		\
		mbedtls_rom_oid.o		\
		mbedtls_rom_pem.o		\
		mbedtls_rom_pk.o		\
		mbedtls_rom_pk_wrap.o		\
		mbedtls_rom_pkwrite.o		\
		mbedtls_rom_rsa.o		\
		mbedtls_rom_sha1.o		\
		mbedtls_rom_sha256.o		\
		mbedtls_rom_sha512.o		\
		mbedtls_rom_ecjpake.o		\
#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS RENAME_ROM_OBJS COPY_ROM_OBJS
	
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

-include $(DEPS)
