CXX = g++
CPPFLAGS = -std=c++11 
DFLAGS=-lgvc -lcgraph -lcdt

all: main
	
main: bin drawer

bin:
	mkdir bin

drawer: src/drawer.cpp
	$(CXX) $(CPPFLAGS) $(DFLAGS) src/drawer.cpp -o bin/draw
	
clean:
	rm -rf bin/
