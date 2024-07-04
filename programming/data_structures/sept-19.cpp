#include <iostream>
#include <climits>
#include <list>


struct Node {

    char label = -1; // only root has label -1
    int value = INT_MIN;
    std::list<Node*> children;
};


void clear_tree(Node* root) {
    if(!root) return;

    for(Node* child: root->children) {
        clear_tree(child);
    }

    delete root;
}

void CommonBranches(Node* u, Node* v, int k, std::string& word) {
    if(!u || !v) { return; }
    if(k == 0 && u->children.empty() && v->children.empty()) {
        std::cout << word << std::endl;
        return;
    }

    for(Node* child_u : u->children) {
        for(Node* child_v : v->children) {
            int curr_val = child_u->value + child_v->value;

            if(child_u->label == child_v->label && 
                curr_val <= k) {
                word.push_back(child_u->label);
                CommonBranches(child_u, child_v, k - curr_val, word);
                word.pop_back();
            }
        }
    }
}

void CommonBranches(Node* u, Node* v, int k) {
    std::string word = "";
    CommonBranches(u, v, k, word);
}




int main() {

 Node* root = new Node{'-', 0}; // root node with dummy label and value
 // Create nodes using Node{}
    Node* u = new Node{'u', 5};
    Node* v = new Node{'v', 4};
    Node* a1 = new Node{'a', 2};
    Node* a2 = new Node{'a', 3};
    Node* b1 = new Node{'b', 1};
    Node* b2 = new Node{'b', 5};
    Node* c = new Node{'c', 5};
    Node* d = new Node{'d', 4};
    Node* e = new Node{'c', 2};
    Node* f = new Node{'d', 3};

    root->children.push_back(u);
    root->children.push_back(v);
    u->children.push_back(a1);
    u->children.push_back(b1);
    a1->children.push_back(c);
    a1->children.push_back(d);
    v->children.push_back(a2);
    v->children.push_back(b2);
    a2->children.push_back(e);
    a2->children.push_back(f);

    // Find common branches starting from nodes 'u' and 'v' with value sum 'k'
    CommonBranches(u, v, 6); // Adjust 'k' as needed
    CommonBranches(u, v, 12); // Adjust 'k' as needed    

    // Clean up memory
    clear_tree(root);
    return 0;
}