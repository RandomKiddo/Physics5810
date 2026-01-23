#  file: bessel_final.py
#
#  Spherical Bessel functions via up and down recursion      
#                                                                     
#
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#               Ralf Bundschuh  bundschuh.2@osu.edu
#
#  Revision history:
#      26-Dec-2008  original version, from bessel_final.cpp
#      21-Dec-2021  converted to python 3
#
#  Notes:  
#   * adapted from: "Projects in Computational Physics" by Landau and Paez  
#             copyrighted by John Wiley and Sons, New York               
#             code copyrighted by RH Landau  
#   * added relative error calculation and output
#   * data saved as: x y1 y2 rel_error log10(x) log10(rel_error)                         
#  
#************************************************************************

from scipy import special
from numpy import *
from math import *


# global constants  
xmax = 100.0	# max of x  
xmin = 0.1	# min of x >0  
step = 0.1	# delta x  
order = 10		# order of Bessel function 
start = 50		# used for downward algorithm 


# function using downward recursion  
def down (x, n, m):
    
    j = zeros(m + 2)		# array to store Bessel functions 
    j[m + 1] = j[m] = 1.		# start with "something" (choose 1 here) 
    for k in range(m, 0, -1):  
        j[k - 1] = ((2.*double(k) + 1.) / x) * j[k] - j[k + 1]  # recur. rel.
  
    scale = (sin(x) / x) / j[0]	# scale the result   
    return (j[n] * scale)


#------------------------------------------------------------------ 

# function using upward recursion  
def up (x, n):

    up3 = 0.
    up1 = sin(x) / x  # start with lowest order 
    up2 = ( sin(x) - x * cos(x) ) / x**2  # next order
  
    for k in range(1, n):
        up3 = ((2.*double(k) + 1.) / x) * up2 - up1	# recurrence relation  
        up1 = up2
        up2 = up3
        
    return up3

#********************************************************************
  
my_out = open('bessel_final2.dat', 'w')
my_out.write('# spherical bessel functions with l = %d \n' % (order) )
my_out.write('#   x        jdown(x)         jup(x)       rel. error      ')
my_out.write('log10(x)    log10(rel.err.) \n')



x = xmin
while (x <= xmax):

    ans_down = down (x, order, start)
    ans_up = up (x, order)

    # we calculate the absolute value of the relative error
    rel_error = abs(ans_down - ans_up) / (abs(ans_down) + abs(ans_up))
    if (rel_error > 1.e-20):
	      log_rel_error = log10 (rel_error)
    else:
	      log_rel_error = -20.

    my_out.write(' %f  %13.6e  %13.6e  %13.6e  %13.6e  %13.6e  \n'  
        % (x, ans_down, ans_up, rel_error, log10(x), log_rel_error) )
    
    x += step
    
print('data stored in bessel_final2.dat.')
my_out.close()

#------------------------end of main program----------------------- 
