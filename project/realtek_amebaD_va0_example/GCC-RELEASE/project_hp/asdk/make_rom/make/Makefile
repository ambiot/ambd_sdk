include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
GLOBAL_CFLAGS += -DCONFIG_BUILD_ROM

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all:
	make -C ../vector all
	make -C ../fwlib all
	make -C ../crypto all
	make -C ../monitor all
	make -C ../string all
	#make -C ../apple all
	#make -C ../mbedtls all

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean:
	make -C ../vector clean
	make -C ../fwlib clean
	make -C ../crypto clean
	make -C ../monitor clean
	make -C ../string clean
	make -C ../apple clean
	make -C ../mbedtls clean

-include $(DEPS)
