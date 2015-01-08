#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include "klist.h"
#include "graphviz.h"

using namespace std;

int main(int argc, char ** argv) {
    
    vector<klist> k;
    klist ex1 = klist("A"); 
    
    list< pair<string, string> > d;
    d.push_back(pair<string, string> ("i", "3"));
    d.push_back(pair<string, string> ("j", "4"));
    ex1.addData(d);
    d.clear();
    
    klist ex2 = klist("A");
    
    d.push_back(pair<string, string> ("i", "2"));
    d.push_back(pair<string, string> ("j", "4"));
    ex2.addData(d);
    d.clear();

    klist ex3 = klist("B");
    
    d.push_back(pair<string, string> ("a", "hello"));
    ex3.addData(d);
    d.clear();
	
	klist ex4 = klist("B");
	
    d.push_back(pair<string, string> ("a", "1"));
    d.push_back(pair<string, string> ("b", "2"));
    d.push_back(pair<string, string> ("c", "3"));
    ex4.addData(d);
    d.clear();
	
	klist ex5 = klist("C");
	
    d.push_back(pair<string, string> ("i", "-1"));
    d.push_back(pair<string, string> ("j", "12"));
    d.push_back(pair<string, string> ("k", "z"));
    ex5.addData(d);
    d.clear();
	
	klist ex6 = klist("D");
	
    d.push_back(pair<string, string> ("z", "2"));
    d.push_back(pair<string, string> ("z", "2"));
    ex6.addData(d);
    d.clear();
    
    list<pair<string, void*> > p;
    p.emplace_back(pair<string, void*> ("p", nullptr));
    ex1.addPointers(p);
    p.clear();
    
    p.push_back(pair<string, void*> ("p", nullptr));
    ex2.addPointers(p);
    p.clear();
    
    p.push_back(pair<string, void*> ("p1", nullptr));
    p.push_back(pair<string, void*> ("p2", nullptr));
    ex3.addPointers(p);
    p.clear();
	
    p.push_back(pair<string, void*> ("p1", nullptr));
    p.push_back(pair<string, void*> ("p2", nullptr));
    ex4.addPointers(p);
    p.clear();
	
    p.push_back(pair<string, void*> ("p1", nullptr));
    ex5.addPointers(p);
    p.clear();
	
    p.push_back(pair<string, void*> ("p1", nullptr));
    p.push_back(pair<string, void*> ("p2", nullptr));
    ex6.addPointers(p);
    p.clear();
    
    k.push_back(move(ex1));
    k.push_back(move(ex2));
    k.push_back(move(ex3));
    k.push_back(move(ex4));
    k.push_back(move(ex5));
    k.push_back(move(ex6));
    
    k.at(1).getPointers().front().second = &k.at(0).getData().front().first;
    k.at(2).getPointers().front().second = &k.at(2).getData().front().second;
    k.at(2).getPointers().back().second = &k.at(0).getData().front().second;
	k.at(3).getPointers().front().second = &k.at(1).getData().back().second;
	k.at(3).getPointers().back().second = &k.at(1).getData().back().first;
	k.at(4).getPointers().front().second = &k.at(5).getData().front().second;
	k.at(5).getPointers().front().second = &k.at(5).getData().front().second;
	k.at(5).getPointers().back().second = &k.at(0).getData().front().second;
    
    prepare(k);
    drawGraph();
    
    return 0;
}