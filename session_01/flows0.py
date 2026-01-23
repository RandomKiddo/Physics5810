#  file: flows0.py
#
#  This program determines overflow and underflow limits                     
#                                                                     
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#
#  Revision history:
#      26-Dec-2008  original Python version from flows2.cpp
#      20-Dec-2021  converted to python 3
#
#  Notes:  
#   * run with:  "python3 flows0.py"
#   * adapted from: "Projects in Computational Physics" by Landau and Paez  
#             copyrighted by John Wiley and Sons, New York               
#             code copyrighted by RH Landau                           
#   * comment: very crude program which produces lots of screen output
#   * to output to flows_py.out:  "python flows0.py > flows_py.out"
#  
#*********************************************************************# 

max_iterations = 2000
                
under = 1.;    # starting values 
over = 1.;	

for i in range(0, max_iterations, 1):   # or range(max_iterations)
    under /= 2.0;		# divide by two 
    over *= 2.0;		# multiply by two 
    print('%d  under: %.5e  over: %.5e' % (i+1, under, over))
