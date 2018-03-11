Work Distribution
==============================

Yanke Song: Set up the git repositories; wrote the first version heuristic function; wrote 
the first version of a depth-2 minimax algorithm; wrote the first version of the depth-
adjustable minimax algorithm with alpha-beta pruning.

Haoyuan Sun: Wrote improved heuristics function; designed and implemented timer heuristic to
use as much of the allowed time limit; updated alpha-beta pruning with speed improvements and 
several major bugfix;


Documentation of Improvements
==============================

	First, we wrote a simple heuristic function, which just calculates the difference of 
black and white pieces, with special scores for the pieces at the corner, near the corner,
and at the border. We pick the move with the highest score. This player can beat the 
Simpleplayer about 70 percent of the time.

	Next, we improved our heuristic function, which takes into account the pieces near
the border as well. Also, we took into account the opponent's pieces we flipped into
the score function. Using the new score function, we built a minimax tree of depth 2, 
and chose the move with the best score. This player can beat Simpleplayer, Constant-
timeplayer, as well as Betterplayer. In the test tournament, we ranked 9th.

	Finally, we extended the minimax tree. With alpha-beta pruning, we search as far as
we think the time limit allows (on average, the searching depth is 8). This player can 
beat Simpleplayer, Constanttimeplayer, Betterplayer, as well as our previous player.

        However, our AI does poorly when time limit is very small (< 60s), in which case the 
search depth is too shallow to justify the extra costs of the alpha-beta pruning overhead. 
We discussed more timing heuristics (such as evaluating the stability of the board), but 
ultimately decided that implementing them will take too long. Also, our AI ties basically
every game with a large time limit (> 15 min), this makes that mini-max priotitize not losing.
We believe this may be addressed with an adaptive heruistic functions. Again this is not done
because it would take too long.
