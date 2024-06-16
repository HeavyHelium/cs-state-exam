#include <iostream>
#include <iomanip>

int power(int base, unsigned int power) {
    int result = 1;
    // a^(2 * n) = (a ^ 2) ^ n
    while(power > 0) {
        if(power % 2 == 1) {
            result = result * base;
        }
        power /= 2;
        base *= base;
    }
    return result;
}



int main() {
    std::cout << power(2, 3) << std::endl;

    int var = 0; 
    while(var++ < 5)
        std::cout << var; // 12345
    
    var = 0;
    std::cout << "\n----\n";
    do {
        std::cout << var;
    } while(++var < 5); // 01234

    std::cout << "\n------\n";
    unsigned int x = 0x11335577;
    // fresh from the shitter
    unsigned char* ptr = (unsigned char*)&x;
    ++*ptr;
    ++*(ptr + 1);
    ++ptr[2];
    ++3[ptr];
    std::cout << std::hex << "0x" << x; // 0x12345678

    const std::size_t size = 3;
    char box[size][size] = {
        'a', 'b', 'c',
        'd', 'e', 'f', 
        'g', 'h', 'i',
    };

    std::cout << "\n-----\n";

    for(int i = 0; i < size; i++) {
        std::cout << box[i][i];
    }
    std::cout << std::endl;

    for(int i = 0; i < size; i++) {
        std::cout << box[i][size - i - 1];
    }

    std::cout << std::endl;

    for(int i = 0; i < size; i++) {
        std::cout << box[size - 1 - i][i];
    }

    std::cout << std::endl;

    for(int i = 0; i < size; ++i)
        std::cout << box[0][i];
    //std::cout << std::endl;

    for(int i = size - 2; i < size; i++) 
        std::cout << box[i][size - 1];
    //std::cout << std::endl;
    
    for(int i = size - 2; i >= 0; --i) 
        std::cout << box[size - 1][i];
    //std::cout << std::endl;

    for(int i = size - 2; i > 0; --i) 
        std::cout << box[i][0];
    std::cout << std::endl;

}