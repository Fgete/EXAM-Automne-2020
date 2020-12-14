#include <stdio.h>
#include <stdlib.h>

// PROTOTYPE
// Title
void MenuTitle(int*);
void MenuVictory(int*);
void MenuDefeat(int*);

// Menu title
void MenuTitle(int* g){
    char answer;

    system("cls");

    printf("   ### LA TRAQUE ###\n");
    printf("\nMonk-C s'est echappe. Il rode dans la region.\nVous etes le responsable d'un groupe de pisteurs.\nCeux-ci vous informent des traces qu'ils decouvrent : ou et surtout depuis quand le monstre est passe par la.\nMais attention, Monk-C est intelligent, et si vous n'y prenez garde, il aneantira vos pisteurs un a un.\n");

    printf("\nVoulez-vous jouer ? [Y/N]\n");
    answer = GetAnswer();
    if (answer == 'Y')
        *g = 1;
    else
        *g = -1;
}

// Menu victory
void MenuVictory(int* g){
    system("cls");

    printf("   ### LA TRAQUE ###\n");
    printf("\nFELICITATION ! Vous avez abattu le monstre qui rodait dans ces bois.\n");

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
