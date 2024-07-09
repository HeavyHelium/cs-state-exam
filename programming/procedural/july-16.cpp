#include <iostream>
#include <vector>
#include <iomanip>

int connected_components(double matrix[][11], int comps[][11], int size=11) {
    int id = 0;
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            if(comps[i][j] < 0) {
                comps[i][j] = id;
                comps[j][i] = id;
                comps[size - 1 - i][size - 1 - j] = id;
                comps[size - 1 - j][size - 1 - i] = id;
                ++id;
            }
        }
    }

    return id;
}

void averagize(double matrix[][11], int comps[][11], int size=11) {
    for(int  i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            comps[i][j] = -1;
        }
    }
    int cnt = connected_components(matrix, comps, size);

    std::vector<double> sums(cnt, 0);
    std::vector<int> cnts(cnt, 0);

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            sums[comps[i][j]] += matrix[i][j];
            cnts[comps[i][j]] += 1;
        }
    }

    for(int i = 0; i < sums.size(); ++i) {
        if(cnts[i]) sums[i] /= cnts[i];
    }

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            matrix[i][j] = sums[comps[i][j]];
        }
    }
}



int main() {
    double matrix[11][11] = {
            {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 1, 2, 3},
            {2.1, 3.2, 4.3, 5.4, 6.5, 7.6, 8.7, 9.8, 2, 3, 4},
            {3.1, 4.2, 5.3, 6.4, 7.5, 8.6, 9.7, 1.8, 3, 4, 5},
            {4.1, 5.2, 6.3, 7.4, 8.5, 9.6, 1.7, 2.8, 4, 5, 6},
            {5.1, 6.2, 7.3, 8.4, 9.5, 1.6, 2.7, 3.8, 5, 6, 7},
            {6.1, 7.2, 8.3, 9.4, 1.5, 2.6, 3.7, 4.8, 6, 7, 8},
            {7.1, 8.2, 9.3, 1.4, 2.5, 3.6, 4.7, 5.8, 7, 8, 9},
            {8.1, 9.2, 1.3, 2.4, 3.5, 4.6, 5.7, 6.8, 8, 9, 1},
            {9.1, 1.2, 2.3, 3.4, 4.5, 5.6, 6.7, 7.8, 9, 1, 2},
            {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 1, 2, 3},
            {2.1, 3.2, 4.3, 5.4, 6.5, 7.6, 8.7, 9.8, 2, 3, 4},
    };

    
    int comps[11][11];

    averagize(matrix, comps, 11);
    
    std::cout << std::setprecision(2);
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}


// a01 a02 a03 a04 a05 
// a11 a12 a13 a14 a15 
// a21 a22 a13 a14 a15
// a11 a12 a13 a14 a15
// a11 a12 a13 a14 a15