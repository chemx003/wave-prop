set terminal latex
set output '19.tex'
stats "u.dat" nooutput

set yr [-3.25:3.25]

set xr [STATS_min_x-0.1:STATS_max_x+0.1]
#set yr [STATS_min_y:STATS_max_y]

set ytics 1
unset key

#do for [i = 1: int(STATS_blocks) - 1]{
#	plot "u.dat" index i with linespoints 
#	print i
#	pause 0.01
#}

plot "u.dat" index int(STATS_blocks)-5 with lines
unset output
#pause -1

