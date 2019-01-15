all: proj5.x sproj5.x

proj5.x: passserver.o proj5.o
	g++ -std=c++11 -o proj5.x proj5.o passserver.o -lcrypt

sproj5.x: passserver.o sproj5.o
	g++ -std=c++11 -o sproj5.x sproj5.o passserver.o -lcrypt -lncurses

passserver.o: passserver.h passserver.cpp hashtable.h hashtable.hpp
	g++ -std=c++11 -c passserver.cpp -lcrypt

proj5.o: passserver.o hashtable.h proj5.cpp
	g++ -std=c++11 -c proj5.cpp -lcrypt

sproj5.o: passserver.o hashtable.h sproj5.cpp
	g++ -std=c++11 -c sproj5.cpp -lcrypt -lncurses

clean:
	rm -f *.o
