#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.c"

// PROTOTYPE
// Data
char GetAnswer();
void Init(struct tile[XMAX][YMAX], struct pisteur[CREW], struct monstre*, int*);
void Round(struct tile[XMAX][YMAX], struct pisteur[CREW], struct monstre*, int*);
void InitMonstre(struct monstre*, struct pisteur[CREW]);
void Footprint(struct tile[XMAX][YMAX], struct pisteur[CREW], struct monstre);
void Detection(struct tile[XMAX][YMAX], struct pisteur, struct monstre*);
void PisteurMovement(struct tile[XMAX][YMAX], struct pisteur*);
void MonstreMovement(struct tile[XMAX][YMAX], struct monstre*);
// Display
void PrintScreen(struct tile[XMAX][YMAX], struct pisteur[CREW], struct monstre);
void PrintField(struct tile[XMAX][YMAX]);
void PrintCrew(struct pisteur[CREW]);
void PrintCrewInfo(struct pisteur[CREW]);
void PrintMonstre(struct monstre);


// Initialization
void Init(struct tile field[XMAX][YMAX], struct pisteur crew[CREW], struct monstre* monk, int* g){
    int nPisteur = 0;
    int hor = 0;
    int ver = 0;

    // Print Screen
    PrintScreen(field, crew, *monk);

    // Init field
    for (int y = 0; y < YMAX; y++)
        for (int x = 0; x < XMAX; x++){
            field[x][y].traceMonstre = 0;
            field[x][y].tracePisteur = 0;
        }

    // Init crew
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

            PrintScreen(field, crew, *monk);
        }else{
            crew[i].icone = '.';
            crew[i].x = -1;
            crew[i].y = -1;
        }
    }

    // Init monk
    InitMonstre(monk, crew);
    PrintScreen(field, crew, *monk);

    gotoxy(XMAX + 5, YMAX / 2);
    printf("Monk-C rode...");

    fflush(stdin);
    getchar();

    *g = 2;
}

// Round
void Round(struct tile field[XMAX][YMAX], struct pisteur crew[CREW], struct monstre* monk, int* g){
    int isCrewDead = 1;

    // Determine if the crew is defeated
    for (int i = 0; i < CREW; i++)
        if (crew[i].icone == 'P')
            isCrewDead = 0;

    if (isCrewDead){
        *g = 4; // DEFEAT
    }else{
        // PHASE 0
        //   Footprints OK
        Footprint(field, crew, *monk);

        // PHASE I
        //   Pisteur detection OK
        for (int i = 0; i < CREW; i++){
            if (crew[i].icone == 'P'){
                crew[i].icone = '!'; // Set icone
                PrintScreen(field, crew, *monk);
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
                    PrintScreen(field, crew, *monk);
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

// Get answer from user
char GetAnswer(){
    char answer = 'x';
    while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N'){
        fflush(stdin);
        answer = getchar();
    }
    return toupper(answer);
}

// Print crew
void PrintCrewInfo(struct pisteur crew[CREW]){
    for (int i = 0; i < CREW; i++){
        gotoxy(XMAX + 5, i + 1);
        printf("P%d : %d | %d", i, crew[i].x, crew[i].y);
    }
}

// Print the field
void PrintField(struct tile field[XMAX][YMAX]){
    for (int y = 0; y < YMAX; y++){
        for (int x = 0; x < XMAX; x++){
                gotoxy(x + 2 + XOFFSET, y + 3 + YOFFSET);
                printf(" ");
        }
    }
}

// Print the field and crew members
void PrintCrew(struct pisteur crew[CREW]){
    for (int i = 0; i < CREW; i++){
        gotoxy(crew[i].x + 2 + XOFFSET, crew[i].y + 3 + YOFFSET);
        if (crew[i].icone == 'P' || crew[i].icone == '?'|| crew[i].icone == '!')
            printf("%c", crew[i].icone);
    }
}

void PrintScreen(struct tile field[XMAX][YMAX], struct pisteur crew[CREW], struct monstre monk){
    system("cls");
    printf("       --- La Traque ---");
    gotoxy(1 + XOFFSET, 2 + YOFFSET);
    for (int i = 0; i < XMAX + 2; i++)
        printf("#");
    gotoxy(1 + XOFFSET, YMAX + 3 + YOFFSET);
    for (int i = 0; i < XMAX + 2; i++)
        printf("#");

    for (int i = 0; i < YMAX + 2; i++){
        gotoxy(1 + XOFFSET, i + 2 + YOFFSET);
        printf("#");
        gotoxy(XMAX + 2 + XOFFSET, i + 2 + YOFFSET);
        printf("#");
    }
    PrintField(field);
    PrintCrew(crew);
    // PrintMonstre(monk);
}

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

void PrintMonstre(struct monstre monk){
    gotoxy(XMAX + 5, 16);
    printf("M : %d | %d | %d", monk.x, monk.y, monk.lifes);
}
