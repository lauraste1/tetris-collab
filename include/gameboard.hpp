#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <vector>

#include "block.hpp"
using namespace std;

#define COLS 10
#define ROWS 21

class GameBoard {
  private:
    int grid[COLS][ROWS];
    int score;
    vector<pair<int, int>> free_positions;
    Block current = Block(Block::straight, false);
    // Block preview;
    void *removeRow();
    void *lockInRow();
    void *pendinglockIn();
    GameBoard();
    void collide();
    int getCell(int x, int y);

  public:
    void toString();
};

#endif
