#include <csignal>
#include "display.hpp"
#include "block.hpp"
#include "gameboard.hpp"
#include <chrono>
#include <vector>
#include <utility>

using namespace std;
using namespace std::chrono;

const int WIDTH = 10;
const int HEIGHT = 21;

// Just a way to have some state while gameboard is still not complete.
/*struct DummyGameBoard {
    int state;
    pair<int,int> front_pos;
    pair<int,int> back_pos;
};*/

// Gameboard or maybe user could be responsible for this?
// TODO: For now, just replace DummyGameBoard with an actual game board
// and put in logic for making a block do things
void advance_tick(Display *disp, SpriteSheet *sprites, GameBoard *board) {
    board->current.shift(0,1);
    board->state+=1;
    for (int i=0; i<WIDTH; i++) {
      for (int j=0; j<HEIGHT; j++) {
        if ((i >= board->current.x) && (i < (board->current.x+4)) && (j >= board->current.y) && (j < (board->current.y+4))) {
          if (board->current.isCell(j-(board->current.y), i-(board->current.x))) {
             disp->blit(sprites->spriteSurf, &sprites->sprites[0], i, j);
          } else {
             disp->clearCell(i,j);
          }
        }
      }
    }
/*    board->front_pos.first += 1;
    board->back_pos.first += 1;
    board->back_pos.first %= WIDTH;
    board->front_pos.first %= WIDTH;
    board->state += 1;

    // An example of relatively efficient sprite-based drawing.
    // Draw the new sprites.
    disp->blit(sprites->spriteSurf, &sprites->sprites[0], 
        board->front_pos.first, 
        board->front_pos.second);
    // Erase the old.
    disp->clearCell( board->back_pos.first, 
                    board->back_pos.second);*/


    // Anything else is just left, ostensibly this creates less work,
    // but modern computers are so powerful that the whole thing is usually redrawn anyway
    // and it only takes microseconds. (and there are a bunch of benefits to doing this).
    //
    // It just so happens that this method maps well to things like tetris and snake
    // you can just erase the block and redraw it, leaving the rest of the game board alone.
}

void signalHandler(int signum) {
  cout << "Received signal " << signum;
  exit(0);
}

int main() {
    Display disp(10,21);
    SpriteSheet sprites("data/tetris.bmp", 8);
    disp.draw_bg(sprites.spriteSurf, &sprites.sprites[7]);

    // This would be replaced with our GameBoard.
    //DummyGameBoard board { 0, make_pair(5,0), make_pair(0,0)};
    GameBoard board = GameBoard();
    board.current = Block(Block::l_piece, false);

    auto now = chrono::steady_clock::now;
    auto begin = now();

    // Also insert events at this point
    //
    // could even have a data structure for events
    // so they are replayable.
    signal(SIGINT, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);
    Display::Event ev;
    while ( 1 ) {
        auto gameTime = chrono::duration_cast<milliseconds>(now() - begin);
        while (  Display::NONE != (ev = disp.getEvent()) ) {
            switch (ev) {
              case Display::QUIT:
                return 0;
              case Display::LEFT:
                cout << "Left\n";
                break;
              case Display::RIGHT:
                cout << "Right\n";
                break;
              case Display::UP:
                cout << "UP\n";
                break;
              case Display::DOWN:
                cout << "DOWN\n";
                break;
              default:
                break;
            }
        }
        // This would be something like game_board.update() or do_tick() or similar.
        if ( gameTime.count() / 400 > board.state) {
            advance_tick(&disp, &sprites, &board);
        }

        disp.update();
    }
    return 0;
}
