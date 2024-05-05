#include <iostream>
#include <cstddef>

class BST {

    struct Node {
        int data;
        Node* left = nullptr;
        Node* right = nullptr;
    };


public: 
    BST() = default;
    BST(const BST& other)
        : root(copy(other.root)), size(other.size) {
    }

    BST& operator=(const BST& other) {
        if(this != & other) {
            Node* cp = copy(other.root);
            clear(root);
            root = cp;
            size = other.size;
        }
        return *this;
    }

    void insert(const int elem) {
        insert(root, elem);
        ++size;
    }

    bool remove(const int key) {
        bool res = remove(root, key);
        if(res) {
            --size;
            return true;
        }
        return false;
    }

    std::size_t height() const {
        return height(root);
    }
    std::size_t weight() const {
        return size;
    }

    bool balanced() const {
        return balanced(root);
    }

    bool perfectly_balanced() const {
        return perfectly_balanced(root);
    }


    bool find(const int elem) {
        return find(root, elem);
    }

    void print() {
        print_inorder(root);
    }


    ~BST() {
        clear(root);
    }
private:
    static Node* copy(const Node* root) {
        return !root ? nullptr : new Node{ root->data, copy(root->left), copy(root->right) };
    }

    static void clear(Node* root) {
        if (!root) { return; }
        clear(root->left);
        clear(root->right);
        delete root;
    }

    static void insert(Node*& root, const int elem) {
        if(!root) {
            root = new Node{ elem };
            return;
        }

        if(root->data > elem) {
            insert(root->left, elem);
            return;
        }

        insert(root->right, elem);
    }

    static bool find(Node* root, const int elem) {
        if(!root) {
            return false;
        }

        if(root->data == elem) {
            return true;
        }
        
        if(root->data > elem) {
            return find(root->left, elem);
        }

        return find(root->right, elem);
    }

    static bool remove(Node*& root, const int key) {
        if(!root) {
            return false;
        }

        if(root->data == key && !root->left) {
            Node* temp = root->right;
            delete root;
            root = temp;
            return true;
        }
        if(root->data == key && !root->right) {
            Node* temp = root->left;
            delete root;
            root = temp;
            return true;
        }

        if(root->data == key) {
            Node* new_root = extractMin(root);
            new_root->left = root->left;
            new_root->right = root->right;
            
            delete root;
            root = new_root;

            return true;
        }

        return root->data > key ? remove(root->left, key) : 
                                  remove(root->right, key);
    }

    static Node* extractMin(Node*& root) {
        // have the assumption that you have a root
        if(root->left) {
            return extractMin(root->left);
        }

        Node* res = root;
        root = root->right;
        return res;
    }

    static void print_inorder(Node* root) {
        if(!root) return;

        print_inorder(root->left);
        
        std::cout << root->data << " ";

        print_inorder(root->right);
    }

    static bool balanced(const Node* root) {
        if(!root) {
            return true;
        }

        return std::abs(height(root->left) - height(root->right) < 2) && 
               balanced(root->left) && balanced(root->right);

    }

    static bool perfectly_balanced(const Node* root) {
        if(!root) {
            return true;
        }

        return std::abs(weight(root->left) - weight(root->right) < 2) && 
               perfectly_balanced(root->left) && perfectly_balanced(root->right);

    }

    static std::size_t height(const Node* root) {
        if(!root) {
            return 0;
        }
        return 1 + std::max(height(root->left), height(root->right));
    }

    static std::size_t weight(const Node* root) {
        if(!root) {
            return 0;
        }

        return 1 + weight(root->left) + weight(root->right);
    }

    Node* root = nullptr;
    std::size_t size = 0;



};

int main() {
    {
        BST tree;

        // Insert nodes to form the BST
        tree.insert(5);
        tree.insert(3);
        tree.insert(8);
        tree.insert(1);
        tree.insert(4);

        std::cout << "Original Tree: ";
        tree.print();  // Expected output: 1 3 4 5 8
        std::cout << std::endl;

        // Remove node with value 3
        tree.remove(3);
        std::cout << "Tree after removing 3: ";
        tree.print();  // Expected output: 1 4 5 8
        std::cout << std::endl;

        // Test removing a leaf node
        tree.remove(1);
        std::cout << "Tree after removing 1: ";
        tree.print();  // Expected output: 4 5 8
        std::cout << std::endl;

        // Test removing a node with one child
        tree.remove(8);
        std::cout << "Tree after removing 8: ";
        tree.print();  // Expected output: 4 5
        std::cout << std::endl;

        // Test removing the root node
        tree.remove(5);
        std::cout << "Tree after removing 5: ";
        tree.print();  // Expected output: 4
        std::cout << std::endl;

        // Test removing a non-existent value
        bool result = tree.remove(10);
        std::cout << "Attempt to remove 10 (non-existent): " << (result ? "Removed" : "Not Found") << std::endl;

        // Test removing the last node
        tree.remove(4);
        std::cout << "Tree after removing 4: ";
        tree.print();  // Expected output: (empty tree)
        std::cout << std::endl;
    }    

    {
        BST balancedTree;

        // Insert nodes to form a balanced tree
        balancedTree.insert(5);
        balancedTree.insert(3);
        balancedTree.insert(8);
        balancedTree.insert(2);
        balancedTree.insert(4);
        balancedTree.insert(7);
        balancedTree.insert(9);

        std::cout << "Balanced Tree: ";
        balancedTree.print();  // Expected output: 2 3 4 5 7 8 9
        std::cout << std::endl;

        std::cout << "Height of balanced tree: " << balancedTree.height() << std::endl;
        std::cout << "Weight of balanced tree: " << balancedTree.weight() << std::endl;
        std::cout << "Is the tree balanced? " << (balancedTree.balanced() ? "Yes" : "No") << std::endl;
        std::cout << "Is the tree perfectly balanced? " << (balancedTree.perfectly_balanced() ? "Yes" : "No") << std::endl;

    }

    return 0;
}