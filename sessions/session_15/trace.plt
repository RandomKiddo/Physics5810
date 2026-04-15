set timestamp

set xlabel 'Iteration i'
set ylabel 'x^2'
set title 'Trace Plot for Initial Skip'

plot "mc_trace.dat" using 1:2 title 'Data'

set term pdfcairo enhanced color font "Times New Roman, 10"
set out "trace.pdf"
replot
set out