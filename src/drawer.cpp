#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "klist.h"
#include "graphviz.h"

using namespace std;

void print_klist() {
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
    
    visualize(k);
}

void print_int_vector() {
	vector<int> v = {1,2,3,4,5,6,7,8,9,10};
	visualize(v);
	v.push_back(5);
	v.push_back(15);
	visualize(v);
	std::random_shuffle(v.begin(), v.end());
	visualize(v);
	std::sort(v.begin(), v.end());
	visualize(v);
}

void print_string_vector() {
	vector<string> v = {"kyle", "minshall", "is", "really", "cool"};
	visualize(v);
	v.push_back("!");
	visualize(v); 
}

void print_double_vector() {
	vector<double> d = {1.1, 2.1, 3.1, 4.1, 5.1};
	visualize(d);
	d.push_back(0.1);
	visualize(d);
	std::sort(d.begin(), d.end());
	visualize(d);
}

void print_forward_list() {
	forward_list<std::string> f {"kyle", "minshall", "is", "really", "cool"};
	visualize(f);
	f.push_front("RA");
	visualize(f);
	f.pop_front();
	visualize(f);
}

void print_list() {
	std::list<std::string> f {"kyle", "minshall", "is", "really", "cool"};
	visualize(f);
	f.push_front("RA");
	visualize(f);
	f.push_back("!");
	visualize(f);
}

void print_tree() {
	std::set<int> s {1,2,3,4,5,6,7,8,9,10};
	visualize(s);
	s.insert(20);
	s.insert(30);
	visualize(s);
	s.insert(40);
	s.insert(50);
	visualize(s);
}

int main(int argc, char ** argv) 
{
	print_int_vector();
	print_string_vector();
	print_double_vector();
	print_klist();
	print_forward_list();
	print_list();
	print_tree();
	
    return 0;
}