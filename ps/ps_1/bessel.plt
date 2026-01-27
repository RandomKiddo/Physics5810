set timestamp

plot "bessel.dat" using 1:4 title 'Relative Error'

set logscale

set xlabel 'x'
set ylabel 'Relative Error'
set title 'Relative Error of j10(x) Via Up and Down Recursion'

set key bottom left

set xrange[0:100]
set yrange[1e-17:10]

set terminal pdfcairo enhanced color font "Times New Roman, 10'
set output 'bessel.pdf'
replot
set output