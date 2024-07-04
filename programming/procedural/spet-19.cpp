#include <iostream>
#include <cstddef>
#include <cstring>

bool find(int value, int* arr, std::size_t size) {
    if(size == 0) return false;

    std::size_t mid = size / 2;

    if(value == arr[mid]) return true;

    if(value < arr[mid]) {
        return find(value, arr, mid);
    }
    return find(value, arr + mid + 1, size - mid - 1);
}


template <typename ReturnType, typename InputType, typename OpType>
ReturnType fold_left(InputType* arr, std::size_t size, OpType op, ReturnType nil) {
    ReturnType result = nil;

    for(std::size_t i = 0; i < size; ++i) {
        result = op(result, arr[i]);
    }

    return result;
}


int op(char Digit, int Result) {
    return Result * 10 + (Digit - '0');
}

int str_to_int(const char* str) {
    return str == nullptr ? 0 : fold_left(str, std::strlen(str), op, 0);
}


int main() {



    return 0;
}