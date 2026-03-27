set timestamp

set terminal pdfcairo enhanced color font "Times New Roman, 10" size 10, 5
set output "pendulum.pdf"

set title "Pendulum RHS Phase Space w/ w0=1, A=0.5, wext=0.6, theta0=0.1, thetadot0=0"
set xlabel "theta"
set ylabel "theta dot"

plot "pendulum_results.dat" using 2:3 title "Phase Space"

set output 