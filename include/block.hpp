#pragma once
#include <string>
#include <iostream>
using namespace std;

class Block{
  private:
    const static int BLOCK_W = 4;
    const static int BLOCK_H = 4;

  public:
    enum Shape {
        l_piece,
        straight,
        squiggley,
        square,
        t_piece
    };
    int x;
    int y;
    int cells[BLOCK_H][BLOCK_W];
    bool isCell(int y, int x);
    int rotation;
    Block(Block::Shape shape, bool mirror);
    void flip(int rotation);
    void shift(int dx, int dy);
    string toString();
    int getX();
    int getY();
};
