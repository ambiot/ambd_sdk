#!/usr/bin/env python

import sys
import subprocess
import os


readelf = '../toolchain/cygwin/asdk-5.4.1/cygwin/newlib/bin/arm-none-eabi-readelf';
axf_file = 'lib/rom_acut/target_rom.axf'

if os.path.exists('rom_symbol.txt'):
	os.remove('rom_symbol.txt')
file=open('rom_symbol.txt', 'w')

#gRamStart_pos = 0x10000bc0  #rom v0
#rom v1
gRamStart_pos = 0x00082000
gFlashStart_pos = 0x08000000

command = readelf + " -W -s " + axf_file + " | sort -k 2";

proc = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)

print >> file, "SECTIONS"
print >> file, "{"
for line in proc.stdout:
#	print line
	items = filter(None, line.strip().split(' '))

        num = len(items)
        if  num >= 8  :
	    type = items[4]
	    if type.lower() == 'global' or type.lower() == 'weak' : 
	    	address = int(items[1], 16)
		if address < gRamStart_pos and (address & gFlashStart_pos) == 0:
            		symbol = items[7]
                	print >> file, "    " + symbol + " = " + hex(address) + ";";
                	#print "    " + symbol + " = " + hex(address) + ";";

print >> file, "}"

file.close()
