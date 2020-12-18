#include "structures.c"
#include "titles.c"

// PROTOTYPES
void PrintScreen(struct tile[XMAX][YMAX], struct pisteur[CREW], struct monstre, struct renderer);
void PrintField(struct renderer sRenderer);
void PrintBackground(struct renderer sRenderer);
void PrintCrew(struct pisteur[CREW], struct renderer);
void PrintCrewInfo(struct pisteur[CREW]);
void PrintMonstre(struct monstre);

// Debug crew
void PrintCrewInfo(struct pisteur crew[CREW]){
    for (int i = 0; i < CREW; i++){
        gotoxy(XMAX + 5, i + 1);
        printf("P%d : %d | %d", i, crew[i].x, crew[i].y);
    }
}

// Print the field
void PrintField(struct renderer sRenderer){
    SDL_Rect slot = {OFFSETX, SLOTSPACE, SLOTWIDTH, SLOTWIDTH};
    rendererObject slotRender;
    slotRender.pSurface = IMG_Load("./assets/misc/square.png");
    slotRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, slotRender.pSurface);
    SDL_FreeSurface(slotRender.pSurface);

    for (int y = 0; y < YMAX; y++){
        for (int x = 0; x < XMAX; x++){
                // Set sprite position
                slot.x = OFFSETX * 2 + x * (SLOTWIDTH + SLOTSPACE);
                slot.y = SLOTSPACE * 2 + y * (SLOTWIDTH + SLOTSPACE);
                // Draw textures
                SDL_RenderCopy(sRenderer.pRenderer, slotRender.pTexture, NULL, &slot);
        }
    }

    SDL_DestroyTexture(slotRender.pTexture);
}

// Print the background
void PrintBackground(struct renderer sRenderer){
    SDL_Rect backgroundRect = {0, 0, GetSystemMetrics(SM_CXSCREEN) * WINDOW_RATIO, GetSystemMetrics(SM_CYSCREEN) * WINDOW_RATIO};
    rendererObject backgroundRender;
    backgroundRender.pSurface = IMG_Load("./assets/background/gameTitle.png");
    backgroundRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, backgroundRender.pSurface);
    SDL_FreeSurface(backgroundRender.pSurface);
    SDL_RenderCopy(sRenderer.pRenderer, backgroundRender.pTexture, NULL, &backgroundRect);
    SDL_DestroyTexture(backgroundRender.pTexture);
}

// Print the field and crew members
void PrintCrew(struct pisteur crew[CREW], struct renderer sRenderer){
    // Create sprite
    SDL_Rect crewSprite = {OFFSETX, SLOTSPACE, SLOTWIDTH, SLOTWIDTH};
    // Create objects renderer
    rendererObject crewRender;
    rendererObject exclamRender;
    rendererObject interoRender;
    // Load images
    crewRender.pSurface = IMG_Load("./assets/misc/crew.png");
    exclamRender.pSurface = IMG_Load("./assets/misc/exclam.png");
    interoRender.pSurface = IMG_Load("./assets/misc/intero.png");
    // Debug loading
    if (!crewRender.pSurface)
        printf("crew.png --- LOAD ERROR !\n");
    if (!exclamRender.pSurface)
        printf("exclam.png --- LOAD ERROR !\n");
    if (!interoRender.pSurface)
        printf("intero.png --- LOAD ERROR !\n");
    // Create textures
    crewRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, crewRender.pSurface);
    exclamRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, exclamRender.pSurface);
    interoRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, interoRender.pSurface);
    // Free surfaces
    SDL_FreeSurface(crewRender.pSurface);
    SDL_FreeSurface(exclamRender.pSurface);
    SDL_FreeSurface(interoRender.pSurface);

    for (int i = 0; i < CREW; i++){
        // Set sprite position
        crewSprite.x = OFFSETX * 2 + crew[i].x * (SLOTWIDTH + SLOTSPACE);
        crewSprite.y = SLOTSPACE * 2 + crew[i].y * (SLOTWIDTH + SLOTSPACE);
        if (crew[i].icone == 'P')
            SDL_RenderCopy(sRenderer.pRenderer, crewRender.pTexture, NULL, &crewSprite);
        if (crew[i].icone == '!')
            SDL_RenderCopy(sRenderer.pRenderer, exclamRender.pTexture, NULL, &crewSprite);
        if (crew[i].icone == '?')
            SDL_RenderCopy(sRenderer.pRenderer, interoRender.pTexture, NULL, &crewSprite);
    }

    SDL_DestroyTexture(crewRender.pTexture);
    SDL_DestroyTexture(exclamRender.pTexture);
    SDL_DestroyTexture(interoRender.pTexture);
}

// Print screen
void PrintScreen(struct tile field[XMAX][YMAX], struct pisteur crew[CREW], struct monstre monk, struct renderer sRenderer){
    // Clear renderer
    SDL_RenderClear(sRenderer.pRenderer);
    PrintCrew(crew, sRenderer);
    // PrintCrewInfo(crew);
    // PrintMonstre(monk);

    // Render
    SDL_RenderPresent(sRenderer.pRenderer);
}

// Debug monster
void PrintMonstre(struct monstre monk){
    gotoxy(XMAX + 5, 16);
    printf("M : %d | %d | %d", monk.x, monk.y, monk.lifes);
}
