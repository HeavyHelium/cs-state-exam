#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Node {
    std::string text;
    Node* next = nullptr;
};


void unite(Node*& head) {
    if(!head) {
        return;
    }
    Node* iter = head; // head is start
    bool end = false;
    while(!end) {
        if(iter->next == head) {
            end = true;
        }
        while(!iter->text.empty() && !iter->next->text.empty() && 
              iter->text.back() == iter->next->text.front() && iter != iter->next) {
            if(iter->next == head) {
                head = head->next;
                end = true;
            }
            iter->text += "-" + iter->next->text;
            Node* temp = iter->next;
            iter->next = iter->next->next;
            delete temp;
        }
        if(end) {
            iter->next = head;
        } else {
            iter = iter->next;
        }
    }
}



void print(Node* head) {
    if(!head) {
        std::cout << "empty\n";
        return;
    }
    Node* iter = head;
    do {
        std::cout << iter->text << " ";
        iter = iter->next;
    } while(iter != head);
}


void insert(Node*& root, const std::string& elem) {
    if(!root) {
        root = new Node{ elem };
        root->next = root;
        return;
    }
    Node* iter = root;

    do {
        iter = iter->next;
    } while(iter->next != root);

    iter->next = new Node{ elem, root };
}


void clear_lst(Node* root) {
    if(!root) return;
    Node* iter = root;

    do { 
        Node* temp = iter->next;
        delete iter;
        iter = temp;
    } while(iter != root);
}

void print_lex_easy(const Node* root) {
    if(!root) {
        std::cout << "empty list" << std::endl;
        return;
    }
    std::vector<std::string> dict;
    const Node* iter = root;
    do {
        dict.push_back(iter->text);
        iter = iter->next;
    } while(iter != root);

    std::sort(dict.begin(), dict.end());

    for(const std::string& elem: dict) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
} 


void print_lex_only_min(const Node* root) {
    if(!root) { return; }
    Node const* min = root;
    Node const* iter = root;
    do {
        if(iter->text < min->text) {
            min = iter;
        }
        iter = iter->next;
    } while(iter->next != root);

    std::cout << min->text << '\n';

    iter = root;

    do {
        if(iter != min) {
            std::cout << iter->text << '\n';
        }
        iter = iter->next;
    } while(iter != root);
}

int main() {
    Node* lst = nullptr;
    std::string read;
    while(std::getline(std::cin, read)) {
        if(read == "stop") break;
        insert(lst, read);
    }    

    unite(lst);
    print(lst);
    std::cout << "\nLexicographically: \n";
    //print_lex_easy(lst);
    print_lex_only_min(lst);

    clear_lst(lst);

    return 0;
}

/*
street
taxi
ink
dog
smile
eat
tall
pass
stop

 */

