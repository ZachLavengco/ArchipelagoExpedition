Project6: p6main.o
	g++ -o Project6 p6main.o

p6main.o: p6main.cpp Island.h
	g++ -c p6main.cpp

clean:
	rm p6main.o Project6