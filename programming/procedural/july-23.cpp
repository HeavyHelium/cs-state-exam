#include <iostream>


bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || 
           c == '\r' || c == '\n';
}

char* removeWhitespace(char* str) {
    std::size_t read = 0; 
    std::size_t write = 0;

    while(str[read]) {
        if(isWhitespace(str[read])) {
            read += 1;
        } else {
            str[write++] = str[read++];
        }
    }

    str[write] = '\n';

    return str;
}



void pass(int* arr, 
          std::size_t size, 
          bool& swappedAtLeastOnce) {

    if(size <= 1) {
        return;
    }

    if(arr[0] > arr[1]) {
        std::swap(arr[0], arr[1]);
        swappedAtLeastOnce = true;
    }

    pass(arr + 1, size - 1, swappedAtLeastOnce);

}


void bubbleSort(int* arr, std::size_t size) {
    bool swappedAtLeastOnce = false;
    pass(arr,size, swappedAtLeastOnce);
    if(swappedAtLeastOnce) {
        bubbleSort(arr, size);
    }
}




int main() {
    for(int i = 0; i < 10; ++i) {
        if(i % 2) continue;
        std::cout << i; 
    } // 0 2 4 6 8
    std::cout << std::endl;
    int i = 0x10; // 16
    std::cout << i << std::endl;

    int a = 1, b = 2, c = 3;

    std::cout << (a ? b : c) << std::endl;
    // 2

    char str[] = "abc";
    char* p = str;
    ++p;
    ++*p;
    std::cout << str; // acc



    std::cout << "\n--------\n";

    int x = 2;
    int arr[] = {10, 20, 30};
    std::cout << "\nA: " << 5./x; // 2.5
    std::cout << "\nB: " << (x << 4); // 32 
    std::cout << "\nC: " << arr[!x]; // 10
    std::cout << "\nD: " << *(arr + x); // 30
    std::cout << "\nE: " << (2 + x++) << std::endl; // 4
}