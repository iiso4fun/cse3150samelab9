
#include "Node.h"
#include <vector>
#include <iostream>

int main() {
    std::vector<std::shared_ptr<Node>> nodes;
    for (auto& name : {"zero","one","two","three","four","five"})
        nodes.push_back(std::make_shared<Node>(name));
    int N = nodes.size();
    for (int i = 0; i < N; ++i)
        nodes[i]->next = nodes[(i + 1) % N];

    std::cout << "Shared_ptr circular list:\n";
    auto ptr = nodes[0];
    do {
        std::cout << "[" << ptr->name << "] : use_count: " << ptr.use_count()
                  << " address: " << ptr.get()
                  << " next: " << ptr->next.get() << "\n";
        ptr = ptr->next;
    } while (ptr != nodes[0]);

    std::cout << "\nClearing nodes vector\n";
    ptr = nodes[0];
    nodes.clear();

    std::cout << "After clear:\n";
    std::cout << "[zero] use_count: " << ptr.use_count()
              << " next: " << ptr->next.get() << "\n";

    return 0;
} 
