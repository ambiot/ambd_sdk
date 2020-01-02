#!/bin/bash 

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

rm -fr *rom*.bin
rm -fr *rom*.txt
rm -fr *rom*.hex

#copy binary
cp rom_code_to/km4_drom_all.bin ./
cp rom_code_to/km4_irom_all.bin ./
cp rom_code_to/km0_irom.bin ./
cp rom_code_to/km0_drom.bin ./

#gen km4 tape out rom hex
binary_pading	km4_drom_all.bin		km4_drom_all_pad.bin 	96
binary_to_txt	km4_drom_all_pad.bin 		km4_drom_all_pad.bin.txt
split -l 8192	km4_drom_all_pad.bin.txt	km4_drom_ -d -a 1

mv km4_drom_0 rom_code_to/km4_drom_0.hex
mv km4_drom_1 rom_code_to/km4_drom_1.hex
mv km4_drom_2 rom_code_to/km4_drom_2.hex

binary_pading	km4_irom_all.bin		km4_irom_all_pad.bin 	256
binary_to_txt	km4_irom_all_pad.bin 		km4_irom_all_pad.bin.txt
split -l 8192	km4_irom_all_pad.bin.txt	km4_irom_ -d -a 1

mv km4_irom_0 rom_code_to/km4_irom_0.hex
mv km4_irom_1 rom_code_to/km4_irom_1.hex
mv km4_irom_2 rom_code_to/km4_irom_2.hex
mv km4_irom_3 rom_code_to/km4_irom_3.hex
mv km4_irom_4 rom_code_to/km4_irom_4.hex
mv km4_irom_5 rom_code_to/km4_irom_5.hex
mv km4_irom_6 rom_code_to/km4_irom_6.hex
mv km4_irom_7 rom_code_to/km4_irom_7.hex

#gen km0 tape out rom hex
binary_pading	km0_drom.bin			km0_drom_pad.bin 	16
binary_to_txt	km0_drom_pad.bin 		km0_drom.hex

binary_pading	km0_irom.bin			km0_irom_pad.bin 	96
binary_to_txt	km0_irom_pad.bin 		km0_irom.hex

cp km0_irom.hex rom_code_to/km0_irom.hex
cp km0_drom.hex rom_code_to/km0_drom.hex

