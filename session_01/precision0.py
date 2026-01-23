#  file: precision0.py
#
#  This program determines machine precision e 
#   (the smallest e for which 1 + e does not equal 1)
#  Be careful when interpreting the output!                     
#                                                                     
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#
#  Revision history:
#      26-Dec-2008  original python version, from precision.cpp
#      20-Dec-2021  converted to python 3
#
#  Notes:  
#   * run with:  "python3 precision0.py"
#   * adapted from: "Projects in Computational Physics" by Landau and Paez  
#             copyrighted by John Wiley and Sons, New York               
#             code copyrighted by RH Landau                           
#   * comment: very crude program which produces lots of output
#  
#*************************************************************************

max_iterations = 100   # automatically an integer

eps = 1.0  		# starting value (automatically a float)
one = 1.0 

for i in range(0, max_iterations, 1):
    eps /= 2.0 		# divide by a fixed factor 
    test = one + eps 	

    print(test, repr(test), repr(eps))
