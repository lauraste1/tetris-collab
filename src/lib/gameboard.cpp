#include <assert.h>
#include <iostream>
#include <string>

#include "gameboard.hpp"

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
