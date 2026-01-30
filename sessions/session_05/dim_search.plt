set timestamp

set xlabel 'N'
set ylabel 'Relative Error'
set title 'Relative Error of Ground State Eigenvalue for Coulomb vs. Dimension'

set key top right

plot "dim_search.dat" using 1:2 title 'E0'
#f(x) title fit_title

set xrange[0:40]

set terminal pdfcairo enhanced color font "Times New Roman, 10'
set output 'dim_search_Coulomb.pdf'
replot
set output