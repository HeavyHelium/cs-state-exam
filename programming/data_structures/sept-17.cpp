#include <iostream>

struct Node {
    int data;
    Node* next = nullptr;
};


struct HOList {
    Node* lst = nullptr;
    HOList* next = nullptr;

};


void clear_list(Node* lst) {
    if(!lst) return;
    clear_list(lst->next);
    delete lst;
}

void clear_ho_list(HOList* lst) {
    if(!lst) return;
    clear_ho_list(lst->next);
    clear_list(lst->lst);
    delete lst; 
}

bool is_sorted(Node* lst) {
    if(!lst || !lst->next) return true;

    if(lst->data > lst->next->data) { return false; }
    return is_sorted(lst->next);
}

Node* merge_lists(Node* lst1, Node* lst2) {
    Node dummy;
    Node* curr = &dummy;

    while(lst1 && lst2) {
        if(lst1->data > lst2->data) {
            curr->next = lst2;
            lst2 = lst2->next;
        } else {
            curr->next = lst1;
            lst1 = lst1->next;
        }
        curr = curr->next;
    }

    while(lst1) {
        curr->next = lst1;
        curr = curr->next;
        lst1 = lst1->next;
    }
    while(lst2) {
        curr->next = lst2;
        curr = curr->next;
        lst2 = lst2->next;
    }
    
    return dummy.next;
}


void print_lst(const Node* lst) {
    while(lst) {
        std::cout << lst->data << " ";
        lst = lst->next;
    } std::cout << std::endl;
}


Node* merged_sorted(HOList* ho) {
    if(!ho) return nullptr;

    Node* res = nullptr;
    while(ho) {
        if(is_sorted(ho->lst)) {
            res = merge_lists(res, ho->lst);
            ho->lst = nullptr; // stolen elems
        }
        ho = ho->next;
    }
    return res;
}


int main() {

    Node* lst1 = new Node{1, new Node{3, new Node{5, new Node {9}}}};
    Node* lst2 = new Node{0, new Node{2, new Node{5, new Node {8}}}};
    Node* lst3 = nullptr;
    Node* lst4 = new Node{5, new Node{15, new Node{3}}};
    Node* lst5 = new Node{17};

    HOList* ho = new HOList{ lst1, new HOList{lst2, new HOList{lst3, new HOList{lst4, new HOList{lst5}}}}};

    Node* merged = merged_sorted(ho);

    print_lst(merged);

    clear_list(merged);
    clear_ho_list(ho);

    return 0;
}