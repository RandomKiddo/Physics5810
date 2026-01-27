"""
  file: area1.py

  This program calculates the area of a circle, given the radius.

  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu

  Revision history:
      26-Dec-2008  original version, modified from area0.py
      20-Dec-2021  converted to python 3

  Notes:  
   * run program using "python3 area1.py"
   * conversion from area0.py:
        * use three quotes for multiline comments instead of #
        * use the value of pi defined in the math module
        * do conversion from raw_input to float in one line

  To do:
   * output the answer with higher precision (more digits)
   * split the calculation into a function (def)
   * output to a file (and/or input from a file)
"""

import math    # read in the definitions from the math module

# Just do it!

# convert the input to a float right away
radius = float(input('Enter the radius of a circle: '))

area = math.pi * radius**2    # area formula A = pi R^2

# partially formatted print: compare %f to %e
print('radius = %f, area = %f' % (radius, area))
print('radius = %e, area = %e' % (radius, area))

# now some additional digits (%.nf means n digits after decimal)
print('radius = %.4f, area = %.8f' % (radius, area))

# That's all, folks!
