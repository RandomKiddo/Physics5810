set timestamp

set xlabel 'N'
set ylabel 'Relative Error'
set title 'Relative Error for Ground State Quantum Harmonic Oscillator Eigenvalue'

set key top right
set logscale

#f(x) = a * x**b
#fit [4:512] f(x) "relative_errors.dat" using 1:2 via a, b
#fit_title = sprintf("%-+4.1f*x**%-+4.1f", a, b)

plot "relative_errors.dat" using 1:2 title 'Error'
#f(x) title fit_title

set terminal pdfcairo enhanced color font "Times New Roman, 10'
set output 'relative_errors_Rmax4.pdf'
replot
set output