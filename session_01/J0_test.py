"""
  file: j0_test.py

  Python script to demonstrate use of the Bessel functions from
   the scipy scientific library.

  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu

  Revision history:
      12/28/09  original Python version, from j0_test.py 
      12/20/21  converted to python 3

  Notes:  
   * to learn more about the special functions in scipy:
      >>> from scipy import special
      >>> help(special)    # list special functions

   * One known value:  J0(5) = -1.775967713143382920e-01 
"""
#*********************************************************************

from scipy import special

x = 5.0   # just a random test value

answer = special.j0(x)   # see the scipy manual for details
answer2 = special.jn(0, x)  # more general

print('These answers should be accurate to about 16 significant figures.\n')
print('Using j0:  J0(%.2f) = %.20e' % (x, answer))
print('Using jn:  J0(%.2f) = %.20e' % (x, answer2))
