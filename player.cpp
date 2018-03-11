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

    int time_last_iter = 0;

    int moves_left = (64 - board->countBlack() - board->countWhite() + 1) / 2;
    int turn_time = (msLeft > 0) ? (msLeft / moves_left) : LARGE;

    if (turn_time > 30000) turn_time = 30000;

    Side other = (this->side == BLACK) ? WHITE : BLACK;
    board->doMove(opponentsMove, other);

    Move *ret = new Move(-1, -1);


    int dep = 1;
    while (time_last_iter * MULTIPLIER < turn_time) {
        auto start = chrono::system_clock::now();

        int bestx = -1, besty = -1;
        int best_score = -LARGE;

        Move *m = new Move(0, 0);
        for (int x = 0; x < 8; ++x){
            for (int y = 0; y < 8; ++y) {
                m->setX(x);
                m->setY(y);

                if (this->board->checkMove(m, this->side)) {

                    Board * newboard = this->board->copy();

                    int v = newboard->score(m, this->side);
                    std::cerr<<"move score is"<<v<<std::endl;
                    newboard->doMove(m, this->side);
                    std::cerr<<"did move "<<x<<"and"<<y<<std::endl;
                    int *alpha, *beta;
                    alpha = new int(-LARGE);
                    beta = new int(LARGE);
                    v += Player::alphabeta(newboard, dep, alpha, beta, other);
                    delete alpha;
                    delete beta;
                    std::cerr<<"final score is"<<v<<std::endl;
                    if (v > best_score) {
                        best_score = v;
                        bestx = x, besty = y;
                    }

                    delete newboard;
                }
            }
        }
        delete m;

        std::cerr<<"best move is "<<bestx<<"and"<<besty<<std::endl;

        if (bestx < 0) break;

        ret->setX(bestx);
        ret->setY(besty);

        auto end = chrono::system_clock::now();
        auto d = chrono::duration<double>(end - start);

        time_last_iter = int(d.count() * 1000 + 0.5);
        turn_time -= time_last_iter;
        dep += 1;
        if (dep >= 10) break;
        std::cerr<<"next round, depth is now "<<dep<<std::endl;

    }

    this->board->doMove(ret, this->side);
    return ret;
}

int Player::alphabeta(Board *b, int depth, int *alpha, int *beta, Side side) {
    Side other = (side == BLACK) ? WHITE : BLACK;

    if (depth == 0) return 0;
    if (!b->hasMoves(side)) return 0;
    if (side == this->side)
    {
      int v = -LARGE;

      Move *m = new Move(0, 0);
      for (int x = 0; x < 8; ++x){
          for (int y = 0; y < 8; ++y) {
              m->setX(x);
              m->setY(y);

              if (b->checkMove(m, side)) {
                  Board * newboard = b->copy();

                  int newv = newboard->score(m, side);
                  newboard->doMove(m, side);

                  newv += Player::alphabeta(newboard, depth-1, alpha, beta, other);
                  delete newboard;
                  if (newv > v) v = newv;
                  if (v > *alpha) *alpha = v;
                  if (*beta <= *alpha) break;


              }
          }
      }
      delete m;
      return v;
    }


    else
    {
      int v = LARGE;

      Move *m = new Move(0, 0);
      for (int x = 0; x < 8; ++x){
          for (int y = 0; y < 8; ++y) {
              m->setX(x);
              m->setY(y);

              if (b->checkMove(m, side)) {
                  Board * newboard = b->copy();

                  int newv = -newboard->score(m, side);
                  newboard->doMove(m, side);

                  newv += Player::alphabeta(newboard, depth-1, alpha, beta, other);
                  delete newboard;
                  if (newv < v) v = newv;
                  if (v < *beta) *beta = v;
                  if (*beta <= *alpha) break;


              }
          }
      }
      delete m;
      return v;
    }
}
