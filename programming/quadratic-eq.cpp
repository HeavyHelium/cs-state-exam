#include <iostream>
#include <cmath>
int main() {
    int a, b, c;
    
    a = 1;
    b = -5;
    c = 6;
    
    if(a == 0 && b == 0 && c == 0) {
        std::cout << "Every real number is a solution\n";
        
    } else if(a == 0 && b == 0 && c != 0) {
        std::cout << "No real number is a solution\n";
    } else if(a == 0 && b != 0) {
        std::cout << "Single solution: " << (-c / (double)b) << "\n";
    } else {
        int discriminant = b * b - 4* a * c;
        double temp = std::sqrt((double)discriminant);
        
        if(discriminant < 0) {
            std::cout << "No real solutions" << std::endl;
        } else if(discriminant == 0) {
            std::cout << "Root of multiplicity two: " << (-b / (2.0 * a));
        } else {
            std::cout << "Two unique real roots:\n";
            std::cout << (-b + temp) / (2 * a) << '\n';
            std::cout << "and\n";
            std::cout << (-b - temp) / (2 * a) << '\n';
        }    
    }
    return 0;
}