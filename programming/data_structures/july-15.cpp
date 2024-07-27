#include <iostream>
#include <vector>
#include <queue>

/*
Следната задача да се реши на един от езиците за програмиране C++ или Java.
Да се обозначи явно на кой от двата езика е решавана задачата. При решението на задачата да не
се използват библиотеки за работа със структури от данни.
а) Да се дефинира подходяща индуктивна (рекурсивна) структура от данни, позволяваща
представянето в паметта на програмата на възел на дърво от цели числа (int), за което всеки връх
може да има произволен брой наследници (0, 1 или повече).
б) Да се дефинира рекурсивна функция (или статичен метод)
[булев тип] member ([подходящ тип]root, int x)
чиято стойност е истина точно тогава, когато в дървото с корен, представен от параметъра root,
съществува възел със стойност x.
в) Да се дефинира рекурсивна функция (или статичен метод)
void filterOdd ([подходящ тип] root)
Функцията да премахва (чрез мутация) всяко поддърво t’на дървото с корен, представен от
параметъра root, за което е изпълнено, че коренът на t’е със стойност нечетно число. На
следната фигура е показано примерно дърво преди и след изпълнението на операцията
filterOdd.


 */

struct Node {
    int value = 42;
    std::vector<Node*> children;

    void self_destruct() {
        for(Node* child: children) {
            child->self_destruct();
        }
        delete this;
    }
};  

// кореново дърво представяме с корена му


bool member(Node* root, int x) {
    if(!root) return false;
    if(root->value == x) return true;

    for(Node* child: root->children) {
        if(member(child, x)) return true;
    }

    return false;
}

void filterOdd(Node*& root) {
    if(root->value % 2 != 0) {
        root->self_destruct();
        root = nullptr;

        return;
    }
    for(Node*& child : root->children) {
        filterOdd(child);
    }
    int write = 0;
    for(int i = 0; i < root->children.size(); ++i) {
        if(root->children[i]) root->children[write++] = root->children[i]; 
    }

    for(int i = 1; i <= root->children.size() - write; ++i) {
        root->children.pop_back();
    }
}


void printBFS(Node* root) {
    if(!root) return;
    std::queue<Node*> q;
    q.push(root);
    int curr = 1;
    int next = 0;
    while(!q.empty()) {
        Node* n = q.front();
        q.pop();
        std::cout << n->value << " ";
        --curr;
        for(Node* child: n->children) {
            q.push(child);
            ++next;
        }
        if(!curr) {
            std::swap(curr, next);
            std::cout << '\n';
        }
    }

}




int main() {

    Node* temp = new Node {8, {new Node{2}, new Node{3, {new Node{4}, new Node{5}, new Node{6}}}}};

    printBFS(temp);

    filterOdd(temp);
    printBFS(temp);
    temp->self_destruct();
    

    return 0;
}