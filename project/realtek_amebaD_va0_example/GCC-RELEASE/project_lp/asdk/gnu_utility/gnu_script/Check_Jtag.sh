#!/bin/sh

#===============================================================================
CURRENT_UTILITY_DIR=$(pwd)
GDBSCPTFILE="./gnu_utility/gnu_script/rtl_gdb_jtag_boot_com.txt"

#===============================================================================
RLXSTS=$(ps -W | grep "rlx_probe_driver.exe" | grep -v "grep" | wc -l)
echo $RLXSTS
JLKSTS=$(ps -W | grep "JLinkGDBServer.exe" | grep -v "grep" | wc -l)
echo $JLKSTS

#===============================================================================
#make the new string for being written
if [ $RLXSTS -gt 0 ]
then
	echo "probe get"
	#-------------------------------------------
	LINE_NUMBER=$(grep -n "monitor reset " $GDBSCPTFILE | awk -F":" '{print $1}')
	DEFAULT_STR=$(grep -n "monitor reset " $GDBSCPTFILE | awk -F":" '{print $2}')
	#echo $LINE_NUMBER
	echo $DEFAULT_STR
	if [ "x$LINE_NUMBER" != "x" ]
	then
		STRLEN_DFT=$(expr length "$DEFAULT_STR")
		DEFAULT_STR="#monitor reset 1"
		echo $DEFAULT_STR               
		#-------------------------------------------
		SED_PARA="$LINE_NUMBER""c""$DEFAULT_STR"
		sed -i "$SED_PARA" $GDBSCPTFILE
	fi
	#===========================================
	LINE_NUMBER=$(grep -n "monitor sleep " $GDBSCPTFILE | awk -F":" '{print $1}')
	DEFAULT_STR=$(grep -n "monitor sleep " $GDBSCPTFILE | awk -F":" '{print $2}')
	#echo $LINE_NUMBER
	echo $DEFAULT_STR
	if [ "x$LINE_NUMBER" != "x" ]
	then
		STRLEN_DFT=$(expr length "$DEFAULT_STR")
		DEFAULT_STR="#monitor sleep 20"
		echo $DEFAULT_STR               
		#-------------------------------------------
		SED_PARA="$LINE_NUMBER""c""$DEFAULT_STR"
		sed -i "$SED_PARA" $GDBSCPTFILE
	fi
else

if [ $JLKSTS -gt 0 ]
then
	echo "jlink get"
	#-------------------------------------------
	LINE_NUMBER=$(grep -n "monitor reset " $GDBSCPTFILE | awk -F":" '{print $1}')
	DEFAULT_STR=$(grep -n "monitor reset " $GDBSCPTFILE | awk -F":" '{print $2}')
	#echo $LINE_NUMBER
	echo $DEFAULT_STR
	if [ "x$LINE_NUMBER" != "x" ]
	then
		STRLEN_DFT=$(expr length "$DEFAULT_STR")
		DEFAULT_STR="monitor reset 1"
		echo $DEFAULT_STR               
		#-------------------------------------------
		SED_PARA="$LINE_NUMBER""c""$DEFAULT_STR"
		sed -i "$SED_PARA" $GDBSCPTFILE
	fi
	#===========================================
	LINE_NUMBER=$(grep -n "monitor sleep " $GDBSCPTFILE | awk -F":" '{print $1}')
	DEFAULT_STR=$(grep -n "monitor sleep " $GDBSCPTFILE | awk -F":" '{print $2}')
	#echo $LINE_NUMBER
	echo $DEFAULT_STR
	if [ "x$LINE_NUMBER" != "x" ]
	then
		STRLEN_DFT=$(expr length "$DEFAULT_STR")
		DEFAULT_STR="monitor sleep 20"
		echo $DEFAULT_STR               
		#-------------------------------------------
		SED_PARA="$LINE_NUMBER""c""$DEFAULT_STR"
		sed -i "$SED_PARA" $GDBSCPTFILE
	fi
fi
fi

#===============================================================================
