
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/application/apple
MODULE_IFLAGS += -I$(DIR)/WACServer/External/Curve25519 \
		 -I$(DIR)/WACServer/External/GladmanAES \
		 -I$(DIR)/homekit/crypto/chacha \
		 -I$(DIR)/homekit/crypto/poly1305 \
		 -I$(DIR)/homekit/crypto/ed25519 \
		 -I$(DIR)/homekit/crypto/ed25519/core \
		 -I$(DIR)/homekit/crypto/sha512
MODULE_IFLAGS += -Os

GLOBAL_CFLAGS += -DCONFIG_SSL_ROM
GLOBAL_CFLAGS += -DCONFIG_BUILD_ROM

vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
#CSRC += $(DIR)/WACServer/External/GladmanAES/rom_wac_aes_modes.c \
	$(DIR)/WACServer/External/GladmanAES/rom_wac_aeskey.c \
	$(DIR)/WACServer/External/GladmanAES/rom_wac_aestab.c

CSRC += $(DIR)/homekit/crypto/chacha/rom_homekit_chacha_enc.c \
	$(DIR)/homekit/crypto/poly1305/rom_homekit_poly1305.c \


CSRC += $(DIR)/WACServer/External/Curve25519/rom_wac_curve25519-donna.c \
	$(DIR)/homekit/crypto/ed25519/rom_homekit_ed25519.c \
	$(DIR)/homekit/crypto/ed25519/rom_homekit_ed25519_keypair.c \
	$(DIR)/homekit/crypto/ed25519/rom_homekit_ed25519_sign.c \
	$(DIR)/homekit/crypto/ed25519/rom_homekit_ed25519_open.c \
	$(DIR)/homekit/crypto/ed25519/rom_homekit_ed25519_ge_fe.c \
	$(DIR)/homekit/crypto/ed25519/rom_homekit_ed25519_sc.c \
	$(DIR)/homekit/crypto/sha512/rom_homekit_sha512.c 

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                              For ROM LINK                                   #
#*****************************************************************************#
APPLE_ROM_OBJS = rom_wac_curve25519-donna.o \
		rom_homekit_sha512.o \
		rom_homekit_ed25519.o \
		rom_homekit_ed25519_keypair.o \
		rom_homekit_ed25519_sign.o \
		rom_homekit_ed25519_open.o \
		rom_homekit_ed25519_ge_fe.o \
		rom_homekit_ed25519_sc.o

#APPLE_ROM_OBJS+ = rom_wac_aes_modes.o rom_wac_aeskey.o rom_wac_aestab.o

APPLE_ROM_OBJS += rom_homekit_chacha_enc.o rom_homekit_poly1305.o
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
