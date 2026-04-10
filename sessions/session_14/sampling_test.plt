# file: sampling_test.plt
#
# gnuplot plotfile for Monte Carlo sampling test
#  
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#               Ralf Bundschuh  bundschuh.2@osu.edu
# 
#  Revision history
#   2004-05-09  original version for 780.20 session 22
#   2005-02-22  minor revisions for 780.20 session 12
#   2022-01-03  hardened terminal handling
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title "Energy Distributions"
set xlabel "energy E"
set ylabel "P(E)"

# plot
set style data linespoints
set pointsize 2
plot \
     "sampling_test_kT10.dat" using 1:3 title 'random sampling' , \
     "sampling_test_kT10.dat" using 1:2 title 'exact T=10.', \
     "sampling_test_kT10.dat" using 1:4 title 'Metropolis T=10.' , \
     "sampling_test_kT1.dat" using 1:2 title 'exact T=1.0', \
     "sampling_test_kT1.dat" using 1:4 title 'Metropolis T=1.0', \
     "sampling_test_kT1_1000.dat" using 1:4 title 'Metropolis small T=1.0'



# output the plot to the file sampling_test_plt.ps
set term push
set term pdfcairo enhanced color font "Times New Roman, 10"
set out "sampling_test_plt_1000.pdf"
replot
set out
