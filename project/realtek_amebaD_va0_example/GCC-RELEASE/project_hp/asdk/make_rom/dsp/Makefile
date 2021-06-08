
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/cmsis-dsp/rom
#MODULE_IFLAGS += -Os
GLOBAL_CFLAGS += -DCONFIG_BUILD_ROM

vpath %.c $(DIR)
#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC =	$(wildcard $(DIR)/*.c) 		

CSRC_NOTDIR = $(notdir $(CSRC))

OBJS = $(patsubst %.c, %.o, $(CSRC_NOTDIR))
#*****************************************************************************#
#                           ROM Object FILE LIST                              #
#*****************************************************************************#
HWLIB_ROM_OBJS=$(patsubst %.c,%.o,$(CSRC_NOTDIR))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS RENAME_ROM_OBJS COPY_ROM_OBJS
	
#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS: $(OBJS)



#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d
	$(REMOVE) *.c

-include $(DEPS)
