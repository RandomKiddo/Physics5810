set timestamp

set terminal pdfcairo enhanced color font "Times New Roman, 10" size 10, 5
set output "multifit2.pdf"

set xlabel "t"
set ylabel "y"
set title "Exact vs. Fit for Weighted Exponential with Cosine Term"

plot "fit_results_bonus.dat" using 1:2:4 title "Exact" with yerrorbars lc rgb "blue" pt 3,\
     "fit_results_bonus.dat" using 1:3 title "Fit" with lines lw 2 lc rgb "purple"

set output 