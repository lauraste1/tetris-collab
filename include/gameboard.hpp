#include "block.hpp"
#pragma once
using namespace std;

#define ROWS 10
#define COLS 5

class GameBoard{
  private:
    int grid[ROWS][COLS];
    //int score;
    //Block current;
    //Block preview;
    void* removeRow();
    void* lockInRow();
    void* pendinglockIn();
    GameBoard();
  public:
};

//GameBoard::GameBoard() : grid() {};
GameBoard::GameBoard() {
  for (int i=0; i<ROWS; i++)
    for (int j=0; j<COLS; j++)
      grid[i][j]=0;
}
