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
    
    string i = "i";
    string two = "2";
    d.push_back(pair<string, string> (i, two));
    d.push_back(pair<string, string> ("j", "4"));
    ex2.addData(d);
    d.clear();

    klist ex3 = klist("B");
    
    string hello = "hello";
    d.push_back(pair<string, string> ("a", hello));
    ex3.addData(d);
    d.clear();
    
    std::list< std::pair<std::string, void*> > p;
    p.push_back(pair<string, void*> ("p", &i));
    ex1.addPointers(p);
    p.clear();
    
    p.push_back(pair<string, void*> ("p", nullptr));
    ex2.addPointers(p);
    p.clear();
    
    p.push_back(pair<string, void*> ("p1", &hello));
    p.push_back(pair<string, void*> ("p2", &two));
    ex3.addPointers(p);
    p.clear();
    
    k.push_back(ex1);
    k.push_back(ex2);
    k.push_back(ex3);
    
    prepare(k);
    drawGraph();
    
    return 0;
}