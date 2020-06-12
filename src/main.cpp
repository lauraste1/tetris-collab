#include <csignal>
#include "display.hpp"
#include <chrono>
#include <vector>
#include <utility>

using namespace std;
using namespace std::chrono;

const int WIDTH = 10;
const int HEIGHT = 21;

// Just a way to have some state while gameboard is still not complete.
struct DummyGameBoard {
    int state;
    pair<int,int> front_pos;
    pair<int,int> back_pos;
    vector<pair<int,Display::Event>> *moves;
    Display::Event front_dir;
    Display::Event back_dir;
};

// Gameboard or maybe user could be responsible for this?
// TODO: For now, just replace DummyGameBoard with an actual game board
// and put in logic for making a block do things
void advance_tick(Display *disp, SpriteSheet *sprites, DummyGameBoard *board) {
    int i = board->state;

    // Check for the move that was made 5 ticks ago.
    if (board->moves->size() > 0 && (*board->moves)[0].first + 5 <= board->state) {
      board->back_dir = (*board->moves)[0].second;
      // This is bad, don't do this.
      board->moves->erase(board->moves->begin());
    }

    // Move the snake's head.
    switch (board->front_dir) {
      case Display::RIGHT:
        board->front_pos.first += 1;
        break;
      case Display::LEFT:
        board->front_pos.first -= 1;
        break;
      case Display::UP:
        board->front_pos.second -= 1;
        break;
      case Display::DOWN:
        board->front_pos.second += 1;
        break;
    }
    // Wrap around the board.
    board->front_pos.first += WIDTH;
    board->front_pos.first %= WIDTH;
    board->front_pos.second += HEIGHT;
    board->front_pos.second %= HEIGHT;

    // Move the snake's tail.
    switch (board->back_dir) {
      case Display::RIGHT:
        board->back_pos.first += 1;
        break;
      case Display::LEFT:
        board->back_pos.first -= 1;
        break;
      case Display::UP:
        board->back_pos.second -= 1;
        break;
      case Display::DOWN:
        board->back_pos.second += 1;
        break;
    }
    board->back_pos.first += WIDTH;
    board->back_pos.first %= WIDTH;
    board->back_pos.second += HEIGHT;
    board->back_pos.second %= HEIGHT;
    board->state += 1;

    // An example of relatively efficient sprite-based drawing.
    // Draw the new sprites.
    disp->blit(sprites->spriteSurf, &sprites->sprites[0], 
        board->front_pos.first, 
        board->front_pos.second);
    // Erase the old.
    disp->clearCell( board->back_pos.first, 
                    board->back_pos.second);
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
    Display disp;
    SpriteSheet sprites("data/tetris.bmp");
    disp.draw_bg(sprites.spriteSurf, &sprites.sprites[7]);

    // This would be replaced with our GameBoard.
    vector<pair<int,Display::Event>> moves;
    DummyGameBoard board { 0, make_pair(5,0), make_pair(0,0),
                           &moves, Display::RIGHT, Display::RIGHT };

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
            // This is just part of the snake game, flip and drop
            // and similar would probably go here.
            if ( ev != Display::QUIT ) {
              board.moves->push_back(make_pair(board.state, ev));
              board.front_dir = ev;
            }
        }
        // This would be something like game_board.update() or do_tick() or similar.
        if ( gameTime.count() / 200 > board.state) {
            advance_tick(&disp, &sprites, &board);
        }

        disp.update();
    }
    return 0;
}
