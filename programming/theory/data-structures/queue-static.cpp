#include <iostream>
#include <vector>
#include <cstddef>


class StaticQueue {
    std::vector<int> container;
    std::size_t head = 0;
    std::size_t tail = 0; // points to past the last elem

public:
    StaticQueue(const std::size_t size = 8)
        : container(size + 1) {
    }

    bool empty() const {
        return head == tail;
    }

    bool full() const {
        return (tail + 1) % size() == head;
    }

    void enqueue(int elem) { 
        container[tail] = elem;
        tail = (tail + 1) % size();
    }

    void dequeue() {
        head = (head + 1) % size();
    }

    const int& front() const {
        return container[head];
    }

    int& front() {
        return container[head];
    }


private: 
    std::size_t size() const {
        return container.size();
    }

};



int main() {
    StaticQueue queue(3);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40); // This should print an error message

    std::cout << "Front element: " << queue.front() << std::endl;

    queue.dequeue();
    std::cout << "Front element after dequeue: " << queue.front() << std::endl;

    queue.enqueue(40);
    std::cout << "Front element after enqueue: " << queue.front() << std::endl;

    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();

    std::cout << queue.empty() << std::endl; 


    return 0;
}