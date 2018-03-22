set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2
set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2

plot 'eF.dat' using 1:2 with lines linestyle 1, \
     'eF.dat' using 1:3 with lines linestyle 2

pause -1 
