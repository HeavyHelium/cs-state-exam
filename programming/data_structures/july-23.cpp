#include <iostream>


struct Node {
    int X = 0; // X < Y
    int Y = 0; 
    // X == Y iff само X има стойност
    Node* left = nullptr; // < X
    Node* mid = nullptr; // >= X & < Y 
    Node* right = nullptr; // > Y
};




void insert(Node*& root, int value) {
    // emptry tree
    if(root == nullptr) {
        root = new Node{value, value};
        return;
    } 

    if(root -> X > value) {
        insert(root -> left, value);
        return;
    } // value < X cases handled

    if(root -> X == root -> Y && value == root -> X) {
        insert(root->mid, value);
        return;
    } // X == Y and value == X

    if(root -> X == root -> Y && value > root -> X) {
        root -> Y = value;
        return;
    } // X == Y and value > X

    // X == Y cases handled
    
    
    if(value < root->Y) {
        insert(root->mid, value);
        return;
    } 
    if(root->Y <= value) {
        insert(root->right, value);
        return;
    }

}


bool find(const Node* root, int value) {
    if(root == nullptr) {
        return false;
    }

    if(root->X == value || root-> Y == value) {
        return true; 
    }
    if(value < root->X) {
        return find(root->left, value);
    } else if(value > root->X && value <= root->Y) {
        return find(root->mid, value);        
    } else {
        return find(root->right, value);
    }
}


void free_tree(Node*& tree) {
    if(!tree) {
        return;
    }

    free_tree(tree->left);
    free_tree(tree->mid);
    free_tree(tree->right);

    delete tree;
    tree = nullptr;
}


int main() {
    Node* tree = nullptr;
    int N = 0;
    std::cin >> N;
    int temp = 0;
    
    std::cout << "Input " << N << " numbers, please: \n";
    
    while(N--) {
        std::cin >> temp; 
        insert(tree, temp); 
    }    
    

    std::cout << "enter a number to check: " << std::endl;
    
    int checker = 0;
    
    std::cin >> checker;
    std::cout << "The number " << checker << " is ";


    if(!find(tree, checker)) {
        std::cout << "not ";
    }
    std::cout << "contained in tree!" << std::endl;

    free_tree(tree);

    return 0;

}