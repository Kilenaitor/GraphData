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

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%H%M%S", &tstruct);

    return buf;
}

void prepare_int_vector(std::vector<int> &v) {
	std::ofstream file("raw.txt");
	if(file.is_open()) {
		
		//Raw file for the graphviz layout
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
		
		int x1 = 0; //Number of nodes
		file << "\"node" << x1 << "\" [" << std::endl;
		file << "label=\"";
		file << "<type> int" << " | ";
		for(auto d : v) {
			file << d << " | ";
		}
		file << "vector<int>";
        file << "\"" << std::endl;
        file << "shape = \"Mrecord\"" << std::endl;
        file << "];" << std::endl;
		file << "}" << std::endl;
	}
}

void prepare_klist(std::vector<klist> &k) {
    
    std::map<std::string,std::string> map;
	std::vector<std::pair<std::string, std::string> > connections;
    std::ofstream file ("raw.txt");
    if(file.is_open()) {
        
        //Raw file for the graphviz layout
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
            file << "shape = \"Mrecord\"" << std::endl;
            file << "];" << std::endl;

            x1++;
        }
        
		for(auto &a : connections) {
			file << a.first << "->\"" << map.at(a.second) << "\":\"" << a.second << "\"" << std::endl;
		}
        
        file << "}" << std::endl;
    }
}

void drawGraph() {
    
    GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
    
    gvc = gvContext();
    fp = fopen("raw.txt", "r");
    g = agread(fp, 0);
    gvLayout(gvc, g, "dot");
	std::string name = "out " + currentDateTime() + ".png";
    gvRenderFilename (gvc, g, "png", name.c_str());
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
    
}


#endif