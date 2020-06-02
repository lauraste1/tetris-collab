#pragma once
#include <string>
using namespace std;

class Block{
  private:
    bool cells[4][4];
    int x;
    int y;
  public:
    enum Shape {
        l_piece,
        straight,
        squiggley,
        square
    };
    Block(Block::Shape shape);
    void flip();
    int shift(int dx, int dy);
    string toString();
    int getX();
    int getY();
};
