#  file: gaussian_random_new.plt 
#
#  Gnuplot plot file for gaussian_random_new histograms
#  
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#               Ralf Bundschuh  bundschuh.2@osu.edu
# 
#  Revision history
#   2004-03-05  original version for 780.20 session 12
#   2022-01-03  hardened terminal handling
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'Random Number Distributions'
set xlabel 'x'
set ylabel '# in bin'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
set xrange [-3:3]
#set yrange [0:100]

# fit the curve
f(x) = b*exp(-x**2/(2*sigma**2))
fit [-3:3] f(x) "random_histogram.dat" using ($5):($6) via b,sigma 

# add a label with the result for sigma
#unset label
set label sprintf("fit sigma = %-4.1f", abs(sigma)) at graph .08,.80

# plot 
plot "random_histogram.dat" using ($5):($6) title 'gaussian 1', \
     b*exp(-x**2/(2*sigma**2)) title 'fit to gaussian 1', \
     "random_histogram.dat" using ($5):($7) title 'gaussian 2'

# output the plot to the file derivative_test_plt.ps   
set term push
set terminal pdfcairo enhanced color font "Times New Roman, 10" size 10, 5
set output "gaussian_random_new.pdf"
replot
set out