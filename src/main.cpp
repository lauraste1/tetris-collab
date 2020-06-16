#include <chrono>
#include <csignal>
#include <iostream>
#include <utility>
#include <vector>

#include "displ.hpp"

using namespace std;
using namespace std::chrono;

const int WIDTH = 10;

// Just a way to have some state while gameboard is still not complete.
struct DummyGameBoard {
    int state;
    pair<int, int> front_pos;
    pair<int, int> back_pos;
};

// Gameboard or maybe user could be responsible for this?
// TODO: For now, just replace DummyGameBoard with an actual game board
// and put in logic for making a block do things
void advance_tick(Displ *disp, SpriteSheet *sprites, DummyGameBoard *board) {
    board->front_pos.first += 1;
    board->back_pos.first += 1;
    board->back_pos.first %= WIDTH;
    board->front_pos.first %= WIDTH;
    board->state += 1;

    // An example of relatively efficient sprite-based drawing.
    // Draw the new sprites.
    disp->blit(sprites->spriteSurf, &sprites->sprites[0],
               board->front_pos.first, board->front_pos.second);
    // Erase the old.
    disp->clearCell(board->back_pos.first, board->back_pos.second);
    // Anything else is just left, ostensibly this creates less work,
    // but modern computers are so powerful that the whole thing is usually
    // redrawn anyway and it only takes microseconds. (and there are a bunch of
    // benefits to doing this).
    //
    // It just so happens that this method maps well to things like tetris and
    // snake you can just erase the block and redraw it, leaving the rest of the
    // game board alone.
}

void signalHandler(int signum) {
    cout << "Received signal " << signum;
    exit(0);
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

    // This would be replaced with our GameBoard.
    DummyGameBoard board{0, make_pair(5, 0), make_pair(0, 0)};

    auto now = chrono::steady_clock::now;
    auto begin = now();

    // Also insert events at this point
    //
    // could even have a data structure for events
    // so they are replayable.
    signal(SIGINT, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);
    Displ::Event ev;
    while (1) {
        auto gameTime = chrono::duration_cast<milliseconds>(now() - begin);
        while (Displ::NONE != (ev = disp.getEvent())) {
            switch (ev) {
            case Displ::QUIT:
                return 0;
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
        // This would be something like game_board.update() or do_tick() or
        // similar.
        if (gameTime.count() / 200 > board.state) {
            advance_tick(&disp, &sprites, &board);
        }

        disp.update();
    }
    return 0;
}
