#include <csignal>
#include "display.hpp"

using namespace std;

void signalHandler(int signum) {
  cout << "Received signal " << signum;
  exit(0);
}

int main() {
    Display disp;
    SpriteSheet sprites("data/tetris.bmp");
    disp.draw_bg(sprites.spriteSurf, &sprites.sprites[7]);
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
