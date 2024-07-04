#include <iostream>
#include <iomanip>

bool valid(int i, int j) {
    return !(i < 0 || j < 0 || i > 5 || j > 5);
}

bool walk(char mat[6][6], const char* str, int i, int j) {
    if(!valid(i, j)) return false;

    if(mat[i][j] < 0 || *str != mat[i][j]) {
        return false;
    }
    if(!*(++str)) return true; 
    mat[i][j] *= -1;

    if(walk(mat, str, i + 1, j) || walk(mat, str, i - 1, j) || 
           walk(mat, str, i, j + 1) || walk(mat, str, i, j - 1)) {
        return true;
    }
    mat[i][j] *= -1;
    return false;
}

bool contains(char mat[6][6], const char* str) {
    if(!*str) return true;

    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 6; ++j) {
            if(walk(mat, str, i, j)) {
                return true;
            }
        }
    }
    return false;
}


int main() {
    char matrix[6][6] = {
        {'y', 'u', 'f', 'a', 'b', 'c'},
        {'G', 'o', 'p', 'g', 'B', '1'},
        {'c', 'b', 'a', 'h', '3', '2'},
        {'d', 'k', 'j', 'i', '2', '3'},
        {'e', 'f', 'Q', 'N', '1', 'C'},
        {'h', 'g', 'h', 'M', 'A', 'r'}
    };

    const char* str1 = "abcdefgh";
    const char* str2 = "A123B123C";

    std::cout << std::boolalpha << contains(matrix, str1) << std::endl;
    std::cout << std::boolalpha << contains(matrix, str2) << std::endl; 

    return 0;
}