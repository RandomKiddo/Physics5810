# plot file for diffeq_oscillations
set timestamp

set title 'Oscillations'


# plot the potential
set xlabel 'x'
set ylabel 'V(x)'
plot "diffeq_oscillations.dat" using ($2):($5) title 'V(x)' with lines

