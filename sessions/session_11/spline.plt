set timestamp

set title 'Spline and Exact Data for Scattering Cross Section'
set xlabel 'E'
set ylabel 'sigma_th' 

set key top right

plot "spline_data.dat" using 1:2 title 'Cubic' with linesp,\
     "spline_data.dat" using 1:5 title 'Exact' with lines,\
     "spline_data.dat" using 1:3 title 'Linear' with linesp,\
     "spline_data.dat" using 1:4 title 'Polynomial' with linesp

set term pdfcairo color enhanced font "Times New Roman, 10"
set out "spline2.pdf"
replot
set out