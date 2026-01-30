set timestamp

set xlabel 'r'
set ylabel 'u(r)'
set title 'u(r) vs. r for the Quantum Harmonic Oscillator'

set key top right

plot "eigen_tridiagonal.dat" using 1:2 title 'u(r)'

set terminal pdfcairo enhanced color font "Times New Roman, 10'
set output 'eigen_tridiagonal.pdf'
replot
set output