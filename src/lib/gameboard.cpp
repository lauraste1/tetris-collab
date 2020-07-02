#include <assert.h>
#include <iostream>
#include <string>

#include "gameboard.hpp"
#include "displ.hpp"

using namespace std;

GameBoard::GameBoard() {
    state = 0;
    for (int x_idx = 0; x_idx < COLS; x_idx++)
        for (int y_idx = 0; y_idx < ROWS; y_idx++)
            grid[x_idx][y_idx] = 0;
}

void GameBoard::toString() {
    for (int x_idx = 0; x_idx < COLS; x_idx++)
        for (int y_idx = 0; y_idx < ROWS; y_idx++)
            cout << grid[x_idx][y_idx];
    cout << '\n';
}

int GameBoard::getCell(int x_idx, int y_idx) { return grid[x_idx][y_idx]; }

bool GameBoard::checkCollision() {
    for (int x_idx = current.x; x_idx < (current.x + 4); x_idx++) {
        for (int y_idx = current.y; y_idx < (current.y + 4); y_idx++) {
            if ((current.isCell(y_idx - current.y, x_idx - current.x)) &&
                (getCell(y_idx, x_idx)) == 0) {
                return true;
            }
        }
    }
    return false;
}

void GameBoard::lockInRow() {
  for (int i=current.x; i<(current.x + 4); i++)
    for (int j=current.y; j<(current.y + 4); j++)
      if (current.isCell(j-current.y, i-current.x))
        grid[j][i]=2;
}

bool GameBoard::isOutOfBounds(int x, int y) {
    return x < 0 || x >= COLS || y < 0 || y > ROWS;
}

bool GameBoard::pendingLockIn(Video_Wrapper *disp, GameBoard *board) {
    int x = board->current.x;
    int y = board->current.y;
    for (int i = x; i < x + 4; i++) {
        for (int j = y; j < y + 4; j++) {
            if (board->current.isCell(j - y, i - x)){
                if ((board->getCell(j+1, x) != 0) || isOutOfBounds(j+x, x))
                    return true;
            }
        }
    }
    return false;
}

/*
void GameBoard::removeRow() {
  ;
}*/

void GameBoard::printGameBoard() {
    for (int x_idx = 0; x_idx < COLS; x_idx++) {
        for (int y_idx = 0; y_idx < ROWS; y_idx++) {
            if ((x_idx >= current.x) && (x_idx < (current.x + 4)) &&
                (y_idx >= current.y) && (y_idx < (current.y + 4))) {
                if (current.isCell(y_idx - current.y, x_idx - current.x)) {
                    cout << "1";
                } else {
                    cout << "0";
                }
            } else {
                cout << grid[x_idx][y_idx];
            }
            if (y_idx == (COLS - 1))
                cout << "\n";
        }
    }
}
