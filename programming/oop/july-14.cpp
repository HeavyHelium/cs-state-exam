#include <iostream>
#include <vector>


/*
) Да се дефинира структура ChessPosition, описваща коректна позиция на фигура върху
шахматна дъска (координатите на позицията са от ‘A’ до ‘H’ по едното измерение и от 1 до 8 по
другото).
Да се дефинира абстрактен клас (или интерфейс) ChessPiece, описващ шахматна фигура със
следните операции:
 ChessPosition getPosition() – Връща позицията на фигурата на дъската;
 [подходящ тип] allowedMoves() – Връща списък (колекция) с всички възможни позиции,
до които дадена фигура може да достигне с един ход;
 [булев тип] captures(ChessPosition pos) – Проверява дали фигурата “владее”
позицията pos, подадена като параметър, т.е. дали позицията е в списъка с възможните
ходове на фигурата. Булевият тип да бъде булевият тип в езика, който сте избрали (напр.
bool, ако пишете на C++).
Б) Да се дефинират класовете Rook и Knight – наследници на ChessPiece, описващи съответно
шахматните фигури топ и кон.
В) „Стабилна конфигурация“ наричаме такава подредба на фигурите върху дъската, при която
никоя фигура да не е върху позволен ход на друга фигура (т.е. никои две фигури да не се „бият“).
Да се дефинира функцията allMoves ([подходящ тип] pieces[, …]), която за списъка
(колекцията) pieces, съдържащ произволен брой разнородни шахматни фигури, отпечатва на
конзолата всеки възможен ход на фигура от pieces такъв, че след изпълнението му списъкът с
фигури да описва стабилна конфигурация. Информацията за ходовете да съдържа типа на
фигурата, старата позиция и новата позиция, например:
Rook A1 ‐> B1
Knight B3 ‐> A5


*/


struct ChessPosition {
    char x;
    int y;

    int i() const { return 'H' - x; }
    int j() const { return y - 1; }

    bool operator==(const ChessPosition& other) const {
        return this->x == other.x && 
               this->y == other.y;
    }

    bool valid() const {
        return x >= 'A' && x <= 'H' && y >= 1 && y <= 8;
    }


    friend std::ostream& operator<<(std::ostream& os, const ChessPosition& chp) {
        return os << chp.x << chp.y;
    }
};



class ChessPiece {
    ChessPosition p;
public: 
    ChessPiece(const ChessPosition& p): p(p) { }
    ChessPosition getPos() const { return p; }
    virtual std::vector<ChessPosition> allowedMovies() const = 0;
    bool captures(const ChessPosition& pos) const {
        for(const ChessPosition& p: allowedMovies()) {
            if(pos == p) return true;
        }
        return false;
    }

    virtual std::string type() const = 0;
};


class Rook: public ChessPiece {

public: 
    Rook(const ChessPosition& p): ChessPiece(p) {}
    virtual std::vector<ChessPosition> allowedMovies() const override {
        std::vector<ChessPosition> moves;
        ChessPosition curr = getPos();
        for(char i = curr.x + 1; i <= 'H'; ++i) {
            moves.push_back(ChessPosition{i, curr.y});
        }
        for(char i = curr.x - 1; i >= 'A'; --i) {
            moves.push_back(ChessPosition{i, curr.y});
        }

        for(int j = curr.y + 1; j <= 8; ++j) {
            moves.push_back(ChessPosition{curr.x, j});
        }

        for(int j = curr.j() - 1; j >= 1; --j) {
            moves.push_back(ChessPosition{curr.x, j});
        }

        return moves;
    }

    virtual std::string type() const override { return "Rook"; }
 
};

class Knight: public ChessPiece {

public: 
    Knight(const ChessPosition& p): ChessPiece(p) {}
    virtual std::vector<ChessPosition> allowedMovies() const override {
        std::vector<ChessPosition> moves;
        ChessPosition curr = getPos();
        const int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
        const int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};

        for(int k = 0; k < 8; ++k) {
            int new_x = curr.x + dx[k];
            int new_y = curr.y + dy[k];
            ChessPosition temp{static_cast<char>(new_x), new_y};
            if(temp.valid()) moves.push_back(temp);
        }

        return moves;   
    } 

    virtual std::string type() const override { 
        return "Knight";
    }
};




void allMoves(const std::vector<ChessPiece*>& pieces) {
// for every figure
// no piece exists such that its position is in the allowed list
    for(const ChessPiece* f: pieces) {
        std::vector<ChessPosition> moves = f->allowedMovies(); 
        for(const ChessPiece* other: pieces) {
            if(f != other) {
                for(const ChessPosition& move: moves) {
                    if(move == other->getPos()) {
                        continue;
                    }
                    std::cout << f->type() << " " << f->getPos() << "-> " << move << '\n'; 
                }
            }
        }
    }

}


int main() {
    ChessPosition posRook{'A', 1};
    ChessPosition posKnight{'B', 3};

    Rook rook(posRook);
    Knight knight(posKnight);

    std::vector<ChessPiece*> pieces = {&rook, &knight};
    allMoves(pieces);

}