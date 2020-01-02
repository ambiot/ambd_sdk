#!/usr/bin/env python

import sys
import subprocess
import os
import re

def obj_list_gen():
	if os.path.exists('obj_list.map'):
		os.remove('obj_list.map')
	file=open('obj_list.map', 'w')

	parse_file=open('../image/ram_size.txt', 'r')
	all_lines = parse_file.readlines()

	for line in all_lines:
		item = filter(None, line.strip().split('\t'))
		num = len(item)
		#print item
		#print num

		line_strip = (line.strip())
		item_split_component=line_strip.split('component')
	
		found=line.find('component')
		if found > 0:
			print >> file, 'component' + item_split_component[1]
		else:
			if num == 1:
				print >> file, item[0]

	parse_file.close()
	file.close()
	return


def parse_text_map(str):
	if os.path.exists('parse_text.map'):
		os.remove('parse_text.map')
	file=open('parse_text.map', 'w')

	parse_file = '../image/text.map'
	
	if (str=='flash'):
		command = "grep" + " 0x080 " +  parse_file + " | grep '\.o$'";
	else:
		command = "grep -i" + " -e 0x1000 -e 0x1001 -e 0x1002 -e 0x1003 " +  parse_file + " | grep '\.o$'";
	#print command
	
	proc = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
	
	for line in proc.stdout:
		items = filter(None, line.strip().split(' '))
		
		num = len(items) 
		if num == 3 :
			print >> file, items[0] + " " + items[1] + " " + items[2] 
		if num == 4 : 
			print >> file, items[1] + " " + items[2] + " " + items[3]

	file.close()
	return

def parse_text_map_2(str):
	if os.path.exists('parse_text_2.map'):
		os.remove('parse_text_2.map')
	file=open('parse_text_2.map', 'w')

	parse_file = 'parse_text.map'
	first = 1
	size = 0
	
	if (str=='flash'):
		command = "grep" + " 0x080 " +  parse_file + " | grep '\.o$'";
	else:
		command = "grep -i" + " -e 0x1000 -e 0x1001 -e 0x1002 -e 0x1003 " +  parse_file + " | grep '\.o$'";
	#print command
	
	proc = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
	
	for line in proc.stdout:
		items = filter(None, line.strip().split(' '))
		
		if first == 1 :
			line_last = line
			size = int(items[1], 16)
			first = 0
			continue
		
		items_last = filter(None, line_last.strip().split(' '))
		
		if  items[2] == items_last[2] :
			size = size + int(items[1], 16)
		else :
			#print items_last[0] + " " + hex(size) + " " + items_last[2]
			split_line=os.path.split(items_last[2])
			print >> file, hex(size) + " " + split_line[1]
			
			size = int(items[1], 16)
			line_last = line
	file.close()
	return

def merge_size_and_objs():
	if os.path.exists('parse_text_obj_size_1.map'):
		os.remove('parse_text_obj_size_1.map')
	file_result=open('parse_text_obj_size_1.map', 'w')

	parse_file = '../image/obj_list.txt'
	command = "grep '\.o$' " +  parse_file;
	last_item='none'
	last_obj_path='none'
	obj_size=0
	file_size=0
	image_size=0
	#print command
	
	proc = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
	file=open('parse_text_2.map', 'r')
	all_lines = file.readlines()

	for line in proc.stdout:
		items = filter(None, line.strip().split(' '))
		items_split=os.path.split(items[0])
		file_size=0
		#print item_split

		line_strip = (line.strip())
		items_split_component=line_strip.split('component')
		items_split_test=line_strip.split('/', line_strip.count('/'))
		#print items_split_test

		obj_path=''
		for num in xrange(17):
			obj_path += items_split_test[num]+"/"
		#print obj_path
		
		# print pattern 1 #
		if (last_obj_path != obj_path):
			if (last_obj_path != 'none'):
				print >> file_result, "Total size hex: " + hex(obj_size) + " dec: %d"%obj_size
			print >> file_result, "============================================================================================"
			obj_size=0
		last_obj_path=obj_path

		# print pattern 2 #
		#if last_item != items_split[0]:
		#	if last_item != 'none':
		#		print >> file_result, "Total size hex: " + hex(obj_size) + " dec: %d"%obj_size 
		#	print >> file_result, "============================================================================================"
		#	obj_size=0
		#last_item=items_split[0]

		#print items[0]
		for line in all_lines:
			item = filter(None, line.strip().split(' '))
			if items_split[1] == item[1]:
				file_size=file_size+int(item[0],16)
		
		print >> file_result, hex(file_size) + "	" + items_split_component[1]
		obj_size = obj_size + file_size
		image_size=image_size+file_size

	print >> file_result, "Total size hex: " + hex(obj_size) + " dec: %d"%obj_size 
	print >> file_result, "============================================================================================"
	print >> file_result, "Image size hex: " + hex(image_size) + " dec: %d"%image_size 
	file_result.close();
	file.close()
	return

def merge_size_and_objs_2(str):
	if (str=='flash'):
		des_file='parse_text_obj_size.map'
	else:
		des_file='parse_text_obj_size_ram.map'

	if os.path.exists(des_file):
		os.remove(des_file)
	file_result=open(des_file, 'w')


	parse_file = 'obj_list.map'
	command = "grep -e '\.o$' -e '=================' " +  parse_file;
	obj_size=0
	file_size=0
	image_size=0
	first=1
	
	proc = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
	file=open('parse_text_2.map', 'r')
	all_lines = file.readlines()

	for line in proc.stdout:
		line_strip = (line.strip())
		file_size=0

		found=line.find('component')
		if (found < 0):
			if (first == 0):
				print >> file_result, "\nTotal:\n" + hex(obj_size) + "\t%d"%obj_size 
			else:
				print >> file_result, "hex\t" + "dec\t" + "file" 
				first=0
			print >> file_result, line_strip
			obj_size=0
		else:
			items = filter(None, line.strip().split(' ')) 
			items_split=os.path.split(items[0]) 

			for line_size in all_lines:
				item = filter(None, line_size.strip().split(' '))
				if items_split[1] == item[1]:
					file_size=file_size+int(item[0],16)

			print >> file_result, hex(file_size) + "\t" + "%d"%file_size + "\t" + line_strip
			obj_size = obj_size + file_size
			image_size=image_size+file_size

	print >> file_result, "\nImage size:\n" + hex(image_size) + "\t%d"%image_size 
	file_result.close()
	file.close()
	return

obj_list_gen()

# flash code and data
parse_text_map('flash')
parse_text_map_2('flash')
merge_size_and_objs_2('flash')

#ram code and data
parse_text_map('ram')
parse_text_map_2('ram')
merge_size_and_objs_2('ram')

#remove temp files
os.remove('obj_list.map')
os.remove('parse_text.map')
os.remove('parse_text_2.map')
