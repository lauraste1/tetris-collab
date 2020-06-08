#include "display.hpp"

Display::Display() {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf("SDL failed to initialize: %s\n", SDL_GetError());
        throw("SDL init failure");
    }
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED,
          SDL_WINDOWPOS_UNDEFINED, RES_W, RES_H, SDL_WINDOW_SHOWN);
    if ( window == NULL ) {
        printf("Window could not be created: %s\n", SDL_GetError());
        throw("SDL window failure");
    }
    screenSurface = SDL_GetWindowSurface(window);
}

Display::~Display() {
    SDL_FreeSurface( screenSurface );
    SDL_DestroyWindow( window );
    SDL_Quit();
}

void Display::blit(SDL_Surface* from_surf, SDL_Rect* bounds, int x_idx, int y_idx) {
    SDL_Rect to_rect = { (1+x_idx) * BLOCK_W, (1+y_idx) * BLOCK_W, BLOCK_W, BLOCK_W };
    SDL_BlitSurface(from_surf, bounds, screenSurface, &to_rect);
}

void Display::clearCell(int x_idx, int y_idx) {
    SDL_Rect to_rect = { (1+x_idx) * BLOCK_W, (1+y_idx) * BLOCK_W, BLOCK_W, BLOCK_W };
    SDL_FillRect(screenSurface, &to_rect, 0);
}

void Display::draw_bg(SDL_Surface* from_surf, SDL_Rect* bounds) {
    SDL_Rect to_rect;
    for(int i=0;i<12;i++) {
        to_rect = { i * BLOCK_W, 0 * BLOCK_W, BLOCK_W, BLOCK_W };
        SDL_BlitSurface(from_surf, bounds, screenSurface, &to_rect);
        to_rect = { i * BLOCK_W, 22 * BLOCK_W, BLOCK_W, BLOCK_W };
        SDL_BlitSurface(from_surf, bounds, screenSurface, &to_rect);
    }
    for(int j=0;j<23;j++) {
        to_rect = { 0 * BLOCK_W, j * BLOCK_W, BLOCK_W, BLOCK_W };
        SDL_BlitSurface(from_surf, bounds, screenSurface, &to_rect);
        to_rect = { 11 * BLOCK_W, j * BLOCK_W, BLOCK_W, BLOCK_W };
        SDL_BlitSurface(from_surf, bounds, screenSurface, &to_rect);
    }
}

Display::Event Display::getEvent() {
    SDL_Event e;
    while ( SDL_PollEvent( &e ) != 0 ) {
        if ( e.key.state == SDL_RELEASED ) continue;
        switch ( e.key.keysym.sym ) {
          case SDLK_UP:
            return UP;
          case SDLK_DOWN:
            return DOWN;
          case SDLK_LEFT:
            return LEFT;
          case SDLK_RIGHT:
            return RIGHT;
          case SDLK_q:
            return QUIT;
          case SDLK_ESCAPE:
            return QUIT;
        }
    }
    return NONE;
}

void Display::update() {
    SDL_UpdateWindowSurface( window );
    SDL_Delay( 16 );
} 

SpriteSheet::SpriteSheet(const char *path) {
    spriteSurf = SDL_LoadBMP(path);

    if ( spriteSurf == NULL ) {
        printf( "Unable to load sprites: %s\n", SDL_GetError() );
        throw("SDL Load failure.");
    }

    int stride = SPRITE_W + GAP_W;
    for (int i=0;i<8;i++) 
        sprites[i] = { GAP_W / 2 + stride * i, GAP_W / 2, SPRITE_W, SPRITE_W};
}

