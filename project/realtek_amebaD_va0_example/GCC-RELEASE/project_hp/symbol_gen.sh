#!/bin/bash 

cd asdk/config

./export_symbol.py > ../lib/rom_symbol_v01.txt
./export_symbol_iar.py > ../lib/rom_symbol_v01_iar.icf

cd -
