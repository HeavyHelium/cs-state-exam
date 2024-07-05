#include <iostream>


struct Node {
    int data;;
    Node* next = nullptr;
};


void clear_lst(Node* lst) {
    if(!lst) return;
    clear_lst(lst->next);
    delete lst;
}


void selection_sort(Node* lst) {
    if(!lst || !lst->next) return;
    
    for(Node* iter = lst; iter->next; iter = iter->next) {
        Node* best = iter;
        for(Node* jter = iter->next; jter; jter = jter->next) {
            if(jter->data < best->data) {
                best = jter;
            }
        }
        std::swap(iter->data, best->data);
    }
}


void insert(Node*& last, int elem) {
    if(!last) {
        last = new Node{elem};
        return;
    } 

    last->next = new Node{elem};
    last = last->next;
}


void print_lst(Node* head) {
    if(!head) return;
    std::cout << head->data << " ";
    print_lst(head->next);
}


int main() {

    int arr[] = {5, 6, 7, 2, 0, 15, 12, 4};

    int size = sizeof(arr) / sizeof(int);

    Node* head = nullptr;
    Node* last = nullptr;
    insert(last, arr[0]);
    head = last;

    for(int i = 1; i < size; ++i) {
        insert(last, arr[i]);
    }
    
    print_lst(head);
    std::cout << std::endl;

    selection_sort(head);
    
    print_lst(head);
    std::cout << std::endl;

    clear_lst(head);

    return 0;
}