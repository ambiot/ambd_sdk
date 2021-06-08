
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/network/ssl/mbedtls-2.4.0
DIR_RAMMAP = $(BASEDIR)/component/common/network/ssl/ssl_ram_map

MODULE_IFLAGS += -DCONFIG_BUILD_SECURE=1

vpath %.c $(DIR) $(shell find $(DIR) -type d) $(DIR_RAMMAP) $(shell find $(DIR_RAMMAP) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/library/aes.c			\
       $(DIR)/library/asn1parse.c		\
       $(DIR)/library/asn1write.c		\
       $(DIR)/library/base64.c			\
       $(DIR)/library/bignum.c			\
       $(DIR)/library/ecdsa.c			\
       $(DIR)/library/ecp.c			\
       $(DIR)/library/ecp_curves.c		\
       $(DIR)/library/md.c			\
       $(DIR)/library/md5.c			\
       $(DIR)/library/md_wrap.c			\
       $(DIR)/library/oid.c			\
       $(DIR)/library/pem.c			\
       $(DIR)/library/pk.c			\
       $(DIR)/library/pk_wrap.c			\
       $(DIR)/library/platform.c		\
       $(DIR)/library/rsa.c			\
       $(DIR)/library/sha1.c			\
       $(DIR)/library/sha256.c			\
       $(DIR)/library/sha512.c			\
       $(DIR)/library/ssl_tls.c			\
       $(DIR_RAMMAP)/ssl_ram_map.c		\
       $(DIR_RAMMAP)/rom/rom_ssl_ram_map.c	\
       $(DIR)/library/pkparse.c

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
# Define the Rules to build the core targets
all: CORE_TARGETS COPY_RAM_OBJS

#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

%.o:%.c
	$(CC) -ffunction-sections $(GLOBAL_CFLAGS) $(MODULE_IFLAGS) $<  -o $@
	$(FROMELF) --prefix-alloc-sections .psram $@

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)
