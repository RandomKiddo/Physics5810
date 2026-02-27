# plot file for comparing eigen_tridiagonal results from GSL and Armadillo
set timestamp

set xlabel 'r'
set ylabel 'u(r)'

set title 'Comparing eigen\_tridiagonal results'

plot \
  "eigen_tridiagonal.dat" using ($1):($2) title 'GSL' with lines, \
  "eigen_tridiagonal_armadillo.dat" using ($1):(-($2)) title 'Armadillo' with lines

set out "eigen_tridiagonal_comparison.pdf"
set term pdfcairo color enhanced font "Times New Roman, 10"
replot  
set out