set timestamp

set terminal pdfcairo enhanced color font "Times New Roman, 10" size 10, 5
set output "random.pdf"

set nokey

set multiplot layout 1, 3 title "Uniform Random Numbers"

set title "2D Distributed Data"
plot "random_numbers.dat" using 1:2 with points pt 7 ps 0.5
set xlabel "x"
set ylabel "y"

set title "Histogram x Data"
binwidth = 0.1
bin(x,width) = width*floor(x/width)
plot 'random_numbers.dat' u (bin($1,binwidth)):(1.0) smooth freq with boxes
set xlabel "x"
set ylabel "Count"

set title "Histogram y Data"
plot 'random_numbers.dat' u (bin($2,binwidth)):(1.0) smooth freq with boxes
set xlabel "y"
set ylabel "Count"

unset multiplot
set output 
