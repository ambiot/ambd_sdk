#!/bin/bash 
 
rom_folder=rom_code_to

rm -f $rom_folder/*

#copy km0 rom & flash
cp ../asdk/image/km0_irom.bin $rom_folder/
cp ../asdk/image/km0_drom.bin $rom_folder/

cp ../asdk/image/km0_boot_all.bin $rom_folder/
cp ../asdk/image/km0_image2_all.bin $rom_folder/

cp ../asdk/image/target_rom.axf $rom_folder/
cp ../asdk/image/target_loader.axf $rom_folder/
cp ../asdk/image/target_img2.axf $rom_folder/

#copy map for debug use
cp ../asdk/image/*.map $rom_folder/

#copy asm for debug use
cp ../asdk/image/*.asm $rom_folder/
