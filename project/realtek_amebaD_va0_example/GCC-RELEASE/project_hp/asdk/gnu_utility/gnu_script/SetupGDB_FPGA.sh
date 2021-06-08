#!/bin/sh

#===============================================================================
CURRENT_UTILITY_DIR=$(pwd)
FLASHDLIMGDIR=$1
IMAGE_TARGET_FOLDER=$CURRENT_UTILITY_DIR/image
echo "..."
echo $CURRENT_UTILITY_DIR
echo $IMAGE_TARGET_FOLDER
GDBSCPTFILE="$FLASHDLIMGDIR/rtl_gdb_flash_write.txt" 
GDBSCPTFILE_ALL="$FLASHDLIMGDIR/rtl_gdb_flash_write_all.txt" 

#===============================================================================
COMPILEOS=$(uname)

if [ "$COMPILEOS" != "Darwin" ]; then
        #set image2 code size
        if [ -f $IMAGE_TARGET_FOLDER/km0_km4_image2.bin ]; then
                FLASHFILENAME="$IMAGE_TARGET_FOLDER/km0_km4_image2.bin";
                FLASH_FILE_SIZE=$(stat -c %s $FLASHFILENAME);
        else
                FLASH_FILE_SIZE=0;
        fi
        sed -i "s#^set \$FlashFileSize =.*#set \$FlashFileSize =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE

        #set boot code size
        FLASHFILENAME="$IMAGE_TARGET_FOLDER/km4_boot_all.bin"
        FLASH_FILE_SIZE=$(stat -c %s $FLASHFILENAME)
        sed -i "s#^set \$XIPBootSize =.*#set \$XIPBootSize =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE

        #set system data size
        FLASHFILENAME="$IMAGE_TARGET_FOLDER/system.bin"
        FLASH_FILE_SIZE=$(stat -c %s $FLASHFILENAME)
        sed -i "s#^set \$SysDataSize =.*#set \$SysDataSize =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE

        #IMG3 size
        FLASHFILENAME="$IMAGE_TARGET_FOLDER/km4_image3_all.bin"
        FLASH_FILE_SIZE=$(stat -c %s $FLASHFILENAME)
        sed -i "s#^set \$IMG3Size =.*#set \$IMG3Size =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE

        #IMG_ALL size
        FLASHFILENAME="$IMAGE_TARGET_FOLDER/flash_all.bin"
        FLASH_FILE_SIZE=$(stat -c %s $FLASHFILENAME)
        sed -i "s#^set \$IMGAllSize =.*#set \$IMGAllSize =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE_ALL
else
        #set image2 code size
        if [ -f $IMAGE_TARGET_FOLDER/km0_km4_image2.bin ]; then
                FLASHFILENAME="$IMAGE_TARGET_FOLDER/km0_km4_image2.bin";
                FLASH_FILE_SIZE=$(stat -f%z $FLASHFILENAME);
        else
                FLASH_FILE_SIZE=0;
        fi
        sed -i " " "s#^set \$FlashFileSize =.*#set \$FlashFileSize =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE

        #set boot code size
        FLASHFILENAME="$IMAGE_TARGET_FOLDER/km4_boot_all.bin"
        FLASH_FILE_SIZE=$(stat -f%z $FLASHFILENAME)
        sed -i " " "s#^set \$XIPBootSize =.*#set \$XIPBootSize =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE

        #set system data size
        FLASHFILENAME="$IMAGE_TARGET_FOLDER/system.bin"
        FLASH_FILE_SIZE=$(stat -f%z $FLASHFILENAME)
        sed -i " " "s#^set \$SysDataSize =.*#set \$SysDataSize =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE

        #IMG3 size
        FLASHFILENAME="$IMAGE_TARGET_FOLDER/km4_image3_all.bin"
        FLASH_FILE_SIZE=$(stat -f%z $FLASHFILENAME)
        sed -i " " "s#^set \$IMG3Size =.*#set \$IMG3Size =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE

        #IMG_ALL size
        FLASHFILENAME="$IMAGE_TARGET_FOLDER/flash_all.bin"
        FLASH_FILE_SIZE=$(stat -f%z $FLASHFILENAME)
        sed -i " " "s#^set \$IMGAllSize =.*#set \$IMGAllSize =$FLASH_FILE_SIZE#g"  $GDBSCPTFILE_ALL
fi
