#include <iostream>


struct Node {
    Node* next = nullptr;
    Node* prev = nullptr;
    int data = 0;
};



void join(Node* begin1, Node* end1, 
          Node* begin2, Node* end2) {

    int Y = 0;
    Node* iter1 = end1;
    Node* iter2 = begin2;
    while(iter1 && iter2) {
        std::cout << iter1->data << ", " << iter2->data << "\n";
        if(iter1->data == iter2->data) {
            begin2->prev = iter1;
            end1->next = iter2;
            std::cout << "Y: " << Y << std::endl;
            break;
        } else {
            iter1 = iter1->prev;
            iter2 = iter2->next;
            ++Y;
        }

    }
                    
}



bool isJoined(Node* begin, Node* end) {
    return end->next != nullptr;
}


int sum(Node* begin, Node* end) {
    if(!begin) return 0;
    Node* iter2 = end->next;
    Node* iter1 = end;

    while(iter1->data != iter2->data) {
        iter1 = iter1->prev;
    } 


    int sum_below = 0;
    Node* iter_down = end->next;
    while(iter_down) {
        sum_below += iter_down->data;
        iter_down = iter_down->next;
    }

    iter_down = iter2->prev;
    while(iter_down != iter1) {
        sum_below += iter_down->data;
        iter_down = iter_down->prev;
    }

    Node* above = begin;
    int sum_above = 0;

    while(above != end) {
        sum_above += above->data;
        above = above->next;
    }
    sum_above += end->data;

    return sum_above + sum_below;
}


void clean_lllst(Node* begin, Node* end) {
    if(!begin) return;
    Node* iter2 = end->next;
    Node* iter1 = end;

    while(iter1->data != iter2->data) {
         iter1 = iter1->prev;
    } 

    Node* curr = iter2->next;
    while(curr) {
         Node* temp = curr->next;
         delete curr;
         curr = temp;
    }
    curr = iter2;
     while(curr != iter1) {
         Node* temp = curr->prev;
         delete curr;
         curr = temp;
     }

    end->next = nullptr;
    
    while(begin) {
      Node* temp = begin->next;
      delete begin;
      begin = temp;
    }

}


int main() {
    // Create two lists L1 and L2
    Node* n1 = new Node{nullptr, nullptr, 1};
    Node* n2 = new Node{nullptr, n1, 3};
    Node* n3 = new Node{nullptr, n2, 5};
    Node* n4 = new Node{nullptr, n3, 7};
    Node* n5 = new Node{nullptr, n4, 9};
    Node* n6 = new Node{nullptr, n5, 6};
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n6;

    Node* m1 = new Node{nullptr, nullptr, 3};
    Node* m2 = new Node{nullptr, m1, 4};
    Node* m3 = new Node{nullptr, m2, 8};
    Node* m4 = new Node{nullptr, m3, 5};
    Node* m5 = new Node{nullptr, m4, 7};
    m1->next = m2;
    m2->next = m3;
    m3->next = m4;
    m4->next = m5;


    join(n1, n6, m1, m5);


    if (isJoined(n1, n6)) {
        std::cout << "Lists are joined!" << std::endl;

        int total = sum(n1, n6);
        std::cout << "Sum of elements: " << total << std::endl;
    } else {
        std::cout << "Lists are not joined." << std::endl;
    }

    clean_lllst(n1, n6);

    return 0;
}

// 31
// 27