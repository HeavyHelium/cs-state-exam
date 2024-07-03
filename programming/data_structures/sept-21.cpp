#include <iostream>
#include <vector>
#include <list>


struct NodeInfo {
    int level;
    int value;
};

using TreeSeq = std::vector<NodeInfo>;


struct Node {
    int value;
    std::list<Node*> children;
};


void clearTree(Node* t) {
    if(!t) return;
    for(Node* child: t->children) {
        clearTree(child);
    }
    delete t;
}

Node* buildTree(const TreeSeq& seq, int level, int& cid) {
    if(cid == seq.size()) return nullptr;

    Node* root = new Node{ seq[cid].value };
    cid += 1;
    while(cid < seq.size() && level + 1 == seq[cid].level) {
        
        Node* child = buildTree(seq, level + 1, cid);
        if(child) { 
            root->children.push_back(child);
        } else {
            clearTree(root);
            return nullptr;
        }
    }
    if(cid < seq.size()  && seq[cid].level > level + 1) {
        clearTree(root);
        return nullptr;
    }
    if(level == 0 && cid < seq.size() && seq[cid].level == level) {
        clearTree(root);
        return nullptr;
    }

    return root;
}


void print(const Node* root, int level=0) {
    if(!root) return;

    std::cout << "(" << level << ", "<< root->value << ")" << ", ";
    for(const Node* child : root->children) {
        print(child, level + 1);
    }
}


int main() {
    TreeSeq seq = { NodeInfo{0, 5}, NodeInfo{1, 4}, NodeInfo{1, 5}, 
                    NodeInfo{2, 3}, NodeInfo{1, 6}, NodeInfo{2, 2}, 
                    NodeInfo{3, 3}, NodeInfo{2, 5}};
    int cid = 0;
    Node* root = buildTree(seq, 0, cid);
    
    print(root);
    std::cout << std::endl;
    clearTree(root);

    cid = 0;
    TreeSeq seq1 = { NodeInfo{0, 1}, NodeInfo{2, 2}, NodeInfo{1, 3} };
    Node* root1 = buildTree(seq1, 0, cid);
    std::cout << (root1 ? "unexp\n" : "nullptr as required\n");

    print(root1);
    clearTree(root1);
 

    return 0;
}