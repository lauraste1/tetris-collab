#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <iostream>
#include <string>
using namespace std;

class Block {
  private:
    const static int BLOCK_W = 4;
    const static int BLOCK_H = 4;

  public:
    enum Shape { l_piece = 1 , straight = 2, squiggley = 3, square = 4, t_piece = 5 };
    int x;
    int y;
    int cells[BLOCK_H][BLOCK_W];
    bool isCell(int x_test, int y_test);
    int rotation;
    Block(Block::Shape shape, bool mirror);
    Block();
    void flip(int new_rotation);
    void shift(int dx, int dy);
    string toString();
    int getX();
    int getY();
};

#endif
