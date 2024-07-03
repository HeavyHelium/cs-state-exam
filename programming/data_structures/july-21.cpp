#include <iostream>
#include <unordered_map>
#include <utility>

/*
В случая можем да изполваме речникова структура с 
ключ -- индекси на елемент от матрицата 
стойност - стойността на позицията, зададена от индекса  

В стандартната библиотека std::map<std::pair<int, int>, double> би ни дала логаримична сложност за основните операции, 
но пазените елементи ще бъдат от порядъка на броя елементи текущо в СД.

От друга страна, std::unordered_map<std::pair<int, int> double> би ни дала константна сложност за основните операции и 
броя на пазените елементи ще бъде от порядъка на броя елементи текущо в СД.

Затова избираме std::unordered_map за демонстрация.
 */



struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2; // комутативна, но добавя Theta(1) сложност в случая
    }
};


using SparseMatrix = std::unordered_map<std::pair<int, int>, double, pair_hash>;

SparseMatrix sum(const SparseMatrix& m1, const SparseMatrix& m2) {
    SparseMatrix s = m1;

    for (auto it = m2.begin(); it != m2.end(); ++it) {
        const std::pair<int, int>& key = it->first;
        const double& value = it->second;
        s[key] += value; 
    }

    return s;
}



int main() {
    SparseMatrix sm1 = { {std::pair<int, int>{0, 10000}, 42.0}, 
                         {std::pair<int, int>{10000, 42}, 6.0} };
    
    SparseMatrix sm2 = { {std::pair<int, int>{0, 10000}, 10.0}, 
                         {std::pair<int, int>{42, 0}, 3.0} };
    
    SparseMatrix sm_sum = sum(sm1, sm2);

    for (auto it = sm_sum.begin(); it != sm_sum.end(); ++it) {
        const auto& key = it->first;
        const auto& value = it->second;
        std::cout << "Position (" << key.first << ", " << key.second << ") has value " << value << std::endl;
    }

    return 0;
}