
include $(MAKE_INCLUDE_GEN)
#include ./Makefile.inc

.PHONY: all clean

CHIP = rtl8195a
HALINCDIR = realtek/v3_0/include

MODULE_IFLAGS += -I$(shell pwd -L)/../inc
MODULE_IFLAGS += -I$(SWLIBDIR)/api
MODULE_IFLAGS += -I$(SWLIBDIR)/api/mbed/hal/
MODULE_IFLAGS += -I$(SWLIBDIR)/api/mbed/api/
MODULE_IFLAGS += -I$(SWLIBDIR)/drivers/targets/cmsis/rtl8195a/
MODULE_IFLAGS += -I$(SWLIBDIR)/drivers/targets/hal/rtl8195a/

GLOBAL_CFLAGS += -DCONFIG_PLATFORM_8195A
#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC       += main.c 
		
		
#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS        = $(CSRC:.c=.o)


#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
#OBJS = monitor.o rtl_consol.o

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
#              GENERATE OBJECT FILE 
#*****************************************************************************#
clean:
	rm -f $(CSRC:.c=.o) $(CSRC:.c=.d) $(CSRC:.c=.i) $(CSRC:.c=.s)
