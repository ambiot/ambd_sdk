
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/verification/swlib/apple

MODULE_IFLAGS = -I$(BASEDIR)/component/common/application/apple/homekit/crypto/chacha \
	-I$(BASEDIR)/component/common/application/apple/homekit/crypto/ed25519 \
	-I$(BASEDIR)/component/common/application/apple/homekit/crypto/ed25519/core \
	-I$(BASEDIR)/component/common/application/apple/homekit/crypto/poly1305 \
	-I$(BASEDIR)/component/common/application/apple/homekit/crypto/sha512 \
	-I$(BASEDIR)/component/common/application/apple/WACServer/External/Curve25519 \
	-I$(BASEDIR)/component/common/application/apple/WACServer/External/GladmanAES \

vpath %.c $(DIR)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC =  \
       $(DIR)/curve25519-donna-test.c \
       $(DIR)/ed25519_test.c \
       $(DIR)/sha512_hkdf_test.c

#CSRC += $(DIR)/aes_test.c

CSRC += $(DIR)/chachatest.c \
       $(DIR)/poly1305test.c \

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS COPY_RAM_OBJS
	
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

