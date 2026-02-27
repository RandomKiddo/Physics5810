set timestamp

set title ""
plot "diffeq_pendulum_alpha0.20.dat" using ($1):($2) title "Motion"
set xlabel "t"
set ylabel "theta"

set terminal pdfcairo enhanced color font "Times New Roman, 10" size 10,7
set output "ddp_motion.pdf" 
replot
set output