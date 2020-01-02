#!/bin/sh

#===============================================================================
CURRENT_UTILITY_DIR=$(pwd)
FLASHDLIMGDIR=$1
IMAGE_TARGET_FOLDER=$CURRENT_UTILITY_DIR/lib/rom_acut
echo "..."
echo $CURRENT_UTILITY_DIR
echo $IMAGE_TARGET_FOLDER
GDBSCPTFILE="$FLASHDLIMGDIR/rtl_gdb_mem_write.txt" 
GDBSCPTFILE_ALL="$FLASHDLIMGDIR/rtl_gdb_jtag_load_rom_all.txt" 

#===============================================================================
#set rom.bin code size
FLASHFILENAME="$IMAGE_TARGET_FOLDER/km4_irom.bin" 
FLASH_FILE_SIZE=$(stat -c %s $FLASHFILENAME)
sed -i "s#^set \$CODESize =.*#set \$CODESize =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE

#set rom_data.bin data size
FLASHFILENAME="$IMAGE_TARGET_FOLDER/km4_drom.bin" 
FLASH_FILE_SIZE=$(stat -c %s $FLASHFILENAME)
sed -i "s#^set \$DATASize =.*#set \$DATASize =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE

#set rom_ns.bin code size
FLASHFILENAME="$IMAGE_TARGET_FOLDER/km4_irom_ns.bin" 
FLASH_FILE_SIZE=$(stat -c %s $FLASHFILENAME)
sed -i "s#^set \$CODESize_NS =.*#set \$CODESize_NS =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE

#set rom_data_ns.bin data size
FLASHFILENAME="$IMAGE_TARGET_FOLDER/km4_drom_ns.bin" 
FLASH_FILE_SIZE=$(stat -c %s $FLASHFILENAME)
sed -i "s#^set \$DATASize_NS =.*#set \$DATASize_NS =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE

#set km4_irom_all.bin data size
FLASHFILENAME="$IMAGE_TARGET_FOLDER/km4_irom_all.bin" 
FLASH_FILE_SIZE=$(stat -c %s $FLASHFILENAME)
sed -i "s#^set \$AllCODESize =.*#set \$AllCODESize =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE_ALL

#set km4_drom_all.bin data size
FLASHFILENAME="$IMAGE_TARGET_FOLDER/km4_drom_all.bin" 
FLASH_FILE_SIZE=$(stat -c %s $FLASHFILENAME)
sed -i "s#^set \$AllDATASize =.*#set \$AllDATASize =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE_ALL
