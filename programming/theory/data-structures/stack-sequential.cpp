#include <iostream>
#include <vector>



class Stack {

public:
    Stack() = default;

    bool empty() const {
        return container.empty();
    }

    const int& top() const {
        return container.back();
    }   

    int& top() {
        return container.back();
    }

    void push(int elem) {
        container.push_back(elem);
    }

    void pop() {
        container.pop_back();
    }

private: 
    std::vector<int> container;

};


int main() {
    Stack stack;

    // Push elements to the stack
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // Print and pop elements from the stack
    while (!stack.empty()) {
        std::cout << "Top element: " << stack.top() << std::endl;
        stack.pop();
    }

    return 0;
}
