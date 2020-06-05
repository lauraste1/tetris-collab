#pragma once
#include <string>
#include <array>

using namespace std;

class Block{
  private:
    array<array<char,4>,4> cells;
    int x;
    int y;
  public:
    enum Shape {
        l_piece,
        straight,
        squiggley,
        square
    };
    Block(Block::Shape shape, bool mirror);
    void flip();
    int shift(int dx, int dy);
    string toString();
    int getX();
    int getY();
};
