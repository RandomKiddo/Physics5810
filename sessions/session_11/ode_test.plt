set timestamp

set terminal pdfcair enhanced color font "Times New Roman, 10" size 10, 5
set output "ode_phase_plots.pdf"

set nokey

set multiplot layout 1, 3 title "Phase Space Plots"

set title "x0=1, v0=0"
plot "ode_test_x0_1_v0_0.dat" using 2:3 notitle
set xlabel "y"
set ylabel "y dot"

set title "x0=0.1, v0=0"
plot "ode_test_x0_0.1_v0_0.dat" using 2:3 notitle
set xlabel "y"
set ylabel "y dot"

set title "x0=-1.5, v0=2"
plot "ode_test_x0_-1.5_v0_2.dat" using 2:3 notitle
set xlabel "y"
set ylabel "y dot"

unset multiplot
set output 