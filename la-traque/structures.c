#include <stdio.h>
#include <stdlib.h>

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

#define XMAX 29
#define YMAX 14
#define CREW 10
#define MAXLIFE 4

#define XOFFSET 1
#define YOFFSET 0

#define ACCURACY 40

typedef struct tile{
    int traceMonstre;
    int tracePisteur;
}tile;

typedef struct pisteur{
    int x;
    int y;
    char icone;
}pisteur;

typedef struct monstre{
    int x;
    int y;
    int lifes;
}monstre;
