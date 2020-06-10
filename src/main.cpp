#include "display.hpp"

using namespace std;

int main() {
    Display disp;
    SpriteSheet sprites("data/tetris.bmp");
    disp.draw_bg(sprites.spriteSurf, &sprites.sprites[7]);

    for (int i=0;i<7;i++) {
      disp.blit(sprites.spriteSurf, &sprites.sprites[i], i, 0);
    }

    bool quit = false;

    while ( disp.update() );
    return 0;
}
