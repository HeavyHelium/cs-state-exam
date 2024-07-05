#include <iostream>
#include <string>


std::string int_to_str(unsigned int a) {
    std::string res; 
    res.push_back('0' + a % 10);
    if(a < 10) {
        return res;
    } 
    return int_to_str(a / 10) + res;
}


int lex_ord(unsigned int a, unsigned int b) {
    std::string stra = int_to_str(a);
    std::string strb = int_to_str(b);

    const char* itera = stra.c_str();
    const char* iterb = strb.c_str();


    while(*itera && *itera == *iterb) {
        ++itera;
        ++iterb;
    }

    return *itera - *iterb;
}


void sortLex(unsigned int* arr, int length) {
    for(int i = 0; i < length; ++i) {
        int best_id = i;
        for(int j = i + 1; j < length; ++j) {
            if(lex_ord(arr[best_id], arr[j]) > 0) {
                best_id = j;
            }
        }
        int temp = arr[best_id];
        arr[best_id] = arr[i];
        arr[i] = temp;
    }

}



int main() {

    std::cout << int_to_str(400) << std::endl;

    std::cout << lex_ord(123, 9) << std::endl;

    unsigned int arr[] = {13, 14, 7, 2018, 9, 0};
    
    int size = sizeof(arr) / sizeof(unsigned int);

    std::cout << "before: \n";
    for(int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    } std::cout << "\nafter:\n";

    sortLex(arr, size);

    for(int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    } std::cout << std::endl;

    return 0;
}