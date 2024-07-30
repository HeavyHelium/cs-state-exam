#include <iostream>
#include <vector>


struct Point {
    int x = 0;
    int y = 0;
    bool operator==(const Point& other) const {
        return other.x == x && y == other.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

using Board = std::vector<std::vector<int>>;


class GamePlayer {
    Point position;

public:
    GamePlayer(const Point& p) : position(p) {}
    virtual Point getPosition() const {
        return position;
    }
    virtual std::vector<Point> allowedMoves(const Board& board) const = 0;
    virtual std::string type() const = 0;
    void move(const Point to) { position = to; }
    static bool valid(const Point& p, const Board& board) {
        return p.x < board.size() && p.x >= 0 && 
               p.y < board.size() && p.y >= 0;
    }
    static bool any_fire_adj(const Point& p, const Board& board) {
        for(int i = -1; i < 2; ++i) {
            for(int j = -1; j < 2; ++j) {
                if(i == 0 && j == 0) continue;
                Point adj = p;
                adj.x += i;
                adj.y += j;
                if(valid(adj, board) && board[adj.x][adj.y] == 1) {
                    return true;
                }
            }
        }

        return false;
    }

    static bool player_at_pos(const std::vector<GamePlayer*>& players, Point pos) {
        for(const GamePlayer* p: players) {
            if(p->getPosition() == pos) return true;
        }
        return false;
    }


    static bool at_war(const std::vector<GamePlayer*>& players, const Board& b) {
        for(const GamePlayer* player: players) {
            Point pos = player->getPosition();
            bool ok = false;

            for(int i = -1; i < 2; ++i) {
                for(int j = -1; j < 2; ++j) {
                    if(i == 0 && j == 0) continue;
                    Point adj = pos;
                    adj.x += i;
                    adj.y += j;

                    if(GamePlayer::valid(adj, b) && player_at_pos(players, adj)) {
                        ok = true;
                    }
                }
            }
            if(!ok) return false;
        }
        return true;
    }
};

class Knight: public GamePlayer {
public:
    Knight(const Point& p) : GamePlayer(p) {}
    std::vector<Point> allowedMoves(const Board& board) const override {
        std::vector<Point> vec;
        for(int i = -1; i < 2; ++i) {
            for(int j = -1; j < 2; ++j) {
                if(i != 0 && j != 0) {
                    Point pos = this->getPosition();
                    pos.x += i;
                    pos.y += j;
                    if(GamePlayer::valid(pos, board) && 
                       board[pos.x][pos.y] == 0 && 
                       !any_fire_adj(pos, board)) {
                        vec.push_back(pos);
                    }
                }
            }
        }

        return vec;
    }


    virtual std::string type() const override {
        return "Knight";
    }
};


class SeaMonster: public GamePlayer {
public:
    SeaMonster(const Point& p) : GamePlayer(p) {}
    std::vector<Point> allowedMoves(const Board& board) const override {
        std::vector<Point> vec;
        for(int j = this->getPosition().y - 1; j >= 0; --j) {
            if(! board[this->getPosition().x][j] == 2) break;
            vec.push_back(Point{this->getPosition().x, j});
        }

        for(int j = this->getPosition().y + 1; j < board.size(); ++j) {
            if(! board[this->getPosition().x][j] == 2) break;
            vec.push_back(Point{this->getPosition().x, j});
        }

        for(int j = this->getPosition().x - 1; j >= 0; --j) {
            if(! board[this->getPosition().x][j] == 2) break;
            vec.push_back(Point{j, this->getPosition().y});
        }

        for(int j = this->getPosition().x + 1; j < board.size(); ++j) {
            if(! board[this->getPosition().x][j] == 2) break;
            vec.push_back(Point{j, this->getPosition().y});
        }

        return vec;
    }

    virtual std::string type() const override {
        return "SeaMonster";
    }

};


void allMoves(std::vector<GamePlayer*> players, const Board& b) {
    for(GamePlayer* player: players) {
        std::vector<Point> allowed_moves = player->allowedMoves(b);
        Point curr = player->getPosition();
        for(const Point& m : allowed_moves) {
            player->move(m);
            if(GamePlayer::at_war(players, b)) {
                std::cout << player->type() << curr << "->" << m << '\n';
            }
            player->move(curr);
        }
    }
}




int main() {
    Board board = {
        {1, 1, 0, 2, 2},
        {0, 2, 1, 0, 2},
        {2, 2, 2, 2, 1},
        {1, 1, 2, 2, 0},
        {2, 2, 1, 1, 1},
    };

    Knight knight(Point{2, 1});
    SeaMonster seaMonster(Point{0, 1});

    std::vector<GamePlayer*> players = {&knight, &seaMonster};

    allMoves(players, board);



    return 0;
}