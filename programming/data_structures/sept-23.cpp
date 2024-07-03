#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <list>
#include <stdexcept>
#include <queue>


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
                                  const char* word="/") {
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


struct Node {
    std::string name;
    std::list<Node*> children;
};


void clear_tree(Node* root) {
    if(!root) {
        return;
    }
    for(Node* child: root->children) {
        clear_tree(child);
    }
    delete root;
}

bool insert(Node* root, const std::vector<std::string>&  path, int cid=0) { // there always is a root dir, root is never nullptr
    if(cid  == path.size()) {
        return true; // nothing to insert
    }

    for(Node* child: root->children) {
        if(child->name == path[cid]) {
            return insert(child, path, cid + 1);
        }
    }

    root->children.push_back(new Node{ path[cid] }); 
    return insert(root->children.back(), path, cid + 1);
}

Node* get_elem(Node* root, const std::vector<std::string>& path, int cid=0) {
    if(cid == path.size()) {
        return root;
    }

    for(Node* child: root->children) {
        if(child -> name  == path[cid]) {
            return get_elem(child, path, cid + 1);
        }
    }

    return nullptr;
}

bool contains(const std::list<Node*> nodes, const std::string& str) {
    for(Node* n : nodes) {
        if(n -> name == str) {
            return true;
        }
    }
    return false;
}

void flatten(Node* root) {
    for(Node* child : root->children) {
        flatten(child);
    }
    // now children, if not leaves, have children, which are leaves 
    std::list<Node*> new_children;

    for(Node* child : root->children) {
        for(Node* grandchild : child->children) {
            if(!contains(new_children, grandchild->name)) {
                new_children.push_back(grandchild);
            } else {
                delete grandchild;
            }
        }
        if(!contains(new_children, child->name)) {
            new_children.push_back(new Node{ child->name });
        } 
        delete child;
    }
    root->children = new_children;

}


void insert(Node* root, const std::string& path) {
    insert(root, split_by(path.c_str()));
}


void flatten(Node* root, const std::string& path) {
    std::vector<std::string> path_v = split_by(path.c_str());
    Node* elem = get_elem(root, path_v);

    if(!elem) {
        std::cout << "your path is wrong!" << std::endl;
        return; 
    }
    flatten(elem);
}


void print(const Node* root) {
    std::queue<const Node*> q;
    q.push(root);
    int curr = 1;
    int next = 0;

    while(!q.empty()) {
        const Node* n = q.front();
        q.pop();
        --curr;
        if(n->name == "") {
            std::cout << "root ";
        } else {
            std::cout << n->name << " ";
        }

        for(const Node* child : n->children) {
            q.push(child);
            next += 1;
        }

        if(curr == 0) {
            curr = next; 
            next = 0;
            std::cout << std::endl;
        }
    }
}





int main() {
    std::string s("/home/user/src");
    std::string s1("/bin");
    std::string s2("/lib");
    std::string s3("/usr/bin");
    std::string s4("/home/di");
    std::string s5("/home/user/src/di");

    Node* root = new Node{ "" }; // the tree is represented by its root


    insert(root, s1);
    insert(root, s2);
    insert(root, s3);
    insert(root, s4);
    insert(root, s5);
    print(root);

    flatten(root, "/home");
    print(root);

    // flatten(root, "/");
    // print(root);

    clear_tree(root);
}