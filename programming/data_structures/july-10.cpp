#include <iostream>
#include <utility>

/*
(15 точки) Класът DLList, представя списък с две връзки, съдържащ числа с плаваща
запетая. Дефиницията на класа е следната:
struct node {
double data;
node* next;
node* prev;
};
class DLList {
private:
node* start; // указател към началото на списъка
node* end; // указател към края на списъка
node* forwardIter; // итератор за обхождане напред
node* backwardIter; // итератор за обхождане назад
public:
// функции от голямата четворка
DLList();
DLList(DLList const&);
DLList& operator=(DLList const&);
~DLList();
// вмъква числото x пред клетката p
void insertBefore(node* p, double x);
// вмъква числото x след клетката p
void insertAfter(node* p, double x);
// премахва клетката p от списъка
void insertAfter(node* p, double x);
// установява forwardIter да сочи към началото на списъка
// или към клетката p, ако ѐ е зададена ненулева стойност
void startForward(node* p=NULL);
// установява backwardIter да сочи към началото на списъка
// или към клетката p, ако ѐ е зададена ненулева стойност
void startBackward(node* p=NULL);
// премества forwardIter напред и връща старата му стойност
node* nextForward();
// премества backwardIter напред и връща старата му стойност
node* nextBackward();
};
а) (3 т.) Да се дефинират член-функциите от голямата четворка;
б) (3 т.) Да се дефинират член-функциите insertBefore и insertAfter;
15.07.2010г. ДИ ОКС „Бакалавър” по Компютърни науки, СУ-ФМИ фак. № стр. 6/12
в) (2 т.) Да се дефинира член-функцията deleteElem;
г) (3 т.) Да се дефинира функцията bool mirror(DLList& dl1, DLList& dl2), която проверява дали
списъкът dl1 е огледален образ на dl2, т.е. дали dl1 се състои от елементите на dl2 в обратен ред


*/

struct node {
    double data;
    node* next = nullptr;
    node* prev = nullptr;

};

class DLList {

    node* start = nullptr;
    node* end = nullptr;
    node* forwardIter = nullptr;
    node* backwardIter = nullptr;

public: 

    DLList() {
    }
    DLList(const DLList& other) {
        copy(other.start, start, end);
    }
    DLList& operator=(const DLList& other) {
        if(this != &other) {
            free(start);
            copy(other.start, start, end);
        } 
        return *this;
    }

    void insertBefore(node* p, double X) {
        if(!p) {
            start = end = new node{ X };
            return;
        }
        node* n = new node{ X, p, p->prev };
        if(p->prev) p->prev->next = n;
        else start = n;
        p->prev = n;
    }

    void insertAfter(node* p, double X) {
        if(!p) {
            start = end = new node{ X };
            return;
        }
        node* n = new node{ X, p->next, p };
        if(p->next) p->next->prev = n; 
        p->next = n;
        if(p == end) end = n;
    }

    void startForward(node* p=nullptr) {

        if(!p) forwardIter = start;
        else forwardIter = p;
    }

    void startBackward(node* p=nullptr) {
        if(!p) backwardIter = end;
        else backwardIter = p;
    }

    node* nextForward() {
        node* temp = forwardIter;
        forwardIter = forwardIter? forwardIter->next : nullptr;
        return temp;
    }

    node* nextBackward() {
        node* temp = backwardIter;
        backwardIter = backwardIter ? backwardIter->prev : nullptr;
        return temp;
    }


    void deleteElem(double elem) {
        if(!start) return;
        node* iter = start;
        while(iter && iter->data != elem) {
            iter = iter->next;
        }
        if(!iter) return;


        if(start == end) {
            delete iter;
            start = end = nullptr;
            return;
        }
        if(iter->prev) {
            iter->prev->next = iter->next;
        } else {
            start = iter->next;
        }
        if(iter->next) {
            iter->next->prev = iter->prev;
        } else {
            end = iter->prev;
        }
        delete iter;
    }


    void deleteElem(node* p) {
        if(p->prev) {
            p->prev->next = p->next;
        } else {
            start = p->next;
        }

        if(p->next) p->next->prev = p->prev;
        else end = p->prev;

        delete p;
    }


    static bool mirror(DLList& dl1, DLList& dl2) {
        node* iter1 = dl1.start;
        node* iter2 = dl2.end;

        while(iter1 && iter2 && iter1->data == iter2->data) {
            iter1 = iter1->next;
            iter2 = iter2->prev;
        }
        return !(iter1 || iter2);
    }

    ~DLList() {
        free(start);
    }

    node* first() {
        return start;
    }

    node* last() {
        return end;
    }

    static node* split(DLList& dl, double x) {
        // hoare partition on a list
        dl.startForward();
        dl.startBackward();

        node* i = dl.nextForward();
        node* j = dl.nextBackward();

        while(i && j && i != j && j->next != i) {
            // std::cout << "here: " << i->data << ", " << j->data << std::endl;
            while(i && i->data < x) i = dl.nextForward();
            while(j && j->data >= x) j = dl.nextBackward();

            if(i && j && i != j && j->next != i) {
                std::swap(i->data, j->data);
            }
            

        }
        return i? i->prev : nullptr;
    }

    friend std::ostream& operator<<(std::ostream& os, DLList& ll) {
        ll.startForward();
        node* n;
        while(n = ll.nextForward()) {
            os << n->data << " ";
        }
        return os << std::endl;
    }

private: 

    static void copy(const node* rs, node*& ws, node*& we) {
        if(!rs) return;
        node* chain = new node{rs->data};
        rs = rs->next;
        ws = chain;
        while(rs) {
            chain->next = new node{ rs->data, nullptr, chain };
            chain = chain->next;
            rs = rs->next;
        }
        we = chain;
    }

    static void free(node* lst) {
        if(!lst) return;

        while(lst) {
            node* temp = lst;
            lst = lst->next;
            delete temp;
        }
    }


};


int main() {

    DLList list1;
    DLList list2;

    list1.insertAfter(list1.last(), 1.1);
    list1.insertAfter(list1.last(), 2.2);
    list1.insertAfter(list1.last(), 3.3);

    list2.insertAfter(list2.last(), 3.3);
    list2.insertAfter(list2.last(), 2.2);
    list2.insertAfter(list2.last(), 1.1);

    if (DLList::mirror(list1, list2)) {
        std::cout << "list1 is a mirror of list2" << std::endl;
    } else {
        std::cout << "list1 is not a mirror of list2" << std::endl;
    }
    
    node* n;
    list1.startForward();
    while(n = list1.nextForward()) {
        std::cout << n->data << " ";
    } std::cout << std::endl;

    list1.startBackward();
    while(n = list1.nextBackward()) {
        std::cout << n->data << " ";
    } std::cout << std::endl;

    DLList list3;

    list3.insertAfter(list3.last(), 1.1);
    list3.insertAfter(list3.last(), 7);
    list3.insertAfter(list3.last(), 3.3);
    list3.insertAfter(list3.last(), 5.3);
    list3.insertAfter(list3.last(), -3.3);
    list3.insertAfter(list3.last(), 2.3);
    list3.insertAfter(list3.last(), 0.5);
    list3.insertAfter(list3.last(), -16);
    
    std::cout << list3;
    std::cout << DLList::split(list3, 0) -> data << std::endl;
    std::cout << list3;

    // node* iter = list1.first();
    // while(iter) {
    //     std::cout << iter->data << " ";
    //     iter = iter->next;
    // } std::cout << std::endl;

    // list1.startForward();

    //std::cout << list1;
    // std::cout << list2;

    return 0;
}



/*

1.1 7 3.3 5.3 -3.3 2.3 0.5 -16


1.1 7 3.3 5.3 -3.3 2.3 0.5 -16

1.1 -16 0.5 2.3 -3.3 5.3 3.3 7


 */