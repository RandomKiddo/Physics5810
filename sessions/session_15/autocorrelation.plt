set timestamp

set xlabel 'l'
set ylabel 'C_l'
set title 'Autocorrelation for Skip'

plot "autocorrelation.dat" using 1:2 title 'Data'

set term pdfcairo enhanced color font "Times New Roman, 10"
set out "autocorrelation.pdf"
replot
set out