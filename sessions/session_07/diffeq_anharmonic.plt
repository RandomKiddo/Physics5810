# plot file for diffeq_oscillations
set timestamp

set title 'Oscillations'

# simple plot versus time
pi = 3.141592653589793
k = (2.*pi)**2
m = 1
omega = sqrt(k/m)
set xlabel 't'
set ylabel 'y(t)'
plot "diffeq_oscillations.dat" using ($1):($2) title 'p=?' with lines 
#plot "diffeq_oscillations.dat" using ($1):($2) title 'p=?' with lines # , \
#  (1/omega)*sin(omega*x)

set timestamp

set xlabel 't'
set ylabel 'x(t)'
set title 'p=4 Anharmonic Oscillator x(t) vs. t'

set key top right

set grid

# Plot all three blocks in ONE command using the block selection syntax
# every :::0::0  means "Select Block 0"
# every :::1::1  means "Select Block 1"
# every :::2::2  means "Select Block 2"

plot "diffeq_oscillations2.dat" every :::0::0 with lines lw 2 lc "blue" title 'x0=0, v0=1', \
     "diffeq_oscillations2.dat" every :::1::1 with lines lw 2 lc "red"  title 'x0=1, v0=0', \
     "diffeq_oscillations2.dat" every :::2::2 with lines lw 2 lc "forest-green" title 'x0=1, v0=1'

set xrange[0:15]

set terminal pdfcairo enhanced color font "Times New Roman, 10'
set output 'p=4.pdf'
replot
set output