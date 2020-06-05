#include <iostream>
#include "block.h"
#include "gameboard.h"

using namespace std;
#include <iostream>
#include <SDL2/SDL.h>

const int RES_W = 640;
const int RES_H = 480;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init() {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf("SDL failed to initialize: %s\n", SDL_GetError());
        return false;
    }
    gWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        RES_W, RES_H, SDL_WINDOW_SHOWN);
    if ( gWindow == NULL ) {
        printf("Window could not be created: %s\n", SDL_GetError());
        return false;
    }
    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true;
}

        
bool loadMedia() {
    gHelloWorld = SDL_LoadBMP("spritesheet.bmp");
    if ( gHelloWorld == NULL ) {
        printf( "Unable to load sprites: %s\n", SDL_GetError() );
        return false;
    }
    return true;
}



int main() {
    init();
    loadMedia();
    SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
    SDL_UpdateWindowSurface( gWindow );
    SDL_Delay( 2000 );
    return 0;
}
