set timestamp

# titles and labels
set title "Energy vs. Time Distribution for Multiple kT"
set xlabel "Time t"
set ylabel "Energy E"

set style data linespoints

# plot
plot "ising_model_kT2.dat" using 1:2 title "kT=2",\
     "ising_model_kT1.dat" using 1:2 title "kT=1",\
     "ising_model_kT0.5.dat" using 1:2 title "kT=0.5"

# output the plot to the file sampling_test_plt.ps
set term pdfcairo enhanced color font "Times New Roman, 10"
set out "ising_model.pdf"
replot
set out
