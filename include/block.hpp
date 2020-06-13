#pragma once
#include <string>
#include <iostream>
using namespace std;

class Block{
  private:
    int x;
    int y;

  public:
    enum Shape {
        l_piece,
        straight,
        squiggley,
        square,
        t_piece
    };
    int cells[4][4];
    bool isCell(int y, int x);
    int rotation;
    Block(Block::Shape shape, bool mirror);
    void flip(int rotation);
    int shift(int dx, int dy);
    string toString();
    int getX();
    int getY();
};
