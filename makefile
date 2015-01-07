CXX = g++ -std=c++11
CXXFLAGS = -lgvc -lcgraph -lcdt

main: drawer.o
	
clean:
	rm -f graphviz