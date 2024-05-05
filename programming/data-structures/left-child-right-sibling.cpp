#include <iostream>
#include <queue>
#include <cstddef>
#include <utility>


class Tree {

    struct Node { 
        int data;
        Node* child = nullptr;
        Node* sibling = nullptr;
    };

public: 
    Tree() = default;
    Tree(const Tree& other)
        : root(copy(other.root)), size(other.size) {
    }

    Tree& operator=(const Tree& other) {
        if(this != &other) {
            Node* cp = copy(other.root);
            size = other.size;
            root = cp;
        }   

        return *this;
    }

    bool find(const int elem) const {
        return find(root, elem);
    }

    std::size_t weight() const {
        return size;
    }

    std::size_t weight_comp() const {
        return weight(root);
    }

    std::size_t height() const {
        return height(root);
    }

    bool erase(const int elem) {
        if(remove(root, elem)) {
            --size;
            return true;
        }
        return false;
    }

    bool insert(const int elem, const int path[]) {
        if(insert(root, elem, path)) {
            ++size;
            return true;
        }
        return false;
    }

    void print() const {
        print_by_bfs(root);
    }



    ~Tree() {
        clear(root);

        size = 0;
    }

private: 

    void clear(Node* root) {
        if(root) {
            clear(root->child);
            clear(root->sibling);
            delete root;
        }
    }

    static Node* copy(Node* root) {
        return root ? new Node{ root->data, 
                                copy(root->child), 
                                copy(root->sibling) } : root;
    }

    static bool find(const Node* root, const int elem) {
        if(!root) return false;
        return root->data == elem ? true : find(root->sibling, elem) || find(root->child, elem);
    }


    static bool remove(Node*& root, const int key) {
        if(!root) {
            return false;
        }

        if(root->data != key) return remove(root->sibling, key) || remove(root->child, key);
        Node* to_delete = root;
        if(!root->child) {
            root = root->sibling;
        } else if(!root->sibling) {
            root = root->child;
        } else { // both children and siblings
            Node* iter = root->child;
            while(iter->sibling) {
               iter = iter->sibling; 
            }
            iter->sibling = root->sibling->child;
            root->sibling->child = root->child;
            root = root->sibling;
        }
        delete to_delete;
        return true;
    }


    static bool insert(Node*& root, const int key, const int* path) {
        //std::cout << *path << std::endl;
        if(path[0] < 0) {
            root = new Node{ key, nullptr, root };  
            return true;
        }

        if(!root) {
            return false;
        }

        if(path[0] == 0) {
            return insert(root->child, key, path + 1);
        }

        int pos = path[0];
        Node* iter = root;
        while(pos > 0 && iter->sibling) {
            --pos;

            iter = iter->sibling;
        }
        return iter -> sibling ? insert(iter->sibling->child, key, path + 1) : false;

    }


    static std::size_t height(const Node* root) {
        if(!root) {
            return 0;
        }

        return std::max(height(root->child) + 1, height(root->sibling));
    }

    static std::size_t weight(const Node* root) {
        if(!root) {
            return 0;
        }
        return 1 + weight(root->child) + weight(root->sibling);
    }

    static void print_by_bfs(const Node* root) {
        if(!root) {
            return;
        }

        std::queue<const Node*> front;
        front.push(root); // push all siblings?
        front.push(nullptr);

        while(true) {
            const Node* current = front.front();
            front.pop();

            if(!current) {
                std::cout << "\n";
                if(front.empty()) {
                    return;
                }
                front.push(nullptr);
            } else {
                std::cout << current->data << " ";
                for(const Node* iter = current->child; iter; iter = iter->sibling) {
                    front.push(iter);

                }
            }
        }
    }


    std::size_t size = 0;
    Node* root = nullptr;
};



int main() {
    Tree tree;

    int path[] = {-1};
    
    bool temp = tree.insert(1, path);
        
    int path2[] = {0, -1};
    tree.insert(2, path2);
    //tree.print();

    int path3[] = {0, 0, -1};
    tree.insert(3, path3);
    //tree.print();

    int path4[] = {0, 0, -1};
    tree.insert(4, path4);
    //tree.print();

    int path41[] = {0, 0, -1};
    tree.insert(5, path41);
    //tree.print();

    int path5[] = {0, 0, 1, -1};
    tree.insert(6, path5);
    tree.print();
    
    std::cout << "Tree Height: " << tree.height() << std::endl;
    std::cout << "Tree Weight: " << tree.weight() << std::endl;
    std::cout << "Tree Weight (computed): " << tree.weight_comp() << std::endl;
    return 0;


}