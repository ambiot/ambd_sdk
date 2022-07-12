
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/app/monitor/rom
DIR_SHELL = $(BASEDIR)/component/soc/realtek/amebad/app/shell/rom
MODULE_IFLAGS += -I$(DIR)/../../include
MODULE_IFLAGS += -Os

GLOBAL_CFLAGS += -DCONFIG_BUILD_ROM

vpath %.c $(DIR) $(DIR_SHELL)
#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
MONI_ROM_OBJS = $(DIR)/monitor_rom.o \
		$(DIR)/shell_rom.o \
		#$(DIR_SHELL)/cmd_shell_rom.o \
		#$(DIR_SHELL)/consol_cmds.o \
		#$(DIR_SHELL)/shell.o \
		#$(DIR)/monitor_lib.o

OBJS = $(notdir $(MONI_ROM_OBJS))

#*****************************************************************************#
#                           ROM Object FILE LIST                              #
#*****************************************************************************#

APP_ROM_OBJS = monitor_rom.o shell_rom.o #monitor_lib.o

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
