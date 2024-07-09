#include <iostream>
#include <vector>
#include <climits>
#include <string>


struct Node {
    int elem = 42;
    std::vector<Node*> children;

};


void free_tree(Node* root) {
    if(!root) {
        return;
    }
    for(Node* child: root->children) {
        free_tree(child);
    }
    delete root;
}

bool whitespace(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

void skip_whitespace(const char*& str) {
    while(*str && whitespace(*str)) {
        ++str;
    }
}

bool digit(char ch) {
    return ch >= '0' && ch <= '9';
}

std::string read_number(const char*& str) {
    std::string number;
    while(*str && digit(*str)) {
        number.push_back(*str++);
    }

    return number;
}

bool is_number(const char* number) {
    while(*number && digit(*number)) {
        ++number;
    }

    return !*(number);
}

int to_number(const char* number) {
    int sum = 0;
    while(*number) {
        sum *= 10;
        sum += (*number - '0');
        ++number;
    }
    return sum;

}

void read_token(const char* str, std::vector<std::string>& res) {
    skip_whitespace(str);
    if(!*str) return;

    if(*str == '(') {
        res.push_back("(");
        read_token(str + 1, res);
        return;
    } 
    
    if(*str == ')') {
        res.push_back(")");
        read_token(str + 1, res);
        return;
    }

    if(*str == ',') {
        res.push_back(",");
        read_token(str + 1, res);
        return;
    }

    if(digit(*str)) {
        res.push_back(read_number(str));
        read_token(str, res);
        return;
    }

    throw std::runtime_error("wrong format");
}


Node* build_dfs(const std::vector<std::string>& tokens, int& cid) {
    
    if(cid >= tokens.size())        
        throw std::runtime_error("Wrong format!");
    if(tokens[cid] != "(") {
        throw std::runtime_error("Wrong format!");
    }
    ++cid;
    if(cid == tokens.size()) {
        throw std::runtime_error("Wrong format!");
    }
    if(tokens[cid] == ")") {
        ++cid;
        return nullptr;
    }

    if(!is_number(tokens[cid].c_str())) {
        throw std::runtime_error("Wrong format, not a number!");
    }

    int number = to_number(tokens[cid].c_str());
    ++cid;

    if(cid >= tokens.size())
        throw std::runtime_error("Wrong format!");
    
    if(tokens[cid] != "(") {
        throw std::runtime_error("Wrong format!");
    }
    ++cid;

    if(cid >= tokens.size()) throw std::runtime_error("Wrong format!");
    
    
    Node* root = new Node{number};
    

    while(cid < tokens.size() && tokens[cid] != ")"){
        Node* child = nullptr;
        try { 
            child = build_dfs(tokens, cid);
            root->children.push_back(child);
        } catch(const std::exception& e) {
            free_tree(root);
            throw std::runtime_error("Wrong format!");
        }
        if(cid >= tokens.size()) {
            free_tree(root);
            throw std::runtime_error("Wrong format!");
        }
        if(tokens[cid] != ",") { break; };
        ++cid;
    } 
    if(cid == tokens.size()) throw std::runtime_error("Wrong format!");

    if(tokens[cid] != ")") {
        free_tree(root);
        throw std::runtime_error("Wrong format!");
    }
    ++cid;
    if(cid == tokens.size()) throw std::runtime_error("Wrong format! ff");
    ++cid;
    return root;

}

int best_cost(Node* root) {
    if(!root) return 0;

    int max = root->children.empty() ? 0 : INT_MIN;

    for(Node* child: root->children) {
        int temp = best_cost(child);
        if(temp > max) {
            max = temp;
        }
    }

    return max + root->elem;
}


void print_tree(const Node* root) {
    if (root == nullptr) return;
    std::cout << "( " << root->elem << " ( ";
    for (const auto& child : root->children) {
        print_tree(child);
    }
    std::cout << " ) ) ";
}


int main() {

    std::string line = "(5 ((9 ()), (1 ( (4 ()), (12 ()), (42 ())))))";

    std::vector<std::string> tokens;
    read_token(line.c_str(), tokens);

    for(auto token: tokens) {
        std::cout << token << ' ';
    } std::cout << std::endl;


    int cid = 0;
    Node* root = build_dfs(tokens, cid);
    print_tree(root);
    std::cout << "\nopt cost: " << best_cost(root) << std::endl;
    free_tree(root);

    return 0;
}