set timestamp

f(x) = m*x + b
fit [4.1:5.9] f(x) "sum_test.dat" using 1:4 via m, b
fit_title = sprintf("%-+4.1f*x %-+4.1f", m, b)

plot "sum_test.dat" using 1:4 title 'Relative Error',\
f(x) title fit_title
 

set xlabel 'log10(N)'
set ylabel 'log10(Relative Error)'
set title 'Error Between Summing Up and Summing Down'

set key top left

set yrange[-8:0]

set terminal pdfcairo enhanced color font "Times New Roman, 10'
set output 'sum_test.pdf'
replot
set output