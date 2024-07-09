#include <iostream>
#include <vector>
#include <queue>


struct Node {
    int data;
    std::vector<Node*> children;
};


Node* build_bfs(const int K, int* arr, int length) {
    if(!length) return nullptr;
    Node* root = new Node{*arr};
    ++arr;
    --length;
    std::queue<Node*> q;
    q.push(root);


    while(!q.empty()) {
        Node* n = q.front();
        q.pop();
        for(int i = 0; i < K && i < length; ++i) {
            Node* child = new Node{*arr};
            ++arr;
            --length;
            n->children.push_back(child);
            q.push(child);
        }
    }

    return root;
}


void print_bfs(Node* root) {
    if(!root) return;

    std::queue<Node*> q;
    q.push(root);
    int curr = 1;
    int next = 0;

    while(!q.empty()) {
        Node* n = q.front();
        q.pop();
        --curr;

        std::cout << n->data << " ";

        for(Node* child : n->children) {
            q.push(child);
            ++next;
        }

        if(!curr) {
            curr = next;
            next = 0;
            std::cout << std::endl;
        }
    }
}


int depth(Node* root) {
    if(!root) return 0;

    int max_children = 0;

    for(Node* child: root->children) {
        int temp = depth(child);
        if(temp > max_children) {
            max_children = temp;
        }
    }

    return max_children + 1;
}




void clear_tree(Node* root) {
    if(!root) return;

    for(Node* child: root->children) {
        clear_tree(child);
    }

    delete root;
}



int main() {


    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int K = 3;
    int length = sizeof(arr) / sizeof(int);

    Node* root = build_bfs(K, arr, length);
    print_bfs(root);

    std::cout << "Depth of tree: " << depth(root) << std::endl;
    
    clear_tree(root);
    return 0;
}