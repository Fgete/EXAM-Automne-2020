#include "structures.c"

// PROTOTYPES
void PrintScreen(struct tile[XMAX][YMAX], struct pisteur[CREW], struct monstre);
void PrintField(struct tile[XMAX][YMAX]);
void PrintCrew(struct pisteur[CREW]);
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

// Print screen
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
    // PrintCrewInfo(crew);
    // PrintMonstre(monk);
}

// Debug monster
void PrintMonstre(struct monstre monk){
    gotoxy(XMAX + 5, 16);
    printf("M : %d | %d | %d", monk.x, monk.y, monk.lifes);
}
