#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>

struct SinglyLinkedList {
    struct Node {
        Node* next = nullptr;
        int data;
    };

    SinglyLinkedList(std::initializer_list<int> ls) {
        for(auto rit = std::rbegin(ls); rit != std::rend(ls); ++rit) {
            push_front(*rit);
        }
    }

    SinglyLinkedList(const SinglyLinkedList& lst)
        : first(lst.copy()), length(lst.length) {}
    
    SinglyLinkedList& operator=(const SinglyLinkedList& lst) {

        if(this != & lst) {
            Node* cp = lst.copy();
            clear();
            first = cp;
            length = lst.length;
        }

        return *this;
    }

    const Node* find(int elem) const {
        const Node* iter = first;
        while(iter) {
            if(iter->data == elem) {
                break;
            }
            iter = iter->next;
        }
        return iter;
    }

    void remove(int elem) {
        if(!first) {
            return;
        }
        Node* prev = first;
        if(first->data == elem) {
            prev = first;
            first = first->next;
            delete prev;
            --length;

            return;
        }
        Node* curr = first->next;
        while(curr && curr->data != elem) {
            curr = curr->next;
            prev = prev->next;
        }
        if(curr && curr->data == elem) {
            prev->next = curr->next;
            delete curr;
            --length;
        }
    }

    Node* push_front(int elem) {
        first = new Node{ first, elem };
        ++length;

        return first;
    }

    Node* pop_front() {
        Node* temp = first;
        first = first->next;
        delete temp;
        --length;
        return first;
    }

    Node* insert_after(Node* iter, int elem) {
        iter->next = new Node{ iter->next, elem };
        ++length;

        return iter->next;
    }

    Node* erase_after(Node* iter) {
        Node* temp = iter->next;
        iter->next = iter->next->next;
        
        delete temp;
        --length;

        return iter->next; 
    }

    Node* begin() {
        return first;
    }

    const Node* begin() const {
        return first;
    }

    Node* end() {
        Node* iter = first;
        while(iter->next) {
            iter = iter->next;
        }

        return iter;
    }

    const Node* end() const {
        const Node* iter = first;
        while(iter->next) {
            iter = iter->next;
        }

        return iter;
    }

    std::size_t size() const {
        return length;
    }

    bool empty() const {
        return !first;
    }

    void append(const SinglyLinkedList& lst) {
        if(empty()) {
            *this = lst;
            return;
        }
        
        Node* last = end();

        for(const Node* iter = lst.begin(); iter; iter = iter->next) {
            last = insert_after(last, iter->data);
        }
    }

    void reverse() {
        reverse_h(first, first);

    }

    template<class Func> void map(const Func& func) {
        Node* iter = first;
        while (iter) {
            iter->data = func(iter->data);
            iter = iter->next; 
        }
    }

    template<class Func> void filter(const Func& predicate) {
        Node res{};
        Node* current = &res;
        Node* iter = first;
        Node* temp;
        while(iter) {
            if(predicate(iter->data)) {
                current->next = iter;
                current = current->next;
                iter = iter->next;
            } else {
                temp = iter;
                iter = iter->next;
                delete temp;
                --length;
            }
        }
        first = res.next;
        current->next = nullptr;
    }

    bool is_sorted() const {
        if(length < 2) {
            return true;
        }

        const Node* iter = first;
        while(iter->next && iter->data <= iter->next->data) {
            iter = iter->next;
        } 
        return !iter->next;
    }

    Node* lower_bound(int elem, Node* end_sorted) { // last smaller or equal
        if (empty() || first->data > elem) {
            return nullptr;
        }

        Node* iter = first;
        Node* prev = first;

        while(iter != end_sorted && iter->data <= elem) {
            prev = iter;
            iter = iter->next;
        }

        if(iter == end_sorted && iter->data <= elem) {
            prev = iter;
        }

        return prev;
    }

    void insertion_sort() {
        if (size() < 2) {
            return;
        }

        Node* sorted_end = first;   
        Node* current = first->next;

        while(current) {
            Node* next_current = current->next;
            Node* lb = lower_bound(current->data, sorted_end);

            if(!lb) {
                current->next = first;
                first = current;
            } else if(lb == sorted_end) {
                sorted_end->next = current;
                sorted_end = current;
            } else {
                current->next = lb->next;
                lb->next = current;
            }
            current = next_current;
        }
        sorted_end->next = nullptr;
    }

    void merge_sort() {
        merge_sort_h(first, length);
        
    }

    ~SinglyLinkedList() {
        clear();
    }


    friend std::ostream& operator<<(std::ostream& os, const SinglyLinkedList& lst) {
        const Node* head = lst.begin();
        while(head) {
            os << head->data << " ";
            head = head->next;
        }
        return os << std::endl;
    }

    
private:
    Node* copy() const {
        if(!first) {
            return nullptr;
        }

        Node* cp = new Node{ nullptr, first->data };
        Node* iter = first->next;
        Node* end = cp;

        while(iter) {
            end -> next = new Node{ nullptr, iter->data };
            end = end->next;
            iter = iter->next;
        }

        return cp;
    }

    void clear() {
        Node* temp = nullptr;
        
        while(first) {
            temp = first;
            first = first->next;
            delete temp;
        }

        length = 0;
    } 

    static Node* merge(Node* left, Node* right) {
        Node res{};
        Node* current = &res;
        while(left && right) {
            if(left -> data < right->data) {
                current->next = left;
                left = left->next;
            } else {
                current->next = right;
                right = right->next;
            }
            current = current->next;
        } 

        current->next = left ? left : right;
        return res.next;
    }

    static void split(Node* head, Node*& left, Node*& right, std::size_t length) {
        left = head;
        std::size_t mid = length / 2 + length % 2;

        Node* iter = head;

        for(std::size_t i = 1; i < mid; ++i) {
            iter = iter->next;
        }
        right = iter->next;
        iter->next = nullptr;
    }

    static void merge_sort_h(Node*& head, std::size_t len) {
        if(len < 2) {
            return;
        }

        Node *l, *r;
        split(head, l, r, len);
        merge_sort_h(l, len / 2  + len % 2);
        merge_sort_h(r, len / 2);

        head = merge(l, r);
    }

    Node* reverse_h(Node* head, Node*& new_head) { // return pointer to last elem
        if(!head || !head->next) {
            new_head = head;
            return head;
        }

        Node* prefix = reverse_h(head->next, new_head);
        prefix->next = head;
        head->next = nullptr;

        return head;
    }

    Node* first = nullptr;
    
    std::size_t length = 0; 

};


int main() {

    SinglyLinkedList list = { 1, 2, 3, 4, 5 };
    std::cout << "Initial list: " << list;
    std::cout << "List size: " << list.size() << std::endl;

    const SinglyLinkedList::Node* found = list.find(3);
    if (found) {
        std::cout << "Found: " << found->data << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    list.remove(3);
    std::cout << "List after removing 3: " << list;
    std::cout << "List size after removing 3: " << list.size() << std::endl;

    found = list.find(3);
    if (found) {
        std::cout << "Found: " << found->data << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    list.push_front(0);
    std::cout << "List after pushing front 0: " << list;
    std::cout << "List size: " << list.size() << std::endl;

    list.pop_front();
    std::cout << "List after popping front: " << list;
    std::cout << "List size: " << list.size() << std::endl;

    list.insert_after(list.begin(), 6);
    std::cout << "List after inserting 6 after the first element: " << list;
    std::cout << "List size: " << list.size() << std::endl;

    list.erase_after(list.begin());
    std::cout << "List after erasing element after the first element: " << list;
    std::cout << "List size: " << list.size() << std::endl;

    SinglyLinkedList list2 = { 7, 8, 9 };
    list.append(list2);
    std::cout << "List after appending another list {7, 8, 9}: " << list;
    std::cout << "List size: " << list.size() << std::endl;

    {
    SinglyLinkedList list = { 5, 3, 8, 1, 7, 2, 6, 4 };
    std::cout << "Initial list: " << list;

    // Testing insertion_sort on unsorted list
    list.insertion_sort();
    std::cout << "Sorted list: " << list;

    // Testing lower_bound function
    SinglyLinkedList::Node* pos;
    pos = list.lower_bound(0, list.end());
    std::cout << "Lower bound of 0: " << (pos ? pos->data : -1) << std::endl;
    
    pos = list.lower_bound(5, list.end());
    std::cout << "Lower bound of 5: " << (pos ? pos->data : -1) << std::endl;
    
    pos = list.lower_bound(10, list.end());
    std::cout << "Lower bound of 10: " << (pos ? pos->data : -1) << std::endl;

    // Testing insertion_sort on already sorted list
    SinglyLinkedList sorted_list = { 1, 2, 3, 4, 5, 6, 7, 8 };
    sorted_list.insertion_sort();
    std::cout << "Already sorted list after insertion_sort: " << sorted_list;

    // Testing insertion_sort on reverse sorted list
    SinglyLinkedList reverse_sorted_list = { 8, 7, 6, 5, 4, 3, 2, 1 };
    reverse_sorted_list.insertion_sort();
    std::cout << "Reverse sorted list after insertion_sort: " << reverse_sorted_list;

    // Testing insertion_sort on list with duplicates
    SinglyLinkedList duplicates_list = { 4, 4, 3, 3, 2, 2, 1, 1 };
    duplicates_list.insertion_sort();
    std::cout << "List with duplicates after insertion_sort: " << duplicates_list;

    // Testing insertion_sort on empty list
    SinglyLinkedList empty_list{};
    empty_list.insertion_sort();
    std::cout << "Empty list after insertion_sort: " << empty_list;

    // Testing insertion_sort on single element list
    SinglyLinkedList single_element_list = { 1 };
    single_element_list.insertion_sort();
    std::cout << "Single element list after insertion_sort: " << single_element_list;


    }

    {
        std::cout << "MERGE SORT" << std::endl;
        SinglyLinkedList list1 = { 5, 2, 9, 1, 5, 6 };
    std::cout << "Initial list1: " << list1;
    list1.merge_sort();
    std::cout << "Sorted list1: " << list1;

    SinglyLinkedList list2 = { 3, 3, 3, 3 };
    std::cout << "Initial list2: " << list2;
    list2.merge_sort();
    std::cout << "Sorted list2: " << list2;

    SinglyLinkedList list3 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    std::cout << "Initial list3: " << list3;
    list3.merge_sort();
    std::cout << "Sorted list3: " << list3;

    SinglyLinkedList list4 = { 1 };
    std::cout << "Initial list4: " << list4;
    list4.merge_sort();
    std::cout << "Sorted list4: " << list4;

    SinglyLinkedList list5 = {};
    std::cout << "Initial list5: " << list5;
    list5.merge_sort();
    std::cout << "Sorted list5: " << list5;

    SinglyLinkedList list6 = { 5, 3, 8, 1, 7, 2, 6, 4 };
    std::cout << "Initial list6: " << list6;
    list6.merge_sort();
    std::cout << "Sorted list6: " << list6;


    } 

    {
        std::cout << "REVERSE\n";
        SinglyLinkedList list6 = { 5, 3, 8, 1, 7, 2, 6, 4 };
        std::cout << "Initial: " << list6 << std::endl;
        list6.reverse();
        std::cout << "Reversed: " << list6; 
    }

    {
        std::cout << "higher order\n";
         // Test map function
    SinglyLinkedList list1 = { 1, 2, 3, 4, 5 };
    std::cout << "Original list1: " << list1;
    
    // Square each element using map
    list1.map([](int x) { return x * x; });
    std::cout << "List1 after squaring elements: " << list1;

    // Test filter function
    SinglyLinkedList list2 = { 1, 2, 3, 4, 5 };
    std::cout << "Original list2: " << list2;

    // Filter out even numbers
    list2.filter([](int x) { return x % 2 != 0; });
    std::cout << "List2 after filtering out even numbers: " << list2;

    // Test with a predicate that keeps all elements
    SinglyLinkedList list3 = { 1, 2, 3, 4, 5 };
    std::cout << "Original list3: " << list3;

    // Keep all elements (predicate always true)
    list3.filter([](int x) { return true; });
    std::cout << "List3 after keeping all elements: " << list3;

    // Test with a predicate that removes all elements
    SinglyLinkedList list4 = { 1, 2, 3, 4, 5 };
    std::cout << "Original list4: " << list4;

    // Remove all elements (predicate always false)
    list4.filter([](int x) { return false; });
    std::cout << "List4 after removing all elements: " << list4;

    }


    return 0;
}