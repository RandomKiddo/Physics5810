#  file: flows1.py
#
#  This program determines overflow and underflow limits
#   with output to file.                     
#                                                                     
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#
#  Revision history:
#      26-Dec-2008  original Python version from flows2.cpp
#      20-Dec-2021  converted to python 3
#
#  Notes:  
#   * run with:  "python3 flows1.py"
#   * adapted from: "Projects in Computational Physics" by Landau and Paez  
#             copyrighted by John Wiley and Sons, New York               
#             code copyrighted by RH Landau                           
#   * comment: very crude program 
#   * dumps output to flows1_py.out
#  
#*********************************************************************# 

max_iterations = 2000
                
under = 1.;    # starting values 
over = 1.;	

my_out = open('flows1_py.out', 'w')  # open a file flows1_py.out for writing

my_out.write('# Output from flows1.py\n')

for i in range(0, max_iterations, 1):
    under /= 2.0;		# divide by two 
    over *= 2.0;		# multiply by two 
    
    # print '%d  under: %.5e  over: %.5e' % (i+1, under, over)
    my_out.write(' %4d  under: %.5e  over: %.5e \n' % (i+1, under, over))

my_out.close()
