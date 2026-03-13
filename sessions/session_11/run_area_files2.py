#!/usr/bin/env python 
#
#  file: run_area_files2.py
#
#  This python script runs the C++ code area_files for a sequence
#   of values that are hardcoded in the script.  The output is to
#   the screen.  Here the ranges are specified from numpy functions.
#
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#               Ralf Bundschuh  bundschuh.2@osu.edu
#
#  Revision history:
#      28-Dec-2010  original version from run_area_cmdline2.py
#      31-Dec-2021  converted to python 3
#
#  Notes:  
#   * run with: "python3 run_area_files2.py"
#   * should check the return code to make sure it worked!
#   * could use Popen instead of call
#   * pass a full string to the shell with the first method below
#      or pass a list of arguments without "shell=True".
#  
#*************************************************************************
from subprocess import call
import numpy   # could use "from numpy import *" to avoid typing numpy
from os import rename

# Define the inputs at the top, so they are easy to find and change
value_list1 = numpy.linspace(1,2,num=11)   # num chosen so nicely spaced
value_list2 = numpy.arange(1.,0.,-0.25)

# Ok, let's do it . . .
print("\nUsing functions from numpy to specify radii in an input file.")

# First we specify the file name and then open it in the next line 
input_filename = "area_files.inp"   
input_file = open (input_filename,'w')  # we'll refer to the file as input_file

# Define strings in quotes for comment lines. We use \n to get new lines.
cmt_line1 = "# This is an input file for the area_files.cpp program\n"
cmt_line2 = "#  After five lines with #'s, any number of radii are given\n"
cmt_line3 = "#  one to a line, with any alignment and formatting.\n"
cmt_line4 = "#\n"

# Write the comment lines to the file (referred to by input_file)
input_file.write(cmt_line1)
input_file.write(cmt_line2)
input_file.write(cmt_line3)
input_file.write(cmt_line4)

hdr_line1 = "#   radius\n"    # a header line
input_file.write(hdr_line1)

for radius in value_list1:    # step through radii; don't forget the colon!
   input_file.write(str(radius)+'\n')  # "+" concatenates the strings

for radius in value_list2:    # step through radii; don't forget the colon!
   input_file.write(str(radius)+'\n')

input_file.close()    # all done, close the input file

my_command = "./area_files.x "   # the C++ executable
print("\n Now running area_files ...")
call(my_command, shell=True)    # pass  "my_command" to be executed

rename("area_files.out","area_files.out2")

#*************************************************************************
