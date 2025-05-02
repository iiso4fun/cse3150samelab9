#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() = default;
LinkedList::~LinkedList() = default;

void LinkedList::SERVER_buildCircularLinkedList() {
    items.clear();
    std::vector<std::string> labels{"zero","one","two","three","four","five"};
    for (const auto& lbl : labels)
        items.push_back(std::make_shared<Node>(lbl));
    size_t count = items.size();
    for (size_t i = 0; i < count; ++i)
        items[i]->next = items[(i + 1) % count];
    head = items[0];
}

void LinkedList::SERVER_printLinkedList() {
    std::cout << "Server (step 2):\n";
    for (const auto& ptr : items) {
        auto nxt = ptr->next.lock();
        std::cout << "[" << ptr->name << "] : use_count: "
                  << ptr.use_count() << " address: " << ptr.get()
                  << " next (from shared_ptr): "
                  << (nxt ? nxt.get() : nullptr) << "\n";
    }
    std::cout << "\n";
}

void LinkedList::CLIENT_printLinkedList() {
    std::cout << "Client (step 3):\n";
    if (!head) return;
    auto curr = head;
    do {
        auto nxt = curr->next.lock();
        std::cout << "[" << curr->name << "] : use_count: "
                  << curr.use_count() << " address: " << curr.get()
                  << " next (from weak_ptr): "
                  << (nxt ? nxt.get() : nullptr) << "\n";
        curr = nxt;
    } while (curr && curr != head);
    std::cout << "\n";
}

void LinkedList::SERVER_deleteCircularLinkedList() {
    std::cout << "Server is deleting the shared_ptrs (step 4)\n\n";
    items.clear();
}

void LinkedList::CLIENT_printAfterDeletion() {
    std::cout << "Client after linked list deleted (step 5):\n";
    if (!head) {
        std::cout << "[Nothing]\n\n";
    } else {
        auto nxt = head->next.lock();
        std::cout << "[" << head->name << "] : use_count: "
                  << head.use_count() << " address: " << head.get()
                  << " next (from weak_ptr): "
                  << (nxt ? nxt.get() : nullptr) << "\n";
        if (!nxt)
            std::cout << "Yipes! shared_ptr not available\n\n";
    }
}

std::shared_ptr<Node> LinkedList::getRoot() const {
    return head;
}

int main(int argc, char** argv) {
    LinkedList demo;
    demo.SERVER_buildCircularLinkedList();
    demo.SERVER_printLinkedList();
    demo.CLIENT_printLinkedList();
    demo.SERVER_deleteCircularLinkedList();
    demo.CLIENT_printAfterDeletion();

    doctest::Context ctx;
    ctx.applyCommandLine(argc, argv);
    return ctx.run();
}

TEST_CASE("SERVER_buildCircularLinkedList creates a valid 6-node cycle") {
    LinkedList l;
    l.SERVER_buildCircularLinkedList();
    auto r = l.getRoot();
    CHECK(r);
    auto second = r->next.lock();
    REQUIRE(second);
    CHECK(second->name == "one");
}

TEST_CASE("SERVER_deleteCircularLinkedList clears all shared_ptrs") {
    LinkedList l;
    l.SERVER_buildCircularLinkedList();
    auto r = l.getRoot();
    REQUIRE(r);
    l.SERVER_deleteCircularLinkedList();
    CHECK(!r->next.lock());
} 


