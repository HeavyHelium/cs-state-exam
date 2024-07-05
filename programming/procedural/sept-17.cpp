#include <iostream>

bool valid(int i, int j, int m, int n) {
    return !(i < 0 || j < 0 || i >= m || j >= n);
}

int get_density(char terrain[101][101], int m, int n, int i, int j) {
    if(terrain[i][j] < 0) return 0;
    int res = 1;
    terrain[i][j] *= -1;
    if(valid(i + 1, j, m, n) && terrain[i + 1][j] * -1 == terrain[i][j]) {
        res += get_density(terrain, m, n, i + 1, j);
    }
    if(valid(i - 1, j, m, n) && terrain[i - 1][j] * -1 == terrain[i][j]) {
        res += get_density(terrain, m, n, i - 1, j);
    }
    if(valid(i, j + 1, m, n) && terrain[i][j + 1] * -1 == terrain[i][j]) {
        res += get_density(terrain, m, n, i, j + 1);
    }
    if(valid(i, j - 1, m, n) && terrain[i][j - 1] * -1 == terrain[i][j]) {
        res += get_density(terrain, m, n, i, j - 1);
    }
    return res;
}


int max_density(char terrain[101][101], int m, int n) {
    int max = -1;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            if(terrain[i][j] == '4') {
                int temp = get_density(terrain, m, n, i, j);
                if(temp > max) max = temp;
            }
        }
    }
    return max;
}


int main() {

    char terrain[101][101] = { { 'R', 'R', '1', '1', '2', '2', }, 
                               { '1', 'R', 'R', 'R', '1', '2', },
                               { 'S', '1', 'R', 'R', '2', '3', },
                               { '4', '4', 'S', 'S', 'R', 'R', }, };

    int m = 4;
    int n = 6;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            std::cout << terrain[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << max_density(terrain, m, n) << std::endl;

    return 0;
}