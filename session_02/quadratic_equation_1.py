#  file: quadratic_equation_1.py
# 
#  Program to calculate roots of a quadratic equation:
#      a*x^2 + b*x + c = 0
#   as an illustration of subtractive cancellation errors
#
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#               Ralf Bundschuh  bundschuh.2@osu.edu
#
#  Revision history:
#      27-Dec-2008  original Python version from quadratic_equation_1.cpp
#      21-Dec-2021  converted to python 3
#
#  Notes:
#   * Based on discussion in section 3.4 of Landau/Paez, "Computational
#      Physics"
#   * First pass: no subroutine, calculate all roots, read in a,b,c
#   * C++ version uses single precision to highlight the subtractive 
#       cancellations; Python has double precision only
#
#  To do:
#   * pick out the best roots
#   * make it into a subroutine
#
#************************************************************************ 

from math import *

print('Calculation of quadratic equation roots in double precision')

my_input = input('Enter a, b, c: [with spaces between, followed by <return>] ')
[a, b, c] = map(float,my_input.split())

print('a = %f, b = %f, c = %f \n' % (a, b, c))

disc = sqrt(b**2 - 4.*a*c)	# definition of discriminant

x1 = (-b + disc) / (2.*a)	# first root, standard formula 
x1p = -2.*c / (b + disc)	# first root, new formula 
x2 = (-b - disc) / (2.*a)	# second root, standard formula 
x2p = (-2.*c) / (b - disc)	# second root, new formula 

print('     first root             second root  ')
print(' %.16f  %.16f ' % (x1, x2))
print(' %.16f  %.16f ' % (x1p, x2p))


