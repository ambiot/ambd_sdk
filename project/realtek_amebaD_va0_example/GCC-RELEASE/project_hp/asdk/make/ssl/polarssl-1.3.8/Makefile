
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/network/ssl/polarssl-1.3.8
DIR_RAMMAP = $(BASEDIR)/component/common/network/ssl/ssl_ram_map

vpath %.c $(DIR) $(shell find $(DIR) -type d) $(DIR_RAMMAP) $(shell find $(DIR_RAMMAP) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/library/aesni.c			\
       $(DIR)/library/ccm.c			\
       $(DIR)/library/cipher.c			\
       $(DIR)/library/cipher_wrap.c		\
       $(DIR)/library/debug.c			\
       $(DIR)/library/ecp_ram.c		\
       $(DIR)/library/error.c			\
       $(DIR)/library/gcm.c			\
       $(DIR)/library/havege.c			\
       $(DIR)/library/memory_buffer_alloc.c	\
       $(DIR)/library/padlock.c		\
       $(DIR)/library/pbkdf2.c			\
       $(DIR)/library/pkcs5.c			\
       $(DIR)/library/pkcs11.c			\
       $(DIR)/library/pkcs12.c			\
       $(DIR)/library/pkparse.c		\
       $(DIR)/library/ssl_cache.c		\
       $(DIR)/library/ssl_cli.c		\
       $(DIR)/library/ssl_srv.c   		\
       $(DIR)/library/ssl_ciphersuites.c	\
       $(DIR)/library/ssl_tls.c		\
       $(DIR)/library/threading.c		\
       $(DIR)/library/timing.c			\
       $(DIR)/library/version.c		\
       $(DIR)/library/version_features.c	\
       $(DIR)/library/x509.c			\
       $(DIR)/library/x509_create.c		\
       $(DIR)/library/x509_crl.c		\
       $(DIR)/library/x509_crt.c		\
       $(DIR)/library/x509_csr.c		\
       $(DIR)/library/x509write_crt.c		\
       $(DIR)/library/x509write_csr.c		\
       $(DIR)/library/net.c		\
       $(DIR_RAMMAP)/ssl_ram_map.c	\
       $(DIR)/ssl_self_test.c

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

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)
