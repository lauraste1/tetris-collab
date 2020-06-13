#pragma once
#include "SDL2/SDL.h"
#include <iostream>

class SpriteSheet {
  private:
    static const int GAP_W = 8;
    static const int SPRITE_W = 36;
  public:
    SDL_Surface* spriteSurf = NULL;
    SDL_Rect sprites[8];

    SpriteSheet(const char *path);
};

class Display {
  private:
    SDL_Window* window;
    SDL_Surface* screenSurface;
    static const int BLOCK_W = 36;
    const int RES_W = 432;
    const int RES_H = 828;
  public:
    enum Event {
      UP,
      DOWN,
      LEFT,
      RIGHT,
      QUIT,
      NONE
    };
    Display();
    ~Display();
    void draw_bg(SDL_Surface* from_surf, SDL_Rect* bounds);
    void blit(SDL_Surface* from_surf, SDL_Rect* bounds, int x_idx, int y_idx);
    void clearCell(int x_idx, int y_idx);
    Event getEvent();
    void update();
};


