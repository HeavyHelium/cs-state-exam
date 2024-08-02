#include <iostream>

/*
Да се дефинира клас BinTree, който представя двоично дърво с наредба на
синовете и ориентация на ребрата от родител към дете, надписано със символи по върховете.
Ориентираният път между два върха на дървото се представя с низа от надписите на
последователните върхове на пътя.
а) (2 т.) Да се дефинират член-данни и помощни структури за класа BinTree, които са
необходими за избраното представяне.
б) (3 т.) Да се реализира член-функция isSymmetric(), която проверява дали двоичното дърво
е симетрично относно наредбата на синовете (ляво-дясно), т.е. дали съвпада с огледалния си
образ.
в) (3 т.) Да се реализира член-функция appendTree(t) която вмъква дадено двоично дърво t на
мястото на всички листа на дървото, чиито надписи съвпадат с надписа в корена на t.
г) (4 т.) Да се реализира член-функция contains(s), която проверява дали даден низ s
представя път в дървото.



*/

struct Node {
    char data;
    Node* child1 = nullptr;
    Node* child2 = nullptr;
};

class BinTree {
    Node* root = nullptr;

public:
    BinTree() {}
    BinTree(const BinTree& other): root(copy(root)) {}
    BinTree& operator=(const BinTree& other) {
        if(this != &other) {
            Node* c = copy(other.root);
            free_tree(root);
            root = c; 
        }
        return *this;
    }

    bool isSymmetric() const {
        if(!root) return true;

        return symmetric(root->child1, root->child2);
    }

    void appendTree(const BinTree& t) {
        append_leaves(t.root, root);
    }

    bool contains(const char* p) const {
        return contains(root, p);
    }

    ~BinTree() {
        free_tree(root);
    }

private:
    static Node* copy(const Node* other) {
        if(!other) return nullptr;

        Node* root = new Node { other->data, 
                                copy(other->child1), 
                                copy(other->child2),  };
        return root;
    }

    static void free_tree(Node* root) {
        if(!root) return;

        free_tree(root->child1);
        free_tree(root->child2);

        delete root;
    }

    static bool symmetric(const Node* root1, const Node* root2) {
        if(!root1 && !root2) return true;
        if(!root1 || !root2) return false;

        if(root1->data != root2->data) return false;
         
        return symmetric(root1->child1, root2->child2) && 
               symmetric(root1->child2, root2->child1);
    }

    static void append_leaves(const Node* tree, Node*& curr) {
        if(!curr) return;
        if(!curr->child1 && !curr->child2) {
            append_tree(tree, curr);
            return;
        }
        append_leaves(tree, curr->child1);
        append_leaves(tree, curr->child2);
    }

    static void append_tree(const Node* tree, Node*& curr) {
        if(!curr) return;
        if(tree->data != curr->data) {
            return;
        }
        if(curr->child1 || curr->child2) return;
        Node* c = copy(tree);
        delete curr;
        curr = c;
    }

    static bool contains(const Node* root, const char* path) {
        if(!root && !*path) return true;
        if(!root || !*path) return false;
        if(root->data != *path) return false;

        return contains(root->child1, path + 1) || 
               contains(root->child2, path + 1);
    }
    

};


int main() {



}