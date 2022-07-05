include $(MAKE_INCLUDE_GEN)

.PHONY: all lib clean

#*****************************************************************************#
#                               VARIABLES	                                  #
#*****************************************************************************#

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets

all:lib

lib:
ifeq ($(CONFIG_MEDIA_CODEC_SW_HELIX_AAC),y)
	make -C haac all
endif
#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean:
ifeq ($(CONFIG_MEDIA_CODEC_SW_HELIX_AAC),y)
	make -C haac clean
endif

-include $(DEPS)
