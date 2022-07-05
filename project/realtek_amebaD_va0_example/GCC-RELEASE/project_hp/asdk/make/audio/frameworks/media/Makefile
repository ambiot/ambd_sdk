
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
audiolib: CORE_TARGETS
	make -C audio lib

playerlib: CORE_TARGETS
	make -C playback lib

#*****************************************************************************#
#              GENERATE OBJECT FILE                                           #
#*****************************************************************************#
CORE_TARGETS: $(OBJS)




#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean:
	make -C audio clean
	make -C playback clean
-include $(DEPS)
