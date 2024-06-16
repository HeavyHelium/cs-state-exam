#include <iostream>
#include <vector>
#include <string>


template<typename T>
std::ostream& operator<<(std::ostream& os, 
                         const std::vector<T>& v) {
    for(int i = 0; i < v.size(); ++i) {
        os << v[i] << "\n";
    }
    os << std::endl;
    return os;
}

bool prefix(const char* str, 
            const char* pref) {
    while(*pref) {
        if(!*str) {
            return false;
        }
        if(*pref++ != *str++) {
            return false;
        }
    }
    return true;

}

bool contains(const char* str, const char* sub) {
    while(*str) {
        if(prefix(str, sub)) {
            return true;
        } else {
            ++str;
        }
    }
    return false;
}

std::vector<std::string> split_by_line(const std::string& str) {
    const char* s = str.c_str();

    std::vector<std::string> lines; 
    while(*s != '\0') {
        std::string line("");
        while(*s != '\0' && *s != '\n') {
            line.push_back(*s);
            ++s;
        }
        if(*s == '\n') {
            ++s;
        }
        lines.push_back(line);
    }
    return lines;
}



struct SearchResult
{
    std::string fileName;
    unsigned line_number;
    std::string line;

    friend std::ostream& operator<<(std::ostream& os, 
                                    const SearchResult& v) {
        return os << "("<< v.fileName <<", "<< v.line_number << ", " << v.line << ")";
    }
};
class File // abstract base class for document  
{ 
public:
    virtual std::vector<SearchResult> search(const std::string&) const=0;
    virtual ~File(){}
};

class Document: public File { 
    std::string name;
    std::string contents;
public:
    Document( const std::string& _name, const std::string& _contents)
        : name(_name), contents(_contents) {    
    }

    std::vector<SearchResult> search(const std::string& str) const {
        std::vector<SearchResult> result; 
        
        std::vector<std::string> lines = split_by_line(contents);
        for(unsigned int i = 0; i < lines.size(); ++i) {
            if(contains(lines[i].c_str(), str.c_str())) {
                result.push_back(SearchResult{name, i + 1, lines[i]});
            }
        }


        return result;
    }
    
};




class Folder: public File {
    std::vector<File*> files;
    std::string name;
public: 
    Folder(const std::string& _name): name(_name){}

    void addFile(File* f) {
        files.push_back(f);
    } 

    std::vector<SearchResult> search(const std::string& str) const {
        std::vector<SearchResult> result;
        for(const File* f: files) {
            std::vector<SearchResult> temp = f->search(str);
            result.insert(result.end(), temp.begin(), temp.end());
        }
        return result;
    }

};


// class Folder: public File {
// files;
// std::string name;
// public:
// Folder( _name):
// void addFile( f)
// {files.push_back(f);}
// std::vector<SearchResult> search( str) const
// {
// std::vector<SearchResult> result;


int main() {
    // std::string str = "\n\nHello World\n\n\nFun, living in the real world...\n";
    // std::vector<std::string> res = split_by_line(str); 
    // std::cout << res;   
    // std::cout << res.size() << std::endl;

    // std::cout << prefix("Hello World!", "Hello") << std::endl;
    // std::cout << contains("Hello World!", "llo");

    // Document d1("employees.txt","John Smith\nMaryia Ivanova\n Johnathan Smith SHerlock\n");
    // std::vector<SearchResult> res = d1.search("Smith");
    // std::cout << res;



    Document d1("employees.txt","John Smith\nMaryia Ivanova\n"),
    d2("inventory.txt","Computers: 3\nPrinters: 1"),
    d3("employees.txt","Ivan Petrov\nJane Smith"),
    d4("inventory.txt","Computers: 5, 3D Printers: 1");
    Folder root("root"), acme("ACME Soft, Inc."), best("Best Soft, OOD");
    acme.addFile(&d1); acme.addFile(&d2);
    best.addFile(&d3); best.addFile(&d4);
    root.addFile(&acme); root.addFile(&best);
    std::vector<SearchResult> results = root.search("Smith");
    for(unsigned i = 0; i < results.size(); ++i) {
        std::cout << results[i].fileName
        << ", line " << results[i].line_number << ": "
        << results[i].line << std::endl;
    }
}