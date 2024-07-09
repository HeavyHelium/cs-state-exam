#include <iostream>


struct Occurence {
    int first = -1;
    int last = -1;

    int dist() const {
        return last - first;
    }
};


int strlen(const char* str) {
    int len = 0;
    while(*str) {
        len += 1;
        ++str;
    }
    return len;
}

Occurence get_occ(const char* str) {
    int length = strlen(str);
    
    Occurence max_occ;

    for(int i = 0; i < length - 1; ++i) {
        for(int j = length - 1; j > i; --j) {
            if(str[i] == str[j] && max_occ.dist() < j - i) {
                max_occ.first = i;
                max_occ.last = j;
            }
        }
    }

    return max_occ;
}


int main() {

    const char* str = "this i sjust a simple example";
    
    Occurence o = get_occ(str);
    std::cout << o.first << " and " << o.last << std::endl;


    return 0;
}