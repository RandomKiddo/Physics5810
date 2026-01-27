plot "< sort -g derivative_test_simple.dat" using 1:2 title 'Forward Diff. Error',\
"< sort -g derivative_test_simple.dat" using 1:3 title 'Central Diff. Error'

# set logscale

set title 'Logarithm of Relative Errors for Forward and Central Differences'
set xlabel 'log10(h)'
set ylabel 'Relative Error (log10)'

set key bottom right

set timestamp

set terminal pdfcairo enhanced color font "Times New Roman"
set out "relative_error.pdf" 

replot
set output
unset output

quit
