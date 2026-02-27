set timestamp
set terminal pdfcairo enhanced color font "Times New Roman, 10" size 10,7
set output "four_plots.pdf" 

set nokey

set multiplot layout 2,2 title "Phase Space Plots"

set title "Undamped"
plot "diffeq_pendulum_alpha0.00.dat" using ($2):($3) notitle
set xlabel "theta"
set ylabel "theta dot"

set title "Underdamped"
plot "diffeq_pendulum_alpha0.10.dat" using ($2):($3) notitle
set xlabel "theta"
set ylabel "theta dot"

set title "Overdamped"
plot "diffeq_pendulum_alpha10.00.dat" using ($2):($3) notitle
set xlabel "theta"
set ylabel "theta dot"

set title "Critically Damped"
plot "diffeq_pendulum_alpha2.00.dat" using ($2):($3) notitle
set xlabel "theta"
set ylabel "theta dot"

unset multiplot
set output