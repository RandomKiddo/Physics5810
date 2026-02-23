set timestamp

set xlabel 'N'
set ylabel 'Relative Error'
set title 'Relative Errors for Simpson/Milne Integration Routines'

set logscale

f1(x) = a1*x**b1
b1=-1.0
fit [10:1e3] f1(x) "errors.dat" using 1:2 via a1, b1 
fit_title = sprintf("%-+4.1f*x**%-+4.1f", a1, b1)

f2(x) = a2*x**b2
b2=-1.0
fit [10:300] f2(x) "errors.dat" using 1:3 via a2, b2
fit_title2 = sprintf("%-+4.1f*x**%-+4.1f", a2, b2)

f3(x) = a3*x**b3
fit [1e4:1e6] f3(x) "errors.dat" using 1:2 via a3, b3
fit_title3 = sprintf("%-+4.1f*x**%-+4.1f", a3, b3)

f4(x) = a4*x**b4
fit [2000:1e6] f4(x) "errors.dat" using 1:3 via a4, b4
fit_title4 = sprintf("%-+4.1f*x**%-+4.1f", a4, b4)

plot "errors.dat" using 1:2 title 'Simpson Error', \
     "errors.dat" using 1:3 title 'Milne Error', \
     f1(x) title fit_title, \
     f2(x) title fit_title2, \
     f3(x) title fit_title3, \
     f4(x) title fit_title4

set xrange[1:1e7]
set yrange[1e-18:1]

set key top right 

set terminal pdfcairo enhanced color font "Times New Roman, 10"
set output "errors.pdf"
replot
set output