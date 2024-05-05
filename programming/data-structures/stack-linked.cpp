#include <iostream>


class Stack {

    struct Node {
        int data;
        Node* next = nullptr;      
    };

public:
    Stack() = default;
    Stack(const Stack& other)
        : top(copy(other.top)) {}
    
    Stack& operator=(const Stack& other) {
        if(this != &other) {
            clear();
            top = copy(other.top);
        }
        return *this;
    }

    bool empty() const {
        return !top;
    }

    const int& peek() const {
        return top->data;
    }

    void push(int elem) {
        top = new Node{ elem, top };
    }

    void pop() {
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    void clear() {
        while(top) {
            pop();
        }
    }

    ~Stack() {
        clear();
    }

private:
    static Node* copy(const Node* chain) {
        Node dummy = Node{}; 
        Node* curr = &dummy;
        while(chain) {
            curr->next = new Node{ chain->data, nullptr };
            curr = curr->next;
            chain = chain->next;
        }
        return dummy.next;
    }

    Node* top = nullptr;
};



int main() {
    Stack s1;
    s1.push(10);
    s1.push(20);
    s1.push(30);

    Stack s2 = s1; // Copy constructor
    s2.push(40);

    Stack s3;
    s3 = s2; // Assignment operator

    // Demonstrate stack operations
    std::cout << "Stack s3 elements (top to bottom): ";
    while (!s3.empty()) {
        std::cout << s3.peek() << " ";
        s3.pop();
    }
    std::cout << std::endl;


    return 0;
}