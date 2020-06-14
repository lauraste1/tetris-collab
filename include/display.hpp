#pragma once
#include "SDL2/SDL.h"
#include <iostream>

class SpriteSheet {
  private:
    const int num_sprites;
    const int sprite_w;
    const int sprite_h;
    const int gap_w;

  public:
    SDL_Surface* spriteSurf;
    SDL_Rect sprites[96]; //TODO: Make this not static.
    SpriteSheet(const char *path, int num_sprites, int sprite_w, int sprite_h, int gap_w);
};

class Display {
  private:
    SDL_Window* window;
    SDL_Surface* screenSurface;
    static const int BLOCK_W = 36;
    const int width;
    const int height;
  public:
    enum Event {
      UP,
      DOWN,
      LEFT,
      RIGHT,
      QUIT,
      NONE
    };
    Display(int width, int height);
    ~Display();
    void draw_bg(SDL_Surface* from_surf, SDL_Rect* bounds, int bg_width, int bg_height);
    void blit(SDL_Surface* from_surf, SDL_Rect* bounds, int x_idx, int y_idx);
    void blitPixel(SDL_Surface* from_surf, SDL_Rect* bounds, int x_px, int y_px);
    void clearCell(int x_idx, int y_idx);
    Event getEvent();
    void update();
};


