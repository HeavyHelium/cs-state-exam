#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream>

struct Node {
    
    int data;
    Node* next = nullptr;
    Node* knext = nullptr;
};


void clear_lst(Node* root) {
    if(!root) return;
    clear_lst(root->next);
    delete root;
}


void insert_refs(Node* curr, unsigned int k) {
    unsigned int id = 0;
    Node* last_mod = curr;
    while(curr) {
        if(id % k == 0) {
            last_mod->knext = curr;
            last_mod = curr;
        }
        curr = curr->next;
        id += 1;
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

Node* read_stream(std::istream& is) {
    int elem;
    Node* head = nullptr;
    Node* last = nullptr;
    int cnt = 0;

    if(is >> elem) {
        insert(last, elem);
        head = last;
        ++cnt;
    }

    while(is >> elem) {
        insert(last, elem);
        ++cnt;
    }

    unsigned int k = std::ceil(std::sqrt((double)cnt));
    insert_refs(head, k);
    return head;
}

void print_lst(Node* root) {
    while(root) {
        std::cout << root->data << " ";
        root = root->next;
    }
    std::cout << "\n";
}

bool member(Node* head, int elem) {
    if(!head) return false;
    //std::cout << head->data << " ";
    if(head->data == elem) { return true; }
    if(head->data > elem) { return false; }
    if(member(head->knext, elem)) { return true; }

    Node* end = head->knext;
    head = head->next;

    while(head != end) {
        //std::cout << head->data << " ";
        if(head->data == elem) return true;
        head = head->next;
    }

    return false;
}

int main() {

    Node* lst = read_stream(std::cin);
    print_lst(lst);
    if(member(lst, 6)) {
        std::cout << "\n6 is a member!\n";
    } else {
        std::cout << "\n6 is not a member!\n";
    }
    clear_lst(lst);
    return 0;
}

/*

1 2 3 4 5 6 7 8 9 
1 2 3 4 5 6 7 8 9 
1 4 7 5 6 
6 is a member!

 */