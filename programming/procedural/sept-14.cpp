#include <iostream>
#include <cfloat>

/*
Дадени са координатите на N-точки, които са записани в масивите float x[N], y[N] по следния
начин: координатите на i-тата точка са (x[i], y[i]).
Напишете функция square, която получава като аргументи броя на точките N и два масива X и Y
съдържащи координатите им и извежда на екрана координатите на центъра и страната на най-
малкия квадрат със страни успоредни на координатните оси, който обхваща всички дадени точки
(всички дадени точки са във вътрешността му или на страните му).
Ако решавате задачата на Java, достатъчно е да напишете статична функция, която решава
задачата.



 */

void square(float* X, float* Y, int N) {
    float x_min = FLT_MAX;
    float y_min = FLT_MAX;
    float x_max = -FLT_MAX, y_max = -FLT_MAX;
    
    for(int i = 0; i < N; ++i) {
        if(X[i] < x_min) x_min = X[i];
        if(X[i] > x_max) x_max = X[i];

        if(Y[i] < y_min) y_min = Y[i];
        if(Y[i] > y_max) y_max = Y[i];
    }

    float dx = x_max - x_min;
    float dy = y_max - y_min;
    float side = 0;
    if(dx > dy) {
        side = dx;
    } else {
        side = dy;
    }

    std::cout << "(" << x_min + side / 2 << ", " << y_min + side / 2 << ")\n";
    std::cout << "side length: " << side << "\n"; 
}

int main() {
float X1[] = {1.0, 2.0, 3.0, 4.0};
    float Y1[] = {1.0, 2.0, 3.0, 4.0};
    std::cout << "Test case 1:\n";
    square(X1, Y1, 4);
    std::cout << "\n";

    // Test case 2: Points form a rectangle
    float X2[] = {0.0, 2.0, 2.0, 0.0};
    float Y2[] = {0.0, 0.0, 1.0, 1.0};
    std::cout << "Test case 2:\n";
    square(X2, Y2, 4);
    std::cout << "\n";

    // Test case 3: Single point
    float X3[] = {5.0};
    float Y3[] = {5.0};
    std::cout << "Test case 3:\n";
    square(X3, Y3, 1);
    std::cout << "\n";

    // Test case 4: Points on a line
    float X4[] = {0.0, 1.0, 2.0, 3.0};
    float Y4[] = {0.0, 0.0, 0.0, 0.0};
    std::cout << "Test case 4:\n";
    square(X4, Y4, 4);
    std::cout << "\n";

    // Test case 5: Random points
    float X5[] = {-1.0, -3.0, 4.0, 2.0};
    float Y5[] = {2.0, -2.0, 3.0, -3.0};
    std::cout << "Test case 5:\n";
    square(X5, Y5, 4);
    std::cout << "\n";

    return 0;
}