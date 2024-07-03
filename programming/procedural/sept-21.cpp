#include <iostream>
#include <cmath>

float epsilon = 0.0001;

bool eq(float a, float b) {
    return std::abs(a - b) < epsilon;
}




struct Point {
    float x = 0;
    float y = 0;

    float dist(const Point& other) const {
        float d1 = (x - other.x) * (x - other.x);
        float d2 = (y - other.y) * (y - other.y);
        return std::sqrt(d1 + d2); 
    }

    bool operator==(const Point& other) const {
        return eq(x, other.x) && eq(y, other.y);
    }
};

struct Circle {
    Point center;
    float r;
};

enum RelativePosition {
    NO_COMMON_POINTS, 
    TOUCHING, 
    INTERSECTING, 
    SAME,
};

RelativePosition find_relative_position(const Circle& c1, const Circle& c2) {
    float dist = c1.center.dist(c2.center);

    if(c1.center == c2.center && c1.r == c2.r) {
        return RelativePosition::SAME;
    }
    if(eq(c1.r + c2.r, dist)) {
        return RelativePosition::TOUCHING;
    }
    if(dist > c1.r + c2.r) {
        return RelativePosition::NO_COMMON_POINTS;
    }
    return RelativePosition::INTERSECTING;
}

int calc(int a[5]) {
    int sum = 0;

    for(int i = 0; a[i]; ++i) {
        sum += i;
    }
    return sum;
}


void f(int* arr1, const int* arr2) {
    int* p1 = arr1;
    const int* p2 = arr2;

    while(*p2 >= 0) {
        *p1++ = *p2++;
    }
}


int main() {
    int a[7] = {1, 2, 3};
    std::cout << calc(a) << std::endl;

    char text[] = "hello", *p = text;

    while(*p) std::cout << ++*p++ << std::endl;

{

    int* pt;
    int a[3] = {4, 19, 13};
    pt = &a[1];
    pt += 1;
    std::cout << *pt << std::endl;

}


{

    int A[4] = { -1, -2, -3, -4 };
    int B[4] = {10, 20, 30, -1};
    f(A, B);

    for(int i = 0; i < 4; ++i) {
        std::cout << A[i] << ' ';
    } std::cout << std::endl;


    for(int i = 0; i < 4; ++i) {
        std::cout << B[i] << ' ';
    } std::cout << std::endl;
}
    


    return 0;
}