#!/bin/bash
str="peripheral_"`date +"%Y%m%d_%H%M%S"`
echo "peripheral image files folder:"$str
mkdir $str
mkdir $str/log

function build_default
{
	#build km0
	cd ../../project_lp
	#remove *_all.bin if exist
	rm	-f	asdk/image/*_all.bin
	
	echo "build km0..."
	{
		make clean
		make
	}>>../project_hp/tools/$str/log/km0.txt 2>&1
	
	#copy image
	if [ -f "asdk/image/km0_image2_all.bin" ]; then
		cp	-f	asdk/image/*_all.bin			../project_hp/tools/$str
		echo "km0 ok">>../project_hp/tools/$str/log/build_result.txt 2>&1
		echo "km0 build ok"
	else
		echo "km0 failed">>../project_hp/tools/$str/log/build_result.txt 2>&1
		echo "km0 build failed"
	fi

	#build km4
	cd ../project_hp
	#remove *_all.bin if exist
	rm	-f	asdk/image/*_all.bin
	
	echo "build km4..."
	{
		make clean
		make
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
	find ../../../example_sources -name "src" > example_list.txt
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
	mv	-f	../../../src/src_hp/main.c		../../../src/src_hp/main.bk

	while read -r example
	do 
		let "build_num+=1"
		read -r new_example_name
		#get example path:
		from_path=${example}
		example_name=${from_path##*/}
		Is_LCDC=${from_path%/*}
		Is_LCDC=${Is_LCDC%/*}
		Is_ir=${Is_LCDC}
		Is_LCDC=${Is_LCDC%/*}
		Is_LCDC=${Is_LCDC##*/}
		Is_ir=${Is_ir##*/}


		#copy *.c *.h
		if [ "$Is_LCDC" = "LCDC" ]; then
			#backup Makefile
			mv	-f	../../../src/src_hp/Makefile		../../../src/src_hp/Makefile_bk 
			cp	-f	$from_path/src_hp/*.*		../../../src/src_hp
			cp	-f	$from_path/src_hp/Makefile		../../../src/src_hp
			if [ "$new_example_name" = "LCDC_SOFTLAYER_HandWriting" ]; then
				#backup LCDConf_RGB_6bit_eval.c
				mv	-f	../../../../../component/common/ui/emwin/Sample/rtl8721d/Config/LCDConf_RGB_6bit_eval.c		../../../../../component/common/ui/emwin/Sample/rtl8721d/Config/LCDConf_RGB_6bit_eval.bk
				cp	-f	$from_path/Config/LCDConf_RGB_6bit_eval.c		../../../../../component/common/ui/emwin/Sample/rtl8721d/Config
			fi
		elif [ "$example_name" = "rdp" ]; then
			#backup secure_src.c
			mv	-f	../../../../../component/soc/realtek/amebad/img3/secure_src.c		../../../../../component/soc/realtek/amebad/img3/secure_src.bk
			cp	-f	$from_path/src/main.c		../../../src/src_hp
			cp	-f	$from_path/src/secure_src.c		../../../../../component/soc/realtek/amebad/img3
		elif [ "$Is_ir" = "ir" ]; then
			#backup Makefile
			mv	-f	../../../src/src_hp/Makefile		../../../src/src_hp/Makefile_bk
			cp	-f	$from_path/src/Makefile		../../../src/src_hp
			cp	-f	$from_path/src/*.*		../../../src/src_hp
		else
			cp	-f	$from_path/src/*.*		../../../src/src_hp
		fi
		
		
		if [ -d "$from_path/inc/" ]; then
			cp	-f	$from_path/inc/*.h		../../../src
		fi
		
		#remove *_all.bin if exist
		rm	-f	../asdk/image/*_all.bin

		#make file
		cd ..
		( make )>>tools/$str/log/$new_example_name.txt 2>&1
		cd tools

		#copy image to example file
		if [ -f "../asdk/image/km0_km4_image2.bin" ]; then
			mv	-f	../asdk/image/km0_km4_image2.bin			$str/$to_path/$new_example_name.bin
			let "build_ok+=1"
			echo "$example ok">>$str/log/build_result.txt 2>&1
			echo "$example ok"
		else
			let "build_failed+=1"
			echo "$example failed">>$str/log/build_result.txt 2>&1
			echo "$example failed"
		fi

		rm	-f	../../../src/src_hp/*.c
		rm	-f	../../../src/src_hp/*.h
		rm	-f	../../../src/src_hp/*.a
		rm	-f	../../../src/src_hp/*.o
		rm	-f	../../../src/src_hp/*.d
		rm	-f	../../../src/src_hp/*.i
		rm	-f	../../../src/src_hp/*.s
		rm	-f	../../../src/src_hp/*.su
		rm	-f	../../../src/src_hp/*.bmp
		rm	-f	../../../src/src_hp/*.txt
		

	done <  $list_file

	#revert main.c
	mv	-f	../../../src/src_hp/main.bk		../../../src/src_hp/main.c
	
	#revert secure_src.c for rdp demo
	if [ "$example_name" = "rdp" ]; then
		rm	-f	../../../../../component/soc/realtek/amebad/img3/secure_src.c
		mv	-f	../../../../../component/soc/realtek/amebad/img3/secure_src.bk		../../../../../component/soc/realtek/amebad/img3/secure_src.c
	fi
	#revert Makefile for LCDC demo
	if [ "$Is_LCDC" = "LCDC" ]; then
		rm	-f	../../../src/src_hp/Makefile
		mv	-f	../../../src/src_hp/Makefile_bk		../../../src/src_hp/Makefile
		if [ "$new_example_name" = "LCDC_SOFTLAYER_HandWriting" ]; then
			echo "$new_example_name"
			#revert LCDConf_RGB_6bit_eval.c
			rm	-f	../../../../../component/common/ui/emwin/Sample/rtl8721d/Config/LCDConf_RGB_6bit_eval.c
			mv	-f	../../../../../component/common/ui/emwin/Sample/rtl8721d/Config/LCDConf_RGB_6bit_eval.bk		../../../../../component/common/ui/emwin/Sample/rtl8721d/Config/LCDConf_RGB_6bit_eval.c
		fi
	elif [ "$Is_ir" = "ir" ]; then
		#revert Makefile
		rm	-f	../../../src/src_hp/Makefile
		mv	-f	../../../src/src_hp/Makefile_bk		../../../src/src_hp/Makefile
	fi

	echo "Build Num: $build_num"
	echo "Build OK: $build_ok"
	echo "Build Failed: $build_failed"
}

#get_list
build_default
build_example interface.txt
#build_example lcdc.txt