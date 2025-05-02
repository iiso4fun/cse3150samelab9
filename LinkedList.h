// LinkedList.h
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <memory>
#include <vector>

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void SERVER_buildCircularLinkedList();
    void SERVER_printLinkedList();
    void CLIENT_printLinkedList();
    void SERVER_deleteCircularLinkedList();
    void CLIENT_printAfterDeletion();

    std::shared_ptr<Node> getRoot() const;

private:
    std::shared_ptr<Node> head;
    std::vector<std::shared_ptr<Node>> items;
};

#endif
