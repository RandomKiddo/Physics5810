# plot file for diffeq_oscillations
set timestamp

set title 'Oscillations'

# phase space plot
set xlabel 'x(t)'
set ylabel 'v(t)'
plot "diffeq_oscillations.dat" using ($2):($3) title 'phase-space plot' with lines

