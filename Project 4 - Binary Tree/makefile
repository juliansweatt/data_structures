proj4.x: bet.o proj4_driver.o
	g++ -std=c++11 -o proj4.x bet.o proj4_driver.o

bet.o: bet.cpp bet.h
	g++ -std=c++11 -c bet.cpp

proj4_driver.o: bet.cpp bet.h
	g++ -std=c++11 -c proj4_driver.cpp

clean:
	rm -f *.o
