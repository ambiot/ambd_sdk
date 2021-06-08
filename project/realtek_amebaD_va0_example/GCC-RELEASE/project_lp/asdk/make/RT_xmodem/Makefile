
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
MODULE_IFLAGS += -I$(TARGETDIR)/app/xmodem \
		 -I$(BASEDIR)/component/common/application/RT_xmodem \
                 -I$(TARGETDIR)/imgtool_floader/include

DIR = $(BASEDIR)/component/common/application/RT_xmodem
DIR_TAR = $(TARGETDIR)/imgtool_floader/src

vpath %.c $(DIR) $(DIR_TAR)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/floader_fw_update.c \
       $(DIR)/floader_xmodem.c \
       $(DIR_TAR)/rtl8721d_floader.c \
       $(DIR_TAR)/rtl8721d_floader_rom_parse.c

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS RENAME_LOADER_OBJS COPY_RAM_OBJS

	
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
