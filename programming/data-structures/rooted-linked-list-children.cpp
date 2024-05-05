#include <iostream>
#include <list>
#include <cstddef>

class Tree {

    int data;
    std::list<Tree> children;

public:
    Tree() = default;
    Tree(const int leaf) {
        data = leaf;
    }
    void add_subtree(const Tree& t) {
        children.push_back(t);
    }
    int root() const { return data; }
    std::list<Tree> subtrees() const { return children; }

    void print() const {
        std::cout << "(" << root();
        for(const Tree& subtree : subtrees()) {
            std::cout << " ";
            subtree.print();
        }
        std::cout << ")";
    }

    std::size_t depth() const {
        std::size_t max_depth = 0;
        for(const Tree& subtree : subtrees()) {
            max_depth = std::max(max_depth, subtree.depth());
        }
        return 1 + max_depth;
    }

    std::size_t breadth() const {
        std::size_t max_breath = children.size();
        for(const Tree& subtree : subtrees()) {
            std::size_t temp = subtree.breadth();
            if(temp > max_breath) {
                max_breath = temp;
            }
        }
        return max_breath;
    }

};



int main() {
    Tree root(1);
    Tree child1(2);
    Tree child2(3);

    Tree grandchild1(4);
    Tree grandchild2(5);

    child1.add_subtree(grandchild1);
    child1.add_subtree(grandchild2);

    root.add_subtree(child1);
    root.add_subtree(child2);

    std::cout << "Tree structure: ";
    root.print();
    std::cout << std::endl;

    std::cout << "Tree depth: " << root.depth() << std::endl;
    std::cout << "Tree breadth: " << root.breadth() << std::endl;

}