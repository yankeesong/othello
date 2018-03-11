#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.hpp"
using namespace std;

constexpr int VALUE[8][8] =
	{{10, -3,  5,  5,  5,  5, -3, 10},
	 {-3, -8, -2, -2, -2, -2, -8, -3},
	 { 5, -2,  1,  1,  1,  1, -2,  5},
	 { 5, -2,  1,  1,  1,  1, -2,  5},
	 { 5, -2,  1,  1,  1,  1, -2,  5},
	 { 5, -2,  1,  1,  1,  1, -2,  5},
	 {-3, -8, -2, -2, -2, -2, -8, -3},
	 {10, -3,  5,  5,  5,  5, -3, 10}};

// all 8 directions
constexpr int dx[] = {0, -1, -1, -1,  0,  1, 1, 1};
constexpr int dy[] = {1,  1,  0, -1, -1, -1, 0, 1};


class Board {

private:
    bitset<64> black;
    bitset<64> taken;

    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);

public:
    Board();
    ~Board();
    Board *copy();

    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    int count(Side side);
    int countBlack();
    int countWhite();

    int test_score(Move *m, Side side);
    int score(Side side);
    int score(Move *m, Side side);

    void setBoard(char data[]);
};

#endif
