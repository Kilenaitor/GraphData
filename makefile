CXX = g++ -std=c++11
CXXFLAGS = -lgvc -lcgraph -lcdt
CERRORS = -Wall

build: drawer.o graphviz.o klist.o
	$(CXX) $(CXXFLAGS) $(CERRORS)
	
drawer.o:	drawer.cpp
	g++ -std=c++11 -c drawer.cpp

graphviz.o: graphviz.h

klist.o: klist.h
	
clean: 
	rm -rf drawer.o a.out