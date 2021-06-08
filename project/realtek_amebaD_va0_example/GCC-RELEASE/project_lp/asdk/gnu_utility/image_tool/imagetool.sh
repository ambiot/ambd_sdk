#!/bin/bash 

################
# Library
################
Usage() {
    echo "Usage: $0 [Image Name]"
}

function relative_to_path {
        local source=$1
        local target=$2
        local common_part=$source
        local result=""

        while [[ "${target#$common_part}" == "${target}" ]]; do
                common_part="$(dirname $common_part)"
                if [[ -z $result ]]; then
                        result=".."
                else
                        result="../$result"
                fi
        done

        if [[ $common_part == "/" ]]; then
                result="$result/"
        fi

        local forward_part="${target#$common_part}"

        if [[ -n $result ]] && [[ -n $forward_part ]]; then
                result="$result$forward_part"
        elif [[ -n $forward_part ]]; then
                result="${forward_part:1}"
        fi

        echo $result
}

################
# Main
################
#if [ "$#" -lt 2 ]; then
#    Usage
#    exit 1
#fi

cd ./gnu_utility/image_tool
source ../../../../security_config.sh

# Get Parameters
COMPILEOS=$(uname)
if [ "$COMPILEOS" != "Darwin" ]; then
	COMPILEOS=$(uname -o)
fi

if [ "$COMPILEOS" == "GNU/Linux" ]; then
	IMAGE_FULLNAME=$1
elif [ "$COMPILEOS" == "Darwin" ]; then
	IMAGE_FULLNAME=$(relative_to_path $(pwd) $1)
else
	IMAGE_FULLNAME=$(realpath --relative-to=$(pwd) $1)
fi

IMAGE_FILENAME=$(basename $1)
CURR_PATH=$(dirname $1)

if [ "$2" != "" ]; then
	if [ "$COMPILEOS" == "GNU/Linux" ]; then
		COPY_PATH=$2
        elif [ "$COMPILEOS" == "Darwin" ]; then
		COPY_PATH=$(relative_to_path $(pwd) $2)
	else
		COPY_PATH=$(realpath --relative-to=$(pwd) $2)
	fi
fi

if [ "$COMPILEOS" == "GNU/Linux" ]; then
	ENCTOOL=./EncTool
else
	ENCTOOL=./EncTool.exe
fi

IMAGE_NAME_EN="${IMAGE_FULLNAME%.*}"'-en.'"${IMAGE_FULLNAME##*.}"

if [ "$IMAGE_FILENAME" == "km0_boot_all.bin" ]; then
	if [ $RSIP_ENABLE == 1 ]; then
		$ENCTOOL rsip $IMAGE_FULLNAME $IMAGE_NAME_EN 0x08000000 $RSIP_KEY $RSIP_IV
		mv $IMAGE_NAME_EN $IMAGE_FULLNAME
	fi
fi

if [ "$IMAGE_FILENAME" == "km4_boot_all.bin" ]; then
	if [ $SBOOT_ENABLE == 1 ]; then
		IMAGE_NAME_SB="${IMAGE_FULLNAME%.*}"'-sb.'"${IMAGE_FULLNAME##*.}"
		$ENCTOOL sboot $IMAGE_FULLNAME $IMAGE_NAME_SB key_pair.txt $SBOOT_SEED
		mv $IMAGE_NAME_SB $IMAGE_FULLNAME
	fi
	
	if [ $RSIP_ENABLE == 1 ]; then
		$ENCTOOL rsip $IMAGE_FULLNAME $IMAGE_NAME_EN 0x08004000 $RSIP_KEY $RSIP_IV
		mv $IMAGE_NAME_EN $IMAGE_FULLNAME
	fi
fi

if [ "$IMAGE_FILENAME" == "km4_image3_all.bin" ]; then
	if [ $RDP_ENABLE == 1 ]; then
		$ENCTOOL rdp $IMAGE_FULLNAME $IMAGE_NAME_EN $RDP_KEY
	fi
fi

if [ "$IMAGE_FILENAME" == "km4_image2_all.bin" ]; then
	if [ $RSIP_ENABLE == 1 ]; then
		$ENCTOOL rsip $IMAGE_FULLNAME $IMAGE_NAME_EN 0x0e000000 $RSIP_KEY $RSIP_IV
		
		if [ ! -f $COPY_PATH/km0_image2_all.bin ]; then
			exit
		fi

		$ENCTOOL rsip $COPY_PATH/km0_image2_all.bin $COPY_PATH/km0_image2_all-en.bin 0x0c000000 $RSIP_KEY $RSIP_IV
		cat $COPY_PATH/km0_image2_all-en.bin $IMAGE_NAME_EN > $CURR_PATH/km0_km4_image2_tmp.bin
	else
		if [ ! -f $COPY_PATH/km0_image2_all.bin ]; then
			exit
		fi		

		cat $COPY_PATH/km0_image2_all.bin $IMAGE_FULLNAME > $CURR_PATH/km0_km4_image2_tmp.bin
	fi
	
	if [ $RDP_ENABLE == 1 ]; then
		if [ -f "$CURR_PATH/km4_image3_all-en.bin" ]; then
			cat $CURR_PATH/km0_km4_image2_tmp.bin $CURR_PATH/km4_image3_all-en.bin > $CURR_PATH/km0_km4_image2.bin
			rm $CURR_PATH/km0_km4_image2_tmp.bin
		else
			mv $CURR_PATH/km0_km4_image2_tmp.bin $CURR_PATH/km0_km4_image2.bin
		fi
	else
		mv $CURR_PATH/km0_km4_image2_tmp.bin $CURR_PATH/km0_km4_image2.bin
	fi

	cp $CURR_PATH/km0_km4_image2.bin $COPY_PATH/km0_km4_image2.bin
fi

if [ "$IMAGE_FILENAME" == "km0_image2_all.bin" ]; then
	if [ $RSIP_ENABLE == 1 ]; then
		$ENCTOOL rsip $IMAGE_FULLNAME $IMAGE_NAME_EN 0x0c000000 $RSIP_KEY $RSIP_IV

		if [ ! -f $COPY_PATH/km4_image2_all.bin ]; then
			exit
		fi

		$ENCTOOL rsip $COPY_PATH/km4_image2_all.bin $COPY_PATH/km4_image2_all-en.bin 0x0e000000 $RSIP_KEY $RSIP_IV
		cat $IMAGE_NAME_EN $COPY_PATH/km4_image2_all-en.bin > $CURR_PATH/km0_km4_image2_tmp.bin
	else
		if [ ! -f $COPY_PATH/km4_image2_all.bin ]; then
			exit
		fi

		cat $IMAGE_FULLNAME $COPY_PATH/km4_image2_all.bin > $CURR_PATH/km0_km4_image2_tmp.bin
	fi
	
	if [ $RDP_ENABLE == 1 ]; then
		if [ -f "$COPY_PATH/km4_image3_all-en.bin" ]; then
			cat $CURR_PATH/km0_km4_image2_tmp.bin $COPY_PATH/km4_image3_all-en.bin > $CURR_PATH/km0_km4_image2.bin
			rm $CURR_PATH/km0_km4_image2_tmp.bin
		else
			mv $CURR_PATH/km0_km4_image2_tmp.bin $CURR_PATH/km0_km4_image2.bin
		fi
	else
		mv $CURR_PATH/km0_km4_image2_tmp.bin $CURR_PATH/km0_km4_image2.bin
	fi

	cp $CURR_PATH/km0_km4_image2.bin $COPY_PATH/km0_km4_image2.bin

fi
