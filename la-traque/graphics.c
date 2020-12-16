#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <windows.h>

#define WINDOW_RATIO 0.5

typedef struct renderer{
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
}renderer;

typedef struct rendererObject{
    SDL_Surface *pSurface;
    SDL_Texture *pTexture;
}rendererObject;

