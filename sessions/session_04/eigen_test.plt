# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'Linear Algebra Hilbert Space Time Test'
set xlabel 'log10(Dimensionality)'
set ylabel 'log10(Time (s) / 1s)'

# move the legend to a free space
set key bottom right

# set the x and y axis scales (already logs)
#set xrange [0.01:2.3]
#set yrange [-12:0]

f(x) = a*x + b
fit [0.8:2.6] f(x) "eigen_test.dat" using 1:2 via a, b
fit_title = sprintf("%-+4.1f*x %-+4.1f", a, b)

#set logscale
plot "eigen_test.dat" using 1:2 title 'Hilbert',\
f(x) title fit_title

set term pdfcairo color enhanced font "Times New Roman, 10"
set out "eigen_test.pdf"
replot
set out

