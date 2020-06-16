#include <assert.h>
#include <iostream>
#include <string>

#include "gameboard.hpp"

using namespace std;

GameBoard::GameBoard() {
    for (int i = 0; i < COLS; i++)
        for (int j = 0; j < ROWS; j++)
            grid[i][j] = 0;
}

void GameBoard::toString() {
    for (int i = 0; i < COLS; i++)
        for (int j = 0; j < ROWS; j++)
            cout << grid[i][j];
    cout << '\n';
}

int GameBoard::getCell(int x, int y) {
    if (grid[x][y])
        return grid[x][y];
    return -1;
}

void GameBoard::collide() {}
