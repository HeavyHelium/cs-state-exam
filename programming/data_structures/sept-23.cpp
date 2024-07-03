#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstring>

std::size_t my_len(const char* str) {
    std::size_t len = 0;
    while(*str++) {
        ++len;
    }
    return len;
}


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> vec) {
    for(std::size_t i = 0; i < vec.size(); ++i) {
        os << vec[i] << ", ";
    }
    return os << std::endl;
}


struct Node {
    std::map<std::string, Node*> children; 
};


using dir_map = std::map<std::string, Node*>;

struct Tree {
    Node root;
};


bool prefix(const char* word, const char* prefix) {
    while(*prefix) {
        if(!*word) {
            return false;
        }
        if(*word++ != *prefix++) {
            return false;
        }
    }
    return true;
}


std::vector<std::string> split_by(const char* str, 
                                  const char* word) {
    std::vector<std::string> words;
    const char* begin = str;
    std::size_t len = my_len(word);

    while(*str) {
        if(prefix(str, word)) {
            if(begin != str){ 
                words.push_back(std::string(begin, str));
            }
            str += len;
            begin = str;
        } else {
            ++str;
        }
    }
    if(begin != str) {
        words.push_back(std::string(begin, str));
    }
    return words;
}


void insert(Node& dm, 
            const std::vector<std::string>& dirs, 
            int index) {
    // find if dir[0] is in dm 
    // if so, 

}


int main() {
    std::string s("/home/user/src");

    std::cout << split_first(s.c_str(), "/");
}