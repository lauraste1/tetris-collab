#pragma once
#include <SDL2/SDL.h>
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
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    static const int BLOCK_W = 36;
    const int RES_W = 640;
    const int RES_H = 480;
  public:
    Display();
    ~Display();
    void blit(SDL_Surface* from_surf, SDL_Rect* bounds, int x_idx, int y_idx);
    bool update();
};

