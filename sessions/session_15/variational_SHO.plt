# gnuplot plot file for variational_SHO program
set timestamp

set title 'Variational Energy'

set xlabel 'Variational Parameter a'
set ylabel 'Ground-State Energy'

set xrange [0:2]
set yrange [0:1.5]

f(x) = 1./2.

plot "variational_SHO_2.dat" using 1:2:3 title "MCS = ??" with yerrorbars, \
   f(x) title "y = 1/2" 

set term push
set term pdfcairo enhanced color font "Times New Roman, 10"
set out "variational_SHO_plt.pdf"
replot
reset
set out
set term pop
