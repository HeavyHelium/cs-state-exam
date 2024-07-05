#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    for(auto elem: v) {
        os << elem << ", ";
    }
    return os << std::endl;
}

int strcmp(const char* str1, const char* str2) {
    while(*str1 && *str1 == *str2) {
        ++str1;
        ++str2;
    }
    return *str1 - *str2;
}

bool is_sorted(const char* strs[][30], int i, int n)  {

    for(int j = 0; j < n - 1; ++j) {
        if(strcmp(strs[i][j], strs[i][j + 1]) > 0) {
            return false;
        }
    }
    return true;
}

bool prefix(const char*& str, const char* word) {
    const char* temp = str;
    while(*word && *str == *word) {
        ++str;
        ++word;
    }

    if(*word) { str = temp; return false; };
    return true;
}

std::vector<std::string> split_str(const char* str, const char* word=" ") {
    std::vector<std::string> res;
    std::string curr;
    while(*str) {
        
        if(!prefix(str, word) && *str) {
            curr.push_back(*str);
            ++str;
        } else if(curr != "") {
            res.push_back(curr);
            curr = "";
        }
    }
    if(curr != "") res.push_back(curr);
    return res;
}

void revealPassword(const char* strs[][30], int m, int n) {
    for(int i = 0; i < m; ++i) {
        if(is_sorted(strs, i, n)) {
            int mid = n / 2;
            std::vector<std::string> spl = split_str(strs[i][mid]);
            for(const std::string& word: spl) {
                std::cout << word.length() << " ";
            }
        }
    }
}


int main() {

    const int m = 3;
    const int n = 3;

    const char* matr[m][n] = {"Алгебра", "Аналитична геометрия", "Математически анализ",
                                 "Увод в програмирането", "Обектно-ориентирано програмиране", "Структури от данни и програмиране", 
                                 "Бази от данни", "Изкуствен интелект", "Функционално програмиране"}; 

    const char* shelf[20][30];

    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            shelf[i][j] = matr[i][j];
        }
    }

    std::cout << is_sorted(shelf, 0, n) << std::endl;
    std::cout << is_sorted(shelf, 1, n) << std::endl;
    std::cout << is_sorted(shelf, 2, n) << std::endl;


    std::cout << split_str(shelf[2][1], " ");
    revealPassword(shelf, m, n);

    return 0;
}