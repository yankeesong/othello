#ifndef __COMMON_H__
#define __COMMON_H__

enum Side {
    WHITE, BLACK
};

class Move {

public:
    int x, y;
    Move(int x, int y) {
        this->x = x;
        this->y = y;
    }
    ~Move() {}

    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

    bool border()
    {
      int x = this->x;
      int y = this->y;
      
      if (x == 0 || x == 7 || y == 0 || y == 7) return true;
      
      return false;
    }

    bool corner()
    {
      int x = this->x;
      int y = this->y;
      
      if ((x == 0 || x == 7) && (y == 0 || y == 7)) return true;
      
      return false;
    }

    bool near_corner()
    {
      int x = this->x;
      int y = this->y;

      if ((x == 1 || x == 6) && (y == 0 || y == 7)) return true;
      else if ((x == 1 || x == 6) && (y == 1 || y == 6)) return true;
      else if ((x == 0 || x == 7) && (y == 1 || y == 6)) return true;

      return false;
    }
};

#endif
