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
    SDL_Rect to_rect = { x_idx * BLOCK_W, y_idx * BLOCK_W, BLOCK_W, BLOCK_W };
    SDL_BlitSurface(from_surf, bounds, screenSurface, &to_rect);
}

bool Display::update() {
    SDL_UpdateWindowSurface( window );
    SDL_Event e;
    while ( SDL_PollEvent( &e ) != 0 ) {
        if ( e.key.keysym.sym == SDLK_q ) return false;
    }
    SDL_Delay( 16 );
    return true;
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

