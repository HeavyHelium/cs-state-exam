#include <iostream>
#include <vector>
#include <string>

bool wletter(char ch) {
    return ch >= 'A' && ch <= 'Z' || 
           ch >= 'a' && ch <= 'z' ||
           ch >= '0' && ch <= '9' || 
           ch == '_'; 
}


bool is_word(const char* str) {
    while(*str) if(!(wletter(*str++))) return false;
    return true;
}

std::string read_word(const char*& str) {
    std::string word;
    while(*str && wletter(*str)) {
        word.push_back(*str);
        ++str;
    }
    return word;
}

std::string read_punc(const char*& str) {
    std::string word;
    while(*str && !wletter(*str)) {
        word.push_back(*str);
        ++str;
    }
    return word;
}


std::vector<std::string> split(const char* text) {
    std::vector<std::string> vec;
    while(*text) {
        if(wletter(*text)) {
            vec.push_back(read_word(text));
        } else {
            vec.push_back(read_punc(text));
        }
    }

    return vec;
}


void transform(const char* text) {
    std::vector<std::string> vec = split(text);

    std::vector<std::string> words;

    for(int i = 0; i < vec.size(); ++i) {
        if(is_word(vec[i].c_str())) {
            words.push_back(vec[i]);
        }
    }

    int cid = words.size() - 1;

    for(int i = 0; i < vec.size(); ++i) {
        if(is_word(vec[i].c_str())) {
            std::cout << words[cid--];
        } else {
            std::cout << vec[i];
        }
    }
}



int main() {
    const char* t1 = "text 1.";
    transform(t1);

    std::cout << "\n---------\n";
    
    const char* t2 = "text !";
    transform(t2);

    std::cout << "\n---------\n";
    
    const char* t3 = "1;;2;3;4;;5.";
    transform(t3);
    

    return 0;
}