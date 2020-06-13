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

void GameBoard::collide(Block current) {
    ;
}