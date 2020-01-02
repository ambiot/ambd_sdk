#!/bin/bash 

################
# Library
################
Usage() {
    echo "Usage: $0 [Image Name]"
}


################
# Main
################
if [ "$#" -lt 1 ]; then
    Usage
    exit 1
fi

if [ -e "zero.bin" ]; then
    echo ">>> Remove old zero.bin"
    rm zero.bin
fi

if [ -e "temp.txt" ]; then
    echo ">>> Remove old temp.txt"
    rm temp.txt
fi


IMAGE_FILENAME=$1
IMAGE_FILENAME_TEXT="$IMAGE_FILENAME".txt

if [ -e "$IMAGE_FILENAME_TEXT" ]; then
    echo ">>> Remove old $IMAGE_FILENAME_TEXT"
    rm "$IMAGE_FILENAME_TEXT"
fi


#
# Generate fixed size padding file.
# Modify "ibs" and "count" parameters to set the file size.
#
dd if=/dev/zero ibs=1k count=256 > zero.bin


#
# Merge binary file and padding file
#
dd if=$IMAGE_FILENAME of=zero.bin conv=notrunc


#
# Use "od" tool to convert binary file to hexadecimal text format
#
od -t x4 -w1 -v zero.bin | cut -d " " -f 2 > "$IMAGE_FILENAME_TEXT"


#
# Remove unnecessary last line generate by od command.
# Another method:
#    head -n -1 rom.bin.1.txt1 > temp.txt && cp temp.txt rom.bin.1.txt1
sed '$ d' "$IMAGE_FILENAME_TEXT" > temp.txt && cp temp.txt "$IMAGE_FILENAME_TEXT"


#
# Remove temporary files
#
rm zero.bin
rm temp.txt
