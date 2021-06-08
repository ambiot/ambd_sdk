
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/soc/realtek/amebad/swlib/string
GLOBAL_CFLAGS += -DCONFIG_BUILD_ROM

vpath %.c $(DIR)
#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/diag.c \
	$(DIR)/memset.c \
	$(DIR)/sscanf.c \
	$(DIR)/rand.c \
	$(DIR)/memcpy.c \
	$(DIR)/memcmp.c \
	$(DIR)/memchr.c \
	$(DIR)/memmove.c \
	$(DIR)/strcat.c \
	$(DIR)/strncat.c \
	$(DIR)/strchr.c \
	$(DIR)/strcmp.c \
	$(DIR)/strncmp.c \
	$(DIR)/strlen.c \
	$(DIR)/strcpy.c \
	$(DIR)/strncpy.c \
	$(DIR)/strsep.c \
	$(DIR)/strstr.c \
	$(DIR)/strtok.c \
	$(DIR)/strtok_r.c \
	$(DIR)/stricmp.c \
	$(DIR)/strupr.c \
	$(DIR)/stratoi.c \
	$(DIR)/strnlen.c \
	$(DIR)/strtol.c \
	$(DIR)/strtoul.c \
	$(DIR)/strtod.c \
	$(DIR)/strpbrk.c \
	$(DIR)/char2num.c \
	#$(DIR)/printf.c \

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                           ROM Object FILE LIST                              #
#*****************************************************************************#
SWLIB_ROM_OBJS = diag.o \
	memcmp.o \
	memcpy.o \
	memset.o \
	rand.o \
	sscanf.o \
	memchr.o \
	memmove.o \
	strcat.o \
	strncat.o \
	strchr.o \
	strcmp.o \
	strcpy.o \
	strlen.o \
	strncmp.o \
	strncpy.o \
	strsep.o \
	strstr.o \
	strtok.o \
	strtok_r.o \
	stricmp.o \
	strupr.o \
	stratoi.o \
	strnlen.o \
	strtol.o \
	strtoul.o \
	strtod.o \
	strpbrk.o \
	#printf.o
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
