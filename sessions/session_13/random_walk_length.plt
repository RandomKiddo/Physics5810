#  file: random_walk_length.plt
#
#  gnuplot plotfile for random walk analysis
#  
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#               Ralf Bundschuh  bundschuh.2@osu.edu
# 
#  Revision history
#   2004-03-05  original version for Wi2004 780.20 session 12
#   2005-02-19  minor revisions for Wi2005 780.20 session 11
#   2022-01-03  hardened terminal handling
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title "Random Walks"
set xlabel "# of steps"
set ylabel "final distance from origin"

# move the legend to a free space
set key left

# fit to the logarithms of the data
f(x) = m*x + b
fit [1:5] f(x) "random_walk_length.dat" using (log10($1)):(log10($2)) via m,b

# add label with 
unset label  # clear old labels
set label sprintf("fit slope = %-+4.2f", m) at graph 0.08, 0.80

# do a log-log plot
set logscale xy

# plot
plot "random_walk_length.dat" using ($1):($2) title "random walks" ,\
 10**b*x**m title "best-fit line", \
 "random_walk_length.dat" using ($1):(sqrt($1)) title "sqrt(# of steps)"

# output the plot to the file random_walk2_plt.ps
set term push
set terminal pdfcairo enhanced color font "Times New Roman, 10" size 10, 5
set output "random_walk_length.pdf"
replot
set out
