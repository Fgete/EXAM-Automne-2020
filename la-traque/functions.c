#include <time.h>
#include <windows.h>
#include "prints.c"

// PROTOTYPES
void Init(struct tile[XMAX][YMAX], struct pisteur[CREW], struct monstre*, int*, struct renderer);
void Round(struct tile[XMAX][YMAX], struct pisteur[CREW], struct monstre*, int*, struct renderer);
void InitMonstre(struct monstre*, struct pisteur[CREW]);
void Footprint(struct tile[XMAX][YMAX], struct pisteur[CREW], struct monstre);
void Detection(struct tile[XMAX][YMAX], struct pisteur, struct monstre*);
void PisteurMovement(struct tile[XMAX][YMAX], struct pisteur*);
void MonstreMovement(struct tile[XMAX][YMAX], struct monstre*);

// Initialization
void Init(struct tile field[XMAX][YMAX], struct pisteur crew[CREW], struct monstre* monk, int* g, struct renderer sRenderer){
    // Font load
    TTF_Font* textFont = TTF_OpenFont("./assets/font/textFont.ttf", 24);
    if (!textFont)
        printf("textFont.ttf --- LOAD ERROR !\n");
    SDL_Color Black = {0, 0, 0};

    // Variables
    SDL_Event event;
    int isComplete = 0;
    int nPisteur = 1;
    int hor = 0;
    int ver = 0;

    // SDL
    SDL_Rect textRect = {GetSystemMetrics(SM_CXSCREEN) * .5 - 1000 * WINDOW_RATIO, 100 * WINDOW_RATIO, 1000 * WINDOW_RATIO, 75 * WINDOW_RATIO};
    SDL_Rect numberRect = {GetSystemMetrics(SM_CXSCREEN) * .5 - 595 * WINDOW_RATIO, 350 * WINDOW_RATIO, 200 * WINDOW_RATIO, 200 * WINDOW_RATIO};
    SDL_Rect leftRect = {GetSystemMetrics(SM_CXSCREEN) * .5 - 700 * WINDOW_RATIO, 415 * WINDOW_RATIO, 80 * WINDOW_RATIO, 80 * WINDOW_RATIO};
    SDL_Rect rightRect = {GetSystemMetrics(SM_CXSCREEN) * .5 - 400 * WINDOW_RATIO, 415 * WINDOW_RATIO, 80 * WINDOW_RATIO, 80 * WINDOW_RATIO};

    rendererObject textRender;
    rendererObject numberRender;
    rendererObject leftRender;
    rendererObject rightRender;

    textRender.pSurface = TTF_RenderText_Solid(textFont, "Nombre de pisteurs", Black);
    numberRender.pSurface = TTF_RenderText_Solid(textFont, "1", Black);
    leftRender.pSurface = IMG_Load("./assets/misc/leftArrow.png");
    rightRender.pSurface = IMG_Load("./assets/misc/rightArrow.png");

    textRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, textRender.pSurface);
    numberRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, numberRender.pSurface);
    leftRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, leftRender.pSurface);
    rightRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, rightRender.pSurface);

    SDL_FreeSurface(textRender.pSurface);
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

    // Init crew (number menber)
    while (!isComplete){
        while (SDL_PollEvent(&event)){
            fflush(stdin);
            if (event.type == SDL_KEYDOWN)
                switch (event.key.keysym.sym){
                    case SDLK_RETURN: /*valid choice*/ isComplete = 1; break;
                    case SDLK_SPACE: /*valid choice*/ isComplete = 1; break;
                    case SDLK_KP_ENTER: /*valid choice*/ isComplete = 1; break;
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
            if (event.type == SDL_QUIT)
                *g = -1;
        }
        numberRender.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, numberRender.pSurface);
        SDL_RenderClear(sRenderer.pRenderer);
        PrintBackground(sRenderer);
        SDL_RenderCopy(sRenderer.pRenderer, textRender.pTexture, NULL, &textRect);
        SDL_RenderCopy(sRenderer.pRenderer, numberRender.pTexture, NULL, &numberRect);
        SDL_RenderCopy(sRenderer.pRenderer, leftRender.pTexture, NULL, &leftRect);
        SDL_RenderCopy(sRenderer.pRenderer, rightRender.pTexture, NULL, &rightRect);
        SDL_RenderPresent(sRenderer.pRenderer);
    }
    SDL_FreeSurface(numberRender.pSurface);

    // Init crew (position member)
    gotoxy(XMAX + 5, YMAX / 2);
    printf("Combien de pisteur souhaitez-vous avoir ? [1-10]\n");
    while (nPisteur < 1 || nPisteur > 10){
        gotoxy(XMAX + 5, YMAX / 2 + 1);
        scanf("%d", &nPisteur);
    }
    for (int i = 0; i < CREW; i++){
        if (i < nPisteur){
            crew[i].icone = 'P';
            while (hor < 1 || hor > XMAX){
                gotoxy(XMAX + 5, YMAX / 2 + 2);
                printf("Donnez la coordonnee horizontale du pisteur %d : [1-%d]\n", i + 1, XMAX);
                gotoxy(XMAX + 5, YMAX / 2 + 3);
                scanf("%d", &hor);
            }
            while (ver < 1 || ver > YMAX){
                gotoxy(XMAX + 5, YMAX / 2 + 4);
                printf("Donnez la coordonnee verticale du pisteur %d : [1-%d]\n", i + 1, YMAX);
                gotoxy(XMAX + 5, YMAX / 2 + 5);
                scanf("%d", &ver);
            }

            crew[i].x = hor - 1;
            crew[i].y = ver - 1;

            hor = 0;
            ver = 0;

            PrintScreen(field, crew, *monk, sRenderer);
        }else{
            crew[i].icone = '.';
            crew[i].x = -1;
            crew[i].y = -1;
        }
    }

    // Init monk
    InitMonstre(monk, crew);
    PrintScreen(field, crew, *monk, sRenderer);

    gotoxy(XMAX + 5, YMAX / 2);
    printf("Monk-C rode...");

    fflush(stdin);
    getchar();

    *g = 2;
}

// Round
void Round(struct tile field[XMAX][YMAX], struct pisteur crew[CREW], struct monstre* monk, int* g, struct renderer sRenderer){
    int isCrewDead = 1;

    // Determine if the crew is defeated
    for (int i = 0; i < CREW; i++)
        if (crew[i].icone == 'P')
            isCrewDead = 0;

    if (isCrewDead){
        *g = 4; // DEFEAT
    }else{
        // PHASE 0
        //   Footprints
        Footprint(field, crew, *monk);

        // PHASE I
        //   Pisteur detection
        for (int i = 0; i < CREW; i++){
            if (crew[i].icone == 'P'){
                crew[i].icone = '!'; // Set icone
                PrintScreen(field, crew, *monk, sRenderer);
                gotoxy(XMAX + 5, YMAX / 2);
                printf("Rapport du pisteur %d :\n", i + 1);
                Detection(field, crew[i], monk);
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
void Detection(struct tile field[XMAX][YMAX], struct pisteur p, struct monstre* monk){
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
