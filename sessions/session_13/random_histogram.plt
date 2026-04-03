# set timestamp

# set terminal pdfcairo enhanced color font "Times New Roman, 10" size 10, 5
# set output "random_histogram.pdf"

# set title "Uniform Distribution Check"
# set xlabel "x value"
# set ylabel "Counts"
# set yrange [0:3000]  # Setting y-range to see the fluctuations clearly
# plot "random_histogram.dat" using 2:3 with boxes title "Uniform 1", \
#      "random_histogram.dat" using 2:4 with boxes title "Uniform 2"

# set output 

set timestamp

set terminal pdfcairo enhanced color font "Times New Roman, 10" size 10, 5
set output "random_histogram2.pdf"

set title "Gaussian Distribution Check"
set xlabel "Standard Deviations"
set ylabel "Counts"
set yrange [0:6000]
plot "random_histogram.dat" using 5:6 with boxes title "Gaussian 1", \
     "random_histogram.dat" using 5:7 with boxes title "Gaussian 2"

set output 

