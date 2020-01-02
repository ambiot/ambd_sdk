#!/bin/bash 
 
rom_folder=rom_code_to

rm -f $rom_folder/*

#copy km4 rom & flash
#cp ../asdk/image/km4_irom.bin $rom_folder/
#cp ../asdk/image/km4_drom.bin $rom_folder/

#cp ../asdk/image/km4_irom_ns.bin $rom_folder/
#cp ../asdk/image/km4_drom_ns.bin $rom_folder/

cp ../asdk/image/km4_boot_all.bin $rom_folder/
cp ../asdk/image/km0_km4_image2.bin $rom_folder/
#cp ../asdk/image/km4_image3_all.bin $rom_folder/

#cp ../asdk/image/target_rom.axf $rom_folder/
#cp ../asdk/image/target_rom_ns.axf $rom_folder/
#cp ../asdk/image/target_loader.axf $rom_folder/
#cp ../asdk/image/target_img2.axf $rom_folder/
#cp ../asdk/image/target_img3.axf $rom_folder/

#copy km0 rom & flash
cp ../../project_lp/asdk/image/km0_boot_all.bin $rom_folder/km0_boot_all.bin
#cp ../../realtek_amebaD_cm0_gcc_verification/asdk/image/km0_image2_all.bin $rom_folder/km0_image2_all.bin
#cp ../../realtek_amebaD_cm0_gcc_verification/tools/rom_code_to/km0_irom.bin.txt $rom_folder/km0_irom.bin.txt
#cp ../../realtek_amebaD_cm0_gcc_verification/tools/rom_code_to/km0_drom.bin.txt $rom_folder/km0_drom.bin.txt
#cp ../../realtek_amebaD_cm0_gcc_verification/tools/rom_code_to/km0_irom.bin $rom_folder/
#cp ../../realtek_amebaD_cm0_gcc_verification/tools/rom_code_to/km0_drom.bin $rom_folder/

#copy map for debug use
#cp ../asdk/image/*.map $rom_folder/

#copy asm for debug use
#cp ../asdk/image/*.asm $rom_folder/
