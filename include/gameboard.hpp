#include "block.hpp"
#include <iostream>
#pragma once
using namespace std;

#define COLS 10
#define ROWS 21

class GameBoard{
  private:
    int grid[ROWS][COLS];
    int score;
    Block current=Block(Block::straight, false);
    //Block preview;
    void* removeRow();
    void* lockInRow();
    void* pendinglockIn();
    bool checkCollision(Block current);
    int getCell(int y, int x);
  public:
    GameBoard();
    void toString();
    void printGameBoard(Block current);
};