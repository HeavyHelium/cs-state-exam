#include <iostream>

bool member(int x, int* a, int size) {
    if(size == 0) return false;

    return a[size/2] == x || 
            (a[size / 2] < x && member(x, a + size / 2 + 1, size - size / 2 - 1)) || 
            (member(x, a, size / 2));
}




// 0 1 2 3 4 5

int main() {

    int nums[] = { 8, 7, 2, 6, 4, 0, 11, 5 };
    int N = sizeof(nums) / sizeof(int);

    for(int i  = 0; i < N; ++i) {
        int min = i;
        for(int j = i + 1; j < N; ++j) {
            if(nums[min] > nums[j]) {
                min = j;
            }
        }
        if(min != i) {
            int x = nums[i];
            nums[i] = nums[min];
            nums[min] = x;
        }
    }

    for(int i = 0; i < N; ++i) {
        std::cout << nums[i] << ' ';
    } std::cout << std::endl;


    int a = 0; int b = 15; int result = 1;
    if (b < 10 && b / a < 10) result = 0;
    else result = 1;

    std::cout << result << std::endl; // 1
    std::cout << (6 | 11) << std::endl;

    return 0;
}



// 6 | 11 
// 000...00110
// |
// 000...01011
// = 
// 000...01111 = 8 + 4 + 2 + 1 = 15