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

void clear_block(Video_Wrapper *disp, GameBoard *board) {
    int y = board->current.y;
    int x = board->current.x;
    for (int i = x; i < (x + 4); i++) {
        for (int j = y; j < (y + 4); j++) {
            if (board->current.isCell(j - y, i - x) &&
                (i >= 0 && i < WIDTH) && 
                (j >= 0 && j < HEIGHT))
                disp->clearCell(i, j);
        }
    }
}

void draw_block(Video_Wrapper *disp, SpriteSheet *sprites, GameBoard *board) {
    int x = board->current.x;
    int y = board->current.y;
    for (int i = x; i < x + 4; i++) {
        for (int j = y; j < y + 4; j++) {
            if ((board->current.isCell(j - (y), i - (x)) ||
                board->getCell(i, j) == 1) && 
                (i >= 0 && i < WIDTH) && 
                (j >= 0 && j < HEIGHT)) {
                disp->blit(sprites->spriteSurf, &sprites->sprites[0], i, j);
            }
        }
    }
}

void advance_tick(Video_Wrapper *disp, SpriteSheet *sprites, GameBoard *board) {
    clear_block(disp, board);
    board->state += 1;
    board->current.shift(0, 1);    
    draw_block(disp, sprites, board);
}

void signalHandler(int signum) {
    cout << "Received signal " << signum;
    exit(0);
}

int main() {
    Video_Wrapper disp(18, 21);
    SpriteSheet sprites("data/tetris.bmp", 8, 36, 36, 8);
    SpriteSheet font("data/font.bmp", 96, 11, 22, 0);
    disp.draw_bg(sprites.spriteSurf, &sprites.sprites[7], 10, 21);
    font.setColor(255, 0, 0);
    disp.writeText(string("Hello World! 0123"), &font, &disp, 13, 3);
    font.setColor(255, 255, 0);
    disp.writeText(string("Hello World! 0123"), &font, &disp, 13, 4);
    font.setColor(0, 255, 0);
    disp.writeText(string("Hello World! 0123"), &font, &disp, 13, 5);
    font.setColor(0, 255, 255);
    disp.writeText(string("Hello World! 0123"), &font, &disp, 13, 6);
    font.setColor(0, 0, 255);
    disp.writeText(string("Hello World! 0123"), &font, &disp, 13, 7);

    GameBoard board;
    board.current = Block(Block::l_piece, false);

    auto now = chrono::steady_clock::now;
    auto begin = now();

    signal(SIGINT, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);

    Video_Wrapper::Event ev;
    while (1) {
        auto gameTime = chrono::duration_cast<milliseconds>(now() - begin);
        int dx=0;
        int dy=0;
        bool flip = false;

        while (Video_Wrapper::NONE != (ev = disp.getEvent())) {
            switch (ev) {
            case Video_Wrapper::QUIT:
                return 0;
            case Video_Wrapper::LEFT:
                dx = -1;
                cout << "Left\n";
                break;
            case Video_Wrapper::RIGHT:
                dx = 1;
                cout << "Right\n";
                break;
            case Video_Wrapper::UP:
                flip = true;
                cout << "UP\n";
                break;
            case Video_Wrapper::DOWN:
                dy = 1;
                break;
            default:
                break;
            }
            clear_block(&disp, &board);
            board.current.shift(dx, dy);
            if (flip)
                board.current.flip(1);
            draw_block(&disp, &sprites, &board);
        }
        if (gameTime.count() / 400 > board.state) {
            advance_tick(&disp, &sprites, &board);
        }

        disp.update();
    }
    return 0;
}
