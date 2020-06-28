#include <chrono>
#include <csignal>
#include <iostream>
#include <utility>
#include <vector>

#include "block.hpp"
#include "displ.hpp"
#include "gameboard.hpp"

using namespace std;
using namespace std::chrono;

const int WIDTH = 10;
const int HEIGHT = 21;
static bool quit = false;

void clear_block(Displ *disp, GameBoard *board) {
    for (int i = board->current.x; i < board->current.x + 4; i++) {
        for (int j = board->current.y; j < board->current.y + 4; j++) {
            disp->clearCell(i, j);
        }
    }
}

void draw_block(Displ *disp, SpriteSheet *sprites, GameBoard *board) {
    int x = board->current.x;
    int y = board->current.y;
    for (int i = x; i < x + 4; i++) {
        for (int j = y; j < y + 4; j++) {
            if (board->current.isCell(j - (y), i - (x)) ||
                board->getCell(i, j) == 1) {
                disp->blit(sprites->spriteSurf, &sprites->sprites[0], i, j);
            }
        }
    }
}

void advance_tick(Displ *disp, SpriteSheet *sprites, GameBoard *board) {
    board->current.shift(0, 1);
    clear_block(disp, board);
    board->state += 1;
    draw_block(disp, sprites, board);
}

void signalHandler(int signum) {
    cout << "Received signal " << signum;
    quit = true;
}

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
    while (!quit) {
        auto gameTime = chrono::duration_cast<milliseconds>(now() - begin);
        while (Displ::NONE != (ev = disp.getEvent())) {
            switch (ev) {
            case Displ::QUIT:
                quit = true;
                break;
            case Displ::LEFT:
                cout << "Left\n";
                break;
            case Displ::RIGHT:
                cout << "Right\n";
                break;
            case Displ::UP:
                cout << "UP\n";
                break;
            case Displ::DOWN:
                cout << "DOWN\n";
                break;
            default:
                break;
            }
        }
        if (gameTime.count() / 400 > board.state) {
            advance_tick(&disp, &sprites, &board);
        }

        disp.update();
    }
    return 0;
}
