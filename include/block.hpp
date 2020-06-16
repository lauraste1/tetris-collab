#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <iostream>
#include <string>
using namespace std;

class Block {
  private:
    const static int BLOCK_W = 4;
    const static int BLOCK_H = 4;
    int x;
    int y;

  public:
    enum Shape { l_piece, straight, squiggley, square, t_piece };
    int cells[BLOCK_H][BLOCK_W];
	bool isCell(int x_test, int y_test);
    int rotation;
    Block(Block::Shape shape, bool mirror);
    void flip(int new_rotation);
    int shift(int dx, int dy);
    string toString();
    int getX();
    int getY();
};

#endif
