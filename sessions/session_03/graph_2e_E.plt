f(x) = m*x+b
fit [0.5:2.25] f(x) "integ6.dat" using 1:6 via m, b


plot "integ2.dat" using 1:2 title 'Trapezoid Rule',\
"integ2.dat" using 1:3 title 'Simpson''s Rule',\
"integ2.dat" using 1:4 title 'Gaussian',\
"integ6.dat" using 1:6 title 'Three-Eight'

# set logscale

set xlabel 'log10(N)'
set ylabel 'log10(Relative Error)'
set title 'Single-Precision Integration of exp(-x)'

set xrange[0.01:2.7]
set yrange[-10:-1]

set timestamp

set key top right

set terminal pdfcairo enhanced color font "Times New Roman"
set out "graph_2e_E.pdf" 

replot
set output
unset output

print '3-8 Slope: ', m

quit
