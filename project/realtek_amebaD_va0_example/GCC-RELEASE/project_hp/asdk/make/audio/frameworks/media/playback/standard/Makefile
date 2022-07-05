
include $(MAKE_INCLUDE_GEN)

.PHONY: lib clean

#*****************************************************************************#
#                               VARIABLES	                                  #
#*****************************************************************************#

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets

lib:
	make -C utils all
	make -C common all
	make -C source all
	make -C demux all
	make -C codec all
	make -C core all
	make -C libmedia all

#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean:
	make -C utils clean
	make -C common clean
	make -C source clean
	make -C demux clean
	make -C codec clean
	make -C core clean
	make -C libmedia clean


-include $(DEPS)
