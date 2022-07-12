#!/bin/bash 


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

cp ../asdk/image/ram_retention.bin ./
binary_to_txt	ram_retention.bin			ram_retention.bin.txt
