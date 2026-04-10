set timestamp

# titles and labels
set title "Magnetization vs. Thermal Energy"
set xlabel "Thermal Energy kT"
set ylabel "Average Magnetization m"

set style data linespoints

# plot
plot "magnetization.dat" using 1:2 title 'Magnetization'

set term pdfcairo enhanced color font "Times New Roman, 10"
set out "magnetization.pdf"
replot
set out
