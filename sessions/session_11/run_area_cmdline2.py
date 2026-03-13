#!/usr/bin/env python 
#
#  file: run_area_cmdline2.py
#
#  This python script runs the C++ code area_cmdline for a sequence
#   of values that are hardcoded in the script.  The output is to
#   the screen.  Here the ranges are specified from numpy functions.
#
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#               Ralf Bundschuh  bundschuh.2@osu.edu
#
#  Revision history:
#      28-Dec-2010  original version from run_area_cmdline1.py
#      31-Dec-2021  converted to python 3
#
#  Notes:  
#   * run with: "python3 run_area_cmdline2.py"
#   * should check the return code to make sure it worked!
#   * could use Popen instead of call
#   * pass a full string to the shell with the first method below
#      or pass a list of arguments without "shell=True".
#  
#*************************************************************************
from subprocess import call
import numpy   # could use "from numpy import *" to avoid typing numpy

# Define the inputs at the top, so they are easy to find and change
value_list1 = numpy.linspace(1,2,num=11)   # num chosen so nicely spaced
value_list2 = numpy.arange(2.,0.,-0.25)

# Ok, let's do it . . .
print("\nUsing functions from numpy to specify radii.")

print("\nFirst try a list of evenly spaced numbers from linspace:")
for radius in value_list1:    # don't forget the colon!
  my_command = "./area_cmdline.x " + str(radius)  # convert radius to a string
  call(my_command, shell=True)    # pass  "my_command" to be executed

print("\nNow try a list using arange:")
for radius in value_list2:    # don't forget the colon!
  my_command = ["./area_cmdline.x", str(radius)]  # convert radius to a string
  call(my_command)

#*************************************************************************
