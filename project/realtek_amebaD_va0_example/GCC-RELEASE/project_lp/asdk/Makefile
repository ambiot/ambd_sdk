
#*****************************************************************************#
#                            Basic Configurations                             #
#*****************************************************************************#

ABS_ROOTDIR		= $(shell pwd)
MAKE_INCLUDE_GEN	= $(ABS_ROOTDIR)/Makefile.include.gen

CONFIG_SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
          else if [ -x /bin/bash ]; then echo /bin/bash; \
          else echo sh; fi ; fi)


CODE_ANALYZE_PYTHON=$(shell $(ABS_ROOTDIR)/code_analyze.py)
#ROM_SYMBOL_GEN_PYTHON=$(shell $(ABS_ROOTDIR)/export_rom_symbol.py)
ROM_SYMBOL_GEN_PYTHON= 

include $(MAKE_INCLUDE_GEN)

export ABS_ROOTDIR MAKE_INCLUDE_GEN HOSTCC


ifeq ($(COMPILEOS_CYGWIN),Cygwin)
HOSTNAME_APP = /usr/bin/hostname
PADTOOL      = $(UTILITYDIR)/imgpad.exe
LBITS := $(shell getconf LONG_BIT)
else
HOSTNAME_APP = $(which hostname)
PADTOOL      = $(UTILITYDIR)/imgpadl
endif


#.PHONY: all build_target_folder menuconfig clean

###############################################################################
#
# Lets work out what the user wants, and if they have configured us yet
#

RAM_OBJS_LIST = ./build/ram/*.o
ROM_OBJS_LIST = ./build/rom/*.o

LINK_ROM_LIB = $(ROOTDIR)/lib/rom_acut/rom.a

LINK_ROM_SYMBOL = ./ld/rlx8721d_rom_symbol_empty.ld
ifeq ($(CONFIG_LINK_ROM_SYMB),y) 
LINK_ROM_LIB =
LINK_ROM_SYMBOL = ./ld/rlx8721d_rom_symbol_acut.ld 
endif

ifeq ($(CONFIG_FT),y) 
#LINK_APP_LIB = $(ASDK_TOOLCHAIN)/lib/libm.a $(CMSISMATHLIBDIR)/libarm_cortexM3l_math.a
LINK_APP_LIB = $(ASDK_TOOLCHAIN)/arm-none-eabi/lib/v8-m.main/softfp/fpv5-sp-d16/libm.a $(CMSISMATHLIBDIR)/libarm_cortexM3l_math.a
else
LINK_APP_LIB =
endif

ROM_LD = $(ROOTDIR)/ld/rlx8721d_rom.ld

.PHONY: all build_target_folder menuconfig clean build_libraries package_prebuilt_rom_objs ucps_image2
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_application_lp.a


image2:LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_wifi_fw.a
ucps_image2:LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_wifi_ucps_fw.a


flashloader: build_target_folder copy_ld_img1 check_toolchain build_info.h make_subdirs_flashloader linker_loader gen_rom_symbol copy_flashloader
imgtool_flashloader: build_target_folder copy_ld_floader check_toolchain build_info.h make_subdirs_imgtool_flashloader linker_loader copy_imgtool_flashloader
rom: build_target_folder copy_ld_rom check_toolchain build_info.h make_subdirs_rom package_prebuilt_rom_objs rom_linker
all: build_target_folder copy_ld_ram check_toolchain build_info.h make_subdirs linker_image2 
image2: build_target_folder copy_ld_img2 check_toolchain build_info.h make_subdirs linker_image2 
ucps_image2: build_target_folder copy_ld_img2 check_toolchain build_info.h make_subdirs linker_image2 
bootloader: build_target_folder copy_ld_img1 check_toolchain build_info.h make_subdirs_bootloader linker_loader gen_rom_symbol
lib_all: build_target_folder copy_ld_img2 check_toolchain build_info.h make_subdirs_lib

#*****************************************************************************#
#                      RULES TO CREATE DIRECTORY                              #
#*****************************************************************************#

build_target_folder:
ifeq ($(COMPILEOS_CYGWIN),Cygwin)
ifneq ("$(LBITS)", "32")
	@echo ONLY 32-BIT CYGWIN IS SUPPORTED!
	@exit -1
endif
endif
	@if [ -d $(BUILD_TARGET_FOLDER) ]; then echo "$(BUILD_TARGET_FOLDER) exist"; else $(MKDIR) -p $(BUILD_TARGET_FOLDER); fi
	@if [ -d $(IMAGE_TARGET_FOLDER) ]; then echo "$(IMAGE_TARGET_FOLDER) exist"; else $(MKDIR) -p $(IMAGE_TARGET_FOLDER); fi
	@if [ -d $(BUILD_TARGET_RAM_FOLDER) ]; then echo "$(BUILD_TARGET_RAM_FOLDER) exist"; else $(MKDIR) $(BUILD_TARGET_RAM_FOLDER); fi
	@if [ -d $(BUILD_TARGET_ROM_FOLDER) ]; then echo "$(BUILD_TARGET_ROM_FOLDER) exist"; else $(MKDIR) $(BUILD_TARGET_ROM_FOLDER); fi


#*****************************************************************************#
#                      RULES TO MAKE SUB DIRS                                 #
#*****************************************************************************#
make_subdirs_flashloader:
	@ rm -f $(RAM_OBJS_LIST)
	@make -C make/flashloader all

make_subdirs_imgtool_flashloader:
	@ rm -f $(RAM_OBJS_LIST)
	@make -C $(ROOTDIR)/make/RT_xmodem all

make_subdirs_rom:
	@echo > $(ROOTDIR)/rom_size.txt
	@make -C make_rom all
	@$(MOVE) $(ROOTDIR)/rom_size.txt $(ROOTDIR)/lib/rom_acut

make_subdirs:
	@rm -f $(RAM_OBJS_LIST)
	@echo > $(ROOTDIR)/ram_size.txt
	@echo > $(ROOTDIR)/obj_list.txt
	@make -C make all
	@$(MOVE) $(ROOTDIR)/ram_size.txt $(IMAGE_TARGET_FOLDER)
	@$(MOVE) $(ROOTDIR)/obj_list.txt $(IMAGE_TARGET_FOLDER)

make_subdirs_bootloader:
	@make -C make/bootloader all

make_subdirs_lib:
	@ rm -f $(RAM_OBJS_LIST)
	@make -C make/target/wifi_fw all
	@make -C make/target/wifi_rcu_fw all
	@ rm -f $(RAM_OBJS_LIST)

#*****************************************************************************#
#                      RULES TO LINKER IMAGE                                  #
#*****************************************************************************#

linker_image2:
	@echo "========= linker img2 start ========="
	$(LD) $(LD_ARG) target_img2.axf $(RAM_OBJS_LIST) $(LINK_ROM_LIB) $(LINK_APP_LIB)

	$(MOVE) text.map $(IMAGE_TARGET_FOLDER)/text_image2.map
	$(MOVE) target_img2.axf $(IMAGE_TARGET_FOLDER)
	$(NM) $(IMAGE_TARGET_FOLDER)/target_img2.axf | sort > $(IMAGE_TARGET_FOLDER)/target_img2.map
	$(OBJDUMP) -d $(IMAGE_TARGET_FOLDER)/target_img2.axf > $(IMAGE_TARGET_FOLDER)/target_img2.asm
	#$(OBJDUMP) -h -S --disassemble-all $(IMAGE_TARGET_FOLDER)/target_img2.axf > $(IMAGE_TARGET_FOLDER)/target_img2.txt
	$(COPY) $(IMAGE_TARGET_FOLDER)/target_img2.axf $(IMAGE_TARGET_FOLDER)/target_pure_img2.axf
	$(STRIP) $(IMAGE_TARGET_FOLDER)/target_pure_img2.axf
	$(NM) $(IMAGE_TARGET_FOLDER)/target_pure_img2.axf | sort > $(IMAGE_TARGET_FOLDER)/target_pure_img2.map
	# $(FROMELF) -Obinary $(IMAGE_TARGET_FOLDER)/target_pure_img2.axf $(IMAGE_TARGET_FOLDER)/target_img2.bin


	$(FROMELF) -j .ram_image2.entry -j .ram_image2.text -j .ram_image2.data \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_img2.axf $(IMAGE_TARGET_FOLDER)/ram_2.bin

	$(FROMELF) -j .xip_image2.text \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_img2.axf $(IMAGE_TARGET_FOLDER)/xip_image2.bin

	$(FROMELF) -j .ram_retention.text -j .ram_retention.entry \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_img2.axf $(IMAGE_TARGET_FOLDER)/ram_retention.bin

	@echo "========== Image Info HEX =========="
	$(CC_SIZE) -A --radix=16 $(IMAGE_TARGET_FOLDER)/target_img2.axf
	$(CC_SIZE) -t --radix=16 $(IMAGE_TARGET_FOLDER)/target_img2.axf
	@echo "========== Image Info HEX =========="

	@echo "========== Image Info DEC =========="
	$(CC_SIZE) -A --radix=10 $(IMAGE_TARGET_FOLDER)/target_img2.axf
	$(CC_SIZE) -t --radix=10 $(IMAGE_TARGET_FOLDER)/target_img2.axf
	@echo "========== Image Info DEC =========="

	$(RM) -f $(RAM_OBJS_LIST)
	@echo "========== linker img2 end =========="

	@echo "========== Image manipulating start =========="
	$(PREPENDTOOL) $(IMAGE_TARGET_FOLDER)/ram_2.bin  __ram_image2_text_start__  $(IMAGE_TARGET_FOLDER)/target_img2.map
	$(PREPENDTOOL) $(IMAGE_TARGET_FOLDER)/xip_image2.bin  __flash_text_start__  $(IMAGE_TARGET_FOLDER)/target_img2.map
	$(PREPENDTOOL) $(IMAGE_TARGET_FOLDER)/ram_retention.bin  __retention_entry_func__  $(IMAGE_TARGET_FOLDER)/target_img2.map
	$(CODE_ANALYZE_PYTHON)

	cat $(IMAGE_TARGET_FOLDER)/xip_image2_prepend.bin $(IMAGE_TARGET_FOLDER)/ram_2_prepend.bin > $(IMAGE_TARGET_FOLDER)/km0_image2_all.bin
	$(UTILITYDIR)/pad.sh $(IMAGE_TARGET_FOLDER)/km0_image2_all.bin

	$(UTILITYDIR)/image_tool/imagetool.sh $(IMAGE_TARGET_FOLDER)/km0_image2_all.bin $(KM4_BUILDDIR)/asdk/image
	
	#@if [ -f $(IMAGE_TARGET_FOLDER)/km0_km4_image2.bin ]; then \
		#$(OTAPREPENDTOOL) $(IMAGE_TARGET_FOLDER)/km0_km4_image2.bin $(KM4_BUILDDIR)/asdk/image; \
	#fi

	@echo "========== Image manipulating end =========="

linker_loader:
	@echo "========= linker loader start ========="
	$(LD) $(LD_ARG) target_loader.axf $(RAM_OBJS_LIST) $(LINK_ROM_LIB) -Wl,--whole-archive -lbootloader_lp -Wl,--no-whole-archive 

	$(MOVE) text.map $(IMAGE_TARGET_FOLDER)/text_loader.map
	$(MOVE) target_loader.axf $(IMAGE_TARGET_FOLDER)
	$(NM) $(IMAGE_TARGET_FOLDER)/target_loader.axf | sort > $(IMAGE_TARGET_FOLDER)/target_loader.map
	$(OBJDUMP) -d $(IMAGE_TARGET_FOLDER)/target_loader.axf > $(IMAGE_TARGET_FOLDER)/target_loader.asm
	$(COPY) $(IMAGE_TARGET_FOLDER)/target_loader.axf $(IMAGE_TARGET_FOLDER)/target_pure_loader.axf
	$(STRIP) $(IMAGE_TARGET_FOLDER)/target_pure_loader.axf

	$(FROMELF) -j .ram_image1.entry  -j .ram_image1.text -j .ram_image1.data \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_loader.axf $(IMAGE_TARGET_FOLDER)/ram_1.bin

	$(FROMELF) -j .xip_image1.text \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_loader.axf $(IMAGE_TARGET_FOLDER)/xip_boot.bin

	@echo "========== Image Info HEX =========="
	$(CC_SIZE) -A --radix=16 $(IMAGE_TARGET_FOLDER)/target_loader.axf
	$(CC_SIZE) -t --radix=16 $(IMAGE_TARGET_FOLDER)/target_loader.axf
	@echo "========== Image Info HEX =========="

	@echo "========== Image Info DEC =========="
	$(CC_SIZE) -A --radix=10 $(IMAGE_TARGET_FOLDER)/target_loader.axf
	$(CC_SIZE) -t --radix=10 $(IMAGE_TARGET_FOLDER)/target_loader.axf
	@echo "========== Image Info DEC =========="

	$(RM) -f $(RAM_OBJS_LIST)
	@echo "========== linker end =========="

	@echo "========== Image manipulating start =========="
	$(PREPENDTOOL) $(IMAGE_TARGET_FOLDER)/ram_1.bin  __ram_start_table_start__  $(IMAGE_TARGET_FOLDER)/target_loader.map
	$(PREPENDTOOL) $(IMAGE_TARGET_FOLDER)/xip_boot.bin  __flash_boot_text_start__  $(IMAGE_TARGET_FOLDER)/target_loader.map
	$(CODE_ANALYZE_PYTHON)

	cat $(IMAGE_TARGET_FOLDER)/xip_boot_prepend.bin $(IMAGE_TARGET_FOLDER)/ram_1_prepend.bin > $(IMAGE_TARGET_FOLDER)/km0_boot_all.bin

	$(UTILITYDIR)/image_tool/imagetool.sh $(IMAGE_TARGET_FOLDER)/km0_boot_all.bin

	@echo "========== Image manipulating end =========="

#*****************************************************************************#
#                      RULES TO SET MENUCONFIG                                #
#*****************************************************************************#

menuconfig:

	cp -f $(CONFIGDIR)/config.in $(CONFIGDIR)/config.in.old
ifeq ($(COMPILEOS_CYGWIN),Cygwin)
	@cp $(LXDIALOG_CYGWIN_STATIC) $(SCRIPTSDIR)/lxdialog/lxdialog.exe
else
	$(MAKE) -C $(SCRIPTSDIR)/lxdialog clean all
endif
	$(CONFIG_SHELL) $(SCRIPTSDIR)/Menuconfig $(CONFIGDIR)/config.in
	@if [ ! -f  $(CONFIGDIR)/.config ]; then \
		echo; \
		echo "You have not saved your config, please re-run make config"; \
		echo; \
		exit 1; \
	fi
	cp -f $(CONFIGDIR)/autoconf.h $(INCDIR)/platform_autoconf.h
	rm -f $(CONFIGDIR)/autoconf.h


#*****************************************************************************#
#                      RULES TO BUILD COMPILER TIME                           #
#*****************************************************************************#

build_info.h:
	@echo \#define UTS_VERSION \"`date +%Y/%m/%d-%T`\" > .ver
	@echo \#define RTL_FW_COMPILE_TIME \"`date +%Y/%m/%d-%T`\" >> .ver
	@echo \#define RTL_FW_COMPILE_DATE \"`date +%Y/%m/%d`\" >> .ver
	@echo \#define RTL_FW_COMPILE_BY \"`id -u -n`\" >> .ver
	@echo \#define RTL_FW_COMPILE_HOST \"`$(HOSTNAME_APP)`\" >> .ver
	@if [ -x /bin/dnsdomainname ]; then \
		echo \#define RTL_FW_COMPILE_DOMAIN \"`dnsdomainname`\"; \
	elif [ -x /bin/domainname ]; then \
		echo \#define RTL_FW_COMPILE_DOMAIN \"`domainname`\"; \
	else \
		echo \#define RTL_FW_COMPILE_DOMAIN ; \
	fi >> .ver
ifeq ($(CONFIG_TOOLCHAIN_ARM_GCC), y)
	@echo \#define RTL_FW_COMPILER \"ARM_GCC\" >> .ver
else
	@echo \#define RTL_FW_COMPILER \"`$(CC) $(CFLAGS) -v 2>&1 | tail -1`\" >> .ver
endif
	@mv -f .ver $(INCDIR)/$@


#*****************************************************************************#
#                      RULES TO CHECK TOOLCHAIN                               #
#*****************************************************************************#

check_toolchain:
	@if [ -d $(ASDK_TOOLCHAIN) ]; \
		then echo "ToolChain Had Existed"; \
		else echo "Extract toolchain"; \
			make -C $(TOOLCHAINDIR) all; fi

#*****************************************************************************#
#                      RULES TO ENTER GDB                                     #
#*****************************************************************************#

gdb_prepare:
ifeq ($(COMPILEOS_CYGWIN),Cygwin)
	$(GNU_SCRIPT)/Check_Jtag.sh $(GNU_SCRIPT)
endif
	@if [ ! -d $(IMAGE_TARGET_FOLDER) ]; \
		then echo "$(IMAGE_TARGET_FOLDER) no exist"; fi
	@if [ -f  $(GNU_SCRIPT)/.bin ]; \
		then	$(REMOVE) $(GNU_SCRIPT)/*.bin; fi

gdb: gdb_prepare
	$(COPY) $(GNU_SCRIPT)/acut_loader/*  $(GNU_SCRIPT)/

	$(GNU_SCRIPT)/SetupGDB_FPGA.sh $(GNU_SCRIPT)
	$(GDB) -x $(GNU_SCRIPT)/rtl_gdb_flash_write.txt
	

gdbboot: gdb_prepare
	$(GDB) -x $(GNU_SCRIPT)/rtl_gdb_jtag_boot.txt

gdbbootxip: gdb_prepare
	$(GDB) -x $(GNU_SCRIPT)/rtl_gdb_jtag_boot_xip.txt

gdbloadrom: gdb_prepare
	$(GDB) -x $(GNU_SCRIPT)/rtl_gdb_jtag_load_rom.txt

swdpwd:
	$(GDB) -x $(GNU_SCRIPT)/rtl_gdb_jtag_pwd.txt

#*****************************************************************************#
#                      RULES TO SET DOWNLOAD AND DEBUG                        #
#*****************************************************************************#
.PHONY: debug setup
setup:
	@echo "----------------"
	@echo Setup $(GDB_SERVER)
	@echo "----------------"
ifeq ($(GDB_SERVER), probe)
	cp -p $(GNU_SCRIPT)/rtl_gdb_debug_probe.txt $(GNU_SCRIPT)/rtl_gdb_debug.txt
	cp -p $(GNU_SCRIPT)/rtl_gdb_flash_write_probe.txt $(GNU_SCRIPT)/rtl_gdb_flash_write.txt
	cp -p $(GNU_SCRIPT)/rtl_gdb_jtag_boot_com_probe.txt $(GNU_SCRIPT)/rtl_gdb_jtag_boot_com.txt
else
	cp -p $(GNU_SCRIPT)/rtl_gdb_debug_jlink.txt $(GNU_SCRIPT)/rtl_gdb_debug.txt
	cp -p $(GNU_SCRIPT)/rtl_gdb_flash_write_jlink.txt $(GNU_SCRIPT)/rtl_gdb_flash_write.txt
	cp -p $(GNU_SCRIPT)/rtl_gdb_jtag_boot_com_jlink.txt $(GNU_SCRIPT)/rtl_gdb_jtag_boot_com.txt
endif

debug:
	@if [ ! -f $(GNU_SCRIPT)/rtl_gdb_debug.txt ] ; then echo Please do \"make setup GDB_SERVER=[jlink or openocd]\" first; echo && false ; fi
ifeq ($(COMPILEOS_CYGWIN),Cygwin)
	$(GNU_SCRIPT)/Check_Jtag.sh
	cmd /c start $(GDBR) -x $(GNU_SCRIPT)/rtl_gdb_debug.txt
else
	$(GDB) -x $(GNU_SCRIPT)/rtl_gdb_debug.txt
endif

#*****************************************************************************#
#                      RULES TO CLEAN                                         #
#*****************************************************************************#

clean:
	@if [ -d $(BUILD_TARGET_FOLDER) ]; \
		then $(REMOVEDIR) $(BUILD_TARGET_FOLDER)/*;\
			echo "====== Remove $(BUILD_TARGET_FOLDER)/* Success ======";\
		else echo "$(BUILD_TARGET_FOLDER) no exist"; fi
	@if [ -d $(IMAGE_TARGET_FOLDER) ]; \
		then $(REMOVEDIR) $(IMAGE_TARGET_FOLDER)/*; \
			echo "====== Remove $(IMAGE_TARGET_FOLDER) Success ======";\
		else echo "$(IMAGE_TARGET_FOLDER) no exist"; fi

	@make -C make clean
	# make -C config clean
	make -C $(SCRIPTSDIR)/lxdialog clean

	#flashloader code start
	make -C make/flashloader clean

	make -C $(TARGETDIR)/imgtool_floader clean

clean_rom:
	@make -C make_rom clean

clean_all: clean
	@if [ $(COMPILEOS) = $(LINUX_OS) ]; \
		then $(REMOVEDIR) $(TOOLCHAINDIR)/linux; \
		else $(REMOVEDIR) $(TOOLCHAINDIR)/cygwin; fi

#*****************************************************************************#
#              PACKAGE PREBUILT ROM OBJECT LIBRARIES                          #
#*****************************************************************************#

############### add ROM OBJS here		

package_prebuilt_rom_objs:

	@if [ -d $(BUILD_TARGET_ROM_FOLDER) ]; then \
		$(CD) $(BUILD_TARGET_ROM_FOLDER); \
		rm -f rom.a; \
		$(AR) crv rom.a $(HWLIB_ROM_OBJS) $(MONI_ROM_OBJS) $(SWLIB_ROM_OBJS) $(VECTOR_ROM_OBJS) $(XMODEM_ROM_OBJS) $(FW_ROM_OBJS); \
		mkdir -p $(ROOTDIR)/lib/rom_acut; \
		$(MOVE) -f rom.a $(ROOTDIR)/lib/rom_acut; \
	else @echo $(BUILD_TARGET_ROM_FOLDER): No such directory; fi

rom_linker:
	#${LD} -r -d -T$(ROOTDIR)/ld/rlx8721d_rom.ld --verbose $(ROM_LD_ARG) $(ROM_OBJS_LIST) -o rom.o  
	${LD_ROM} -r -d -T $(ROM_LD) --verbose --warn-common -Map=rom.map $(ROM_OBJS_LIST) -o rom.o  
	${AR} crv rom.a rom.o
	${READELF} -S rom.o
	$(MOVE) -f rom.o $(ROOTDIR)/lib/rom_acut
	$(MOVE) -f rom.a $(ROOTDIR)/lib/rom_acut
	$(MOVE) -f rom.map $(ROOTDIR)/lib/rom_acut

	@echo "========= linker rom start ========="
	$(LD) $(LD_ARG) target_rom.axf $(LINK_ROM_LIB)

	$(MOVE) text.map $(IMAGE_TARGET_FOLDER)/text_rom.map
	$(MOVE) target_rom.axf $(IMAGE_TARGET_FOLDER)
	$(NM) $(IMAGE_TARGET_FOLDER)/target_rom.axf | sort > $(IMAGE_TARGET_FOLDER)/target_rom.map
	$(OBJDUMP) -d $(IMAGE_TARGET_FOLDER)/target_rom.axf > $(IMAGE_TARGET_FOLDER)/target_rom.asm
	#$(OBJDUMP) -h -S --disassemble-all $(IMAGE_TARGET_FOLDER)/target_rom.axf > $(IMAGE_TARGET_FOLDER)/target_rom.txt
	$(COPY) $(IMAGE_TARGET_FOLDER)/target_rom.axf $(IMAGE_TARGET_FOLDER)/target_pure_rom.axf
	$(STRIP) $(IMAGE_TARGET_FOLDER)/target_pure_rom.axf
	$(NM) $(IMAGE_TARGET_FOLDER)/target_pure_rom.axf | sort > $(IMAGE_TARGET_FOLDER)/target_pure_rom.map

	$(FROMELF) -j .rom.text -j .rom.text.libgcc \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_rom.axf $(IMAGE_TARGET_FOLDER)/km0_irom.bin
	$(FROMELF) -j .rom.rodata \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_rom.axf $(IMAGE_TARGET_FOLDER)/km0_drom.bin

	@echo "========== Image Info HEX =========="
	$(CC_SIZE) -A --radix=16 $(IMAGE_TARGET_FOLDER)/target_rom.axf
	$(CC_SIZE) -t --radix=16 $(IMAGE_TARGET_FOLDER)/target_rom.axf
	@echo "========== Image Info HEX =========="

	@echo "========== Image Info DEC =========="
	$(CC_SIZE) -A --radix=10 $(IMAGE_TARGET_FOLDER)/target_rom.axf
	$(CC_SIZE) -t --radix=10 $(IMAGE_TARGET_FOLDER)/target_rom.axf
	@echo "========== Image Info DEC =========="

	$(RM) -f $(RAM_OBJS_LIST)
	@echo "========== linker rom end =========="

gen_rom_symbol:
	@echo "AMEBAD_TODO"
	#@echo "gen rom_symbol.txt ..."
	#$(REMOVE) $(ROOTDIR)/lib/rom_symbol.txt
	#$(ROM_SYMBOL_GEN_PYTHON) 
	#$(MOVE) -f rom_symbol.txt $(ROOTDIR)/lib/

copy_rom:
	@$(COPY) $(IMAGE_TARGET_FOLDER)/*rom* $(ROOTDIR)/lib/rom_acut

#*****************************************************************************#
#              PACKAGE COPY link script file-ld                               #
#*****************************************************************************#
copy_ld_ram:
	$(COPY) $(ROOTDIR)/ld/rlx8721d_ram.ld $(BUILD_TARGET_FOLDER)/rlx8721d.ld
	cat $(LINK_ROM_SYMBOL) >> $(BUILD_TARGET_FOLDER)/rlx8721d.ld
copy_ld_img1:
	$(COPY) $(ROOTDIR)/ld/rlx8721d_boot.ld $(BUILD_TARGET_FOLDER)/rlx8721d.ld
	cat $(LINK_ROM_SYMBOL) >> $(BUILD_TARGET_FOLDER)/rlx8721d.ld
copy_ld_img2:
	$(COPY) $(ROOTDIR)/ld/rlx8721d_img2.ld  $(BUILD_TARGET_FOLDER)/rlx8721d.ld
	cat $(LINK_ROM_SYMBOL) >> $(BUILD_TARGET_FOLDER)/rlx8721d.ld
copy_ld_rom:
	$(COPY) $(ROOTDIR)/ld/rlx8721d_rom_bin.ld  $(BUILD_TARGET_FOLDER)/rlx8721d.ld
copy_ld_floader:
	$(COPY) $(ROOTDIR)/ld/rlx8721d_boot.ld $(BUILD_TARGET_FOLDER)/rlx8721d.ld
ifeq ($(CONFIG_LINK_ROM_SYMB),y)
	cat ./ld/rlx8721d_rom_symbol.ld >> $(BUILD_TARGET_FOLDER)/rlx8721d.ld
endif

#*****************************************************************************#
#              COPY flashloader into flashdownload folder                     #
#*****************************************************************************#
copy_flashloader:

	$(COPY) -f $(IMAGE_TARGET_FOLDER)/target_loader.axf $(GNU_SCRIPT)/acut_loader/target_FPGA.axf
	$(COPY) -f $(IMAGE_TARGET_FOLDER)/ram_1.bin $(GNU_SCRIPT)/acut_loader/flash_loader_ram_1.bin

copy_imgtool_flashloader:

	$(COPY) -f $(IMAGE_TARGET_FOLDER)/target_loader.axf $(TARGETDIR)/imgtool_floader/image/target_FPGA.axf
	$(COPY) -f $(IMAGE_TARGET_FOLDER)/ram_1.bin $(TARGETDIR)/imgtool_floader/image/imgtool_flashloader_amebad.bin
