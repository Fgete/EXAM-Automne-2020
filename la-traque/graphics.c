#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <windows.h>

#define WINDOW_RATIO .6
#define RESIZE .9
#define OFFSETX (1 - RESIZE) * (GetSystemMetrics(SM_CXSCREEN) * WINDOW_RATIO) * .25
#define SLOTSPACE ((GetSystemMetrics(SM_CXSCREEN) * WINDOW_RATIO) * RESIZE) / (XMAX) * .1
#define SLOTWIDTH ((GetSystemMetrics(SM_CXSCREEN) * WINDOW_RATIO) * RESIZE) / (XMAX) * .9

typedef struct renderer{
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
}renderer;

typedef struct rendererObject{
    SDL_Surface *pSurface;
    SDL_Texture *pTexture;
}rendererObject;

