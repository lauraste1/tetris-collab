#include <chrono>
#include <csignal>
#include <iostream>
#include <utility>
#include <vector>

#include "../include/block.hpp"
#include "../include/displ.hpp"
#include "../include/gameboard.hpp"

using namespace std;
using namespace std::chrono;

const int WIDTH = 10;
const int HEIGHT = 21;

// Auto formatting -- I personally hate auto brackets but some people like them.
// Autocomplete
// Error tagging
//
// Break points
// Integrated debugger
// Learning how to use gdb
//
void clear_block(Displ *disp, GameBoard *board) {
    for (int i = board->current.x; i < board->current.x + 4; i++) {
        for (int j = board->current.y; j < board->current.y + 4; j++) {
            if (board->current.isCell(j - board->current.y, i - board->current.x) &&
                (i >= 0 && i < WIDTH) && 
                (j >= 0 && j < HEIGHT))
                disp->clearCell(i, j);
        }
    }
}

bool isOutOfBounds(int x, int y) {
    return x < 0 || x >= WIDTH || y < 0 || y > HEIGHT;
}

bool pendingLocking(Displ *disp, GameBoard *board) {
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

// Display was a bad name because it collided with something in a library somewhere.
void draw_block(Displ *disp, SpriteSheet *sprites, GameBoard *board) {
    int x = board->current.x;
    int y = board->current.y;
    for (int i = x; i < x + 4; i++) {
        for (int j = y; j < y + 4; j++) {
            if ((board->current.isCell(j - (y), i - (x)) ||
                board->getCell(i, j) == 1) && 
                (i >= 0 && i < WIDTH) && 
                (j >= 0 && j < HEIGHT)
                ) {
                disp->blit(sprites->spriteSurf, &sprites->sprites[0], i, j);
            }
        }
    }
}


void advance_tick(Displ *disp, SpriteSheet *sprites, GameBoard *board) {
    // Will clear the background if it lines up with the top of the block.
    clear_block(disp, board);
    board->current.shift(0, 1);
    board->state += 1;
    draw_block(disp, sprites, board);
}

void signalHandler(int signum) {
    cout << "Received signal " << signum;
    exit(0);
}

// TODO: Probably belongs in the video wrapper.
void writeText(string text, SpriteSheet *font, Displ *disp, int x, int y) {
    int offset = 0;
    auto xy = disp->getPx(x, y);
    int x_margin = (36 - 11) / 2;
    int y_margin = (36 - 22) / 2;
    for (char c : text) {
        auto *curr_sprite = &font->sprites[c - ' '];
        disp->blitPixel(font->spriteSurf, curr_sprite,
                        xy.first + offset + x_margin, xy.second + y_margin);
        offset += curr_sprite->w;
    }
}

int main() {
    Displ disp(18, 21);
    SpriteSheet sprites("data/tetris.bmp", 8, 36, 36, 8);
    SpriteSheet font("data/font.bmp", 96, 11, 22, 0);
    disp.draw_bg(sprites.spriteSurf, &sprites.sprites[7], 10, 21);
    font.setColor(255, 0, 0);
    writeText(string("Hello World! 0123"), &font, &disp, 13, 3);
    font.setColor(255, 255, 0);
    writeText(string("Hello World! 0123"), &font, &disp, 13, 4);
    font.setColor(0, 255, 0);
    writeText(string("Hello World! 0123"), &font, &disp, 13, 5);
    font.setColor(0, 255, 255);
    writeText(string("Hello World! 0123"), &font, &disp, 13, 6);
    font.setColor(0, 0, 255);
    writeText(string("Hello World! 0123"), &font, &disp, 13, 7);

    GameBoard board;
    board.current = Block(Block::l_piece, false);

    auto now = chrono::steady_clock::now;
    auto begin = now();

    signal(SIGINT, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);

    Displ::Event ev;
    while (1) {
        auto gameTime = chrono::duration_cast<milliseconds>(now() - begin);
        int dx=0;
        int dy=0;
        bool flip = false;
        while (Displ::NONE != (ev = disp.getEvent())) {
            switch (ev) {
            case Displ::QUIT:
                return 0;
            case Displ::LEFT:
                dx = -1;
                break;
            case Displ::RIGHT:
                dx = 1;
                break;
            case Displ::UP:
                flip = true;
                break;
            case Displ::DOWN:
                dy = 1;
                break;
            default:
                break;
            }
            clear_block(&disp, &board);
            board.current.shift(dx, dy);
            if (flip) board.current.flip(1);
            draw_block(&disp, &sprites, &board);
        }
        if (gameTime.count() / 400 > board.state) {
            advance_tick(&disp, &sprites, &board);
        }

        disp.update();
    }
    return 0;
}
