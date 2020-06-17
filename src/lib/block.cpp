#include <cstring>

#include "block.hpp"

using namespace std;

Block::Block(Block::Shape shape, bool mirror) {
    x = 4;
    y = 0;
    switch (shape) {
    case straight: {
        int value[4][4] = {
            {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        memcpy(cells, value, sizeof(value));
        break;
    }
    case l_piece: {
        if (mirror) {
            int value[4][4] = {
                {0, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}};
            memcpy(cells, value, sizeof(value));
        } else {
            int value[4][4] = {
                {0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}};
            memcpy(cells, value, sizeof(value));
        }
        break;
    }
    case squiggley: {
        if (mirror) {
            int value[4][4] = {
                {0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}};
            memcpy(cells, value, sizeof(value));
        } else {
            int value[4][4] = {
                {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}};
            memcpy(cells, value, sizeof(value));
        }
        break;
    }
    case square: {
        int value[4][4] = {
            {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
        memcpy(cells, value, sizeof(value));
        break;
    }
    case t_piece: {
        int value[4][4] = {
            {0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}};
        memcpy(cells, value, sizeof(value));
        break;
    }
    }
}

Block::Block() {
    int value[4][4] = {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}};
    memcpy(cells, value, sizeof(value));
}

string Block::toString() {
    string piece;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            piece.append(to_string(cells[i][j]));
            if (j == 3) {
                piece.append("\n");
            }
        }
    }
    return piece;
}

void Block::flip(int new_rotation) {
    int flipped_cells[4][4];
    rotation = new_rotation;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (rotation == 1)
                flipped_cells[3 - j][i] = cells[i][j];
            if (rotation == 2)
                flipped_cells[3 - i][3 - j] = cells[i][j];
            if (rotation == 3)
                flipped_cells[j][3 - i] = cells[i][j];
        }
    }
    memcpy(cells, flipped_cells, sizeof(flipped_cells));
}

void Block::shift(int dx, int dy) {
    x += dx;
    y += dy;
}

bool Block::isCell(int x_idx, int y_idx) {
    if ((y_idx < 0) || (y_idx > 3) || (x_idx < 0) || (x_idx > 3))
        return false;
    if (cells[x_idx][y_idx] > 0)
        return true;
    return false;
}

int Block::getX() { return x; }

int Block::getY() { return y; }
