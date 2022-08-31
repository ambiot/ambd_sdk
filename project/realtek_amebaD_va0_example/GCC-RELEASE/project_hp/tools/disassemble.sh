#!/bin/bash 

#
#gen disassemble
#
rom_folder=rom_code_to
../toolchain/cygwin/asdk-5.4.1/cygwin/newlib/bin/arm-elf-objdump.exe -h -S --disassemble-all $rom_folder/target_loader.axf > $rom_folder/target_loader_disassemble.txt
../toolchain/cygwin/asdk-5.4.1/cygwin/newlib/bin/arm-elf-objdump.exe -h -S --disassemble-all $rom_folder/target_rom.axf > $rom_folder/target_rom_disassemble.txt
../toolchain/cygwin/asdk-5.4.1/cygwin/newlib/bin/arm-elf-objdump.exe -h -S --disassemble-all $rom_folder/target_rom_ns.axf > $rom_folder/target_rom_ns_disassemble.txt
../toolchain/cygwin/asdk-5.4.1/cygwin/newlib/bin/arm-elf-objdump.exe -h -S --disassemble-all $rom_folder/target_img3.axf > $rom_folder/target_img3_disassemble.txt
../toolchain/cygwin/asdk-5.4.1/cygwin/newlib/bin/arm-elf-objdump.exe -h -S --disassemble-all $rom_folder/target_img2.axf > $rom_folder/target_img2_disassemble.txt
