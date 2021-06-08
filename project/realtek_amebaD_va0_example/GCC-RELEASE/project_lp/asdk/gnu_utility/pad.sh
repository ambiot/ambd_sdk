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

# Get Parameters
IMAGE_FILENAME=$1
COMPILEOS=$(uname)
if [ "$COMPILEOS" != "Darwin" ]; then
        filesize=$(stat -c "%s" $IMAGE_FILENAME)
else
        filesize=$(stat -f%z $IMAGE_FILENAME)
fi
newsize=$((((($filesize - 1) >> 12) + 1) << 12))
padcount=$(($newsize - $filesize))

for (( i=$padcount; i > 0; i-- ))
do
	echo -n -e "\xFF" >> $IMAGE_FILENAME
done
