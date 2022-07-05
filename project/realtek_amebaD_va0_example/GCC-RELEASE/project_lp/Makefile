include ./asdk/config/.config

.PHONY: all clean flash debug setup

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = 

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS
#	make -C asdk flashloader
	make -C asdk bootloader
ifeq ($(CONFIG_USER_CTRL_PS),y)
	make -C asdk ucps_image2
else
	make -C asdk image2
endif
	
rom2: CORE_TARGETS
	make -C asdk rom2

setup:
	make -C asdk $(MAKECMDGOALS)

flash:
	make -C asdk gdb

debug:
	make -C asdk debug
	
xip: CORE_TARGETS
	make -C asdk lib_all
#	make -C asdk flashloader
	make -C asdk bootloader
ifeq ($(CONFIG_USER_CTRL_PS),y)
	make -C asdk ucps_image2
else
	make -C asdk image2
endif

rom_debug_if_need: CORE_TARGETS
	make -C asdk rom
	make -C asdk copy_rom

imgtool_flashloader:
	make -C asdk imgtool_flashloader

clean: CORE_TARGETS
	make -C asdk clean

clean_all: CORE_TARGETS
	#make -C asdk clean_rom
	make -C asdk clean_all

menuconfig: CORE_TARGETS
	make -C asdk menuconfig

gdb: CORE_TARGETS
	make -C asdk gdb #step2: load flash if need
	#please use tools\AmebaZ\Image Tool!!!!!!!!!!!!!!!!!!
	#user guide: WS_20160928_WLAN5_AmebaZ_Image_Tool_User_Guide_1v0

gdbloadrom: CORE_TARGETS
	make -C asdk gdbloadrom #step1: load rom if need

swdpwd: CORE_TARGETS
	make -C asdk swdpwd

#image2: CORE_TARGETS
#	make -C asdk image2
#
#bootloader: CORE_TARGETS
#	make -C asdk bootloader
#
#flashloader:
#	make -C asdk flashloader
#
#
#gdbboot: CORE_TARGETS
#	make -C asdk gdbboot #boot from RAM
#
#gdbbootxip: CORE_TARGETS
#	make -C asdk gdbbootxip #step3: boot from flash
#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

