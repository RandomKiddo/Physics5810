set timestamp

set terminal pdfcairo enhanced color font "Times New Roman, 10" size 10, 5
set output "random_walk_dependence.pdf"

# set title "Random Walk Visualization"
# set xlabel "x"
# set ylabel "y"
# plot "random_walk.dat" using 1:2 with lines title "Random Walk"

set logscale

f(x) = a*x**b
fit[10:1000] f(x) "random_walk_avg.dat" using 1:2 via a, b
fit_title = sprintf("%-+4.1f*x** %-+4.1f", a, b)

set title "Random Walk Dependence"
set xlabel "N"
set ylabel "R"
plot "random_walk_avg.dat" using 1:2 title "Data",\
    f(x) title fit_title

set output 
