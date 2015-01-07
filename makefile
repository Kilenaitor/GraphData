CXX = g++
CPPFLAGS = -std=c++11 
DFLAGS=-lgvc -lcgraph -lcdt

all: main
	
main: drawer.o

drawer.o: drawer.cpp
	$(CXX) $(CPPFLAGS) $(DFLAGS) drawer.cpp -o draw
	
clean:
	rm -f drawer.o