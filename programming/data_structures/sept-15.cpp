#include <iostream>
#include <vector>

using graph = std::vector<std::vector<int>>;

bool connected(graph& g, std::vector<bool>& visited, int root, int goal) {
    if(root == goal) return true;
    visited[root] = true;

    for(int child: g[root]) {
        if(child == goal) {
            return true;
        }
        if(!visited[child]) {
            if(connected(g, visited, child, goal)) {
                return true;
            }
        }
    }

    return false;
}

bool isConnected(graph& g) {
    for(int i = 0; i < g.size(); ++i) {
        for(int j = i + 1; j < g.size(); ++j) {
            std::vector<bool> visited(g.size(), false);
            if(!(connected(g, visited, i, j) || connected(g, visited, j, i))) {
                return false;
            }
        }
    }

    return true;
}


void testGraph(graph& g, int numNodes) {
    std::cout << "Тестов случай: ";
    if (isConnected(g)) {
        std::cout << "Графът е свързан." << std::endl;
    } else {
        std::cout << "Графът не е свързан." << std::endl;
    }
}


bool connected_adj(int mat[][1000], bool visited[], int n, int u, int v) {
    if(u == v) return true; 
    visited[u] = true;
    for(int i = 0; i < n; ++i) {
        if(mat[u][i]) {
            if(i == u) continue;
            if(i == v) return true;
            if(!visited[i] && connected_adj(mat, visited, n, i, v)) return true;
        }
    }
    return false;
} 

void init_false(bool v[], int n) {
    for(int i = 0; i < n; ++i) v[i] = false;
}

bool isConnecedAdj(int mat[][1000], int n) {
    bool visited[10000] = {false, };

    for(int i = 0 ; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            init_false(visited, n);
            if(!(connected_adj(mat, visited, n, i, j) || connected_adj(mat, visited, n, j, i))) {
                return false;
            }
        }
    }
    return true;
}


int main() {

   // Тестов случай 1: Свързан граф
    {
        int numNodes = 6;
        graph g(numNodes);
        g[0].push_back(1);
        g[1].push_back(2);
        g[2].push_back(3);
        g[3].push_back(4);
        g[4].push_back(5);
        testGraph(g, numNodes);
    }

    // Тестов случай 2: Несвързан граф
    {
        int numNodes = 6;
        graph g(numNodes);
        g[0].push_back(1);
        g[2].push_back(3);
        g[4].push_back(5);
        testGraph(g, numNodes);
    }

    // Тестов случай 3: Свързан граф с цикъл
    {
        int numNodes = 5;
        graph g(numNodes);
        g[0].push_back(1);
        g[1].push_back(2);
        g[2].push_back(3);
        g[3].push_back(4);
        g[4].push_back(0); // Цикъл
        testGraph(g, numNodes);
    }

    // Тестов случай 4: Граф с изолирани върхове
    {
        int numNodes = 6;
        graph g(numNodes);
        g[0].push_back(1);
        g[1].push_back(2);
        g[3].push_back(4);
        testGraph(g, numNodes);
    }

    // Тестов случай 5: Празен граф
    {
        int numNodes = 0;
        graph g(numNodes);
        testGraph(g, numNodes);
    }

    // Тестов случай 6: Един връх без ребра
    {
        int numNodes = 1;
        graph g(numNodes);
        testGraph(g, numNodes);
    }

    {
        int numNodes = 6;
        int mat[1000][1000] = {0};

        mat[0][1] = 1;
        mat[1][2] = 1;
        mat[2][3] = 1;
        mat[3][4] = 1;
        mat[4][5] = 1;

        if (isConnecedAdj(mat, numNodes)) {
            std::cout << "Графът е свързан." << std::endl;
        } else {
            std::cout << "Графът не е свързан." << std::endl;
        }
    }

    {
        int numNodes = 6;
        int mat[1000][1000] = {0};

        mat[0][1] = 1;
        mat[2][3] = 1;
        mat[4][5] = 1;

        if (isConnecedAdj(mat, numNodes)) {
            std::cout << "Графът е свързан." << std::endl;
        } else {
            std::cout << "Графът не е свързан." << std::endl;
        }
    }

    {
        int numNodes = 5;
        int mat[1000][1000] = {0};

        mat[0][1] = 1;
        mat[1][2] = 1;
        mat[2][3] = 1;
        mat[3][4] = 1;
        mat[4][0] = 1; // Цикъл

        if (isConnecedAdj(mat, numNodes)) {
            std::cout << "Графът е свързан." << std::endl;
        } else {
            std::cout << "Графът не е свързан." << std::endl;
        }
    }

    {
        int numNodes = 6;
        int mat[1000][1000] = {0};

        mat[0][1] = 1;
        mat[1][2] = 1;
        mat[3][4] = 1;

        if (isConnecedAdj(mat, numNodes)) {
            std::cout << "Графът е свързан." << std::endl;
        } else {
            std::cout << "Графът не е свързан." << std::endl;
        }
    }

    {
        int numNodes = 0;
        int mat[1000][1000] = {0};

        if (isConnecedAdj(mat, numNodes)) {
            std::cout << "Графът е свързан." << std::endl;
        } else {
            std::cout << "Графът не е свързан." << std::endl;
        }
    }

    {
        int numNodes = 1;
        int mat[1000][1000] = {0};

        if (isConnecedAdj(mat, numNodes)) {
            std::cout << "Графът е свързан." << std::endl;
        } else {
            std::cout << "Графът не е свързан." << std::endl;
        }
    }





    return 0;
}