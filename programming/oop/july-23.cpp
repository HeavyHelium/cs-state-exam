#include <iostream>
#include <vector>



template<typename T>
class Function {

public: 
    virtual T value(R) const = 0;

};


class Inc: public Function<double> {

public: 
    double value(double x) const {
        return x + 1;
    }
};


class Square: public Function<double> {

public: 
    double value(double x) const {
        return x * x;
    }
};


template<typename T>
class Max: public Function<T> {

private: 
    std::vector<Function<T>*> functions;
public: 
    void addFunction(Function<T>* f) {
        functions.push_back(f);
    }

    T value(T x) const {
        if(!functions.size()) {
            throw "Function list is empty!";
        }

        T max = functions[0]->value(x);

        for(std::size_t i = 1; i < functions.size(); ++i) {
            T temp = functions[i]->value(x);
            if(temp > max) {
                max = temp; 
            }
        }
        return max;

    }

};

template<typename T>
class Sum: public Function<T> {

private: 
    std::vector<Function<T>*> functions;
public: 
    void addFunction(Function<T>* f) {
        functions.push_back(f);
    }
    T value(T x) const {
        if(!functions.size()) {
            throw "Function list is empty!";
        }

        T sum = 0;

        for(std::size_t i = 0; i < functions.size(); ++i) {
            sum += functions[i]->value(x);
        }
        return sum;
    }

};
