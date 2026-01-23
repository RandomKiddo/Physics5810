#  file: area0.py
#
#  This program calculates the area of a circle, given the radius.
#
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#
#  Revision history:
#      26-Dec-2008  original version, translated from area.cpp
#      20-Dec-2021  converted to python 3
#
#  Notes:  
#   * run program using "python3 area0.py"
#   * conversion from .cpp to .py:
#        * // --> # for comments on a single line
#        * drop the semicolons
#        * no variable declarations like int or double 
#        * radius**2 instead of radius*radius
#        * different functions for input and output
#
#  To do:
#   * output the answer with higher precision (more digits)
#   * split the calculation into a function (def)
#   * output to a file (and/or input from a file)
#
#*********************************************************************# 

pi = 3.141592653589793    # put in \pi by hand

answer = input('Enter the radius of a circle: ')  # answer is a string
radius = float(answer)   # convert to floating point number

area = pi * radius**2    # area formula; x**n is x to the n'th power

# simple printing (illustrates that either type of quotes can be used)
print('radius = ', radius, ', area = ', area)
print("radius = ", radius, ", area = ", area)
  
# That's all, folks!
