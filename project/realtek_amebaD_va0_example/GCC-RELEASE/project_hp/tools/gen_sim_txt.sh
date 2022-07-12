#!/bin/bash 

#KM0_MEMORY
#{
#	IROM (rx) : 			ORIGIN = 0x00000000, LENGTH = 0x18000	/* ROM: 96k */
#	DROM (rx) : 			ORIGIN = 0x00020000, LENGTH = 0x4000	/* ROM: 16k */
#}

#KM4_MEMORY
#{
#	IROM (rx) : 			ORIGIN = 0x10100000, LENGTH = 0x1010A000 - 0x10100000	/* ROM: 40k */
#	IROM_NS (rx) : 			ORIGIN = 0x1010A000, LENGTH = 0x10140000 - 0x1010A000	/* ROM: 216k */

#	DROM_NS (rx) : 			ORIGIN = 0x101C0000, LENGTH = 0x101D4000 - 0x101C0000	/* ROM: 80k */
#	DROM (rx) : 			ORIGIN = 0x101D4000, LENGTH = 0x101D8000 - 0x101D4000	/* ROM: 16k */
#}

#FLASH_MEMORY
#{
#	KM0_BOOT (rx)  :		ORIGIN = 0x08000000+0x20, LENGTH = 0x04000-0x20	/* XIPBOOT: 16k, 32 Bytes resvd for header*/
#	KM4_BOOT (rx)  :		ORIGIN = 0x08004000+0x20, LENGTH = 0x04000-0x20	/* XIPBOOT: 16k, 32 Bytes resvd for header*/
#	BACKUP (r) :			ORIGIN = 0x08008000, LENGTH = 0x1000	/* BACKUP: 4K system data in flash */
#	XIPSYS (r) :			ORIGIN = 0x08009000, LENGTH = 0x1000	/* XIPSYS: 4K system data in flash */
#	RESVD (r) :			ORIGIN = 0x0800A000, LENGTH = 0x1000	/* RESVD: 4K reserved user section in flash */
#	KM0_IMG2 (rx)  : 		ORIGIN = 0x0800B000+0x20, LENGTH = 0x20000-0x20	/* KM0_IMG2: 128k, 32 Bytes resvd for header */
#	KM4_IMG2 (rx)  : 		ORIGIN = 0x0802B000+0x20, LENGTH = 0x65000-0x20	/* KM4_IMG2 OTA1: 404k, 32 Bytes resvd for header */
#	KM4_IMG2_OTA2 (rx)  : 		ORIGIN = 0x08090000+0x20, LENGTH = 0x65000-0x20	/* KM4_IMG2 OTA2: 404k, 32 Bytes resvd for header */
#	KM4_IMG3 (rx)  : 		ORIGIN = 0x080F5000+0x20, LENGTH = 0xB000-0x20	/* KM4_IMG3 Secure Image: 44k, 32 Bytes resvd for header */
#}

rom_folder=rom_code_to
out_folder=rom_code_to

function binary_pading()
{
	form_file=$1
	to_file=$2
	size=$3

	dd if=$form_file ibs=1k count=$size >  temp.bin
	dd if=/dev/zero ibs=1k count=$size >> temp.bin
	dd if=temp.bin ibs=1k count=$size > $to_file

	rm temp.bin
}

function binary_to_txt()
{
	form_file=$1
	to_file=$2

	# Use "od" tool to convert binary file to hexadecimal text format
	od -t x4 -w1 -v $form_file | cut -d " " -f 2 > $to_file

	# Remove unnecessary last line generate by od command.
	sed '$ d' $to_file > temp.txt && cp temp.txt $to_file
	
	rm temp.txt
}

function binary_to_txt_x1()
{
	form_file=$1
	to_file=$2

	# Use "od" tool to convert binary file to hexadecimal text format
	od -t x1 -w1 -v $form_file | cut -d " " -f 2 > $to_file

	# Remove unnecessary last line generate by od command.
	sed '$ d' $to_file > temp.txt && cp temp.txt $to_file
	
	rm temp.txt
}

#gen IROM
#binary_pading	$rom_folder/km4_irom.bin	$rom_folder/km4_irom_pad.bin		40
#cat		$rom_folder/km4_irom_pad.bin	$rom_folder/km4_irom_ns.bin >		$rom_folder/km4_irom_all.bin
#binary_to_txt	$rom_folder/km4_irom_all.bin 	$out_folder/km4_irom_all.bin.txt
#binary_to_txt	$rom_folder/km4_irom.bin 	$out_folder/km4_irom.bin.txt
#binary_to_txt	$rom_folder/km4_irom_ns.bin 	$out_folder/km4_irom_ns.bin.txt


#gen DROM
#binary_pading	$rom_folder/km4_drom_ns.bin	$rom_folder/km4_drom_ns_pad.bin 	80
#cat 		$rom_folder/km4_drom_ns_pad.bin $rom_folder/km4_drom.bin >		$rom_folder/km4_drom_all.bin
#binary_to_txt	$rom_folder/km4_drom_all.bin	$out_folder/km4_drom_all.bin.txt
#binary_to_txt	$rom_folder/km4_drom.bin 	$out_folder/km4_drom.bin.txt
#binary_to_txt	$rom_folder/km4_drom_ns.bin 	$out_folder/km4_drom_ns.bin.txt

#gen Flash
binary_pading	$rom_folder/km0_boot_all.bin	$rom_folder/km0_boot_all_pad.bin	8
binary_pading	$rom_folder/km4_boot_all.bin	$rom_folder/km4_boot_all_pad.bin	4

binary_pading	$rom_folder/km0_km4_image2.bin	$rom_folder/km0_km4_image2_all_pad.bin	1000

cat		$rom_folder/km0_boot_all_pad.bin > 		$rom_folder/flash_all.bin
cat		FF4K.bin >> 					$rom_folder/flash_all.bin
cat		FF4K.bin >> 					$rom_folder/flash_all.bin
cat		$rom_folder/km4_boot_all_pad.bin >>		$rom_folder/flash_all.bin
cat		FF4K.bin >> 					$rom_folder/flash_all.bin
cat		$rom_folder/km0_km4_image2_all_pad.bin >> 		$rom_folder/flash_all.bin


binary_to_txt_x1	$rom_folder/flash_all.bin	$out_folder/flash_all.bin.txt

cp		$rom_folder/flash_all.bin	../asdk/image/
#cp		$rom_folder/km4_irom_all.bin	../asdk/image/
#cp		$rom_folder/km4_drom_all.bin	../asdk/image/

str="KM0-KM4-"`date +"%Y%m%d-%H%M%S"`
echo "simulation files folder:"$str
mkdir $str
cp		$out_folder/flash_all.bin.txt			$str
#cp		$out_folder/km4_drom_all.bin.txt		$str
#cp		$out_folder/km4_irom_all.bin.txt		$str
#cp		$out_folder/km0_irom.bin.txt			$str
#cp		$out_folder/km0_drom.bin.txt			$str

#copy map for debug use
#cp		$out_folder/*.map				$str

#copy asm for debug use
#cp		$out_folder/*.asm				$str

#echo "split rom code for tapeout !!!!!!!!"
#./split_rom.sh
#mkdir $str"-ROM-TO"
#cp		$out_folder/*.hex			 	$str"-ROM-TO"		

#echo "take some time to gen asm text !!!!!!!!"
#./disassemble.sh
#cp		$out_folder/*disassemble.txt			$str

