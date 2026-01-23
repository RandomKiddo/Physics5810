f(x) = m*x + b
fit [0.4:2.25] f(x) "integ2.dat" using 1:2 via m, b

g(x) = n*x + c
fit [0.4:1.2] g(x) "integ2.dat" using 1:3 via n, c

h(x) = p*x + d
fit [2.3:2.7] h(x) "integ2.dat" using 1:2 via p, d

j(x) = q*x + f
fit [1.5:2.6] j(x) "integ2.dat" using 1:3 via q,f

plot "integ2.dat" using 1:2 title 'Trapezoid Rule',\
"integ2.dat" using 1:3 title 'Simpson''s Rule',\
"integ2.dat" using 1:4 title 'Gaussian',\
f(x) title 'Trapezoid Fit',\
g(x) title 'Simpson Fit'

# set logscale

set xlabel 'log10(N)'
set ylabel 'log10(Relative Error)'
set title 'Single-Precision Integration of exp(-x)'

# set xrange[0.01:2.7]
set yrange[-8:-1]

set timestamp

set key top right

set terminal pdfcairo enhanced color font "Times New Roman"
set out "graph_2e_D.pdf" 

replot
set output
unset output

print 'Trapezoid slope is: ', m
print 'Simpson slope is: ', n
print 'Trapezoid round-off slope is: ', p
print 'Simpson round-off slope is: ', q

quit
