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
	make -C ../fwlib_ns all
	make -C ../crypto all
	make -C ../monitor all
	make -C ../string all
	make -C ../apple all
	make -C ../mbedtls all
	make -C ../dsp all

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean:
	make -C ../vector clean
	make -C ../fwlib_ns clean
	make -C ../crypto clean
	make -C ../monitor clean
	make -C ../string clean
	make -C ../apple clean
	make -C ../mbedtls clean
	make -C ../dsp clean

-include $(DEPS)
