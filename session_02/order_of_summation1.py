#************************************************************************ 
#  file: order_of_summation1.py
# 
#  Script to demonstrate that the order of summation of even positive
#   numbers matters
#
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#               Ralf Bundschuh  bundschuh.2@osu.edu
#
#  Revision history:
#      26-Dec-2008  original Python version from demo1.cpp
#      01-Jan-2011  updated, renamed version
#      21-Dec-2021  converted to python3
#
#  Notes:
#   * An example to try to understand summing upward vs. summing
#      downward.  Add a small number eps (slightly below single-precision
#      machine precision) many times to 1.  It makes a big difference
#      (in single precision) whether you do 1 + eps + eps + ... or
#      eps + eps + ... + 1.
#
#
#   * First pass: no function definitions
#   * Python has double precision ONLY
#   * Here is the C++ output with eps=5e-8 added 10^7 time:
#
#                           1+eps+eps+...   eps+eps+...+1
#        single precision:  1.0000000000    1.5323836803
#        double precision:  1.4999999992    1.4999999999
#
#  To do:
#
#*************************************************************************

num_eps = 10000000	# number of times to add eps to 1 
eps_dp = 5.e-8	# double precision small increment 

sum_first_dp = 1. # adding 1 first (double precision) 
sum_last_dp = 0.  # adding 1 at the end (double precision) 

print('Adding small numbers many times to a big number:\n')

# add small numbers (in single or double precision) num_eps times
for i in range(0, num_eps):
    sum_first_dp += eps_dp
    sum_last_dp += eps_dp

sum_last_dp += 1.		# add 1 at the end

print('                   1+eps+eps+...  eps+eps+...+1  ')
print('double precision:  %.10f    %.10f' % (sum_first_dp, sum_last_dp))

