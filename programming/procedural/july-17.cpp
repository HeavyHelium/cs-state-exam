#include <iostream>


bool valid(int i, int j, int m, int n) {
    return !(i >= m || j >= n || i < 0 || j < 0);
}

bool sparser(const char arr[101][101], int i, int j, int m, int n) {
    int cnt = -1;
    for(int r = -1; r < 2; ++r) {
        for(int s = -1; s < 2; ++s) {
            if(valid(i + r, j + s, m, n) && arr[i][j] == arr[i + r][j + s]) {
                cnt += 1;
            }
        }
    } 
    return cnt > 2;

}

void change10(const char arr[101][101], char res[101][101], int m, int n) {
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            if(arr[i][j] == '1') {
                res[i][j] = '2';
            } else if(arr[i][j] == '2') {
                res[i][j] = '3';
            } else if(arr[i][j] == '3') {
                res[i][j] = '4';
            } else if(arr[i][j] == 'R' || arr[i][j] == 'S') {
                res[i][j] = arr[i][j];
            } else if(arr[i][j] == '4' && sparser(arr, i, j, m, n)) {
                res[i][j] = '3';
            } else if(arr[i][j] == '4'){
                res[i][j] = arr[i][j];
            } else {
                std::cout << "mistake!\n";
            }
        }
    }
}


void change100(char arr[101][101], int  m, int n) {
    char res[101][101];

    for(int i = 0; i < 10; ++i) {
        if((unsigned)i % 2 == 0)
            change10(arr, res, m, n);
        else 
            change10(res, arr, m, n);
    }
}

void print_terrain(const char arr[101][101], int m, int n) {
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            std::cout << arr[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    int m = 4, n = 6;
    char terrain[101][101] = {
        {'R', 'R', '1', '1', '2', '2'},
        {'1', 'R', 'R', 'R', '1', '2'},
        {'S', '1', 'R', 'R', '2', '3'},
        {'4', '4', 'S', 'S', 'R', 'R'}
    };

    

    std::cout << "Initial terrain:\n";
    print_terrain(terrain, m, n);

    change100(terrain, m, n);

    std::cout << "Terrain after 100 years:\n";
    print_terrain(terrain, m, n);

    return 0;
}