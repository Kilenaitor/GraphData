CXX = g++
CPPFLAGS = -std=c++11 #-lgvc -lcgraph -lcdt

all:
	g++ drawer.cpp
	
clean:
	rm -f drawer.o