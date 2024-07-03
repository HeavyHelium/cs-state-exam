#include <iostream>
#include <algorithm>
#include <vector>

bool valid(int i, int j, int m, int n) {
    return !(i >= m || j < 0 || i < 0 || j >= n);
} 

bool adj(int a, int b) {
    return a + b == 0 || a != 0 && b != 0;
}

int directions[3] = {-1, 0, 1};


void fill_component(int matrx[][6], int compn[][6], int m, int n, int i, int j, int id=1) {
    if(!valid(i, j, m, n)) {
        return;
    }
    if(compn[i][j] != -1) return;
    compn[i][j] = id;

    for(int x = -1; x < 2; ++x) {
        for(int y = -1; y < 2; ++y) {
            if(valid(i + x, j + y, m, n) && adj(matrx[i + x][j + y], matrx[i][j])) {
                fill_component(matrx, compn, m, n, i + x, j + y, id);
            }
        }
    }
}


int fill_components(int matrx[][6], int comp[][6], int m, int n) {
    int id = 0;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            if(comp[i][j] != -1) continue;

            if(matrx[i][j] == 0) {
                fill_component(matrx, comp, m, n, i, j, 0);
            } else {
                id += 1;
                fill_component(matrx, comp, m, n, i, j, id);
            }
        }
    }
    return id;
}

struct EqMem {
    int x = -1; 
    int y = -1;
    double score = 0;

    bool empty() const { return x == -1 && y == -1; }
};

void component_scores(int matrix[][6], int components[][6], int m, int n) {
    int comps = fill_components(matrix, components, 6, 6);
    std::vector<EqMem> members(comps + 1);

    std::vector<double> cnts(comps + 1, 0);

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(members[components[i][j]].empty()) {
                members[components[i][j]].x = i;
                members[components[i][j]].y = j;
            }
            members[components[i][j]].score += matrix[i][j];
            cnts[components[i][j]] += 1;            
        }
    }
    for(int i = 0; i < members.size(); ++i) {
        members[i].score /= cnts[i];
    }

    std::sort(members.begin(), members.end(), [](const EqMem& m1, const EqMem& m2){ 
                                                 return m1.score > m2.score; });

    for(int i = 0; i < int(members.size()) - 1; ++i) {
        const EqMem& m = members[i]; 
        std::cout << "(" << m.x << ", " << m.y << ")" << m.score << "; "; 
    } std::cout << std::endl;

    
}

int main() {

    int matrix[][6] = { 170, 0, 0, 255, 221, 0, 
                        68, 0, 17, 0, 0, 68, 
                        221, 0, 238, 136, 0, 255, 
                        0, 0, 85, 0, 136, 238, 
                        238, 17, 0, 68, 0, 255, 
                        85, 170, 0, 221, 17, 0 };

    int components[6][6] = { -1, };

    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 6; ++j) {
            components[i][j] = -1;
        }
    }

    component_scores(matrix, components, 6, 6);

    return 0;
}