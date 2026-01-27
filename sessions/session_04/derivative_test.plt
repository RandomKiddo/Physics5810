#  file: derivative_test.plt 
#
#  Gnuplot plot file for derivative_test output
#  
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#               Ralf Bundschuh  bundshcuh.2@osu.edu
# 
#  Revision history
#   2004-01-24  original version for 780.20 session 5
#   2004-01-16  added postscript enhanced and comments for session 4
#   2021-12-29  made terminal type agnostic and restored output at the end
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'Test of Numerical Derivatives using exp(-x)'
set xlabel 'log10(mesh size)'
set ylabel 'relative error'

# move the legend to a free space
set key bottom right

# set the x and y axis scales (already logs)
set xrange [-10:-1]
#set yrange [-12:0]

# fit the curve
f1(x) = a1*x + b1
fit [-8:-1] f1(x) "derivative_test.dat" using ($1):($2) via a1,b1 
fit_title = sprintf("%-+4.1f*x %-+4.1f",a1,b1)

# central derivative
f2(x) = a2*x + b2
fit [-5:-1] f2(x) "derivative_test.dat" using ($1):($3) via a2, b2
fit_title2 = sprintf("%-+4.1f*x %-+4.1f", a2, b2)

# extrapolated derivative
f3(x) = a3*x + b3
fit [-2:-1] f3(x) "derivative_test.dat" using ($1):($4) via a3, b3
fit_title3 = sprintf("%-+4.1f*x %-+4.1f", a3, b3)

# plot the data as well as the fit, with appropriate titles 
plot "derivative_test.dat" using ($1):($2) title 'forward difference', \
     f1(x) title fit_title,\
     "derivative_test.dat" using ($1):($3) title 'central difference', \
     f2(x) title fit_title2,\
     "derivative_test.dat" using ($1):($4) title 'extrapolated difference', \
     f3(x) title fit_title3

# output the plot to the file derivative_test_plt.ps
# remember terminal type
set term push
set term pdfcairo color enhanced font "Times New Roman, 10"
set out "derivative_test_plt3.pdf"
replot
set out
# restore terminal type
set term pop
