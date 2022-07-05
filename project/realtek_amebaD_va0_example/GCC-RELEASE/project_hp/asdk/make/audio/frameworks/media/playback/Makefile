
include $(MAKE_INCLUDE_GEN)

.PHONY: clean lib tests

#*****************************************************************************#
#                               VARIABLES	                                  #
#*****************************************************************************#

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets

tests:
ifeq ($(CONFIG_MEDIA_PLAYER),y)
	make -C standard/tests all
endif

lib:
ifeq ($(CONFIG_MEDIA_PLAYER),y)
	make -C standard lib
	make -C xip lib
endif
#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean:
ifeq ($(CONFIG_MEDIA_PLAYER),y)
	make -C standard clean
	make -C xip clean
	make -C standard/tests clean
endif

-include $(DEPS)
