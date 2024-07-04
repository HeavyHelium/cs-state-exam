#include <iostream>
#include <list>


struct Node {

    char sym;
    int val;

    std::list<Node*> children;
};




int sumVal(Node* u, Node* v, bool& succ) {

    if(!u && !v) {
        succ = true;
        return 0;
    }
    if(!u && v || u && !v) { 
        succ = false; 
        return 0; 
    };

    if(u->sym != v->sym) { 
        succ = false;
        return 0;
    }

    if(u->children.empty() && v->children.empty()) {
        succ = true;
        return u->val + v->val;
    }

    int sum = 0;
    succ = false;
    bool my_succ = false;

    for(Node* child_u : u->children) {
        for(Node* child_v: v->children) {
            int temp = sumVal(child_u, child_v, succ);
            if(succ) {
                sum += u->val + v->val + temp;
                my_succ = true;
            }
        }
    }
    succ = my_succ;
    return sum;
}


void clear_tree(Node* root) {
    if(!root) return;
    for(Node* child : root->children) {
        clear_tree(child);
    }
    delete root;
}


int main() {

    Node* root1 = new Node{'a', 1, {}};
    Node* child1 = new Node{'b', 2, {}};
    Node* child2 = new Node{'c', 3, {}};
    root1->children.push_back(child1);
    root1->children.push_back(child2);

    Node* root2 = new Node{'a', 4, {}};
    Node* child3 = new Node{'b', 5, {}};
    Node* child4 = new Node{'c', 6, {}};
    root2->children.push_back(child3);
    root2->children.push_back(child4);

    bool succ;
    int result = sumVal(root1, root2, succ);

    if (succ) {
        std::cout << "Sum of values: " << result << std::endl;
    } else {
        std::cout << "No matching branches found." << std::endl;
    }

    clear_tree(root1);
    clear_tree(root2);



    return 0;
}