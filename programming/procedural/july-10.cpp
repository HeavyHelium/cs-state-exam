#include <iostream>
#include <vector>


void sort(std::vector<char>& v1) {
    for(int i = 0; i < v1.size(); ++i) {
        int best_id = i;
        for(int j = i + 1; j < v1.size(); ++j) {
            if(v1[best_id] > v1[j]) {
                best_id = j;
            }
        }
        std::swap(v1[i], v1[best_id]);
    }
}


bool anagrams(const char* str1, const char* str2) {
    std::vector<char> v1;
    std::vector<char> v2;

    while(*str1) { v1.push_back(*str1++); }
    while(*str2) { v2.push_back(*str2++); }

    if(v1.size() != v2.size()) return false;

    sort(v1);
    sort(v2);

    for(int i = 0; i < v1.size(); ++i) {
        if(v1[i] != v2[i]) return false;
    }

    return true;
}


void find_connected_components(const char* strings[], int cnt) {
    std::vector<int> ids(cnt, -1);

    int id = 0;

    for(int i = 0; i < cnt; ++i) {
        if(ids[i] == -1) {
            ids[i] = id;
            for(int j = i + 1; j < cnt; ++j) {
                if(anagrams(strings[i], strings[j])) {
                    ids[j] = id;
                }
            }
            ++id;
        }
    }
    std::vector<int> cnts(id, 0);
    for(int i = 0; i < cnt; ++i) {
        ++cnts[ids[i]];
    }
    int max_id = 0;
    for(int j = 1; j < cnts.size(); ++j) {
        if(cnts[j] > cnts[max_id]) {
            max_id = j;
        }
    }
    std::cout << "Max cnt: " << cnts[max_id] << " \nStrings: "; 
    for(int i = 0; i < cnt; ++i) {
        if(ids[i] == max_id) {
            std::cout << strings[i] << " ";
        }
    }
}



int main() {

    const char* strs[] = { "string", "ginrts", "ringst", 
                          "strong", "spong", "shpong", "pongs", };
    int cnt = 7;

    find_connected_components(strs, cnt);

    std::cout << (1 << 5);

    for (int k = 1; k < 5; k <<= 5) {
        std::cout << k << " ";
    }
}
/*
n ^2 > 1

// n + n ^ 2 > 1 + n == n(1 + n) > 1 + n 
// 
// n + n^2  > 2 + n

// Theta(n^2)
*/