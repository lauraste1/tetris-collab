#include <csignal>
#include "display.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

// Just a way to have some state while gameboard is still not complete.
struct DummyGameBoard {
    int state;
};

// Gameboard or maybe user could be responsible for this?
void advance_tick(Display *disp, SpriteSheet *sprites, DummyGameBoard *board) {
    int i = board->state;
    board->state += 1;
    disp->blit(sprites->spriteSurf, &sprites->sprites[i%7], i % 10, (i / 10) % 21);
}

void signalHandler(int signum) {
  cout << "Received signal " << signum;
  exit(0);
}

int main() {
    Display disp;
    SpriteSheet sprites("data/tetris.bmp");
    disp.draw_bg(sprites.spriteSurf, &sprites.sprites[7]);
    DummyGameBoard board = {0};

    auto now = chrono::steady_clock::now;
    auto begin = now();

    while ( disp.update() ) {
      auto gameTime = chrono::duration_cast<milliseconds>(now() - begin);
      while ( gameTime.count() / 500 > board.state )
        // Also insert events at this point
        //
        // could even have a data structure for events
        // so they are replayable.
        advance_tick(&disp, &sprites, &board);
    signal(SIGINT, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);

    for (int i=0;i<7;i++) {
      disp.blit(sprites.spriteSurf, &sprites.sprites[i], i, 0);
      if (i == 3) disp.clearCell(i,0);
    }

    Display::Event ev;
    while ( 1 ) {
      while ( Display::NONE != (ev = disp.getEvent()) ) {
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
      disp.update();
    }
    return 0;
}
