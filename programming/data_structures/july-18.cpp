#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>
#include <string>
#include <fstream>


struct Node {
    char ch;
    Node* child1 = nullptr;
    Node* child2 = nullptr;
    Node* child3 = nullptr;
};

int height(Node* root) {
    if(!root) {
        return 0;
    }

    int h1 = height(root->child1);
    int h2 = std::max(height(root->child2), height(root->child3));

    return 1 + std::max(h1, h2);
}


std::string readLast(Node* root) {
    if(!root) return "";
    std::string res;

    std::queue<Node*> q;
    q.push(root);

    int curr = 1;
    int next = 0;
    int curr_level = 1;

    int last_level = height(root);

    while(!q.empty()) {
        Node* n = q.front();
        q.pop();
        --curr;

        if(curr_level == last_level) {
            res.push_back(n->ch);
        }

        if(n->child1) { q.push(n->child1); ++next; };
        if(n->child2) { q.push(n->child2); ++next; };
        if(n->child3) { q.push(n->child3); ++next; };

        if(curr == 0) {
            ++curr_level;
            curr = next;
            next = 0;
        }
    }
    return res;
}


void clear_tree(Node* root) {
    if(!root) return;

    clear_tree(root->child1);
    clear_tree(root->child2);
    clear_tree(root->child3);

    delete root;
}

void serialize_stream(Node* root, std::ostream& os) {
    if(!root) { os << '*'; return; }
    os << '(' << root->ch << " ";
    serialize_stream(root->child1, os); os << " ";
    serialize_stream(root->child2, os); os << " ";
    serialize_stream(root->child3, os);
    os << ")";
}


void serialize(Node* root, const std::string& path) {
    std::ofstream os(path);
    serialize_stream(root, os);
    os.close();
}



int main() {
    Node* root = new Node{'b', new Node{'x', new Node{'p'}, 
                                            new Node{'q'}, 
                                            new Node{'r', new Node{'c'}, 
                                                        nullptr, 
                                                        new Node {'a'}}}, 
                                            new Node{'y', nullptr, 
                                                         nullptr, 
                                                         new Node{'s', new Node{'t'}}}};
    std::string res = readLast(root);
    std::cout << res << std::endl;

    serialize_stream(root, std::cout);
    serialize(root, "./tree.txt");
    clear_tree(root);




    return 0;
}