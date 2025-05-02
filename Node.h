
#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <memory>
#include <string>

struct Node {
    std::string name;
#ifdef USE_SHARED
    std::shared_ptr<Node> next;
#else
    std::weak_ptr<Node>   next;
#endif

    Node(const std::string& s) : name(s) {}
    ~Node() { std::cout << "Node [" << name << "] destructor\n"; }
};

#endif 
