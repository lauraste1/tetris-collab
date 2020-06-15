#include "gameboard.hpp"
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

GameBoard::GameBoard() {
  for (int i=0; i<ROWS; i++)
    for (int j=0; j<COLS; j++)
      grid[i][j]=0;
}

void GameBoard::toString() {
    for (int i=0; i<ROWS; i++)
        for (int j=0; j<COLS; j++)
            cout << grid[i][j];
}

int GameBoard::getCell(int y, int x) {
	if (grid[x][y])
        return grid[x][y];
  return -1;
}

bool GameBoard::checkCollision(Block current) {
  for (int i=current.x; i<(current.x + 4); i++) {
    for (int j=current.y; j<(current.y + 4); j++) {
      if ((current.isCell(j-current.y, i-current.x)) && (getCell(j,i))==0) {
        return true;
      }
    }
  }
  return false;
}
/*
void GameBoard::lockInRow(Block current) {
  for (int i=current.x; i<(current.x + 4); i++) {
    for (int j=current.y; j<(current.y + 4); j++) {
      if (current.isCell(j-current.y, i-current.x)) {
        grid[i][j]=2;
      }
    }
  }
}*/


//void* pendinglockIn();

void GameBoard::printGameBoard(Block current) {
    for (int i=0; i<ROWS; i++) {
      for (int j=0; j<COLS; j++) {
        if ((i >= current.x) && (i < (current.x+4)) && (j >= current.y) && (j < (current.y+4))) {
          if (current.isCell(j-current.y, i-current.x)) {
             cout << "1";
          } else {
             cout << "0";
          }
        } else {
          cout << grid[i][j];
        }
        if (j==(COLS-1))
          cout << "\n";
      }
    }
}