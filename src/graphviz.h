#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H

#include <iostream>
#include <fstream>
#include "graphviz/gvc.h"
#include <string>
#include <list>
#include <sstream>
#include <map>
#include <vector>
#include "klist.h"
#include <time.h>
#include <typeinfo>
#include <type_traits>
#include <cxxabi.h>
#include <forward_list>
#include <set>

int counter = 0;

void drawGraph() {
    
    GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
	
    gvc = gvContext();
    fp = fopen("raw.txt", "r");
    g = agread(fp, 0);
    gvLayout(gvc, g, "dot");
	std::string name = "out-" + std::to_string(counter++) + ".png";
    gvRenderFilename (gvc, g, "png", name.c_str());
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
}

void prepareGraph(std::ofstream &file) {
    file << "digraph g {" << std::endl;        
    file << "graph [" << std::endl;
    file << "rankdir = \"LR\"," << std::endl;
	file << "nodesep=0.5" << std::endl;
	file << "sep=5" << std::endl;
    file << "];" << std::endl;
    file << "node [" << std::endl;
    file << "fontsize = \"11\"" << std::endl;
    file << "];" << std::endl;
    file << "edge [" << std::endl;
    file << "];" << std::endl;
}

template<typename T>
struct Data {
	void operator()(T t1) {
		std::cout << "Error!" << std::endl;
	}
};

template<>
struct Data<std::vector<klist> > {
	void operator()(std::vector<klist> &k) {
	    std::map<std::string,std::string> map;
		std::vector<std::pair<std::string, std::string> > connections;
	    std::ofstream file ("raw.txt");
	    if(file.is_open()) {
        
	        //Raw file for the graphviz layout
			prepareGraph(file);
	        int x1 = 0; //Number of nodes
	        for(auto &a : k) {
	            file << "\"node" << x1 << "\" [" << std::endl;
	            file << "label=\"";
	            file << "<type> " << a.getType() << " | ";
	            for(auto &d : a.getData()) {
	                file << "{ <"<< &d.first << "> " << d.first << " | ";
	                file << " <" << &d.second << "> " << d.second << "} |";
	                std::stringstream strm1, strm2;
	                strm1 << &d.first;
	                strm2 << &d.second;
	                map.insert(std::pair<std::string,std::string>(strm1.str(), "node" + std::to_string(x1)));
	                map.insert(std::pair<std::string,std::string>(strm2.str(), "node" + std::to_string(x1)));
	            }
	            for(auto &p : a.getPointers()) {
	                file << "{ <" << &p.first << "> " << p.first << " | ";
	                file << " <" << p.first << "> " << p.second << "} | ";
	                if(p.second != nullptr) {
	                    std::stringstream strm;
	                    strm << p.second;
						connections.push_back(std::pair<std::string, std::string> ("\"node" + std::to_string(x1) + "\":\"" + p.first + "\"", strm.str()));
	                }
	            }
	            file << "node" << x1;
	            file << "\"" << std::endl;
	            file << "shape = \"record\"" << std::endl;
	            file << "];" << std::endl;

				x1++;
	        }
        
			for(auto &a : connections) {
				file << a.first << "->\"" << map.at(a.second) << "\":\"" << a.second << "\"" << std::endl;
			}
        
	        file << "}" << std::endl;
	    }
		drawGraph();
	}
};

template<typename T>
struct Data<std::vector<T> > {
	void operator()(std::vector<T> &v) {
		int status;
		std::ofstream file("raw.txt");
		if(file.is_open()) {
	
			//Raw file for the graphviz layout
			prepareGraph(file);
			int x1 = 0; //Number of nodes
			file << "\"node" << x1 << "\" [" << std::endl;
			file << "label=\"";
			std::string realname = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
			if(realname == "std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >")
				realname = "string";
			file << "<type> "<< realname << " | ";
			for(auto d : v) {
				file << d << " | ";
			}
			file << "vector<T>";
		    file << "\"" << std::endl;
		    file << "shape = \"record\"" << std::endl;
		    file << "];" << std::endl;
			file << "}" << std::endl;
		}
		drawGraph();
	}
};

template<typename T>
struct Data<std::forward_list<T> > {
	void operator()(std::forward_list<T> &f) {
		std::ofstream file("raw.txt");
		if(file.is_open()) {
			int status;
			//Raw file for the graphviz layout
			prepareGraph(file);
			int x1 = 0; //Number of nodes
			for(auto d : f) {
				file << "\"node" << x1++ << "\" [" << std::endl;
				file << "label=\"";
				std::string realname = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
				if(realname == "std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >")
					realname = "string";
				file << "<type> "<< realname << " | ";
				file << d << " | ";
				file << "forward_list<T>";
			    file << "\"" << std::endl;
			    file << "shape = \"record\"" << std::endl;
			    file << "];" << std::endl;
			}
			for(int i = 0; i < x1-1; i++) {
				file << "\"node" << i << "\"->" << "\"node" << i+1 << "\"" << std::endl;
			}
			file << "}" << std::endl;
		}
		drawGraph();
	}
};

template<typename T>
struct Data<std::list<T> > {
	void operator()(std::list<T> &f) {
		std::ofstream file("raw.txt");
		if(file.is_open()) {
			int status;
			//Raw file for the graphviz layout
			prepareGraph(file);
			int x1 = 0; //Number of nodes
			for(auto d : f) {
				file << "\"node" << x1++ << "\" [" << std::endl;
				file << "label=\"";
				std::string realname = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
				if(realname == "std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >")
					realname = "string";
				file << "<type> "<< realname << " | ";
				file << d << " | ";
				file << "list<T>";
			    file << "\"" << std::endl;
			    file << "shape = \"record\"" << std::endl;
			    file << "];" << std::endl;
			}
			for(int i = 0; i < x1-1; i++) {
				file << "\"node" << i << "\"->" << "\"node" << i+1 << "\"" << std::endl;
				file << "\"node" << i+1 << "\"->" << "\"node" << i << "\"" << std::endl;
			}
			file << "}" << std::endl;
		}
		drawGraph();
	}
};

template<typename T>
struct Data<std::set<T> > {
	void operator()(std::set<T> &s) {
		std::ofstream file("raw.txt");
		if(file.is_open()) {
			int status;
			//Raw file for the graphviz layout
			prepareGraph(file);
			int x1 = 0; //Number of nodes
			for(auto d : s) {
				file << "\"node" << x1++ << "\" [" << std::endl;
				file << "label=\"";
				std::string realname = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
				if(realname == "std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >")
					realname = "string";
				file << "<type> "<< realname << " | ";
				file << d << " | ";
				file << "set<T>";
			    file << "\"" << std::endl;
			    file << "shape = \"record\"" << std::endl;
			    file << "];" << std::endl;
			}
			int set_size = s.size();
			int midpoint = set_size/2;
			auto mid_iterator = s.begin();
			std::advance(mid_iterator, midpoint);
			auto mid_rev_iterator = s.rbegin();
			std::advance(mid_rev_iterator, midpoint+1);
			file << "\"node" << midpoint << "\"->" << "\"node" << *mid_iterator << "\"" << std::endl;
			file << "\"node" << midpoint << "\"->" << "\"node" << *mid_rev_iterator << "\"" << std::endl;
			for(int left_side = *mid_rev_iterator; left_side > 1; left_side--) {
				file << "\"node" << left_side << "\"->" << "\"node" << left_side-1 << "\"" << std::endl;
				file << "\"node" << left_side << "\"->" << "\"node" << left_side-2 << "\"" << std::endl;
			}
			for(int right_side = *mid_iterator; right_side < set_size-2; right_side++) {
				file << "\"node" << right_side << "\"->" << "\"node" << right_side+1 << "\"" << std::endl;
				file << "\"node" << right_side << "\"->" << "\"node" << right_side+2 << "\"" << std::endl;
			}
			file << "}" << std::endl;
		}
		drawGraph();
	}
};

template <typename T> 
void visualize(T &v) {
	Data<T> d;
	d(v);
}

#endif