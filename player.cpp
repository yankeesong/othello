#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    this->side = side;
    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    this->board = new Board;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete this->board;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* the greedy method
       Move * move = new Move(0, 0);
       Side oppo;
       if (this->side == BLACK) oppo = WHITE;
       else oppo = BLACK;


       this->board->doMove(opponentsMove, oppo);



       if (!this->board->hasMoves(this->side)) return nullptr;

       int bestx = 0;
       int besty = 0;
       int bestscore = -100;
       for (int x = 0; x < 8; x++)
       {
       for (int y = 0; y < 8; y++)
       {
       move->setX(x);
       move->setY(y);

       if (this->board->checkMove(move, this->side))
       {
       int diff = this->board->score(move, side);
       if (diff > bestscore)
       {
       bestx = x;
       besty = y;
       bestscore = diff;
       }
       }
       }
       }
       move->setX(bestx);
       move->setY(besty);
       this->board->doMove(move, this->side);
       return move;
       */
    Move * move = new Move(0, 0);
    Move * next = new Move(0, 0);
    Side other;
    if (this->side == BLACK) other = WHITE;
    else other = BLACK;

    this->board->doMove(opponentsMove, other);

    if (!this->board->hasMoves(this->side)) return nullptr;

    int bestx = 0;
    int besty = 0;
    int minimax = -LARGE;
    
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            move->setX(x);
            move->setY(y);

            if (this->board->checkMove(move, this->side))
            {
                Board * newboard = this->board->copy();
                newboard->doMove(move, this->side);

                int min = LARGE;

                for (int x1 = 0; x1 < 8; x1++)
                {
                    for (int y1 = 0; y1 < 8; y1++)
                    {
                        next->setX(x1);
                        next->setY(y1);

                        if (newboard->checkMove(next, other))
                        {
                            int diff = testingMinimax ? -(newboard->test_score(next, other))
                            	: -(newboard->score(next, other));
                            if (diff < min) min = diff;
                        }
                    }
                }
                
                int cur_score = (testingMinimax ? board->test_score(move, side)
                            	: board->score(move, side)) + min;
                
                if (cur_score > minimax)
                {
                    minimax = cur_score;
                    bestx = x;
                    besty = y;
                }
                delete newboard;
            }
        }
    }
    
    delete next;

    move->setX(bestx);
    move->setY(besty);
    this->board->doMove(move, this->side);

    return move;
}
