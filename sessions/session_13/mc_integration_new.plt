# file: mc_integration_new.plt
#
# gnuplot plotfile for monte carlo integratoin
#  
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#               Ralf Bundschuh  bundschuh.2@osu.edu
# 
#  Revision history
#   2004-03-05  original version for 780.20 session 12
#   2012-02-25  based on mc_integration.plt
#   2022-01-03  hardened terminal handling
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title "Monte Carlo Integration"
set xlabel "# of integration vectors"
set ylabel "absolute error"

# fit to the logarithms of the data
f(x) = m*x + b
fit [1:8] f(x) "mc_integration_new.dat" using (log10($1)):(log10(abs($2-$3)/$3)) via m,b
 
# add label with fitted slope
unset label   # clear old labels
set label "fit slope = %-+4.2f", m at graph 0.75,0.80

# do a log-log plot
set logscale

# plot
plot "mc_integration_new.dat" using ($1):(abs($2-$3)/$3) title "monte carlo estimate" ,\
 10**b*x**m title "best-fit line"

# output the plot to the file mc_integration_new_plt.ps   
set term push
set term postscript 
set out "mc_integration_new_plt.ps"
replot
set out
set term pop
