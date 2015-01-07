#include <iostream>
#include <string>
#include <list>
#include "klist.h"
#include "graphviz.h"

using namespace std;

int main(int argc, char ** argv) {
    
    list<klist> k;
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
    
    list<pair<string, void*> > p;
    p.push_back(pair<string, void*> ("p", &ex1.getData().front().first));
    ex1.addPointers(p);
    p.clear();
    
    p.push_back(pair<string, void*> ("p", nullptr));
    ex2.addPointers(p);
    p.clear();
    
    p.push_back(pair<string, void*> ("p1", nullptr));
    p.push_back(pair<string, void*> ("p2", nullptr));
    ex3.addPointers(p);
    p.clear();
    
    k.push_back(ex1);
    k.push_back(ex2);
    k.push_back(ex3);
    
    prepare(k);
    drawGraph();
    
    return 0;
}