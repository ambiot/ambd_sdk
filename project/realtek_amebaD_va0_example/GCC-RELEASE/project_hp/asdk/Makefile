
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
#ROM_SYMBOL_S_GEN_PYTHON=$(shell $(ABS_ROOTDIR)/export_rom_symbol_s.py)
ROM_SYMBOL_GEN_PYTHON= 
ROM_SYMBOL_S_GEN_PYTHON= 

BUILD_TYPE = NONE
mp_image2_ns:BUILD_TYPE = MFG
mp_image3_s:BUILD_TYPE = MFG
export BUILD_TYPE

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
ROM_OBJS_LIST_NS = ./build/rom_ns/*.o

LINK_ROM_LIB = $(ROOTDIR)/lib/rom_acut/rom.a
LINK_ROM_LIB_NS = $(ROOTDIR)/lib/rom_acut/rom_ns.a

LINK_ROM_SYMBOL_NS = ./ld/rlx8721d_rom_symbol_empty.ld
LINK_ROM_SYMBOL_S = ./ld/rlx8721d_rom_symbol_empty.ld
LINK_ROM_SYMBOL_BOOT = ./ld/rlx8721d_rom_symbol_empty.ld
ifeq ($(CONFIG_LINK_ROM_SYMB),y) 
LINK_ROM_LIB =
LINK_ROM_LIB_NS =
LINK_ROM_SYMBOL_NS = ./ld/rlx8721d_rom_symbol_acut.ld
LINK_ROM_SYMBOL_S = ./ld/rlx8721d_rom_symbol_acut_s.ld
LINK_ROM_SYMBOL_BOOT = ./ld/rlx8721d_rom_symbol_acut_boot.ld
endif

ifeq ($(CONFIG_FT),y) 
LINK_APP_LIB = $(ASDK_TOOLCHAIN)/arm-none-eabi/lib/v8-m.main/fpu/fpv5-sp-d16/libm.a $(CMSISMATHLIBDIR)/libarm_cortexM3l_math.a
else
LINK_APP_LIB =
endif

ifeq ($(CONFIG_AUDIO_EN),y)
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_ac3.a
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_amr.a
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_haac.a
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_hls.a
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_hmp3.a
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_m4a.a
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_m4a_self.a
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_mp3.a
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_flac.a
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_ekho.a
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_gsm610.a
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_libogg.a
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_opusfile.a
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_opus.a
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_opusenc.a
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_resample.a
endif

ifeq ($(CONFIG_BT_EN), y) 
LINK_APP_LIB += $(BASEDIR)/component/common/bluetooth/realtek/sdk/board/amebad/lib/btgap.a
ifeq ($(findstring y, $(CONFIG_BT_MESH_PROVISIONER) $(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE)), y)
LINK_APP_LIB += $(BASEDIR)/component/common/bluetooth/realtek/sdk/example/bt_mesh/lib/lib/amebad/btmesh_prov.a
else ifeq ($(findstring y, $(CONFIG_BT_MESH_DEVICE) $(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE)), y)
LINK_APP_LIB += $(BASEDIR)/component/common/bluetooth/realtek/sdk/example/bt_mesh/lib/lib/amebad/btmesh_dev.a
endif
endif

# MMF LIBRARY
ifeq ($(CONFIG_MMF_EN), y) 
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_mmfv2.a
endif
ifeq ($(CONFIG_RTSP_EN), y) 
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_rtsp.a
endif
ifeq ($(CONFIG_MMF_EN), y) 
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_mmfv2.a
endif
ifeq ($(CONFIG_RTP_CODEC_EN), y) 
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_rtp_codec.a
endif
# LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_g711.a
# LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_speex.a
# LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_haac.a
# LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_faac.a
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_cmsis_dsp.a
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_application_hp.a


ifeq ($(CONFIG_TRUSTZONE), y)
LINK_APP_LIB += $(IMAGE_TARGET_FOLDER)/cmse_implib.lib
endif

.PHONY: all build_target_folder menuconfig clean build_libraries package_prebuilt_rom_objs mp_image2_ns 


ifeq ($(CONFIG_WIFI_EN), y)
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_httpc.a
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_httpd.a
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_mdns.a
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_websocket.a
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_tftp.a
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_dct.a
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_coap.a
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_eap.a
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_http2.a
#LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_rt_airkiss_algo.a
#LINK_APP_LIB += $(BASEDIR)/component/common/application/airkiss/2.0.0-26515/lib/libairkiss.a

image2_ns:LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_wlan.a $(ROOTDIR)/lib/application/lib_wps.a 
mp_image2_ns:LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_wlan_mp.a $(ROOTDIR)/lib/application/lib_wps.a
endif

ifeq ($(CONFIG_LINKKIT_AWSS), y)
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_aliiot.a
endif

ifeq ($(findstring y, $(CONFIG_USB_HOST_EN) $(CONFIG_USBH_VERIFY)), y)
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_usbh.a
endif
ifeq ($(findstring y, $(CONFIG_USB_DEVICE_EN) $(CONFIG_USBD_VERIFY)), y)
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_usbd.a
endif
ifeq ($(CONFIG_V4L2_EN),y)
LINK_APP_LIB += $(ROOTDIR)/lib/application/lib_v4l2.a
endif

ifeq ($(CONFIG_EMWIN_EN),y)
LINK_APP_LIB += $(BASEDIR)/component/common/ui/emwin/emWinLibrary/lib/rtl8721d/lib_emwin.a
endif

rom: build_target_folder copy_ld_rom check_toolchain build_info.h make_subdirs_rom package_prebuilt_rom_objs rom_linker 
rom_ns: build_target_folder copy_ld_rom_ns check_toolchain build_info.h make_subdirs_rom_ns package_prebuilt_rom_objs rom_linker_ns 
image2_ns: build_target_folder copy_ld_img2 check_toolchain build_info.h make_subdirs linker_image2_ns 
mp_image2_ns:build_target_folder copy_ld_img2 check_toolchain build_info.h make_subdirs linker_image2_ns 
image3_s: build_target_folder copy_ld_img3 check_toolchain build_info.h make_subdirs_secure linker_image3 
mp_image3_s: build_target_folder copy_ld_img3 check_toolchain build_info.h make_subdirs_secure linker_image3
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
	@if [ -d $(BUILD_TARGET_ROM_FOLDER_NS) ]; then echo "$(BUILD_TARGET_ROM_FOLDER_NS) exist"; else $(MKDIR) $(BUILD_TARGET_ROM_FOLDER_NS); fi
	@$(ROM_SYMBOL_GEN_PYTHON) 
	@$(ROM_SYMBOL_S_GEN_PYTHON) 


#*****************************************************************************#
#                      RULES TO MAKE SUB DIRS                                 #
#*****************************************************************************#
make_subdirs_rom:
	@echo > $(ROOTDIR)/rom_size.txt
	@make -C make_rom/make all
	@$(MOVE) $(ROOTDIR)/rom_size.txt $(ROOTDIR)/lib/rom_acut/rom_size_s.txt
make_subdirs_rom_ns:
	@echo > $(ROOTDIR)/rom_size.txt
	@make -C make_rom/make_ns all
	@$(MOVE) $(ROOTDIR)/rom_size.txt $(ROOTDIR)/lib/rom_acut/rom_size_ns.txt

make_subdirs:
	@ rm -f $(RAM_OBJS_LIST)
	@echo > $(ROOTDIR)/ram_size.txt
	@echo > $(ROOTDIR)/obj_list.txt
	@make -C make all
	@$(MOVE) $(ROOTDIR)/ram_size.txt $(IMAGE_TARGET_FOLDER)
	@$(MOVE) $(ROOTDIR)/obj_list.txt $(IMAGE_TARGET_FOLDER)

make_subdirs_secure:
	@ rm -f $(RAM_OBJS_LIST)
	@echo > $(ROOTDIR)/ram_size.txt
	@echo > $(ROOTDIR)/obj_list.txt
	@make -C make_secure all
	@$(MOVE) $(ROOTDIR)/ram_size.txt $(IMAGE_TARGET_FOLDER)
	@$(MOVE) $(ROOTDIR)/obj_list.txt $(IMAGE_TARGET_FOLDER)

make_subdirs_bootloader:
	@ rm -f $(RAM_OBJS_LIST)
	@make -C make/bootloader all

make_subdirs_lib:
	@ rm -f $(RAM_OBJS_LIST)
	@make -C make/wlan lib
	#@make -C make/wlan clean
	#@make -C make/wlan lib_mp
	#@make -C make/wlan clean
	#@make -C make/wlan lib_lp	
	@make -C make/cmsis-dsp all
	@make -C make/wps all
	@make -C make/network/httpc all
	@make -C make/network/httpd all
	@make -C make/network/websocket all
	#@make -C make/network/http2 all
	@make -C make/network/eap all
	@make -C make/network/tftp all
	@make -C make/file_system/dct all
	#@make -C make/network/libcoap all
#	MMF LIBRARY
# 	@make -C make/audio/g711 all
# 	@make -C make/audio/faac all
# 	@make -C make/audio/haac all
#	@make -C make/audio/speex all
	@make -C make/media/rtp_codec all
#	@make -C make/network/rtsp all
	@make -C make/media/mmfv2 all
	@make -C make/video/v4l2 all
#	@make -C make/target/usb_otg/device/lib all
#	@make -C make/target/usb_otg/host/lib all
#	@make -C make/ui/emwin/emWinLibrary/GUI lib

#*****************************************************************************#
#                      RULES TO LINKER IMAGE                                  #
#*****************************************************************************#

linker_image3:
ifeq ($(CONFIG_TRUSTZONE), y)
	@echo "========= linker img3 secure start ========="
	$(LD) $(LD_SEC_OUT_ARG) $(LD_ARG) target_img3.axf $(LINK_ROM_LIB) $(RAM_OBJS_LIST)

	$(MOVE) cmse_implib.lib $(IMAGE_TARGET_FOLDER)/cmse_implib.lib
	$(MOVE) text.map $(IMAGE_TARGET_FOLDER)/text_image3.map
	$(MOVE) target_img3.axf $(IMAGE_TARGET_FOLDER)
	$(NM) $(IMAGE_TARGET_FOLDER)/target_img3.axf | sort > $(IMAGE_TARGET_FOLDER)/target_img3.map
	$(OBJDUMP) -d $(IMAGE_TARGET_FOLDER)/target_img3.axf > $(IMAGE_TARGET_FOLDER)/target_img3.asm
	$(COPY) $(IMAGE_TARGET_FOLDER)/target_img3.axf $(IMAGE_TARGET_FOLDER)/target_pure_img3.axf
	$(STRIP) $(IMAGE_TARGET_FOLDER)/target_pure_img3.axf
	$(NM) $(IMAGE_TARGET_FOLDER)/target_pure.axf | sort > $(IMAGE_TARGET_FOLDER)/target_pure_img3.map

	##secure
	$(READELF) -s $(IMAGE_TARGET_FOLDER)/cmse_implib.lib > $(IMAGE_TARGET_FOLDER)/cmse_implib.txt
	$(OBJDUMP) -j .gnu.sgstubs -d $(IMAGE_TARGET_FOLDER)/target_img3.axf > $(IMAGE_TARGET_FOLDER)/cmse_implib.asm


	$(FROMELF) -j .ram_image3.text -j .ram_image3.data \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_img3.axf $(IMAGE_TARGET_FOLDER)/ram_3_s.bin

	$(FROMELF) -j .gnu.sgstubs \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_img3.axf $(IMAGE_TARGET_FOLDER)/ram_3_nsc.bin

	$(FROMELF) -j .psram_image3.text -j .psram_image3.data \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_img3.axf $(IMAGE_TARGET_FOLDER)/psram_3_s.bin

	@echo "========== Image Info HEX =========="
	$(CC_SIZE) -A --radix=16 $(IMAGE_TARGET_FOLDER)/target_img3.axf
	$(CC_SIZE) -t --radix=16 $(IMAGE_TARGET_FOLDER)/target_img3.axf
	@echo "========== Image Info HEX =========="

	@echo "========== Image Info DEC =========="
	$(CC_SIZE) -A --radix=10 $(IMAGE_TARGET_FOLDER)/target_img3.axf
	$(CC_SIZE) -t --radix=10 $(IMAGE_TARGET_FOLDER)/target_img3.axf
	@echo "========== Image Info DEC =========="

	$(RM) -f $(RAM_OBJS_LIST)
	@echo "========== linker img3 secure end =========="

	@echo "========== Image manipulating start =========="
	$(PREPENDTOOL) $(IMAGE_TARGET_FOLDER)/ram_3_s.bin  __ram_image3_text_start__  $(IMAGE_TARGET_FOLDER)/target_img3.map
	$(PREPENDTOOL) $(IMAGE_TARGET_FOLDER)/ram_3_nsc.bin  __ram_image3_nsc_start__  $(IMAGE_TARGET_FOLDER)/target_img3.map
	$(PREPENDTOOL) $(IMAGE_TARGET_FOLDER)/psram_3_s.bin  __psram_image3_text_start__  $(IMAGE_TARGET_FOLDER)/target_img3.map
	$(CODE_ANALYZE_PYTHON)

	cat $(IMAGE_TARGET_FOLDER)/ram_3_s_prepend.bin $(IMAGE_TARGET_FOLDER)/ram_3_nsc_prepend.bin > $(IMAGE_TARGET_FOLDER)/km4_image3_all.bin
	cat $(IMAGE_TARGET_FOLDER)/psram_3_s_prepend.bin > $(IMAGE_TARGET_FOLDER)/km4_image3_psram.bin

	$(UTILITYDIR)/image_tool/imagetool.sh $(IMAGE_TARGET_FOLDER)/km4_image3_all.bin
	$(UTILITYDIR)/image_tool/imagetool.sh $(IMAGE_TARGET_FOLDER)/km4_image3_psram.bin

	@echo "========== Image manipulating end =========="
endif
linker_image2:
	@echo "========= linker img2 start ========="
	$(LD) $(LD_ARG) target.axf $(RAM_OBJS_LIST) $(LINK_ROM_LIB) $(LINK_APP_LIB)

	$(MOVE) text.map $(IMAGE_TARGET_FOLDER)/text_image2.map
	$(MOVE) target.axf $(IMAGE_TARGET_FOLDER)
	$(NM) $(IMAGE_TARGET_FOLDER)/target.axf | sort > $(IMAGE_TARGET_FOLDER)/target.map
	$(OBJDUMP) -d $(IMAGE_TARGET_FOLDER)/target.axf > $(IMAGE_TARGET_FOLDER)/target.asm
	$(COPY) $(IMAGE_TARGET_FOLDER)/target.axf $(IMAGE_TARGET_FOLDER)/target_pure.axf
	$(STRIP) $(IMAGE_TARGET_FOLDER)/target_pure.axf
	$(NM) $(IMAGE_TARGET_FOLDER)/target_pure.axf | sort > $(IMAGE_TARGET_FOLDER)/target_pure.map


	$(FROMELF) -j .ram_image2.entry -j .ram_image2.text -j .ram_image2.data \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure.axf $(IMAGE_TARGET_FOLDER)/ram_2.bin

	$(FROMELF) -j .xip_image2.text \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure.axf $(IMAGE_TARGET_FOLDER)/xip_image2.bin

	@echo "========== Image Info HEX =========="
	$(CC_SIZE) -A --radix=16 $(IMAGE_TARGET_FOLDER)/target.axf
	$(CC_SIZE) -t --radix=16 $(IMAGE_TARGET_FOLDER)/target.axf
	@echo "========== Image Info HEX =========="

	@echo "========== Image Info DEC =========="
	$(CC_SIZE) -A --radix=10 $(IMAGE_TARGET_FOLDER)/target.axf
	$(CC_SIZE) -t --radix=10 $(IMAGE_TARGET_FOLDER)/target.axf
	@echo "========== Image Info DEC =========="

	$(RM) -f $(RAM_OBJS_LIST)
	@echo "========== linker img2 end =========="

	@echo "========== Image manipulating start =========="
	$(PREPENDTOOL) $(IMAGE_TARGET_FOLDER)/ram_2.bin  __ram_image2_text_start__  $(IMAGE_TARGET_FOLDER)/target.map
	$(PREPENDTOOL) $(IMAGE_TARGET_FOLDER)/xip_image2.bin  __flash_text_start__  $(IMAGE_TARGET_FOLDER)/target.map
	$(CODE_ANALYZE_PYTHON)

	cat $(IMAGE_TARGET_FOLDER)/xip_image2_prepend.bin $(IMAGE_TARGET_FOLDER)/ram_2_prepend.bin > $(IMAGE_TARGET_FOLDER)/km4_image2_all.bin
	@echo "========== Image manipulating end =========="

linker_image2_ns:
	@echo "========= linker img2_ns start ========="
	$(LD) $(LD_ARG) target_img2.axf $(RAM_OBJS_LIST) $(LINK_ROM_LIB_NS) $(LINK_APP_LIB)  -lm -lstdc++

	$(MOVE) text.map $(IMAGE_TARGET_FOLDER)/text_image2_ns.map
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

	$(FROMELF) -j .psram_image2.text -j .psram_image2.data \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_img2.axf $(IMAGE_TARGET_FOLDER)/psram_2.bin	

	# for Bluetooth trace
ifeq ($(CONFIG_BT_EN), y) 
	$(FROMELF) -j .bluetooth_trace.text \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_img2.axf $(IMAGE_TARGET_FOLDER)/APP.trace
	 $(COPY) $(IMAGE_TARGET_FOLDER)/APP.trace $(BASEDIR)/tools/bluetooth/DebugAnalyzer/APP.trace
	 $(COPY) -f $(IMAGE_TARGET_FOLDER)/APP.trace $(BASEDIR)/tools/bluetooth/DebugAnalyzer/"APP_`date +%Y%m%d_%H%M%S`".trace
endif

	@echo "========== Image Info HEX =========="
	$(CC_SIZE) -A --radix=16 $(IMAGE_TARGET_FOLDER)/target_img2.axf
	$(CC_SIZE) -t --radix=16 $(IMAGE_TARGET_FOLDER)/target_img2.axf
	@echo "========== Image Info HEX =========="

	@echo "========== Image Info DEC =========="
	$(CC_SIZE) -A --radix=10 $(IMAGE_TARGET_FOLDER)/target_img2.axf
	$(CC_SIZE) -t --radix=10 $(IMAGE_TARGET_FOLDER)/target_img2.axf
	@echo "========== Image Info DEC =========="
	
	$(RM) -f $(RAM_OBJS_LIST)
	@echo "========== linker img2_ns end =========="

	@echo "========== Image manipulating start =========="
	$(PREPENDTOOL) $(IMAGE_TARGET_FOLDER)/ram_2.bin  __ram_image2_text_start__  $(IMAGE_TARGET_FOLDER)/target_img2.map
	$(PREPENDTOOL) $(IMAGE_TARGET_FOLDER)/xip_image2.bin  __flash_text_start__  $(IMAGE_TARGET_FOLDER)/target_img2.map
	$(PREPENDTOOL) $(IMAGE_TARGET_FOLDER)/psram_2.bin  __psram_image2_text_start__  $(IMAGE_TARGET_FOLDER)/target_img2.map
	$(CODE_ANALYZE_PYTHON)

	cat $(IMAGE_TARGET_FOLDER)/xip_image2_prepend.bin $(IMAGE_TARGET_FOLDER)/ram_2_prepend.bin $(IMAGE_TARGET_FOLDER)/psram_2_prepend.bin  > $(IMAGE_TARGET_FOLDER)/km4_image2_all.bin
	$(UTILITYDIR)/pad.sh $(IMAGE_TARGET_FOLDER)/km4_image2_all.bin

	$(UTILITYDIR)/image_tool/imagetool.sh $(IMAGE_TARGET_FOLDER)/km4_image2_all.bin $(KM0_BUILDDIR)/asdk/image ${BUILD_TYPE}

	@if [ ${BUILD_TYPE} = "MFG" ]; then \
		$(MOVE) $(IMAGE_TARGET_FOLDER)/km0_km4_image2.bin $(IMAGE_TARGET_FOLDER)/km0_km4_image2_mp.bin; \
	fi

	#@if [ -f $(IMAGE_TARGET_FOLDER)/km0_km4_image2.bin ]; then \
		#$(OTAPREPENDTOOL) $(IMAGE_TARGET_FOLDER)/km0_km4_image2.bin $(KM0_BUILDDIR)/asdk/image; \
	#fi

	@echo "========== Image manipulating end =========="

linker_loader:
	@echo "========= linker loader start ========="
	$(LD) $(LD_ARG) target_loader.axf $(RAM_OBJS_LIST) $(LINK_ROM_LIB)  -Wl,--whole-archive -lbootloader_hp -Wl,--no-whole-archive

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

	cat $(IMAGE_TARGET_FOLDER)/xip_boot_prepend.bin $(IMAGE_TARGET_FOLDER)/ram_1_prepend.bin > $(IMAGE_TARGET_FOLDER)/km4_boot_all.bin

	$(UTILITYDIR)/image_tool/imagetool.sh $(IMAGE_TARGET_FOLDER)/km4_boot_all.bin

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

gdb_all: gdb_prepare
	$(COPY) $(FLASHDLIMGDIR_KM0)/*  $(FLASHDLIMGDIR)/
	$(COPY) $(GNU_SCRIPT)/acut_loader/*  $(GNU_SCRIPT)/
	$(GNU_SCRIPT)/SetupGDB_FPGA.sh $(GNU_SCRIPT)
	$(GDB) -x $(GNU_SCRIPT)/rtl_gdb_flash_write_all.txt

gdb: gdb_prepare
	$(COPY) $(FLASHDLIMGDIR_KM0)/*  $(FLASHDLIMGDIR)/
	$(COPY) $(GNU_SCRIPT)/acut_loader/*  $(GNU_SCRIPT)/
	$(GNU_SCRIPT)/SetupGDB_FPGA.sh $(GNU_SCRIPT)
	$(GDB) -x $(GNU_SCRIPT)/rtl_gdb_flash_write.txt
	

gdbboot: gdb_prepare
	$(GDB) -x $(GNU_SCRIPT)/rtl_gdb_jtag_boot.txt

gdbbootxip: gdb_prepare
	$(GDB) -x $(GNU_SCRIPT)/rtl_gdb_jtag_boot_xip.txt

gdbloadrom: gdb_prepare
	$(GNU_SCRIPT)/SetupGDB_FPGA_MEM.sh $(GNU_SCRIPT)
	$(GDB) -x $(GNU_SCRIPT)/rtl_gdb_jtag_load_rom.txt

gdbloadromall: gdb_prepare
	$(GNU_SCRIPT)/SetupGDB_FPGA_MEM.sh $(GNU_SCRIPT)
	$(GDB) -x $(GNU_SCRIPT)/rtl_gdb_jtag_load_rom_all.txt

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
	@make -C make_secure clean
	# make -C config clean
	make -C $(SCRIPTSDIR)/lxdialog clean

clean_rom:
	@make -C make_rom/make clean
	@make -C make_rom/make_ns clean

clean_xip:
	@make -C make clean
	@make -C make_ns clean

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
		$(AR) crv rom.a $(APPLE_ROM_OBJS) $(HWLIB_ROM_OBJS) $(MBEDTLS_ROM_OBJS) $(MONI_ROM_OBJS) $(SWLIB_ROM_OBJS) $(VECT_ROM_OBJS) ; \
		mkdir -p $(ROOTDIR)/lib/rom_acut; \
		$(MOVE) -f rom.a $(ROOTDIR)/lib/rom_acut; \
	else @echo $(BUILD_TARGET_ROM_FOLDER): No such directory; fi

rom_linker:
	#${LD} -r -d -T $(ROOTDIR)/ld/rlx8721d_rom.ld --verbose --warn-common -Map=rom.map $(ROM_OBJS_LIST) -o rom.o  
	${LD_ROM} -r -d -T $(ROOTDIR)/ld/rlx8721d_rom.ld --verbose --warn-common -Map=rom.map $(ROM_OBJS_LIST) -o rom.o  
	${AR} crv rom.a rom.o
	${READELF} -S rom.o
	$(MOVE) -f rom.o $(ROOTDIR)/lib/rom_acut
	$(MOVE) -f rom.a $(ROOTDIR)/lib/rom_acut
	$(MOVE) -f rom.map $(ROOTDIR)/lib/rom_acut

	@echo "========= linker rom start ========="
	$(LD) $(LD_ARG) target_rom.axf $(LINK_ROM_LIB) 

	$(MOVE) text.map $(IMAGE_TARGET_FOLDER)/text_rom.map
	$(MOVE) target_rom.axf $(IMAGE_TARGET_FOLDER)
	$(OBJDUMP) -d $(IMAGE_TARGET_FOLDER)/target_rom.axf > $(IMAGE_TARGET_FOLDER)/target_rom.asm
	$(COPY) $(IMAGE_TARGET_FOLDER)/target_rom.axf $(IMAGE_TARGET_FOLDER)/target_pure_rom.axf
	$(STRIP) $(IMAGE_TARGET_FOLDER)/target_pure_rom.axf

	$(FROMELF) -j .rom.text -j .rom.text.libgcc \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_rom.axf $(IMAGE_TARGET_FOLDER)/km4_irom.bin
	$(FROMELF) -j .rom.rodata \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_rom.axf $(IMAGE_TARGET_FOLDER)/km4_drom.bin

	@echo "========== Image Info HEX SEC =========="
	$(CC_SIZE) -A --radix=16 $(IMAGE_TARGET_FOLDER)/target_rom.axf
	$(CC_SIZE) -t --radix=16 $(IMAGE_TARGET_FOLDER)/target_rom.axf
	@echo "========== Image Info HEX SEC =========="

	@echo "========== Image Info DEC SEC =========="
	$(CC_SIZE) -A --radix=10 $(IMAGE_TARGET_FOLDER)/target_rom.axf
	$(CC_SIZE) -t --radix=10 $(IMAGE_TARGET_FOLDER)/target_rom.axf
	@echo "========== Image Info DEC SEC =========="

	@echo "========== Image Info HEX NSEC =========="
	$(CC_SIZE) -A --radix=16 $(IMAGE_TARGET_FOLDER)/target_rom_ns.axf
	$(CC_SIZE) -t --radix=16 $(IMAGE_TARGET_FOLDER)/target_rom_ns.axf
	@echo "========== Image Info HEX NSEC =========="

	@echo "========== Image Info DEC NSEC =========="
	$(CC_SIZE) -A --radix=10 $(IMAGE_TARGET_FOLDER)/target_rom_ns.axf
	$(CC_SIZE) -t --radix=10 $(IMAGE_TARGET_FOLDER)/target_rom_ns.axf
	@echo "========== Image Info DEC NSEC =========="

	$(RM) -f $(RAM_OBJS_LIST)
	@echo "========== linker rom end =========="



rom_linker_ns:
	$(MOVE)	-f $(ROM_OBJS_LIST) $(BUILD_TARGET_ROM_FOLDER_NS)
	${LD_ROM} -r -d -T $(ROOTDIR)/ld_ns/rlx8721d_rom.ld --verbose --warn-common -Map=rom_ns.map $(ROM_OBJS_LIST_NS) -o rom_ns.o  
	${AR} crv rom_ns.a rom_ns.o
	${READELF} -S rom_ns.o
	$(MOVE) -f rom_ns.o $(ROOTDIR)/lib/rom_acut
	$(MOVE) -f rom_ns.a $(ROOTDIR)/lib/rom_acut
	$(MOVE) -f rom_ns.map $(ROOTDIR)/lib/rom_acut

	@echo "========= linker loader start ========="
	$(LD) $(LD_ARG) target_rom_ns.axf $(LINK_ROM_LIB_NS) 

	$(MOVE) text.map $(IMAGE_TARGET_FOLDER)/text_rom_ns.map
	$(MOVE) target_rom_ns.axf $(IMAGE_TARGET_FOLDER)
	$(OBJDUMP) -d $(IMAGE_TARGET_FOLDER)/target_rom_ns.axf > $(IMAGE_TARGET_FOLDER)/target_rom_ns.asm
	$(COPY) $(IMAGE_TARGET_FOLDER)/target_rom_ns.axf $(IMAGE_TARGET_FOLDER)/target_pure_rom_ns.axf
	$(STRIP) $(IMAGE_TARGET_FOLDER)/target_pure_rom_ns.axf

	$(FROMELF) -j .rom.text -j rom.text.libgcc \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_rom_ns.axf $(IMAGE_TARGET_FOLDER)/km4_irom_ns.bin
	$(FROMELF) -j .rom.rodata \
	-Obinary $(IMAGE_TARGET_FOLDER)/target_pure_rom_ns.axf $(IMAGE_TARGET_FOLDER)/km4_drom_ns.bin



	$(RM) -f $(RAM_OBJS_LIST)
	@echo "========== linker end =========="

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
copy_ld_rom:
	$(COPY) ./ld/rlx8721d_rom_bin.ld  $(BUILD_TARGET_FOLDER)/rlx8721d.ld
copy_ld_img1:
	$(COPY) ./ld/rlx8721d_img1_s.ld  $(BUILD_TARGET_FOLDER)/rlx8721d.ld
	cat $(LINK_ROM_SYMBOL_BOOT) >> $(BUILD_TARGET_FOLDER)/rlx8721d.ld
copy_ld_img2:
ifeq ($(CONFIG_TRUSTZONE_EN), y)
	$(COPY) ./ld/rlx8721d_img2_tz.ld  $(BUILD_TARGET_FOLDER)/rlx8721d.ld
else
	$(COPY) ./ld/rlx8721d_img2_is.ld  $(BUILD_TARGET_FOLDER)/rlx8721d.ld
endif
	cat $(LINK_ROM_SYMBOL_NS) >> $(BUILD_TARGET_FOLDER)/rlx8721d.ld
copy_ld_img3:
	$(COPY) ./ld/rlx8721d_img3_s.ld  $(BUILD_TARGET_FOLDER)/rlx8721d.ld
	cat $(LINK_ROM_SYMBOL_S) >> $(BUILD_TARGET_FOLDER)/rlx8721d.ld
copy_ld_rom_ns:
	$(COPY) ./ld_ns/rlx8721d_rom_bin.ld  $(BUILD_TARGET_FOLDER)/rlx8721d.ld

