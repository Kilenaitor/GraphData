#include <iostream>
#include <sstream>
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
    cout << (void*)ex2.getData().front().first.data() << endl;
    p.emplace_back(pair<string, void*> ("p", (void*)ex2.getData().front().first.data()));
    cout << p.front().second << endl;
    ex1.addPointers(p);
    p.clear();
    
    p.push_back(pair<string, void*> ("p", nullptr));
    ex2.addPointers(p);
    p.clear();
    
    p.push_back(pair<string, void*> ("p1", nullptr));
    p.push_back(pair<string, void*> ("p2", nullptr));
    ex3.addPointers(p);
    p.clear();
    
    cout << (void*)ex2.getData().front().first.data() << endl;
//    k.insert(k.begin(),ex1);
    k.insert(k.begin(),ex2);
    cout << (void*)k.front().getData().front().first.data() << endl;
    k.push_back(ex3);
  
    k.front().draw(cout);
    cout << (void*)k.front().getData().front().first.data() << endl;
    
    prepare(k);
    drawGraph();
    
    return 0;
}