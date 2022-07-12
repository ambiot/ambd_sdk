
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

MODULE_IFLAGS = -I./


#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = main.o 
ifeq ($(CONFIG_RELEASE_BUILD),y)
	OBJS = 
else
	ifeq ($(CONFIG_RELEASE_BUILD_LIBRARIES),y)
	OBJS =
	endif
endif


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
clean: 
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)	
