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

void prepare(std::list<klist> &k) {
    
    std::map<std::string,std::string> map;
	std::vector<std::pair<std::string, std::string> > connections;
    std::ofstream file ("raw.txt");
    if(file.is_open()) {
        
        //Raw file for the graphviz layout
        file << "digraph g {" << std::endl;
        file << "graph [" << std::endl;
        file << "rankdir = \"LR\"" << std::endl;
        file << "concentrate=true" << std::endl;
        file << "];" << std::endl;
        file << "node [" << std::endl;
        file << "fontsize = \"16\"" << std::endl;
        file << "shape = \"ellipse\"" << std::endl;
        file << "];" << std::endl;
        file << "edge [" << std::endl;
        file << "];" << std::endl;
        
        int x1 = 0; //Number of nodes
        for(auto a : k) {
            file << "\"node" << x1 << "\" [" << std::endl;
            file << "label=\"";
            file << "<type> " << a.getType() << " | ";
            for(auto d : a.getData()) {
                file << "{ <"<< &d.first << "> " << d.first << " | ";
                file << " <" << &d.second << "> " << d.second << "} |";
            }
            for(auto p : a.getPointers()) {
                file << "{ <" << &p.first << "> " << p.first << " | ";
                file << " <" << p.first << "> " << p.second << "} | ";
                if(p.second != nullptr) {
                    std::stringstream strm;
                    strm << p.second;
					connections.push_back(std::pair<std::string, std::string> ("\"node" + std::to_string(x1) + "\":\"" + p.first + "\"", strm.str()));
                    map.insert(std::pair<std::string,std::string>(strm.str(), "node" + std::to_string(x1)));
                }
            }
            file << "node" << x1;
            file << "\"" << std::endl;
            file << "shape = \"record\"" << std::endl;
            file << "];" << std::endl;

            x1++;
        }
        
		for(auto a : connections) {
			file << a.first << "->\"" << map.at(a.second) << "\":\"" << a.second << "\"" << std::endl;
		}
        
        file << "}" << std::endl;
    }
    std::cout << "Completed" << std::endl;
}

void drawGraph() {
    
    GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
    
    gvc = gvContext();
    fp = fopen("raw.txt", "r");
    g = agread(fp, 0);
    gvLayout(gvc, g, "dot");
    gvRenderFilename (gvc, g, "png", "out.png");
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
    
}


#endif