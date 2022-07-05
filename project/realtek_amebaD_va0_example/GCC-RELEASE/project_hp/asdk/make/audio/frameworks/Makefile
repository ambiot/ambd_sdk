
include $(MAKE_INCLUDE_GEN)

.PHONY: all audiolib playerlib clean


#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS =

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
#all: CORE_TARGETS
#	make -C media all

audiolib: CORE_TARGETS
	make -C media audiolib

playerlib: CORE_TARGETS
	make -C media playerlib

#*****************************************************************************#
#              GENERATE OBJECT FILE                                           #
#*****************************************************************************#
CORE_TARGETS: $(OBJS)




#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean:
	make -C media clean
-include $(DEPS)