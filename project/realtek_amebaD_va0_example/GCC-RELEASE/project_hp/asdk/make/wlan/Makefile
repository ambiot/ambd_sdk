
include $(MAKE_INCLUDE_GEN)

.PHONY: all lib lib_mp clean


#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = 

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
lib: CORE_TARGETS
	make -C sram lib
	make -C xip lib
	
lib_mp: CORE_TARGETS
	make -C sram lib_mp
	make -C xip lib_mp
all:
	make -C option all

#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

	


#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: 
	make -C sram clean
	make -C xip clean
	make -C option clean
	



