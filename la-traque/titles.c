#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "graphics.c"

// PROTOTYPE
// Title
void MenuTitle(int*, struct renderer);
void MenuVictory(int*);
void MenuDefeat(int*);
void PrintKeyInfo(SDL_KeyboardEvent *key);
void ToggleArrow(int*, SDL_Rect*);
void Validation(int, int*);

// Menu title
void MenuTitle(int* g, struct renderer sRenderer){
    SDL_Event event;
    char answer;
    int choice = 0;

    // Create sprites
    SDL_Rect background = {0, 0, GetSystemMetrics(SM_CXSCREEN) * WINDOW_RATIO, GetSystemMetrics(SM_CYSCREEN) * WINDOW_RATIO};
    SDL_Rect arrow = {500, 195, 40, 40};
    // Create objects renderer
    rendererObject menuTitle;
    rendererObject leftArrow;
    // Load images
    menuTitle.pSurface = IMG_Load("./assets/background/menuTitle.png");
    leftArrow.pSurface = IMG_Load("./assets/misc/leftArrow.png");
    // Debug loading
    if (!menuTitle.pSurface)
        printf("menuTitle.png --- LOAD ERROR !\n");
    if (!leftArrow.pSurface)
        printf("leftArrow.png --- LOAD ERROR !\n");
    // Create textures
    menuTitle.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, menuTitle.pSurface);
    leftArrow.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, leftArrow.pSurface);
    // Free surfaces
    SDL_FreeSurface(menuTitle.pSurface);
    SDL_FreeSurface(leftArrow.pSurface);

    system("cls");

    printf("   ### LA TRAQUE ###\n");
    printf("\nMonk-C s'est echappe. Il rode dans la region.\nVous etes le responsable d'un groupe de pisteurs.\nCeux-ci vous informent des traces qu'ils decouvrent : ou et surtout depuis quand le monstre est passe par la.\nMais attention, Monk-C est intelligent, et si vous n'y prenez garde, il aneantira vos pisteurs un a un.\n");

    printf("\nVoulez-vous jouer ? [Y/N]\n");

    while (*g == 0){
        while (SDL_PollEvent(&event)){
            fflush(stdin);
            if (event.type == SDL_KEYDOWN)
                switch (event.key.keysym.sym){
                    case SDLK_RETURN: Validation(choice, g); break;
                    case SDLK_SPACE: Validation(choice, g); break;
                    case SDLK_ESCAPE: *g = -1; break;
                    case SDLK_UP: ToggleArrow(&choice, &arrow); break;
                    case SDLK_DOWN: ToggleArrow(&choice, &arrow); break;
                    case SDL_QUIT: *g = -1; break;
                    default : break;
                }
            if (event.type == SDL_QUIT)
                *g = -1;
            // Draw textures
            SDL_RenderCopy(sRenderer.pRenderer, menuTitle.pTexture, NULL, &background);
            SDL_RenderCopy(sRenderer.pRenderer, leftArrow.pTexture, NULL, &arrow);
            // Render
            SDL_RenderPresent(sRenderer.pRenderer);
        }
    }
}



// Menu victory
void MenuVictory(int* g){
    system("cls");

    printf("   ### LA TRAQUE ###\n");
    printf("\nFELICITATIONs ! Vous avez abattu le monstre qui rodait dans ces bois.\n");

    *g = 0;

    fflush(stdin);
    getchar();
}

// Menu defeat
void MenuDefeat(int* g){
    system("cls");

    printf("   ### LA TRAQUE ###\n");
    printf("\nQUEL DRAME ! Tous vos pisteurs sont mort...\n");

    *g = 0;

    fflush(stdin);
    getchar();
}

// Validate menu proposition
void Validation(int choice, int* g){
    if (!choice)
        *g = 1;
    else
        *g = -1;
}

// Navigate belong menu propositions
void ToggleArrow(int* choice, SDL_Rect* arrow){
    if (*choice == 0){
        *choice = 1;
        arrow->y = 250;
    }else{
        *choice = 0;
        arrow->y = 195;
    }
}
