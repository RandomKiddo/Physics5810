#!/usr/bin/env python 
#
#  file: run_area_cmdline3.py
#
#  This python script runs the C++ code area_cmdline for a sequence
#   of values that are hardcoded in the script.  The output is processed
#   to convert it to a nice table.
#
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#               Ralf Bundschuh  bundschuh.2@osu.edu
#
#  Revision history:
#      28-Dec-2010  original version based on 
#      31-Dec-2021  converted to python 3
#
#  Notes:  
#   * run with: "python3 run_area_cmdline3.py"
#  
#*************************************************************************
from subprocess import Popen,PIPE
from re import findall
from operator import itemgetter

# Define the inputs at the top, so they are easy to find and change
value_list1 = [1, 10, 100]
value_list2 = [1.0, 0.5, 0.25]

my_filename = "test.file"

# Ok, let's do it . . .
print("\nOutput is to", my_filename, ". . .")

tmp_file = open (my_filename,'w')
for radius in value_list1:    # don't forget the colon!
  my_command = "./area_cmdline.x " + str(radius)  # convert radius to a string
  my_pipe = Popen(my_command, shell=True, stdout=tmp_file)  

for radius in value_list2:    # don't forget the colon!
  my_command = "./area_cmdline.x " + str(radius)  # convert radius to a string
  my_pipe = Popen(my_command, shell=True, stdout=tmp_file)  

print("All done!")

tmp_file.close()   # all done, close the file

print("\nNow try it without files!")
my_output = []   # start with an empty list
for radius in (value_list1 + value_list2):   
  my_command = "./area_cmdline.x " + str(radius)  # same command as before
  # We're sending no input to communicate and keeping the first element
  #  of the tuple that is returned.  Then we append it to the my_output string.
  my_output.append(Popen(my_command, shell=True, stdout=PIPE).communicate()[0])  

# At this stage we have a list of all of the output in the string my_output
print(" Here is what the output list looks like:")
print(my_output, "\n")

# Step through the output and pull out the radius and area values
print(" radius          area  "); print("-------------------------")
for entry in my_output:
  # pull out the two numbers in each entry (if no words, this would be easier!!)
  my_matches = findall("\d+\.*\d*",entry.decode('utf-8'))  # 1+ digits, 0+ periods, 0+ digits
  radius = float(my_matches[0]); area = float(my_matches[1])

  # Here is the old way of formatting
  print(' %6.2f  %12.3f ' % (radius, area))
  # Here is the new way (for newer versions of Python)
  #  print(' {0:6.2f}  {1:12.3f}'.format(radius, area))

# Step through the output and gather all the radius and area values
radii = [];  areas = [];
for entry in my_output:
  # pull out the two numbers in each entry (if no words, this would be easier!!)
  my_matches = findall("\d+\.*\d*",entry.decode('utf-8'))
  radii.append(float(my_matches[0])); areas.append(float(my_matches[1]))

print("\n radius          area  "); print("-------------------------")
for radius,area in zip(radii,areas):
  print(' {0:6.2f}  {1:12.3f}'.format(radius, area))

# Now try sorting with itemgetter
print("\n Now we sort by radius:")
print("\n radius          area  "); print("-------------------------")
for radius,area in sorted(zip(radii,areas),key=itemgetter(0)):
  print(' {0:6.2f}  {1:12.3f}'.format(radius, area))

#*************************************************************************
