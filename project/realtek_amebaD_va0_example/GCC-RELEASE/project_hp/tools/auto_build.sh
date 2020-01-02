#!/bin/bash
str="peripheral_"`date +"%Y%m%d_%H%M%S"`
echo "peripheral image files folder:"$str
mkdir $str
mkdir $str/log

function build_default
{
	#build km0
	cd ../../realtek_amebaD_cm0_gcc_verification
	#remove *_all.bin if exist
	rm	-f	asdk/image/*_all.bin
	
	echo "build km0..."
	{
		make clean
		make xip
	}>>../realtek_amebaD_cm4_gcc_verification/tools/$str/log/km0.txt 2>&1
	
	#copy image
	if [ -f "asdk/image/km0_image2_all.bin" ]; then
		cp	-f	asdk/image/*_all.bin			../realtek_amebaD_cm4_gcc_verification/tools/$str
		echo "km0 ok">>../realtek_amebaD_cm4_gcc_verification/tools/$str/log/build_result.txt 2>&1
		echo "km0 build ok"
	else
		echo "km0 failed">>../realtek_amebaD_cm4_gcc_verification/tools/$str/log/build_result.txt 2>&1
		echo "km0 build failed"
	fi

	#build km4
	cd ../realtek_amebaD_cm4_gcc_verification
	#remove *_all.bin if exist
	rm	-f	asdk/image/*_all.bin
	
	echo "build km4..."
	{
		make clean
		make xip
	}>>tools/$str/log/km4.txt 2>&1

	#copy image
	if [ -f "asdk/image/km4_image2_all.bin" ]; then
		cp	-f	asdk/image/*_all.bin			tools/$str
		echo "km4 ok">>tools/$str/log/build_result.txt 2>&1
		echo "km4 build ok"
	else
		echo "km4 failed">>tools/$str/log/build_result.txt 2>&1
		echo "km4 build failed"
	fi
	
	cd tools
}

#get all example list
function get_list
{
	find ../example_sources -name "src" > example_list.txt
	sort -o example_list.txt example_list.txt
}

function build_example
{
	list_file=$1
	to_path=${list_file%.txt}
	mkdir -p $str/$to_path
	echo "build $to_path"
	build_num=0
	build_ok=0
	build_failed=0
	
	#backup main.c
	mv	-f	../src/main.c		../src/main.bk

	while read -r example
	do 
		let "build_num+=1"
		
		#get example path:
		from_path=${example%/src}
		example_name=${from_path##*/}

		#copy *.c *.h
		cp	-f	$from_path/src/*.*		../src
		
		if [ -d "$from_path/inc/" ]; then
			cp	-f	$from_path/inc/*.h		../src
		fi
		
		#remove *_all.bin if exist
		rm	-f	../asdk/image/*_all.bin

		#make file
		cd ..
		( make xip )>>tools/$str/log/$example_name.txt 2>&1
		cd tools

		#copy image to example file
		if [ -f "../asdk/image/km0_km4_image2.bin" ]; then
			mv	-f	../asdk/image/km0_km4_image2.bin			$str/$to_path/$example_name.bin
			let "build_ok+=1"
			echo "$example ok">>$str/log/build_result.txt 2>&1
			echo "$example ok"
		else
			let "build_failed+=1"
			echo "$example failed">>$str/log/build_result.txt 2>&1
			echo "$example failed"
		fi

		rm	-f	../src/*.c
		rm	-f	../src/*.h
		rm	-f	../src/*.a
		rm	-f	../src/*.o
		rm	-f	../src/*.d
		rm	-f	../src/*.i
		rm	-f	../src/*.s
		rm	-f	../src/*.su

	done <  $list_file

	#revert main.c
	mv	-f	../src/main.bk		../src/main.c

	echo "Build Num: $build_num"
	echo "Build OK: $build_ok"
	echo "Build Failed: $build_failed"
}

#get_list
build_default
build_example interface.txt
build_example application.txt