
include $(MAKE_INCLUDE_GEN)


.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
OBJS =

#*****************************************************************************#
#                               Include Dependency                            #
#*****************************************************************************#
-include $(OBJS:.o=.d)


#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all: CORE_TARGETS COPY_RAM_OBJS
ifeq ($(CONFIG_PER_TEST),y)
	make -C verification all
endif
ifeq ($(CONFIG_DHRYSTONE_TEST),y)
	make -C coremark all
	make -C dhrystone all
endif
ifeq ($(CONFIG_RTLIB_VERIFY),y)
	make -C std_lib all
	make -C apple all
endif
#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean: 
	make -C coremark clean
	make -C dhrystone clean
	make -C std_lib clean
	make -C apple clean
	make -C verification clean

-include $(DEPS)
