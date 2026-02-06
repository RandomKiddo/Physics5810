# plot file for diffeq_test_exp_back
set timestamp

set xlabel 'h'
set ylabel 'Relative Error'

set title 'Comparing Differential Equation Algorithms w/ Relative Error as h Scales'

set logscale 

set key bottom left

plot \
    "diffeq_h_scaling.dat" using ($1):($2) title 'Euler', \
    "diffeq_h_scaling.dat" using ($1):($3) title 'RK4'

set terminal pdfcairo enhanced color font "Times New Roman, 10"
set output "diffeq_test_scaling.pdf"
replot
set output