
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/os/freertos/freertos_v10.2.0
DIR_PORT = $(DIR)/Source/portable/GCC/RTL8721D_HP/non_secure

vpath port.c $(DIR_PORT)
vpath portasm.c $(DIR_PORT)
vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/Source/tasks.c \
       $(DIR)/Source/list.c \
       $(DIR)/Source/croutine.c \
       $(DIR)/Source/queue.c \
       $(DIR)/Source/timers.c \
       $(DIR)/Source/event_groups.c \
       $(DIR)/Source/stream_buffer.c

CSRC+= $(DIR_PORT)/port.c \
       $(DIR_PORT)/portasm.c

CSRC+= $(DIR)/Source/portable/MemMang/heap_5.c

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
#all: CORE_TARGETS COPY_RAM_OBJS
all: CORE_TARGETS COPY_RAM_OBJS
	
#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS:	$(OBJS)

%.o:%.c
	$(CC) $(GLOBAL_CFLAGS) $(MODULE_IFLAGS) $<  -o $@
	$(FROMELF) --prefix-sections .image2.net.ram $@
	
#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d
	
-include $(DEPS)
