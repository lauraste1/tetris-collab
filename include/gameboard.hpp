#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <vector>

#include "block.hpp"
#include "displ.hpp"

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
    bool isOutOfBounds(int x, int y);
    bool pendingLockIn(Video_Wrapper *disp, GameBoard *board);
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
