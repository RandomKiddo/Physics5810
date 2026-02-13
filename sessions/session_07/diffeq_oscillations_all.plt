# plot file for diffeq_oscillations

#
# WARNING: If you get a message along the lines of
#          "unknown or ambiguous terminal type"
#          replace "set term x11" with "set term qt"
#          everywhere in this script
#

# simple plot versus time
set term qt 1 title "Time Dependence"  # plot window 1
set timestamp
set title 'Oscillations: Time Dependence'
pi = 3.141592653589793
k = (2.*pi)**2
m = 1
omega = sqrt(k/m)
set xlabel 't'
set ylabel 'y(t)'
plot "diffeq_oscillations.dat" using ($1):($2) title 'p=?' with lines 
#plot "diffeq_oscillations.dat" using ($1):($2) title 'p=?' with lines # , \
#  (1/omega)*sin(omega*x)


# phase space plot
set term qt 2 title "Phase Space"  # plot window 2
set timestamp
set title 'Oscillations: Phase Space'
set xlabel 'x(t)'
set ylabel 'v(t)'
plot "diffeq_oscillations.dat" using ($2):($3) title 'phase-space plot' with lines


# plot the potential
set term qt 3 title "Potential V(x)"  # plot window 3
set timestamp
set title 'Oscillations: Potential V(x)'
set xlabel 'x'
set ylabel 'V(x)'
plot "diffeq_oscillations.dat" using ($2):($5) title 'V(x)' with lines


# plot of kinetic energy and potential energy versus time
set term qt 4 title "Energy"  # plot window 4
set timestamp
set title 'Oscillations: Energy'
set xlabel 't'
set ylabel 'energy'
plot "diffeq_oscillations.dat" using ($1):($4) title 'KE(t)' with lines, \
     "diffeq_oscillations.dat" using ($1):($5) title 'PE(t)' with lines
 
set term qt 5 title "Total Energy"
set timestamp
set title 'Total Energy'
set xlabel 't'
set ylabel 'E'
set title 'Total Energy vs. Time'
plot "diffeq_oscillations.dat" using ($1):(abs($5+$4-0.5)/0.5) title 'Relative Error E(t)' with lines