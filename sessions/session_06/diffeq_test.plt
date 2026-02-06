# plot file for diffeq_test_exp_back
set timestamp

set xlabel 't'
set ylabel 'x(t)'

set title 'Comparison of RK4 and Exact for Coupled DE Harmonic Oscillator'


#plot \
#  "diffeq_test.dat" using ($1):($2) title 'Euler', \
#  "diffeq_test.dat" using ($1):($3) title '4th order Runge-Kutta', \
#  "diffeq_test.dat" using ($1):($4) title 'exact'

# set logscale 
# set xrange[:3]

set xrange[0:10]
set yrange[-1.1:1.1]

set key top right

# plot \
#   "diffeq_test2.dat" using ($1):(abs(($2-$4)/$4)) title 'Euler Error', \
#   "diffeq_test2.dat" using ($1):(abs(($3-$4)/$4)) title 'RK4 Error', \
#   "diffeq_test3.dat" using ($1):(abs(($2-$4)/$4)) title 'Euler Error h/10', \
#   "diffeq_test3.dat" using ($1):(abs(($3-$4)/$4)) title 'RK4 Error h/10', \

# f(x) = a * x**b
# fit [1e-6:1e-2] f(x) "diffeq_h_scaling3.dat" using ($1):($3) via a, b

# plot "diffeq_h_scaling3.dat" using ($1):($3) title 'RK2 Error', \
# f(x) title 'Fit' 

plot "diffeq_test7.dat" using ($1):($2) title 'RK4', \
"diffeq_test7.dat" using ($1):($4) title 'Exact'

set terminal pdfcairo enhanced color font "Times New Roman, 10"
set output "harmonic_oscillator.pdf"
replot
set output