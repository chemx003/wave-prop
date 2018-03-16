stats "u.dat" nooutput

set xr [STATS_min_x-0.1:STATS_max_x+0.1]
set yr [STATS_min_y:STATS_max_y]

do for [i = 1: int(STATS_blocks) - 1]{
	plot "u.dat" index i 
	print i
	pause 0.01
}

pause -1
