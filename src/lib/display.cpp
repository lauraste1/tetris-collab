#include <iostream>
#include <utility>

#include "displ.hpp"
#include "SDL2/SDL.h"

using namespace std;

Displ::Displ(int width, int height) {
    // 2 is for border around drawable area.
    const int RES_W = BLOCK_W * (2 + width);
    const int RES_H = BLOCK_W * (2 + height);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL failed to initialize: %s\n", SDL_GetError());
        throw("SDL init failure");
    }
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, RES_W, RES_H,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created: %s\n", SDL_GetError());
        throw("SDL window failure");
    }
    screenSurface = SDL_GetWindowSurface(window);
}

Displ::~Displ() {
    SDL_FreeSurface(screenSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Displ::blit(SDL_Surface *from_surf, SDL_Rect *bounds, int x_idx,
                 int y_idx) {
    SDL_Rect to_rect = {(1 + x_idx) * BLOCK_W, (1 + y_idx) * BLOCK_W, BLOCK_W,
                        BLOCK_W};
    SDL_BlitSurface(from_surf, bounds, screenSurface, &to_rect);
}

void Displ::blitPixel(SDL_Surface *from_surf, SDL_Rect *bounds, int x_px,
                      int y_px) {
    SDL_Rect to_rect = {x_px, y_px, bounds->w, bounds->h};
    SDL_BlitSurface(from_surf, bounds, screenSurface, &to_rect);
}

void Displ::clearCell(int x_idx, int y_idx) {
    SDL_Rect to_rect = {(1 + x_idx) * BLOCK_W, (1 + y_idx) * BLOCK_W, BLOCK_W,
                        BLOCK_W};
    SDL_FillRect(screenSurface, &to_rect, 0);
}

void Displ::draw_bg(SDL_Surface *from_surf, SDL_Rect *bounds, int bg_width,
                    int bg_height) {
    SDL_Rect to_rect;
    for (int i = 0; i < (bg_width + 2); i++) {
        to_rect = {i * BLOCK_W, 0 * BLOCK_W, BLOCK_W, BLOCK_W};
        SDL_BlitSurface(from_surf, bounds, screenSurface, &to_rect);
        to_rect = {i * BLOCK_W, (bg_height + 1) * BLOCK_W, BLOCK_W, BLOCK_W};
        SDL_BlitSurface(from_surf, bounds, screenSurface, &to_rect);
    }
    for (int j = 0; j < (bg_height + 2); j++) {
        to_rect = {0 * BLOCK_W, j * BLOCK_W, BLOCK_W, BLOCK_W};
        SDL_BlitSurface(from_surf, bounds, screenSurface, &to_rect);
        to_rect = {(bg_width + 1) * BLOCK_W, j * BLOCK_W, BLOCK_W, BLOCK_W};
        SDL_BlitSurface(from_surf, bounds, screenSurface, &to_rect);
    }
}

Displ::Event Displ::getEvent() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.key.state == SDL_RELEASED)
            continue;
        switch (e.key.keysym.sym) {
        case SDLK_UP:
            return UP;
        case SDLK_DOWN:
            return DOWN;
        case SDLK_LEFT:
            return LEFT;
        case SDLK_RIGHT:
            return RIGHT;
        case SDLK_q:
            if (e.key.keysym.mod & KMOD_CTRL)
                return QUIT;
            break;
        }
        if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
            return QUIT;
        }
    }
    return NONE;
}

void Displ::update() {
    SDL_UpdateWindowSurface(window);
    SDL_Delay(16);
}

pair<int, int> Displ::getPx(int x, int y) {
    return make_pair(x * BLOCK_W, y * BLOCK_W);
}

void SpriteSheet::setColor(uint8_t r, uint8_t b, uint8_t g) {
    SDL_SetSurfaceColorMod(spriteSurf, r, g, b);
}

SpriteSheet::SpriteSheet(const char *path, int num_sprites, int sprite_w,
                         int sprite_h, int gap_w) {
    spriteSurf = SDL_LoadBMP(path);
    if (spriteSurf == NULL) {
        printf("Unable to load sprites: %s\n", SDL_GetError());
        throw("SDL Load failure.");
    }

    int stride = sprite_w + gap_w;
    for (int i = 0; i < num_sprites; i++)
        sprites[i] = {gap_w / 2 + stride * i, gap_w / 2, sprite_w, sprite_h};
}
