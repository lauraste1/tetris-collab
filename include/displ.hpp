#ifndef DISPL_H
#define DISPL_H

#include <iostream>
#include <utility>

#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_video.h"

using namespace std;

class SpriteSheet {
  public:
    SDL_Surface *spriteSurf;
    SDL_Rect sprites[96]; // TODO: Make this not static.
    void setColor(uint8_t r, uint8_t b, uint8_t g);
    SpriteSheet(const char *path, int num_sprites, int sprite_w, int sprite_h,
                int gap_w);
    ~SpriteSheet();
};

class Displ {
  private:
    SDL_Window *window;
    SDL_Surface *screenSurface;
    static const int BLOCK_W = 36;

  public:
    enum Event { UP, DOWN, LEFT, RIGHT, QUIT, NONE };
    Displ(int width, int height);
    ~Displ();
    void draw_bg(SDL_Surface *from_surf, SDL_Rect *bounds, int bg_width,
                 int bg_height);
    void blit(SDL_Surface *from_surf, SDL_Rect *bounds, int x_idx, int y_idx);
    void blitPixel(SDL_Surface *from_surf, SDL_Rect *bounds, int x_px,
                   int y_px);
    void clearCell(int x_idx, int y_idx);
    pair<int, int> getPx(int x, int y);
    Event getEvent();
    void update();
};

#endif
