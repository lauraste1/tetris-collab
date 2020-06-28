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

  public:
    void removeRow();
    void pendinglockIn();
    void collide();
    int getCell(int x, int y);
    void lockInRow();
    bool checkCollision();
    int state;
    Block current = Block(Block::squiggley, false);
    GameBoard();
    void toString();
    void printGameBoard();
};

#endif
