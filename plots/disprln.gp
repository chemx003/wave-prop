set terminal latex 
set output "plot.tex"
set samples 800
unset key
set xrange [-2*pi:2*pi]
set yrange [-0.5:3]
set xtics ('-2' -2*pi, '-1' -pi, 0, '1' pi, '2' 2*pi)
set ytics 1
plot (2*(1-cos(x)))**(0.5)
unset output
