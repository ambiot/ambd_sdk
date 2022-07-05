
include $(MAKE_INCLUDE_GEN)

.PHONY: all test lib clean


#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS =

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
test: CORE_TARGETS
ifeq ($(CONFIG_AUDIO_MIXER_SERVICE),y)
	make -C lite/audio_stream/tests all
else ifeq ($(CONFIG_AUDIO_PASSTHROUGH_INTERFACE),y)
	make -C passthrough/tests all
endif

lib: CORE_TARGETS
ifeq ($(CONFIG_AUDIO_MIXER_SERVICE),y)
	make -C algorithms lib
	make -C lite lib
else ifeq ($(CONFIG_AUDIO_PASSTHROUGH_INTERFACE),y)
	make -C passthrough lib
endif
	make -C xip lib
	make -C preprocess lib
#*****************************************************************************#
#              GENERATE OBJECT FILE                                           #
#*****************************************************************************#
CORE_TARGETS: $(OBJS)




#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean:
	make -C algorithms clean
	make -C lite clean
	make -C passthrough clean
	make -C lite/audio_stream/tests clean
	make -C passthrough/tests clean
	make -C xip clean
	make -C preprocess clean
-include $(DEPS)
