set timestamp

set xlabel 'Error'
set ylabel 'Count'
set title 'Histogram of Randomness of Round-Off Errors'

set key top left

bin_width = 1e-9
bin(x, width) = width * floor(x/width) + width/2.0

plot "randomness.dat" using (bin($2, bin_width)):(1.0) smooth freq with boxes notitle

set terminal pdfcairo enhanced color font "Times New Roman, 10'
set output 'randomness.pdf'
replot
set output