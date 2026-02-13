# plot file for diffeq_oscillations
set timestamp

set title 'Oscillations'


# plot of kinetic energy and potential energy versus time
set xlabel 't'
set ylabel 'energy'
plot "diffeq_oscillations.dat" using ($1):($4) title 'KE(t)' with lines, \
     "diffeq_oscillations.dat" using ($1):($5) title 'PE(t)' with lines
 
