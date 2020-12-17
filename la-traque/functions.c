#include <time.h>
#include <windows.h>
#include "prints.c"

// PROTOTYPES
void Init(struct tile[XMAX][YMAX], struct pisteur[CREW], struct monstre*, int*, struct renderer);
void Round(struct tile[XMAX][YMAX], struct pisteur[CREW], struct monstre*, int*, struct renderer);
void InitMonstre(struct monstre*, struct pisteur[CREW]);
void Footprint(struct tile[XMAX][YMAX], struct pisteur[CREW], struct monstre);
void Detection(struct tile[XMAX][YMAX], struct pisteur, struct monstre*, struct renderer);
void PisteurMovement(struct tile[XMAX][YMAX], struct pisteur*);
void MonstreMovement(struct tile[XMAX][YMAX], struct monstre*);
void IntToString(int, char[2]);

// Initialization (SDL OK)
void Init(struct tile field[XMAX][YMAX], struct pisteur crew[CREW], struct monstre* monk, int* g, struct renderer sRenderer){
    // Font load
    TTF_Font* textFont = TTF_OpenFont("./assets/font/textFont.ttf", 24);
    if (!textFont)
        printf("textFont.ttf --- LOAD ERROR !\n");
    SDL_Color Black = {0, 0, 0};

    // Variables
    SDL_Event event;
    int nChoice = 0;
    int initState = 0;
    int nPisteur = 1;
    int hor = 0;
    int ver = 0;

    // SDL
    SDL_Rect textRect = {GetSystemMetrics(SM_CXSCREEN) * .5 - 1000 * WINDOW_RATIO, 100 * WINDOW_RATIO, 1000 * WINDOW_RATIO, 75 * WINDOW_RATIO};
    SDL_Rect instructionRect = {GetSystemMetrics(SM_CXSCREEN) * .5 - 1000 * WINDOW_RATIO, 700 * WINDOW_RATIO, 1000 * WINDOW_RATIO, 50 * WINDOW_RATIO};
    SDL_Rect numberRect = {GetSystemMetrics(SM_CXSCREEN) * .5 - 595 * WINDOW_RATIO, 350 * WINDOW_RATIO, 200 * WINDOW_RATIO, 200 * WINDOW_RATIO};
    SDL_Rect leftRect = {GetSystemMetrics(SM_CXSCREEN) * .5 - 700 * WINDOW_RATIO, 415 * WINDOW_RATIO, 80 * WINDOW_RATIO, 80 * WINDOW_RATIO};
    SDL_Rect rightRect = {GetSystemMetrics(SM_CXSCREEN) * .5 - 400 * WINDOW_RATIO, 415 * WINDOW_RATIO, 80 * WINDOW_RATIO, 80 * WINDOW_RATIO};
    // SDL_Rect cursorRect = {OFFSETX * 2 + hor * (SLOTWIDTH + SLOTSPACE), SLOTSPACE * 2 + ver * (SLOTWIDTH + SLOTSPACE), SLOTWIDTH, SLOTWIDTH};

    rendererObject textRender;
    rendererObject instructionRender;
    rendererObject numberRender;
    rendererObject leftRender;
    rendererObject rightRender;
    rendererObject cursorRender;

    textRender.pSurface = TTF_RenderText_Solid(textFont, "Nombre de pisteurs", Black);
    instructionRender.pSurface = TTF_RenderText_Solid(textFont, "Positionnez vos pisteurs", Black);
    numberRender.pSurface = TTF_RenderText_Solid(textFont, "1", Black);
    leftRender.pSurface = IMG_Load("./assets/misc/leftArrow.png");
    rightRender.pSurface = IMG_Load("./assets/misc/rightArrow.png");
    cursorRender.pSurface = IMG_Load("./assets/misc/cursor.png");

    textRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, textRender.pSurface);
    instructionRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, instructionRender.pSurface);
    numberRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, numberRender.pSurface);
    leftRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, leftRender.pSurface);
    rightRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, rightRender.pSurface);
    cursorRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, cursorRender.pSurface);

    SDL_FreeSurface(textRender.pSurface);
    SDL_FreeSurface(instructionRender.pSurface);
    SDL_FreeSurface(leftRender.pSurface);
    SDL_FreeSurface(rightRender.pSurface);

    // Print Screen
    PrintBackground(sRenderer);

    // Init field
    for (int y = 0; y < YMAX; y++)
        for (int x = 0; x < XMAX; x++){
            field[x][y].traceMonstre = 0;
            field[x][y].tracePisteur = 0;
        }

    while (initState != -1){
        switch (initState){
            case 0: /*crew number member*/
                while (SDL_PollEvent(&event)){
                    fflush(stdin);
                    if (event.type == SDL_KEYDOWN)
                        switch (event.key.keysym.sym){
                            case SDLK_RETURN: /*valid choice*/ initState = 1; break;
                            case SDLK_SPACE: /*valid choice*/ initState = 1; break;
                            case SDLK_KP_ENTER: /*valid choice*/ initState = 1; break;
                            case SDLK_LEFT: /*choice left*/
                                if (nPisteur == 1)
                                    nPisteur = 10;
                                else
                                    nPisteur--;
                                switch (nPisteur){
                                    case 1: numberRender.pSurface = TTF_RenderText_Solid(textFont, "1", Black); break;
                                    case 2: numberRender.pSurface = TTF_RenderText_Solid(textFont, "2", Black); break;
                                    case 3: numberRender.pSurface = TTF_RenderText_Solid(textFont, "3", Black); break;
                                    case 4: numberRender.pSurface = TTF_RenderText_Solid(textFont, "4", Black); break;
                                    case 5: numberRender.pSurface = TTF_RenderText_Solid(textFont, "5", Black); break;
                                    case 6: numberRender.pSurface = TTF_RenderText_Solid(textFont, "6", Black); break;
                                    case 7: numberRender.pSurface = TTF_RenderText_Solid(textFont, "7", Black); break;
                                    case 8: numberRender.pSurface = TTF_RenderText_Solid(textFont, "8", Black); break;
                                    case 9: numberRender.pSurface = TTF_RenderText_Solid(textFont, "9", Black); break;
                                    case 10: numberRender.pSurface = TTF_RenderText_Solid(textFont, "10", Black); break;
                                    default : break;
                                }
                                break;
                            case SDLK_RIGHT: /*choice right*/
                                if (nPisteur == 10)
                                    nPisteur = 1;
                                else
                                    nPisteur++;
                                switch (nPisteur){
                                    case 1: numberRender.pSurface = TTF_RenderText_Solid(textFont, "1", Black); break;
                                    case 2: numberRender.pSurface = TTF_RenderText_Solid(textFont, "2", Black); break;
                                    case 3: numberRender.pSurface = TTF_RenderText_Solid(textFont, "3", Black); break;
                                    case 4: numberRender.pSurface = TTF_RenderText_Solid(textFont, "4", Black); break;
                                    case 5: numberRender.pSurface = TTF_RenderText_Solid(textFont, "5", Black); break;
                                    case 6: numberRender.pSurface = TTF_RenderText_Solid(textFont, "6", Black); break;
                                    case 7: numberRender.pSurface = TTF_RenderText_Solid(textFont, "7", Black); break;
                                    case 8: numberRender.pSurface = TTF_RenderText_Solid(textFont, "8", Black); break;
                                    case 9: numberRender.pSurface = TTF_RenderText_Solid(textFont, "9", Black); break;
                                    case 10: numberRender.pSurface = TTF_RenderText_Solid(textFont, "10", Black); break;
                                    default : break;
                                }
                                break;
                            default : break;
                        }
                    if (event.type == SDL_QUIT){
                        initState = -1;
                        *g = -1;
                    }
                }
                numberRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, numberRender.pSurface);
                SDL_RenderClear(sRenderer.pRenderer);
                PrintBackground(sRenderer);
                SDL_RenderCopy(sRenderer.pRenderer, textRender.pTexture, NULL, &textRect);
                SDL_RenderCopy(sRenderer.pRenderer, numberRender.pTexture, NULL, &numberRect);
                SDL_RenderCopy(sRenderer.pRenderer, leftRender.pTexture, NULL, &leftRect);
                SDL_RenderCopy(sRenderer.pRenderer, rightRender.pTexture, NULL, &rightRect);
                SDL_RenderPresent(sRenderer.pRenderer);
                for (int i = 0; i < CREW; i++){
                    if (i < nPisteur)
                        crew[i].icone = 'P';
                    else
                        crew[i].icone = '.';
                    crew[i].x = -10;
                    crew[i].y = -10;
                }
                break;
            case 1: /*crew members position*/
                while (SDL_PollEvent(&event)){
                    fflush(stdin);
                    if (event.type == SDL_KEYDOWN)
                        switch (event.key.keysym.sym){
                            case SDLK_RETURN: /*valid choice*/
                                if (nChoice < nPisteur){
                                    crew[nChoice].x = hor;
                                    crew[nChoice].y = ver;
                                    crew[nChoice].icone = 'P';
                                    nChoice++;
                                }
                                if (nChoice >= nPisteur)
                                    initState = 2;
                                break;
                            case SDLK_SPACE: /*valid choice*/
                                if (nChoice < nPisteur){
                                    crew[nChoice].x = hor;
                                    crew[nChoice].y = ver;
                                    crew[nChoice].icone = 'P';
                                    nChoice++;
                                }
                                if (nChoice >= nPisteur)
                                    initState = 2;
                                break;
                            case SDLK_KP_ENTER: /*valid choice*/
                                if (nChoice < nPisteur){
                                    crew[nChoice].x = hor;
                                    crew[nChoice].y = ver;
                                    crew[nChoice].icone = 'P';
                                    nChoice++;
                                }
                                if (nChoice >= nPisteur)
                                    initState = 2;
                                break;
                            case SDLK_UP: /*choice up*/
                                if (ver > 0)
                                    ver--;
                                break;
                            case SDLK_DOWN: /*choice down*/
                                if (ver < YMAX - 1)
                                    ver++;
                                break;
                            case SDLK_LEFT: /*choice left*/
                                if (hor > 0)
                                    hor--;
                                break;
                            case SDLK_RIGHT: /*choice right*/
                                if (hor < XMAX - 1)
                                    hor++;
                                break;
                            default : break;
                        }
                    if (event.type == SDL_QUIT){
                        initState = -1;
                        *g = -1;
                    }
                }
                SDL_Rect cursorRect = {OFFSETX * 2 + hor * (SLOTWIDTH + SLOTSPACE), SLOTSPACE * 2 + ver * (SLOTWIDTH + SLOTSPACE), SLOTWIDTH, SLOTWIDTH};
                SDL_RenderClear(sRenderer.pRenderer);
                PrintBackground(sRenderer);
                SDL_RenderCopy(sRenderer.pRenderer, instructionRender.pTexture, NULL, &instructionRect);
                PrintField(field, sRenderer);
                PrintCrew(crew, sRenderer);
                SDL_RenderCopy(sRenderer.pRenderer, cursorRender.pTexture, NULL, &cursorRect);
                SDL_RenderPresent(sRenderer.pRenderer);
                break;
            case 2: /*monster position*/
                InitMonstre(monk, crew);
                initState = -1;
                *g = 2;
                break;
        }
    }
    SDL_FreeSurface(numberRender.pSurface);
    SDL_FreeSurface(cursorRender.pSurface);

    // PrintCrewInfo(crew);
}

// Round
void Round(struct tile field[XMAX][YMAX], struct pisteur crew[CREW], struct monstre* monk, int* g, struct renderer sRenderer){
    // Font load
    TTF_Font* textFont = TTF_OpenFont("./assets/font/textFont.ttf", 24);
    if (!textFont)
        printf("textFont.ttf --- LOAD ERROR !\n");
    SDL_Color Black = {0, 0, 0};
    SDL_Color Red = {255, 0, 0};
    SDL_Color Green = {0, 255, 0};

    // Variables
    SDL_Event event;
    char s[2];
    int nPisteur = 0;
    int isCrewDead = 1;
    int roundState = 0;
    IntToString(nPisteur + 1, s);

    // SDL
    SDL_Rect titleRect = {GetSystemMetrics(SM_CXSCREEN) * .5 - 1200 * WINDOW_RATIO, 700 * WINDOW_RATIO, 350 * WINDOW_RATIO, 50 * WINDOW_RATIO};
    SDL_Rect numberRect = {GetSystemMetrics(SM_CXSCREEN) * .5 - 800 * WINDOW_RATIO, 700 * WINDOW_RATIO, 75 * WINDOW_RATIO, 50 * WINDOW_RATIO};
    SDL_Rect stateRect = {GetSystemMetrics(SM_CXSCREEN) * .5 - 1150 * WINDOW_RATIO, 750 * WINDOW_RATIO, 300 * WINDOW_RATIO, 50 * WINDOW_RATIO};
    SDL_Rect leftRect = {GetSystemMetrics(SM_CXSCREEN) * .5 - 830 * WINDOW_RATIO, 715 * WINDOW_RATIO, 25 * WINDOW_RATIO, 25 * WINDOW_RATIO};
    SDL_Rect rightRect = {GetSystemMetrics(SM_CXSCREEN) * .5 - 730 * WINDOW_RATIO, 715 * WINDOW_RATIO, 25 * WINDOW_RATIO, 25 * WINDOW_RATIO};

    rendererObject titleRender;
    rendererObject numberRender;
    rendererObject stateRender;
    rendererObject leftRender;
    rendererObject rightRender;

    titleRender.pSurface = TTF_RenderText_Solid(textFont, "Pisteur", Black);
    numberRender.pSurface = TTF_RenderText_Solid(textFont, s, Black);
    stateRender.pSurface = TTF_RenderText_Solid(textFont, "Actif", Green);
    leftRender.pSurface = IMG_Load("./assets/misc/leftArrow.png");
    rightRender.pSurface = IMG_Load("./assets/misc/rightArrow.png");

    titleRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, titleRender.pSurface);
    leftRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, leftRender.pSurface);
    rightRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, rightRender.pSurface);

    SDL_FreeSurface(titleRender.pSurface);
    SDL_FreeSurface(leftRender.pSurface);
    SDL_FreeSurface(rightRender.pSurface);

    // If defeated
    for (int i = 0; i < CREW; i++)
        if (crew[i].icone == 'P')
            isCrewDead = 0;
    if (isCrewDead){
        roundState = -1;
        *g = 4; // DEFEAT
    }

    // PHASE 0
    //   Footprints
    Footprint(field, crew, *monk);

    while (roundState != -1){
        switch (roundState){
            case 0: /* DETECTION */
                while (SDL_PollEvent(&event)){
                    fflush(stdin);
                    if (event.type == SDL_KEYDOWN)
                        switch (event.key.keysym.sym){
                            case SDLK_RETURN: /*valid choice*/ break;
                            case SDLK_SPACE: /*valid choice*/ break;
                            case SDLK_KP_ENTER: /*valid choice*/ break;
                            case SDLK_LEFT: /*choice left*/
                                if (nPisteur > 0)
                                    nPisteur--;
                                else
                                    nPisteur = CREW - 1;
                                IntToString(nPisteur + 1, s);
                                break;
                            case SDLK_RIGHT: /*choice right*/
                                if (nPisteur < CREW - 1)
                                    nPisteur++;
                                else
                                    nPisteur = 0;
                                IntToString(nPisteur + 1, s);
                                break;
                            default : break;
                        }
                    if (event.type == SDL_QUIT){
                        roundState = -1;
                        *g = -1;
                    }
                }
                for (int i = 0; i < CREW; i++)
                    if (crew[i].icone != '.')
                        crew[i].icone = 'P';
                if (crew[nPisteur].icone == 'P'){
                    crew[nPisteur].icone = '!';
                    stateRender.pSurface = TTF_RenderText_Solid(textFont, "Actif", Green);
                }else
                    stateRender.pSurface = TTF_RenderText_Solid(textFont, "Inactif", Red);
                numberRender.pSurface = TTF_RenderText_Solid(textFont, s, Black);

                numberRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, numberRender.pSurface);
                stateRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, stateRender.pSurface);
                // Draw
                SDL_RenderClear(sRenderer.pRenderer);
                PrintBackground(sRenderer);
                PrintField(field, sRenderer);
                PrintCrew(crew, sRenderer);
                SDL_RenderCopy(sRenderer.pRenderer, titleRender.pTexture, NULL, &titleRect);
                SDL_RenderCopy(sRenderer.pRenderer, numberRender.pTexture, NULL, &numberRect);
                SDL_RenderCopy(sRenderer.pRenderer, stateRender.pTexture, NULL, &stateRect);
                SDL_RenderCopy(sRenderer.pRenderer, leftRender.pTexture, NULL, &leftRect);
                SDL_RenderCopy(sRenderer.pRenderer, rightRender.pTexture, NULL, &rightRect);
                // Detection
                // Detection(field, crew[nPisteur], monk, sRenderer);

                SDL_RenderPresent(sRenderer.pRenderer);
            break;
        }
    }

    SDL_FreeSurface(numberRender.pSurface);
    SDL_FreeSurface(stateRender.pSurface);

    if (isCrewDead){
        *g = 4; // DEFEAT
    }else{
        // PHASE I
        //   Pisteur detection
        for (int i = 0; i < CREW; i++){
            if (crew[i].icone == 'P'){
                crew[i].icone = '!'; // Set icone
                PrintScreen(field, crew, *monk, sRenderer);
                gotoxy(XMAX + 5, YMAX / 2);
                printf("Rapport du pisteur %d :\n", i + 1);
                Detection(field, crew[i], monk, sRenderer);
                crew[i].icone = 'P'; // Reset icone
            }
        }
        if (monk->lifes < 1){
            *g = 3; // VICTORY
        }else{
            // PHASE II
            //   Pisteur movement
            for (int i = 0; i < CREW; i++)
                if (crew[i].icone == 'P'){
                    crew[i].icone = '?'; // Set icone
                    PrintScreen(field, crew, *monk, sRenderer);
                    gotoxy(XMAX + 5, YMAX / 2);
                    printf("Deplacement du pisteur %d :\n", i + 1);
                    PisteurMovement(field, &crew[i]);
                    crew[i].icone = 'P'; // Reset icone
                }
            // PHASE III
            //   Monk movement & Pisteur death
            MonstreMovement(field, &(*monk));
            for (int i = 0; i < CREW; i++){
                if (crew[i].x == monk->x && crew[i].y == monk->y)
                    crew[i].icone = '.';
            }
        }
    }
}

// Monstre movement
void MonstreMovement(struct tile field[XMAX][YMAX], struct monstre* monk){
    int pMax = 0;
    int dir;
    int mX = monk->x;
    int mY = monk->y;

    if (mX > 0)
        if (field[mX-1][mY].tracePisteur > pMax){
            pMax = field[mX-1][mY].tracePisteur;
            dir = 0;
        }
    if (mX < XMAX - 1)
        if (field[mX+1][mY].tracePisteur > pMax){
            pMax = field[mX+1][mY].tracePisteur;
            dir = 1;
        }
    if (mY > 0)
        if (field[mX][mY-1].tracePisteur > pMax){
            pMax = field[mX][mY-1].tracePisteur;
            dir = 2;
        }
    if (mY < YMAX - 1)
        if (field[mX][mY+1].tracePisteur > pMax){
            pMax = field[mX][mY+1].tracePisteur;
            dir = 3;
        }

    if (pMax == 0){
        srand(GetTickCount());
        dir = rand() % 4; // 0 - 3
    }

    switch (dir){
        case 0:
            (monk->x)--;
            break;
        case 1:
            (monk->x)++;
            break;
        case 2:
            (monk->y)--;
            break;
        case 3:
            (monk->y)++;
            break;
        default:
            break;
    }
}


// Pisteur movement
void PisteurMovement(struct tile field[XMAX][YMAX], struct pisteur* p){
    char dir = 'x';
    int dist = -1;

    // GET MOVEMENT INFOS
    gotoxy(XMAX + 8, (YMAX / 2) + 2);
    printf("Le pisteur attend vos ordres...");
    gotoxy(XMAX + 8, (YMAX / 2) + 4);
    printf("Deplacement haut, bas, gauche ou droite ? [H/B/G/D]");
    while (dir != 'h' && dir != 'H' && dir != 'b' && dir != 'B' && dir != 'g' && dir != 'G' && dir != 'd' && dir != 'D'){
        gotoxy(XMAX + 8, (YMAX / 2) + 5);
        scanf("%c", &dir);
    }
    gotoxy(XMAX + 8, (YMAX / 2) + 6);
    printf("De combien doit-il se deplacer ? [0-4]");
    while (dist < 0 || dist > 4){
        gotoxy(XMAX + 8, (YMAX / 2) + 7);
        scanf("%d", &dist);
    }

    // MOVE
    if (dist > 0){
        switch (toupper(dir)){
        case 'H':
            if (p->y > dist)
                p->y -= dist;
            else
                p->y = 0;
            break;
        case 'B':
            if (p->y < YMAX - dist)
                p->y += dist;
            else
                p->y = YMAX - 1;
            break;
        case 'G':
            if (p->x > dist)
                p->x -= dist;
            else
                p->x = 0;
            break;
        case 'D':
            if (p->x < XMAX - dist)
                p->x += dist;
            else
                p->x = XMAX - 1;
            break;
        default : break;
        }
    }
}

// Pisteur detection
void Detection(struct tile field[XMAX][YMAX], struct pisteur p, struct monstre* monk, struct renderer sRenderer){
    int view[8];
    for (int i = 0; i < 8; i++)
        view[i] = 0;

    // a
    if (p.x > 0 && p.y > 0)
        view[0] = field[p.x-1][p.y-1].traceMonstre;
    // b
    if (p.y > 0)
        view[1] = field[p.x][p.y-1].traceMonstre;
    // c
    if (p.x < XMAX-1 && p.y > 0)
        view[2] = field[p.x+1][p.y-1].traceMonstre;
    // d
    if (p.x > 0)
        view[3] = field[p.x-1][p.y].traceMonstre;
    // e
    if (p.x < XMAX-1)
        view[4] = field[p.x+1][p.y].traceMonstre;
    // f
    if (p.x > 0 && p.y < YMAX-1)
        view[5] = field[p.x-1][p.y+1].traceMonstre;
    // g
    if (p.y < YMAX-1)
        view[6] = field[p.x][p.y+1].traceMonstre;
    // h
    if (p.x < XMAX-1 && p.y < YMAX-1)
        view[7] = field[p.x+1][p.y+1].traceMonstre;


    // PRINT RESULTS
    gotoxy(XMAX + 8, (YMAX / 2) + 2);
    printf("%c%c%c%c%c%c%c%c%c%c", 201, 205, 205, 203, 205, 205, 203, 205, 205, 187);
    gotoxy(XMAX + 8, (YMAX / 2) + 3);
    printf("%c  %c  %c  %c", 186, 186, 186, 186);
    gotoxy(XMAX + 8, (YMAX / 2) + 4);
    printf("%c%c%c%c%c%c%c%c%c%c", 204, 205, 205, 206, 205, 205, 206, 205, 205, 185);
    gotoxy(XMAX + 8, (YMAX / 2) + 5);
    printf("%c  %c  %c  %c", 186, 186, 186, 186);
    gotoxy(XMAX + 8, (YMAX / 2) + 6);
    printf("%c%c%c%c%c%c%c%c%c%c", 204, 205, 205, 206, 205, 205, 206, 205, 205, 185);
    gotoxy(XMAX + 8, (YMAX / 2) + 7);
    printf("%c  %c  %c  %c", 186, 186, 186, 186);
    gotoxy(XMAX + 8, (YMAX / 2) + 8);
    printf("%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 202, 205, 205, 202, 205, 205, 188);

    gotoxy(XMAX + 9, (YMAX / 2) + 3);
    printf("%d", view[0]);
    gotoxy(XMAX + 12, (YMAX / 2) + 3);
    printf("%d", view[1]);
    gotoxy(XMAX + 15, (YMAX / 2) + 3);
    printf("%d", view[2]);
    gotoxy(XMAX + 9, (YMAX / 2) + 5);
    printf("%d", view[3]);
    gotoxy(XMAX + 15, (YMAX / 2) + 5);
    printf("%d", view[4]);
    gotoxy(XMAX + 9, (YMAX / 2) + 7);
    printf("%d", view[5]);
    gotoxy(XMAX + 12, (YMAX / 2) + 7);
    printf("%d", view[6]);
    gotoxy(XMAX + 15, (YMAX / 2) + 7);
    printf("%d", view[7]);

    for (int i = 0; i < 8; i++)
        if (view[i] == 16){
            gotoxy(XMAX / 2, (YMAX / 2) + 0);
            printf("**********************");
            gotoxy(XMAX / 2, (YMAX / 2) + 1);
            printf("* JE LE VOIS ! FEU ! *");
            gotoxy(XMAX / 2, (YMAX / 2) + 2);
            printf("**********************");
            fflush(stdin);
            getchar();
            srand(GetTickCount());
            if ((rand() % 100) + 1 <= ACCURACY){
                monk->lifes--;
                gotoxy(XMAX / 2, (YMAX / 2) + 0);
                printf("**********************");
                gotoxy(XMAX / 2, (YMAX / 2) + 1);
                printf("*  JE L'AI TOUCHE !  *");
                gotoxy(XMAX / 2, (YMAX / 2) + 2);
                printf("**********************");
            }else{
                gotoxy(XMAX / 2, (YMAX / 2) + 0);
                printf("**********************");
                gotoxy(XMAX / 2, (YMAX / 2) + 1);
                printf("*   JE L'AI RATE !   *");
                gotoxy(XMAX / 2, (YMAX / 2) + 2);
                printf("**********************");
            }
        }

    fflush(stdin);
    getchar();
}

void Footprint(struct tile field[XMAX][YMAX], struct pisteur crew[CREW], struct monstre monk){
    for (int y = 0; y < YMAX; y ++)
        for (int x = 0; x < XMAX; x++){
            if (field[x][y].tracePisteur > 0)
                (field[x][y].tracePisteur)--;
            if (field[x][y].traceMonstre > 0)
                (field[x][y].traceMonstre)--;
        }

    for (int i = 0; i < CREW; i++)
        if (crew[i].icone == 'P')
            field[crew[i].x][crew[i].y].tracePisteur = 16;

    field[monk.x][monk.y].traceMonstre = 16;
    field[monk.x][monk.y].tracePisteur = 0;
}

// Initialize monster
void InitMonstre(struct monstre* monk, struct pisteur crew[CREW]){
    int isCorrect = 1;
    monk->lifes = MAXLIFE;

    srand(GetTickCount());
    // Set position X [0; XMAX-1]
    int x = rand() % XMAX;
    // Set position Y [0; YMAX-1]
    int y = rand() % YMAX;
    // Verify if there is no pisteur around
    for (int i = 0; i < CREW; i++){
        if (x-1 == crew[i].x){
            if (y-1 == crew[i].y) isCorrect = 0;
            if (y   == crew[i].y) isCorrect = 0;
            if (y+1 == crew[i].y) isCorrect = 0;
        }
        if (x   == crew[i].x){
            if (y-1 == crew[i].y) isCorrect = 0;
            if (y   == crew[i].y) isCorrect = 0;
            if (y+1 == crew[i].y) isCorrect = 0;
        }
        if (x+1 == crew[i].x){
            if (y-1 == crew[i].y) isCorrect = 0;
            if (y   == crew[i].y) isCorrect = 0;
            if (y+1 == crew[i].y) isCorrect = 0;
        }
    }

    if (isCorrect == 0){
        InitMonstre(monk, crew);
    }else{
        // printf("PLACED !");
        monk->x = x;
        monk->y = y;
    }
}

// Convert int to string
void IntToString(int n, char s[2]){
    const char digit[10] = {'0','1','2','3','4','5','6','7','8','9'};
    int dixaine = n / 10;
    int unite = n % 10;
    if (dixaine)
        s[0] = digit[dixaine];
    else
        s[0] = ' ';
    s[1] = digit[unite];
}
