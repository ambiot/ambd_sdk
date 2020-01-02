
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean


#*****************************************************************************#
#                            OBJECT FILE LIST                                 #
#*****************************************************************************#
OBJS =

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all:

ifneq ($(CONFIG_TOOLCHAIN_ARM_GCC), y)
ifeq ($(COMPILEOS),$(LINUX_OS))
	if [ ! -f $(KM4_BUILDDIR)/toolchain/asdk/asdk-6.4.1-linux-newlib-build-2773-i686.tar.bz2 ] ; then cat $(KM4_BUILDDIR)/toolchain/asdk/asdk-6.4.1-linux-newlib-build-2773-i686.tar.bz2* > $(KM4_BUILDDIR)/toolchain/asdk/asdk-6.4.1-linux-newlib-build-2773-i686.tar.bz2; fi;\
	$(MKDIR) -p linux
	tar -jxvf $(KM4_BUILDDIR)/toolchain/asdk/asdk-6.4.1-linux-newlib-build-2773-i686.tar.bz2 -C linux/

	#LZM for GCC Server build & Cygwin Download
	#$(MKDIR) -p cygwin
	#tar -jxvf asdk/asdk-4.9.3-m4-EL-rtos-n2.1-a16ft-150617-cygwin.tar.bz2 -C cygwin/
else
	if [ ! -f $(KM4_BUILDDIR)/toolchain/asdk/asdk-6.4.1-cygwin-newlib-build-2778-i686.tar.bz2 ] ; then cat $(KM4_BUILDDIR)/toolchain/asdk/asdk-6.4.1-cygwin-newlib-build-2778-i686.tar.bz2* > $(KM4_BUILDDIR)/toolchain/asdk/asdk-6.4.1-cygwin-newlib-build-2778-i686.tar.bz2; fi;\
	$(MKDIR) -p cygwin
	tar -jxvf $(KM4_BUILDDIR)/toolchain/asdk/asdk-6.4.1-cygwin-newlib-build-2778-i686.tar.bz2 -C cygwin/
endif

else
	$(MKDIR) -p cygwin
	tar -zxvf ../../../tools/arm-none-eabi-gcc/4.8.3-2014q1.tar.gz -C cygwin/
endif

#*****************************************************************************#
#                          GENERATE OBJECT FILES                              #
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

