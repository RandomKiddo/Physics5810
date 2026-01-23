# gnuplot plot file: quad_eq.plt
set terminal x11   # terminal type: for a Mac, use "aqua" instead of "x11"
set title 'Landau/Paez 3.4-1 Quadratic Equation'
set xlabel '1/c [with a=1,b=2]'
set ylabel 'relative error'
set logscale
set format y "10^{%L}"
set xrange [1:1e7]
set pointsize 1.5   # set the size of the plotted points
set key top left    # move the key away from the lines
set timestamp	  # turn on a date/time indicator
plot "quadratic_eq.dat" using 1:2 title '1st root',\
     "quadratic_eq.dat" using 1:3 title '2nd root'
set out "quadratic_eq.ps"	# name of the output postscript file
set terminal postscript color enhanced	        # switch to postscript mode
replot  		  	# plot to the file
