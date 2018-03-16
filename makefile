main: oned.cpp
	make clean-data
	g++ oned.cpp

clean:
	make clean-data clean-exe
clean-data:
	rm *.dat -f
clean-exe:
	rm c-main -f
	rm c-postp -f
