#include <stdio.h>
#include <stdlib.h>
#include "functions.c"
#include "titles.c"

struct tile field[XMAX][YMAX];
struct pisteur crew[CREW];
struct monstre monk;

int main()
{
    int gameState = 0;

    while (gameState != -1){
        switch (gameState){
        case 0:
            // Menu
            MenuTitle(&gameState);
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

    system("cls");
    printf("Au revoir.\n");
    return 0;
}
