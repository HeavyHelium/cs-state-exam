#include <iostream>


class LinkedQueue {
    struct Node { 
        int data;
        Node* next = nullptr;
    };
public: 
    LinkedQueue() = default;

    LinkedQueue(const LinkedQueue& other) {
        copy(other);
    }

    LinkedQueue& operator=(const LinkedQueue& other) {
        if(this != &other) {
            copy(other);
        }
        return *this;
    }

    void enqueue(int elem) {
        if(empty()) {
            first = last = new Node{ elem, nullptr };
        } else {
            last->next = new Node { elem, nullptr };
            last = last->next;
        }
    }

    const int& front() const {
        return first->data;
    }

    int& front() {
        return first->data;
    }

    void dequeue() {
        Node* temp = first; 
        first = first->next;
        delete temp;
    }

    bool empty() const {
        return !first;
    }

    void clear() {
        while(!empty()) {
            dequeue();
        }
    }

    ~LinkedQueue() {
        clear();
    }
private:
    void copy(const LinkedQueue& other) {
        Node dummy;
        Node* curr = &dummy;
        const Node* iter = other.first;
       
        while(iter) {
            curr->next = new Node{ iter->data, nullptr };
            iter = iter->next;
            curr = curr->next;
        }

        clear();
        first = dummy.next;
        last = curr;
    }

    Node* first = nullptr;
    Node* last = nullptr;

};


int main() {
 // Test 1: Basic enqueue and dequeue
    LinkedQueue queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    std::cout << "Test 1: Basic enqueue and dequeue\n";
    std::cout << "Front element: " << queue.front() << "\n"; // Expected: 10
    queue.dequeue();
    std::cout << "Front element after one dequeue: " << queue.front() << "\n"; // Expected: 20
    queue.dequeue();
    std::cout << "Front element after two dequeues: " << queue.front() << "\n"; // Expected: 30
    queue.dequeue();


    // Test 3: Enqueue after clearing
    std::cout << "Test 3: Enqueue after clearing\n";
    queue.enqueue(40);
    queue.enqueue(50);
    std::cout << "Front element: " << queue.front() << "\n"; // Expected: 40

    // Test 4: Copy constructor
    std::cout << "Test 4: Copy constructor\n";
    LinkedQueue copiedQueue(queue);
    std::cout << "Front element of copied queue: " << copiedQueue.front() << "\n"; // Expected: 40
    copiedQueue.dequeue();
    std::cout << "Front element of copied queue after dequeue: " << copiedQueue.front() << "\n"; // Expected: 50

    // Test 5: Assignment operator
    std::cout << "Test 5: Assignment operator\n";
    LinkedQueue assignedQueue;
    assignedQueue = queue;
    std::cout << "Front element of assigned queue: " << assignedQueue.front() << "\n"; // Expected: 40
    assignedQueue.dequeue();
    std::cout << "Front element of assigned queue after dequeue: " << assignedQueue.front() << "\n"; // Expected: 50

    // Test 6: Multiple enqueues and dequeues
    std::cout << "Test 6: Multiple enqueues and dequeues\n";
    queue.enqueue(60);
    queue.enqueue(70);
    queue.enqueue(80);
    std::cout << "Dequeuing elements:\n";
    while (!queue.empty()) {
        std::cout << queue.front() << " "; // Expected: 40 50 60 70 80
        queue.dequeue();
    }
    std::cout << "\nQueue should be empty now.\n";
    
    return 0;
}