#include "block.hpp"
#include <iostream>
#include <vector>
#pragma once
using namespace std;

#define COLS 10
#define ROWS 21

class GameBoard{
  private:
    int grid[ROWS][COLS];
    int score;
    vector <pair<int,int>> free_positions;
    Block current=Block(Block::straight, false);
    //Block preview;
    void* removeRow();
    void* lockInRow();
    void* pendinglockIn();
    GameBoard();
    void collide(Block current);
    int getCell(int y, int x);
  public:
    void toString();
};