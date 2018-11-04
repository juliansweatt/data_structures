proj1.x: proj1.o driver.o
	g++ -o proj1.x proj1.o driver.o -std=gnu++11

proj1.o: proj1.cpp proj1.h
	g++ -c proj1.cpp -std=gnu++11

driver.o: proj1.cpp proj1.h
	g++ -c driver.cpp -std=gnu++11

clean:
	rm -f *.o proj1
