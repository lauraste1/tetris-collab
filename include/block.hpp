#pragma once
#include <string>
#include <iostream>
using namespace std;

class Block{
  private:
    int cells[4][4];
    int x;
    int y;
    int rotation;

  public:
    enum Shape {
        l_piece,
        straight,
        squiggley,
        square,
        t_piece
    };
    Block(Block::Shape shape, bool mirror);
    void flip(int rotation);
    int shift(int dx, int dy);
    string toString();
    int getX();
    int getY();
};