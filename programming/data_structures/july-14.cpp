#include <iostream>
#include <climits>


struct Node {
    Node* next = nullptr;
    int data;
};


int length(Node* ll) {
    if(!ll) return 0;
    int len = 0;
    Node* iter = ll;

    do {
        len += 1;
        iter = iter->next;
    } while(iter != ll);
    return len;
}

void printCircularList(Node* head) {
    if (!head) return;
    Node* curr = head;
    do {
        std::cout << curr->data << " ";
        curr = curr->next;
    } while (curr != head);
    std::cout << std::endl;
}

Node* preceeds(Node* L, int M, int N) {
    Node* iter = L;
    if(!iter || !iter->next) return nullptr;
    do {
        if(iter->data == M && iter->next->data == N) {
            return iter;
        }
        iter = iter->next;
    } while(iter != L);


    return nullptr;
}


Node* merge(Node* L1, Node* L2, Node* A, Node* B) {
    Node dummy;
    Node* to_del = nullptr;

    int M = A->data;
    int N = A->next->data;
    to_del = B;

    Node* curr = &dummy;
    Node* iter = A->next;
    while(iter != A) {
        curr->next = iter;
        iter = iter->next;
        curr = curr->next;
    }
    curr->next = A;
    curr = curr->next;
    Node* temp = A->next;

    Node* iter2 = B->next->next;
    while(iter2 != B) {
        curr->next = iter2;
        iter2 = iter2->next;
        curr = curr->next;
    }
    curr->next = temp;

    
    delete to_del->next;
    delete to_del;


    return dummy.next;

}


Node* merge(Node* L1, Node* L2) {
    if(!L1 || !L2 || !L1->next || !L2->next) return nullptr;

    Node* iter = L1; 
    int sum = INT_MIN;

    Node* A = nullptr;
    Node* B = nullptr;
    do {    
        if(iter->data + iter->next->data <= sum) {
            iter = iter->next;
            continue;
        }    
        sum = iter->data + iter->next->data;
        
        Node* b_poten = preceeds(L2, iter->next->data, iter->data);
        if(b_poten) {
            A = iter;
            B = b_poten;
        } else {
            iter = iter->next;
            continue;
        }
        iter = iter->next;

    } while(iter != L1);

    return A ? merge(L1, L2, A, B) : nullptr;
}




void clear(Node* L) {
    if(!L) return;
    Node* iter = L;

    do {
        Node* temp = iter;
        iter = iter->next;
        delete temp;
    } while(iter != L);
}


void split(Node* L) {
    int len = length(L);
    Node* A = L; 
    Node* B = A;
    int M = A->data;
    
    for(int i = 0; i <= len / 2; ++i) {
        B = B -> next;
    }

    int N = B->data;

    Node L1;
    Node* curr = &L1;
    for(Node* iter = A; iter != B; iter = iter->next) {
        curr->next = iter;
        curr = curr->next;
    }
    curr->next = B;
    
    Node* iter = B->next;
    B->next = A;

    Node L2;
    L2.next = new Node{ nullptr, N };
    curr = L2.next;
    while(iter != A) { 
        curr->next = iter;
        curr = curr->next;
        iter = iter->next;
    }
    curr->next = new Node { L2.next, M };

    printCircularList(L1.next);
    printCircularList(L2.next);
    clear(L1.next);
    clear(L2.next);
}


Node* createCircularList(int arr[], int size) {
    if (size == 0) return nullptr;
    Node* head = new Node{nullptr, arr[0]};
    Node* curr = head;
    for (int i = 1; i < size; ++i) {
        curr->next = new Node{nullptr, arr[i]};
        curr = curr->next;
    }
    curr->next = head; 
    return head;
}


int main() {
    int arr1[] = {1, 2, 3, 4, 5, 3};
    Node* L1 = createCircularList(arr1, 6);
    printCircularList(L1);
    int arr2[] = {2, 5, 8, 4, 3};

    Node* L2 = createCircularList(arr2, 5);
     printCircularList(L2);
    
    Node* mergedList = merge(L1, L2);
    std::cout << "Merged List: ";
    printCircularList(mergedList);
    split(mergedList);

    return 0;
}