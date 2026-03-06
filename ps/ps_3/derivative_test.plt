#  file: derivative_test.plt 
#
#  Gnuplot plot file for derivative_test output
#  
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#               Ralf Bundschuh  bundshcuh.2@osu.edu
#               Neil Ghugare    ghugare.1@osu.edu
# 
#  Revision history
#   2004-01-24  original version for 780.20 session 5
#   2004-01-16  added postscript enhanced and comments for session 4
#   2021-12-29  made terminal type agnostic and restored output at the end
#   2026-03-06  updated for better-precision extrapolated diff
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'Test of Numerical Derivatives using exp(-x)'
set xlabel 'log10(mesh size)'
set ylabel 'relative error'

# set limits
set xrange[-10:0]
set yrange[-15:-4]

# move the legend to a free space
set key bottom left

# set the x and y axis scales (already logs)

# fit the curve
f1(x) = a1*x + b1
fit [-9:-3] f1(x) "derivative_test.dat" using ($1):($4) via a1, b1 
fit_title1 = sprintf("%-+4.1f*x %-+4.1f", a1, b1)

f2(x) = a2*x + b2
fit [-9:-3] f2(x) "derivative_test.dat" using ($1):($5) via a2, b2
fit_title2 = sprintf("%-+4.1f*x %-+4.1f", a2, b2)

f3(x) = a3*x + b3
fit [-2:0] f3(x) "derivative_test.dat" using ($1):($4) via a3, b3 
fit_title3 = sprintf("%-+4.1f*x %-+4.1f", a3, b3)

f4(x) = a4*x + b4
fit [-1:0] f4(x) "derivative_test.dat" using ($1):($5) via a4, b4
fit_title4 = sprintf("%-+4.1f*x %-+4.1f", a4, b4)

# plot the data as well as the fit, with appropriate titles 
plot "derivative_test.dat" using 1:4 title 'Extrapolated Diff', \
     "derivative_test.dat" using 1:5 title 'Extrapolated Diff 2', \
     f1(x) title fit_title1, \
     f2(x) title fit_title2, \
     f3(x) title fit_title3, \
     f4(x) title fit_title4

# output the plot to the file derivative_test_plt.ps
# remember terminal type
set term pdfcairo color enhanced font "Times New Roman, 10"
set out "derivative_test_plt.pdf"
replot
set out
