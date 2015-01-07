#ifndef KLIST_H
#define KLIST_H

#include <iostream>
#include <string>
#include <list>

class klist {
    
private:
    
    void* address;
    std::string type;
    std::list< std::pair<std::string, std::string> > data;
    std::list< std::pair<std::string, void*> > ptrs;
    
public:
    klist() {
        address = nullptr;
    }
    
    klist(std::string t) { 
        address = nullptr;
        type = t; 
    }
    
    klist(std::string t, std::list<std::pair<std::string, std::string> > d, std::list<std::pair<std::string, void*> > p) {
        address = nullptr;
        type = t;
        data = d;
        ptrs = p;
    }
    
    klist(void* add, std::string t, std::list<std::pair<std::string, std::string> > d, std::list<std::pair<std::string, void*> > p) {
        address = add;
        type = t;
        data = d;
        ptrs = p;
    }
    
    void* getAddress() {
        return address;
    }
    
    void setAddress(void* v) {
        address = v;
    }
    
    std::string getType() {
        return type;
    }
    
    void setType(std::string name) {
        type = name;
    }
    
    void addData(std::list<std::pair<std::string, std::string> > &d) {
        for(auto a : d)
            data.push_back(a);
    }
    
    std::list<std::pair<std::string, std::string> > getData() {
        return data;
    }
    
    void clearData() {
        data.clear();
    }
    
    void addPointers(std::list<std::pair<std::string, void*> > &p) {
        for(auto a : p)
            ptrs.push_back(a);
    }
    
    std::list<std::pair<std::string, void*> > getPointers() {
        return ptrs;
    }
    
    void clearPointers() {
        ptrs.clear();
    }
    
    void draw(std::ostream &os) {
        os << address << std::endl;
        os << type << std::endl;
        os << "---------" << std::endl;
        for(auto a : data) {
            os << "| " << a.first << " | " << a.second << " |" << std::endl;
            os << "---------" << std::endl;
        }
        for(auto a : ptrs) {
            os << "| " << a.first << " | " << a.second << " |" << std::endl;
            os << "---------" << std::endl;
        }
    }
    
};


#endif 