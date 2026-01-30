set timestamp

set xlabel 'b'
set ylabel 'E0'
set title 'Ground State Eigenvalue for Square Well vs. Oscillator Parameter'

set key top right

#f(x) = a * x**b
#fit [4:512] f(x) "relative_errors.dat" using 1:2 via a, b
#fit_title = sprintf("%-+4.1f*x**%-+4.1f", a, b)

plot "b_search.dat" using 1:2 title 'E0'
#f(x) title fit_title

set xrange[0:4]

set terminal pdfcairo enhanced color font "Times New Roman, 10'
set output 'b_search.pdf'
replot
set output