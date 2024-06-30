#include <iostream>

class BinaryTree {

    struct Node {
        int data;
        Node* left = nullptr;
        Node* right = nullptr;
    };

public:
    BinaryTree() = default;
    BinaryTree(const int data) : root(new Node{ data }) {}

    BinaryTree(const BinaryTree& other)
        : root(copy(other.root)) {
    }
    BinaryTree& operator=(const BinaryTree& other) {
        if(this != & other) {
            Node* cp = copy(other.root);
            root = cp;
        }
        return *this;
    }

    std::size_t size() const {
        return size(root);
    }

    std::size_t height() const {
        return height(root);
    }

    void insert_subtree(const BinaryTree& subtree, bool left=true) {
        if(root) {
            Node* new_sub = copy(subtree.root);
            if(left) {
                clear(root->left);
                root->left = new_sub;
            } else {
                clear(root->right);
                root->right = new_sub;
            }
        } else {
            *this = subtree;
        }
    }

    void print_inorder() const {
        print_inorder(root);
        std::cout << std::endl;
    }

    ~BinaryTree() {
        clear(root);
    } 

private:
    static Node* copy(const Node* root) {
        return root ? new Node{ root->data, copy(root->left), copy(root->right)} : nullptr; 
    }

    static void clear(Node* root) {
        if(!root) {
            return;
        }
        clear(root->left);
        clear(root->right);
        delete root;
    }


    static std::size_t size(const Node* root) {
        if(!root) return 0;
        return 1 + size(root->left) + size(root->right);
    }

    static std::size_t height(const Node* root) {
        if(!root) {
            return 0;
        } 
        return 1 + std::max(height(root->left), height(root->right));
    }

    static void print_inorder(const Node* node) {
        if(!node) return;
        print_inorder(node->left);
        std::cout << node->data << " ";
        print_inorder(node->right);
    }

    Node* root = nullptr;
};


int main() {
    BinaryTree tree(1);

    BinaryTree leftSubtree(2);
    leftSubtree.insert_subtree(BinaryTree(4), true);  // Insert 4 as left child of 2
    leftSubtree.insert_subtree(BinaryTree(5), false); // Insert 5 as right child of 2

    BinaryTree rightSubtree(3);
    rightSubtree.insert_subtree(BinaryTree(6), true);  // Insert 6 as left child of 3
    rightSubtree.insert_subtree(BinaryTree(7), false); // Insert 7 as right child of 3

    tree.insert_subtree(leftSubtree, true);   // Insert leftSubtree at the left of root
    tree.insert_subtree(rightSubtree, false); // Insert rightSubtree at the right of root

    std::cout << "In-order traversal: ";
    tree.print_inorder();

    std::cout << "Tree size: " << tree.size() << std::endl;
    std::cout << "Tree height: " << tree.height() << std::endl;


    return 0;
}