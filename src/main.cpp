#include "display.hpp"

using namespace std;

int main() {
    Display disp;
    SpriteSheet sprites("data/tetris.bmp");

    for (int i=0;i<8;i++) {
      disp.blit(sprites.spriteSurf, &sprites.sprites[i], i, 0);
    }

    bool quit = false;

    while ( disp.update() );
    return 0;
}
