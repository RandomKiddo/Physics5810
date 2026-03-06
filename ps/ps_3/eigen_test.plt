#  file: eigen_test.plt 
#
#  Gnuplot plot file for eigen_test outputs
#  
#  Programmer:  Neil Ghugare    ghugare.1@osu.edu
# 
#  Revision history
#   2026-03-06  original version for PS3
#

# set time stamp and terminal output
set timestamp
set terminal pdfcairo enhanced color font "Times New Roman, 10" size 10,7
set output "wavefunctions.pdf" 

# No key needed
set nokey

# Limits
set xrange[0:6]
set yrange[0:1.5]

# For multiple plots on a singular pdf
set multiplot layout 2,2 title "Approximate Wavefunctions With Differing Basis Sizes, Green=Exact, b=1.0"

# Top left plot
set title "Basis Size = 1"
plot "wf_state0_dim1.dat" using 1:2 title 'Exact', \
     "wf_state0_dim1.dat" using 1:3 title 'Basis Size = 1'
set xlabel 'r'
set ylabel 'Reduced u(r)'

# Top right plot
set title "Basis Size = 5"
plot "wf_state0_dim5.dat" using 1:2 title 'Exact', \
     "wf_state0_dim5.dat" using 1:3 title 'Basis Size = 5'
set xlabel 'r'
set ylabel 'Reduced u(r)'

# Bottom left plot
set title "Basis Size = 10"
plot "wf_state0_dim10.dat" using 1:2 title 'Exact', \
     "wf_state0_dim10.dat" using 1:3 title 'Basis Size = 10'
set xlabel 'r'
set ylabel 'Reduced u(r)'

# Bottom right plot
set title "Basis Size = 20"
plot "wf_state0_dim20.dat" using 1:2 title 'Exact', \
     "wf_state0_dim20.dat" using 1:3 title 'Basis Size = 20'
set xlabel 'r'
set ylabel 'Reduced u(r)'

# Set the output
unset multiplot
set output