plot "integ3.dat" using 1:2 title 'Trapezoid Rule',\
"integ3.dat" using 1:3 title 'Simpson''s Rule',\
"integ3.dat" using 1:4 title 'Gaussian',\
"integ3.dat" using 1:5 title 'GSL QAG'

# set logscale

set xlabel 'log10(N)'
set ylabel 'log10(Relative Error)'
set title 'Single-Precision Integration of exp(-x)'

set xrange[0.01:2.7]
#set yrange[-8:-1]

set timestamp

set key top right

set terminal pdfcairo enhanced color font "Times New Roman"
set out "graph_F.pdf"

replot
set output
unset output

quit
