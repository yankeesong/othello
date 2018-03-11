#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <chrono>

using namespace std;


constexpr int MULTIPLIER = 10;

constexpr int LARGE = 999999;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    int alphabeta(Board *b, int depth, int *alpha, int *beta, Side s);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Side side;
    Board *board;
};

#endif
