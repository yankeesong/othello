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

}
