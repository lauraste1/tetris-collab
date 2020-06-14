#pragma once
#include <string>
#include <iostream>
using namespace std;

class Block{
  private:
    const static int BLOCK_W = 4;
    const static int BLOCK_H = 4;
    int cells[BLOCK_H][BLOCK_W];
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
    int rotation;
    Block(Block::Shape shape, bool mirror);
    void flip(int rotation);
    int shift(int dx, int dy);
    string toString();
    int getX();
    int getY();
};
