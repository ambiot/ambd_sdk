#!/bin/bash 

################
# Library
################
Usage() {
    echo "Usage: $0 [Image Name] [Start Symbol Name] [Symbols List File]"
}

# Parameter:
#     value, width, dest
function MakeFixedWidthHeaderString() {
    local __value=$1
    local __width=$2
    local __dest=$3
    local __reorder=$4
    local __header_raw
    local __header_raw_reorder
    local __header_array

    if [[ "$__dest" ]]; then

        __header_raw=$(printf "%0""$__width""x" $__value)
        # echo $__header_raw

        if [ "$__reorder" -eq 1 ]; then
                # 20000680 to 80060020
                for (( i=$__width; i > 0; i-=2 ))
                do
                    __header_raw_reorder+=$(echo ${__header_raw:(i-2):2})
                done
        else
                __header_raw_reorder=$__header_raw
        fi
        #echo $__header_raw_reorder

        __header_array=($(echo $__header_raw_reorder | sed 's/\(.\)/\1 /g'))

        for (( i=0; i < $__width; i+=2))
        do
            eval $__dest+='\\x'"${__header_array[$i]}${__header_array[$i+1]}"
        done
    fi
}

################
# Main
################
if [ "$#" -lt 2 ]; then
    Usage
    exit 1
fi

# Get Parameters
COMPILEOS=$(uname)

# Get Parameters
COMPILEOS=$(uname)
if [ "$COMPILEOS" != "Darwin" ]; then
	COMPILEOS=$(uname -o)
fi

cd ./gnu_utility
if [ "$COMPILEOS" == "GNU/Linux" ]; then
	CHECKSUMTOOL=./checksum
else
	CHECKSUMTOOL=./checksum.exe
fi

# Constant Variables
VERSION=0xFFFFFFFF
OTA_NUM=1
OTA_SIGN=0x4F544131
HEADER_LEN=24
CHECKSUM=0
IMAGE_LEN=0
OFFSET=32
IMAGE_ADDR=0xFFFFFFFF


if [ "$COMPILEOS" == "GNU/Linux" ]; then
	IMAGE_FILENAME=$1
	COPY_PATH=$2
elif [ "$COMPILEOS" == "Darwin" ]; then
	IMAGE_FILENAME=$(relative_to_path $(pwd) $1)
	COPY_PATH=$(relative_to_path $(pwd) $2)
else
	IMAGE_FILENAME=$(realpath --relative-to=$(pwd) $1)
	COPY_PATH=$(realpath --relative-to=$(pwd) $2)
fi

IMAGE_FILENAME_PREPEND="${IMAGE_FILENAME%.*}"'_prepend.'"${IMAGE_FILENAME##*.}"
IMAGE_FILENAME_NEW=$(basename $IMAGE_FILENAME)

if [ "$COMPILEOS" != "Darwin" ]; then
    IMAGE_LEN=$(du -b $IMAGE_FILENAME | cut -f 1)
else
    IMAGE_LEN=$(stat -f%z $IMAGE_FILENAME)
fi

HEADER_FINAL=''
if [ "$IMAGE_FILENAME_NEW" == "km0_km4_image2.bin" ]; then
    MakeFixedWidthHeaderString $VERSION   8  HEADER_FINAL 0
    MakeFixedWidthHeaderString $OTA_NUM   8  HEADER_FINAL 1
    MakeFixedWidthHeaderString $OTA_SIGN   8  HEADER_FINAL 0
    MakeFixedWidthHeaderString $HEADER_LEN   8  HEADER_FINAL 1
    MakeFixedWidthHeaderString $CHECKSUM    8  HEADER_FINAL 1
	MakeFixedWidthHeaderString $IMAGE_LEN    8  HEADER_FINAL 1
	MakeFixedWidthHeaderString $OFFSET    8  HEADER_FINAL 1
	MakeFixedWidthHeaderString $IMAGE_ADDR    8  HEADER_FINAL 1
fi

# echo $HEADER_FINAL

echo -n -e $HEADER_FINAL | cat - $IMAGE_FILENAME > $IMAGE_FILENAME_PREPEND

#checksum
$CHECKSUMTOOL $IMAGE_FILENAME $IMAGE_FILENAME_PREPEND

CURR_PATH=$(dirname $IMAGE_FILENAME_PREPEND)
mv $IMAGE_FILENAME_PREPEND $CURR_PATH/OTA_All.bin
cp $CURR_PATH/OTA_All.bin $COPY_PATH/OTA_All.bin