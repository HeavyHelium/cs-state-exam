#include <iostream>
#include <cstddef>
#include <initializer_list>
#include <cassert>

struct DoublyLinkedList {
    struct Node {
        int data;
        Node* prev = nullptr;
        Node* next = nullptr;
    };

    DoublyLinkedList(const std::initializer_list<int>& lst) {
        dummy.next = dummy.prev = &dummy;
        for(int elem: lst) {
            push_back(elem);
        }
    }

    DoublyLinkedList(const DoublyLinkedList& other) {
        dummy.next = dummy.prev = &dummy;
        copy(other);
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if(this != &other) {
            clear();
            copy(other);
        }

        return *this;
    }

    void insert_before(Node* pos, int elem) {
        Node* new_node = new Node{ elem, pos->prev, pos };
        new_node->prev->next = new_node;
        pos->prev = new_node;

        ++length;
    }

    void erase(Node* pos) {
        pos->prev->next = pos->next;
        pos->next->prev = pos->prev;
        delete pos;

        --length;
    }

    void push_front(int elem) {
        insert_before(dummy.next, elem);
    }

    void push_back(int elem) {
        insert_before(&dummy, elem);   
    }

    void pop_front() {
        erase(dummy.next);
    }

    void pop_back() {
        erase(dummy.prev);
    }

    const Node* begin() const {
        return dummy.next;
    }

    const Node* end() const {
        return &dummy;
    }

    std::size_t size() const {
        return length;
    }

    bool empty() const {
        if(length == 0) {
            assert(dummy.prev == dummy.next && dummy.next == &dummy);
        }
        return length == 0;
    }


    ~DoublyLinkedList() {
        clear();
    }

    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList& lst) {
        for(const Node* iter = lst.begin(); iter != lst.end(); iter = iter->next) {
            os << iter->data << " ";
        }

        return os << std::endl;
    }

private: 

    void copy(const DoublyLinkedList& other) {
        for(const Node* iter = other.begin(); iter != other.end(); iter = iter->next) {
            push_back(iter->data);
        }
    }

    void clear() {
        while(!empty()) {
            pop_back();
        }
    }

    Node dummy;
    std::size_t length = 0;

};


int main() {
    // Testing initializer list constructor
   DoublyLinkedList list1 = { 1, 2, 3, 4, 5 };
    std::cout << "List1: ";
    std::cout << (list1);

    // Testing size and empty methods
    std::cout << "Size of list1: " << list1.size() << std::endl;
    std::cout << "Is list1 empty: " << std::boolalpha << list1.empty() << std::endl;

    // Testing push and pop methods
    list1.push_front(0);
    list1.push_back(6);
    std::cout << "List1 after push_front(0) and push_back(6): ";
    std::cout << (list1);

    list1.pop_front();
    list1.pop_back();
    std::cout << "List1 after pop_front() and pop_back(): ";
    std::cout << (list1);

    // Testing copy constructor
    DoublyLinkedList list2 = list1;
    std::cout << "List2 (copy of list1): ";
    std::cout << (list2);

    // Testing assignment operator
    DoublyLinkedList list3 = { 7, 8, 9 };
    list3 = list1;
    std::cout << "List3 (assigned from list1): ";
    std::cout << (list3);

    // Ensure list1 and list2 are still valid after assignment
    std::cout << "List1 after assignment to list3: ";
    std::cout << (list1);
    std::cout << "List2 after assignment to list3: ";
    std::cout << (list2);

    // Testing empty list
    DoublyLinkedList emptyList{};
    std::cout << "Empty list: ";
    std::cout << (emptyList);
    std::cout << "Size of empty list: " << emptyList.size() << std::endl;
    std::cout << "Is empty list empty: " << std::boolalpha << emptyList.empty() << std::endl;

    return 0;

    return 0;
}