#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"
#include "titles.c"

int main(int argc, char *argv[])
{
    struct tile field[XMAX][YMAX];
    struct pisteur crew[CREW];
    struct monstre monk;
    struct renderer sRenderer;

    // Init program
    SDL_Event event;
    sRenderer.pWindow = NULL;
    sRenderer.pRenderer = NULL;
    int gameState = 0;

    // Init renderer

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
        return 1; // return error
    }else{
        // Draw screen
        SDL_Point wSize = {GetSystemMetrics(SM_CXSCREEN) * WINDOW_RATIO, GetSystemMetrics(SM_CYSCREEN) * WINDOW_RATIO};
        SDL_Point wPos = {(GetSystemMetrics(SM_CXSCREEN) / 2) - (wSize.x / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (wSize.y / 2)}; // center window on the screen
        sRenderer.pWindow = SDL_CreateWindow("La Traque", wPos.x, wPos.y, wSize.x, wSize.y, SDL_WINDOW_SHOWN);

        // Init renderer
        if (sRenderer.pWindow){
            sRenderer.pRenderer = SDL_CreateRenderer(sRenderer.pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
        }

        // Init SDL_image
        int flags = IMG_INIT_JPG|IMG_INIT_PNG;
        int initted = IMG_Init(flags);
        if ((initted & flags) != flags){
            SDL_Log("IMG_Init : Failed to init required .jpg and .png support !\n");
            SDL_Log("IMG_Init : %s\n", IMG_GetError());
        }

        while (gameState != -1){
            switch (gameState){
            case 0:
                // Menu
                MenuTitle(&gameState, sRenderer);
                /* while (SDL_PollEvent(&event)){
                    switch (event.type){
                        case SDL_KEYDOWN: printf("%s", SDL_GetKeyName(event.key.keysym.sym)); break;
                        case SDL_KEYUP: printf("--"); break;
                        case SDL_QUIT: gameState = -1;
                        default : break;
                    }
                } */
                break;
            case 1:
                // Init
                Init(field, crew, &monk, &gameState);
                break;
            case 2:
                // Game
                Round(field, crew, &monk, &gameState);
                break;
            case 3:
                // Victory
                MenuVictory(&gameState);
                break;
            case 4:
                // Defeat
                MenuDefeat(&gameState);
                break;
            default :
                gameState = -1;
            }
        }
    }

    SDL_Quit();

    system("cls");
    printf("Au revoir.\n");
    return 0;
}
