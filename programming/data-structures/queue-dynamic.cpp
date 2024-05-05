#include <iostream>
#include <vector>
#include <cstddef>


class DynamicQueue {
    std::vector<int> container;
    std::size_t head = 0;
    std::size_t tail = 0; // points to past the last elem

public:
    DynamicQueue(const std::size_t size = 4)
        : container(size + 1) {
    }

    bool empty() const {
        return head == tail;
    }

    bool full() const {
        return (tail + 1) % size() == head;
    }

    void enqueue(int elem) { 
        if(full()) {
            std::cout << elem;
            resize();
        }
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
    void resize() {
        // std::cout << "resize\n";
        std::vector<int> new_container(2 * size());
        std::size_t iter = 0;

        for(std::size_t i = head; i < tail; i = (i + 1) % size()) {
            new_container[iter++] = container[i];
        }
        container = new_container;
        head = 0;
        tail = iter;
    }

    std::size_t size() const {
        return container.size();
    }

};



int main() {
    DynamicQueue queue(4);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);
    queue.enqueue(60);
    queue.enqueue(70);
    queue.enqueue(80);
    queue.enqueue(90);
    queue.enqueue(100); 

    while(!queue.empty()) {
        std::cout << "Front element: " << queue.front() << std::endl;
        queue.dequeue();
    }


    std::cout << "Front element after dequeue: " << queue.front() << std::endl;

    return 0;
}