Work distribution:

Yanke Song: Set up the git repositories; wrote the first version heuristic function; wrote 
the first version of a depth-2 minimax algorithm; wrote the first version of the depth-
adjustable minimax algorithm with alpha-beta pruning.

Haoyuan Sun:



Documentation of improvements:

	First, we wrote a simple heuristic function, which just calculates the difference of 
black and white pieces, with special scores for the pieces at the corner, near the corner,
and at the border. We pick the move with the highest score. This player can beat the 
Simpleplayer about 70 percent of the time.

	Next, we improved out heuristic functions, which takes into account the pieces near
the border as well. Also, we took into account the opponent's pieces we flipped into
the score funtion. Using the new score function, we built a minimax tree of depth 2, 
and chose the move with the best score. This player can beat Simpleplayer, Constant-
timeplayer, as well as the Betterplayer. In the test tournament, we ranked 9th.

	Finally, we extend the minimax tree. With alpha-beta pruning, we search as far as
we think the time limit allows (on average, the searching depth is 8). This player can 
beat Simpleplayer, Constanttimeplayer, Betterplayer, as well as our previous player.