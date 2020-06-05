#pragma once
#include <string>
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
    void flip();
    int shift(int dx, int dy);
    string toString();
    int getX();
    int getY();
};

Block::Block(Block::Shape shape, bool mirror) {
    switch (shape) {
        case straight: {
            int value[4][4] = {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}};
            memcpy(cells, value, sizeof(value));
            break;
        }
        case l_piece: {
            if (mirror) {
                int value[4][4] = {{0,0,1,0},{0,0,1,0},{0,1,1,0},{0,0,0,0}};
                memcpy(cells, value, sizeof(value));
            } else {
                int value[4][4] = {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}};
                memcpy(cells, value, sizeof(value));
            }
            break;
        }
        case squiggley: {
            if (mirror) {
                int value[4][4] = {{0,0,0,0},{0,0,1,1},{0,1,1,0},{0,0,0,0}};
                memcpy(cells, value, sizeof(value));
            } else {
                int value[4][4] = {{0,0,0,0},{0,1,1,0},{0,0,1,1},{0,0,0,0}};
                memcpy(cells, value, sizeof(value));
            }
            break;
        }
        case square: {
            int value[4][4] = {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}};
            memcpy(cells, value, sizeof(value));
            break;
        }
        case t_piece: {
            int value[4][4] = {{0,0,0,0},{0,0,1,0},{0,1,1,1},{0,0,0,0}};
            memcpy(cells, value, sizeof(value));
            break;
        }
    }
}
/*
void flipClockwise(Block::Shape, ) {
    if (l_piece) {
        if (mirror) {
            ;
        } else {
            ;
        }

    }
    if (squiggley) {
        if (mirror) {
            ;
        } else {
            ;
        }
    }
*/



