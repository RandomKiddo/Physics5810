set timestamp

# titles and labels
set title "Energy vs. Time Distribution for Multiple kT w/ Cooling"
set xlabel "Time t"
set ylabel "Energy E"

set style data linespoints

# plot
plot "ising_cooling_kT2.dat" using 1:2 title "kT=2",\
     "ising_cooling_kT1.dat" using 1:2 title "kT=1",\
     "ising_cooling_kT0.5.dat" using 1:2 title "kT=0.5"

# output the plot to the file sampling_test_plt.ps
set term pdfcairo enhanced color font "Times New Roman, 10"
set out "ising_cooling.pdf"
replot
set out
